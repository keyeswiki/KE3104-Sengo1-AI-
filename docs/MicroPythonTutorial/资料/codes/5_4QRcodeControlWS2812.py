from machine import I2C,UART,Pin
from  Sengo1  import *
import time
from neopixel import myNeopixel

# 等待Sengo1完成操作系统的初始化。此等待时间不可去掉，避免出现Sengo1尚未初始化完毕主控器已经开发发送指令的情况
time.sleep(3)

# 选择UART或者I2C通讯模式，Sengo1出厂默认为I2C模式，短按模式按键可以切换
# 4种UART通讯模式：UART9600（标准协议指令），UART57600（标准协议指令），UART115200（标准协议指令），Simple9600（简单协议指令），
#########################################################################################################
# port = UART(2,rx=Pin(16),tx=Pin(17),baudrate=9600)
port = I2C(0,scl=Pin(21),sda=Pin(20),freq=400000)

# Sengo1通讯地址：0x60。如果I2C总线挂接多个设备，请避免出现地址冲突
sengo1 = Sengo1(0x60)

err = sengo1.begin(port)
print("sengo1.begin: 0x%x"% err)

#启动二维码识别算法
err = sengo1.VisionBegin(sengo1_vision_e.kVisionQrCode)
print("sengo1.VisionBegin(sengo1_vision_e.kVisionQrCode):0x%x"% err)

#Define the number of pin and LEDs connected to neopixel.
NUM_LEDS = 4
np = myNeopixel(NUM_LEDS, 13)
np.brightness(150) #brightness: 0 ~ 255

lastDetectionTime = 0

while True:
    # Sengo1不主动返回检测识别结果，需要主控板发送指令进行读取。读取的流程：首先读取识别结果的数量，接收到指令后，Sengo1会刷新结果数据，如果结果数量不为零，那么主控再发送指令读取结果的相关信息。请务必按此流程构建程序。
    obj_num = sengo1.GetValue(sengo1_vision_e.kVisionQrCode, sentry_obj_info_e.kStatus)
    # Sengo1只可识别并解码一个由不超过10个字符生成的二维码；所以返回结果非0时，只要获取并处理第1个结果的相关数据即可
    #获取运行时间
    currentMillis = time.ticks_ms()
    if obj_num:
        lastDetectionTime = currentMillis
        QRcodeStr = sengo1.GetQrCodeString()
        if QRcodeStr == "Red":
            np.fill(255,0,0)
            np.show()
        elif QRcodeStr == "Green":
            np.fill(0,255,0)
            np.show()
        elif QRcodeStr == "Blue":
            np.fill(0,0,255)
            np.show()
        elif QRcodeStr == "Black":
            np.fill(0,0,0)
            np.show()
        elif QRcodeStr == "White":
            np.fill(255,255,255)
            np.show()
    # 如果5秒内没有检测到二维码将会熄灭WS2812灯
    if currentMillis - lastDetectionTime >= 5000:
        lastDetectionTime = currentMillis
        np.fill(0,0,0)
        np.show()

