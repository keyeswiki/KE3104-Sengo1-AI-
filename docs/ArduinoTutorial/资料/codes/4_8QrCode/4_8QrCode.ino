// 引入 Arduino 核心库
#include <Arduino.h>
// 引入 Sentry 视觉传感器库
#include <Sentry.h>

// 定义 Sengo1 类型的别名（简化使用）
typedef Sengo1 Sengo;

// 选择通信方式（当前启用 I2C）
#define SENGO_I2C
// #define SENGO_UART  // UART 方式被注释掉

// 根据选择的通信方式包含相应库
#ifdef SENGO_I2C
#include <Wire.h>  // I2C 通信库
#endif
#ifdef SENGO_UART
#include <SoftwareSerial.h>
#define TX_PIN 11  // 软件串口发送引脚
#define RX_PIN 10  // 软件串口接收引脚
SoftwareSerial mySerial(RX_PIN, TX_PIN);  // 创建软件串口对象
#endif

// 设置视觉识别类型为二维码识别
#define VISION_TYPE Sengo::kVisionQrCode
Sengo sengo;  // 创建 Sentry 传感器对象

// 初始化设置（Arduino 启动时执行一次）
void setup() {
  sentry_err_t err = SENTRY_OK;  // 错误状态变量

  Serial.begin(9600);  // 初始化串口通信（用于调试输出）
  Serial.println("Waiting for sengo initialize...");

  // I2C 初始化流程
#ifdef SENGO_I2C
  Wire.begin();  // 初始化 I2C 总线
  // 循环等待传感器初始化成功
  while (SENTRY_OK != sengo.begin(&Wire)) { 
    yield();  // 在等待期间让出 CPU 控制权
  }
#endif  // SENGO_I2C

  // UART 初始化流程（当前未启用）
#ifdef SENGO_UART
  mySerial.begin(9600);
  while (SENTRY_OK != sengo.begin(&mySerial)) { 
    yield();
  }
#endif  // SENGO_UART

  Serial.println("Sengo begin Success.");
  
  // 启动二维码识别功能
  err = sengo.VisionBegin(VISION_TYPE);
  
  // 打印初始化结果
  Serial.print("sengo.VisionBegin(kVisionQrCode) ");
  if (err) {
    Serial.print("Error: 0x");
  } else {
    Serial.print("Success: 0x");
  }
  Serial.println(err, HEX);  // 十六进制输出错误码
}

// 主循环（重复执行）
void loop() {
  // 获取检测到的二维码数量（kStatus 表示查询状态）
  int obj_num = sengo.GetValue(VISION_TYPE, kStatus);
  
  if (obj_num) {  // 如果检测到二维码
    Serial.print("Totally ");
    Serial.print(obj_num);
    Serial.println(" objects");
    
    // 获取二维码的位置和尺寸信息
    int x = sengo.GetValue(VISION_TYPE, kXValue);      // 左上角 X 坐标
    int y = sengo.GetValue(VISION_TYPE, kYValue);      // 左上角 Y 坐标
    int w = sengo.GetValue(VISION_TYPE, kWidthValue);  // 二维码宽度
    int h = sengo.GetValue(VISION_TYPE, kHeightValue); // 二维码高度
    
    // 获取二维码内容（字符串）
    char* c = sengo.GetQrCodeValue();
    
    // 打印二维码详细信息
    Serial.print("  obj");
    Serial.print(": ");
    Serial.print("x=");
    Serial.print(x);
    Serial.print(",y=");
    Serial.print(y);
    Serial.print(",w=");
    Serial.print(w);
    Serial.print(",h=");
    Serial.print(h);
    Serial.print(",value=");
    Serial.println(c);  // 打印二维码内容
  }
}