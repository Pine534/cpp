#include <deque>
#include <memory>
#include <iostream>
#include <boost/asio.hpp>
#include <main.h>

using namespace std;
using namespace boost;

namespace conn{
const int PACKSIZE = 1 << 16;
enum class ClientST{ESTABLISHED, CLOSED};
enum class TScheST{RUNNING, CLOSED};

class TClient:public std::enable_shared_from_this<TClient>{
    private:
    int Vfd;
    asio::ip::tcp::socket Socket;
    // asio::ip::tcp::endpoint EndPoint;
    asio::strand<asio::executor> Strand;
    std::unique_ptr<asio::deadline_timer> TimerPtr;
    std::chrono::_V2::system_clock::time_point ActiveTime;

    byte RecvBuffer[PACKSIZE * 2];
    byte* RecvBufHead = RecvBuffer;
    byte* RecvBufTail = RecvBuffer;
    const byte* const RecvBufEnd = RecvBuffer + sizeof(RecvBuffer);
    byte SendBuffer[PACKSIZE * 2];
    byte* SendBufTail = SendBuffer;
    const byte* const SendBufEnd = SendBuffer + sizeof(SendBuffer);
    bool ProcessPtoFlag;   // 协议处理状态 
    atomic_flag Writing;
    asio::streambuf StreamBuffer;
    ClientST State;

    

    public:
    TClient(asio::ip::tcp::socket&& _Socket);
    ~TClient(){
        Socket.cancel();
        cout<< "TClient Destroyed" << endl;
    }

    static int gVfd;
    void ProcessPto();//处理接收到的消息，拆包，然后发给主线程处理(涉及Lua层)
    void Start();//执行StartTimer()和StartRead()
    void StartTimer();//TimerPtr->expires_from_now/TimerPtr->async_wait
    void StartRead();//async_receive 接收到数据后:刷新ActiveTime、SetProcessPtoReady(true)、

    void CachePto(const byte* ptodata, size_t Len);//粘包，放到SendBuffer，满则触发ZipCachePto();
    void ZipCachePto();//压缩
    void FlushZipData();//发送数据 async_write
    template <typename Function>
     void Post(Function&& Func){
     	asio::post(Strand, std::forward<Function>(Func));
     };//Strand.post

    int GetVfd() const{return Vfd;}
    void CheckAlive();
    void Close();
    void SetReady(bool Flag) {ProcessPtoFlag = Flag;};//如果为true，通知调度器NetSched.Dispatch(self)
    bool GetReady() const {return ProcessPtoFlag;};
    void SetState(ClientST _State) {
        State = _State;
    }
    ClientST GetState(){
        return State;
    }

};


class TScheduler{
    std::deque<int> mQueue;
    TScheST State;
    public:
    TScheduler(){};
    ~TScheduler(){};
    int Poll();
    void Dispatch(std::shared_ptr<TClient> client);
    void SetState(TScheST _State) {
        State = _State;
    }
    TScheST GetState() {
        return State;
    }

};

void Init();
void ShutDown();
bool CloseVfd(int Vfd);
}