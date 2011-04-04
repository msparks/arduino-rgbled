/*
rgbled: An Arduino library for controlling an integrated RGB LED or three
        separate red, green, and blue LEDs.

Copyright (c) 2011, Matt Sparks
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in
    the documentation and/or other materials provided with the
    distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
SUCH DAMAGE.
*/
#ifndef ARDUINO_RGBLED_H_
#define ARDUINO_RGBLED_H_

#include <stdint.h>


class RGBLED {
 public:
  typedef uint8_t Intensity;

  enum Channel {
    kRed   = 1,
    kGreen = 2,
    kBlue  = 4
  };

  /**
   * Constructor.
   *
   * Args:
   *   red_pin: pin number connected to the red LED.
   *   green_pin: pin number connected to the green LED.
   *   blue_pin: pin number connected to the blue LED.
   */
  RGBLED(int red_pin, int green_pin, int blue_pin);

  /**
   * Get the current intensity of a channel.
   *
   * Args:
   *   channel: color channel
   *
   * Returns:
   *   channel intensity
   */
  Intensity channelIntensity(Channel channel) const;

  /**
   * Set the intensity of a single channel.
   *
   * Args:
   *   channel: color channel
   *   intensity: channel intensity
   */
  void channelIntensityIs(Channel channel, Intensity value);

  /**
   * Set the LED color by setting all channel intensities simultaneously.
   *
   * Args:
   *   red: red channel intensity
   *   green: green channel intensity
   *   blue: blue channel intensity
   */
  void colorIs(Intensity red, Intensity green, Intensity blue);

  /**
   * Convenience interface for colorIs().
   *
   * Args:
   *   color: RGB intensities in 3 least-significant bytes
   */
  void colorIs(uint32_t color);

  /**
   * Fade a single channel between two intensities.
   *
   * initial <= final and final < initial are both supported.
   *
   * Args:
   *   channel: color channel
   *   initial: initial intensity
   *   final: final intensity
   *   delay_ms (optional): delay between color changes in milliseconds
   *                        the default value is used if 0 is passed
   */
  void fadeChannel(Channel channel,
                   Intensity initial,
                   Intensity final,
                   uint16_t delay_ms = 0);

  /**
   * Fade a group of channels between two intensities.
   *
   * initial <= final and final < initial are both supported.
   *
   * Args:
   *   channel_mask: mask formed by a bitwise OR of Channel values
   *   initial: initial intensity
   *   final: final intensity
   *   delay_ms (optional): delay between color changes in milliseconds
   *                        the default value is used if 0 is passed
   */
  void fadeChannels(uint8_t channel_mask,
                    Intensity initial,
                    Intensity final,
                    uint16_t delay_ms = 0);

  /**
   * Get the default fading delay.
   *
   * Returns:
   *   fading delay in milliseconds
   */
  uint16_t defaultDelay() const { return default_delay_; }

  /**
   * Set the default fading delay.
   *
   * Args:
   *   value: delay value in milliseconds
   */
  void defaultDelayIs(uint16_t value) { default_delay_ = value; }

 private:
  const int red_pin_;
  const int green_pin_;
  const int blue_pin_;

  Intensity red_value_;
  Intensity green_value_;
  Intensity blue_value_;

  // Default delay (in milliseconds) for use in fading.
  uint16_t default_delay_;

  // Uses PWM to write 'value' to all channels present in 'channel_mask'.
  void writeChannels(uint8_t channel_mask, Intensity value);
};

#endif
