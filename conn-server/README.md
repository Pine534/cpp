1.用boost asio的socket
2.创建服务端acceptor:
    1.Acceptor.async_accept接收并创建socket
    2.socket对象绑定到类对象中，并给编号、交由AllClients管理


3.socket的async_receive：
    1.刷新ActiveTime
    2.SetProcessPtoReady(true)
    3.NetSched.Dispatch()

4.socket的async_write:
    1.刷新ActiveTime

5.socket的Timer:
    1.0.1s一次
    2.发数据
    3.检查ActiveTime




```C++
typedef unsigned char byte;

class TScheduler{
    Container<std::pair<long long, xynet::TVFD>> mQueue;// 存放待处理的客户端,优先队列，根据用户消耗的时间做优先排序， 可以先用普通的队列FIFO
    std::unique_ptr<asio::deadline_timer> mTimerPtr;//定时统计，暂且不管
    int Poll();// mQueue中取请求，然后调用Client->ProcessPto()去让conn线程处理
    void Dispatch(std::shared_ptr<TClient> pClient);
}

std::unordered_map<xynet::TVFD, std::shared_ptr<TClient> > AllClients;
const int PACKSIZE = 1 << 16;
class TClient{
    static GVfd = 100;
    asio::ip::tcp::socket Socket; //连接
    asio::ip::tcp::endpoint endpoint;//ip
    asio::io_service::strand Strand;//async_write保序用的,可以用给service post任务,同一Strand中的任务会FIFO
    std::unique_ptr<asio::deadline_timer> TimerPtr;//定时器：0.1s执行一次、心跳10min、发送SendBuffer中的数据
    int Vfd = GVfd++;
    std::shared_ptr<ZLIB> DicPtr;//压缩用，暂且不搞
	// asio::ip::tcp::endpoint endpoint;
    time_t ActiveTime; //上次收发时间，用来判断超时
    byte RecvBuffer[PACKSIZE * 2];
    byte* RecvBufHead = RecvBuffer;
    byte* RecvBufTail = RecvBuffer;
    const byte* const RecvBufEnd = RecvBuffer + sizeof(RecvBuffer);
    byte SendBuffer[PACKSIZE * 2];
    byte* SendBufTail = SendBuffer;
    const byte* const SendBufEnd = SendBuffer + sizeof(SendBuffer);
    bool ProcessPtoFlag;   // 协议处理状态 
    std::atomic_flag Writing; //async_write的时候用的是同一个SendBuffer，通过cas控制不会同时执行多个async_write

    int ProcessPto();//处理接收到的消息，拆包，然后发给主线程处理(涉及Lua层)
    void Start();//执行StartTimer()和StartRead()
    void StartTimer();//TimerPtr->expires_from_now/TimerPtr->async_wait
    void StartRead();//async_receive 接收到数据后:刷新ActiveTime、SetProcessPtoReady(true)、
    void SetProcessPtoReady(bool Flag);//如果为true，通知调度器NetSched.Dispatch(self)
    bool CachePto(const xynet::byte* ptodata, size_t Len);//粘包，放到SendBuffer，满则触发ZipCachePto();
    int ZipCachePto();//压缩
    void FlushZipData();//发送数据 async_write
    void Post(HANDLER&& Func);//Strand.post
    
}
```
    
NetService:
1.TScheduler::Dispatch, 把请求放到mQueue
2.控制net线程主循环在空闲时每0.1s循环一次

ConnService:
1.执行TClient.Post



net线程：
1.NetService.poll()
2.NetSched.Poll()

conn线程:
1.ConnService.Run()