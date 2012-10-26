#include <Wire.h>
#include "nunchuck_funcs.h"

boolean pattern[4][16];
unsigned long lastPatternTime = 0;

boolean zPressed = false;

boolean forwards = true;

boolean drawPattern(int frameTime, int howManyFrames, void (*drawFunction)(void));

void setup()
{
  for (int pin = 0; pin < 20; pin++)
    pinMode(pin, OUTPUT); // Set up pins
  lastPatternTime = millis();
  randomSeed(millis());
  
  nunchuck_setpowerpins();
  nunchuck_init();
}

int currentPattern = 0;
int currentColumn = 1;
boolean direction_pressed = false;

void loop()
{
  display_pattern();/*
  nunchuck_get_data();
  if (!direction_pressed && nunchuck_joyx() > 160)
  {
    currentColumn = max(currentColumn-1,0);
    direction_pressed = true;
    clearCube();
    setXZPlane(currentColumn,true);
  }
  else if (!direction_pressed && nunchuck_joyx() < 80)
  {
    currentColumn = min(currentColumn+1,3);
    direction_pressed = true;
    clearCube();
    setXZPlane(currentColumn,true);
  }
  else if (!direction_pressed && nunchuck_joyy() < 80)
  {
    currentColumn = max(currentColumn-1,0);
    direction_pressed = true;
    clearCube();
    setXYPlane(currentColumn,true);
  }
  else if (!direction_pressed && nunchuck_joyy() > 160)
  {
    currentColumn = min(currentColumn+1,3);
    direction_pressed = true;
    clearCube();
    setXYPlane(currentColumn,true);
  }
  else if (nunchuck_joyx() > 80 && nunchuck_joyx() < 160 && nunchuck_joyy() > 80 && nunchuck_joyy() < 160)
  
    direction_pressed = false;*/
  
  boolean result = false;
 /* nunchuck_get_data();
  if (nunchuck_zbutton() == 1 && !zPressed)
  {
    zPressed = true;
    currentPattern = (currentPattern + 1) % 15;
  }
  else if (!nunchuck_zbutton())
  {
    zPressed = false;
  }*/
  switch (currentPattern)
  {
    case 0:
      result = drawPattern(80,200,&jumpingLEDs);
      break;
    case 1:
      result = drawPattern(300,30,&bouncingXWall);
      break;
    case 2:
      result = drawPattern(300,45,&rotatingWall);
      break;
    case 8:
      result = drawPattern(300,30,&bouncingYWall);
      break;
    case 11:
      result = drawPattern(50,600,&randomBlink);
      break;
    case 5:
      result = drawPattern(300,30,&bouncingZWall);
      break;
    case 6:
      result = drawPattern(400,15,&innerOuterCube); // Should be 4n-1 frames
      break;
    case 12:
      result = drawPattern(150,36,&spinAboutZ);
      break;
    case 3:
      result = drawPattern(150,36,&spinAboutY);
      break;
    case 9:
      result = drawPattern(150,36,&spinAboutX);
      break;
    case 10:
      result = drawPattern(220,30,&zigZagX);
      break;
    case 7:
      result = drawPattern(220,30,&zigZagY);
      break;
    case 4:
      result = drawPattern(100,125,&rain);
      break;
    case 13:
      result = drawPattern(100,63,&cycleDown);
      break;
    case 14:
      result = drawPattern(170,40,&risingPlane);
      break;
    case 15:
      result = drawPattern(300,16,&loadingPleaseWait);
      break;
  }
  if (result)
  {
    if (++currentPattern > 15)
      currentPattern = 0;
  }
}
