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

* `0x40` (double): Battery voltage
* `0x41` (double): Dynamo voltage
* `0x42` (double): Sense resistor voltage

# Handled Messages

None yet
