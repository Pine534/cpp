#include <thread>
#include <chrono>
#include "conn.h"

namespace conn {
int TClient::gVfd = 0;
static asio::io_context NetService;
static asio::ip::tcp::acceptor Acceptor(NetService, asio::ip::tcp::endpoint(asio::ip::address::from_string("127.0.0.1"), 5340));
// static asio::deadline_timer NetTimer{NetService};

asio::io_context ConnService;
static std::unique_ptr<boost::asio::io_context::work> ConnWorkPtr;
static TScheduler NetScheduler;
static auto TimeOut = std::chrono::minutes(15);

static vector<std::shared_ptr<std::thread>> threadList;

static unordered_map<int, std::shared_ptr<TClient>> AllClients;

int TScheduler::Poll() {
    if(mQueue.empty()) return 0;
    int Vfd = mQueue.front();
    auto ClientPtr = AllClients[Vfd];
    
    ClientPtr->Post([ClientPtr, Vfd](){
        if(!ClientPtr->GetReady()) return;
        ClientPtr->SetReady(false);
        ClientPtr->ProcessPto();
        if(ClientPtr->GetReady()) {
            NetScheduler.Dispatch(ClientPtr);
        }else {
            ClientPtr->StartRead();
        }
    });
    cout << "queue pop" << endl;
    mQueue.pop_front();
    return 1;
}

void TScheduler::Dispatch(std::shared_ptr<TClient> ClientPtr) {
    int Vfd = ClientPtr->GetVfd();
    cout << "queue push:" << Vfd << endl;
    mQueue.push_back(Vfd);
}


TClient::TClient(asio::ip::tcp::socket&& _Socket):
    Socket(std::move(_Socket)),
    Strand(Socket.get_executor()),
    Vfd(gVfd++),
    ActiveTime(std::chrono::system_clock::now()),
    ProcessPtoFlag(false)
{
    TimerPtr = std::make_unique<asio::deadline_timer>(ConnService, boost::posix_time::milliseconds(100));
}

void TClient::Start() {
    StartTimer();
    StartRead();
}

void TClient::StartTimer() {
    if(State == ClientST::CLOSED) 
        return;
    TimerPtr->expires_from_now(boost::posix_time::milliseconds(1000));
    TimerPtr->async_wait([self = shared_from_this()](const boost::system::error_code& ec){
        if(ec) {
            cout << "async_wait Failed:" << ec.message() << endl;
        }else {
            self->ZipCachePto();
            self->CheckAlive();
            self->StartTimer();
        }
    });
}

void TClient::StartRead() {
    if(State == ClientST::CLOSED) 
        return;
    Socket.async_receive(asio::buffer(RecvBufTail, RecvBufEnd - RecvBufTail), [self = shared_from_this()](const boost::system::error_code& error, std::size_t recv_size){
        if(self->GetState() == ClientST::CLOSED) {
            cout << "OnReceive: Client has closed" << endl; 
            return;
        }
        cout << "Client Read" << endl;
        self->RecvBufTail += recv_size;
        self->ActiveTime = std::chrono::system_clock::now();
        self->SetReady(true);
        NetScheduler.Dispatch(self);

    });
}

void TClient::ProcessPto() {
    uint8_t Header = 0;
    memcpy(&Header, RecvBufHead, 1);
    int UsedLen = 0;
    int HeaderLen = 0;
    int PtoLen = 0;
    if((Header >> 6) & 0x03) { // 11000000  判断前2位是否为1
        HeaderLen = (Header >> 6) & 0x03;
        memcpy(&PtoLen, RecvBufHead + 1, HeaderLen);
        UsedLen = 1 + HeaderLen + PtoLen;
    } else {
        PtoLen = Header & 0x3f; //00111111  判断后6位是否为1
        UsedLen = 1 + PtoLen;
    }
    cout << "ProcessPto Len:" << UsedLen << " " << 1 << " " << HeaderLen << " " << PtoLen << endl;
    if(RecvBufTail - RecvBufHead < UsedLen) {
        cout << "ProcessPto not enough data:" << RecvBufTail - RecvBufHead << " " << UsedLen << endl;
        return;
    }
    

    auto PtoData = std::shared_ptr<byte>(new byte[UsedLen],[](byte* p) {cout << "Try delete p" <<endl;delete[] p;});
    memcpy(PtoData.get(), RecvBufHead + UsedLen - PtoLen, PtoLen);
    
    RecvBufHead += UsedLen;


    //TODO 暂时把拆出来的包重新发给下个Vfd或者自己
    RunInMainThread([UsedLen, Vfd = this->Vfd, PtoData]() {
        int TarVfd = Vfd;
        if(AllClients.find(Vfd + 1) != AllClients.end()) {
            TarVfd = Vfd + 1;
        }
        auto TarClient = AllClients[TarVfd];
        TarClient->CachePto(PtoData.get(), UsedLen);

    });

}

//TODO 装包
void TClient::CachePto(const byte* ptodata, size_t Len) {
    uint8_t Header = 0;
    int ExtLen = 0;
    if(Len > 0x3f) {
        int tmplen = Len;
        while(tmplen >= 8) {
            ExtLen++;
        }
        Header |= (ExtLen << 6);
    } else {
        Header |= Len;
    }
    int TotalLen = Len + ExtLen + 1;
    cout << "CachePto Len:" << TotalLen << " " << 1 << " " << ExtLen << " " << Len << endl;
    if(SendBufTail + TotalLen > SendBufEnd) {
        ZipCachePto();
    }
    if(SendBufTail + TotalLen > SendBufEnd) {
        cout << "Ptodata too long: " << TotalLen << endl;
        return;
    }

    memcpy(SendBufTail, &Header, 1);
    SendBufTail += 1;
    if(ExtLen > 0) {
        memcpy(SendBufTail, &Len, ExtLen);
        SendBufTail += ExtLen;
    }
    memcpy(SendBufTail, ptodata, Len);
    SendBufTail += Len;

    ZipCachePto();
}

//TODO:tmp do nothing
void TClient::ZipCachePto() {
    if(SendBufTail == SendBuffer) {
        cout << "ZipCachePto Skip" << endl;
        return;
    }
    //直接用一次拷贝模拟压缩
    std::ostream OutStream(&StreamBuffer);
    OutStream.write(reinterpret_cast<const char*>(SendBuffer), SendBufTail - SendBuffer);
    SendBufTail = SendBuffer;
    FlushZipData();
}

void TClient::FlushZipData() {
    if(State == ClientST::CLOSED) 
        return;
    if(StreamBuffer.size() <= 0) {
        std::cout << "Nothing to Flush" << std::endl;
        return;
    }
    
    async_write(Socket, StreamBuffer, [](const system::error_code& ec,size_t Len){
        if(ec) {
            cout << "async_send fail: " << ec.message() << endl;
        }
        else {
            cout << "async_send succeed:" << Len << endl;
        }

    });
}


void TClient::CheckAlive() {
    auto Now = std::chrono::system_clock::now();
    if(Now - ActiveTime >= TimeOut) {
        
        CloseVfd(Vfd);
        cout << "OnTimeout: " << shared_from_this().use_count() << endl;
    }
}
void TClient::Close() {
    if(State == ClientST::CLOSED) return;
    ZipCachePto();
    State = ClientST::CLOSED;
    Socket.cancel();
}

void StartAccept(){
    auto SocketPtr = make_shared<asio::ip::tcp::socket>(ConnService);
    Acceptor.async_accept(*SocketPtr, [SocketPtr](const system::error_code& ec){
        if(!ec) {
            cout << "Client Connect Succeeded" << endl;
            auto Client = make_shared<TClient>(std::move(*SocketPtr));
            Client->Start();
            AllClients.insert({Client->GetVfd(), Client});
            
        }else {
            cout << "Client Connect Failed:" << ec.message() << endl;
        }
        StartAccept();
    });
}

void NetThread(){
    pthread_setname_np(pthread_self(), "net");

    auto Internal = chrono::microseconds(1000);
    while(1) {
        int Count = NetService.poll();
        int PtoCount = NetScheduler.Poll();
        if(Count <= 1 && PtoCount <= 1) {
            NetService.run_for(Internal);
        }
        if(NetScheduler.GetState() != TScheST::RUNNING) {
            cout << "ConnService.stop()"  << endl;
            ConnWorkPtr.reset();
            ConnService.stop();
            break;
        }
    }
}

void Init() {
    
    StartAccept();
    std::thread net(NetThread);
    net.detach();
    ConnWorkPtr = std::make_unique<boost::asio::io_context::work>(ConnService);
    
    for(int i = 1; i <= 1; i++) {
        std::shared_ptr<std::thread> threadPtr = std::make_shared<std::thread>(([i](){
            string name = "conn" + to_string(i);
            pthread_setname_np(pthread_self(), name.c_str());
            ConnService.run();
        
        }));
        threadPtr->detach();
        threadList.push_back(std::move(threadPtr));

    }
}

void ShutDown() {
    NetScheduler.SetState(TScheST::CLOSED);
}

bool CloseVfd(int Vfd){
    if(AllClients.find(Vfd) == AllClients.end()) {
        return false;
    }
    auto Client = AllClients[Vfd];
    Client->Close();
    AllClients.erase(Vfd);
    return true;
}

}