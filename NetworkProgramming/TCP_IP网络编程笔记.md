# TCP/IP网络编程笔记

## 理解网络编程和套接字

网络编程就是编写程序使两台联网的计算机相互交换数据。

1. 两台计算机之间传输数据首先需要物理连接。如今大部分计算机都已经连接到庞大的互联网，因此不用担心这一点。
2. 在此基础上，只需要考虑如何编写数据传输软件。但实际上这也不用愁，因为操作系统会提供名为socket的部件。socket是网络数据传输用的软件设备。它封装了底层硬件细节，使得用户即使对网络数据传输原理不太熟悉，也能通过套接字完成数据传输。

由此来看，我们当前处在的地位如下：



> **问：网络编程又称为socket编程，为什么要用socket这个词呢？**
> 
> **答：**socket在英文中的含义是：插座。在我们日常生活中，我们把插头插到插座上就能从电网中获得电力供给，这里的插座就相当于电网当中的一个节点，我们可以从这个节点获取到电力。同样，为了与远程计算机进行数据传输，我们需要接入到互联网，即在互联网中创建一个新的互联网节点接入互联网才能与其他计算机互联通信，而socket就是我们在互联网中的一个节点。我们利用socket来与互联网上的其他计算机进行数据传输，就好像我们利用插座来获取电力一样。



### 基于Linux的文件操作







### 编写“Hello world！”服务端客户端程序

示例代码如下：
- [hello_server.c](https://github.com/cellphonef/Learn/blob/main/NetworkProgramming/code/hello_server.c)
- [hello_client.c](https://github.com/cellphonef/Learn/blob/main/NetworkProgramming/code/hello_client.c)

代码说明：
- 调用socket函数创建socket。
- 调用bind函数分配IP地址和端口号。
- 调用listen函数将socket转为可接收连接状态。
- 调用accept函数受理连接请求。如果在没有连接请求的情况下调用该函数，则不会返回，直到有连接请求为止。
- 创建socket，但此时socket并不马上分为服务器端和客户端。如果紧接着调用bind、listen函数将成为服务端socket；如果调用connect函数，将成为客户端socket。
- 调用connect函数向服务器端发送连接请求。



## socket协议及协议设置

socket协议的选择在创建socket时进行设置：

```c
#include <sys/socket.h>

/*
** domain   socket中使用的协议族（protocol family）。
** type     socket中使用的数据传输类型信息。
** protocol socket中使用的协议信息。
*/
int socket(int domain, int type, int protocol);
```



### 协议族

socket通信中的协议具有一些分类。通过socket函数的第一个参数传递socket中使用的协议分类信息。此协议分类信息称为协议族，可分为如下几类：

| 名称      | 协议族             |
| :-------- | ------------------ |
| PF_INET   | IPv4互联网协议族   |
| PF_INET6  | IPv6互联网协议族   |
| PF_LOCAL  | 本地通信UNIX协议族 |
| PF_PACKET | 底层socket的协议族 |
| PF_IPX    | IPX Novell协议族   |

通常我们只使用PF_INET对应的IPv4互联网协议族。其他协议族并不常用或尚未普及。



### socket数据传输类型

socket数据传输类型通过socket函数的第二个参数指定。

对于IPv4互联网协议族，有两种不同的数据传输类型。

#### 面向连接的socket（SOCK_STREAM）

面向连接的socket特点：
- 传输过程中数据不会丢失。
- 按序传输数据。
- 传输的数据不存在数据边界。



收发数据的socket内部有缓冲，简言之就是字节数组。通过socket传输的数据将保存到该数组。因此，收到数据并不意味着马上调用read函数。只要不超过数组容量，则有可能在数据填充满缓冲后通过一次read函数调用读取全部，也有可能分成多次read函数调用进行读取。





#### 面向消息的socket（SOCK_DGRAM）

面向消息的socket特点：







### 协议的最终选择

对于IPv4互联网协议族，只有两种数据传输类型，因此确定了前面两个参数即可确定所要使用的协议。因此，大部分情况下可以向第三个参数传递0。

```C
int tcp_sock = socket(PF_INET, SOCK_STREAM, 0);
int udp_sock = socket(PF_INET, SOCK_DGRAM, 0);
```



### 面向连接的socket: TCP socket示例

使用示例代码验证TCP socket如下特性：

* 传输的数据不存在数据边界。



示例代码：

* [tcp_server.c](https://github.com/cellphonef/Learn/blob/main/NetworkProgramming/code/tcp_server.c)
* [tcp_client.c](https://github.com/cellphonef/Learn/blob/main/NetworkProgramming/code/tcp_client.c)





## 地址族与数据顺序



### 地址信息的表示

应用程序中使用的IP地址和端口号以结构体的形式给出了定义。

#### 表示IPv4地址的结构体

填写地址信息时应以如下提问为线索进行：

1. 问题一：采用哪一种地址族？
2. 问题二：IP地址是多少？
3. 问题三：端口号是多少？

因此结构体定义为如下形态，此结构体作为地址信息传递给bind函数。

```C
struct sockaddr_in
{
    sa_family_t    sin_family;  /* 地址族 */
    uint16_t       sin_port;    /* 16位TCP/UDP端口号 */
    struct in_addr sin_addr;    /* 32位IP地址 */
    char           sin_zero[8]; /* 填充bits */
}

/* in_addr如下 */
struct in_addr
{
    In_addr_t s_addr;           /* 32为IPv4地址 */
}
```



### 网络字节序与地址变换









## 基于TCP的服务端和客户端



### 实现迭代服务器端/客户端——存在问题

本节编写回声（echo）服务器端/客户端。顾名思义，服务器端将客户端传输的字符串数据原封不动地传回客户端，就像回声一样。



示例代码：

* [echo_server.c](https://github.com/cellphonef/Learn/blob/main/NetworkProgramming/code/echo_server.c)
* [echo_client.c](https://github.com/cellphonef/Learn/blob/main/NetworkProgramming/code/echo_client.c)





### 实现计算服务器端/客户端——完美实现











## 基于UDP的服务端和客户端

UDP服务器端/客户端不像TCP那样在连接状态下交换数据，因此与TCP不同，无需经过连接过程。也就是说，不必调用TCP连接过程中调用的listen函数和accept函数。





### 编写基于UDP的回声服务器端/客户端程序















