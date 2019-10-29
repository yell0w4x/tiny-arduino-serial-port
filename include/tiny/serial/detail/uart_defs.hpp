// Arduino async serial port library with nine data bits support.
//
// 2015, (c) Gk Ltd.
// MIT License


#ifndef TINY_SERIAL_DETAIL_UART_DEFS_HPP_
#define TINY_SERIAL_DETAIL_UART_DEFS_HPP_

#include <avr/io.h>

// fixme: Make all of used bits

// Check at compiletime that it is really ok to use the bit positions of
// UART0 for the other UARTs as well, in case these values ever get
// changed for future hardware.
#if defined(TXC1) && (TXC1 != TXC0 || RXEN1 != RXEN0 || RXCIE1 != RXCIE0 || \
		      UDRIE1 != UDRIE0 || U2X1 != U2X0 || UPE1 != UPE0 || \
		      UDRE1 != UDRE0)
#	error "Not all bit positions for UART1 are the same as for UART0"
#endif

#if defined(TXC2) && (TXC2 != TXC0 || RXEN2 != RXEN0 || RXCIE2 != RXCIE0 || \
		      UDRIE2 != UDRIE0 || U2X2 != U2X0 || UPE2 != UPE0 || \
		      UDRE2 != UDRE0)
#	error "Not all bit positions for UART2 are the same as for UART0"
#endif

#if defined(TXC3) && (TXC3 != TXC0 || RXEN3 != RXEN0 || RXCIE3 != RXCIE0 || \
		      UDRIE3 != UDRIE0 || U3X3 != U3X0 || UPE3 != UPE0 || \
		      UDRE3 != UDRE0)
#	error "Not all bit positions for UART3 are the same as for UART0"
#endif


// Ensure that the various bit positions we use are available with a 0
// postfix, so we can always use the values for UART0 for all UARTs. The
// alternative, passing the various values for each UART to the
// HardwareSerial constructor also works, but makes the code bigger and
// slower.
#if !defined(TXC0)
#	if defined(TXC)

// Some chips like ATmega8 don't have UPE, only PE. The other bits are
// named as expected.
#		if !defined(UPE) && defined(PE)
#			define UPE PE
#		endif

		// On ATmega8, the uart and its bits are not numbered, so there is no TXC0 etc.
		#define TXC0 TXC
		#define RXEN0 RXEN
		#define TXEN0 TXEN
		#define RXCIE0 RXCIE
		#define UDRIE0 UDRIE
		#define U2X0 U2X
		#define UPE0 UPE
		#define UDRE0 UDRE
#	elif defined(TXC1)
		// Some devices have uart1 but no uart0
		#define TXC0 TXC1
		#define RXEN0 RXEN1
		#define TXEN0 TXEN1
		#define RXCIE0 RXCIE1
		#define UDRIE0 UDRIE1
		#define U2X0 U2X1
		#define UPE0 UPE1
		#define UDRE0 UDRE1
#	else
		#error "It seems there is no UART: Can't find out"
#	endif // defined(TXC)
#endif // !defined TXC0

namespace tiny
{

enum
{
	RXCIE = RXCIE0,
	TXCIE = TXCIE0,
	UDRIE = UDRIE0,
	RXEN 	= RXEN0,
	TXEN 	= TXEN0,
	UPM0 	= UPM00,
	UPM1 	= UPM01,
	UCSZ2 = UCSZ02,
	UCSZ1 = UCSZ01,
	UCSZ0 = UCSZ00,
//	UBRRH = UBRR0H,
//	UBRRL = UBRR0L,
	USBS 	= USBS0,
	DOR 	= DOR0,
	FE 		= FE0,
	RXB8 	= RXB80,
	TXB8 	= TXB80,
	UDRE 	= UDRE0,
	RXC 	= RXC0,
	TXC 	= TXC0,
	UPE		= UPE0
};

} // namespace tiny

#endif // TINY_SERIAL_DETAIL_UART_DEFS_HPP_
