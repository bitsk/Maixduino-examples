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

  int i,j;

  for(i=0,j=255;i<256;i++)

  {

    setColor(i,j,0);

    delay(4);

    j--;

  }

  delay(100);           //绿色向红色渐变

  for(i=0,j=255;i<256;i++)

  {

    setColor(j,0,i);

    delay(4);

    j--;

  }

  delay(100);           //红色向蓝色渐变

  for(i=0,j=255;i<256;i++)

  {

    setColor(0,i,j);

    delay(4);

    j--;

  }

  delay(100);          //蓝色向绿色渐变

}
