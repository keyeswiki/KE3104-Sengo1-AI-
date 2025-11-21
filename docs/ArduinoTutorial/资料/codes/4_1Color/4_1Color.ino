#include <Arduino.h>
#include <Sentry.h>  // 引入Sentry机器视觉传感器库

typedef Sengo1 Sengo;  // 为Sengo2类型创建别名Sengo，简化后续使用

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
}

void loop() {
  // 读取检测到的物体数量（kStatus表示获取状态）
  int obj_num = sengo.GetValue(VISION_TYPE, kStatus);

  if (obj_num > 0) {  // 如果检测到物体
    Serial.print("Totally ");
    Serial.print(obj_num);
    Serial.println(" objects");
    // 获取物体的标签（颜色ID）
    int label = sengo.GetValue(VISION_TYPE, kLabel, 1);
    Serial.print('|');
    Serial.print(label);    // 输出标签（如 |1|）
    Serial.println("|");  // 结束标记
  }
  delay(500);  // 延时500ms降低刷新率
}