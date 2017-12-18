/*-------------------------------------------------------------------------
  Arduino library to control a wide variety of WS2811- and WS2812-based RGB
  LED devices such as Adafruit FLORA RGB Smart Pixels and NeoPixel strips.
  Currently handles 400 and 800 KHz bitstreams on 8, 12 and 16 MHz ATmega
  MCUs, with LEDs wired for RGB or GRB color order.  8 MHz MCUs provide
  output on PORTB and PORTD, while 16 MHz chips can handle most output pins
  (possible exception with upper PORT registers on the Arduino Mega).

  Written by Phil Burgess / Paint Your Dragon for Adafruit Industries,
  contributions by PJRC and other members of the open source community.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing products
  from Adafruit!

  -------------------------------------------------------------------------
  This file is part of the Adafruit NeoPixel library.

  NeoPixel is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation, either version 3 of
  the License, or (at your option) any later version.

  NeoPixel is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with NeoPixel.  If not, see
  <http://www.gnu.org/licenses/>.
  -------------------------------------------------------------------------*/

#include "Adafruit_NeoPixel-ANDnXOR.h"

Adafruit_NeoPixel::Adafruit_NeoPixel(uint16_t n, uint8_t p, uint8_t t) : numLEDs(n), numBytes(n * 3), pin(p), type(t), pixels(NULL)
#ifdef __AVR__
  ,port(portOutputRegister(digitalPinToPort(p))),
   pinMask(digitalPinToBitMask(p))
#endif
{
  if((pixels = (uint8_t *)malloc(numBytes))) {
    memset(pixels, 0, numBytes);
  }
}

static inline void delayShort(uint32_t) __attribute__((always_inline, unused));
static inline void delayShort(uint32_t num) {
  asm volatile(
    "L_%=_delay:"       "\n\t"
    "subs   %0, #1"     "\n\t"
    "bne    L_%=_delay" "\n"
    : "+r" (num) :
  );
}


void Adafruit_NeoPixel::begin(void) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void Adafruit_NeoPixel::show(void) {

  if(!pixels) return;

  // Data latch = 50+ microsecond pause in the output stream.  Rather than
  // put a delay at the end of the function, the ending time is noted and
  // the function will simply hold off (if needed) on issuing the
  // subsequent round of data until the latch time has elapsed.  This
  // allows the mainline code to start generating the next frame of data
  // rather than stalling for the latch.
  while((micros() - endTime) < 50L);
  // endTime is a private member (rather than global var) so that mutliple
  // instances on different pins can be quickly issued in succession (each
  // instance doesn't delay the next).

  // In order to make this code runtime-configurable to work with any pin,
  // SBI/CBI instructions are eschewed in favor of full PORT writes via the
  // OUT or ST instructions.  It relies on two facts: that peripheral
  // functions (such as PWM) take precedence on output pins, so our PORT-
  // wide writes won't interfere, and that interrupts are globally disabled
  // while data is being issued to the LEDs, so no other code will be
  // accessing the PORT.  The code takes an initial 'snapshot' of the PORT
  // state, computes 'pin high' and 'pin low' values, and writes these back
  // to the PORT register as needed.

  noInterrupts(); // Need 100% focus on instruction timing

  #define DELAY_800_T0H  1
  #define DELAY_800_T0L  4
  #define DELAY_800_T1H 6
  #define DELAY_800_T1L  1

  #define SET_HI    (PIN_MAP[pin].gpio_device->regs->BSRR = (1U << PIN_MAP[pin].gpio_bit) << (16 *  ((uint8_t)!1)) );
  #define SET_LO   (PIN_MAP[pin].gpio_device->regs->BSRR = (1U << PIN_MAP[pin].gpio_bit) << (16 *  ((uint8_t)!0)) );

  uint8_t *p   = pixels,
          *end = p + numBytes, pix, mask;

  if((type & NEO_SPDMASK) == NEO_KHZ800) { // 800 KHz bitstream
    while(p < end) {
      pix = *p++;
//uint32_t start = 0;
//uint32_t end = 0;
      for(mask = 0x80; mask; mask >>= 1) {
//start = micros();
        SET_HI
        if(pix & mask) {
          delayShort(DELAY_800_T1H);
          SET_LO
          delayShort(DELAY_800_T1L);
        } else {
          delayShort(DELAY_800_T0H);
          SET_LO
          delayShort(DELAY_800_T0L);
        }
//end = micros();
//Serial.print("Time:");Serial.println(end-start);
      }
    }
  } else { // 400 kHz bitstream
    
    return;
    //TODO: FIGURE OUT TIMINGS FOR 400KHZ LEDS ON MAPLE
    /*while(p < end) {
      pix = *p++;
      for(mask = 0x80; mask; mask >>= 1) {
        SET_HI
        if(pix & mask) {
          delayShort(DELAY_400_T1H);
          SET_LO
          delayShort(DELAY_400_T1L);
        } else {
          delayShort(DELAY_400_T0H);
          SET_LO
          delayShort(DELAY_400_T0L);
        }
      }
    }*/
  }
  
  interrupts();
  endTime = micros(); // Save EOD time for latch on next call
}

