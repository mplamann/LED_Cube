#include <Firmata.h>

boolean pattern[4][16];

void digitalWriteCallback(byte pin, int value)
{
  pattern[pin>>4][pin&0xF] = (boolean)value;
}

void setup()
{
    Firmata.setFirmwareVersion(0, 1);
    Firmata.attach(DIGITAL_MESSAGE, digitalWriteCallback);
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
