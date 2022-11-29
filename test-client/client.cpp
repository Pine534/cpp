#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>

int
run(void)
{
    const char* hello = "Hello,123123123123123213";
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sin;
    char buffer[1024];

    sin.sin_family = AF_INET;
    // sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(40713);
    inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr);
    if (connect(sock, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
        printf("connect failed\n");
        return -1;
    }

    printf("connected\n");
    int ret = send(sock, hello, strlen(hello), 0);
    printf("sended %s %d\n", hello, ret);
    
    char sendline[16];
    while(1) {
        fgets(sendline,1024,stdin);
        int ret = send(sock, sendline, strlen(sendline), 0);
        printf("sended %d\n", ret);
        read(sock, buffer, 1024);
        printf("%s\n", buffer);
        memset(buffer, 0, sizeof(buffer));
        memset(sendline, 0, sizeof(sendline));
    }
    
    return 0;

}

int main()
{
   return run();
}