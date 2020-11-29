#include <Mkeyin.h>
Mkeyin<2> Mkey; //按键控制芯片
//========所有IO功能口定义===========
const int LMotor=5;//左震动电机
const int RMotor=6;//右震动电机
const int buzzer=9;//蜂鸣器
const int SET=10;//串口无线模块AT调试使能接口
const int CS=11;//无线模块使能管脚
//const int Mosi=11;//无线模块MOSI数据口
//const int Miso=12;//无线模块MISO数据口
//const int Sck=13;//无线模块SCK数据口
const int Bat=A0;//电池电压读取
const int Offpower=15;//关机高电平有效
const int Lxvr=A2;//左摇杆上下
const int Lyvr=A3;//左摇杆左右
const int UartSwitch=18;//串口无线模块通讯切换
const int LED=19;//状态指示灯
const int Rxvr=A6;//右摇杆上下
const int Ryvr=A7;//右摇杆上下

long keyint=0;
byte setwi;
float Var;//计算公式得到的数值存储变量
float voltage;//实际电压存储变量

byte Lset;  //左摇杆数据发送状态变量
byte Rset;  //左摇杆数据发送状态变量

int L1int=0;  //左摇杆上下数据存储变量
int L2int=0;  //左摇杆左右数据存储变量
int R1int=0;  //右摇杆上下数据存储变量
int R2int=0;  //右摇杆左右数据存储变量

void setup() {
 Var=1023.0/(3.3/(10.0/(10.0+10.0)));//计算公式，并将计算好的数值送给变量
 pinMode(CS, OUTPUT);
 pinMode(SET, OUTPUT);
 pinMode(LED, OUTPUT);
 pinMode(UartSwitch, OUTPUT);
 Serial.begin(9600);
 Mkey.begin();
 digitalWrite(CS, LOW);
 digitalWrite(SET, HIGH);
 digitalWrite(UartSwitch, LOW);
}
void loop() {
 //  while (Serial.available() > 0) {
    if (Serial.read()=='A'){
      bibi();
      }
  //  }
  voltage = (float)analogRead(Bat)/Var;//读取电压并除以计算公式所得到的数值，然后将得到的实际电压送给实际电压存储变量
  L1int = analogRead(Lxvr);//读取左摇杆上下数据
  L2int = analogRead(Lyvr);//读取左摇杆左右数据
  R1int = analogRead(Rxvr);//读取右摇杆上下数据
  R2int = analogRead(Ryvr);//读取右摇杆左右数据
  L1int= map(L1int, 0, 1023, 0, 255);//将左摇杆上下数据1023转换成255，并送给发送数据串里
  L2int=map(L2int, 0, 1023, 0, 255);//将左摇杆左右数据1023转换成255，并送给发送数据串里
  R1int= map(R1int, 0, 1023, 0, 255);//将右摇杆上下数据1023转换成255，并送给发送数据串里
  R2int= map(R2int, 0, 1023, 0, 255);//将右摇杆左右数据1023转换成255，并送给发送数据串里
  if (Mkey.update()) {
    for (int i = 0; i < Mkey.getDataWidth(); i++);
   // Serial.println(shift.getCurrent());
   keyint=Mkey.getCurrent();
   Serial.println(keyint);
  }  
//======SELECT+START按键切换无线串口模块AT设置===============
  if(keyint==16383){
    setwi=!setwi;
    if(setwi==1){
    digitalWrite(LED, HIGH);
    digitalWrite(SET, LOW);
    digitalWrite(UartSwitch, HIGH);
    delay(500); 
    }
    else{
    digitalWrite(LED, LOW);
    digitalWrite(SET, HIGH);  
    digitalWrite(UartSwitch, LOW);
    delay(500);
     }
    }
//==============================================================
//==========L2按键控制振动电机==================================
   if(keyint==65279){
       analogWrite(LMotor, 150);//左震动电机震动级数150（0-255）
      }
      else{
        analogWrite(LMotor, 0);//左震动电机震动级数0，也就是停止震动（0-255）
      }  
//=================================================================
//==========R2按键控制振动电机==================================
   if(keyint==65503){
       analogWrite(RMotor, 150);//右震动电机震动级数150（0-255）   
      }
      else{
        analogWrite(RMotor, 0);//右震动电机震动级数0，也就是停止震动（0-255）
      }
//=================================================================
//==========L1按键控制蜂鸣器==================================
   if(keyint==65023){
       tone(buzzer, 1000); // 发送给蜂鸣器1KHz声音信号
      }
      else{
        noTone(buzzer);     //停止发送
      }
//=================================================================
//==========R1按键读取电压==================================
   if(keyint==65519){
      Serial.print("Volts: ");//串口输出“Volts: ”字符串
      Serial.print(voltage);//串口输出电池电压数值
      Serial.print("LX: ");//串口输出“LX: ”字符串
      Serial.print(L1int);//串口输出左摇杆X轴数据
      Serial.print("LY: ");//串口输出“LY: ”字符串
      Serial.print(L2int);//串口输出左摇杆Y轴数据
      Serial.print("RX: ");//串口输出“RX: ”字符串
      Serial.print(R1int);////串口输出右摇杆X轴数据
      Serial.print("RY: ");//串口输出“RY: ”字符串
      Serial.println(R2int);////串口输出右摇杆Y轴数据，并换行
      }
//=================================================================
  delay(10);
}
 
void bibi(){
  tone(buzzer, 800); // 发送给蜂鸣器800Hz声音信号
  delay(300);//延时200ms
  tone(buzzer, 500); // 发送给蜂鸣器500Hz声音信号
  delay(300);//延时200ms
  tone(buzzer, 1000); // 发送给蜂鸣器1KHz声音信号
  delay(300);//延时200ms
  noTone(buzzer); //停止发送
  }

