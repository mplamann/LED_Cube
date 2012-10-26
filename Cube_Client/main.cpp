#define MACOSX
#include "serial.h"

#include <iostream>
using namespace std;

int main()
{
  Serial* serial = new Serial();
  cout << "Initializing arduino...";
  if (!serial->Set_baud(9600))
    //    return -1;
  cout << "\nSelecting device...";
  if (!serial->Open("/dev/tty.usbmodemfa121"))
    //    return -1;
  cout << "Done.\n";
  char msg[9];
  msg[0] = 0x00;
  msg[1] = 0x0F;
  msg[2] = 0x00;
  msg[3] = 0xF0;
  msg[4] = 0x00;
  msg[5] = 0x0F;
  msg[6] = 0x00;
  msg[7] = 0xF0;
  msg[8] = 0x00;

  serial->Write(msg, 9);
  return 0;
}
