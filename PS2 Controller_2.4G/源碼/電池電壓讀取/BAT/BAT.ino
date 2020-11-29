const int voltPin = A0; //电压读取管脚
float Var;//计算公式得到的数值存储变量
float voltage;//实际电压存储变量
void setup() { 
 Serial.begin(9600);//初始化串口，波特率设置为9600
 Var=1023.0/(3.3/(10.0/(10.0+10.0)));//计算公式，并将计算好的数值送给变量
 //需要更精确，可以用万用表，测量实际控制芯片的供电电压和电阻值，这样可以获得更精准的电压（123.4016887816647）
} 
void loop() { 
  voltage = (float)analogRead(voltPin)/Var;//读取电压并除以计算公式所得到的数值，然后将得到的实际电压送给实际电压存储变量
  Serial.print("Volts: ");//串口输出“Volts: ”字符串
  Serial.println(voltage);//串口输出电池电压数值，并且换行
  delay(500);//延时500ms
}

