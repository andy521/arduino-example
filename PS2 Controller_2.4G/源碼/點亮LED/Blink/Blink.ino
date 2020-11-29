void setup() {
  pinMode(13, OUTPUT);//设定数字13管脚为输出
}
void loop() {
  digitalWrite(13, HIGH); //数字13管脚输出高电平
  delay(1000); //延时1000ms                      
  digitalWrite(13, LOW);//数字13管脚输出低电平
  delay(1000); //延时1000ms
}
