//程序任务：PS2手柄数据采集和遥控主机发送数据。
#include <PS2X_lib.h>  //声明PS2X库文件
PS2X ps2x; // 定义ps2x为PS2X类变量
int PS_LY;//存储PS2手柄左摇杆Y轴数据
int PS_RX;//存储PS2手柄右摇杆X轴数据
int flag;//存储PS2手柄按键标识
//初始化
void setup(){
 Serial.begin(9600); //启动串行通信
 //初始化PS2与Arduino控制器接口
 ps2x.config_gamepad(13,11,10,12, true, true);  
}
//主程序
void loop(){   
   ps2x.read_gamepad();//读PS2数据   
   //如果按下PS2的绿色“三角”按键，标识为'A'
   if(ps2x.NewButtonState(PSB_GREEN))          
        { flag='A' ; }   
   //如果按下PS2的蓝色“X”按键，标识为'B'
    else if(ps2x.NewButtonState(PSB_BLUE))      
         { flag='B' ; } 
    //如果没有按键按下，标识为'C'
    else  if(ps2x.NewButtonState(PSB_PINK))      
         { flag='C' ; } 
    //如果没有按键按下，标识为'C'
    else  if(ps2x.NewButtonState(PSB_RED))      
         { flag='D' ; } 
    //如果没有按键按下，标识为'C'////////////////////////////////////////
    else  if(ps2x.NewButtonState(PSB_PAD_UP))      
         { flag='E' ; } 
    //如果没有按键按下，标识为'C'
    else  if(ps2x.NewButtonState(PSB_PAD_DOWN))      
         { flag='F' ; } 
    //如果没有按键按下，标识为'C'
    else  if(ps2x.NewButtonState(PSB_PAD_LEFT))      
         { flag='G' ; } 
    //如果没有按键按下，标识为'C'
    else  if(ps2x.NewButtonState(PSB_PAD_RIGHT))      
         { flag='H' ; } 
    //如果没有按键按下，标识为'C'
    else 
        { flag='X' ; } 
   //把PS2手柄左摇杆Y轴数据读到变量PS_LY
    PS_LY=ps2x.Analog(PSS_LY);
    //把PS2手柄右摇杆X轴数据读到变量PS_RX
    PS_RX=ps2x.Analog(PSS_LX);
   //把PS2手柄操作数据从遥控器发到乐高小车的接收端
   Serial.write(flag); 
   Serial.write(PS_LY);    
   Serial.write(PS_RX);  
   delay(100); //等待数据发送与接收 
}
