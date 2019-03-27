void setup() {
  // put your setup code here, to run once:
  pinMode(14,INPUT_PULLUP);//data
  pinMode(13,INPUT_PULLUP);//clk
}

void loop() {
  // put your main code here, to run repeatedly:
   int value = shiftIn(14,13,LSBFIRST);
   printf("rec : %d\n",value);
   delay(500);
}
