int frame = 0;
unsigned long lastFrameTime = 0;

boolean drawPattern(int frameTime, int howManyFrames, void (*drawFunction)(void))
{
  if (frame > howManyFrames)
  {
    frame = 0;
    return true;
  }
  if (millis() - lastFrameTime > frameTime)
  {
    drawFunction();
    frame++;
    lastFrameTime = millis();
  }
  return false;
}

void rotatingWall()
{
  int localizedFrame = frame % 15;
  clearCube();
  switch (localizedFrame)
  {
    case 0:
    case 1:
      setXYPlane(3, true);
      break;
    case 2:
      setAllY(0,3,true);
      setAllY(1,3,true);
      setAllY(2,2,true);
      setAllY(3,2,true);
      break;
    case 3:
      setAllY(0,3,true);
      setAllY(1,2,true);
      setAllY(2,1,true);
      setAllY(3,0,true);
      break;
    case 4:
      setAllY(0,3,true);
      setAllY(0,2,true);
      setAllY(1,1,true);
      setAllY(1,0,true);
      break;
    case 5:
    case 6:
      setYZPlane(0,true);
      break;
    case 7:
      setAllZ(0,0,true);
      setAllZ(0,1,true);
      setAllZ(1,2,true);
      setAllZ(1,3,true);
      break;
    case 8:
      setAllZ(0,0,true);
      setAllZ(1,1,true);
      setAllZ(2,2,true);
      setAllZ(3,3,true);
      break;
    case 9:
      setAllZ(0,0,true);
      setAllZ(1,0,true);
      setAllZ(2,1,true);
      setAllZ(3,1,true);
      break;
    case 10:
    case 11:
      setXZPlane(0,true);
      break;
    case 12:
      setAllX(0,3,true);
      setAllX(0,2,true);
      setAllX(1,1,true);
      setAllX(1,0,true);
      break;
    case 13:
      setAllX(0,3,true);
      setAllX(1,2,true);
      setAllX(2,1,true);
      setAllX(3,0,true);
      break;
    case 14:
      setAllX(0,3,true);
      setAllX(1,3,true);
      setAllX(2,2,true);
      setAllX(3,2,true);
      break;
  }
}

void bouncingXWall()
{
  int localizedFrame = frame % 6;
  int plane;
  clearCube();
  switch (localizedFrame)
  {
    case 0:
      plane = 0;
      break;
    case 1:
    case 5:
      plane = 1;
      break;
    case 2:
    case 4:
      plane = 2;
      break;
    case 3:
      plane = 3;
      break;
  }
  setYZPlane(plane,true);
}

void bouncingYWall()
{
  int localizedFrame = frame % 6;
    int plane;
    clearCube();
    switch (localizedFrame)
    {
      case 0:
        plane = 0;
        break;
      case 1:
      case 5:
        plane = 1;
        break;
      case 2:
      case 4:
        plane = 2;
        break;
      case 3:
        plane = 3;
        break;
    }
    setXZPlane(plane,true);
}

void bouncingZWall()
{
    int localizedFrame = frame % 6;
    int plane;
    clearCube();
    switch (localizedFrame)
    {
      case 0:
        plane = 0;
        break;
      case 1:
      case 5:
        plane = 1;
        break;
      case 2:
      case 4:
        plane = 2;
        break;
      case 3:
        plane = 3;
        break;
    }
    setXYPlane(plane,true);
}

void randomBlink()
{
  if (frame == 0)
  {
    for (int layer = 0; layer < 4; layer++)
      for (int node = 0; node < 16; node++)
        pattern[layer][node] = (random(2) == 1);
    frame++;
  }
    int layer = random(0,4);
    int node = random(0,16);
    pattern[layer][node] = !pattern[layer][node];
    frame++;
    lastFrameTime = millis();
}

boolean jLedState[16];
int jPatternState = 0;
int jCurrentLed = 0;

void jumpingLEDs()
{
  if (frame == 0)
  {
    for (int node = 0; node < 16; node++)
      jLedState[node] = true;
    clearCube();
    setXYPlane(3,true);
    jPatternState = -3;
    return;
  }
  if (jPatternState < -1)
  {
    jPatternState++;
    return;
  }
  if (jPatternState == -1)
  {
    jPatternState = 3;
    jCurrentLed = random(16);
    return;
  }
  if (jLedState[jCurrentLed])
  {
    pattern[jPatternState][jCurrentLed] = false;
    pattern[--jPatternState][jCurrentLed] = true;
  }
  else
  {
    pattern[(3-jPatternState)][jCurrentLed] = false;
    pattern[(3 - --jPatternState)][jCurrentLed] = true;
  }
  if (jPatternState == 0)
  {
    jPatternState = -3;
    jLedState[jCurrentLed] = !jLedState[jCurrentLed];
  }
}

