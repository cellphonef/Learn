#include <stdio.h>     /* for puts */
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <unistd.h>

#define BUF_SIZE 30

int main()
{
    fd_set reads, temps;
    int result, str_len;
    char buf[BUF_SIZE];
    struct timeval timeout;

    // 1.1 设置文件描述符
    FD_ZERO(&reads);
    FD_SET(0, &reads);

    while (1) {
        temps = reads;
        
        // 1.3 设置超时
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        // 2. 调用select函数
        result = select(1, &temps, 0, 0, &timeout);  // 1.2 设置监视范围

        // 3. 查看调用结果
        if (result == -1) 
        {
            puts("select() error!");
            break;
        } 
        else if (result == 0) 
        {
            puts("Time-out!");

        }
        else 
        {
            if (FD_ISSET(0, &temps))
            {
                str_len = read(0, buf, BUF_SIZE);
                buf[str_len] = 0;
                printf("message from console: %s", buf);
            }
        }

    }

}