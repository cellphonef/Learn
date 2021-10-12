# git学习笔记

## git版本回退

第一步：使用`git log`查看提交历史。

第二步：使用`git reset`进行版本回退。
```bash
$ git reset --hard commit_id
```







## git分支与合并

> git鼓励在工作流程中频繁地使用分支与合并。

为了真正理解Git处理分支的方式，我们需要知道Git是如何保存数据的。

:star:git保存的不是文件的变化或者差异，而是一系列不同时刻的**快照**。






> 冲突产生的原因：每个文件只能有一个正确的版本，不能有多个版本。因此当合并分支时如何该文件有多个版本，则会产生冲突，需要用户手动取舍，如果不存在同一个文件有多个版本，则可以直接使用fast-forward方式解决冲突。



## git远程仓库

**查看远程仓库**

使用`git remote`查看远程仓库或者`git remote -v`查看远程仓库URL。

```bash
$ git remote
# origin

$ git remote -v
#origin  git@github.com:cellphonef/Learn.git (fetch)
#origin  git@github.com:cellphonef/Learn.git (push)
```

**添加远程仓库**

使用`git clone`或者`git remote add`可以添加远程仓库。

使用`git clone`来克隆一个远程仓库，命令会自动将该仓库添加为远程仓库并默认以origin命名。


**从远程仓库中抓取与拉取**

使用`git fetch <remote>`从远程仓库中获得数据。

该命令会访问远程仓库，从中拉取所有你还没有的数据。执行完成后，你将会拥有那个远程仓库中所有分支的引用，可以随时合并或查看。

必须注意`git fetch`命令只会将数据下载到你的本地仓库——它并不会自动合并或修改你当前的工作。当准备好时你必须手动将其合并入你的工作。

如果你的当前分支设置了跟踪远程分支，那么可以用`git pull`命令来自动抓取后合并该远程分支到当前分支。（默认情况下，使用`git clone`克隆远程仓库，该命令会自动设置本地main分支跟踪克隆的远程仓库的main分支）



****






## git文件重命名


第一步：使用`git mv`修改文件名。
```bash
$ git mv old_filename new_filename
```

第二步：使用`git status`查看新旧文件名。
```bash
$ git status
# On branch your-branch
# Changes to be committed:
#   (use "git reset HEAD ..." to unstage)
#
#     renamed: old_filename -> new_filename
#
```

第三步：使用`git commit`提交暂存区。
```bash
$ git commit -m "rename file"
```

第四步：使用`git push`推送更改到远程仓库。
```bash
$ git push origin your-branch
```