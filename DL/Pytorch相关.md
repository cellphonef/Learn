# Pytorch

The Pytorch library, besides offering the computational functions as Numpy does, also offer a set of modules that enable developers to quickly design, train, and test deep learning models.

创建和训练神经网络包括以下基本步骤：
1. 构建神经网络结构。
2. 使用输入数据在神经网络中进行前向传播。
3. 计算损失loss。
4. 反向传播，计算每个权重参数的梯度。
5. 使用学习率更新权重参数。

> :warning:计算梯度和更新参数通常分两个步骤完成。 

## torch.nn

> step 1 
> 
> -> 定义神经网络结构和前向传播。

When building a neural network architecture, the fundamental aspects that the network is build on are:
- number of layers.
- number of neurons in each layer.
- which are those are learnable.
- ...


### 神经网络基类——nn.Module

Q：神经网络结构应该是怎么样的？

A：`nn.Module`给出了答案。

在`nn.Module`里面定义或声明了一个神经网络结构该有的所有属性和方法，这些属性和方法用于完成以下工作：
1. 构造一个神经网络模型。
2. 前向传播。
3. 反向传播（???）。
4. 获取整个神经网络模型或各层的信息（如结构信息，参数信息）。
5. 保存和恢复模型。

#### construct model

`nn.Module`类通过维护8个字典（orderedDict）来完成上述操作：
- `_parameters`:网络结构的权重参数，类型为tensor。
- `_buffers`：通过register_buffer API填充值，通常用来将一些需要持久化的状态（但又不是网络的参数）放到_buffer里。 
- `_backward_hooks`
- `_forward_hooks`
- `_forward_pre_hooks`
- `_state_dict_hooks`
- `_load_state_dict_pre_hooks`
- `modules`：起到很重要的桥梁作用，在获取一个net的所有parameters的时候，是通过递归遍历该net的所有_modules来实现的。

这些字典都在`nn.Module`初始化时（通过调用`__init__()`）创建。

> :warning:当你自定义你的Net时，应该确保父类的构造函数首先被调用，这样才能确保上述OrderedDict被创建出来。


#### forward

`nn.Module`的`forward`函数只提供了声明而没有实现，需要在子类实现，显然每个网路结构都是不一样的，因此`forward`函数应该在子类中实现，否则报错。



函数`require_grad_`和`zero_grad`

网络的前向需要通过诸如`Net(input)`这样的形式来调用（即调用网络的`__call__`），而非`Net.forward(input)`，是因为前者实现了额外的功能：
1. 先执行完所有的`_forward_pre_hooks`里的hook
2. 再执行Net的`forward`函数
3. 再执行所有的`_forward_hooks`中的hook
4. 再执行完所有的`_backward_hooks`中的hook






#### model information

对于函数`parameters`，我们可以使用`for param in parameters()`来遍历网络模型中的参数，因为该函数返回的是一个迭代器`iterator`。我们在使用优化算法的时候就是将`model.parameters()`传递给优化器`Optimizer`。与之类似的还有函数`buffers`、函数`children`和函数`modules`。


#### backward train

函数`train`和`eval`的作用是将module及其submodule分别设置为training mode和evaluation mode。


#### model save & load

如果我们要保存一个训练好的pytorch模型的话，会使用下面的API:

```python
cn = CivilNet()
# ...
torch.save(cn.state_dict(), "your_model_path.pth")
```

可见保存一个训练好的模型需要两步：
1. 网络通过`state_dict()`的调用得到网络参数一个字典。
2. 然后通过`pickle`模块序列化成文件。

如果我们要加载一个保存的模型，则会使用如下API：

```python
cn = CivilNet()

state_dict = torch.load("your_model_path.pth")
cn.load_state_dict(state_dict)
```

加载一个保存的模型，过程则与保存模型相反：
1. 首先通过`pickle`模块反序列化成网络参数字典
2. 然后网络通过`load_state_dict()`加载参数。






