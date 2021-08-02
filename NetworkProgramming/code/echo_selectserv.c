#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/time.h>
#include <sys/select.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 100
void error_handling(char* msg);

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    int serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket() error!");

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    serv_addr.sin_port = htons(atoi(argv[1]));


    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error!");

    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error!");

    fd_set reads;
    fd_set copy_reads;
    FD_ZERO(&reads);
    FD_SET(serv_sock, &reads);
    char buf[BUF_SIZE];
    int fd_max = serv_sock;

    while (1)
    {

        copy_reads = reads;
        struct timeval timeout;
        timeout.tv_sec = 5;
        timeout.tv_usec = 5000;
        int result = select(fd_max + 1, &copy_reads, 0, 0, &timeout);
        if (result == -1)
        {
            error_handling("select() error");
        }
        else if (result == 0)
        {
            continue;
        }
        else 
        {
            for (int i = 0; i < fd_max + 1; i++)
            {
                if (FD_ISSET(i, &copy_reads))
                {
                    if (i == serv_sock)  // new connection!
                    {
                        struct sockaddr_in client_addr;
                        socklen_t client_addr_size = sizeof(client_addr);

                        int client_sock = accept(serv_sock, (struct sockaddr*)&client_addr, &client_addr_size);
                        if (client_sock == -1)
                            error_handling("accept() error!");
                    
                        FD_SET(client_sock, &reads);
                        if (fd_max < client_sock)
                            fd_max = client_sock;
                        printf("connected client: %d\n", client_sock);
                    }
                    else  // read message
                    {
                        int str_len = read(i, buf, BUF_SIZE);
                        if (str_len == 0) // close request!
                        {
                            FD_CLR(i, &reads);
                            close(i);
                            printf("closed client: %d\n", i);
                        }
                        write(i, buf, str_len); // echo!
                    }
                }
               
                  
            }

        }
    }

    close(serv_sock);
    return 0;

}

void error_handling(char* msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}