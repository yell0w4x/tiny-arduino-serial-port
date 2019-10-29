// Arduino async serial port library with nine data bits support.
//
// 2015, (c) Gk Ltd.
// MIT License

#include <tiny/detail/auto_sense.hpp>

#if defined (TINY_ARDUINO_MEGA)
# include "uart_mega.ipp"
#elif defined (TINY_ARDUINO_DUE)
# include "uart_due.ipp"
#else
# error "Tiny UART: Unknown arduino platform!"
#endif //defined (TINY_ARDUINO_MEGA)

