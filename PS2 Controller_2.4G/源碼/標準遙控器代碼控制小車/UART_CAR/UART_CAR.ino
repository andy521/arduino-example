int IN1 = 25;//定义控制IO口“D2”
int IN2 = 26;//定义控制IO口“D3”
int IN3 = 27;//定义控制IO口“D4”                         
int IN4 = 28;//定义控制IO口“D5”
int ENA = 2; //定义控制PWM输出口“D6”                        
int ENB = 3; //定义控制PWM输出口“D7”    
byte rx_data[4];
void setup(){ //初始运行设置
    pinMode(IN1, OUTPUT);//定义控制IO口为输出“D2”
    pinMode(IN2, OUTPUT);//定义控制IO口为输出“D3”
    pinMode(IN3, OUTPUT);//定义控制IO口为输出“D4”
    pinMode(IN4, OUTPUT);//定义控制IO口为输出“D5”
    Serial1.begin(9600);
} 
void loop(){  //主程序循环
  serialEvent();
}
void serialEvent(){ 
  unsigned int incomingByte = 0;   // for incoming serial data
  unsigned int i = 0;
  Serial1.readBytes(rx_data,4);
  delay(100);
  if( (rx_data[0] == 0xAA) && (rx_data[3] == 0xBB) )
  {
      if(rx_data[1] == 0x13){
       qian(255);
      }else
      if(rx_data[1] == 0x14){
       hou(255);
      }else
      if(rx_data[1] == 0x15){
       zuo(255);
      }else
      if(rx_data[1] == 0x16){
       you(255);
      }else
      if(rx_data[1] == 0xEE){
       ting(0);
      }else
      if(rx_data[1] == 0x03){
     // analogWrite(pwmled,rx_data[2]);
     }     
  }  
}

void qian(int xo)//定义前进带参数函数
  {      
  digitalWrite(IN1,HIGH); //定义D2输出高电平
  digitalWrite(IN2,LOW); //定义D3输出低电平
  digitalWrite(IN3,HIGH); //定义D4输出高电平
  digitalWrite(IN4,LOW); //定义D5输出低电平
  analogWrite(ENA,xo);//定义D6输出PWM
  analogWrite(ENB,xo);//定义D7输出PWM      
  }
  void hou(int xo)//定义后退带参数函数
  {      
  digitalWrite(IN1,LOW); //定义D2输出低电平
  digitalWrite(IN2,HIGH); //定义D3输出高电平
  digitalWrite(IN3,LOW); //定义D4输出低电平
  digitalWrite(IN4,HIGH); //定义D5输出高电平
  analogWrite(ENA,xo);//定义D6输出PWM
  analogWrite(ENB,xo);//定义D7输出PWM      
  }
  void zuo(int xo)//定义左转带参数函数
  {      
  digitalWrite(IN1,LOW); //定义D2输出低电平
  digitalWrite(IN2,HIGH); //定义D3输出高电平
  digitalWrite(IN3,HIGH); //定义D4输出高电平
  digitalWrite(IN4,LOW); //定义D5输出低电平
  analogWrite(ENA,xo);//定义D6输出PWM
  analogWrite(ENB,xo);//定义D7输出PWM      
  }
  void you(int xo)//定义右转带参数函数
  {      
  digitalWrite(IN1,HIGH); //定义D2输出高电平
  digitalWrite(IN2,LOW); //定义D3输出低电平
  digitalWrite(IN3,LOW); //定义D4输出低电平
  digitalWrite(IN4,HIGH); //定义D5输出高电平
  analogWrite(ENA,xo);//定义D6输出PWM
  analogWrite(ENB,xo);//定义D7输出PWM      
  }
  void ting(int xo)//定义停止带参数函数
  {      
  digitalWrite(IN1,LOW); //定义D2输出低电平
  digitalWrite(IN2,LOW); //定义D3输出低电平
  digitalWrite(IN3,LOW); //定义D4输出低电平
  digitalWrite(IN4,LOW); //定义D5输出低电平
  analogWrite(ENA,xo);//定义D6输出PWM
  analogWrite(ENB,xo);//定义D7输出PWM      
  }
