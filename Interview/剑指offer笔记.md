# 剑指offer

"我剑动了，剑指SXX"——RNG粉丝。



## 面试的流程

如果应聘者能够通过公司的简历筛选环节，那恭喜他取得了阶段性的成功。但是要拿到心仪的offer，应聘者还有更长的路要走，因为还需要进行面试。

---

### 面试的三种形式

面试主要有三种形式：

- 电话面试。
- 共享桌面远程面试。
- 现场面试。



#### 电话面试

顾名思义，电话面试是面试官以打电话的形式考查应聘者：

- 应聘者在电话面试的时候应该尽可能用形象的语言把细节说清楚。
- 如果在英语面试中没有听清或没有听懂面试官的问题，则应聘者要敢于说Pardon。



#### 共享桌面远程面试

共享桌面远程面试是指利用一些共享桌面的软件，应聘者把自己电脑的桌面共享给远程面试官：

- 思考清楚再编码。
- 保持良好的编码风格。
- 能够进行单元测试。
- 调试能力十分关键。

> 在共享桌面远程面试过程中，面试官最关心的是应聘者的编程习惯及调试能力。



**To-Do-List：**  

- [ ] 编码风格养成。
- [ ] 调试能力养成。



#### 现场面试

在通过电话面试和共享桌面远程面试之后，应聘者不久就会收到E-mail，邀请他去公司参加现场面试：

- 规划好路线并估算出行时间。
- 准备好得体的衣服。
- 注意面试邀请函里的面试流程。
- 准备几个问题。

---

### 面试的三个环节

通常面试官会把每一轮面试分为三个环节：

1. 首先是行为面试。面试官参照简历了解应聘者的过往经验。
2. 其次是技术面试。可能会要求应聘者现场写代码。
3. 最后是应聘者提问。



#### 行为面试

为了在行为面试中能够出色发挥，需要做好两件事：

- 准备一个自我介绍。
- 写好简历（非常重要）。



简历内容：

- 基本信息。

- 教育背景。
- 项目经验/工作经验。
- 技术栈。



**To-Do-List：**

- [ ] 简历制作。



#### 技术面试

技术面试主要考察应聘者的五种素质：

- 基础知识扎实全面，包括编程语言、数据结构、算法等。
- 能写出正确的、完整的、鲁棒性的高质量代码。
- 能思路清晰地分析、解决复杂问题。
- 能从时间、空间复杂度两方面优化算法效率。
- 具有优秀的沟通能力。



技术面试通用法则：

- 如果遇到简单的题目，则应聘者一定要注重细节，写出完整、鲁棒的代码。
- 如果遇到复杂的题目，则应聘者可以通过画图、举具体例子分析和分解复杂问题等方法厘清思想再动手编程，可能刚开始会写出一个能正确得出结果的不太高效的解法，这时应聘者应该尝试进行优化，力求找到最优解法。
- 尽量把解决前面问题的思路迁移到后面的问题中去，展示自己良好的学习能力。

#### 应聘者提问

推荐问的问题是与应聘的职位或者项目相关的问题。





## 技术面试——基础知识

面试的基础知识通常包括以下部分：

- 编程语言。
- 计算机基础：
  - 数据结构与算法。
  - 操作系统。
  - 计算机网络。
  - 计算机组成原理（少）。

---

### 编程语言

通常编程语言面试有三种类型：

- 题型一：概念题，询问概念。
- 题型二：分析题，分析代码运行结果。
- 题型三：实操题，代码实现某些操作。



本人主要编程语言是C/C++，以下列出一些C/C++面试题。



#### 概念题

概念题主要包括几个方面：

- C/C++基础。
- 内存管理。
- 面向对象。
  - 虚函数。
- STL。
- C++11新特性。



**面试题0x：编译链接模型?**





**面试题0x：const关键字的作用？**




> :warning: const全局变量默认只在当前文件可见，而non-const全局变量默认为所有文件可见。





**面试题0x：static关键字作用？**

static关键词有三种完全不同的用途：

1. 表示一个静态存储期的变量，且具有internal linkage（即static全局变量）。
2. 表示一个静态存储期的变量，但是只在一个局部作用域可见，保证仅初始化一次（即static局部变量）。
3. 表示一个class的静态成员，整个class共享一份，不绑定到任何对象实例（即static成员变量）。



static会生成Local Symbol。

补充：

static全局变量、static局部变量和全局变量都存放在数据段，因此在程序运行之前编译器已经分配好内存，但是初始化这些变量的时机在C和C++中有些不同：

