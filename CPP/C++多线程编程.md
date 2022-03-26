
# 现代计算机体系结构


## 


context switches can only happen on interrupts, and interrupts happen before or after an instruction, not in the middle.

## Cache coherence

key point：为了保持缓存一致性，每个core都需要监听总线事务，而想要执行写操作的core也必须在总线上发起invalidate。



- 当多个核心同时写的情况，并不存在同时写的情况，只是写到当前核心的L1 cache上，再经过一定的cycle后通过总线广播同步到其他核心上。此时总线广播的动作由总线仲裁机制进行仲裁，即只有一个核心的写入动作会成功广播出去，另一个核心必须接收invalidate，然后重启操作。

- 当对总线加锁后，则CPU核心会通过总线告知其他核心要锁定的地址，如果其他核心需要修改对应的地址，就会停下来等待，直到对总线进行加锁的核心完成操作后再执行对应操作。




> **Q: How does multi-core CPU work? In terms of "communication". How do they "communicate" with each other. Do one core control others or they use another method for connection?**
>
> **A:** After a system is up and running, the different cores mostly communicate through shared memory. Most multiprocessors these days have coherent shared memory, so that changes to memory made by one core will be visible to the others. This is convenient, but sometimes the changes are not seen in the same order by different cores, so an elaborate system of locks and fences and complexity under the name of “memory ordering rules” is needed. The different cores are really co-equal and just run programs independently. Any coordination is a matter for software, either the OS or application code. 
> 
> **Details：**[answer](https://www.quora.com/How-does-multi-core-CPU-work-In-terms-of-communication-How-do-they-communicate-with-each-other-Do-one-core-control-others-or-they-use-another-method-for-connection)



> **Q: What happens when two CPU cores require write access to the same memory address at the same exact moment?**
> 
> A: [answer](https://www.quora.com/What-happens-when-two-CPU-cores-require-write-access-to-the-same-memory-address-at-the-same-exact-moment) 


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

在多线程编程中，我们有两个需求：
- 原子性需求
- 顺序性需求

**Atomicity** means that operation either executes fully and all it's side effects are visible, or it does not execute at all. So all other threads can either see state before the operation or after it.




## 原子操作

原子操作即满足原子性（要么执行完全，要么不执行，且执行过程不会被其他线程侵入干扰）的一系列操作，通常由底层硬件提供指令支持。这些原子操作是构建其他高级同步工具的基础。

常用的原子操作有:
- Test-And-Set (TSL)
- Compare-And-Swap (CAS)
- Load Link/S Condition (LL/SC)

### 原子操作的实现

在目前的SMP架构下（当然还有另一种架构），原子操作实现是通过总线锁或者缓存锁实现的，保证在一个core在操作时，其他core需要等待该core操作完成。




## 锁

原子操作能够满足简单操作的原子性需求，而对于复杂操作，我们需要其他的同步工具——锁。

的出现是为了满足互斥的需求。

### 锁的种类

锁的目的都是为了满足互斥访问，但是出于性能的考虑，再结合场景就出现了各种不同种类的锁：
- 自旋锁
- 睡眠锁
- 读写锁
- 

### 锁的实现

锁的实现一般来说依赖底层的硬件指令。






## 条件变量

**条件变量的出现是为了满足等待的需求。**

标准写法：

```CPP
// 初始化

pthread_mutex_t mtx;
pthread_cond_t cnd;


// 生产者
pthread_mutex_lock(&mtx);
while (list.IsFull()) {
    pthread_cond_wait(&mtx, &cnd);
}
produce();
pthread_cond_signal(&cnd);
pthread_mutex_unlock(&mtx);




// 消费者
pthread_mutex_lock(&mtx)
while (list.IsEmpty()) {
    pthread_cond_wait(&mtx, &cnd);
}
consume();
pthread_cond_signal(&cnd);
pthread_mutex_unlock(&mtx);
```


覆盖条件

当唤醒无法精确控制时，一个简单有效的方法就是广播，这样虽然会有一定的性能损失，但是能够使程序正确执行。




一些问题：
- [为什么pthread_cond_wait需要mutex参数？]()
- [Condvars: Signal With Mutex Locked Or Not?](https://1feng.github.io/2016/07/20/signal-with-mutex-locked-or-not/)