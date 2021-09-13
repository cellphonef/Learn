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

与非模版函数一样，我们在一次调用中传递给函数模版的实参被用来初始化函数的形参。如果一个函数形参的类型使用了模版类型参数，那么它将采用特殊的初始化规则。只有很有限的几种类型转换会自动地应用于这些实际参数。因为编译器通常不是对实参进行类型转换，而是生成一个新的模版实例。

与往常一样，顶层const无论是在形参还是实参中，都会被忽略（更高的灵活性）。在其他类型转换中，能在调用中应用于函数模版的包括如下两项：
- const转换：可以将一个非const对象的引用（或指针）传递给一个const的引用（或指针）形参。
- 数组或函数指针转换：如果函数形参不是引用类型（引用是别名，类型必须和实参一致），则可以对数组或函数类型的实参应用正常的指针转换。一个数组实参可以转换为一个指向其首元素的指针。类似的一个函数实参可以转换为一个该函数类型的指针（其他转换都不能应用于函数模板，相反编译器生成新的模板实例）。

**函数模版中依赖于模版参数的函数参数采用值传递**

值传递只有两种：
- 普通值传递
- 指针传递

形如下列函数签名：

```c++
template <typename T>
void fun(T arg); /* arg依赖于模版参数并且采用值传递 */
```

由于采用值传递，传递后实参和形参就相互独立了，因此会忽略掉实参的顶层const（更高的灵活性，不应该让实参限制了形参，因为他们是独立的）。但是底层const需要保留（为了安全性）。

e.g. 

```C++
int i = 10;
const int ci = 20;
int* pi = &i;
const int* pci = &ci;
fun(i);    // T is int
fun(ci);   // T is int, arg has type int
fun(pi);   // T is int*
fun(pci);  // T is const int*
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

总结：
1. 忽略顶层const，即普通值传递或指针传递的顶层const会忽略。
2. 保留底层const，即指针传递中的底层const会保留。


**函数模版中依赖于模版参数的函数参数采用引用传递**

引用传递有两种：
- 左值引用
- 右值引用

形如下列函数签名：

```C++
template <typename T>
void fun(T& arg);


template <typename T>
void fun(T&& arg);

```

当一个函数参数是模板类型参数的左值引用（即`T&`）时，只能传递一个左值，否则将会将一个左值引用绑定到右值上，这是不允许的。并且会保留实参的所有const属（包括底层const和顶层const），原因很简单引用是别名，它应该和实参保持一致。

e.g.

```c++
fun(i);     // T is int
fun(ci);    // T is const int
fun(42);    // error: T deduced to int 
            // but int& can not bind to rvalue

fun(pi);    // T is int*
fun(pci);   // T is const int*

const int* const cpci = &ci;
fun(cpci);  // T is const int* const 
```

当一个左值引用含有const时（即`const T&`），我们可以传递给它左值和右值（因此可以接受任何类型的值）。当函数参数本身是const时，T的类型推导将不会再含有const（参数已经包含了没必要再包含了）。

```C++
template <typename T>
void fun(const T& arg);

fun(i);    // T is int
fun(ci);   // T is int
fun(5);    // T is int
```


当一个函数参数是模板类型参数的右值引用时，正常的绑定规则告诉我们可以传递右值。当我们这样做时，类型推导过程类似普通左值引用函数参数的推导过程，即推导出的类型为该右值实参的类型。

```C++
template <typename T>
void fun(T&& arg);

fun(5);    // T is int
fun(6.0);  // T is double
 ```

 从正常绑定规则来讲，不可以传递左值，但实际上C++在正常绑定规则之外定义了两个例外规则：
 1. 当我们将一个左值传递给函数的右值引用参数，且此右值引用参数指向模板类型参数时，编译器推导模板类型参数为实参的左值引用类型。
 2. 如果我们间接创建一个引用的引用，则这些引用形成了"折叠"，编译器会进行引用折叠处理。



在实际中，函数模板的依赖于模板类型参数的右值引用参数通常用于两种情况：
- 完美转发。
- 模板重载。

首先对于完美转发，我们要的是将实参的类型完完整整的传递给其他函数，因此：
- 对于传递进来的左值，我们应该保持它左值的性质以及它的const属性（因此需要传引用）。
- 对于传递进来的右值，保持它右值的性质以及const属性。


而对于模板重载，我们知道实际上左值和右值是有区别的，我们要利用他们的区别来提高程序的效率。因此，我们在模板重载时会区分开左值和右值。




> 当有多个重载模板对一个调用提供同样好的匹配时，应选择最特例化的版本。












完美转发

某些函数需要将其一个或多个实参连同类型不变地转发给其他函数。在此情况下，我们需要保持被转发实参的所有性质，包括实参类型是否为const以及实参是左值还是右值。









## STL 核心

STL是一个template程序库，它是一套完整的程序库。它包含六个组件：
- 容器（container）
- 迭代器（iterator）
- 算法（ algorithm）
- 适配器（adpator）
- 函数对象（function objects）








