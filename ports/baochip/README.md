# The minimal port

This port is intended to be a minimal MicroPython port that actually runs.
It can run on a Baochip Dabao board.

## Building for Baochip

To build:

    $ make

Building will produce the build/firmware.uf2 file which can be programmed
to a Baochip board using USB file transfer with the Baochip bootloader.

This version of the build will will give you a MicroPython REPL on UART2 (pins
PB14 and PB13) at 1000000 baud.
