# git学习笔记

## git版本回退

第一步：使用`git log`查看提交历史。

第二步：使用`git reset`进行版本回退。
```bash
$ git reset --hard commit_id
```







## git分支与合并



> 冲突产生的原因：每个文件只能有一个正确的版本，不能有多个版本。因此当合并分支时如何该文件有多个版本，则会产生冲突，需要用户手动取舍，如果不存在同一个文件有多个版本，则可以直接使用fast-forward方式解决冲突。




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