- 在C中，采用的是编译期初始化，编译阶段分配好内存后就会进行初始化（直接将初始化值放在目标文件的.data段，未初始化值或初始化值为0的放在.bss段）。由于是编译期初始化，而编译采用的是各文件独立编译，编译器在编译时必须能够直接看到初始值，所以不能使用变量（使用变量需要程序运行然后从内存中获取，编译期还没运行），只能使用常量即字面值。
- 在C++中，引入了对象，静态对象和全局对象等非pod类型的变量不能采用编译期初始化，对象需要调用构造函数进行初始化并且调用析构函数进行销毁，这意味着需要执行相关代码，无法再编译期完成，因此在C++中，对于不同的static变量，需要采用不同的初始化手段：
  - 如果静态全局变量或全局变量是基本数据类型（POD），且初始化值是常量，则可以采用编译期初始化。
  - 如果静态全局变量或全局变量是非POD的对象类型，或初始值为非常量，则采用加载时初始化（程序运行main前执行入口函数进行初始化，执行出口函数进行销毁）。
  - 如果是静态局部变量，则采用运行时初始化（第一次执行该函数时进行初始化，并且只初始化一次，一般通过静态局部变量后面的一个32位内存位做标志来判断是否初始化）。



参考链接：

1. [C++中static变量的初始化](https://blog.csdn.net/qq_34139994/article/details/105157313)





**面试题0x：extern的作用？extern C的作用？**





**面试题0x：new/delete、malloc/free，底层使用什么进行分配？**

首先需要知道内存分配的每一层面：

｜分配｜释放｜类型｜可否重载｜
｜----｜----｜-------｜------------｜
｜malloc()｜free()｜C函数｜不可重载｜
|  new   | delete| C++表达式| 不可重载 |
|  ::operator new() |  ::operator delete()| C++   | 可以重载 |


new在C++具有固定行为，不可以被重载：
1. 调用operator new分配内存。
2. 调用对象的构造函数。

delete在C++中具有固定行为，不可以被重载：
1. 调用对象的析构函数。
2. 调用operator delete释放内存。

虽然new的行为固定，但是我们可以重载operator new。 


**面试题0x：浅拷贝和深拷贝有什么区别？**




**什么是内存泄漏？如何检测？**

内存泄漏，是指由于疏忽或错误造成程序未能释放已经不再使用的内存。内存泄漏并非指内存在物理上消失了，而是应用程序分配某段内存后，由于设计错误导致在释放该内存之前就失去了对该段内存的控制，从而造成内存的浪费。





**面试题0x：虚函数表**

**面试题0x：构造函数和析构函数可以是虚函数吗？可以调用虚函数吗？**

构造函数不能是虚函数，而析构函数在某些情况下必须为虚函数。





**面试题0x：STL用过吗？xxx是怎么实现的？**

STL主要包括三个部分：容器、算法、迭代器。

| 容器名         | 底层数据结构 | 备注                     |
| -------------- | ------------ | ------------------------ |
| vector         | 数组         |                          |
| deque          | 数组+迭代器  |                          |
| list           | 双向链表     |                          |
| set            | 红黑树       |                          |
| map            | 红黑树       |                          |
| unordered_set  | 哈希表       | 解决冲突的方法是拉链法。 |
| unordered_map  | 哈希表       |                          |
| stack          | deque        |                          |
| queue          | deque        |                          |
| priority_queue | vector       |                          |
| heap           | vector       |                          |


vector底层是一个动态数组，包括三个迭代器（由于vector底层是数组，因此可以直接使用元素类型指针作为迭代器），start、finish和end_of_storage。其中[start, finish)表示已经被使用的空间范围（size），[start, end_of_storage)表示整块连续空间（capacity）。当空间不够装下数据时，会自动扩容，重新申请一段连续空间（大小为原来的2倍），然后将原来空间的数据拷贝到新的空间，接着释放原空间（简称三部曲：“申请-拷贝-释放”）。

resize和reserve的区别？
- resize(n, val), Resizes the container so that it contains n elements.
  - If n is smaller than the current container size, the content is reduced to its first n elements, removing those beyond (and destroying them).
  - If n is greater than the current container size, the content is expanded by inserting at the end as many elements as needed to reach a size of n. If n is also greater than current container capacity, an automatic reallocation of the allocated storage takes place.
- reserve(n), Requests that the vector capacity be at least enough to contain n elements. 
  - If n is greater than the current vector capacity, the function causes the container to reallocate its storage increasing its capacity to n (or greater).
  - If all other cases, the function call doses not cause a reallocation and the vector capacity is not affected.



**面试题0x：STL萃取技术知道吗？**

STL有两种萃取技术：
- iterator_traits。负责萃取迭代器的特性，以正确完成算法。
  - iterator_category。
  - value_type。
  - difference_type。
  - pointer。
  - reference。
- type_traits。负责萃取类型的特性，以提高执行效率。
  - has trivial default ctor?
  - has trivial copy ctor?
  - has trivial assignment operator?
  - has trivial dtor?
  - is pod type?






**面试题0x：C++11有那些新特性？**

C++11常用的新特性有：

- nullptr替代NULL。
- 引入auto和decltype关键字。
- range-for循环。
- lambda表达式（匿名函数）。
- 新的STL容器。
- 智能指针。
- 移动语义和完美转发。


**面试题0x：c++惯用法有哪些？**

c++惯用法主要有以下几种：
- 初始化列表
- 枚举类替换命令空间
- RAII
- Copy And Swap
- Pimpl





#### 实操题

C/C++存在许多最佳实践，在实操中我们应该使用这些最佳实践，避免掉坑。



**面试题0x：实现单例模式**

懒汉式

懒汉式即单例实例在第一次使用时才进行实例化，即"lazy"。
```c++
class Singleton {
public:
    // 关键点1:必须为static函数，因为此时还没有实例，并且用户也无法生成实例。
    static Singleton* getInstance()
    {
        if (instance == NULL)
            instance = new Singleton();
        return instance;
    
    }

private:
    // 关键点2:禁用任何可能产生实例的方法。
    Singleton();
    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);
    ~Singleton();

private:
    // 关键点3:懒汉式使用指针。
    static Singleton* instance;
};

Singleton* Singleton::instance = NULL;


```

饿汉式

饿汉式即程序运行时立即实例化，即"hungry"。
```c++
class Singleton {
public:
    static Singleton& getInstance()
    {
        return instance;
    }

private:


private:
    static Singleton instance;
    


};

```



参考链接：

1. [C++11中局部变量初始化的线程安全性](https://blog.csdn.net/imred/article/details/89069750)



**面试题0x：限制类对象只能在堆上或只能在栈上**





**面试题0x：手写strcpy、memcpy、strcat、strcmp**

```c
/*
** 功能：将参数src字符串复制到参数dest所指的地址，包括结束符号。
** 返回值：返回参数dest所指的地址。
** 注意：只能用于拷贝字符串。
*/
char* strcpy(char* dest, const char* src)
{
    char* ret = dest;
    while (*dest++ = *src++)
        ;
    *dest = '\0';
    return ret;
}



/*
** 功能：从参数src所指的空间逐字节复制num bytes到参数dest所指的地址。
** 返回值：返回参数dest所指的地址。
** 注意事项：
**   1.为了避免溢出，dest和src所指的内存空间的大小至少应该等于num bytes。
**   2.dest和src所指的内存空间不应该有重叠，否则将会出错。 
**   3.由于是逐字节拷贝，因此memcpy函数不关心dest和src的类型，它只是把字节拷贝过去。
*/
void* memcpy(void* dest, const void* src, size_t num)
{
    char* tmp = (char*)dest;
    const char* s = src;

    while (num--) 
        *tmp++ = *s++;
    
    return dest;
}


/*
**
**
*/
void memmove(void* dest, const void* src, size_t num)
{



}

```




---

### 计算机基础



#### 数据结构与算法



#### 操作系统



**面试题0x：进程和线程的区别？进程和线程共享那些资源？**



**面试题0x：堆与栈的区别**

堆与栈主要在以下方面有所区别：
- 管理方式不同
- 生长方式不同
- 碎片问题不同
- 


**面试题0x：Linux虚拟地址空间实现？**



**面试题0x：如何解决多线程访问共享资源？你知道哪些方法？无锁编程知道吗？**

使用锁、条件变量、信号量。

并发编程的三大核心问题：
- 原子性，
- 可见性，
- 顺序性，


> 通常情况下，我们有一个对共享变量必须使用原子操作的规则：
>
> 任何时刻，只要存在两个或多个线程并发地对同一个共享变量进行操作，并且这些操作中的其中一个是执行了写操作，那么所有的线程都必须使用原子操作。
>
> 什么样的内存操作是原子的呢？通常情况下，如果一个内存操作使用了多条CPU指令，那么这个内存操作是非原子的。那么只使用一条CPU指令的内存操作是不是就一定是原子的呢？答案是不一定，某些仅仅使用一条CPU的内存操作，在绝大多数CPU架构上是原子，但是，在个别CPU架构上是非原子的。如果，我们想写出可移植的代码，就不能做出使用一条CPU指令的内存操作一定是原子的假设。


**面试题0x：如何实现一个锁？**


