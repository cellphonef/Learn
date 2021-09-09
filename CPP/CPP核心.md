# CPP

最初，C++只是C语言加上一些面向对象的特性，所以C++的原名是"C with Classes"。

现在的C++已经逐渐成熟，成为一门**多范式的程序设计语言（multiparadigm programming language）**。同时支持：
- 过程形式（procedural）
- 面向对象形式（object-oriented）
- 函数形式（functional）
- 泛型形式（generic）
- 元编程形式（metaprogramming）

这些能力和弹性使得C++成为一个无可匹敌的语言，但是各个范式之间并没有紧密的关联性。

最好将C++看成一个由相关语言组成的联邦而非单一的语言。在其某个次语言（sublanguage）中，各种守则与通例都倾向简单、直观易懂、并且容易记住。然而当你从一个次语言移往另一个次语言，守则可能改变。

C++主要得次语言总共四个：
- C。
- Object-Oriented C++。
- Template C++。
- STL。


## C 核心

C核心只有很少的东西：
- 基本数据类型与变量。
- 指针与数组。
- 函数。
- 结构体、联合体与枚举。



## Object-Oriented C++ 核心

Object-Oriented C++即面向对象编程，其关注点在于如何将数据和操作数据的方法组装在一起。

而将数据和操作数据的方法组装在一起的实现手段即类，因此Object-Oriented C++的核心是**类的设计**。

而类的设计主要分为三个部分：
- 封装。
- 继承。
- 多态。


## Template C++ 核心

Template C++即泛型编程，其关注点是如何让同一套代码适用于不同的类型。

Template C++的核心即为template，主要有两种：
- function template
- class template

function template又分为
- non-member function（即normal function），对应normal function tempalte。
- member function，对应member function template。


### 模版实参推导法则

对于函数模版，编译器利用函数实参来确定其模版参数。从函数实参来确定模版实参的过程被称为模版实参推导。

**函数模版中依赖于模版参数的函数参数采用值传递**

形如下列函数签名：

```c++
template <typename T>
void fun(T arg); /* arg依赖于模版参数并且采用值传递 */
```

由于采用值传递，传递后实参和形参就相互独立了，因此会忽略掉实参的顶层const（更高的灵活性，不应该让实参限制了形参，因为他们是独立的）。

e.g. 

```C++
int i = 10;
const int ci = 20;
fun(i);   // T is int
fun(ci);  // T is int, arg has type int
```

但是如果函数模版设计者想要维持顶层const，则可以显式的加上，如下所示：
```c++
template <typename T>
void fun(const T arg);
```

e.g.

```C++
fun(i);   // T is int
fun(ci);  // T is int, arg has type const int 
```


将实参传递给带模版类型的函数形参时，能够自动应用的类型转换只有const转换以及数组或函数到指针的转换。








**函数模版中依赖于模版参数的函数参数采用引用传递**

引用传递有两种：
- 左值引用
- 右值引用








完美转发

某些函数需要将其一个或多个实参连同类型不变地转发给其他函数。在此情况下，我们需要保持被转发实参的所有性质，包括实参类型是否为const以及实参是左值还是右值。









## STL 核心

STL是一个template程序库，它是一套完整的程序库。它包含六个组件：
- 容器（container）
- 迭代器（iterator）
- 算法（ algorithm）
- 适配器（adpator）
- 函数对象（function objects）








