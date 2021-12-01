

# DL

DL，即Deep Learning=深度学习。

**What**

在人工智能领域里，有一个方法叫机器学习，而机器学习里面有一类算法叫神经网络，而深度学习就是使用深层神经网络进行学习的方法。


![DL](img/DL基础_2021-09-16-10-34-12.png)






## 数学基础

### 方向导数与梯度

『导数』是函数的局部性质，一个函数在某一点的导数描述了这个函数在这一点附近的变化率。

『方向导数』顾名思义就是某个方向上的导数。

对于一元函数 $y = f(x)$，其自变量为一元，因此只有一个方向的方向导数，即沿着x轴方向的导数（因为x只能增加或减少）。

而对于多元函数，如二元函数 $z = f(x, y)$，其自变量为二元，因此可以朝着一个平面的任意方向进行改变，因此有无数个方向导数。

在这无数个方向导数中，有两个特殊方向（即沿着坐标轴x和y轴）的方向导数称为偏导数。



### 梯度下降算法数学原理

神经网络的梯度下降法能够朝着正确方向行进的本质是：[泰勒公式](https://zhuanlan.zhihu.com/p/36564434)。

有三种不同的梯度下降算法，其区别在于使用多少数据来计算目标函数的梯度（根据我们手上的数据量，我们折中考虑权重参数更新的准确率以及参数更新的频率）：
- BGD（Batch Gradient Descent，批量梯度下降法），利用所有训练数据来计算权重参数的梯度后更新梯度，权重参数更新方向准确，但更新频率低。对于凸误差表面，BGD保证能够到达全局最小值，而对于非凸表面，BGD保证能到达一个局部的最小值（并且困于此，不会逃出）。
- SGD（Stochastic Gradient Descent，随机梯度下降法），利用每一个样本计算一次权重参数的梯度并更新梯度，权重参数更新方向不一定准确（目标函数会波动），但更新频率高。由于SGD的波动，可能会使得权重参数逃离当前的局部最小值，到达另一个更小的局部最小值，不过SGD难以逃离鞍点。
- MBGD（Mini-Batch Gradient Descent，小批量梯度下降法），以上两种的折中，也最常用。


> SGD-M优化
> 
> The momentum term increases for dimensions whose gradients point in the same directions and reduces updates for dimensions whose gradients change directions. As a result, we gain faster convergence and reduced oscillation.


> NAG
> 



### 计算机中实现梯度下降——计算图

> 计算图就是一个有向无环图。

假设我们优化的目标函数为 $J(a, b, c) = 3(a + b*c)$

我们令 $u = b*c$，$v = a + u$，$J = 3*v$

则我们的计算图如下（设a = 5, b = 3, c = 2）：

![compute graph](img/DL基础_2021-09-22-10-41-43.png)

得到结果为33，这就是一次前向传播的过程（forward）。

计算图通常包含两种元素：
- tensor，即输入输出数据。
- Function，某个节点的激活函数，内部包括`forward`、`backward`两个方法，分别用于前向和反向。

如果我们想计算目标函数 $J$ 对于各个自变量的导数，则我们需要反向传播。

**反向传播的推导与编程实现**

网络结果如下图：

![nn](img/DL基础_2021-09-22-13-18-36.png)

目标函数： $E = \frac{1}{2}\sum\limits_{i\in outputs}(t_i - y_i)^2$

符号定义：
- $net_j = \vec{w_j} \cdot \vec{x_j} = \sum\limits_{i}w_{ji}x_{ji}$，其中 $net_j$ 表示节点 $j$ 的输入加权和，$\vec{w_j}$ 表示节点 $j$ 的输入权重， $\vec{x_j}$ 表示节点 $j$ 的输入特征。

由于 $E$ 是 $net_j$ 的函数，而 $net_j$ 是 $w_{ji}$ 的函数，根据链式法则有：
- $\frac{\partial{E}}{\partial{w_{ji}}}=\frac{\partial{E}}{\partial{net_j}}\cdot\frac{\partial{net_j}}{\partial{w_{ji}}}$

对于 $\frac{\partial{net_j}}{\partial{w_{ji}}}$ ，其计算方法不管是在隐藏层还是输出层都是一样的，结果都为：
- $\frac{\partial{net_j}}{\partial{w_{ji}}}=x_{ji}$，其中 $x_{ji}$ 为节点 $i$ 的输出值。

而对于 $\frac{\partial{E}}{\partial{net_j}}$ 的计算则需要区分是输出层还是隐藏层。

*输出层的权重训练*

对于输出层，$net_j$ 通过影响节点 $j$的输出值 $y_j$来影响网络的其他部分，即 $E$ 是 $y_j$ 的函数，而 $y_j$ 是 $net_j$ 的函数。其中 $y_j=sigmoid(net_j)$。所以根据链式求导法则：
- $\frac{\partial{E}}{\partial{net_j}}=\frac{\partial{E}}{\partial{y_j}}\cdot\frac{\partial{y_j}}{\partial{net_j}}$

考虑上式的第一项：
- $\frac{\partial{E}}{\partial{y_j}}=\frac{\partial}{\partial{y_j}}\frac{1}{2}\sum\limits_{j\in outputs}(t_j - y_j)^2=-(t_j- y_j)$

考虑上式第二项：
- $\frac{\partial{y_j}}{\partial{net_j}}=y_j(1-y_j)$

将以上两项带入：
- $\frac{\partial{E}}{\partial{net_j}} = -(t_j - y_j)y_j(1-y_j)$

此时我们令：
- $\delta_j = -\frac{\partial{E}}{\partial{net_j}}=(t_j-y_j)y_j(1-y_j)$


*隐藏层权重训练*

对于隐藏层，首先我们定义节点 $j$ 的所有直接下游节点的集合为 $Downstream(j)$，例如对于网络结构图中节点4，其直接下游节点集合节点8和9。可以看到 $net_j$只能通过影响集合 $Downstream(j)$ 中的节点的输入值来进一步影响 $E$。设 $net_k$ 为是节点 $j$的下游节点的加权和输入，则 $E$ 是 $net_k$的函数，而 $net_k$ 是 $net_j$ 的函数。因为$net_k$有多个，这里应用全导数公式，可得到：
- $\frac{\partial{E}}{\partial{net_j}}=\sum\limits_{k \in Downstream(j)}\frac{\partial{E}}{\partial{net_k}}\frac{\partial{net_k}}{\partial{net_j}}$
- $=\sum\limits_{k \in Downstream(j)}-\delta_k\frac{\partial{net_k}}{\partial{net_j}}$
- $=\sum\limits_{k \in Downstream(j)}-\delta_k\frac{\partial{net_k}}{\partial{a_j}}\frac{\partial{a_j}}{net_j}$
- $=\sum\limits_{k \in Downstream(j)}-\delta_k w_{kj}a_j(1-a_j)$
- $=-a_j(1-a_j)=\sum\limits_{k \in Downstream(j)}-\delta_k w_{kj}$

因为，我们令：
- $\delta_j = -\frac{\partial{E}}{\partial{net_j}}$

因此，对于隐藏层的误差项：
- $\delta_j = a_j(1-a_j)\sum\limits_{k \in Downstream(j)}\delta_k w_{kj}$

则各层的权重训练公式如下：
- $w_{ji} \leftarrow w_{ji} - \eta\frac{\partial{E}}{\partial{w_{ji}}} = w_{ji} + \eta\delta_j x_{ji}$


因此，反向传播的过程就是从后往前传递误差项，然后根据误差项计算梯度。





## 神经网络

神经网络如下图所示：

![NN](img/DL基础_2021-09-16-10-36-20.png)

图中每个圆圈都是一个神经元，每条线表示神经元之间的连接。上面的神经元被分成了多层，层与层之间的神经元有连接，而层内之间的神经元没有连接。

一个神经网络的架构分层一般分为三层：
- 最左边的输入层（Input Layer, 1层）
- 中间的隐藏层（Hidden Layer, >=1层）
- 最右边的输出层（Output Layer, 1层）

隐藏层比较多的神经网络称为深度神经网络。

**神经元**

神经网络的基本组成结构是神经元。

一个神经元的结构如下图：

![神经元](img/DL基础_2021-09-16-10-50-46.png)

其组成部分有：
- 输入权值（Input & Weight）。一个神经元可以接受多个输入，每个输入上都有一个权值，此外还有一个bias偏置项。
- 激活函数（activate function）。激活函数有多重选择。
- 输出。每个神经元都会产生一个输出，可能作为下一层神经元的输入。输出的计算方式 $y = f(w * x + b)$

> Q：[为什么要有激活函数？](https://www.zhihu.com/question/22334626)
> 
> A：激活函数是用来加入非线性因素的，解决线性模型不能解决的问题。


目标函数

损失函数

优化算法

我们的目标是使得目标函数最优，每次根据样本的标签和预测计算损失，然后求得目标函数，根据优化算法进行优化。



实际上根据神经元的不同连接方式有不同的神经网络：
- 卷积神经网络
- 循环神经网络
- 长短时记忆神经网络
- 递归神经网络




## CNN——卷积神经网络

### CNN的发展史

![CNN](img/DL基础_2021-09-22-20-34-25.png)

CNN1989年问世：
- 第一个CNN称为**ConvNet**，该模型可以用于可视化认知任务，例如手写数字识别。
- 1998年，改进后的ConvNet的模型**LeNet**问世，由于其高准确率被工业界采用，自此CNN模型变成最成功的机器学习模型，工业界和学术界都广泛使用。
- 1998年自2012年，AlexNet
- GoogleNet
- VGGNet
- (skip connection start)...
- ResNet
- DenseNet
- EfficientNet


feature map的尺寸计算方式： 
- $(input\_size + 2 * padding\_size - filter\_size) / stride + 1$

### 卷积层（Conv）



把filter看成特征提取器，由神经网络自己训练，越深的网络提取的特征越深越具有一般性




### 池化层（Pool）

作用：
- 平移不变性（？）。
- 减少计算量。
- 获得定长输出。
- 防止过拟合或有可能带来欠拟合。

### 全连接层（FC）







## RNN——循环神经网络


## LSTM——长短时记忆神经网络


## 递归神经网络
















## 名词概念

### backbone


### fine-tuning
- 译为：微调。用于迁移学习。


### embedding

embedding，是一项技术方法，它将离散变量（discrete variables）转换成连续的向量（continuous vectors）。


好处（个人总结）：
- 便于计算机处理。
- 每个实体都有统一表示，因此可以计算相似度，并且可以对原始数据进行降维。
- 可以通过监督的方法学习，避免干扰。



参考文献：[Neural Network Embeddings Explained](https://towardsdatascience.com/neural-network-embeddings-explained-4d028e6f0526)


### open/close-set

所谓close-set，就是所有测试集都在训练集出现过，不会出现新的未见过测试数据，并且测试结果一定会有一个确定的结果。形象化的解释就是：如果把训练看成学习教科书上的知识，测试集看成考试的题的话，那么考试过程中出的所有题目都是教科书上的，也因此题目的一定有一个明确的答案。

所谓open-set，就是存在训练集中不存在的新测试数据，并且测试结果可能不存在一个确定的结果。形象化的解释是：如果把训练看成学习教科书上的知识，测试看成考试的题的话，那么考试过程中出的题会出现一些新题不是出自教科书的，也因此这个新题可能是没有答案的。


![open/close-set](img/DL基础_2021-11-29-16-22-26.png)



### 训练过程名词

- sota：结果最优的。
- iteration：一次iteration更新一次模型参数
- batch/batch_size

#### epoch、iteration、batch/batch_size

- 一个epoch（中译：轮次）指的是遍历完训练集里的每一个样本，即跑完所有batch。
-  多个epoch的目的是为了寻找全局最低值，因为一个epoch可能到不了全局最低值（参见：[Why are multiple epochs needed for deep learning?](https://www.quora.com/Why-are-multiple-epochs-needed-for-deep-learning)）。
- 每次epoch通常伴随着shuffle（参见：[浅谈深度学习shuffle问题](https://blog.csdn.net/g_b_l/article/details/109600536)）。

#### Ground Truth

- 译为地面实况。在机器学习中就是『参考标准』，预测结果根据该参考标准计算损失，并优化该损失，在有监督学习中，可以简单理解成标签。

例如目标检测情景中：

![Ground Truth](img/DL基础_2021-09-15-20-27-06.png)








## DL总结



任何形式的信息都要经过编码转换成计算机能够处理的形式才能被计算机利用起来，而计算机处理的形式就是向量vector。因此我们在处理信息时，我们首先要将信息转换成向量vector，通常的做法有one-hot编码，embedding等等，这些编码方式可以人为设定也可以让网络通过学习得到。

对于每个神经网络结构，它都有自己擅长的做的事：
- CNN：擅长提取图像特征（例如：用于图像分类）。
- RNN：擅长提取序列的时空特征（例如：用于句子填空）。
- Transformer：擅长提取序列的时空特征。
- GAN：擅长生成数据（例如：用于生成二次元头像）。
- FCN：擅长计算相关性（通常用来分类）


对于某些任务，我们可能需要将以上神经网络结构进行结合，以发挥各自的优势：
- Image caption generation：利用CNN提取图像特征vector，利用RNN生成句子。
- machine translation/chat-bot：利用RNN生成输入句子的vector（这个过程可以称为encoder），再利用另一个RNN生成句子（这个过程可以称为decoder）。

原始RNN：不擅长捕获长期依赖关系。

LSTM：可以解决长期依赖问题，但是时序性的结构这一方面使其很难具备高效的并行计算能力，另一方面使得整个LSTM模型总体上更类似马尔科夫决策过程，难以提取全局信息。

Transformer：可以取代RNN。

![image caption](img/DL基础_2021-11-28-16-13-02.png)

![machine translation](img/DL基础_2021-11-28-16-17-02.png)

![encoder-decoder](img/DL基础_2021-11-28-16-19-33.png)

