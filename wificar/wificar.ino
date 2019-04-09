#include <L298N.h>
#define runSpeed   100

#define EN_L 41
#define IN1_L 43
#define IN2_L 45


#define EN_R 40
#define IN1_R 42
#define IN2_R 44

 
#define LEFT "3" //左转编码
#define RIGHT "4"//右转编码
#define GO "1"//前进编码
#define BACK "2"//后退编码
#define STOP "0"//停止编码

L298N motor_l(EN_L,IN1_L,IN2_L);
L298N motor_r(EN_R,IN1_R,IN2_R);
 
void setup() {
  motor_l.setSpeed(runSpeed);
  motor_r.setSpeed(runSpeed);
  // set the data rate for the SoftwareSerial port
  Serial1.begin(115200);
  Serial.begin(9600);
  delay(1000);
  //开启多连接模式命令
  Serial1.println("AT+CIPMUX=1");
  //开启服务器模式    8080为端口号，手机连接时会用到
  delay(2000);
  Serial1.println("AT+CIPSERVER=1,8080");
  delay(3000);
  while(Serial.read() >= 0){}
  while(Serial1.read() >= 0){}
  initCar();
  Serial.println("wificar init");
}
 
void loop() {
    char buf[100];
    int leng = ReceiveWifiMessage(buf);
 
    if(leng>0){
      if(strcmp(buf, GO) == 0){
        Serial.println("go");
         //前进
         go();
      }else if(strcmp(buf, BACK) == 0){
        Serial.println("back");
         //后退
         back();
      }else if(strcmp(buf, LEFT) == 0){
         //左转
         Serial.println("left");
         turnLeft();
      }else if(strcmp(buf, RIGHT) == 0){
        //右转
        Serial.println("right");
        turnRight();
      }else if(strcmp(buf, STOP) == 0){
        //停车
        Serial.println("stop");
        stopCar();
      }
    }
}
 
void initCar(){
  //默认全是低电平 停止状态
  motor_l.setSpeed(runSpeed);
  motor_r.setSpeed(runSpeed);
}
 
/**
* 左转
*/
void turnLeft(){
  motor_l.backward();
  motor_r.forward();
  Serial.println("leftrotate");
}
 
/**
* 右转
*/
void turnRight(){
  motor_l.forward();
  motor_r.backward();
  Serial.println("rightrotate");
}
 
/**
* 前进
*/
void go(){
  motor_l.forward();
  motor_r.forward();
  Serial.println("forward");
}
 
/**
* 倒车
*/
void back(){
  motor_l.backward();
  motor_r.backward(); 
  Serial.println("backward");
}
 
/**
* 停车
*/
void stopCar(){
  8motor_l.stop();
  motor_r.stop();
  Serial.println("holdhere");
}
 
/**
* 读取串口缓冲区里面的数据
*/
int ReceiveWifiMessage(char *buf){
  //+IPD,<len>:<data>
  //+IPD,<id>,<len>:<data>
  String data = "";
  if (Serial1.available()>0){
    unsigned long start;
    start = millis();
    char c0 = Serial1.read();
    if (c0 == '+')
    {
      while (millis()-start<100) 
      {
        if (Serial1.available()>0)
        {
          char c = Serial1.read();
          data += c;
        }
        if (data.indexOf("\nOK")!=-1)
        {
          break;
        }
      }
 
      int sLen = strlen(data.c_str());
      int i,j;
      for (i = 0; i <= sLen; i++){
        if (data[i] == ':'){
          break;
        }
      }
      //判断是否存在id
      boolean found = false;
      for (j = 4; j <= i; j++){
        if (data[j] == ','){
          found = true;
          break;
        }
      }
      int iSize;
      if(found ==true){
        //+IPD,<id>,<len>:<data>
          String _size = data.substring(j+1, i);
          iSize = _size.toInt();
          String str = data.substring(i+1, i+1+iSize);
          strcpy(buf, str.c_str());     
      }else{
        //+IPD,<len>:<data>     
          String _size = data.substring(4, i);
          iSize = _size.toInt();
          String str = data.substring(i+1, i+1+iSize);
          strcpy(buf, str.c_str());
      }
      return iSize;
    }else{
      while(Serial1.read() >= 0){}  
    }
  }
  return 0;
}
