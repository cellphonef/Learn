
# 现代计算机体系结构

多个核只有一个核能够执行，其他的将会阻塞直到该核执行完。

# 多线程编程


学习多线程编程面临的最大的思维方式的转变有两点：
- 当前线程可能随时会被切换出去，或者说被抢占（preempt）了
- 多线程程序中事件的发生顺序不再具有全局同一的先后顺序了

**第一点意味着在多线程情况下，当线程从被抢占到切换回来执行下一条指令时，全局数据（包括当前进程在操作系统内核中的状态）可能已经被其他线程修改了。因此在没有适当同步的情况下，对于一些非原子操作由于抢占可能会导致错误。**

以下例子在多线程环境下可能会出现段错误：

```cpp
// 在逻辑与&&的前一个分支evaluate为true之后的那一刹那
// p可能被其他线程置为NULL或是被释放，后一个分支就访问了非法地址
if (p && p->next) { /* ...  */}
```

**第二点意味着**



原子操作

> **Q: How does multi-core CPU work? In terms of "communication". How do they "communicate" with each other. Do one core control others or they use another method for connection?**
>
> **A:** After a system is up and running, the different cores mostly communicate through shared memory. Most multiprocessors these days have coherent shared memory, so that changes to memory made by one core will be visible to the others. This is convenient, but sometimes the changes are not seen in the same order by different cores, so an elaborate system of locks and fences and complexity under the name of “memory ordering rules” is needed. The different cores are really co-equal and just run programs independently. Any coordination is a matter for software, either the OS or application code. 
> 
> Details：[answer](https://www.quora.com/How-does-multi-core-CPU-work-In-terms-of-communication-How-do-they-communicate-with-each-other-Do-one-core-control-others-or-they-use-another-method-for-connection)



> **Q: What happens when two CPU cores require write access to the same memory address at the same exact moment?**
> 
> A: [answer](https://www.quora.com/What-happens-when-two-CPU-cores-require-write-access-to-the-same-memory-address-at-the-same-exact-moment) 



锁

利用原子操作实现锁。




条件变量
