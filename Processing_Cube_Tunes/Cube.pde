
abstract class AudioRenderer implements AudioListener {
  float[] left;
  float[] right;
  synchronized void samples(float[] samp) { left = samp; }
  synchronized void samples(float[] sampL, float[] sampR) { left = sampL; right = sampR; }
  abstract void setup();
  abstract void draw(); 
}

import ddf.minim.analysis.*;

abstract class FourierRenderer extends AudioRenderer {
  FFT fft; 
  float maxFFT;
  float[] leftFFT;
  float[] rightFFT;
  FourierRenderer(AudioSource source) {
    float gain = .125;
    fft = new FFT(source.bufferSize(), source.sampleRate());
    maxFFT =  source.sampleRate() / source.bufferSize() * gain;
    fft.window(FFT.HAMMING);
  }
  
  void calc(int bands) {
    if(left != null) {
      leftFFT = new float[bands];
      fft.linAverages(bands);
      fft.forward(left);
      for(int i = 0; i < bands; i++) leftFFT[i] = fft.getAvg(i);   
    }
  }
}

int lastMillis = 0;
int lastPeak = 0;

int calls = 0;
//int 

class CubeRenderer extends FourierRenderer {
  Arduino arduino;
  float[] maxValue;
  int bands = 8;
  int lastDecay = 0;
  int decayDelay = 200;

  CubeRenderer(Arduino _arduino, AudioSource source) {
    super(source);
    arduino = _arduino;
  }
  
  void setup() {
    colorMode(RGB, TWO_PI, 1, 1);
    background(0);
    maxValue = new float[bands];
    for (int band = 0; band < bands; band++)
      maxValue[band] = -1;
  }
  
  synchronized void samples(float[] samp) 
  { 
    left = samp;
    //println ("Min: " + minValue);
    //println ("Max: " + maxValue);
  }
  
  synchronized void samples(float[] sampL, float[] sampR) 
  {
    this.samples(sampL);
    right = sampR;
  }
  
  int lastMillis = 0;
  
  synchronized void draw()
  {
    /*int diff = (millis()-lastMillis);
    if (diff < 0)
      return;
    //println("Time since last call: " + diff);
    lastMillis = millis();*/
    if (left == null)
      return;
    super.calc(4);
    for (int band = 0; band < 4; band++)
    {
      if (maxValue[band] < 0 || leftFFT[band] > maxValue[band])
        maxValue[band] = leftFFT[band];
      else if (millis() - lastDecay > decayDelay)
      {
        maxValue[band] *= .96;
        lastDecay = millis();
      }
      //int bandIndex = band - 1;
      //if (band == 0)
      //  bandIndex = 0;
      int bandIndex = band;
      arduino.analogWrite(band,int(4*leftFFT[bandIndex]/maxValue[bandIndex]));
    }
  }
}

