# DL外的领域知识

## 语义分割


## 生成对抗网络（GAN）




## 注意力机制（Attention）

按注意力机制的可微性，可分为：
- Hard-Attention，即0/1问题，某个区域要么被关注，要么不关注，不可微。
- Soft-Attention，[0, 1]连续分布问题，用0到1的不同权重表示每个区域被关注程度的高低，可微。


按注意力机制的关注域，可分为：
- 空间域spatial domain
- 通道域channel domain
- 层域layer domain
- 混合域mixed domain
- 时间域time domain

### CNN with Attention

主要分为两种，一种是spatial attention，另外一种是channel attention。


Attention机制听起来高大上，其实就是学习出一种权重映射图，再拿这个权重映射图加在原来的特征之上，就叫Attention。




## 熵

### 信息熵

信息熵是衡量随机变量分布的混乱程度，是随机分布各事件发生的信息量的期望值，随机变量的取值个数越多，状态数也就越多，信息熵就越大。当随机变量服从均匀分布时，熵最大。

信息熵的数学定义:
$$H(X) = -\sum_{x}p(x)logp(x) = -\sum_{i=1}^{n}p(x_i)logp(x_i)$$

### 相对熵，KL散度

相对熵可以用来衡量两个概率分布之间的差异，但不是距离。

相对熵的数学定义：设
$$D_{KL}(p || q) = \sum_{x}p(x)log\frac{p(x)}{q(x)}$$




### 交叉熵




参考链接：
- [详解机器学习中的熵、条件熵、相对熵和交叉熵](https://www.cnblogs.com/kyrieng/p/8694705.html)






