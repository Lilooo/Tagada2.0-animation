/*
Tagada 2.0 (CC) 2018 Alice Giordani
AtTiny85 + WS2812 + knitted Pressure Sensor
Press it again (and again) to change the animation!
*/

#include <Adafruit_NeoPixel.h>    //https://github.com/adafruit/Adafruit_NeoPixel
#include <elapsedMillis.h>        //https://github.com/pfeerick/elapsedMillis

elapsedMillis elapsedTime;

#define SENSORPIN 3
#define PIN 0
#define NUMPIXEL 3

int delayval = 1;

int newSensorValue = 0;
int oldSensorValue = 0;
int state = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXEL, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  //Serial.begin(9600);
  strip.begin();
  strip.setBrightness(100);
  strip.show();
}

void loop() {
  newSensorValue = analogRead(SENSORPIN);
  //Serial.println(newSensorValue);

  int diff = newSensorValue - oldSensorValue;
  //Serial.println(diff);

  if (diff > 20) {
    state = 1;
  } else {
    state = 0;
  }
  //Serial.println(state);
  
    if (state == 1) {
      theaterChase(strip.Color(127,   0,   0), 50); // Red
    } else {
      nonBlockingRainbow(20);
    }
  
  strip.show();
  oldSensorValue = newSensorValue;
  delay(delayval);
}

/****Neopixels****/
void nonBlockingRainbow(int waitMs) {

  // non blocking delay:
  if (elapsedTime < waitMs)
    return;
  elapsedTime = 0;

  // "loop" on colors:
  static int j = 0;
  j = j < 256 ? j+1 : 0;

  // "loop" on strip:
  for(int i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
  }

  strip.show();
}

void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

