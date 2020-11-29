#include <Mkeyin.h> //调用按键函数库 
Mkeyin<2> Mkey; //按键控制芯片
//========所有IO功能口定义===========
const int Lmoto=5;//左震动电机
const int Rmoto=6;//右震动电机
const int buzzer=9;//蜂鸣器
const int SET=10;//串口无线模块AT调试使能接口
const int CS=11;//串口无线模块使能管脚
const int Bat=A0;//电池电压读取
const int Lxvr=A2;//左摇杆上下
const int Lyvr=A3;//左摇杆左右
const int UartSwitch=18;//无线模块连接USB转串口通讯切换开关
const int LED=19;//状态指示灯
const int Rxvr=A6;//右摇杆上下
const int Ryvr=A7;//右摇杆上下

byte UPdata[4]={0xaa,0x01,0x00,0xbb};     //按键上的十六进制数据串
byte DOWNdata[4]={0xaa,0x02,0x00,0xbb};   //按键下的十六进制数据串
byte LEETdata[4]={0xaa,0x03,0x00,0xbb};   //按键左的十六进制数据串
byte RIGHTdata[4]={0xaa,0x04,0x00,0xbb};  //按键右的十六进制数据串
byte SELECTdata[4]={0xaa,0x05,0x00,0xbb}; //按键设置（SELECT）的十六进制数据串
byte STARTdata[4]={0xaa,0x06,0x00,0xbb};  //按键开始（START）的十六进制数据串
byte L1data[4]={0xaa,0x07,0x00,0xbb};     //左按键L1的十六进制数据串
byte L2data[4]={0xaa,0x08,0x00,0xbb};     //左按键L2的十六进制数据串
byte L3data[4]={0xaa,0x09,0x00,0xbb};     //左按键L3的十六进制数据串
byte R1data[4]={0xaa,0x10,0x00,0xbb};     //右按键R1的十六进制数据串
byte R2data[4]={0xaa,0x11,0x00,0xbb};     //右按键R2的十六进制数据串
byte R3data[4]={0xaa,0x12,0x00,0xbb};     //右按键R3的十六进制数据串
byte JIAOdata[4]={0xaa,0x13,0x00,0xbb};   //三角按键的十六进制数据串
byte CAdata[4]={0xaa,0x14,0x00,0xbb};     //X按键的十六进制数据串
byte FANGdata[4]={0xaa,0x15,0x00,0xbb};   //正方形按键的十六进制数据串
byte QUANdata[4]={0xaa,0x16,0x00,0xbb};   //圆圈按键的十六进制数据串
byte LL1data[4]={0xaa,0x17,0x00,0xbb};    //左摇杆上下的十六进制数据串
byte LL2data[4]={0xaa,0x18,0x00,0xbb};    //左摇杆左右的十六进制数据串
byte RL1data[4]={0xaa,0x19,0x00,0xbb};    //右摇杆上下的十六进制数据串
byte RL2data[4]={0xaa,0x20,0x00,0xbb};    //右摇杆左右的十六进制数据串
byte Xdata[4]={0xaa,0xee,0x00,0xbb};      //按键放开使发送的十六进制数据串

long keyint=0;//按键读取存储变量
byte setwi;  //无线模块设置状态变量
byte Lset;  //左摇杆数据发送状态变量
byte Rset;  //左摇杆数据发送状态变量

int L1int=0;  //左摇杆上下数据存储变量
int L2int=0;  //左摇杆左右数据存储变量
int R1int=0;  //右摇杆上下数据存储变量
int R2int=0;  //右摇杆左右数据存储变量

byte rx_data[4];//串口读取到的数据存储变量
byte Lmotor1=0;//左电机开关标志

