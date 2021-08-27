# TCP_IP网络基础知识


什么是协议

一个协议定义了在两个或多个通信实体之间交换报文的格式次序，以及报文发送或接收一条报文或其他事件所采取的动作。

由以上定义可以知道协议规定一下几部分：
- 报文的语法格式。
- 报文的时序。
- 报文的动作。


因特网广泛的使用了协议。不同的协议用于完成不同的通信任务。由于完成的通信任务不同，因此协议的复杂度也不相同。


因特网的协议栈由五个层次组成（自顶向下）：
- 应用层
- 传输层
- 网络层
- 数据链路层
- 物理层


## 应用层


### HTTP

### STMP

### DNS——Domain Name System

The DNS is:
1. a distributed database implemented in a hierarchy of DNS servers.
2. an application-layer protocol that allow hosts to query the distributed databse.

DNS protocol runs over UDP and uses port 53.

DNS除了提供主机名到IP地址的转换外还提供以下服务：
- 主机别名（Host aliasing）。拥有复杂主机名的主机可以同时拥有一个或者多个别名。应用程序可以向DNS发送别名来获取主机的规范主机名和IP地址。
- 邮件服务器别名（Mail server aliasing）。
- 负载分配。


#### DNS协议工作概览

为了解决以上问题，DNS没有采用单机的方式，而是采用了大量以层次结构组织的分布式服务器的方式。

不像单机那样存储所有的映射，而是将所有的映射分散存储在所有DNS服务器中。



![hierarchy of DNS](img/TCP_IP网络基础知识_2021-08-26-16-20-49.png)

![iterative query](img/TCP_IP网络基础知识_2021-08-26-15-32-37.png)



#### DNS报文格式

DNS只有两种报文，即DNS请求报文和DNS应答报文，并且它们使用同样的报文格式。

每个DNS应答报文携带一个或多个资源记录。


一个资源记录（resource record）是一个四元组：
- `(Name, Value, Type, TTL)`

其中`TTL（Time-To-Live）`表示该资源记录有效时间，它决定了该记录什么时候应该从cache中清除。而`Name`和`Value`中根据`Type`不同有不同的含义：
- 如果`Type=A`，则`Name`表示主机名，而`Value`表示该主机名对应的IP地址。因此一个`Type=A`的资源记录提供主机名到IP地址的映射。
- 如果`Type=NS`，则`Name`表示一个域，而`Value`表示知道权威DNS服务器的主机名。因此这种资源记录用于
- 如果`Type=CNAME`，则`Value`是主机名别名`Name`的规范主机名。因此这种记录主要用于通过由主机名别名获得其规范主机名。
- 如果`Type=MX`，则是`Value`是邮件服务器别名`Name`对应的规范主机名。




为什么说DNS是应用层协议？
- 采用客户-服务器的通信模式。
- 依赖底层的端到端的传输协议来传输DNS报文。




### 作业


#### Review

**R. 为什么HTTP，SMTP和POP3使用TCP而不是UDP？**



## 传输层


### 可靠数据传输原则






## 补充：WireShark抓包工具

![WireShark](img/TCP_IP网络基础知识_2021-08-24-16-04-02.png)

WireShark界面包括五个组成部分：
- 命令菜单（command menu）。包括文件和捕获菜单，可以通过文件菜单保存捕获的数据或打开一个包含捕获数据的文件；捕获菜单可以控制捕获的开始和结束。
- 显示过滤说明（display filter specification）。可以输入协议名称或者其他信息用来过滤显示的包信息。
- 包列表窗口（packet-listing window）。以列表的方式显示捕获到的包，每行对应一个包，包括（包序号、时间、源地址、目的地址、使用协议、协议长度、以及该协议特定的信息）。点击每个显示栏可以进行排序。
- 包头详情窗口（packet-header details window）。显示在包列表窗口中选中的包的包头详细信息。
- 包的所有内容窗口（packet content window）。以十六进制和ASCII的形式显示被选中包的所有数据。







