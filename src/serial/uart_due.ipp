// Arduino async serial port library with nine data bits support.
//
// 2015, (c) Gk Ltd.
// MIT License


#include <tiny/serial/uart_due.hpp>

namespace tiny
{

namespace io
{

template <typename UartT>
inline void call_irq_handler(UartT& uart)
{
  uart.handle_irq();
}

} // namespace io

} // namespace tiny

//////////////////////////////////////////////////////////////////////////
// Serial 0, use USART2 interrupts for arduino due (sam3x8e)

#ifdef TINY_HAS_HWSERIAL0
void USART2_Handler(void)
{
  tiny::io::call_irq_handler(tiny::io::serial0());
}
# if (TINY_HAS_HWSERIAL0 == 9)
tiny::io::extended_uart& tiny::io::serial0(void)
{
  return extended_port2::instance();
}
# else
tiny::io::usual_uart& tiny::io::serial0(void)
{
  return usual_port2::instance();
}
# endif // TINY_HAS_HWSERIAL0 == 9
#endif // TINY_HAS_HWSERIAL0

//////////////////////////////////////////////////////////////////////////
// Serial 1, use USART0

#ifdef TINY_HAS_HWSERIAL1
void USART0_Handler(void)
{
  tiny::io::call_irq_handler(tiny::io::serial1());
}
# if (TINY_HAS_HWSERIAL1 == 9)
tiny::io::extended_uart& tiny::io::serial1(void)
{
  return extended_port0::instance(); // use USART0
}
# else
tiny::io::usual_uart& tiny::io::serial1(void)
{
  return usual_port0::instance(); // use USART0
}
# endif // TINY_HAS_HWSERIAL1 == 9
#endif // TINY_HAS_HWSERIAL1

//////////////////////////////////////////////////////////////////////////
// Serial 2, use USART1

#ifdef TINY_HAS_HWSERIAL2

void USART1_Handler(void)
{
  tiny::io::call_irq_handler(tiny::io::serial2());
}

# if (TINY_HAS_HWSERIAL2 == 9)
tiny::io::extended_uart& tiny::io::serial2(void)
{
  return extended_port1::instance();
}
# else
tiny::io::usual_uart& tiny::io::serial2(void)
{
  return usual_port1::instance();
}
# endif // TINY_HAS_HWSERIAL2 == 9
#endif // TINY_HAS_HWSERIAL2

//////////////////////////////////////////////////////////////////////////
// Serial 3, use USART3

#ifdef TINY_HAS_HWSERIAL3

void USART3_Handler(void)
{
  tiny::io::call_irq_handler(tiny::io::serial3());
}

# if (TINY_HAS_HWSERIAL3 == 9)
tiny::io::extended_uart& tiny::io::serial3(void)
{
  return extended_port3::instance();
}
# else
tiny::io::usual_uart& tiny::io::serial3(void)
{
  return usual_port3::instance();
}
# endif // TINY_HAS_HWSERIAL3 == 9
#endif // TINY_HAS_HWSERIAL3

