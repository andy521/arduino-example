const int LMotor = 5; //PWM管脚-左震动电机控制
const int RMotor = 6; //PWM管脚-右震动电机控制
void setup() {
}
void loop() {
  analogWrite(LMotor, 150);//左震动电机震动级数150（0-255）
  delay(1000);//延时1S
  analogWrite(LMotor, 0);//左震动电机震动级数0，也就是停止震动（0-255）
  delay(1000);//延时1S
  analogWrite(RMotor, 150);//右震动电机震动级数150（0-255）
  delay(1000);//延时1S
  analogWrite(RMotor, 0);//右震动电机震动级数0，也就是停止震动（0-255）
  delay(1000);//延时1S
  analogWrite(LMotor, 255);//左震动电机震动级数255，最大震动级数（0-255）
  analogWrite(RMotor, 255);//右震动电机震动级数255，最大震动级数（0-255）
  delay(1000);//延时1S
  analogWrite(LMotor, 0);//左震动电机震动级数0，也就是停止震动（0-255）
  analogWrite(RMotor, 0);//右震动电机震动级数0，也就是停止震动（0-255）
  delay(1000);//延时1S
}
