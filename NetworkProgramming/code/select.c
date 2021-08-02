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

    // 1.1 �����ļ�������
    FD_ZERO(&reads);
    FD_SET(0, &reads);

    while (1) {
        temps = reads;
        
        // 1.3 ���ó�ʱ
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        // 2. ����select����
        result = select(1, &temps, 0, 0, &timeout);  // 1.2 ���ü��ӷ�Χ

        // 3. �鿴���ý��
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