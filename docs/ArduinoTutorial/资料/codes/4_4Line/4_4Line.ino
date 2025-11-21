#include <Arduino.h>
#include <Sentry.h>  // 引入Sentry机器视觉库

typedef Sengo1 Sengo;  // 为Sengo1类型创建别名Sengo

// 通信方式选择（当前启用I2C）
#define SENGO_I2C
// #define SENGO_UART  // UART备用选项（已注释）

#ifdef SENGO_I2C
#include <Wire.h>  // I2C通信所需库
#endif

#ifdef SENGO_UART
#include <SoftwareSerial.h>
#define TX_PIN 11  // 自定义TX引脚
#define RX_PIN 10  // 自定义RX引脚
SoftwareSerial mySerial(RX_PIN, TX_PIN);  // 创建软串口对象
#endif

#define VISION_TYPE Sengo::kVisionLine  // 使用线条检测模式
Sengo sengo;  // 创建Sengo传感器对象

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
  mySerial.begin(9600);
  while (SENTRY_OK != sengo.begin(&mySerial)) { 
    yield();
  }
#endif

  Serial.println("Sengo begin Success.");  
  // 启动线条视觉识别
  err = sengo.VisionBegin(VISION_TYPE);
  Serial.print("sengo.VisionBegin(kVisionLine) ");
  if (err) {
    Serial.print("Error: 0x");
  } else {
    Serial.print("Success: 0x");
  }
  Serial.println(err, HEX);
}

void loop() {
  // 读取检测到的线条
  int obj_num = sengo.GetValue(VISION_TYPE, kStatus);
  
  if (obj_num > 0) {  // 如果检测到线条
    Serial.print("Totally ");
    Serial.print(obj_num);
    Serial.println(" lines detected");
    
    // 遍历所有检测到的线条
    for (int i = 1; i <= obj_num; ++i) {
      // 获取线条端点坐标
      int x1 = sengo.GetValue(VISION_TYPE, kXValue, i);      // 起点X坐标
      int y1 = sengo.GetValue(VISION_TYPE, kYValue, i);      // 起点Y坐标
      int x2 = sengo.GetValue(VISION_TYPE, kWidthValue, i);  // 终点X坐标
      int y2 = sengo.GetValue(VISION_TYPE, kHeightValue, i);  // 终点Y坐标
      
      // 获取线条角度（0-180度）
      int degree = sengo.GetValue(VISION_TYPE, kLabel, i);
      
      // 格式化输出检测结果
      Serial.print("  Line #");
      Serial.print(i);
      Serial.print(": ");
      Serial.print("Start=(");
      Serial.print(x1);
      Serial.print(",");
      Serial.print(y1);
      Serial.print("), End=(");
      Serial.print(x2);
      Serial.print(",");
      Serial.print(y2);
      Serial.print("), Angle=");
      Serial.print(degree);
      Serial.println("°");
    }
  }
  
  delay(100);  // 适当延时，降低刷新率
}