#include <PS2X_lib.h>  //for v1.6

PS2X ps2x; //创建PS2控制器类
//现在，该库不支持热插拔的控制器，这意味着
//你必须始终以重新启动后，你的Arduino CONECT的控制器，
//或呼叫config_gamepad的（引脚）后再次连接控制器。
int error = 0; 
byte type = 0;
byte vibrate = 0;

void setup(){
 Serial.begin(9600);

 //改变V1.6这里！ **************注意*************
  
 error = ps2x.config_gamepad(13,11,10,12, true, true); //设置引脚和设置：手柄（时钟，命令，注意，数据，压力，轰隆隆？）检查是否有错误
 
 if(error == 0){
   Serial.println("Found Controller, configured successful");//发现控制器，配置成功
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");//尝试了所有的按键，X将振动控制器，速度更快一些，因为你用力按下
  Serial.println("holding L1 or R1 will print out the analog stick values.");//控股L1或R1将打印出的类比摇杆值。
  Serial.println("Go to www.billporter.info for updates and to report bugs.");//转到www.billporter.info的更新和报告错误。
 }
   
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");//控制器，检查接线，请参阅readme.txt文件启用调试。访问www.billporter.info的故障排除提示
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");//控制器发现，但不接受命令。见readme.txt以启用调试。访问www.billporter.info故障排除提示
   
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");//控制器拒绝进入压力模式，可能不支持它
   
   //Serial.print的ps2x.Analog（1），（HEX）;
   
   type = ps2x.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");//未知的控制器类型
       break;
       case 1:
        Serial.println("DualShock Controller Found");//DUALSHOCK控制器
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");//GuitarHero控制器
       break;
     }
  
}

void loop(){
   /*您必须阅读游戏手柄获得新的价值
   游戏手柄和振动值设置
   ps2x.read_gamepad（开/关，从0到255之间的较大功率的电机实力的小马达）
   如果您不启用的隆隆声中，使用ps2x.read_gamepad（）;没有值
   
   你应该至少一次，第二次调用该
   */
 
 if(error == 1) //跳过循环，如果没有控制器发现
  return; 
  
 if(type == 2){ //吉他英雄控制器
   
   ps2x.read_gamepad();          //读控制器 
   
   if(ps2x.ButtonPressed(GREEN_FRET))
     Serial.println("Green Fret Pressed");//绿钢丝按下
   if(ps2x.ButtonPressed(RED_FRET))
     Serial.println("Red Fret Pressed");//红钢丝按下
   if(ps2x.ButtonPressed(YELLOW_FRET))
     Serial.println("Yellow Fret Pressed");//黄钢丝按下
   if(ps2x.ButtonPressed(BLUE_FRET))
     Serial.println("Blue Fret Pressed");//蓝钢丝按下
   if(ps2x.ButtonPressed(ORANGE_FRET))
     Serial.println("Orange Fret Pressed");//橙品按下
     

    if(ps2x.ButtonPressed(STAR_POWER))
     Serial.println("Star Power Command");//星力命令
    
    if(ps2x.Button(UP_STRUM))          //将真实的，只要按下按钮
     Serial.println("Up Strum");//上乱弹
    if(ps2x.Button(DOWN_STRUM))
     Serial.println("DOWN Strum");//DOWN乱弹
  
 
    if(ps2x.Button(PSB_START))                   //将真实的，只要按下按钮
         Serial.println("Start is being held");//开始举行的
    if(ps2x.Button(PSB_SELECT))                 
         Serial.println("Select is being held");//选择正在召开的

    
    if(ps2x.Button(ORANGE_FRET)) // 打印棒值如果为true
    {
        Serial.print("Wammy Bar Position:");
        Serial.println(ps2x.Analog(WHAMMY_BAR), DEC); 
    } 
 }

 else { //DualShock Controller
  
    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
    
    if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
         Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
         Serial.println("Select is being held");
         
         
     if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
       Serial.print("Up held this hard: ");
       Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
      }
      if(ps2x.Button(PSB_PAD_RIGHT)){
       Serial.print("Right held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
      }
      if(ps2x.Button(PSB_PAD_LEFT)){
       Serial.print("LEFT held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
      }
      if(ps2x.Button(PSB_PAD_DOWN)){
       Serial.print("DOWN held this hard: ");
     Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
      }   
  
    
      vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on 
                                              //how hard you press the blue (X) button    
    
    if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
    {
     
       
         
        if(ps2x.Button(PSB_L3))
         Serial.println("L3 pressed");
        if(ps2x.Button(PSB_R3))
         Serial.println("R3 pressed");
        if(ps2x.Button(PSB_L2))
         Serial.println("L2 pressed");
        if(ps2x.Button(PSB_R2))
         Serial.println("R2 pressed");
        if(ps2x.Button(PSB_GREEN))
         Serial.println("Triangle pressed");
         
    }   
         
    
    if(ps2x.ButtonPressed(PSB_RED))             //will be TRUE if button was JUST pressed
         Serial.println("Circle just pressed");
         
    if(ps2x.ButtonReleased(PSB_PINK))             //will be TRUE if button was JUST released
         Serial.println("Square just released");     
    
    if(ps2x.NewButtonState(PSB_BLUE))            //will be TRUE if button was JUST pressed OR released
         Serial.println("X just changed");    
    
    
    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
    {
        Serial.print("Stick Values:");
        Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_LX), DEC); 
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_RY), DEC); 
        Serial.print(",");
        Serial.println(ps2x.Analog(PSS_RX), DEC); 
    } 
    
    
 }
 
 
 delay(50);
     
}