// Set pixel color from separate R,G,B components:
void Adafruit_NeoPixel::setPixelColor(
 uint16_t n, uint8_t r, uint8_t g, uint8_t b) {
  if(n < numLEDs) {
    if(brightness) { // See notes in setBrightness()
      r = (r * brightness) >> 8;
      g = (g * brightness) >> 8;
      b = (b * brightness) >> 8;
    }
    uint8_t *p = &pixels[n * 3];
    if((type & NEO_COLMASK) == NEO_GRB) { *p++ = g; *p++ = r; }
    else                                { *p++ = r; *p++ = g; }
    *p = b;
  }
}

// Set pixel color from 'packed' 32-bit RGB color:
void Adafruit_NeoPixel::setPixelColor(uint16_t n, uint32_t c) {
  if(n < numLEDs) {
    uint8_t
      r = (uint8_t)(c >> 16),
      g = (uint8_t)(c >>  8),
      b = (uint8_t)c;
    if(brightness) { // See notes in setBrightness()
      r = (r * brightness) >> 8;
      g = (g * brightness) >> 8;
      b = (b * brightness) >> 8;
    }
    uint8_t *p = &pixels[n * 3];
    if((type & NEO_COLMASK) == NEO_GRB) { *p++ = g; *p++ = r; }
    else                                { *p++ = r; *p++ = g; }
    *p = b;
  }
}

// Convert separate R,G,B into packed 32-bit RGB color.
// Packed format is always RGB, regardless of LED strand color order.
uint32_t Adafruit_NeoPixel::Color(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

// Query color from previously-set pixel (returns packed 32-bit RGB value)
uint32_t Adafruit_NeoPixel::getPixelColor(uint16_t n) {

  if(n < numLEDs) {
    uint16_t ofs = n * 3;
    return (uint32_t)(pixels[ofs + 2]) |
      (((type & NEO_COLMASK) == NEO_GRB) ?
        ((uint32_t)(pixels[ofs    ]) <<  8) |
        ((uint32_t)(pixels[ofs + 1]) << 16)
      :
        ((uint32_t)(pixels[ofs    ]) << 16) |
        ((uint32_t)(pixels[ofs + 1]) <<  8) );
  }

  return 0; // Pixel # is out of bounds
}

uint16_t Adafruit_NeoPixel::numPixels(void) {
  return numLEDs;
}

// Adjust output brightness; 0=darkest (off), 255=brightest.  This does
// NOT immediately affect what's currently displayed on the LEDs.  The
// next call to show() will refresh the LEDs at this level.  However,
// this process is potentially "lossy," especially when increasing
// brightness.  The tight timing in the WS2811/WS2812 code means there
// aren't enough free cycles to perform this scaling on the fly as data
// is issued.  So we make a pass through the existing color data in RAM
// and scale it (subsequent graphics commands also work at this
// brightness level).  If there's a significant step up in brightness,
// the limited number of steps (quantization) in the old data will be
// quite visible in the re-scaled version.  For a non-destructive
// change, you'll need to re-render the full strip data.  C'est la vie.
void Adafruit_NeoPixel::setBrightness(uint8_t b) {
  // Stored brightness value is different than what's passed.
  // This simplifies the actual scaling math later, allowing a fast
  // 8x8-bit multiply and taking the MSB.  'brightness' is a uint8_t,
  // adding 1 here may (intentionally) roll over...so 0 = max brightness
  // (color values are interpreted literally; no scaling), 1 = min
  // brightness (off), 255 = just below max brightness.
  uint8_t newBrightness = b + 1;
  if(newBrightness != brightness) { // Compare against prior value
    // Brightness has changed -- re-scale existing data in RAM
    uint8_t  c,
            *ptr           = pixels,
             oldBrightness = brightness - 1; // De-wrap old brightness value
    uint16_t scale;
    if(oldBrightness == 0) scale = 0; // Avoid /0
    else if(b == 255) scale = 65535 / oldBrightness;
    else scale = (((uint16_t)newBrightness << 8) - 1) / oldBrightness;
    for(uint16_t i=0; i<numBytes; i++) {
      c      = *ptr;
      *ptr++ = (c * scale) >> 8;
    }
    brightness = newBrightness;
  }
}
