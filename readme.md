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

* [ ] Incorrect management of switching between dynamo and battery power.  The MOSFET method I was originally planning to use was probably unworkable; instead just use a schottky diode before the junction point of both.

### Maxwell-remote

* [ ] Incorrect diode footprint for polarity protection.  There also might be a power deliver problem through those diodes.  Investigate that the selected mosftet is ON at Vgs -3.3.
* [ ] I think the gerbers I generated originally may have excluded the rear solder mask, as the resistors and vias were covered.
* [ ] Board-to-board interconnect should probably either not use an FPC connector, or use multiple conductors for power/ground.  I had to build a workaround connector for transferring power between the two boards.
* [ ] Resistor R2 of maxwell-remote-2 isn't really necessary; it could be connected directly to VCC.
