const int buzzer = 9; //蜂鸣器控制管脚数字9
void setup(){
  pinMode(buzzer, OUTPUT); // 将蜂鸣器引脚9设置为输出
}
void loop(){
  tone(buzzer, 1000); // 发送给蜂鸣器1KHz声音信号
  delay(1000);        // 延时1秒
  noTone(buzzer);     //停止发送
  delay(1000);        //延时1秒
}
