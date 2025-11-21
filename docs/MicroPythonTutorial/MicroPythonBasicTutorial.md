MicroPython是Python 3语言的精简实现，包括Python标准库的一小部分，经过优化可在微控制器和受限环境中运行。以下是MicroPython的主要特点：

1. **兼容性**：MicroPython努力与普通的Python（称为CPython）尽可能兼容，这意味着如果你了解Python，就已经掌握了MicroPython的基础知识。
2. **硬件访问**：除了实现一系列核心Python库之外，MicroPython还包括用于访问低级硬件的“机器”等模块，使得开发者能够直接控制微控制器的硬件资源。
3. **交互式提示符（REPL）**：MicroPython提供了一个交互式提示符（REPL），允许用户直接在嵌入式平台上从桌面计算机执行命令。这对于嵌入式系统的快速实时测试和调试非常有用。
4. **多线程支持**：MicroPython固件支持多线程功能，这使得单个微控制器能够同时处理多个嵌入式任务，从而加速嵌入式应用程序的执行。
5. **开源项目**：MicroPython是一个开源项目，其源代码可在Github上获取。它遵循MIT许可证，可免费用于教育和商业目的。
6. **广泛支持**：MicroPython支持多种微控制器板和RTOS（实时操作系统），如ESP32、ESP8266、STM32，Pico等。此外，它还提供了丰富的库和模块，以满足不同开发需求。

# 2.1 软件下载

## 2.1.1 Windows系统 软件下载

**操作系统：Windows 10**

