from machine import I2C,UART,Pin,PWM
from Sengo1 import *
import time

# 等待Sengo1完成操作系统的初始化。此等待时间不可去掉，避免出现Sengo1尚未初始化完毕主控器已经开发发送指令的情况
time.sleep(3)

# 选择UART或者I2C通讯模式，Sengo1出厂默认为I2C模式，短按模式按键可以切换
# 4种UART通讯模式：UART9600（标准协议指令），UART57600（标准协议指令），UART115200（标准协议指令），Simple9600（简单协议指令），
#########################################################################################################
# port = UART(2,rx=Pin(16),tx=Pin(17),baudrate=9600)
port = I2C(0,scl=Pin(21),sda=Pin(20 ),freq=400000)

# Sengo1通讯地址：0x60。如果I2C总线挂接多个设备，请避免出现地址冲突
sengo1 = Sengo1(0x60)

err = sengo1.begin(port)
print("sengo1.begin: 0x%x"% err)
 
#开启卡片识别算法
err = sengo1.VisionBegin(sengo1_vision_e.kVisionCard)
print("sengo1.VisionBegin(sengo1_vision_e.kVisionCard):0x%x"% err)

# right wheel
pin1=Pin(14,Pin.OUT)
pin2=PWM(Pin(16))
pin2.freq(50)

# left wheel
pin3=Pin(15,Pin.OUT)
pin4=PWM(Pin(17))
pin4.freq(50)

#速度变量
right_speed = 30000
left_speed = 30000

# As a function of the car going forward.
def car_forward(): 
  pin1.value(0)
  pin2.duty_u16(right_speed) 
  pin3.value(0)
  pin4.duty_u16(left_speed)

# As a function of the car going backwards.
def car_back(): 
  pin1.value(1)
  pin2.duty_u16(50000 - right_speed)  
  pin3.value(1)
  pin4.duty_u16(50000 - left_speed)

# As a function of the car going left.
def car_left(): 
  pin1.value(0)
  pin2.duty_u16(25000)  
  pin3.value(1)
  pin4.duty_u16(25000)
# As a function of the car going right.
def car_right(): 
  pin1.value(1)
  pin2.duty_u16(25000)  
  pin3.value(0)
  pin4.duty_u16(25000)

# As a function of the car stopping.
def car_stop(): 
  pin1.value(0)
  pin2.duty_u16(0)  
  pin3.value(0)
  pin4.duty_u16(0)

while True:
    # Sengo1不主动返回检测识别结果，需要主控板发送指令进行读取。读取的流程：首先读取识别结果的数量，接收到指令后，Sengo1会刷新结果数据，如果结果数量不为零，那么主控再发送指令读取结果的相关信息。请务必按此流程构建程序。
    obj_num = (sengo1.GetValue(sengo1_vision_e.kVisionCard, sentry_obj_info_e.kStatus))
    #判断避免识别到多张卡片时出现混乱
    if obj_num == 1:
        for i in range(1,obj_num+1):
            #获取卡片标签值
            Tags = sengo1.GetValue(sengo1_vision_e.kVisionCard,sentry_obj_info_e.kLabel,i)
            #识别到前进卡片
            if Tags == 1:
                #小车前进
                car_forward()
            #识别到左转卡片
            elif Tags == 2:
                #小车左转
                car_left()
            #识别到右转卡片
            elif Tags == 3:
                #小车右转
                car_right()
            #识别到后退卡片
            elif Tags == 4:
                #小车后退
                car_back()
            #识别到停止卡片
            elif Tags == 5:
                #小车停止
                car_stop()
    #没有识别到卡片小车停止
    else : car_stop()
    time.sleep(0.2)    
