# 将AI视觉模块安装到KE3059小车上

使用KE3059小车的`搬运机器人`乐高造型，如下图：

![install-1](./media/install-1.png)

准备好AI视觉模块与乐高插销

![install-2](./media/install-2.png)

将乐高插销插到AI视觉模块排线接口两边的乐高孔中

![install-3](./media/install-3.png)

将AI视觉模块的连接线从小车乐高缝中穿过来以便于接线

![install-4](./media/install-4.png)

将AI连接线端子接入AI视觉模块，并将AI视觉模块通过乐高接到小车上，如图：

![install-5](./media/install-5.png)

最后将线连接到I2C接口即可，注意不要接错线：

|  AI视觉模块  | 小车接口 |
| :----------: | :------: |
| T/C (黄色线) |   SCL    |
| R/D (白色线) |   SDA    |
| V/+ (红色线) |    5V    |
| G/- (黑色线) |    G     |

![install-6](./media/install-6.png)