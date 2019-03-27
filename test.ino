
#include <stdio.h>
#include "bsp.h"
void setup() {
  // put your setup code here, to run once:
  printf("In setup func.\n.");
}

void loop() {
  // put your main code here, to run repeatedly:
  printf("In loop func.\n");
  msleep(1000);
  
}
