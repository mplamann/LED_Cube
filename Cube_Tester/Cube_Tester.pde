import processing.serial.*;
import cc.arduino.*;

Arduino arduino;
println(Arduino.list());
arduino = new Arduino(this, Arduino.list()[0], 57600);
arduino.digitalWrite(0x02,1);