**神经网络各种层——以nn.Linear为例**

神经网络的各种层，如全连接层或卷积层都继承于`nn.module`。

每个层都定义了如下函数：
- `__init__`：用于初始化该层的参数（使用`reset_parameter`），以及其他各种属性。
- `forward`：用于该层的前向传播（通常为间接调用）。

对于包含内在参数的函数，都会定义如下函数：
- `reset_parameter`：用于初始化参数，通常使用Xavier。




## torch.utils

> step 2 
> 
> -> 定义数据加载器

当我们定义好我们的神经网络结构后，我们就可以定义数据加载器用于模型的前向传播。

所谓数据加载器，其实就是一个不断从数据集中读取数据的生成器类。



### torch.utils.data

Under the utils.data module, torch provides its own dataset and *DatasetLoader* classes, which extremely handy due to their abstract and flexble implementations.

为了加载我们自己的数据，我们可以通过继承`torch.utils.data`中的`Dataset`类，并修改其中方法来实现：
- `__init__`函数做一些初始化工作，通常保存文件的路径。
- `__getitem__`函数，应该返回指定索引的数据集中的数据和标签。
- `__len__`函数，应该返回数据集的大小。


```python
# 样例
class MyDataset(data.Dataset):
    def __init__(self, txt, transform=None, traget_transform=None, loader=default_loader):
        fh = open(txt, 'r')
        for line in fh:
            line = line.strip(('\n')
            words = line.split()
            imgs.append(words[0], int(words[1]))
        
        self.imgs = imgs
        self.transform = transform
        self.traget_transform = traget_transform
        self.loader = loader
        

    def __getitem(self, index):
        fn, label = self.imgs[index]

        img = self.loader(fn)
        if self.transform is not None:
            img = self.transform(img)
        return img, label

    def __len__(self):
        return len(self.imgs)
```

光有Dataset还不够，因为Dataset类仅仅只是读入数据集数据并且对读入的数据进行了索引。在实际加载数据中我们的数据量往往都很大，对此我们还需要以下几个功能：
- 能够以batch_size的大小读入数据。
- 能够对数据进行随机读取（即shuffle=True）。
- 可以并行加载数据（num_worker = n）

这就是DataLoader的功能了，我们在实现好我们的Dataset后，就可以使用`torch.util.data`中的`DataLoader`来实现这些功能了。




## torch.optim

> step 3 
> 
> -> 定义优化器用来更新梯度

当我们计算出梯度后，我们应该利用优化器来更新梯度。

The *optim* module includes all the tools and functionalities related to running various types of optimization schedules which training a deep learning model.

优化器的作用就是根据学习率和求得的梯度来更新梯度。



## train & test

> step 4 
> 
> -> 定义训练方法和测试方法

```python
# model: 待训练的模型
# device: 使用的设备
# train_dataloader: 训练集加载器
# optim: 优化器
# epoch: 轮次
def train(model, device, train_dataloader, optim, epoch)
    model.train()  
    optim.zero_grad()
    pred_prob = model()
    loss = F.nll_loss(pred_prob, y)
    loss.backward()
    optim.step()  # 更新梯度
    for i in range(epoch):

```



```python
def test(model, device, test_dataloader)

```








## Tensor module

Tensors are conceptually similar to Numpy arrays. A tensor is an n-dimensional array on which we can operate mathematical functions, accelerate computations via GPUs, and tensors can also be used to keep track of a computational graph and gradients, which prove vital for deep learning. To run a tensor on a GPU, all we need is to cast the tensor into a certain data type.

Pytorch中的计算依赖于Tensor。一个Tensor中记录了很多属性其中包括：
- data：存储的数据。
- requires_grad：是否需要求导，默认为False。只要有输入Tensor的requires_grad为True，则其输出Tensor也需要求导。
- grad：该Tensor的梯度。
- grad_fn：用于指示梯度函数的类型。
- is_leaf：用来指示该Tensor是否为叶子节点。




