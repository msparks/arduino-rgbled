/**
 * rgblinear
 *
 * Smoothly scans through the color spectrum using an RGB LED.
 * This code is released to the public domain.
 */

#include <rgbled.h>

static const int kRed = 11;    // red channel pin
static const int kGreen = 10;  // green channel pin
static const int kBlue = 9;    // blue channel pin

// Brightest value (intensity) to use for any channel.
static const uint8_t kMaxBrightness = 255;

// Delay between color changes.
static const int kDelay = 10;  // milliseconds

// Create the RGBLED object to control our 3-channel LED.
RGBLED led(kRed, kGreen, kBlue);


void setup()
{
  // Quick demo mode: cycle between red, green, blue, white, off.
  led.colorIs(255, 0, 0);      // red
  delay(1000);                 // 1 second
  led.colorIs(0, 255, 0);      // green
  delay(1000);
  led.colorIs(0, 0, 255);      // blue
  delay(1000);
  led.colorIs(255, 255, 255);  // white
  delay(1000);
  led.colorIs(0, 0, 0);        // off

  delay(500);

  // Do the same, faster, using the shorthand interface.
  led.colorIs(0xFF0000);       // red
  delay(250);                  // 250 ms
  led.colorIs(0x00FF00);       // green
  delay(250);
  led.colorIs(0x0000FF);       // blue
  delay(250);
  led.colorIs(0xFFFFFF);       // white
  delay(250);
  led.colorIs(0);              // off
  delay(250);

  // Off -> red.
  led.fadeChannel(RGBLED::red_, 0, kMaxBrightness);

  // Set fading delay.
  led.defaultDelayIs(kDelay);
}


void loop()
{
  // Fade through the color spectrum.
  //   red -> violet -> blue -> cyan -> green -> yellow -> white -> red -> ...

  // Red -> red + blue (violet).
  led.fadeChannel(RGBLED::blue_, 0, kMaxBrightness);

  // Red + blue -> blue.
  led.fadeChannel(RGBLED::red_, kMaxBrightness, 0);

  // Blue -> blue + green (cyan).
  led.fadeChannel(RGBLED::green_, 0, kMaxBrightness);

  // Blue + green -> green.
  led.fadeChannel(RGBLED::blue_, kMaxBrightness, 0);

  // Green -> green + red (yellow).
  led.fadeChannel(RGBLED::red_, 0, kMaxBrightness);

  // Green + red -> green + red + blue (white).
  led.fadeChannel(RGBLED::blue_, 0, kMaxBrightness);

  // White -> red.
  uint8_t mask = RGBLED::blue_ | RGBLED::green_;
  led.fadeChannels(mask, kMaxBrightness, 0);
}
