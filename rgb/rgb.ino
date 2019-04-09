int led1 = 12;

int led2 = 13;

int led3 = 14;

void setup()

{

  pinMode(led1,OUTPUT);

  pinMode(led2,OUTPUT);

  pinMode(led3,OUTPUT);

}

void setColor(int red,int green,int blue)

{

  analogWrite(led1,255-red);

  analogWrite(led2,255-green);

  analogWrite(led3,255-blue);

}

void loop()

{

  setColor(random(255),random(255),random(255));
  delay(500);       

}
