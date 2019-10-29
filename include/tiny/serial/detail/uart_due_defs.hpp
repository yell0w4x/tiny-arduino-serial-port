// Arduino async serial port library with nine data bits support.
//
// 2015, (c) Gk Ltd.
// MIT License


#ifndef TINY_SERIAL_DETAIL_UART_DUE_MACRO_HPP_
#define TINY_SERIAL_DETAIL_UART_DUE_MACRO_HPP_

#include <chip.h>

#define SERIAL_5N1 (US_MR_USART_MODE_NORMAL | \
                    US_MR_USCLKS_MCK | \
                    US_MR_CHRL_5_BIT | \
                    US_MR_PAR_NO | \
                    US_MR_NBSTOP_1_BIT | \
                    US_MR_CHMODE_NORMAL)

#define SERIAL_6N1 (US_MR_USART_MODE_NORMAL | \
                    US_MR_USCLKS_MCK | \
                    US_MR_CHRL_6_BIT | \
                    US_MR_PAR_NO | \
                    US_MR_NBSTOP_1_BIT | \
                    US_MR_CHMODE_NORMAL)

#define SERIAL_7N1 (US_MR_USART_MODE_NORMAL \
                    | US_MR_USCLKS_MCK | \
                    US_MR_CHRL_7_BIT | \
                    US_MR_PAR_NO | \
                    US_MR_NBSTOP_1_BIT | \
                    US_MR_CHMODE_NORMAL)

#define SERIAL_8N1 (US_MR_USART_MODE_NORMAL | \
                    US_MR_USCLKS_MCK | \
                    US_MR_CHRL_8_BIT | \
                    US_MR_PAR_NO | \
                    US_MR_NBSTOP_1_BIT | \
                    US_MR_CHMODE_NORMAL)

#define SERIAL_9N1 (US_MR_USART_MODE_NORMAL | \
                    US_MR_USCLKS_MCK | \
                    US_MR_MODE9 | \
                    US_MR_PAR_NO | \
                    US_MR_NBSTOP_1_BIT | \
                    US_MR_CHMODE_NORMAL)

#define SERIAL_5N2 (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_5_BIT | US_MR_PAR_NO | US_MR_NBSTOP_2_BIT | US_MR_CHMODE_NORMAL)
#define SERIAL_6N2 (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_6_BIT | US_MR_PAR_NO | US_MR_NBSTOP_2_BIT | US_MR_CHMODE_NORMAL)
#define SERIAL_7N2 (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_7_BIT | US_MR_PAR_NO | US_MR_NBSTOP_2_BIT | US_MR_CHMODE_NORMAL)
#define SERIAL_8N2 (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_8_BIT | US_MR_PAR_NO | US_MR_NBSTOP_2_BIT | US_MR_CHMODE_NORMAL)
#define SERIAL_9N2 (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_MODE9 | US_MR_PAR_NO | US_MR_NBSTOP_2_BIT | US_MR_CHMODE_NORMAL)

#define SERIAL_5E1 (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_5_BIT | US_MR_PAR_EVEN | US_MR_NBSTOP_1_BIT | US_MR_CHMODE_NORMAL)
#define SERIAL_6E1 (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_6_BIT | US_MR_PAR_EVEN | US_MR_NBSTOP_1_BIT | US_MR_CHMODE_NORMAL)
#define SERIAL_7E1 (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_7_BIT | US_MR_PAR_EVEN | US_MR_NBSTOP_1_BIT | US_MR_CHMODE_NORMAL)
#define SERIAL_8E1 (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_8_BIT | US_MR_PAR_EVEN | US_MR_NBSTOP_1_BIT | US_MR_CHMODE_NORMAL)
#define SERIAL_9E1 (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_MODE9 | US_MR_PAR_EVEN | US_MR_NBSTOP_1_BIT | US_MR_CHMODE_NORMAL)

#define SERIAL_5E2 (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_5_BIT | US_MR_PAR_EVEN | US_MR_NBSTOP_2_BIT | US_MR_CHMODE_NORMAL)
#define SERIAL_6E2 (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_6_BIT | US_MR_PAR_EVEN | US_MR_NBSTOP_2_BIT | US_MR_CHMODE_NORMAL)
#define SERIAL_7E2 (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_7_BIT | US_MR_PAR_EVEN | US_MR_NBSTOP_2_BIT | US_MR_CHMODE_NORMAL)
#define SERIAL_8E2 (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_8_BIT | US_MR_PAR_EVEN | US_MR_NBSTOP_2_BIT | US_MR_CHMODE_NORMAL)
#define SERIAL_9E2 (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_MODE9 | US_MR_PAR_EVEN | US_MR_NBSTOP_2_BIT | US_MR_CHMODE_NORMAL)

#define SERIAL_5O1 (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_5_BIT | US_MR_PAR_ODD | US_MR_NBSTOP_1_BIT | US_MR_CHMODE_NORMAL)
#define SERIAL_6O1 (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_6_BIT | US_MR_PAR_ODD | US_MR_NBSTOP_1_BIT | US_MR_CHMODE_NORMAL)
#define SERIAL_7O1 (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_7_BIT | US_MR_PAR_ODD | US_MR_NBSTOP_1_BIT | US_MR_CHMODE_NORMAL)
#define SERIAL_8O1 (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_8_BIT | US_MR_PAR_ODD | US_MR_NBSTOP_1_BIT | US_MR_CHMODE_NORMAL)
#define SERIAL_9O1 (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_MODE9 | US_MR_PAR_ODD | US_MR_NBSTOP_1_BIT | US_MR_CHMODE_NORMAL)

#define SERIAL_5O2 (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_5_BIT | US_MR_PAR_ODD | US_MR_NBSTOP_2_BIT | US_MR_CHMODE_NORMAL)
#define SERIAL_6O2 (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_6_BIT | US_MR_PAR_ODD | US_MR_NBSTOP_2_BIT | US_MR_CHMODE_NORMAL)
#define SERIAL_7O2 (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_7_BIT | US_MR_PAR_ODD | US_MR_NBSTOP_2_BIT | US_MR_CHMODE_NORMAL)
#define SERIAL_8O2 (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_8_BIT | US_MR_PAR_ODD | US_MR_NBSTOP_2_BIT | US_MR_CHMODE_NORMAL)
#define SERIAL_9O2 (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_MODE9 | US_MR_PAR_ODD | US_MR_NBSTOP_2_BIT | US_MR_CHMODE_NORMAL)

#endif // TINY_SERIAL_DETAIL_UART_DUE_MACRO_HPP_
