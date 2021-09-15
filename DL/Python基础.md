

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



# 高级特性

> 为了写出更pythonic的代码

## 切片

切片，即从整体中取部分。例如从`list`或`tuple`取出部分元素。

## 迭代


## 列表生成式

写列表生成式时，把要生成的元素放在前面，后面跟for循环，可以使用多重循环或者加上if判断。

## 生成器




## 迭代器



# 函数式编程

## 匿名函数

匿名函数又称lambda函数。

## 装饰器

装饰器即不改变原函数代码及调用方式的基础上为原函数添加新的功能，即装饰器对于原函数是完全透明的。



# 面向对象编程



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

