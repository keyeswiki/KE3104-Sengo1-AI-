#include <Arduino.h>
#include <Sentry.h>  // 引入Sentry机器视觉传感器库
#include <Servo.h>   //引入Servo舵机控制库

Servo servo;  //创建伺服对象以控制伺服系统

typedef Sengo1 Sengo;  // 为Sengo1类型创建别名Sengo，简化后续使用

// 通信方式选择（通过取消注释启用其中一种）
#define SENGO_I2C  // 当前启用I2C通信
// #define SENGO_UART   // 备用选项：UART串口通信

#ifdef SENGO_I2C
#include <Wire.h>  // I2C通信所需的库
#endif

#ifdef SENGO_UART
#include <SoftwareSerial.h>               // 软串口库（用于非硬件串口）
#define TX_PIN 11                         // 自定义TX引脚
#define RX_PIN 10                         // 自定义RX引脚
SoftwareSerial mySerial(RX_PIN, TX_PIN);  // 创建软串口对象
#endif

#define VISION_TYPE Sengo::kVisionColor  // 定义视觉算法类型（颜色识别）
Sengo sengo;                             // 创建Sengo传感器对象

//电机驱动引脚
#define ML 4
#define ML_PWM 6
#define MR 2
#define MR_PWM 5

void setup() {
  sentry_err_t err = SENTRY_OK;  // 错误状态变量

  Serial.begin(9600);  // 初始化串口用于调试输出
  Serial.println("Waiting for sengo initialize...");

  // 根据选择的通信方式初始化传感器
#ifdef SENGO_I2C
  Wire.begin();  // 初始化I2C总线
  // 持续尝试连接直到成功
  while (SENTRY_OK != sengo.begin(&Wire)) {
    yield();  // 在等待时允许其他任务运行
  }
#endif

#ifdef SENGO_UART
  mySerial.begin(9600);  // 初始化软串口
  while (SENTRY_OK != sengo.begin(&mySerial)) {
    yield();
  }
#endif

  sentry_object_t param;  // 参数结构体
  Serial.println("Sengo begin Success.");
  //设置识别框位置x坐标
  param.x_value = 50;
  //设置识别卡位置y坐标
  param.y_value = 50;
  //设置识别框宽
  param.width = 20;
  //设置识别框高
  param.height = 20;
  // 将参数写入传感器
  err = sengo.SetParam(VISION_TYPE, &param);
  //错误处理
  if (err) {
    Serial.print("sengo.SetParam ");
    if (err) {
      Serial.print("Error: 0x");
    } else {
      Serial.print("Success: 0x");
    }
    Serial.println(err, HEX);  // 打印16进制错误码
    for (;;)
      ;  // 死循环阻塞（需手动重启）
  }

  // 启动视觉识别算法
  err = sengo.VisionBegin(VISION_TYPE);
  Serial.print("sengo.VisionBegin(kVisionColor) ");
  if (err) {
    Serial.print("Error: 0x");
  } else {
    Serial.print("Success: 0x");
  }
  Serial.println(err, HEX);  // 输出初始化结果

  servo.attach(A0);
  servo.write(160);

  pinMode(ML, OUTPUT);      //设置左电机方向控制引脚为输出
  pinMode(ML_PWM, OUTPUT);  //设置左电机方向控制引脚为输出
  pinMode(MR, OUTPUT);      //设置左电机方向控制引脚为输出
  pinMode(MR_PWM, OUTPUT);  //设置左电机方向控制引脚为输出
}

void loop() {
  // 读取检测到的物体数量（kStatus表示获取状态）
  int obj_num = sengo.GetValue(VISION_TYPE, kStatus);

  if (obj_num > 0) {                              // 如果检测到物体
    int l = sengo.GetValue(VISION_TYPE, kLabel);  // 颜色标签
    //检测到红色块
    if (l == 3) {
      sorting(l);
      //检测到蓝色块
    } else if (l == 5) {
      sorting(l);
    } else car_stop();
  } else car_stop();
}


//色块分拣代码（目的减少重复代码量）
void sorting(int val) {
  //抓住色块
  servo.write(180);
  delay(500);
  //用if区分红色块和蓝色块的分拣方向
  if (val == 3) {
    //左转
    car_left();
  } else {
    //右转
    car_right();
  }
  delay(300);
  //前进
  car_forward();
  delay(300);
  car_stop();
  delay(300);
  //松开色块
  servo.write(160);
  delay(300);
  //后退
  car_back();
  delay(300);
  //用if区分红色块和蓝色块的返回方向
  if (val == 3) {
    //右转
    car_right();
  } else {
    //左转
    car_left();
  }
  delay(300);
}


//小车前进代码
void car_forward() {
  digitalWrite(ML, LOW);
  analogWrite(ML_PWM, 100);
  digitalWrite(MR, LOW);
  analogWrite(MR_PWM, 100);
}

//小车后退代码
void car_back() {
  digitalWrite(ML, HIGH);
  analogWrite(ML_PWM, 150);
  digitalWrite(MR, HIGH);
  analogWrite(MR_PWM, 150);
}

//小车左转代码
void car_left() {
  digitalWrite(ML, HIGH);
  analogWrite(ML_PWM, 155);
  digitalWrite(MR, LOW);
  analogWrite(MR_PWM, 100);
}

//小车右转代码
void car_right() {
  digitalWrite(ML, LOW);
  analogWrite(ML_PWM, 100);
  digitalWrite(MR, HIGH);
  analogWrite(MR_PWM, 155);
}

//小车停止代码
void car_stop() {
  digitalWrite(ML, LOW);
  analogWrite(ML_PWM, 0);
  digitalWrite(MR, LOW);
  analogWrite(MR_PWM, 0);
}