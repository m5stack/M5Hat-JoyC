#include <M5StickC.h>
// #include <M5StickCPlus.h>
#include "M5_JoyC.h"

TFT_eSprite canvas = TFT_eSprite(&M5.Lcd);

M5_JOYC joyc;
void setup() {
  M5.begin();
  M5.Lcd.setRotation(1);
  canvas.createSprite(160, 80);
  canvas.setTextColor(ORANGE);
  joyc.begin();
}

char info[50];

void loop(){
  joyc.update();
  canvas.fillSprite(BLACK);
  canvas.setCursor(0,10);
  canvas.println("JoyC TEST");
  sprintf(info, "X0: %d Y0: %d", joyc.x0, joyc.y0);
  canvas.println(info);
  Serial.println(info);
  sprintf(info, "X1: %d Y1: %d", joyc.x1, joyc.y1);
  canvas.println(info);
  Serial.println(info);
  sprintf(info, "Angle0: %d Angle1: %d",joyc.angle0, joyc.angle1);
  canvas.println(info);
  Serial.println(info);
  sprintf(info, "D0: %d D1: %d", joyc.distance0, joyc.distance1);
  canvas.println(info);
  Serial.println(info);
  sprintf(info, "Btn0: %d Btn1: %d", joyc.btn0, joyc.btn1);
  canvas.println(info);
  Serial.println(info);
  canvas.pushSprite(10, 0);
  if(joyc.btn0 && joyc.btn1){
    joyc.setLEDColor(0x00ffe8);
  }else if(joyc.btn0){
    joyc.setLEDColor(0xff0000);
  }else if(joyc.btn1){
    joyc.setLEDColor(0x0000ff);
  }else {
    joyc.setLEDColor(0x00ff00);
  }
}
