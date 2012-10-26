#include <Firmata.h>
void analogWriteCallback(byte pin, int value)
{
  //clearCube();
  setYZPlane(pin,false);
  for (int i = 0; i < value; i++)
    setAllY(pin,i,true);
  //setYZPlane(pin,(value>50));
  /*if (value > 0)
    setXYPlane(0,true);
  if (value > 25)
    setXYPlane(1,true);
  if (value > 50)
    setXYPlane(2,true);
  if (value > 75)
    setXYPlane(3,true);*/
}

void setup()
{
    Firmata.setFirmwareVersion(0, 1);
    Firmata.attach(ANALOG_MESSAGE, analogWriteCallback);
    Firmata.begin(57600);
    for (int i = 2; i < 20; i++)
      pinMode(i,OUTPUT);
    clearCube();
}

void loop()
{
  display_pattern();
  while (Firmata.available())
  {
    Firmata.processInput();
  }
}
