# Maxwell: Bicycle Electrification

## Serial Command Interface

* `uptime`: Returns uptime in milliseconds.
* `ping`: Returns "pong"
* `beep [FREQUENCY [DURATION]]`: Beep.  Optionally specify a frequency (Hz) and duration (ms).
* `voltage (battery|dynamo|sense)`: Returns voltage at specified circuit location.
* `charging`: Returns "Yes" or "No" to indicate whether the Li-ion battery is currently charging.
* `btcmd <COMMAND>`: Send command to bluetooth interface board and print result afterward.  Do not interact until prompt is redisplayed.
* `reset`: Resets the board.  Note that you must disconnect from bluetooth within five seconds or the board will enter flash mode.
* `flash`: Resets the board into flash mode.  Remain connected until board has reset.

## CanBus Interface

See `can_message_ids.h` for a complete list.

# Emitted Messages

* `0x30` (double): Main microcontroller uptime in milliseconds
* `0x40` (double): Battery voltage
* `0x41` (double): Dynamo voltage
* `0x42` (double): Sense resistor voltage

# Handled Messages

None yet


## Schematics

### Main

![](https://s3-us-west-2.amazonaws.com/coddingtonbear-public/github/maxwell/maxwell.svg)
![](https://s3-us-west-2.amazonaws.com/coddingtonbear-public/github/maxwell/microcontroller-Microcontroller.svg)
![](https://s3-us-west-2.amazonaws.com/coddingtonbear-public/github/maxwell/power-Power.svg)

## Errata

*Note* None of these have been corrected in the schematics.

* Neglected to add P-Channel MOSFET-based polarity protection to the board.  Added now via a small board; see `maxwell-polarity`. Note that even *that* board is incorrect in that the input and output sides are swapped, and the button does not properly turn the MOSFET off.
* Battery and Sense resistors used GNDPWR as their ground reference, but GNDPWR is intentionally turned off to save power sometimes.  In the case of a voltage divider, that means that the microcontroller would see the full voltage of the battery (exceeding maximum ratings).
* I used the wrong footprint for the LT1529, so I've had to bend the pins in unreasonable ways to fit.
