#include <Wire.h>

boolean pattern[4][16];

void setup()
{
  for (int pin = 0; pin < 20; pin++)
    pinMode(pin, OUTPUT); // Set up pins
  randomSeed(millis());
  
  Serial.begin(9600);
}

void setPattern(char* commandData)
{
  for (int layer = 0; layer < 4; layer++)
  {
    for (int offset = 0; offset < 2; offset++)
    {
      for (int index = 0; index < 8; index++)
      {
        pattern[layer][offset*8+index] = commandData[layer*2+offset]*(1<<index);
      }
    }
  }
}

void loop()
{
  display_pattern();
  clearCube();
  setXYPlane(3,true);
  for (int i = 0; i < Serial.available(); i++)
  {
    pattern[0][i%16] = true;
  }
  
  /*if (Serial.available() >= 9)
  {
    digitalWrite(13,HIGH);
    char commandType = Serial.read();
    char commandData[8];
    Serial.readBytes(commandData, 8);
    
    if (commandType == 0)
    {
      setPattern(commandData);
    }
  }*/
}
