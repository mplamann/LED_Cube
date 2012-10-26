int nodeMap[4][4] = {{3,2,1,0},
                     {4,5,6,7},
                     {11,10,9,8},
                     {12,13,14,15}};
                     
int A = 0xF9F9;
int B = 0x4466;
int C = 0xE88E;
int D = 0xEAAE;
int F = 0xE8E8;
int G = 0xEB9F;
int H = 0x9FF9;
int I = 0xF66F;
int J = 0xF2AE;
int K = 0x5665;
int L = 0x888F;
int M = 0x9F99;
int N = 0x9DB9;
int O = 0xF99F;
int P = 0x6644;
int Q = 0xEAE1;
int R = 0xEAE9;
int S = 0x4A4E;
int T = 0xF666;
int U = 0x999F;
int V = 0x9996;
int W = 0x99F6;
int X = 0x9669;
int Y = 0x9966;
int Z = 0xF24F;

int latchPin = 8;
int clockPin = 6;
int dataPin = 7;

void setXYPlane(int z, boolean value)
{
  for (int node = 0; node < 16; node++)
    pattern[z][node] = value;
}

void setYZPlane(int x, boolean value)
{
  for (int layer = 0; layer < 4; layer++)
    for (int y = 0; y < 4; y++)
      pattern[layer][nodeMap[x][y]] = value;
}

void setXZPlane(int y, boolean value)
{
  for (int layer = 0; layer < 4; layer++)
    for (int x = 0; x < 4; x++)
      pattern[layer][nodeMap[x][y]] = value;
}

void setAllX(int y, int z, boolean value)
{
  for (int x = 0; x < 4; x++)
    pattern[z][nodeMap[x][y]] = value;
}

void setAllY(int x, int z, boolean value)
{
  for (int y = 0; y < 4; y++)
    pattern[z][nodeMap[x][y]] = value;
}

void setAllZ(int x, int y, boolean value)
{
  for (int z = 0; z < 4; z++)
    pattern[z][nodeMap[x][y]] = value;
}

void clearCube()
{
  for (int layer = 0; layer < 4; layer++)
    for (int node = 0; node < 16; node++)
      pattern[layer][node] = false;
}

void setPoint(int x, int y, int z, boolean value)
{
  pattern[z][nodeMap[x][y]] = value;
}

void setXYPlaneMask(int z, int mask)
{
  for (int node = 0; node < 16; node++)
  {
    pattern[z][node] = ((mask & (1<<node)) != 0);
  }
}

void setXZPlaneMask(int y, int mask)
{
  for (int z = 0; z < 4; z++)
  {
    for (int x = 0; x < 4; x++)
    {
      int offset = 4*z+x;
      pattern[z][nodeMap[3-x][y]] = ((mask & (1<<offset)) != 0);
    }
  }
}

void display_pattern()
{
  for (int layer = 0; layer < 4; layer++)
  {
    int byteForRegister2 = 0;
    int byteForRegister1 = 0;
    for (int register1 = 0; register1 < 8; register1++)
    {
      if (pattern[layer][register1])
        byteForRegister1 += (1 << register1);
    }
    for (int register2 = 0; register2 < 8; register2++)
    {
      if (pattern[layer][register2+8])
        byteForRegister2 += (1 << register2);
    }
    
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, byteForRegister2);
    shiftOut(dataPin, clockPin, MSBFIRST, byteForRegister1);
    digitalWrite(latchPin,HIGH);
    
    int layerPin;
    switch (layer)
    {
      case 0:
        layerPin = 9;
        break;
      case 1:
        layerPin = 12;
        break;
      case 2:
        layerPin = 11;
        break;
      case 3:
        layerPin = 10;
        break;
    }
    digitalWrite(layerPin,HIGH);
    delay(1);
    digitalWrite(layerPin,LOW);
    delay(1);
  }
}
