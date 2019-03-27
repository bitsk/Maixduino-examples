#include <L298N.h>

#include <PS2X_lib.h>


//defination for connect pins with driver board

#define runSpeed   50

#define EN_L 8
#define IN1_L 10
#define IN2_L 11
#define EN_R 9
#define IN1_R 12
#define IN2_R 13


//defination for AFmotor
L298N motor_l(EN_L,IN1_L,IN2_L);
L298N motor_r(EN_R,IN1_R,IN2_R);


//defination for connect pins with PS2 receiver
#define PS2_DAT        18      
#define PS2_CMD        19  
#define PS2_SEL        20  
#define PS2_CLK        21  
// create PS2 Controller Class
PS2X ps2x;
//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false
int error = 0;
byte type = 0;
byte vibrate = 0; 

// Reset func 
void (* resetFunc) (void) = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  motor_l.setSpeed(runSpeed);
  motor_r.setSpeed(runSpeed);
  delay(500);

  //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  
  if(error == 0){
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
  if (pressures)
    Serial.println("true ");
  else
    Serial.println("false");
  Serial.print("rumble = ");
  if (rumble)
    Serial.println("true)");
  else
    Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }  
  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  
  type = ps2x.readType(); 
  switch(type) {
    case 0:
      Serial.println("Unknown Controller type found ");
      break;
    case 1:
      Serial.println("DualShock Controller found ");
      break;
    case 2:
      Serial.println("GuitarHero Controller found ");
      break;
  case 3:
      Serial.println("Wireless Sony DualShock Controller found ");
      break;
   }
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


void tank_movement(float X, float Y)
{
  //div 0 protect
  if((X < 0.1) && (X > -0.1))
  {
    if ((Y < 0.01) && (Y > -0.01))
    {
      holdhere();
    }
    else
    {
      (Y > 0) ? forward() : backward();
    }
  }
  else
  {
    float div = Y / X;
    if(X > 0)
    {
      //right side of the unit circle
      float theta = atan(div) / PI;
      //Serial1.print("theta:"); Serial1.println(theta);
      if((theta <= 0.125) && (theta > -0.125))
      {
        rightrotate();
      }
      else if((theta <= 0.5) && (theta > 0.375))
      {
        forward();
      }
      else if((theta <= -0.375) && (theta >= -0.5))
      {
        backward();
      }
      else
      {
        //abnormal protect
        holdhere();
      }
    }
    else
    {
      //left side of the unit circle, opposite of right side
      float theta = atan(div) / PI;
      //Serial1.print("theta:"); Serial1.println(theta);
      if ((theta <= 0.125) && (theta > -0.125))
      {
        leftrotate();
      }
      else if ((theta <= 0.5) && (theta > 0.375))
      {
        backward();
      }
      else if ((theta <= -0.375) && (theta >= -0.5))
      {
        forward();
      }
      else
      {
        //abnormal protect
        holdhere();
      }

    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(error == 1){ //skip loop if no controller found
       resetFunc();
   }
   //读取手柄输入信息
    ps2x.read_gamepad(false, vibrate);

    float x = (ps2x.Analog(PSS_LX)-127)/128.0f;
    float y = (ps2x.Analog(PSS_LY)-127)/128.0f;
    Serial.print("x:"); Serial.print(x);
    Serial.print("   y:"); Serial.println(y);
  
    tank_movement(x,y);
}
