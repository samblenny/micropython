# The minimal port

This port is intended to be a minimal MicroPython port that actually runs.
It can run on a Baochip Dabao board.

## Building for Baochip

This is only tested on Debian 13 (Trixie). YMMV for any other distro/OS.

1. Follow the
   [Dev Environment Setup](https://github.com/samblenny/baochip-sdk#dev-environment-setup)
   instructions in the
   [baochip-sdk](https://github.com/samblenny/baochip-sdk) README to install
   rust with the riscv32imac-unknown-none-elf target. You also need the Debian
   packages for binutils-riscv64-unknown-elf, gcc-riscv64-unknown-elf, and
   picolibc-riscv64-unknown-elf.

2. Clone this repo

3. Get the Baochip SDK submodule (you don't need any other submodules):
   ```
   cd micropython
   git submodule update --init -- ports/baochip/baochip-sdk
   ```

4. Build:
   ```
   cd micropython/ports/baochip
   make
   ```

5. Copy ports/baochip/build/firmware.uf2 to your Dabao board (must be in
   bootloader mode so you can see the BAOCHIP USB drive. Sync, eject BAOCHIP,
   then press the Dabao board's PROG button (assuming you have bootwait mode
   active in the bootloader config).

This version of the build will will give you a MicroPython REPL on UART2 (pins
PB14 and PB13) at 1000000 baud.