void innerOuterCube()
{
  clearCube();
  if (frame % 4 == 0)
  {
    setPoint(0,0,0,true);
    setPoint(0,0,3,true);
    setPoint(0,3,0,true);
    setPoint(0,3,3,true);
    setPoint(3,0,0,true);
    setPoint(3,0,3,true);
    setPoint(3,3,0,true);
    setPoint(3,3,3,true);
  }
  else if (frame % 4 == 1 || frame % 4 == 3)
  {
    setPoint(1,1,1,true);
    setPoint(1,1,2,true);
    setPoint(1,2,1,true);
    setPoint(1,2,2,true);
    setPoint(2,1,1,true);
    setPoint(2,1,2,true);
    setPoint(2,2,1,true);
    setPoint(2,2,2,true);
  }
  else
  {
    setPoint(1,0,1,true);
    setPoint(2,0,1,true);
    setPoint(1,0,2,true);
    setPoint(2,0,2,true);
    setPoint(1,3,1,true);
    setPoint(2,3,1,true);
    setPoint(1,3,2,true);
    setPoint(2,3,2,true);
    
    setPoint(0,1,1,true);
    setPoint(0,1,2,true);
    setPoint(0,2,1,true);
    setPoint(0,2,2,true);
    setPoint(3,1,1,true);
    setPoint(3,1,2,true);
    setPoint(3,2,1,true);
    setPoint(3,2,2,true);
    
    setPoint(1,1,0,true);
    setPoint(1,2,0,true);
    setPoint(2,1,0,true);
    setPoint(2,2,0,true);
    setPoint(1,1,3,true);
    setPoint(1,2,3,true);
    setPoint(2,1,3,true);
    setPoint(2,2,3,true);
  }
}

void spinAbout(void (*setAll)(int, int, boolean))
{
  clearCube();
  switch (frame % 6)
  {
    case 0:
      setAll(0,3,true);
      setAll(1,2,true);
      setAll(2,1,true);
      setAll(3,0,true);
      break;
    case 1:
      setAll(1,3,true);
      setAll(1,2,true);
      setAll(2,1,true);
      setAll(2,0,true);
      break;
    case 2:
      setAll(2,3,true);
      setAll(2,2,true);
      setAll(1,1,true);
      setAll(1,0,true);
      break;
    case 3:
      setAll(0,0,true);
      setAll(1,1,true);
      setAll(2,2,true);
      setAll(3,3,true);
      break;
    case 4:
      setAll(0,1,true);
      setAll(1,1,true);
      setAll(2,2,true);
      setAll(3,2,true);
      break;
    case 5:
      setAll(0,2,true);
      setAll(1,2,true);
      setAll(2,1,true);
      setAll(3,1,true);
      break;
  }
}

void spinAboutZ()
{
  spinAbout(&setAllZ);
}

void spinAboutY()
{
  spinAbout(&setAllY);
}

void spinAboutX()
{
  spinAbout(&setAllX);
}

bool zzPattern[6][4] = {{true,false,false,false},
                        {false,true,false,false},
                        {false,false,true,false},
                        {false,false,false,true},
                        {false,false,true,false},
                        {false,true,false,false}};
int zzOffset = 0;

void zigZag(void (*setAll)(int,int,boolean))
{
  clearCube();
  for (int x = zzOffset; x < zzOffset+4; x++)
  {
    for (int z = 0; z < 4; z++)
      setAll((x - zzOffset),z,zzPattern[x%6][z]);
  }
  zzOffset++;
}

void zigZagX()
{
  zigZag(setAllY);
}

void zigZagY()
{
  zigZag(setAllX);
}

void rain()
{
  if (frame == 0)
  {
    clearCube();
    for (int i = 0; i < random(3,7); i++)
      pattern[3][random(16)] = true;
  }
  
  for (int layer = 0; layer < 4; layer++)
  {
    for (int node = 0; node < 16; node++)
    {
      if (pattern[layer][node])
      {
        pattern[layer][node] = false;
        if (layer > 0)
          pattern[layer-1][node] = true;
      }
    }
  }
  
  if (frame % 3 == 0)
  {
    for (int i = 0; i < random(1,4); i++)
      pattern[3][random(16)] = true;
  }
}

void cycleDown()
{
  clearCube();
  pattern[(frame/16)%4][frame%16] = true;
}

int rpPattern[7] = {0x1000,
                    0x2800,
                    0x4410,
                    0x8228,
                    0x0144,
                    0x0082,
                    0x0001};

void risingPlane()
{
  for (int layer = 0; layer < 4; layer++)
  {
    int index = (frame % 11) - layer;
    if (index < 0 || index > 7)
    {
      setXYPlane(layer,false);
      continue;
    }
    setXYPlaneMask(layer,rpPattern[index]);
  }
}

int vPattern[7] = {V,I,C,T,O,R,Y};

void victory()
{
  clearCube();
  setXZPlaneMask(0,vPattern[frame%7]);
}

int wPattern[4] = {W,H,A,T};

void what()
{
  clearCube();
  setXZPlaneMask(0,wPattern[frame%4]);
}

void loadingPleaseWait()
{
  clearCube();
  switch (frame%9)
  {
    case 0:
      break;
    case 4:
    case 5:
      setXYPlane(3,true);
    case 3:
    case 6:
      setXYPlane(2,true);
    case 2:
    case 7:
      setXYPlane(1,true);
    case 1:
    case 8:
      setXYPlane(0,true);
  }
}
