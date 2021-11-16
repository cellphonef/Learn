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

`nn.Module`类通过维护8个有序字典（orderedDict）来完成上述操作：
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

函数`train`和`eval`的作用是将module及其submodule分别设置为training mode和evaluation mode。通常这两个模式会影响BN层和Dropout层的表现。


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






**全连接层——Linear**

神经网络的各种层，如全连接层或卷积层都继承于`nn.module`。

每个层都定义了如下函数：
- `__init__`：用于初始化该层的参数（使用`reset_parameter`），以及其他各种属性。
- `forward`：用于该层的前向传播（通常为间接调用）。

对于包含内在参数的函数，都会定义如下函数：
- `reset_parameter`：用于初始化参数，通常使用Xavier。

Linear，即线性层，也可以用作全连接层。

step1：构造一个全连接层

```python
# in_features: 输入样本尺寸，无默认值
# out_features: 输出样本尺寸，无默认值
# bias: 是否添加bias，默认为True
Linear(in_features, out_features, bias = True, device = None, dtype = None)
```

step2：输入输出
- 输入Input为：$(*, H_{in})$。 
- 输出Output为：$(*, H_{out})$。


step3：可学习参数
- 全连接层权重weight，shape为(out_features, in_features)。
- 全连接层偏置bias，shape为(out_features)。



**卷积层——Conv2D**

Conv2D，即2维卷积层。

step1：构造一个2维卷积层

```python
# in_channels(int): 输入图像的通道数，无默认值
# out_channels(int): 卷积后输出通道数（与kernel数量相同），无默认值
# kernel_size(int or tuple): 卷积核尺寸，无默认值
# stride(int or tuple): 步长，默认值为1
# padding(int, tuple or str): 填充值，默认值为0
# diliation: 
# groups: 
# bias: 是否添加bias，默认为True
# padding_mode: 
# device: 
# dtype: 
Conv2d(in_channels, out_channels, kernel_size, stride = 1, padding = 0,
       diliation = 1, groups = 1, bias = True, padding_mode = 'zeros', 
       device = None, dtype = None)
```

step2：输入输出
- 输入Input为：$(N, C_{in}, H_{in}, W_{in})$
- 输出Ouput为：$(N, C_{out}, H_{out}, W_{out})$


step3：可学习参数
- 卷积层权重weight，shape为 $(out\_channels, \frac{in\_channels}{groups}, kernel\_size[0], kernel\_size[1])$
- 卷积层偏置bias，shape为 $(out\_channels)$


**池化层——MaxPool2d**

MaxPool2d，即2维最大值池化层。

step1：构造一个二维最大值池化层

```python
# kernel_size: 卷积核大小
# stride: 卷积核步长，默认大小与kernel_size相同（以此来保证不重叠）
# padding: 在四周补0的层数，默认为0即不填充
# dilation:
# ceil_mode:
MaxPool2d(kernel_size, stride =  None, padding = 0, dilation = 1,
          return_indices = False, ceil_mode = False)

```

step2：输入输出
- 输入Input为：$(N, C, H_{in}, W_{in})$
- 输出Output为：$(N, C, H_{out}, W_{out})$

step3：无可学习参数


**标准化层——BatchNorm2d**

BatchNorm2d，即2维批标准化层。

step1：构造一个2维批标准化层

```python
# 
BatchNorm2d(num_features, eps=1e-05, momentum = 0.1, affine = True,
            track_running_stats = True, device = None, dtype = None)
```

step2：输入输出
- 输入Input：$(N, C, H, W)$
- 输出Output：$(N, C, H, W)$ 与输入相同。


step3：无可学习参数



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

光有Dataset还不够，因为Dataset类仅仅只是(1)读入数据集数据并且(2)对读入的数据进行了索引。在实际加载数据中我们的数据量往往都很大，对此我们还需要以下几个功能：
- 能够以batch_size的大小读入数据（节约空间，用不到的数据可以晚加载）。
- 能够对数据进行随机读取（即shuffle=True）。
- 可以并行加载数据（num_worker = n）

这就是DataLoader的功能了，我们在实现好我们的Dataset后，就可以使用`torch.util.data`中的`DataLoader`来实现这些功能了（Dataset充当数据源的作用）。


`torch.utils.data.Sampler` classes are used to specify the sequence of indices/keys used in data loading. They represent iterable objects over the indices to datasets. E.g., in the common case with stochastic gradient decent (SGD), a Sampler could randomly permute a list of indices and yield each one at a time, or yield a small number of them for mini-batch SGD.

A sequential or shuffled `sampler` will be automatically constructed based on the `shuffle` argument to a `DataLoader`. Alternatively, users may use the `sampler` argument to specify a custom Sampler object that at each time yields the next index/key to fetch.

A custom `Sampler` that yields a list of batch indices at a time can be passed as the `batch_sampler` argument. Automatic batching can also be enabled via batch_size and drop_last arguments.


## torch.optim

> step 3 
> 
> -> 定义优化器用来更新梯度

