# DL外的领域知识


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









