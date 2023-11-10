#include "MIDIcontroller.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 20

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, PIN, NEO_GRB + NEO_KHZ800);

const int channel = 1;  // used for buttons..
byte MIDIchannel = 5;   // used for encoders..

Bounce knob1 = Bounce(0, 5);  // 5 = 5 ms debounce time
const int enc1PinA = 1;   // Change these numbers to
const int enc1PinB = 2;   // the two pins your encoder is on.

Bounce knob2 = Bounce(3, 5);  // 5 = 5 ms debounce time
const int enc2PinA = 4;   // Change these numbers to
const int enc2PinB = 5;   // the two pins your encoder is on.

Bounce knob3 = Bounce(21, 5);  // 5 = 5 ms debounce time
const int enc3PinA = 22;   // Change these numbers to
const int enc3PinB = 23;   // the two pins your encoder is on.

MIDIenc myEnc1(enc1PinA, enc1PinB, 24, PER_DETENT);
MIDIenc myEnc2(enc2PinA, enc2PinB, 25, PER_DETENT );
MIDIenc myEnc3(enc3PinA, enc3PinB, 26, PER_DETENT);


Bounce button1 = Bounce(8, 5);  // 5 = 5 ms debounce time
Bounce button2 = Bounce(9, 5);  // which is appropriate for good
Bounce button3 = Bounce(10, 5);  // quality mechanical pushbuttons
Bounce button4 = Bounce(11, 5);  // 5 = 5 ms debounce time
Bounce button5 = Bounce(12, 5);  // which is appropriate for good
Bounce button6 = Bounce(13, 5);  // quality mechanical pushbuttons
Bounce button7 = Bounce(14, 5);  // 5 = 5 ms debounce time
Bounce button8 = Bounce(15, 5);  // which is appropriate for good
Bounce button9 = Bounce(16, 5);  // quality mechanical pushbuttons

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void setup() {
  for(int p=0; p<24; p++)
  {
    pinMode(p, INPUT_PULLUP);
  }
  pinMode(20, OUTPUT);
  
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'  
 
}

int firsttime = 0;

void loop() {
  if(firsttime == 0)
  {
      // Some example procedures showing how to display to the pixels:
    colorWipe(strip.Color(0, 0, 255), 100); // Blue
    colorWipe(strip.Color(255, 0, 0), 80); // Red
    colorWipe(strip.Color(0, 255, 0), 80); // Green
    //colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
    firsttime = 1;
  }
  knob1.update();
  knob2.update();
  knob3.update();

  button1.update();
  button2.update();
  button3.update();
  button4.update();
  button5.update();
  button6.update();  
  button7.update();
  button8.update();
  button9.update();

  myEnc1.sendRelative();
  myEnc2.send();
  myEnc3.send();

  // Note On messages when each button is pressed
  if (knob1.fallingEdge()) {
    usbMIDI.sendNoteOn(61, 127, channel);  // 60 = C4
  }
  if (knob2.fallingEdge()) {
    usbMIDI.sendNoteOn(62, 127, channel);  // 61 = C#4
  }
  if (knob3.fallingEdge()) {
    usbMIDI.sendNoteOn(63, 127, channel);  // 62 = D4
  }

  if (button1.fallingEdge()) {
    usbMIDI.sendNoteOn(51, 127, channel);  // 62 = D4
  }
  if (button2.fallingEdge()) {
    usbMIDI.sendNoteOn(52, 127, channel);  // 62 = D4
  }
  if (button3.fallingEdge()) {
    usbMIDI.sendNoteOn(53, 127, channel);  // 62 = D4
  }
  if (button4.fallingEdge()) {
    usbMIDI.sendNoteOn(54, 127, channel);  // 62 = D4
  }
  if (button5.fallingEdge()) {
    usbMIDI.sendNoteOn(55, 127, channel);  // 62 = D4
  }
  if (button6.fallingEdge()) {
    usbMIDI.sendNoteOn(56, 127, channel);  // 62 = D4
  }
  if (button7.fallingEdge()) {
    usbMIDI.sendNoteOn(57, 127, channel);  // 62 = D4
  }
  if (button8.fallingEdge()) {
    usbMIDI.sendNoteOn(58, 127, channel);  // 62 = D4
  }
  if (button9.fallingEdge()) {
    usbMIDI.sendNoteOn(59, 127, channel);  // 62 = D4
  }

 //-------------------------------------
  // Note Off messages when each button is released
  if (knob1.risingEdge()) {
    usbMIDI.sendNoteOff(61, 0, channel);  // 60 = C4
  }
  if (knob2.risingEdge()) {
    usbMIDI.sendNoteOff(62, 0, channel);  // 61 = C#4
  }
  if (knob3.risingEdge()) {
    usbMIDI.sendNoteOff(63, 0, channel);  // 62 = D4
  }


  if (button1.risingEdge()) {
    usbMIDI.sendNoteOn(51, 0, channel);  // 62 = D4
  }
  if (button2.risingEdge()) {
    usbMIDI.sendNoteOn(52, 0, channel);  // 62 = D4
  }
  if (button3.risingEdge()) {
    usbMIDI.sendNoteOn(53, 0, channel);  // 62 = D4
  }
  if (button4.risingEdge()) {
    usbMIDI.sendNoteOn(54, 0, channel);  // 62 = D4
  }
  if (button5.risingEdge()) {
    usbMIDI.sendNoteOn(55, 0, channel);  // 62 = D4
  }
  if (button6.risingEdge()) {
    usbMIDI.sendNoteOn(56, 0, channel);  // 62 = D4
  }
  if (button7.risingEdge()) {
    usbMIDI.sendNoteOn(57, 0, channel);  // 62 = D4
  }
  if (button8.risingEdge()) {
    usbMIDI.sendNoteOn(58, 0, channel);  // 62 = D4
  }
  if (button9.risingEdge()) {
    usbMIDI.sendNoteOn(59, 0, channel);  // 62 = D4
  }

  // MIDI Controllers should discard incoming MIDI messages.
  while (usbMIDI.read()) {
  }
}
