// Arduino async serial port library with nine data bits support.
//
// 2015, (c) Gk Ltd.
// MIT License


#ifndef TINY_DETAIL_AUTO_SENSE_HPP_
#define TINY_DETAIL_AUTO_SENSE_HPP_

#if defined (ARDUINO_SAM_DUE) || defined (ARDUINO_ARCH_SAM)
# define TINY_ARDUINO_DUE
#elif defined (ARDUINO_ARCH_AVR) || defined (ARDUINO_AVR_MEGA2560)
# define TINY_ARDUINO_MEGA
# else
# error "Can't detect platform we are doing!"
#endif // TINY_DETAIL_AUTO_SENSE_HPP_

#endif // TINY_DETAIL_AUTO_SENSE_HPP_
