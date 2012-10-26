import ddf.minim.signals.*;
import ddf.minim.*;
import ddf.minim.analysis.*;
import ddf.minim.effects.*;
import processing.serial.*;
import cc.arduino.*;

Arduino arduino;

Minim minim;

//AudioPlayer player;
AudioInput input;
CubeRenderer cube;
//BeatDetect beat;
//BeatListener bl;

void setup()
{
  size (512,512,P3D);
  println(Arduino.list());
  arduino = new Arduino(this, Arduino.list()[4], 57600);
  minim = new Minim(this);
  //smooth();
  //player = minim.loadFile("Wizards in Winter.mp3");
  //player = minim.loadFile("The Seal is Broken.mp3");
  //player = minim.loadFile("Skillet - Hero.mp3");
  //player = minim.loadFile("Inverting the Tower Temple.mp3");
  //player = minim.loadFile("Lost Radiance.mp3");
  //player = minim.loadFile("The Ultimate Show.mp3");
  //player = minim.loadFile("4-09 Black Wing Metamorphosis (One-Winged Angel).mp3");
  //player = minim.loadFile("Immortal Souls.mp3");
  //player = minim.loadFile("2323 Dovahkiin.mp3");
  input = minim.getLineIn();
  //beat = new BeatDetect(player.bufferSize(), player.sampleRate());
  //beat.setSensitivity(150);
  //bl = new BeatListener(beat, player);
  //player.play();
  
  //player.loop();
  
  cube = new CubeRenderer(arduino, input);//player);
  //player.addListener(cube);
  input.addListener(cube);
  cube.setup();
}

int lastKick = 0;
int lastSnare = 0;
int lastHat = 0;
int lastBeat = 0;

void draw()
{
  cube.draw();
  /*if (beat.isRange( 5, 10, 2 ) )
  {
    lastBeat = 100;
  }
  else
  {
    lastBeat = constrain(lastBeat-12,0,100);
  }
  if (beat.isKick())
  {
    lastKick = 100;
  }
  else
  {
    lastKick = constrain(lastKick-12,0,100);
  }
  if (beat.isHat())
  {
    lastHat = 100;
  }
  else
  {
    lastHat = constrain(lastHat-12,0,100);
  }
  if (beat.isSnare())
  {
    lastSnare = 100;
  }
  else
  {
    lastSnare = constrain(lastSnare-12,0,100);
  }
  //lastPeak = int(player.mix.level()*150);
  arduino.analogWrite(0,lastBeat);
  arduino.analogWrite(1,lastKick);
  arduino.analogWrite(2,lastHat);
  arduino.analogWrite(3,lastSnare);
  //println(lastPeak);*/
}

void stop()
{
  input.close();//player.close();
  minim.stop();
  super.stop();
}
