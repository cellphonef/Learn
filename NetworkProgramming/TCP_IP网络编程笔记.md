# TCP/IP网络编程笔记

## 理解网络编程和套接字

网络编程就是编写程序使两台联网的计算机相互交换数据。

1. 两台计算机之间传输数据首先需要物理连接。如今大部分计算机都已经连接到庞大的互联网，因此不用担心这一点。
2. 在此基础上，只需要考虑如何编写数据传输软件。但实际上这也不用愁，因为操作系统会提供名为socket的部件。socket是网络数据传输用的软件设备。它封装了底层硬件细节，使得用户即使对网络数据传输原理不太熟悉，也能通过套接字完成数据传输。

由此来看，我们当前处在的地位如下：



> 网络编程又称为socket编程，为什么要用socket这个词呢？
> 答：socket在英文中的含义是：插座。在我们日常生活中，我们把插头插到插座上就能从电网中获得电力供给，这里的插座就相当于电网当中的一个节点，我们可以从这个节点获取到电力。同样，为了与远程
> 计算机进行数据传输，我们需要接入到互联网，即在互联网中创建一个新的互联网节点接入互联网才能与其他计算机互联通信，而socket就是我们在互联网中的一个节点。我们利用socket来与互联网上的其他
> 计算机进行数据传输，就好像我们利用插座来获取电力一样。



### 编写“Hello world！”服务器端

示例代码如下：
- [hello_server.c](https://github.com/cellphonef/Learn/blob/main/NetworkProgramming/code/hello_server.c)
- [hello_client.c](https://github.com/cellphonef/Learn/blob/main/NetworkProgramming/code/hello_client.c)






