#include <stdio.h>        /* for printf fputs */
#include <sys/types.h>
#include <sys/socket.h> 
#include <string.h>       /* for memset */
#include <arpa/inet.h>    /* for htonl htons */
#include <stdlib.h>       /* for atoi  */
#include <unistd.h>       /* for write */

void error_handling(char* message);

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    /* 创建服务端socket */
    int serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
    {
        error_handling("socket() error!");
    }

    /* 初始化地址信息 */
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    /* 将服务端socket绑定到该地址 */
    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
    {
        error_handling("bind() error!");
    }

    /* 将服务端socket转为可连接状态 */
    if (listen(serv_sock, 5) == -1)
    {
        error_handling("listen() error!");
    }

    /* 受理客户端连接请求 */
    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    int client_sock = accept(serv_sock, (struct sockaddr*)&client_addr, &client_addr_size);
    if (client_sock == -1)
    {
        error_handling("accept() error!");
    }

    /* 与客户端进行数据传输 */
    char message[] = "Hello world!";
    write(client_sock, message, sizeof(message));
    close(client_sock);
    close(serv_sock);
    return 0;
}

/* 错误处理函数 */
void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
