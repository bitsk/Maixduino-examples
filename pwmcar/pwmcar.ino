/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/
#include <L298N.h>
#define runSpeed   100

#define EN_L 6
#define IN1_L 10
#define IN2_L 8


#define EN_R 7
#define IN1_R 9
#define IN2_R 11

L298N motor_l(EN_L,IN1_L,IN2_L);
L298N motor_r(EN_R,IN1_R,IN2_R);
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  motor_l.setSpeed(runSpeed);
  motor_r.setSpeed(runSpeed);

}
void forward()
{
  motor_l.forward();
  motor_r.forward();
  Serial.println("forward");
}

void backward()
{
  motor_l.backward();
  motor_r.backward(); 
  Serial.println("backward");
}

void leftrotate()
{
  motor_l.backward();
  motor_r.forward();
  Serial.println("leftrotate");
}

void rightrotate()
{
  motor_l.forward();
  motor_r.backward();
  Serial.println("rightrotate");
}

void holdhere()
{
  motor_l.stop();
  motor_r.stop();
  Serial.println("holdhere");
}
// the loop function runs over and over again forever
void loop() {
  forward();
  delay(1000);
  leftrotate();
  delay(1000);
  holdhere();
  delay(2000); 
}
