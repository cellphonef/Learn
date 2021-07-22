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




## socket协议及数据传输特性



socket type

面向连接的socket（SOCK_STREAM）

面向连接的socket有什么特点呢？
- 传输过程中数据不会丢失。
- 按序传输数据。
- 传输的数据不存在数据边界。


面向消息的socket（SOCK_DGRAM）


## 地址族与数据顺序







## 基于TCP的服务端和客户端







## 基于UDP的服务端和客户端

UDP服务器端/客户端不像TCP那样在连接状态下交换数据，因此与TCP不同，无需经过连接过程。也就是说，不必调用TCP连接过程中调用的listen函数和accept函数。





### 编写基于UDP的回声服务器端/客户端程序















