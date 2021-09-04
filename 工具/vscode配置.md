# vscode


## 配置

vscode提供两种级别的配置：
- 用户级配置——配置的生效范围为你打开的所有vscode实例。
- 工作区配置——配置存储在你的工作区并且仅仅在你打开该工作区才生效。

其中可以把用户级配置全局配置，而工作区配置看成进一步配置。因此，工作区的配置会覆盖掉用户级配置。

> Note: 一个vscode工作区通常指的是你的项目根目录文件夹。工作区配置和调试(debugging)以及任务(task)配置均存放在工作区根目录的`.vscode`文件夹中。


### task配置

> Tasks in VS Code can be configured to run scripts and start processes so that many of these existing tools can be used from within VS Code without having to enter a command line or write new code. Workspace or folder specific tasks are configured from the **`tasks.json`** file in the **`.vscode`** folder for a workspace.


### debug配置

> However, for most debugging scenarios, creating a launch configuration file is beneficial because it allows you to configure and save debugging setup details. VS Code keeps debugging configuration information in a **`launch.json`** file located in a **`.vscode`** folder in your workspace (project root folder) or in your user settings or workspace settings.


### C++配置

> You can override the default values for properties set in **`c_cpp_properties.json`**.








## 快捷键——macOS


**添加注释**
- 注释一行代码：`command + /`
- 注释一整段代码：`option + shift + A`


**格式化代码**
- 格式化全部代码
- 代码缩进
- 格式化选中行代码




