#include <MSA300.h>
#include <Wire.h>

acc_t data;
MSA300 msa;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  msa.begin();

  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  data = msa.getAcceleration();
  Serial.print(data.x);
  Serial.print(",");
  Serial.print(data.y);
  Serial.print(",");
  Serial.println(data.z);
  delay(10);
}
