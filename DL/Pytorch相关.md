# Pytorch

The Pytorch library, besides offering the computational functions as Numpy does, also offer a set of modules that enable developers to quickly design, train, and test deep learning models.


## torch.nn

> step 1 : 定义网络结构和训练测试方法（包括优化器）

When building a neural network architecture, the fundamental aspects that the network is build on are:
- number of layers.
- number of neurons in each layer.
- which are those are learnable.
- ...


**神经网络基类——nn.module**

所有的neural network module都应该继承`nn.module`，自己创建的网络模型都应该是`nn.module`的子类。

首先是`__init__`和`forward`函数。前者主要用于初始化一些内部需要使用的state。而后者没有实现，只提供声明，需要在子类实现，显然每个网路结构都是不一样的，因此`forward`函数应该在子类中实现，否则报错。

函数`train`和`eval`的作用是将module及其submodule分别设置为training mode和evaluation mode。

函数`require_grad_`和`zero_grad`。

函数`__call__`

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

## torch.save

> step 3 : 保存模型





## 

> 迁移学习