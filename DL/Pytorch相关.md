# Pytorch

The Pytorch library, besides offering the computational functions as Numpy does, also offer a set of modules that enable developers to quickly design, train, and test deep learning models.


## torch.nn

> step 1 : 定义网络结构和训练测试方法（包括优化器）

When building a neural network architecture, the fundamental aspects that the network is build on are:
- number of layers.
- number of neurons in each layer.
- which are those are learnable.
- ...


**神经网络基类——nn.Module**

所有的neural network module都应该继承`nn.Module`，自己创建的网络模型都应该是`nn.Module`的子类。

通常来说，我们继承某个类，是希望复用这个类的属性和方法，因此在`nn.Module`里面定义或声明了一个神经网络结构该有的所有属性和方法。

`nn.Module`相当于是一个神经网络的模板，它的定义中应该包含以下几部分：
1. 构造一个神经网络模型。
2. 前向传播。
3. 反向传播（???）。
4. 获取整个神经网络模型或各层的信息（如结构信息，参数信息）。
5. 保存和恢复模型（即序列化和反序列化）。



首先是`__init__`和`forward`函数。前者主要用于初始化一些内部需要使用的state。而后者没有实现，只提供声明，需要在子类实现，显然每个网路结构都是不一样的，因此`forward`函数应该在子类中实现，否则报错。

函数`train`和`eval`的作用是将module及其submodule分别设置为training mode和evaluation mode。

函数`require_grad_`和`zero_grad`

函数`__call__`会调用`forward`函数。

对于函数`parameters`，我们可以使用`for param in parameters()`来遍历网络模型中的参数，因为该函数返回的是一个迭代器`iterator`。我们在使用优化算法的时候就是将`model.parameters()`传递给优化器`Optimizer`。与之类似的还有函数`buffers`、函数`children`和函数`modules`。

**神经网络各种层——以nn.Linear为例**

神经网络的各种层，如全连接层或卷积层都继承于`nn.module`。

每个层都定义了如下函数：
- `__init__`：用于初始化该层的参数（使用`reset_parameter`），以及其他各种属性。
- `forward`：用于该层的前向传播（通常为间接调用）。

对于包含内在参数的函数，都会定义如下函数：
- `reset_parameter`：用于初始化参数，通常使用Xavier。







## torch.optim

The *optim* module includes all the tools and functionalities related to running various types of optimization schedules which training a deep learning model.




## torch.utils

> step 2 : 加载数据

### torch.utils.data

Under the utils.data module, torch provides its own dataset and *DatasetLoader* classes, which extremely handy due to their abstract and flexble implementations.





## Tensor module

Tensors are conceptually similar to Numpy arrays. A tensor is an n-dimensional array on which we can operate mathematical functions, accelerate computations via GPUs, and tensors can also be used to keep track of a computational graph and gradients, which prove vital for deep learning. To run a tensor on a GPU, all we need is to cast the tensor into a certain data type.

## torch.save

> step 3 : 保存模型





## 

> 迁移学习