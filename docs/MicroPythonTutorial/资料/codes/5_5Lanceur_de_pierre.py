from machine import I2C,UART,Pin,PWM
from Sengo1 import *
import time

# 舵机控制引脚GPIO 3
servo_pin = Pin(3)
servo = PWM(servo_pin)

#蜂鸣器控制引脚GPIO12
buzzer = PWM(Pin(12))

# 设置PWM频率为50Hz（标准舵机频率）
servo.freq(50)

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
 
# 正常使用时，应由主控器发送指令控制Sengo1算法的开启与关闭，而非通过摇杆手动进行操作；
err = sengo1.VisionBegin(sengo1_vision_e.kVisionBody)
print("sengo1.VisionBegin(sengo1_vision_e.kVisionBody):0x%x"% err)


def tone(pin, frequency, duration):
    """Play the sound of the specified frequency"""
    if frequency > 0:
        pin.freq(frequency)
        pin.duty_u16(32768)  # 50% duty cycle
    time.sleep_ms(duration)
    pin.duty_u16(0)  # stop play tone

def no_tone(pin):
    """no tone"""
    pin.duty_u16(0)

def countdown(seconds):
    """countdown sound"""
    for i in range(seconds, 0, -1):
        # The ticking of the countdown
        tone(buzzer, 800, 100)
        time.sleep_ms(200)
        no_tone(buzzer)
        
        # Interval time
        time.sleep_ms(500)

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


while True:
  # Sengo不主动返回检测识别结果，需要主控板发送指令进行读取。读取的流程：首先读取识别结果的数量，接收到指令后，Sengo1会刷新结果数据，如果结果数量不为零，那么主控再发送指令读取结果的相关信息。请务必按此流程构建程序。
    obj_num = (sengo1.GetValue(sengo1_vision_e.kVisionBody, sentry_obj_info_e.kStatus))
    #判断是否检测到人体
    if obj_num:
        #投掷前倒计时声音，三声
        countdown(3)
        #投掷
        set_servo_angle(90)
        time.sleep(1)
        #缓慢的回落投掷臂
        for j in range(90,0,-1):
            set_servo_angle(j)
            time.sleep(0.01)
                    