当我们计算出梯度后，我们应该利用优化器来更新梯度。

The *optim* module includes all the tools and functionalities related to running various types of optimization schedules which training a deep learning model.

优化器的作用就是根据学习率和求得的梯度来更新梯度。

优化器是与权重参数和梯度打交道的，它有以下常用方法：
- zero_grad：将梯度清零（不清零的话会累加）。



一个batch的loss关于weight的导数是所有sample的loss关于weight导数的累加和。



## train & test

> step 4 
> 
> -> 定义训练方法和测试方法

训练过程对于每个batch执行的基本步骤：
1. 梯度清零：`optimize.zero_grad()`
2. 前向传播得到预测值：`outputs = model(input)`
3. 计算损失：`loss = criterion(outputs, labels)`
4. 反向传播：`loss.backward()`
5. 更新参数：`optimize.step()`


```python
# model: 待训练的模型
# device: 使用的设备
# train_dataloader: 训练集加载器
# optim: 优化器
# epoch: 轮次
def train(model, device, train_dataloader, optim, epoch)
    model.train()    # 使用BN和Dropout生效
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


**torch.no_grad**

```python
with torch.no_grad():
    # ...
```





## Tensor module

Tensors are conceptually similar to Numpy arrays. A tensor is an n-dimensional array on which we can operate mathematical functions, accelerate computations via GPUs, and tensors can also be used to keep track of a computational graph and gradients, which prove vital for deep learning. To run a tensor on a GPU, all we need is to cast the tensor into a certain data type.

Pytorch中的计算依赖于Tensor。一个Tensor中记录了很多属性其中包括：
- data：存储的数据。
- requires_grad：是否需要求导，默认为False。只要有输入Tensor的requires_grad为True，则其输出Tensor也需要求导。
- grad：该Tensor的梯度。
- grad_fn：用于指示梯度函数的类型，用于计算该tensor的output对于input的梯度。
- is_leaf：用来指示该Tensor是否为叶子节点，只有叶子节点才会保留梯度。


为了使用自动求导（autograd）：
1. 创建叶子节点。首先要创建初始参数（叶子节点），并将初始参数的`requires_grad`设为true。
2. 前向结算。接着将初始参数进行运算得到中间结果（非叶子节点），该中间结果是新的tensor对象并且自动被赋予`grad_fn`属性，该属性为梯度函数。
3. 反向传播。对最后的结果执行`backward`则会进行反向传播，求出各个叶子节点的梯度，保存在`grad`里面。


注意：
- 非叶子节点的梯度在`backward`执行完后会清空。如果要保留则需要将`retain_graph`设置为true。
- 多次反向传播时，梯度是累加的，因此每次进行梯度计算时需要考虑是否清零。


对于Function，其是反向传播的关键，Tensor和Function互相结合就可以构建一个记录有整个计算过程的有向无环图。Function包含两个重要函数forward和backward，其中forward将保留足够的信息用于backward，backward接收由实参传递的对于output的gradient，并通过该gradient计算所有input的gradient然后返回。



数学上，如果有一个函数值和自变量都为向量的函数 $\vec{y} = f(\vec{x})$，那么 $\vec{y}$ 关于 $\vec{x}$ 的梯度就是一个雅克比矩阵：
$$J = \left( \frac{\partial{y_1}}{\partial{x_1}} \right)$$


### 常用函数

- `Tensor.view(-1, feature_num)`：将特征向量拉平用于后续全连接层，-1表示通过其他维度推导。
- `Tensor.size(dim=None)`：返回指定维度对应大小，如果不指定则返回包含所有维度的元组。
- `Tensor.item()`：返回只有一个元素的Tensor的该元素的值。







## 继续阅读
- [Understanding pytorch’s autograd with grad_fn and next_functions](https://amsword.medium.com/understanding-pytorchs-autograd-with-grad-fn-and-next-functions-b2c4836daa00)
- [Getting Started with PyTorch Part 1: Understanding how Automatic Differentiation works](https://towardsdatascience.com/getting-started-with-pytorch-part-1-understanding-how-automatic-differentiation-works-5008282073ec)



## 构建全新模型的pipeline

1. 构建自己的数据集：
   - 借助Dataset定义trainset（包含数据预处理transform），并借助trainset构建train_loader。
   - 借助Dataset定义testset（包含数据预处理transform），并借助testset构建test_loader。
2. 搭建网络模型：
   - 借助Module定义自己的网络模型（包含网络结构和forward）。
     - 仅层的堆叠（Lenet、AlexNet等）
     - 层与基本块堆叠（GoogleNet、ResNet、RNN等）
3. 定义训练和测试方法（训练一轮）：
   - 训练方法参数为：网络模型net，训练数据train_loader，优化器optim，当前轮次epoch。
   - 测试方法参数为：网络模型net，测试数据test_loader。
4. 定义优化器，定义轮次epoch，开始训练和测试。
5. 保存模型。




## fine-tuning模型pipeline


