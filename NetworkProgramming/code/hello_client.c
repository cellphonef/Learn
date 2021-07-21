#include <stdio.h>       /* for printf */
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>      /* for memset */
#include <netinet/in.h>  /* for inet_addr */
#include <arpa/inet.h>   /* for htons inet_addr */
#include <stdlib.h>      /* for atoi */
#include <unistd.h>      /* for read */

void error_handling(char* message);

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    /* 创建客户端socket */
    int client_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (client_sock == -1) 
    {
        error_handling("socket() error!");
    }

    /* 初始化要连接的服务端地址信息 */
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    /* 客户端发起连接请求 */
    if (connect(client_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
    {
        error_handling("connect() error!");
    }

    /* 与服务器端进行数据传输 */
    char message[30];
    int str_len = read(client_sock, message, sizeof(message) - 1);
    if (str_len == -1)
    {
        error_handling("read() error!");
    }

    printf("Message from server: %s \n", message);
    close(client_sock);
    return 0;

}

/* 错误处理函数 */
void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