void setup() {
 pinMode(CS, OUTPUT);  //串口无线模块开关使能管脚，设置为输出控制。
 pinMode(SET, OUTPUT); //无线串口模块设置管脚，设置为输出控制。
 pinMode(LED, OUTPUT); //状态显示管脚，设置为输出控制。
 pinMode(UartSwitch, OUTPUT); //串口切换控制，设置为输出控制。
 Serial.begin(9600);//初始化串口，波特率设置为9600
 Mkey.begin();//初始化按键读取芯片
 digitalWrite(CS, LOW);//启动无线串口模块
 digitalWrite(SET, HIGH);//关闭无线串口模块设置
 digitalWrite(UartSwitch, LOW);//默认不切换串口
}
void loop() {  
  L1int = analogRead(Lxvr);//读取左摇杆上下数据
  L2int = analogRead(Lyvr);//读取左摇杆左右数据
  R1int = analogRead(Rxvr);//读取右摇杆上下数据
  R2int = analogRead(Ryvr);//读取右摇杆左右数据
  LL1data[2]= map(L1int, 0, 1023, 0, 255);//将左摇杆上下数据1023转换成255，并送给发送数据串里
  LL2data[2]= map(L2int, 0, 1023, 0, 255);//将左摇杆左右数据1023转换成255，并送给发送数据串里
  RL1data[2]= map(R1int, 0, 1023, 0, 255);//将右摇杆上下数据1023转换成255，并送给发送数据串里
  RL2data[2]= map(R2int, 0, 1023, 0, 255);//将右摇杆左右数据1023转换成255，并送给发送数据串里
  if (Mkey.update()) {  //判读按键是否有更新
   for (int i = 0; i < Mkey.getDataWidth(); i++);//如果任何按钮在最后一帧中已更改其状态，则返回true
   keyint=Mkey.getCurrent();//读取按键芯片并将读取的数据送个变量
  // Serial.println(keyint);
  }
   Bnkey();//调用按键按下和释放功能函数
   Bkeyred(); //调用按键函数
    if(Lset==1){ //判断左摇杆的开关变量
     Serial.write(LL1data,4); //发送左摇杆的数据串
     Serial.write(LL2data,4); //发送左摇杆的数据串
     delay(10);//延时10毫秒 
    }
    if(Rset==1){ //判断左摇杆的开关变量
     Serial.write(RL1data,4); //发送左摇杆的数据串
     Serial.write(RL2data,4); //发送左摇杆的数据串
     delay(10);//延时10毫秒 
    }
    if(keyint==16383){//组合按键（SELECT+START）设置无线模块串口切换串口
    setwi=!setwi;//无线模块设置状态变量
    if(setwi==1){//判断无线模块设置是否开启
    digitalWrite(LED, HIGH);//打开状态指示灯
    digitalWrite(SET, LOW);//无线模块设置为AT模式
    digitalWrite(UartSwitch, HIGH);//切换串口直接连接无线模块，慎重使用（一旦切换了是无法下载程序，需要切换回去再能再下载程序）
    delay(500); //延时500毫秒
    }
    else{
    digitalWrite(LED, LOW);//关闭状态指示灯
    digitalWrite(SET, HIGH);//关闭无线模块AT 模式，设置完无线模块记得重新关机再开机 
    digitalWrite(UartSwitch, LOW);//关闭串口切换，
    delay(500);//延时500毫秒
     }
   }
  delay(10);//延时10毫秒
}
void Bkeyred(){//按键函数
  switch(keyint){
    case 64511://判断如果是上按键按下
    Serial.write(UPdata,4);
    delay(100);//延时100毫秒
    break;
    case 61439://判断如果是下按键按下
    Serial.write(DOWNdata,4); 
    delay(100);//延时100毫秒
    break;
    case 63487://判断如果是左按键按下
    Serial.write(LEETdata,4); 
    delay(100);//延时100毫秒
    break;
    case 57343://判断如果是右按键按下
    Serial.write(RIGHTdata,4); 
    delay(100);//延时100毫秒
    break;

    case 65023://判断如果是L1按键按下
    Serial.write(L1data,4); 
    delay(100);//延时100毫秒
    break;
    case 65279://判断如果是L2按键按下
    Serial.write(L2data,4); 
    delay(100);//延时100毫秒
    break;
    case 65519://判断如果是R1按键按下
    Serial.write(R1data,4);
    delay(100);//延时100毫秒 
    break;
    case 65503://判断如果是R2按键按下
    Serial.write(R2data,4); 
    delay(100);//延时100毫秒
    break;
   }
 }
 
void Bnkey(){
   if(Mkey.released(7)){//判断按键是否按下
    Lset=!Lset;//按下将反转变量，用于设置左摇杆的数据发送开关
    }
    if(Mkey.released(6)){//判断按键是否按下
    Rset=!Rset;//按下将反转变量，用于设置左摇杆的数据发送开关
    }
 //===========三角按键=======================
   if(Mkey.released(3)){//判断按键是否按下
    Serial.write(JIAOdata,4);  
    }
   if(Mkey.pressed(3)){ //按键是否松开
    Serial.write(Xdata,4);//发送按键松开数据串
    }
//============================================
 //===========X按键=======================
   if(Mkey.released(1)){//判断按键是否按下
    Serial.write(CAdata,4);  
    }
   if(Mkey.pressed(1)){ //按键是否松开
    Serial.write(Xdata,4);//发送按键松开数据串
    }
//============================================
 //===========正方形按键=======================
   if(Mkey.released(0)){//判断按键是否按下
    Serial.write(FANGdata,4);  
    }
   if(Mkey.pressed(0)){ //按键是否松开
    Serial.write(Xdata,4);//发送按键松开数据串
    }
//============================================
 //===========圆圈按键=======================
   if(Mkey.released(2)){//判断按键是否按下
    Serial.write(QUANdata,4);  
    }
   if(Mkey.pressed(2)){ //按键是否松开
    Serial.write(Xdata,4);//发送按键松开数据串
    }
//============================================
 //===========SELECT按键=======================
   if(Mkey.released(14)){//判断按键是否按下
    Serial.write(SELECTdata,4);  
    }
   if(Mkey.pressed(14)){ //按键是否松开
    Serial.write(Xdata,4);//发送按键松开数据串
    }
//============================================
 //===========START按键=======================
   if(Mkey.released(15)){//判断按键是否按下
    Serial.write(STARTdata,4);  
    }
   if(Mkey.pressed(15)){ //按键是否松开
    Serial.write(Xdata,4);//发送按键松开数据串
    }
//============================================
  }
void RedUart(){
  Serial.readBytes(rx_data,4);
  delay(100);
  if( (rx_data[0] == 0xCC) && (rx_data[3] == 0xDD) )
  {
      if(rx_data[1] == 0x01){
       Lmotor1=1;
      }
  }
}
