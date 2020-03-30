#include <PS2X_lib.h>
// Definitions PS2 Controller Pin Setup
#define ps2_att 10
#define ps2_cmd 11
#define ps2_dat 12
#define ps2_clk 13
#define pressures true
#define rumble true

PS2X ps2x;  // create PS2 Controller Class
int ps2_error = 0;

// Definitions L298N H Bridge to connect arduino input pins
#define in1 4 // Motor Right - Negative
#define in2 5 // Motor Right - Positive
#define in3 6 // Motor Left - Negative
#define in4 7 // Motor Left - Positive
#define enA 8 // Needs to be a PWM pin to be able to control motor speed
#define enB 9 // Needs to be a PWM pin to be able to control motor speed

void setup()
{
  Serial.begin(9600);
  // Set L298N to output pins
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  // PS2 Controller Setup
  do {
    ps2_error = ps2x.config_gamepad(ps2_clk, ps2_cmd, ps2_att, ps2_dat, pressures, rumble); //GamePad(clock, command, attention, data, Pressures?, Rumble?)
    if (ps2_error == 0) {
        Serial.print("PS2 Controller Conntected.");
        break;
    }
    else {
        delay(100);
    }
  } while (1);

}


void loop()
{
    ps2x.read_gamepad(false, 0);  //read ps2 controller and set large motor to spin at vibrate speed (read_gamepad(boolean motor1, byte motor2);)
    if(ps2x.ButtonPressed(PSB_PAD_UP)){
        // Forward
      digitalWrite(in1, HIGH); // Motor Right - clockwise
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW); // Motor Left - counter-clockwise
      digitalWrite(in4, HIGH);
      analogWrite(enA, 255); // Sets speed variable via PWM (0-255)
      analogWrite(enB, 255); // Sets speed variable via PWM (0-255)
    }
    if(ps2x.ButtonPressed(PSB_PAD_DOWN)){
        // Backward
      digitalWrite(in1, LOW); // Motor Right - counter-clockwise
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH); // Motor Left - clockwise
      digitalWrite(in4, LOW);
      analogWrite(enA, 255); // Sets speed variable via PWM (0-255)
      analogWrite(enB, 255); // Sets speed variable via PWM (0-255)
    }
    if(ps2x.ButtonPressed(PSB_PAD_LEFT)){
        // Turn Left
      digitalWrite(in1, LOW); // Motor Right - clockwise
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW); // Motor Left - clockwise
      digitalWrite(in4, HIGH);
      analogWrite(enA, 255); // Sets speed variable via PWM (0-255)
      analogWrite(enB, 255); // Sets speed variable via PWM (0-255)
    }
    if(ps2x.ButtonPressed(PSB_PAD_RIGHT)){
        // Turn Right
      digitalWrite(in1, HIGH); // Motor Right - counter-clockwise
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH); // Motor Left - counter-clockwise
      digitalWrite(in4, LOW);
      analogWrite(enA, 255); // Sets speed variable via PWM (0-255)
      analogWrite(enB, 255); // Sets speed variable via PWM (0-255)
    }
    if (!ps2x.Button(PSB_PAD_DOWN) && !ps2x.Button(PSB_PAD_UP) && !ps2x.Button(PSB_PAD_RIGHT) && !ps2x.Button(PSB_PAD_LEFT)) {
      // Stop
      digitalWrite(in1, LOW); // Motor Stop
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW); // Motor Stop
      digitalWrite(in4, LOW);
      analogWrite(enA, 0); // Sets speed variable via PWM (0-255)
      analogWrite(enB, 0); // Sets speed variable via PWM (0-255)

    }
    delay(10);

}