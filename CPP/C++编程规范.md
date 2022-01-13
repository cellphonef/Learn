# C++编程规范

## 类的设计与继承

###  Be clear what kind of class you're writing

**摘要**

了解自己：有很多种不同的类，弄清楚要编写的是哪一种。

**讨论**

不同种类的类适用于不同的用途，因此遵循着不同的规则。

*值类*

值类（如`std::vector`）模仿的是内置类型。

一个值类应该：
- 有一个公用的析构函数，带有值语义的复制构造函数和赋值运算符。
- 用作具体类，不做基类，因此没有虚函数（包括虚析构函数）。
- 总是在栈中实例化，或者作为另一个类直接包含的成员实例化（有待考究）。

*基类*

基类是类层次结构的构成要素。

一个基类应该：
- 有一个公用的且虚拟的（即外界可以通过基类指针调用析构函数），或者保护的而且非虚拟的析构函数，和一个非公用的复制构造函数和赋值操作符。
- 通过虚函数建立接口。
- 总是动态地在堆中实例化为具体的派生类对象，并通过一个（智能）指针来使用（工厂函数）。


### Declare destructors virtual in polymorphic base classes.

**摘要**

对于用于多态用途的基类，即其他类会从该类进行公用继承。




### Prevent exceptions from leaving destructors.

**摘要**

析构函数吐出异常十分危险，总会带来"过早结束程序"或"发生不明确行为"的风险。

### Never call virtual functions during construction and destruction.

**摘要**

你不该在你的构造函数和析构函数期间调用虚函数，因为这样的调用并不会带来你预想的结果（暗含：可以调用但结果不理想）。

**讨论**

### Handle assignment to self in operator=.

**摘要**





## 名字空间与模块

### 59. Don't write namespace `using`s in a header file or before an `#include`

**摘要**

名字空间`using`的使用原则应该是使我们更方便，但它们的引入不应该干扰别人。



**讨论**

名字空间`using`，将会在该语句的所在作用域引入名字（只要是同一名字就会被引入）。


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





Name lookup

Name lookup is the procedure by which a name, when encountered in a program, is associated with the declaration that introduced it.

For function names, name lookup can associate multiple declarations with the same name, and may obtain additional declarations from argument-dependent lookup (ADL). Template argument deduction may also apply, and the set of declarations is passed to overload resolution, which selects the declaration that will be used. Member access rules, if applicable, are considered only after name lookup and overload resolution.

For all other names (variables, namespaces, classes, etc), name lookup must produce a single declaration in order for the program to compile.

名字查找就是查找与该名字相关的声明来构造一个候选集合的过程：
- 对于函数名，其候选集合可能包含多个声明（函数重载）。
- 对于其他名字（变量名，名字空间，类等）候选集合只有一个声明，否则将无法编译。

名字查找包含两种类型：
- unqualified name lookup.
- qualified name lookup.

> 模版中还有两种类型的名字：1）dependent name 2）non-dependent name




ADL only works with unqualified names.


Because of argument-dependent lookup, non-member functions and non-member operators defined in the same namespace as a class are considered part of the public interface of that class (if they are found through ADL).




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







## Naming

- File Names: all use `my_useful_class.cc`
- Type Names: all use `CamelCase`
  - Class/Struct name
  - Type alias
  - Enums
  - Type template parameter
- Variable Names
  - Local Variable & Struct Data Members: all use `lower_case`
  - Class Data Members: all use `lower_case_`
- Constant Names: all use `kCamelCase8_0_0`
- Function Names
  - Normal function: all use `CamelCase`
  - Member function: all use ""
- Namespace Names: 
- Enumerator Names: all use `kCamelCase8_0_0`
- Macro Names: all use `UPPER_CASE`
- Exceptions to Naming Rules: If you are naming something that is analogous to an existing C or C++ entity then you can follow the existing naming convention scheme.


## Comment

- Comment style

use either the `//` or `/* */` syntax, as long as you are consistent.



## Formating

General Rules
- fit in one line
- break into two line:
  - subsequent line aligned with the first 
- break into multiline
  - four space indent.

- Line Length

Each line of text in your code should be at most 80 characters long.

- Function Declarations and Definitions

```cpp
ReturnType ClassName::FunctionName(Type par_name1, Type par_name2) {
  DoSomething();
  // ...
}

ReturnType ClassName::ReallyLongFunctionName(Type par_name1,
                                             Type par_name2) {
  DoSomething();
  // ...                                             
}

ReturnType ClassName::ReallyReallyReallyLongFunctionName(
    Type par_name1,
    Type par_name2,
    Type par_name3) {
  DoSomething();
  // ...

}

```




- Conditionals (i.e, `if` statement)

```cpp
// Normal situation

// IF
if (condition) {            // Note that brace position       
  DoOneThing();
  DoAnotherThing();
}

// IF-ELSE
if (condition) {
  DoOneThing();
  DoTwoThing();
} else {                    // Note that else and brace position.
  DoThreeThing();
}


// IF-ELSEIF-ELSE
if (condition1) {
  DoOneThing();
  DoAnotherThing();         // Note that else if and brace
} else if (condition2) {   
  DoAThirdThing();
} else {
  DoNothing();
}

// Special situation

if (x == kFoo) return new Foo();

if (x == kBar)
  return new Bar(arg1, arg2, arg3);

if (x == kQuz) { return new Quz(1, 2, 3); }

```




- Loops and Switch statement



- Boolean Experssion

```cpp
if (this_one_thing > this_other_thing &&
    a_third_thing == a_fourth_thing &&
    yet_another && lastone) {

}

```


- Class Formatting

```cpp
class MyClass : public OtherClass {
 public:                                              // Note that one space indent
  MyClass();                                          // Regular two space indent
  explicit MyClass(int var);
  ~MyClass();

  void SomeFunction();

  void set_some_val(int val) {some_val_ = var; }
  void some_val() const { return some_val_; }

 private:
  bool SomeInternalFunction();

  int some_val_;
  int some_other_val_
};
```

```cpp
// When everything fits on one line:
MyClass::MyClass(int val) : some_var_(var) {
  DoSomething();
}

// 
MyClass::MyClass(int val)
    : some_val_(val), some_other_var_(var + 1) {
  DoSomething();
}


//
MyClass::MyClass(int val)
    : some_val_(val),
      some_other_val_(val + 1) {
  DoSomething();
}



```





- Namespace Formatting

```cpp
namespace ns {

void foo() {        // Note that no space here!

}

}  // ns

```





