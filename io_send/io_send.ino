void setup() {
  // put your setup code here, to run once:
    pinMode(14,OUTPUT);//data
    pinMode(13,OUTPUT);//clk
}

void loop() {
  // put your main code here, to run repeatedly:
    for(int i = 0;i<255;i++)
    {
      shiftOut(14,13,LSBFIRST,i);
      printf(" send:%d \n",i);
      delay(500);
    }

}
