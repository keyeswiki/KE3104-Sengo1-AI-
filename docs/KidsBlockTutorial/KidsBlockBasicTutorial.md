# 2.1 Windows 系统

## 2.1.1 KidsBlock 软件下载

* [Windows 系统 KidsBlock 软件下载](https://xiazai.keyesrobot.cn/KidsBlock.exe)

## 2.1.2 KidsBlock 安装

1\. 双击下载好的软件 “**KidsBlock.exe**” 。

![Img](./media/kidsblock-1.png)

2\. 先选中 “**为使用这台电脑的任何人安装**” ，再点击 “**下一步**”。

![Img](./media/kidsblock-2.png)

3\. 先点击 “**浏览(B)...**”，选择安装的位置（我这里选择安装在C盘，你也可以选择安装在电脑的其他盘），再点击 “**安装**”。这样，软件就在安装过程中。

![Img](./media/kidsblock-3.png)

![Img](./media/kidsblock-4.png)

4\. 几秒种后，安装完成。点击 “**完成**” 就可以打开安装好的软件。

![Img](./media/kidsblock-5.png)

5\. 如果出现电脑安全警报窗口，点击 “**允许访问**”。这样就可以打开了软件页面。

![Img](./media/kidsblock-7.png)

![Img](./media/kidsblock-6.png)

有更新软件时一般打开Kidsblock IDE页面时会自动提醒，为了软件能正常使用我们选择升级。

![Img](./media/kidsblock-8.png)

我们也可在设置中手动更新软件。

![Img](./media/kidsblock-9.png)

![Img](./media/kidsblock-8.png)

如果已经是最新版本则显示以下提示。

![Img](./media/kidsblock-10.png)

# 2.2 MacOS 系统

## 2.2.1 KidsBlock 软件下载

* [MacOS 系统 kidsBlock 软件下载](https://xiazai.keyesrobot.cn/KidsBlock.dmg)

## 2.2.2 KidsBlock 软件安装

1\. 双击下载好的软件文件 “**KidsBlock.dmg**”。

![Img](./media/kidsblock-11.png)

2\. 双击之后，出现如下图。

![Img](./media/kidsblock-12.png)

3\. 按住鼠标左键将 “**KidsBlock**” 拖动到 **Applications** 文件夹中。

![Img](./media/kidsblock-13.png)

4\. “**KidsBlock**” 在复制拷贝至 **Applications** 文件夹过程中，有可能会出现 “**安全提醒**” 框 。

![Img](./media/kidsblock-14.png)

![Img](./media/kidsblock-15.png)

5\. 先点击电脑的 “**设置**”，找到 “**隐私与安全性**” 并且点击它；然后找到 “**仍要打开**” 并且点击它，出现 “ **打开“KidsBlock”？**”对话框，最后点击 “**仍要打开**” 按钮。

![Img](./media/kidsblock-16.png)

![Img](./media/kidsblock-17.png)

6\. 出现 “**隐私与安全性**”对话框，在对话框中输入好 “**管理员用户名**” 和 “**密码**”，然后单击 “**好**” 按钮。

![Img](./media/kidsblock-18.png)

7\. 过一会儿之后，就可以打开了Kidsblock IDE页面。

![Img](./media/kidsblock-19.png)

有更新软件时一般打开Kidsblock IDE页面时会自动提醒，为了软件能正常使用我们选择升级。

![Img](./media/kidsblock-8.png)

# 2.3 KidsBlock软件的使用方法

⚠️ **特别提醒：** 以下是以Windows系统为例，MacOS系统可以参考。

## 2.3.1 安装开发板驱动

1. 安装好KisdBlock软件后，在桌面双击打开![KidsBlock](./media/KidsBlock.png)
2. 进入页面后点击右上角的设置按钮

![Equip-21](./media/Equip-21.png)

3. 再点击`安装驱动`。

![Equip-22](./media/Equip-22.png)

4. 根据电脑弹窗提示依次确认后最后会弹出这个弹窗，我们点击`INSTALL`然后等待安装成功

![Equip-23](./media/Equip-23.png)

## 2.3.2 选择设备

1\. 确保ESP32主控板与计算机连接成功，然后在电脑桌面双击 “**KidsBlock**” 图标![KidsBlock](./media/KidsBlock.png)打开KidsBlock软件。

![Equip-18](./media/Equip-18.png)

2\. 单击![Equip](./media/Equip.png)，如下图所示：

![Equip-1](./media/Equip-1.png)

3\. 由于本教程使用的是 ESP32 设备，所以选择 “**ESP32S development board**” 设备（在搜索栏输入`esp32`就会出现），如下图所示：

![Equip-3](./media/Equip-3.png)

4\. 连接串口端口(COM7)，点击 “**连接**”，如下图所示：

![Equip-4](./media/Equip-4.png)

5\. 然后单击 “**返回编辑器**” 返回代码编辑区，如下图所示：

![Equip-5](./media/Equip-5.png)

![Equip-6](./media/Equip-6.png)



## 2.3.3 软件界面介绍

了解KidsBlock软件界面，有利于代码编程的学习，如下图所示：

![Equip-7](./media/Equip-7.png)

![Equip-8](./media/Equip-8.png)



## 2.3.4 添加KidsBlock库文件

⚠️ **特别提醒：** 如果是自己拖动代码块来编写实验代码，则必须手动添加库文件没有库文件你是找不到对应功能的代码块的。如果你是直接导入我们提供的代码文件则无需添加库文件因为导入代码文件时会自动添加。

基础教程中我们需要添加`Sengo1`的库文件，方法如下：

在KidsBlock 软件的左下角点击![Img](./media/Extension.png)进入扩展界面。

![Extension1](./media/Extension1.png)

在搜索栏中输入`sengo1`便会直接找到Sengo1的库，我们点击它即可添加Sengo1的库文件。

![PRO1](./media/PRO1.png)

添加成功如图：

![PRO01](./media/PRO01.png)

点击![Return](./media/Return.png)返回编程界面，在KidsBlock 左侧的代码块栏中可以看到添加成功的 “Sengo1” 库。

![Equip-19](./media/Equip-19.png)

## 2.3.5 如何搭建代码与保存以及上传

确保ESP32主控板与计算机连接成功，然后双击 “ **KidsBlock** ” 图标打开KidsBlock软件。

直接拖动代码块到代码编辑区进行代码编写，下面我们搭建一个使用串口打印的程序，如下图所示：

![Equip-9](./media/Equip-9.gif)

如果你想要将代码保存到电脑，则鼠标单击`文件`然后再单击`保存到电脑`

![Equip-10](./media/Equip-10.png)

选择保存的位置（最好是自己能轻易找到的位置），给代码文件命名然后点击`保存`。

![Equip-20](./media/Equip-20.png)

上传代码前确保开发板是连接状态![](./media/Equip-15.png)

单击![upload](./media/upload.png)将代码上传到ESP32主控板，如下图所示：

![Equip-11](./media/Equip-11.png)

上传成功后串口打印区回打印字符“Hello KidsBlock”

![Equip-16](./media/Equip-16.png)

## 2.3.6 如何打开代码文件并上传

从电脑打开已经编写好的代码，这里我们以`2.3.4 如何搭建代码与保存以及上传`保存的"Hello_KidsBlock.sb3"代码文件为例。

单击`文件`然后再点击`从电脑中上传`

![Equip-12](./media/Equip-12.png)

然后选择保存"Hello_KidsBlock.sb3"代码文件的路径，选中代码文件打开即可，如下图所示：

![Equip-13](./media/Equip-13.png)

代码文件打开后，需要手动连接串口端口，如下图所示：

![Equip-14](./media/Equip-14.png)

![Img](./media/Equip-4.png)

然后单击 “**返回编辑器**” 返回代码编辑区，如下图所示：

![Img](./media/Equip-5.png)

单击![Img](./media/upload.png)将代码上传到ESP32主控板，如下图所示：

![Img](./media/Equip-11.png)

上传成功后串口打印区回打印字符“Hello KidsBlock”

![](./media/Equip-16.png)