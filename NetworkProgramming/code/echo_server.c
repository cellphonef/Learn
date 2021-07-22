#include <stdio.h>        /* for printf fputs */
#include <sys/types.h>
#include <sys/socket.h> 
#include <string.h>       /* for memset */
#include <arpa/inet.h>    /* for htonl htons */
#include <stdlib.h>       /* for atoi  */
#include <unistd.h>       /* for write */

#define BUF_SIZE 1024
void error_handling(char* message);

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    /* ���������socket */
    int serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
    {
        error_handling("socket() error!");
    }

    /* ��ʼ����ַ��Ϣ */
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    /* �������socket�󶨵��õ�ַ */
    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
    {
        error_handling("bind() error!");
    }

    /* �������socketתΪ������״̬ */
    if (listen(serv_sock, 5) == -1)
    {
        error_handling("listen() error!");
    }

    /* ����ͻ����������� */
    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    char message[BUF_SIZE];
    for (int i = 0; i < 5; ++i)
    {
        int client_sock = accept(serv_sock, (struct sockaddr*)&client_addr, &client_addr_size);
        if (client_sock == -1)
        {
            error_handling("accept() error!");
        }
        else
        {
            printf("Connectd client %d \n", i+1);
        }
        /* ��ͻ��˽������ݴ��� */
        int str_len;
        while(str_len = read(client_sock, message, BUF_SIZE))
        {
            write(client_sock, message, str_len);
        }
        close(client_sock);
    
    }
    

    close(serv_sock);
    return 0;
}

/* �������� */
void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
