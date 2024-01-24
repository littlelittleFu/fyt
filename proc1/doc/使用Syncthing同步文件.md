##### 原因

- 脚本组在阿里云上远程编辑服务端脚本、配置，没有使用git/svn，同步不便
- 服务端变更接口、枚举值、游戏配置等，也需要同步到脚本

Syncthing可以解决以上问题，在任一端的修改都可以同步到另一端。

##### 操作步骤

- 下载[Syncthing压缩包](https://github.com/syncthing/syncthing/releases/download/v1.23.1/syncthing-windows-amd64-v1.23.1.zip)
- 按[官网教程](https://docs.syncthing.net/users/autostart.html#autostart-windows-taskschd)设置为登录自启动
- 用浏览器打开管理界面`127.0.0.1:8384`，语言选中文，点击`操作-设置`修改设备名，最好是本人缩写
- 打开远程Syncthing管理界面，地址、帐号如下

| 地址                | 帐号 | 密码 |
| ------------------- | ---- | ---- |
| 39.103.229.43:9960  | Van  | 4201 |
| 114.215.187.39:9960 | Tim  | 8402 |
| 120.26.169.28:9960  | Mac  | 2703 |

- 在远程Syncthing管理界面上点击`操作-显示ID-Copy`，在本地管理界面中点击`添加远程设备`，将之前复制的ID粘贴在`设备ID`栏并设置`设备名`
- 远程管理界面会收到本机的添加请求，接受并设置设备名
- 选择远程设备上的文件夹，点击`选项-共享`，勾选自己的设备。本地会收到同步请求，接受并选择一个空文件夹进行同步
- 点击本地文件夹`选项-忽略模式`，加入以下内容表示只同步指定目录下的lua、grid、csv文件到远程

```
!/MapServer.d/MapGrid/*.grid
!/MapServer.d/Scripts/**.lua
!/res/db/*.csv
*
```

##### 注意事项

同时修改同一份文件，当一方保存时另一方正在编辑，有些编辑器会提示文件已修改是否重新加载，此时不要点击是，否则会覆盖已有修改，另存为其他文件然后比对编辑。

##### 服务器指定脚本路径

脚本同步以后，在本地有多个版本的情况，指定其中的一个版本可以通过服务器的[配置文件](配置文件说明.md#mapserver)，例如：

```ini
[CenterServer]
ScriptFolderPath=D:\sync\28\bin\CenterServer.d\Scripts
GameCfgFolderPath=D:\sync\28\bin\res\db

[MapServer]
ScriptFolderPath=D:\sync\28\bin\MapServer.d\Scripts
MapGridFolderPath=D:\sync\28\bin\MapServer.d\MapGrid
GameCfgFolderPath=D:\sync\28\bin\res\db
```