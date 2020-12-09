#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define IN 0
#define OUT 1
#define LOW 0
#define HIGH 1
#define PIN 20
#define POUT 21
#define VALUE_MAX 256
#define BUFFER_MAX 3
#define DIRECTION_MAX 45

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main()
{
    int serv_sock, clnt_sock = -1;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;
    int sock = socket(PF_INET,SOCK_STREAM,0);

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(8888);
    
    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        error_handling("bind() error");
        close(serv_sock);

    } 
        int kk=0;
        int a = listen(serv_sock, 5);
        if (a == -1)
            error_handling("listen() error");
        if (clnt_sock < 0)
        {
            clnt_addr_size = sizeof(clnt_addr);
            clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr,
                               &clnt_addr_size);
            printf("%d\n", clnt_addr.sin_addr.s_addr);
            if (clnt_sock == -1)
                error_handling("accept() error");
        }
        char msg[100]="0";
        while (1)
        {
            scanf("%s",msg);
            write(clnt_sock, msg, sizeof(msg));
            printf("msg = %s\n", msg);
            if(!strcmp("1",msg))
            {
                break;
            }
        }

    close(serv_sock);
    return (0);
}