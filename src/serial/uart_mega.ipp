// Arduino async serial port library with nine data bits support.
//
// 2015, (c) Gk Ltd.
// MIT License


#include <tiny/serial/uart_mega.hpp>

namespace tiny
{

namespace io
{

template <typename UartT>
inline void call_rx_handler(UartT& uart)
{
  uart.handle_rx_complete_irq();
}

//------------------------------------------------------------------------
template <typename UartT>
inline void call_tx_handler(UartT& uart)
{
  uart.handle_tx_udr_empty_irq();
}

//template <>
//template <>
//void basic_uart<port_kind::usual,
//                16, port_kind_traits<port_kind::usual> >::vector_25<port_num::com0>(void)
//{
//  typedef basic_uart<port_kind::usual,
//      16, port_kind_traits<port_kind::usual> > this_type;
//
//  this_type* thiz = 0;
//
//  thiz->handle_rx_complete_irq();
//}

} // namespace io

} // namespace tiny

//////////////////////////////////////////////////////////////////////////
// Serial 0 interrupts for arduino mega

#if defined(TINY_HAS_HWSERIAL0)
#	if defined(USART_RX_vect)
		ISR(USART_RX_vect)
#	elif defined(USART0_RX_vect)
		ISR(USART0_RX_vect)
#	elif defined(USART_RXC_vect)
		ISR(USART_RXC_vect) // ATmega8
#	else
#   error "Can't define uart0 RX interrupt handler!"
#	endif
{
  tiny::io::call_rx_handler(tiny::io::serial0());
}

# if defined(UART0_UDRE_vect)
		ISR(UART0_UDRE_vect)
# elif defined(UART_UDRE_vect)
		ISR(UART_UDRE_vect)
# elif defined(USART0_UDRE_vect)
		ISR(USART0_UDRE_vect)
# elif defined(USART_UDRE_vect)
		ISR(USART_UDRE_vect)
# else
#   error "Can't define uart0 TX interrupt handler!"
# endif
{
  tiny::io::call_tx_handler(tiny::io::serial0());
}

# if (TINY_HAS_HWSERIAL0 == 9)
tiny::io::extended_uart& tiny::io::serial0(void)
{
  return extended_port0::instance();
}
# else
tiny::io::usual_uart& tiny::io::serial0(void)
{
  return usual_port0::instance();
}
# endif // TINY_HAS_HWSERIAL0 == 9
#endif // TINY_HAS_HWSERIAL0

//////////////////////////////////////////////////////////////////////////
// Serial 1

#ifdef TINY_HAS_HWSERIAL1
# if defined(UART1_RX_vect)
    ISR(UART1_RX_vect)
# elif defined(USART1_RX_vect)
    ISR(USART1_RX_vect)
# else
#   error "Can't define uart1 RX interrupt handler!"
# endif
{
  tiny::io::call_rx_handler(tiny::io::serial1());
}

# if defined(UART1_UDRE_vect)
    ISR(UART1_UDRE_vect)
# elif defined(USART1_UDRE_vect)
    ISR(USART1_UDRE_vect)
# else
#   error "Can't define uart1 TX interrupt handler!"
# endif
{
  tiny::io::call_tx_handler(tiny::io::serial1());
}

# if (TINY_HAS_HWSERIAL1 == 9)
tiny::io::extended_uart& tiny::io::serial1(void)
{
  return extended_port1::instance();
}
# else
tiny::io::usual_uart& tiny::io::serial1(void)
{
  return usual_port1::instance();
}
# endif // TINY_HAS_HWSERIAL1 == 9

//bool Serial1_available() {
//  return Serial1.available();
//}

#endif // TINY_HAS_HWSERIAL1

//////////////////////////////////////////////////////////////////////////
// Serial 2

#ifdef TINY_HAS_HWSERIAL2

ISR(USART2_RX_vect)
{
  tiny::io::call_rx_handler(tiny::io::serial2());
}

ISR(USART2_UDRE_vect)
{
  tiny::io::call_tx_handler(tiny::io::serial2());
}

# if (TINY_HAS_HWSERIAL2 == 9)
tiny::io::extended_uart& tiny::io::serial2(void)
{
  return extended_port2::instance();
}
# else
tiny::io::usual_uart& tiny::io::serial2(void)
{
  return usual_port2::instance();
}
# endif // TINY_HAS_HWSERIAL2 == 9
#endif // TINY_HAS_HWSERIAL2

//////////////////////////////////////////////////////////////////////////
// Serial 3

#ifdef TINY_HAS_HWSERIAL3

ISR(USART3_RX_vect)
{
  tiny::io::call_rx_handler(tiny::io::serial3());
}

ISR(USART3_UDRE_vect)
{
  tiny::io::call_tx_handler(tiny::io::serial3());
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

