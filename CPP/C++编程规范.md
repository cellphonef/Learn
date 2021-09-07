# C++编程规范

## 类的设计与继承

### 32. Be clear what kind of class you're writing

**摘要**

了解自己：有很多种不同的类，弄清楚要编写的是哪一种。

**讨论**

不同种类的类适用于不同的用途，因此遵循着不同的规则。

*值类*

值类（如`std::vector`）模仿的是内置类型。

一个值类应该：
- 有一个公用的析构函数，带有值语义的复制构造函数和赋值。
- 用作具体类，不做基类，因此没有虚函数（包括析构函数）。
- 总是在栈中实例化，或者作为另一个类直接包含的成员实例化。

*基类*

基类是类层次结构的构成要素。

一个基类应该：
- 有一个公用的且虚拟的，或者保护的而且非虚拟的析构函数，和一个非公用的复制构造函数和赋值操作符。
- 通过虚函数建立接口。
- 总是动态地在堆中实例化为具体的派生类对象，并通过一个（智能）指针来使用。

## 名字空间与模块

### 59. Don't write namespace `using`s in a header file or before an `#include`

**摘要**

名字空间`using`的使用原则应该是使我们更方便，但它们的引入不应该干扰别人。



**讨论**

名字空间`using`，将会在该语句的所在作用域引入名字。


**请记住**

1. 在所有头文件中，总是明确地使用名字空间限定所有名字。
2. 在所有实现文件中的所有`#include`之前，总是明确地使用名字空间限定所有名字。
3. 在所有实现文件中的所有`#include`之后，可以而且应该不受限制地编写名字空间级别的using声明和指令。


### 61. Don't define entities with linkage in a header file

**摘要**

重复会导致膨胀：具有链接属性的实体，包括名字空间级的变量或函数，都需要分配内存。在头文件中定义这样的实体讲导致链接时错误或者内存的浪费。因此，请将所有具有链接属性的实体放入实现文件。

**讨论**

链接具有三种情况：
- 外部链接。
- 内部链接。
- 无链接。

名字空间级的实体肯定具有内部或外部链接，而局部变量（非`static`）肯定无链接。


情形一：避免在头文件中定义具有外部链接的实体

```c++
int fudgeFactor;
string hello("Hello, world!");
void foo() { /* */ }
```
只要被一个以上的源文件所包含，就很容易的导致链接时错误，编译器会报告存在重复符号错误。原因很简单：在每个源文件中，都会定义`fudgeFactor`、`hello` 、`foo`，并分配空间。当要将它们都链接起来的时候，链接器将面对具有多个相同名字而且互相在竞争的可见性的符号。一句话就是违反了C++的`ODR`原则。

解决之道非常简单——只在头文件中放置声明而不是定义。

```c++
extern int fudgeFactor;
extern string hello;
void foo();
```

情形二：避免在头文件中定义名字空间级别的static实体。









## 模版与范型

### 64. Blend static and dynamic polymorphism judiciously

**摘要**

1 + 1 > 2：静态多态性和动态多态性是相辅相成的。理解他们的优缺点，善用他们的长处，结合两者以获得两方面的优势。

**讨论**

多态包括两种：
- 静态多态（编译阶段完成）
  - 函数重载
  - 模版
- 动态多态（运行阶段完成）
  - 虚函数







ADL only works with unqualified names.

Because of argument-dependent lookup, non-member functions and non-member operators defined in the same namespace as a class are considered part of the public interface of that class (if they are found through ADL).