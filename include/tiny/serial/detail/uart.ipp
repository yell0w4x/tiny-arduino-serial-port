// Arduino async serial port library with nine data bits support.
//
// 2015, (c) Gk Ltd.
// MIT License


#ifndef TINY_SERIAL_UART_ARDUINO_MEGA_HPP_
#	error "tiny/detial/uart.ipp is not for direct include!"
#endif // TINY_SERIAL_UART_ARDUINO_MEGA_HPP_

namespace detail
{

/** Generic instance factory declaration. */
template <port_kind Kind, port_num Num> inline basic_uart<Kind>& uart_instance(void);

/** Returns a reference to uart0, 8bit max. */
template <> inline basic_uart<port_kind::usual>& uart_instance<port_kind::usual, port_num::com0>(void)
{
#if defined(UBRRH) && defined(UBRRL)
	static basic_uart<port_kind::usual> port(iocs_registers(&UBRRH, &UBRRL, &UCSRA, &UCSRB, &UCSRC, &UDR));
#else
	static basic_uart<port_kind::usual> port(iocs_registers(&UBRR0H, &UBRR0L, &UCSR0A, &UCSR0B, &UCSR0C, &UDR0));
#endif

	return port;
}

/** Returns a reference to uart1, 8bit max. */
template <> inline basic_uart<port_kind::usual>& uart_instance<port_kind::usual, port_num::com1>(void)
{
	static basic_uart<port_kind::usual> port(iocs_registers(&UBRR1H, &UBRR1L, &UCSR1A, &UCSR1B, &UCSR1C, &UDR1));

	return port;
}

/** Returns a reference to uart2, 8bit max. */
template <> inline basic_uart<port_kind::usual>& uart_instance<port_kind::usual, port_num::com2>(void)
{
	static basic_uart<port_kind::usual> port(iocs_registers(&UBRR2H, &UBRR2L, &UCSR2A, &UCSR2B, &UCSR2C, &UDR2));

	return port;
}

/** Returns a reference to uart3, 8bit max. */
template <> inline basic_uart<port_kind::usual>& uart_instance<port_kind::usual, port_num::com3>(void)
{
	static basic_uart<port_kind::usual> port(iocs_registers(&UBRR3H, &UBRR3L, &UCSR3A, &UCSR3B, &UCSR3C, &UDR3));

	return port;
}

/** Returns a reference to uart0, 9bit max. */
template <> inline basic_uart<port_kind::extended>& uart_instance<port_kind::extended, port_num::com0>(void)
{
#if defined(UBRRH) && defined(UBRRL)
	static basic_uart<port_kind::extended> port(iocs_registers(&UBRRH, &UBRRL, &UCSRA, &UCSRB, &UCSRC, &UDR));
#else
	static basic_uart<port_kind::extended> port(iocs_registers(&UBRR0H, &UBRR0L, &UCSR0A, &UCSR0B, &UCSR0C, &UDR0));
#endif

	return port;
}

/** Returns a reference to uart1, 9bit max. */
template <> inline basic_uart<port_kind::extended>& uart_instance<port_kind::extended, port_num::com1>(void)
{
	static basic_uart<port_kind::extended> port(iocs_registers(&UBRR1H, &UBRR1L, &UCSR1A, &UCSR1B, &UCSR1C, &UDR1));

	return port;
}

/** Returns a reference to uart2, 9bit max. */
template <> inline basic_uart<port_kind::extended>& uart_instance<port_kind::extended, port_num::com2>(void)
{
	static basic_uart<port_kind::extended> port(iocs_registers(&UBRR2H, &UBRR2L, &UCSR2A, &UCSR2B, &UCSR2C, &UDR2));

	return port;
}

/** Returns a reference to uart3, 9bit max. */
template <> inline basic_uart<port_kind::extended>& uart_instance<port_kind::extended, port_num::com3>(void)
{
	static basic_uart<port_kind::extended> port(iocs_registers(&UBRR3H, &UBRR3L, &UCSR3A, &UCSR3B, &UCSR3C, &UDR3));

	return port;
}

} // namespace detail
