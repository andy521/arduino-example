#include <PS2X_lib.h> 
PS2X ps2x; // 定义ps2x为PS2X类变量
int PS_LY;//存储PS2手柄左摇杆Y轴数据
int PS_RX;//存储PS2手柄右摇杆X轴数据
int flag;//存储PS2手柄按键标识
int EN2 = 2;  
int EN3 = 3;
int EN4 = 4;
int EN5 = 5;                            
void qian(void)
        {        
          digitalWrite(EN2,LOW);
          digitalWrite(EN3,HIGH);
          digitalWrite(EN4,LOW);
          digitalWrite(EN5,HIGH);     
        }
void hou(void)
        {        
          digitalWrite(EN2,HIGH);
          digitalWrite(EN3,LOW);
          digitalWrite(EN4,HIGH);
          digitalWrite(EN5,LOW);            
        }
void you(void)
        {        
          digitalWrite(EN2,LOW);
          digitalWrite(EN3,HIGH);
          digitalWrite(EN4,HIGH);
          digitalWrite(EN5,LOW);     
        }        
void zuo(void)
        {        
          digitalWrite(EN2,HIGH);
          digitalWrite(EN3,LOW);
          digitalWrite(EN4,LOW);
          digitalWrite(EN5,HIGH);         
        }  
void ting(void)
        {
          digitalWrite(EN2,LOW);   
          digitalWrite(EN3,LOW);
          digitalWrite(EN4,LOW);   
          digitalWrite(EN5,LOW);       
        }        
void setup() 
{ 
   ps2x.config_gamepad(13,11,10,12, true, true);  
   pinMode(EN2, OUTPUT);
   pinMode(EN3, OUTPUT);
   pinMode(EN4, OUTPUT);
   pinMode(EN5, OUTPUT);  
    Serial.begin(9600);  
} 
void loop() 
{ 
      ps2x.read_gamepad();//读PS2数据  
      ps2x.read_gamepad(false, 255);
      if(ps2x.Button(PSB_PAD_UP))
     {
       qian();
       delay(20);
       ting();
     } 
     else  if(ps2x.Button(PSB_PAD_DOWN))      
         {
           hou();
         delay(20);
         ting();
         }
    else  if(ps2x.Button(PSB_PAD_LEFT))      
         {
           zuo();
         delay(20);
         ting();
         }
    else  if(ps2x.Button(PSB_PAD_RIGHT))      
         {
           you();
         delay(20);
         ting();
         }
}
