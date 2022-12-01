#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>

#include "ping.pb.h"
#include <ostream>
#include <iostream>
using namespace std;
using namespace google::protobuf::io;

int
run(void)
{
    const char* hello = "Hello,123123123123123213";
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sin;
    

    sin.sin_family = AF_INET;
    // sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(40713);
    inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr);
    if (connect(sock, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
        printf("connect failed\n");
        return -1;
    }


    ping::Ping ping;
    ping.set_id(1);
    ping.set_name("first");
    ping.add_num(1);
    ping.add_num(2);
    ping.add_num(3);
    // 这里+1是留一个数字来表示后面payload的长度， 为什么是1有待研究
    int size = ping.ByteSizeLong() + 1;
    char *buffer[size];
    ArrayOutputStream aos(buffer, size);
    CodedOutputStream *co = new CodedOutputStream(&aos);
    co->WriteVarint32(ping.ByteSizeLong());
    ping.SerializeToCodedStream(co);

    
    printf("connected\n");
    int ret = send(sock, buffer, size, 0);
    printf("sended %x %d\n", *buffer, size);

    google::protobuf::uint32 rsize;
    // MSG_WAITALL才会阻塞
    //这里写死了接收长度， 正确的做法应该是先读出第一个字节得到payload长度，然后等接收达到指定长度再解析，太复杂了先不写了
    recv(sock, buffer, 12, MSG_WAITALL);
    ArrayInputStream ais(buffer, rsize);
    CodedInputStream coded_input(&ais);
    coded_input.ReadVarint32(&rsize);
    cout << "size is " << size << endl;
    google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit(rsize);
    ping::Pong pong;
    pong.ParseFromCodedStream(&coded_input);
    coded_input.PopLimit(msgLimit);
    cout << "msg is " << pong.DebugString() << endl;
    
    return 0;

}


int main()
{
   return run();
}