# Maxwell: Bicycle Electrification

I have a bicycle dynamo on my bike, a rudimentary understanding of electronics, and a bunch of neopixels, gps, and bluetooth modules to use.  This is what happens when those things combine.

Maxwell is a two-part bike computer I've designed to allow me to do a few things:

* Light and control neopixel LEDs wrapped around my bike for added safety while biking at night, and added fun when biking with groups.
* Charge an easily-swappable 18650 Li-On cell for potential use when bike touring.
* Gather and transmit GPS coordinates for display on the internet somewhere.
* Display status information including my current speed, battery voltage, and current consumption, as well as disable or enable bike features including, most importantly, disabling and enabling the LEDs from a small screen mounted at the front of the bike.

The "remote" unit is based around the STM32F103CB microcontroller, and the "base" unit is based around its slightly-more-full-featured brother, the STM32F103RE.  Both communicate with one another over a CANBus (routed through two of the conductors in a length of ethernet cable) to share status information and emit/handle commands.

## Schematics

### Main

![](https://s3-us-west-2.amazonaws.com/coddingtonbear-public/github/maxwell/maxwell.svg?v=2)
![](https://s3-us-west-2.amazonaws.com/coddingtonbear-public/github/maxwell/microcontroller-Microcontroller.svg?v=2)
![](https://s3-us-west-2.amazonaws.com/coddingtonbear-public/github/maxwell/power-Power.svg?v=2)

### Head Unit (Remote)

![](https://s3-us-west-2.amazonaws.com/coddingtonbear-public/github/maxwell/maxwell-remote.svg)

## Errata

Checked items indicate errata that have been corrected in the schematic.

### Maxwell

* [ ] Capacitor C15 is unnecessary; the buck regulator breakout board that is attached already has a more-than-adequate capacitor.  I discovered this only when attempting to identify C15 had failed, and when discovering that its voltage rating was far too low and that I didn't have capacitors having a similar-enough footprint and a high-enough voltage cieling to work, then did some investigation to see if there was sufficient capacitance on that net: there was.
* [ ] I really should've added a mosfet for disabling the HC-05 module.  While in sleep mode, the bluetooth module will consume ~20mA of power, which while not _huge_, is more than enough to drain the whole battery over the course of a couple days.
* [ ] The bluetooth module will have a thin metal shield overhead for the duration of its life, and is not likely to get a GPS lock ever.  I hadn't considered this when designing this, but given the placement of this unit on my bike, the bluetooth module will never be useful, so I've removed it from the live board.
* [ ] Mis-labeled SPI2 pins for SPI2 ports; two of the labels are swapped starting from the microcontroller itself.  Although labeled `+`, `CLK`, `DI`, `DO`, `+`, `CS`, the pins are actually `+`, `DO`, `DI`, `CLK`, `+`, `CS`.
* [ ] The CanBus transceiver's Rs pin should be connected to the microcontroller to allow me to put the device into sleep mode.  Experimentation with sleep modes showed that I was able to get power consumption down to ~5.5mA (from ~50-150mA while running, depending on whether or which radios are turned on), but sleep power consumption _should_ be on the order of microamps.  Most of that 5.5mA is the CanBus transceiver.
* [ ] The ESP32 module should have a decoupling capacitor.

### Maxwell-remote

* [ ] Missing 2.2k pull-up resistors for both SCL and SDA on the I2C bus.  These have been bodged on for my current instance of this board, but were this re-built, I'd add them...probably to the back of the board.
