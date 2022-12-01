/* For sockaddr_in */
#include <netinet/in.h>
/* For socket functions */
#include <sys/socket.h>
/* For fcntl */
#include <fcntl.h>

#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>

#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <fstream>
#include <iostream>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
using namespace std;

using namespace google::protobuf::io;

#include "ping.pb.h"

#define MAX_LINE 16

void do_read(evutil_socket_t fd, short events, void *arg);
void do_write(evutil_socket_t fd, short events, void *arg);


void
readcb(struct bufferevent *bev, void *ctx)
{
    // 读取不了的原因是因为这个值初始化为0， 但不知道什么因素会影响初始值
    google::protobuf::uint32 size = 10000;
    struct evbuffer *input, *output;
    input = bufferevent_get_input(bev);
    output = bufferevent_get_output(bev);
    
    // 这里+1大概是为了留一个\0
    int buf_size = evbuffer_get_length(input) + 1;
    char *buffer[buf_size];
    cout << "buffer len is " << buf_size << endl;

    evbuffer_remove(input, &buffer, buf_size);
    // 16进制输出buffer的值
    printf("%s\n", buffer);
    
    cout << "size is " << size << endl;
    ArrayInputStream ais(buffer, size);
    CodedInputStream coded_input(&ais);
    cout << "size is " << size << endl;
    coded_input.ReadVarint32(&size);
    cout << "size is " << size << endl;
    printf("%x \n", *buffer);
    
    CodedInputStream::Limit msgLimit = coded_input.PushLimit(size);
    ping::Ping ping;
    ping.ParseFromCodedStream(&coded_input);
    coded_input.PopLimit(msgLimit);
    cout << "msg is " << ping.DebugString() << endl;


    ping::Pong pong;
    pong.set_id(ping.id());
    pong.set_name(ping.name());
    int sum = 0;
    // 这里不知道为什么一执行前面的就解析不了
    for (int i = 0; i < ping.num_size(); i++)
    {
        sum += ping.num(i);
    }
    pong.set_sum(sum);
    cout << "Pong Msg :" << pong.DebugString() << endl;

    int ssize = pong.ByteSizeLong() + 1;
    cout << "Pong Size = " << ssize << endl;
    char *sbuffer[ssize];
    google::protobuf::io::ArrayOutputStream aos(sbuffer, ssize);
    google::protobuf::io::CodedOutputStream *co = new google::protobuf::io::CodedOutputStream(&aos);
    co->WriteVarint32(pong.ByteSizeLong());
    pong.SerializeToCodedStream(co);
    cout << "Pong Size = " << ssize << endl;
    evbuffer_add(output, sbuffer, ssize);
    cout << "Sended" << endl;

}

void
errorcb(struct bufferevent *bev, short error, void *ctx)
{
    
    if (error & BEV_EVENT_EOF) {
        printf("BEV_EVENT_EOF\n");
        /* connection has been closed, do any clean up here */
        /* ... */
    } else if (error & BEV_EVENT_ERROR) {
        printf("BEV_EVENT_ERROR\n");
        /* check errno to see what error occurred */
        /* ... */
    } else if (error & BEV_EVENT_TIMEOUT) {
        printf("BEV_EVENT_TIMEOUT\n");
        /* must be a timeout event handle, handle it */
        /* ... */
    }
    bufferevent_free(bev);
}

void
do_accept(evutil_socket_t listener, short event, void *arg)
{
    printf("accept\n");
    struct event_base *base = static_cast<event_base *>(arg);
    struct sockaddr_storage ss;
    socklen_t slen = sizeof(ss);
    int fd = accept(listener, (struct sockaddr*)&ss, &slen);
    if (fd < 0) {
        perror("accept");
    } else if (fd > FD_SETSIZE) {
        close(fd);
    } else {
        struct bufferevent *bev;
        evutil_make_socket_nonblocking(fd);
        bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
        bufferevent_setcb(bev, readcb, NULL, errorcb, NULL);
        bufferevent_setwatermark(bev, EV_READ, 0, MAX_LINE);
        bufferevent_enable(bev, EV_READ|EV_WRITE);
    }
}

void
run(void)
{
    evutil_socket_t listener;
    struct sockaddr_in sin;
    struct event_base *base;
    struct event *listener_event;

    base = event_base_new();
    if (!base)
        return; /*XXXerr*/

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(40713);

    listener = socket(AF_INET, SOCK_STREAM, 0);
    evutil_make_socket_nonblocking(listener);

#ifndef WIN32
    {
        int one = 1;
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    }
#endif

    if (bind(listener, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
        perror("bind");
        return;
    }

    if (listen(listener, 16)<0) {
        perror("listen");
        return;
    }

    listener_event = event_new(base, listener, EV_READ|EV_PERSIST, do_accept, (void*)base);
    /*XXX check it */
    event_add(listener_event, NULL);

    event_base_dispatch(base);
}


void deserialize_foo() {
    fstream input("file", ios::in | ios::binary);
    ping::Ping ping;
    if(!ping.ParseFromIstream(&input)){
        cout << "ParseFromIstream Failed" << endl;
    }
    cout << ping.id() << ping.name() << ping.num_size() << endl;
}

int
main(int c, char **v)
{
    setvbuf(stdout, NULL, _IONBF, 0);

    run();
    return 0;

}