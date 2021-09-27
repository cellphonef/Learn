

# 数据类型



## 字符串

字符串是不可变对象。

## list vs tuple

python内置的一种数据类型是列表：`list`。

`list`是一种有序的集合，可以随时添加和删除其中的元素，其中的元素可以是不同的数据类型。

`list`的使用方式：
- `len(mylist)`，获取list长度
- `mylist[index]`，索引list中index位置的元素，索引从0开始。
- `mylist.append(elem)`，往list尾部添加元素。
- `mylist.pop()`，删除list尾部元素。
- `mylist.insert(index, elem)`，把元素插入到list的index位置。
- `mylist.pop(index)`，删除list中index位置的元素。


另一种有序列表叫元组：`tuple`。`tuple`与`list`非常类似，但是`tuple`一旦初始化后就不能修改。



## dict vs set

python内置了两种无序容器：
- dict
- set


```python
>>> d = {'a' : 1, 'b' : 2, 'c' : 3}
>>> d['a']
1
```



# 高级特性

> 为了写出更pythonic的代码

## 切片

切片，即从整体中取部分。例如从`list`或`tuple`取出部分元素。


参考文献：[切片完全指南](https://zhuanlan.zhihu.com/p/79541418)


对于多维数组，每个维度又可以看成是一维的切片。





## 列表生成式

写列表生成式时，把要生成的元素放在前面，后面跟for循环，可以使用多重循环或者加上if判断。

## 生成器

生成器是根据算法推演出元素的可迭代对象，其目的是为了节省内存，同时可以用来存放无穷序列。因此生成器是一种特殊的`iterator`，它的元素是惰性计算的，只有使用时才计算。

生成器有两种方式实现：
- 第一种是使用类似于列表生成器的方式。
- 第二种是使用yield。

第一种用于简单的元素推演算法，第二种用于复杂的元素推演算法。

例如：

```python
# 第一种
g = (x * x for x in range(10))  # 将列表生成器的[]替换成()

# 使用
next(g)
# ...不断next(g)推导出下一个元素

# 为了方便通常使用for，因为for会自动调用next以及处理异常
for x in g:
    print(x)


# 第二种，显然难以使用列表生成器的形式推导
def fib(int x):
    n, a, b = 0, 0, 1
    while n < max:
        yield b  # 运行到yield会停下直到下次next()调用
        a, b = b, a + b
        n = n + 1

# 使用
f = fib(6)
next(f)
# ... 不断next(f)推导出下一个元素

# 为了方便通常使用for，因为for会自动调用next以及处理异常
for x in f:
    print(x)

```



## 迭代器

**可迭代对象和迭代器**

- 凡是可用于for循环的对象都是可迭代对象，即是`Iterable`类型。
- 凡是可作用于`next()`函数的对象都是Iterator类型，它们表示一个惰性计算的序列。
- 集合数据类型如`list`、`dict`、`str`等是`Iterable`但不是`Iterator`，不过可以通过`iter()`函数获得一个`Iterator`对象。
- `Iterator`对象一定`Iterable`。

Python中的for循环本质上就是通过不断调用`next()`函数实现的，例如：

```python
for x in [1, 2, 3, 4, 5]:
    print(x)
```

实际上完全等价为：

```python
it = iter([1, 2, 3, 4, 5])

while True:
    try:
        x = next(it)
        print(x)
    except StopIteration:
        break
```



# 函数式编程

## 匿名函数

匿名函数又称lambda函数。

## 装饰器

装饰器即不改变原函数代码及调用方式的基础上为原函数添加新的功能，即装饰器对于原函数是完全透明的。



# 面向对象编程


## magic method



如果调用magic method

许多magic method直接对应到内置函数，此时我们的如果调用magic method就一目了然了，但是某些magic method的调用方式不是那么显然的，这时我们就需要知道magic method与其特殊的调用方式了。


|Magic Method| 何时调用（例子）|解释|
|------------|--------------|----|
|`__new__`   |instance = MyClass(arg1, arg2)| 创建实例对象时调用|
|`__init__`|||
|`__index__`|`x[self]`||
|`__getattr__(self, name)`|`self.name #name不存在`|访问不存在属性|
|`__setattr__(self, name, val)`|`self.name = val`|给属性赋值|
|`delattr__(self, name)`|`del self.name`|删除一个属性|
|`__getattribute__(self, name)`|||
|`__getitem__(self, key)`|||
|`__setitem__(self, key, val)`|||
|`__delitem(self, key)`|||
|`__iter(self)__`|`for x in self`||
|`__contain__(self, value)`|`value in self, value not in self`||
|`__call__(self [, ...])`|`self(args)`||
|`__enter__(self)`|||
|`__exit(self, exc, val, trace)`|||
|`__getstate__(self)`|`pickle,dump(pkl_file, self)`||
|`__setstate__(self)`|`data = pickle.load(pkl_file)`||

# 模块

## sys

sys模块中最重要的就是
- sys.path
- sys.argv
- 

## os

os模块中最重要的就是
- os.path

os.path主要用于获取文件的属性。



# 常用函数

- enumerate()，用于将一个可迭代对象组合为一个索引序列，同时包括数据下标和数据。
- format()，用于格式化输出。


# numpy

设axis=i，则numpy沿着第i个下标变化的方向进行操作。