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
using namespace std;

#include "proto/ping.pb.h"

#define MAX_LINE 16

void do_read(evutil_socket_t fd, short events, void *arg);
void do_write(evutil_socket_t fd, short events, void *arg);


void
readcb(struct bufferevent *bev, void *ctx)
{
    printf("1\n");
    struct evbuffer *input, *output;
    char *line;
    size_t n;
    int i;
    input = bufferevent_get_input(bev);
    output = bufferevent_get_output(bev);

    while ((line = evbuffer_readln(input, &n, EVBUFFER_EOL_LF))) {
        printf("%s\n", line);
        evbuffer_add(output, line, n);
        evbuffer_add(output, "\n", 1);
        free(line);
    }

    if (evbuffer_get_length(input) >= MAX_LINE) {
        /* Too long; just process what there is and go on so that the buffer
         * doesn't grow infinitely long. */
        char buf[1024];
        while (evbuffer_get_length(input)) {
            int n = evbuffer_remove(input, buf, sizeof(buf));
            printf("%s\n", buf);
            evbuffer_add(output, buf, n);
        }
        evbuffer_add(output, "\n", 1);
        // bufferevent_write_buffer(bev, output);
    }
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

// protobuf foo
int serialize_foo() {
    ping::Ping ping;
    ping.set_id(1);
    ping.set_name("first");
    ping.set_num(1,1);
    ping.add_num(2);
    ping.add_num(3);

    fstream output("file", ios::out | ios::trunc | ios::binary);
    if(!ping.SerializeToOstream(&output)) {
        cout << "SerializeToOstream Failed" << endl;
    }
    cout << "ByteSizeLong:" <<  ping.ByteSizeLong() << endl;

}

int deserialize_foo() {
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
    // setvbuf(stdout, NULL, _IONBF, 0);

    // run();
    // return 0;

    serialize_foo();
    deserialize_foo();
}