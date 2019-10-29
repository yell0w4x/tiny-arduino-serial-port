# Tiny async serial port C++ library for embedded devices with 9nth bit support

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

The library supports Arduino Due based on SAM3x8e. Also version for Arduino Mega is provided, but it can be outdated.
Everything below are regarded to Arduino Due and applicable for Mega in most. Exceptions for Arduino Mega are noted explicilty.

## Patch

Before start using it's necessary to apply patch to the arduino `variant.h` and `variant.cpp` files. Assume line below is executed within location of these files.

`patch -p1 < variant.patch`

For Arduino Mega patch is not provided. It's likely necessary to exclude `HardwareSerial*.cpp` from being compiled.

## Preprocessor definitions

Port numbering complies to Arduino library. To make ports avaiable it's necessary to define these. By default 8 bit variant is provided.

`TINY_HAS_HWSERIAL0`
`TINY_HAS_HWSERIAL1`
`TINY_HAS_HWSERIAL2`
`TINY_HAS_HWSERIAL3`

It's recommeded to define them within compiler command line by using `-D` switch like `-DTINY_HAS_HWSERIAL1`. For 9nth bit support use this `-DTINY_HAS_HWSERIAL1=9`.

Also we provide "Serial 0" support for Arduino Due. Actually MCU port and Arduino port numbers don't match. Table below describes mappings between these.

Arduino   | Tiny    | SAM3x8e |
:--------:|:-------:|:-------:|
Serial1   | serial1 | USART0  |
Serial2   | serial2 | USART1  |
Serail3   | serial3 | USART3  |
Not provided, pins TXD - 11, RXD - 52 | serial0 | USART2, pins: TXD - PB20, RXD - PB21 |

Before use `serail0` it's necessary to explicilty call `init_serial0()`. It's made intentionally to avoid accidental configuration override of pins used by port.

To designate in/out buffer queue size to be used by ports define `TINY_SERIAL_DEF_BUF_SIZE`, defaulted to 32.

## Usage

```c++
#include <tiny/serial/uart.hpp>

using tiny::io::serial1; 
using tiny::io::extended_port_traits;

...
serial1().open(19200, extended_port_traits::_9n1);

...
while (serial1().available())
{
  const auto octet = serial1().async_read();
  ...
}
```
9nth bit version operates with `unsinged short int` type.

## Tests

```
cd tiny
mkdir test-build && cd test-build
cmake ../test 
make && ctest
```
Serial port mock is provided via `#include <tiny/serial.hpp>`.


