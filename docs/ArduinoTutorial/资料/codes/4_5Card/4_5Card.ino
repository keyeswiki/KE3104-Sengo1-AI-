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

// 定义视觉处理类型为卡片识别模式
#define VISION_TYPE Sengo::kVisionCard  

// 创建Sengo传感器对象实例
Sengo sengo;

// 卡片类型名称映射表（索引对应卡片标签值）
const char* card_classes[] = {
  "unknown",      // 0: 未知卡片类型
  "forward",      // 1: 前进卡片
  "left",         // 2: 左转卡片
  "right",        // 3: 右转卡片
  "turn_around",  // 4: 掉头卡片
  "park",         // 5: 停车卡片
  // 注意：数组大小应与实际卡片类型数量匹配
};

void setup() {
  sentry_err_t err = SENTRY_OK;  // 定义错误状态变量，初始化为无错误

  Serial.begin(9600);            // 初始化串口通信，波特率9600
  Serial.println("Waiting for sengo initialize...");  // 打印初始化提示

// 根据选择的通信方式初始化传感器
#ifdef SENGO_I2C
  Wire.begin();                   // 初始化I2C总线
  // 循环尝试连接传感器，直到成功
  while (SENTRY_OK != sengo.begin(&Wire)) { 
    yield();  // 在等待连接期间允许系统处理其他任务
  }
#endif  // SENGO_I2C

#ifdef SENGO_UART
  mySerial.begin(9600);           // 初始化软串口，波特率9600
  // 循环尝试连接传感器，直到成功
  while (SENTRY_OK != sengo.begin(&mySerial)) { 
    yield();  // 在等待连接期间允许系统处理其他任务
  }
#endif  // SENGO_UART

  Serial.println("Sengo begin Success.");  // 打印传感器初始化成功信息
  
  // 启动卡片视觉识别功能
  err = sengo.VisionBegin(VISION_TYPE);
  
  // 打印视觉识别初始化结果
  Serial.print("sengo.VisionBegin(kVisionCard) ");
  if (err) {
    Serial.print("Error: 0x");    // 如果出错，打印错误前缀
  } else {
    Serial.print("Success: 0x");  // 如果成功，打印成功前缀
  }
  Serial.println(err, HEX);       // 以16进制格式打印错误代码
}

void loop() {
  // 获取是否检测到的卡片
  int obj_num = sengo.GetValue(VISION_TYPE, kStatus);
  
  // 如果检测到至少一张卡片
  if (obj_num > 0) {
    // 打印检测到的卡片数
    Serial.print("Totally ");
    Serial.print(obj_num);
    Serial.println(" cards detected");
    
    // 遍历所有检测到的卡片
    for (int i = 1; i <= obj_num; ++i) {
      // 获取卡片在图像中的位置和尺寸信息
      int x = sengo.GetValue(VISION_TYPE, kXValue, i);      // 卡片中心X坐标
      int y = sengo.GetValue(VISION_TYPE, kYValue, i);      // 卡片中心Y坐标
      int w = sengo.GetValue(VISION_TYPE, kWidthValue, i);  // 卡片宽度
      int h = sengo.GetValue(VISION_TYPE, kHeightValue, i); // 卡片高度
      
      // 获取卡片类型标签（对应card_classes数组索引）
      int card_type = sengo.GetValue(VISION_TYPE, kLabel, i);
      
      // 确保卡片类型在有效范围内（防止数组越界）
      if (card_type < 0) card_type = 0;
      if (card_type >= sizeof(card_classes)/sizeof(card_classes[0])) 
        card_type = 0;
      
      // 打印卡片详细信息
      Serial.print("  Card #");
      Serial.print(i);
      Serial.print(": ");
      Serial.print("Position=(");
      Serial.print(x);
      Serial.print(",");
      Serial.print(y);
      Serial.print("), Size=");
      Serial.print(w);
      Serial.print("x");
      Serial.print(h);
      Serial.print(", Type=");
      Serial.println(card_classes[card_type]);  // 使用映射表获取类型名称
    }
  }
  
  delay(200);
}