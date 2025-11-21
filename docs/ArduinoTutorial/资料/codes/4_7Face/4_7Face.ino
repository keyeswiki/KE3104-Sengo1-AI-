#include <Arduino.h>          // Arduino核心库
#include <Sentry.h>           // Sentry机器视觉传感器库

// 为Sengo1类型创建别名"Sengo"，简化后续使用
typedef Sengo1 Sengo;

// 定义通信方式（当前启用I2C）
#define SENGO_I2C             
// #define SENGO_UART          // UART串口通信方案（已注释禁用）

// 根据选择的通信方式包含相应库
#ifdef SENGO_I2C
#include <Wire.h>             // I2C通信所需库
#endif

#ifdef SENGO_UART
#include <SoftwareSerial.h>   // 软串口库
#define TX_PIN 11             // 自定义TX引脚号
#define RX_PIN 10             // 自定义RX引脚号
SoftwareSerial mySerial(RX_PIN, TX_PIN);  // 创建软串口对象
#endif

// 定义视觉处理类型为人脸检测模式
#define VISION_TYPE Sengo::kVisionFace  

// 创建Sengo传感器对象实例
Sengo sengo;

void setup() {
  sentry_err_t err = SENTRY_OK;  // 定义错误状态变量，初始化为无错误

  Serial.begin(9600);            // 初始化串口通信，波特率9600
  Serial.println("Waiting for sengo initialize...");  // 打印初始化提示

// 根据选择的通信方式初始化传感器
#ifdef SENGO_I2C
  Wire.begin();                   // 初始化I2C总线
  // 循环尝试连接传感器，直到成功
  // yield()函数在等待期间允许ESP8266/ESP32处理后台任务
  while (SENTRY_OK != sengo.begin(&Wire)) { 
    yield();  
  }
#endif  // SENGO_I2C

#ifdef SENGO_UART
  mySerial.begin(9600);           // 初始化软串口，波特率9600
  // 循环尝试连接传感器，直到成功
  while (SENTRY_OK != sengo.begin(&mySerial)) { 
    yield();  
  }
#endif  // SENGO_UART

  Serial.println("Sengo begin Success.");  // 打印传感器初始化成功信息
  
  // 启动人脸检测功能
  err = sengo.VisionBegin(VISION_TYPE);
  
  // 打印人脸检测初始化结果
  Serial.print("sengo.VisionBegin(kVisionFace) ");
  if (err) {
    Serial.print("Error: 0x");    // 如果出错，打印错误前缀
  } else {
    Serial.print("Success: 0x");  // 如果成功，打印成功前缀
  }
  Serial.println(err, HEX);       // 以16进制格式打印错误代码
  
}

void loop() {
  // 获取检测到的人脸
  int face_count = sengo.GetValue(VISION_TYPE, kStatus);
  
  // 如果检测到至少一个人脸
  if (face_count > 0) {
    // 打印检测到的人脸总数
    Serial.print("Totally ");
    Serial.print(face_count);
    Serial.println(" faces detected");
    
    // 遍历所有检测到的人脸
    for (int i = 1; i <= face_count; ++i) {
      // 获取人脸在图像中的位置和尺寸信息
      int face_x = sengo.GetValue(VISION_TYPE, kXValue, i);      // 人脸区域中心X坐标
      int face_y = sengo.GetValue(VISION_TYPE, kYValue, i);      // 人脸区域中心Y坐标
      int face_width = sengo.GetValue(VISION_TYPE, kWidthValue, i);  // 人脸区域宽度
      int face_height = sengo.GetValue(VISION_TYPE, kHeightValue, i); // 人脸区域高度
      
      // 获取人脸标签（在人脸检测中通常表示人脸ID，用于追踪不同的人）
      int face_id = sengo.GetValue(VISION_TYPE, kLabel, i);
      
      // 打印人脸详细信息
      Serial.print("  Face #");
      Serial.print(i);
      Serial.print(": ");
      Serial.print("Position=(");
      Serial.print(face_x);
      Serial.print(",");
      Serial.print(face_y);
      Serial.print("), Size=");
      Serial.print(face_width);
      Serial.print("x");
      Serial.print(face_height);
      Serial.print(", ID=");
      Serial.println(face_id);
    }
  }
  
  delay(200);
}