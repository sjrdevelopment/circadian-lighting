// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PINA        6 // On Trinket or Gemma, suggest changing this to 1
#define PINB        7 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 12 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PINA, NEO_GRB + NEO_KHZ800);


uint32_t daybreakSunset = pixels.Color(211, 25, 1);
uint32_t earlyMorningLateNight = pixels.Color(223, 52, 9);
uint32_t midMorningEarlyEvening = pixels.Color(232, 214, 10);
uint32_t prePostCore = pixels.Color(150, 105, 102);
uint32_t core = pixels.Color(106, 128, 249);

uint32_t warmWhite = pixels.Color(205, 160, 25);
uint32_t brightWhite = pixels.Color(255, 255, 255);
//
Adafruit_NeoPixel pixelsb(NUMPIXELS, PINB, NEO_GRBW);

uint32_t daybreakSunsetB = pixelsb.Color(211, 25, 1, 0);
uint32_t earlyMorningLateNightB = pixels.Color(223, 52, 9, 0);
uint32_t midMorningEarlyEveningB = pixels.Color(232, 214, 10, 0);
uint32_t prePostCoreB = pixels.Color(150, 105, 102, 0);
uint32_t coreB = pixels.Color(106, 128, 249, 0);
uint32_t warmWhiteB = pixelsb.Color(0, 0, 0, 255);

unsigned long currentTime;

const int buttonPin = 2; 
int buttonState = 0; 
bool buttonFlag = false;

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixelsb.begin();

  pinMode(buttonPin, INPUT);
  
}

void loop() {
   currentTime = millis();

     buttonState = digitalRead(buttonPin);

     if (buttonState == HIGH) {
      buttonFlag = !buttonFlag;
     } 

     if (buttonFlag) {
      setColor(warmWhite, warmWhiteB);
     } 
   else if (currentTime < 1800000) {
     setColor(earlyMorningLateNight, earlyMorningLateNightB);
   } else if (currentTime < 3100000) {
     setColor(midMorningEarlyEvening, midMorningEarlyEveningB);
   } else if (currentTime < 5400000) {
     setColor(prePostCore, prePostCoreB);
   } else if (currentTime < 21600000) {
     setColor(core, coreB);
   } else if (currentTime < 23400000) {
     setColor(prePostCore, prePostCoreB);
   } else if (currentTime < 24300000) {
     setColor(midMorningEarlyEvening, midMorningEarlyEveningB);
   } else if (currentTime < 25200000) {
     setColor(earlyMorningLateNight, earlyMorningLateNightB);
   } else {
     setColor(daybreakSunset, daybreakSunsetB);
   } 

}

void setColor(uint32_t col1, uint32_t col2) {
  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    
      pixels.setPixelColor(i, col1);
    
      pixelsb.setPixelColor(i, col2);
    
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    

      // Send the updated pixel colors to the hardware.
    
  }
  pixelsb.show();
   
   pixels.show(); 
   delay(3000);

}
