// Arduino async serial port library with nine data bits support.
//
// 2015, (c) Gk Ltd.
// MIT License

#ifndef TINY_SERIAL_UART_HPP_
#define TINY_SERIAL_UART_HPP_

#include <tiny/detail/auto_sense.hpp>

#if defined (TINY_ARDUINO_MEGA)
# include <tiny/serial/uart_mega.hpp>
#elif defined (TINY_ARDUINO_DUE)
# include <tiny/serial/uart_due.hpp>
#else
# error "Tiny UART: Unknown Arduino platform!"
#endif //defined (TINY_ARDUINO_MEGA)

#endif // TINY_SERIAL_UART_HPP_