软件下载链接：[Thonny软件官网](https://thonny.org)

鼠标触碰到箭头所示处，会出现Windows官方下载的版本选择。

![1101](./media/thonny-1.png)

![1102](./media/thonny-2.png)

## 2.1.2 MAC系统

请参考Windows系统教程。

![1103](./media/thonny-3.png)

![1104](./media/thonny-4.png)

# 2.2 软件安装

Thonny应用程序安装支持两种安装方式：

- 安装Thonny+Python捆绑包

  这种方式本质是将Python环境和Thonny打包在一起，即可一键安装使用，快捷方便，推荐新手使用此方式。捆绑包的方式安装又分为两种：

  - Installer安装

    ![1201](./media/thonny-5.png)

  - 免安装版本

    ![1202](./media/thonny-6.png)

- 单独安装Thonny

  Thonny应用本质是以python包的形式存在，当用户已经具备python环境，即可通过`pip install thonny`单独安装Thonny。这种方式更适合开发者。

  ![1203](./media/thonny-7.png)

请根据您的需求选择下载相应版本的压缩包。

## 2.2.1 Installer安装

请根据您的操作系统选择对应的程序下载。以 <span style="background:#ff0;color:#000">64bit Windows 10</span> 环境下，安装程序`Installer with 64-bit Python 3.10` 为例。

（1）下载完成后双击![1204](./media/thonny-8.png) 。弹出 Select Setup Install Mode 窗口，选择 **Install for me only** 。

![1205](./media/thonny-9.png)

（2）单击 **Next** 。

![1206](./media/thonny-10.png)

（3）选中 **I accept the agreement** ，单击 **Next** 。

![1207](./media/thonny-11.png)

（4）Thonny软件的安装路径，默认安装在C盘。单击 Browse... 可以选择其他安装位置，单击 **Next** 进行下一步。

![1208](./media/thonny-12.png)

（5）默认将在下面的开始菜单文件夹中创建程序的快捷方式。单击 Browse... 可以选择其他安装位置，单击 **Next** 进行下一步。

![1209](./media/thonny-13.png)

（6）勾选 **Creat desktop icon** ，单击 **Next** 。

![1210](./media/thonny-14.png)

（7）单击 Inatall 进行安装。

![1211](./media/thonny-15.png)

（8）单击“**Finish**”结束安装,安装完成。

![1212](./media/thonny-16.png)

（9）回到桌面，双击 Thonny 图标。选择语言，即可开始运行。

![1213](./media/thonny-17.png)

（10）安装完成。

![1214](./media/thonny-18.png)

## 2.2.2 免安装版本

请根据您的操作系统选择对应的程序下载。以 <span style="background:#ff0;color:#000">64bit Windows 10</span> 环境下，安装程序`Portable variant with 64-bit Python 3.10` 为例。

（1）下载完成后解压，双击![1105](./media/thonny-19.png)，选择语言，即可开始运行。

![1213](./media/thonny-17.png)

（2）安装完成。

![1214](./media/thonny-18.png)



## 2.2.3 语言设置

点击`Tools`然后再点击`Options...`

![thonny-56](./media/thonny-56.png)

点击`General`

![thonny-57](./media/thonny-57.png)

下拉语言选择框，找到`简体中文`，选中后点击`OK`

![thonny-58](./media/thonny-58.png)

设置成功后，需要关闭软件重新打开才能显示中文。

![thonny-59](./media/thonny-59.png)

# 2.3 烧录固件（重要）

要想在Pico上运行MicroPython代码，就必须要给Pico烧录MicroPython 固件。

![thonny-22](./media/thonny-22.png)

A.连接microUSB线一端到你的电脑USB口。

B.按住“Raspberry Pi Pico”上的白色按钮（BOOTSEL）。然后，通过microUSB线另一端将Raspberry Pi Pico与电脑连接。

![thonny-23](./media/thonny-23.png)

C.松开按钮，当连接成功时，在你的电脑上打开[设备管理器]，电脑将自动识别可移动磁盘(RPI-RP2)，如下所示:

![thonny-24](./media/thonny-24.png)

D.复制"Firmware"文件夹中的`RPI_PICO-20250809-v1.26.0.uf2`文件到可移动磁盘(RPI-RP2)，并等待它完成，就像复制文件到U盘一样。

![thonny-25](./media/thonny-25.gif)

E.当固件烧入完成后，Raspberry Pi Pico会自动重启。之后，你可以运行Micropython。

# 2.4 页面介绍

单击 **视图** ，勾选 **文件** ，打开文件路径管理，方便使用。

![1401](./media/thonny-26.png)

![1402](./media/thonny-27.png)

# 2.5 工具栏介绍:

![1403](./media/thonny-28.png)

|              按钮              |       功能        |
| :----------------------------: | :---------------: |
| ![1404](./media/thonny-29.png) |     新建页面      |
| ![1405](./media/thonny-30.png) |      打开...      |
| ![1406](./media/thonny-31.png) |       保存        |
| ![1407](./media/thonny-32.png) |   运行当前脚本    |
| ![1408](./media/thonny-33.png) |   调试当前脚本    |
| ![1409](./media/thonny-34.png) |       步过        |
| ![1410](./media/thonny-35.png) |       步进        |
| ![1411](./media/thonny-36.png) |       步出        |
| ![1412](./media/thonny-37.png) |     恢复执行      |
| ![1413](./media/thonny-38.png) | 停止/重启后端进程 |



# 2.6 如何将Pico连接到Thonny软件

将Pico开发板连接到电脑，然后设置开发板为Pico并且选择端口。步骤如下：点击`工具`-->`选项...`

![thonny-42](./media/thonny-42.png)

选择`解释器`，然后设置开发板为`MicroPython(Raspberry Pi Pico)`，端口则选择自动识别到的端口（如果你有多个端口不确认是哪个时你可以拔掉Pico开发板与电脑的连接看哪个端口消失了来确认），选择好后点击`确认`

![thonny-43](./media/thonny-43.png)

连接成功后，Thonny的左边会出现“Raspberry Pi Pico”的区域并且右下角也会有提示

![thonny-44](./media/thonny-44.png)

# 2.7 如何打开代码文件

<span style="color:red;">注意：需要再`1.代码和库文件下载`中下载项目所需的资料文件，然后解压到电脑桌面以便于寻找。</span>

在 文件区单击 “此电脑” ，按照电脑桌面的路径找到文件`资料`

![thonny-39](./media/thonny-39.png)

再进入`codes`文件夹便能看到代码文件了，鼠标双击代码文件即可在Thonny软件中打开。

![thonny-40](./media/thonny-40.png)

# 2.8 如何将库文件保存到Pico中（重要）

没有保存库文件到Pico开发板时运行代码报错现象如下：

![thonny-46](./media/thonny-46.png)



**添加库文件方法：** 在文件区打开`资料`文件中的`lib`文件便能看到库文件了

![thonny-41](./media/thonny-41.png)

鼠标右击`Sengo1.py`文件然后选择"上传到 / "

![thonny-45](./media/thonny-45.png)

上传成功后会在"Raspberry Pi Pico"区域内显示`Sengo1.py`文件，剩下的`neopixel.py`也是用同样的方法添加。

![thonny-47](./media/thonny-47.png)

# 2.9 如何在线运行代码

我们以运行代码"4_1Color.py"代码文件为例

首先在"Files"区选中"4_1Color.py"文件并打开，然后点击做上交的运行按键![1407](./media/thonny-32.png)即可运行代码（注意：需要将Sengo1 AI视觉模块正确的连接到Pico开发板否则将会报错)，如果我们不想运行当前代码时我们只需要点击停止按键![1413](./media/thonny-38.png)。

![thonny-48](./media/thonny-48.png)

# 2.10 如何离线运行代码

我们也以"4_1Color.py"代码文件为例

首先点击"Raspberry Pi Pico"后方的![thonny-50](./media/thonny-50.png)然后点击"新建文件..."

![thonny-49](./media/thonny-49.png)

命名为`main.py`然后点击确认（注意：这个名称不能变更也不能输入错必须保证是`main.py`）

![thonny-51](./media/thonny-51.png)

创建文件成功

![thonny-52](./media/thonny-52.png)



打开"4_1Color.py"代码文件然后“Ctrl + A”全选 “Ctrl + C”复制 ，打开"main.py"代码文件 “Ctrl + V”粘贴

![thonny-53](./media/thonny-53.png)

点击保存按键进行保存

![thonny-54](./media/thonny-54.png)

保存成功，这样当Pico开发板重新上电后就会自动运行`main.py`中的代码（注意：保存时需要停止在线代码的运行，否则将魂保存不成功）

![thonny-55](./media/thonny-55.png)





