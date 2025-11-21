from machine import I2C, Pin, PWM
import time
import random
from Sengo1 import *

# 等待Sengo1初始化 (重要!)
time.sleep(3)

# 初始化I2C (根据实际接线调整引脚)
port = I2C(0, scl=Pin(21), sda=Pin(20), freq=400000)  # 使用参考代码中的引脚

# 创建Sengo1对象
sengo1 = Sengo1(0x60)

# 开始传感器
err = sengo1.begin(port)
if err != SENTRY_OK:
    print(f"Initialization failed，error code:{err}")
else:
    print("Initialization succeeded")
    
sengo1.SetParam(sengo1_vision_e.kVisionBlob,[0, 0, 6, 8, color_label_e.kColorRed], 1)    #红色

# 等待新参数生效后的识别结果产出，该时间间隔不得低于该算法识别1帧所花费的时间，可以通过算法开启后，屏幕下方的帧率进行推算
time.sleep(0.1)

#正常使用时，应由主控板发送指令控制Sengo1的算法开启关闭，而不是通过Sengo1的摇杆进行操作；
err = sengo1.VisionBegin(sengo1_vision_e.kVisionBlob)
if err != SENTRY_OK:
    print(f"Starting algo Blob failed，error code:{err}")
else:
    print("Starting algo Blob succeeded")
    

# right wheel
pin1=Pin(14,Pin.OUT)
pin2=PWM(Pin(16))
pin2.freq(50)

# left wheel
pin3=Pin(15,Pin.OUT)
pin4=PWM(Pin(17))
pin4.freq(50)

# As a function of the car going forward.
def car_forward(): 
  pin1.value(0)
  pin2.duty_u16(20000) 
  pin3.value(0)
  pin4.duty_u16(20000)

# As a function of the car going backwards.
def car_back(): 
  pin1.value(1)
  pin2.duty_u16(30000)  
  pin3.value(1)
  pin4.duty_u16(30000)

# As a function of the car going left.
def car_left(): 
  pin1.value(0)
  pin2.duty_u16(5000)  
  pin3.value(1)
  pin4.duty_u16(45000)
# As a function of the car going right.
def car_right(): 
  pin1.value(1)
  pin2.duty_u16(45000)  
  pin3.value(0)
  pin4.duty_u16(5000)

# As a function of the car stopping.
def car_stop(): 
  pin1.value(0)
  pin2.duty_u16(0)  
  pin3.value(0)
  pin4.duty_u16(0)
    

# 主检测循环
try:
    while True:
        # 获取检测到的色块数量
        obj_num = sengo1.GetValue(sengo1_vision_e.kVisionBlob,sentry_obj_info_e.kStatus)
        
        if obj_num:
            # 获取位置与大小
            x = sengo1.GetValue(sengo1_vision_e.kVisionBlob,sentry_obj_info_e.kXValue,1)
            y = sengo1.GetValue(sengo1_vision_e.kVisionBlob,sentry_obj_info_e.kYValue,1)
            w = sengo1.GetValue(sengo1_vision_e.kVisionBlob,sentry_obj_info_e.kWidthValue,1)
            h = sengo1.GetValue(sengo1_vision_e.kVisionBlob,sentry_obj_info_e.kHeightValue,1)
            if y >= 80:
                #小车后退
                car_back()
            elif x <= 20:
                #小车左转
                car_left()
            elif x >= 80:
                #小车右转
                car_right()
            elif w <= 15 and h <= 15:
                #小车前进
                car_forward()
            elif w >= 70 and h >= 70:
                #小车后退
                car_back()
            else:
                car_stop()
        else: car_stop()
        time.sleep(0.1)  # 短暂延时

except KeyboardInterrupt:
    sengo1.VisionEnd(sengo1_vision_e.kVisionBlob)
    print("The program has stopped")


