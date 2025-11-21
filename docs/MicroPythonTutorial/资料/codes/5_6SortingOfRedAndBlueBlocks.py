from machine import I2C, Pin, PWM
import time
import random
from Sengo1 import *

#初始化PWM对象，控制引脚GPIO3
servo_pin = Pin(3)
servo = PWM(servo_pin)

#设置PWM频率为50HZ（标准舵机频率）
servo.freq(50)

# 初始化I2C (根据实际接线调整引脚)
port = I2C(0, scl=Pin(21), sda=Pin(20), freq=400000)  # 使用参考代码中的引脚

# 等待Sengo1初始化 (重要!)
time.sleep(2)

# 创建Sengo1对象
sengo1 = Sengo1()

# 开始传感器
err = sengo1.begin(port)
if err != SENTRY_OK:
    print(f"Initialization failed，error code:{err}")
else:
    print("Initialization succeeded")

#颜色识别功能配置
sengo1.SetParam(sengo1_vision_e.kVisionColor,[50, 50, 20, 20, 1])
time.sleep(0.1)

#Sengo1每次只能运行一种识别算法；
err = sengo1.VisionBegin(sengo1_vision_e.kVisionColor)
if err != SENTRY_OK:
    print(f"Starting algo Color failed，error code:{err}")
else:
    print("Starting algo Color succeeded")
    
    
# 定义舵机角度到占空比的转换函数
def set_servo_angle(angle):
    # 确保角度在0-270度范围内
    if angle < 0:
        angle = 0
    elif angle > 270:
        angle = 270
    
    # 将角度转换为占空比
    # 对于270度舵机，通常0.5ms脉冲对应0度，2.5ms脉冲对应270度
    min_duty = 1638  # 0.5ms的占空比值 (0.5/20 * 65535)
    max_duty = 8192  # 2.5ms的占空比值 (2.5/20 * 65535)
    
    # 计算对应角度的占空比
    duty = int(min_duty + (max_duty - min_duty) * angle / 270)
    servo.duty_u16(duty)
    
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
  pin2.duty_u16(40000)  
  pin3.value(1)
  pin4.duty_u16(40000)

# As a function of the car going left.
def car_left(): 
  pin1.value(0)
  pin2.duty_u16(10000)  
  pin3.value(1)
  pin4.duty_u16(45000)
# As a function of the car going right.
def car_right(): 
  pin1.value(1)
  pin2.duty_u16(45000)  
  pin3.value(0)
  pin4.duty_u16(10000)

# As a function of the car stopping.
def car_stop(): 
  pin1.value(0)
  pin2.duty_u16(0)  
  pin3.value(0)
  pin4.duty_u16(0)
    
#色块分拣代码
def sorting(val):
    #夹住色块
    set_servo_angle(270)
    time.sleep(1)
    #判断val，是0则是红色块，是1则是蓝色块
    if val == 0:
        #小车左转
        car_left()
    else :
        #小车右转
        car_right()
    time.sleep(0.3)
    #小车前进0.3秒
    car_forward()
    time.sleep(0.3)
    car_stop()
    time.sleep(0.3)
    #打开夹子放下色块
    set_servo_angle(240)
    time.sleep(0.5)
    #小车后退0.3秒
    car_back()
    time.sleep(0.3)
    #判断val，是0则是红色块，是1则是蓝色块
    if val == 0:
        #小车右转
        car_right()
    else :
        #小车左转
        car_left()
    time.sleep(0.3)

# 主检测循环
try:
    while True:
    # Sengo1不主动返回检测识别结果，需要主控板发送指令进行读取。读取的流程：首先读取识别结果的数量，接收到指令后，Sengo1会刷新结果数据，如果结果数量不为零，那么主控再发送指令读取结果的相关信息。请务必按此流程构建程序。
    # Sengo最多输出1个识别结果。
        obj_num = sengo1.GetValue(sengo1_vision_e.kVisionColor,sentry_obj_info_e.kStatus)
        if obj_num:
            # 获取颜色标签
            color_label = sengo1.GetValue(sengo1_vision_e.kVisionColor,sentry_obj_info_e.kLabel)
            #判断是否检测到红色块
            if color_label == color_label_e.kColorRed:
                sorting(0)
            #判断是否检测到蓝色块
            elif color_label == color_label_e.kColorBlue:
                sorting(1)
            else :
                car_stop()
        time.sleep(0.1)  # 短暂延时

except KeyboardInterrupt:
    sentry.VisionEnd(sengo1_vision_e.kVisionColor)
    # 程序被中断时关闭PWM
    servo.duty_u16(0)
    servo.deinit()
    print("The program has stopped")
