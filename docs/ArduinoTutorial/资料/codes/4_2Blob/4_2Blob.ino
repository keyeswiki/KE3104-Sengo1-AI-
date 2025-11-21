#include <Arduino.h>
#include <Sentry.h>  // 引入Sentry机器视觉传感器库

typedef Sengo1 Sengo;  // 为Sengo1类型创建别名Sengo，简化后续使用

// 通信方式选择（当前启用I2C）
#define SENGO_I2C
// #define SENGO_UART   // UART备用选项（已注释）

#ifdef SENGO_I2C
#include <Wire.h>       // I2C通信所需的库
#endif

#ifdef SENGO_UART
#include <SoftwareSerial.h>
#define TX_PIN 11       // 自定义TX引脚
#define RX_PIN 10       // 自定义RX引脚
SoftwareSerial mySerial(RX_PIN, TX_PIN);  // 创建软串口对象
#endif

#define VISION_TYPE Sengo::kVisionBlob  // 使用Blob检测（色块识别）
Sengo sengo;  // 创建Sengo传感器对象

// Blob检测结果标签的文本描述
const char* blob_classes[] = {
  "UNKNOWN", "BLACK", "WHITE", "RED", "GREEN", "BLUE", "YELLOW"
};

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

  // ============== Blob检测参数配置 ==============
  sengo.SetParamNum(VISION_TYPE, 1);  // 设置检测1种颜色的色块，Sengo1一次只能检测一种颜色
  
  sentry_object_t param = {0};  // 初始化参数结构体
  
  /* 设置色块最小检测尺寸（像素）*/
  param.width = 5;    // 最小宽度5像素
  param.height = 5;   // 最小高度5像素
  
  /* 配置色块（红色）*/
  param.label = Sengo::kColorRed;  // 设置颜色标签为红色
  err = sengo.SetParam(VISION_TYPE, &param);  // 应用到参数
  
  // 输出配置结果
  Serial.print("sengo.SetParam[");
  Serial.print(blob_classes[param.label]);  // 打印颜色名称
  if (err) {
    Serial.print("] Error: 0x");
  } else {
    Serial.print("] Success: 0x");
  }
  Serial.println(err, HEX);  // 输出16进制状态码

  // 启动Blob视觉识别
  err = sengo.VisionBegin(VISION_TYPE);
  Serial.print("sengo.VisionBegin(kVisionBlob) ");
  if (err) {
    Serial.print("Error: 0x");
  } else {
    Serial.print("Success: 0x");
  }
  Serial.println(err, HEX);
}

void loop() {
  // 读取检测到的物体总数
  int obj_num = sengo.GetValue(VISION_TYPE, kStatus);
  
  if (obj_num > 0) {  // 如果检测到物体
    Serial.print("Totally ");
    Serial.print(obj_num);
    Serial.println(" objects");
    
    // 遍历所有检测到的色块
    for (int i = 1; i <= obj_num; ++i) {
      // 获取色块的位置和尺寸信息
      int x = sengo.GetValue(VISION_TYPE, kXValue, i);      // X坐标
      int y = sengo.GetValue(VISION_TYPE, kYValue, i);      // Y坐标
      int w = sengo.GetValue(VISION_TYPE, kWidthValue, i);  // 宽度
      int h = sengo.GetValue(VISION_TYPE, kHeightValue, i); // 高度
      int l = sengo.GetValue(VISION_TYPE, kLabel, i);      // 颜色标签
      
      // 格式化输出检测结果
      Serial.print("  obj");
      Serial.print(i);
      Serial.print(": ");
      Serial.print("x=");
      Serial.print(x);
      Serial.print(",y=");
      Serial.print(y);
      Serial.print(",w=");
      Serial.print(w);
      Serial.print(",h=");
      Serial.print(h);
      Serial.print(",label=");
      Serial.println(blob_classes[l]);  // 输出颜色名称而非数字
    }
  }
}