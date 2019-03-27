/*
   BUZZER2
   使用无源蜂鸣器播放《葫芦娃》
*/

//对应音符和频率值
#define NOTE_D0 0
#define NOTE_D1 294
#define NOTE_D2 330
#define NOTE_D3 350
#define NOTE_D4 393
#define NOTE_D5 441
#define NOTE_D6 495
#define NOTE_D7 556

#define NOTE_DL1 147
#define NOTE_DL2 165
#define NOTE_DL3 175
#define NOTE_DL4 196
#define NOTE_DL5 221
#define NOTE_DL6 248
#define NOTE_DL7 278

#define NOTE_DH1 589
#define NOTE_DH2 661
#define NOTE_DH3 700
#define NOTE_DH4 786
#define NOTE_DH5 882
#define NOTE_DH6 990
#define NOTE_DH7 112

#define WHOLE 1
#define HALF 0.5
#define QUARTER 0.25
#define EIGHTH 0.25
#define SIXTEENTH 0.625

//整首曲子的音符部分
int tune[] =
{
  NOTE_DH1, NOTE_D6, NOTE_D5, NOTE_D6, NOTE_D0,
  NOTE_DH1, NOTE_D6, NOTE_D5, NOTE_DH1, NOTE_D6, NOTE_D0, NOTE_D6,
  NOTE_D6, NOTE_D6, NOTE_D5, NOTE_D6, NOTE_D0, NOTE_D6,
  NOTE_DH1, NOTE_D6, NOTE_D5, NOTE_DH1, NOTE_D6, NOTE_D0,

  NOTE_D1, NOTE_D1, NOTE_D3,
  NOTE_D1, NOTE_D1, NOTE_D3, NOTE_D0,
  NOTE_D6, NOTE_D6, NOTE_D6, NOTE_D5, NOTE_D6,
  NOTE_D5, NOTE_D1, NOTE_D3, NOTE_D0,
  NOTE_DH1, NOTE_D6, NOTE_D6, NOTE_D5, NOTE_D6,
  NOTE_D5, NOTE_D1, NOTE_D2, NOTE_D0,
  NOTE_D7, NOTE_D7, NOTE_D5, NOTE_D3,
  NOTE_D5,
  NOTE_DH1, NOTE_D0, NOTE_D6, NOTE_D6, NOTE_D5, NOTE_D5, NOTE_D6, NOTE_D6,
  NOTE_D0, NOTE_D5, NOTE_D1, NOTE_D3, NOTE_D0,
  NOTE_DH1, NOTE_D0, NOTE_D6, NOTE_D6, NOTE_D5, NOTE_D5, NOTE_D6, NOTE_D6,
  NOTE_D0, NOTE_D5, NOTE_D1, NOTE_D2, NOTE_D0,
  NOTE_D3, NOTE_D3, NOTE_D1, NOTE_DL6,
  NOTE_D1,
  NOTE_D3, NOTE_D5, NOTE_D6, NOTE_D6,
  NOTE_D3, NOTE_D5, NOTE_D6, NOTE_D6,
  NOTE_DH1, NOTE_D0, NOTE_D7, NOTE_D5,
  NOTE_D6,
};

//曲子的节拍，即音符持续时间
float duration[] =
{
  1, 1, 0.5, 0.5, 1,
  0.5, 0.5, 0.5, 0.5, 1, 0.5, 0.5,
  0.5, 1, 0.5, 1, 0.5, 0.5,
  0.5, 0.5, 0.5, 0.5, 1, 1,

  1, 1, 1 + 1,
  0.5, 1, 1 + 0.5, 1,
  1, 1, 0.5, 0.5, 1,
  0.5, 1, 1 + 0.5, 1,
  0.5, 0.5, 0.5, 0.5, 1 + 1,
  0.5, 1, 1 + 0.5, 1,
  1 + 1, 0.5, 0.5, 1,
  1 + 1 + 1 + 1,
  0.5, 0.5, 0.5 + 0.25, 0.25, 0.5 + 0.25, 0.25, 0.5 + 0.25, 0.25,
  0.5, 1, 0.5, 1, 1,
  0.5, 0.5, 0.5 + 0.25, 0.25, 0.5 + 0.25, 0.25, 0.5 + 0.25, 0.25,
  0.5, 1, 0.5, 1, 1,
  1 + 1, 0.5, 0.5, 1,
  1 + 1 + 1 + 1,
  0.5, 1, 0.5, 1 + 1,
  0.5, 1, 0.5, 1 + 1,
  1 + 1, 0.5, 0.5, 1,
  1 + 1 + 1 + 1
};

int length;
int tonePin = 8; 

void setup()
{
  pinMode(tonePin, OUTPUT); 
  length = sizeof(tune) / sizeof(tune[0]); 
}

void loop()
{
  for (int x = 0; x < length; x++) 
  {
    tone(tonePin, tune[x]); 
    delay(400 * duration[x]); 
    noTone(tonePin);
  }
  delay(5000);
}
