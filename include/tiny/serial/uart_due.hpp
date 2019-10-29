// Arduino async serial port library with nine data bits support.
//
// 2015, (c) Gk Ltd.
// MIT License

#ifndef TINY_SERIAL_UART_ARDUINO_DUE_HPP_
#define TINY_SERIAL_UART_ARDUINO_DUE_HPP_

#include <tiny/serial/detail/uart_due_defs.hpp>

#include <tiny/container.hpp>
#include <tiny/basic.hpp>
#include <tiny/serial.hpp>

#include <Arduino.h>

#include <chip.h>

#include <inttypes.h>

/** Library root namespace. */
namespace tiny
{

/** IO Library root namespace. */
namespace io
{

/** The type of the uart. */
enum port_kind
{
  usual,   /**< Usual com port.*/
  extended /**< 9bit supporting uart.*/
};

/** Comport number. */
enum port_num { com0, com1, com2, com3 };

/** Port type traits, just a generic declaration. */
template <port_kind> struct port_kind_traits;

/** Usual variant, not more 8 bits support. */
template <>
struct port_kind_traits<usual>
{
  /** Current port kind. */
  enum { kind_of_port = static_cast<unsigned int>(usual) };

  /** The octet_type to be used. */
  typedef unsigned char octet_type;

  /** Port configuration. */
  enum config
  {
    _5n1 = SERIAL_5N1, _6n1 = SERIAL_6N1, _7n1 = SERIAL_7N1, _8n1 = SERIAL_8N1,
    _5n2 = SERIAL_5N2, _6n2 = SERIAL_6N2, _7n2 = SERIAL_7N2, _8n2 = SERIAL_8N2,
    _5e1 = SERIAL_5E1, _6e1 = SERIAL_6E1, _7e1 = SERIAL_7E1, _8e1 = SERIAL_8E1,
    _5e2 = SERIAL_5E2, _6e2 = SERIAL_6E2, _7e2 = SERIAL_7E2, _8e2 = SERIAL_8E2,
    _5o1 = SERIAL_5O1, _6o1 = SERIAL_6O1, _7o1 = SERIAL_7O1, _8o1 = SERIAL_8O1,
    _5o2 = SERIAL_5O2, _6o2 = SERIAL_6O2, _7o2 = SERIAL_7O2, _8o2 = SERIAL_8O2
  };
};

/** Extended variant, 9 bits support. */
template <>
struct port_kind_traits<extended>
{
  /** Current port kind. */
  enum { kind_of_port = static_cast<unsigned int>(extended) };

  /** The octet_type to be used. */
  typedef unsigned short octet_type;

  /** Port configuration. */
  enum config
  {
    _5n1 = SERIAL_5N1, _6n1 = SERIAL_6N1, _7n1 = SERIAL_7N1, _8n1 = SERIAL_8N1, _9n1 = SERIAL_9N1,
    _5n2 = SERIAL_5N2, _6n2 = SERIAL_6N2, _7n2 = SERIAL_7N2, _8n2 = SERIAL_8N2, _9n2 = SERIAL_9N2,
    _5e1 = SERIAL_5E1, _6e1 = SERIAL_6E1, _7e1 = SERIAL_7E1, _8e1 = SERIAL_8E1, _9e1 = SERIAL_9E1,
    _5e2 = SERIAL_5E2, _6e2 = SERIAL_6E2, _7e2 = SERIAL_7E2, _8e2 = SERIAL_8E2, _9e2 = SERIAL_9E2,
    _5o1 = SERIAL_5O1, _6o1 = SERIAL_6O1, _7o1 = SERIAL_7O1, _8o1 = SERIAL_8O1, _9o1 = SERIAL_9O1,
    _5o2 = SERIAL_5O2, _6o2 = SERIAL_6O2, _7o2 = SERIAL_7O2, _8o2 = SERIAL_8O2, _9o2 = SERIAL_9O2
  };
};

/** Usual port traits type. */
typedef port_kind_traits<usual> usual_port_traits;

/** Extended port traits type. */
typedef port_kind_traits<extended> extended_port_traits;

/** Uart i/o control status registers bundle. */
typedef Usart iocs_registers;

/** Irq number type. */
typedef IRQn_Type irqn_type;

#ifndef TINY_SERIAL_DEF_BUF_SIZE
# define TINY_SERIAL_DEF_BUF_SIZE 32
#endif // TINY_SERIAL_DEF_BUF_SIZE

#define XSTRINGIFY(s) STRINGIFY(s)
#define STRINGIFY(s) #s

#ifdef __GNUG__
# pragma message "Tiny serial buffer size is " XSTRINGIFY(TINY_SERIAL_DEF_BUF_SIZE)
#endif // __GNUG__

/** Serial port.
 *
 *  @tparam Kind The type of port whether usual or extended see port_kind.
 *  @tparam BufferSize The size of the internal buffer. Use pow of two for
 *    optimizing indexing.
 *  @tparam PortKindTraits Prot kind traits.
 */
template<
  port_kind Kind,
  size_t BufferSize = TINY_SERIAL_DEF_BUF_SIZE,
  typename PortKindTraitsT = port_kind_traits<Kind> >
class basic_uart : public serial<typename port_kind_traits<Kind>::octet_type>
{
public:
  /** Port kind traits type. */
  typedef PortKindTraitsT kind_traits_type;

  /** Control and status register type. */
  typedef ::tiny::register_type register_type;

  /** Pointer to control and status register type. */
  typedef register_type* /*const*/ register_ptr;

  /** Buffer item type. */
  typedef typename kind_traits_type::octet_type octet_type;

  /** Possible port configuration. */
  typedef typename kind_traits_type::config config_type;

  /** Buffer size. */
  enum { buffer_size = BufferSize };

public:
  /** Creates an uart. */
  basic_uart(iocs_registers* regs, irqn_type irqn, uint32_t component_id):
    _regs(regs),
    _irqn(irqn),
    _comp_id(component_id)
  {
    // empty
  }

  void open(baud_rate baud) override
  {
    open(static_cast<unsigned long>(baud), kind_traits_type::_8n1);
  }

  /** Available bytes in receive cache. */
  size_t available(void) const override
  {
    rx_lock lock(const_cast<basic_uart*>(this));
    return _rx_buffer.size();
  }

  octet_type read(void) override
  {
    return async_read();
  }

  void write(octet_type b) override
  {
    while (!async_write(b));
  }

  /** Opens port.
   *
   *  @param baud_rate Baud rate.
   *  @param Remaining port configuration like stop bits, parity and data bits.
   */
  void open(unsigned long baud_rate = baud_rate::br_9600, /*config_type*/uint32_t config = kind_traits_type::_8n1)
  {
    close();
    // baud rate settings
    // Configure PMC
    pmc_enable_periph_clk(_comp_id);

    // Disable PDC channel
    _regs->US_PTCR = US_PTCR_RXTDIS | US_PTCR_TXTDIS ;

    // Configure mode
    _regs->US_MR = config;

    // Configure baudrate, asynchronous no oversampling
    _regs->US_BRGR = (SystemCoreClock / baud_rate) / 16 ;
//    USART_Configure(_regs, config, baud_rate, SystemCoreClock);

    // Configure interrupts
    _regs->US_IDR = 0xffffffff;
    _regs->US_IER = US_IER_RXRDY;// | US_IER_OVRE | US_IER_FRAME;

    // Enable UART interrupt in NVIC
    NVIC_EnableIRQ(_irqn);

    // Enable receiver and transmitter
    _regs->US_CR = US_CR_RXEN | US_CR_TXEN;
  }

  /** Closes port. */
  void close(void)
  {
    // Reset and disable receiver and transmitter
    _regs->US_CR = US_CR_RSTRX | US_CR_RSTTX | US_CR_RXDIS | US_CR_TXDIS;
    _rx_buffer.clear();
    _tx_buffer.clear();
  }

  /** Whether port opened. */
  bool opened(void) const
  {
    return (is_bit(_regs->US_CR, US_CR_RXEN) && !is_bit(_regs->US_CR, US_CR_RXDIS)) ||
        (is_bit(_regs->US_CR, US_CR_TXEN) && !is_bit(_regs->US_CR, US_CR_TXDIS));
  }

  /** Returns an octet from the queue and remove it if remove is true.
   *
   *  @param remove If true remove octet from queue else leave it.
   */
  octet_type async_read(bool remove = true)
  {
    rx_lock lock(this);
    if (_rx_buffer.empty()) { return 0; }

    const typename queue_type::value_type c = *_rx_buffer.front();
    if (remove) { _rx_buffer.pop(); }
    return c;
  }

  /** Writes an octet asynchronously.
   *
   *  @return If were no write operation due to buffer overflow return false
   *    else returns true.
   *
   *  Note that data is only pushed into the internal buffer and will be
   *  sent as soon as possible if interrupts allowed. But if they are disabled
   *  it's necessary to call it in a loop while it returns false.
   */
  bool async_write(octet_type octet)
  {
    tx_lock lock(this);
    if (_tx_buffer.empty() && can_write())
    {
      write_port(octet);
      return true;
    }

    if (!_tx_buffer.can_push()) { return false; }

    _tx_buffer.push(octet);

    return true;
  }

//  /** Returns currently configured stop bits. */
//  size_t stop_bits(void) const {}
//
//  /** Returns currently set parity mode. */
//  parity_t parity(void) const {}
//
//  /** Returns the data bits currently set. */
//  size_t data_bits(void) const {}

  /** Returns registers bundle associated with the uart. */
  const iocs_registers* registers(void) const { return _regs; }
  irqn_type irq_num(void) const { return _irqn; }
  uint32_t component_id(void) const { return _comp_id; }


//////////////////////////////////////////////////////////////////////////
// private stuff

private:
  typedef queue<octet_type, buffer_size> queue_type;
  typedef basic_uart<Kind, buffer_size, kind_traits_type> this_type;

private:
  basic_uart(const this_type&); // inhibit copy
  this_type& operator=(const this_type&);

private:
  /** Whether receiver available for read. */
  bool can_read(void) const
  {
    return is_bit(_regs->US_CSR, US_CSR_RXRDY);
  }

  /** Whether transmitter available for write. */
  bool can_write(void) const
  {
    return is_bit(_regs->US_CSR, US_CSR_TXRDY);
  }

  //-----------------------------------------------------------------------------
  inline void write_octet(octet_type octet) const
  {
    _regs->US_THR = octet;
  }

  //-----------------------------------------------------------------------------
  inline octet_type read_octet(void) const
  {
    return _regs->US_RHR;
  }

  //-----------------------------------------------------------------------------
  inline octet_type read_port(void) const
  {
    return read_octet();
  }

  //-----------------------------------------------------------------------------
  inline void write_port(octet_type word) const
  {
    write_octet(word);
  }

  //-----------------------------------------------------------------------------
  inline void enable_rx_int(void) /*const*/
  {
    set_bit(_regs->US_IER, US_IER_RXRDY);
  }

  //-----------------------------------------------------------------------------
  // enables/disables tx complete interrupt
  inline void enable_tx_int(void) /*const*/
  {
    set_bit(_regs->US_IER, US_IER_TXRDY);
  }

  //-----------------------------------------------------------------------------
  // fixme: check interrupt control
  inline void disable_rx_int(void) /*const*/
  {
    set_bit(_regs->US_IDR, US_IER_RXRDY);
  }

  //-----------------------------------------------------------------------------
  inline void disable_tx_int(void) /*const*/
  {
    set_bit(_regs->US_IDR, US_IER_TXRDY);
  }

  //-----------------------------------------------------------------------------
  // interrupt handlers
  void handle_rx_ready_irq(void)
  {
    // read after
    const octet_type c = read_port();
    // No Parity error, read byte and store it in the buffer if there is room
    _rx_buffer.push(c);
  }

  //-----------------------------------------------------------------------------
  void handle_tx_ready_irq(void)
  {
    if (_tx_buffer.empty())
    {
      // Buffer empty, so disable interrupts
      disable_tx_int();
    } else
    {
      write_port(_tx_buffer.pop());
    }
  }

  //-----------------------------------------------------------------------------
  void handle_irq(void)
  {
    if (can_read())
    {
      handle_rx_ready_irq();
    }

    if (can_write())
    {
      handle_tx_ready_irq();
    }
  }

private:
  ////////////////////////////////////////////////////////////////////////
  // classes
  struct rx_lock
  {
    rx_lock(basic_uart* uart): _uart(uart) { _uart->disable_rx_int(); }
    ~rx_lock(void) { _uart->enable_rx_int(); }

  private:
    basic_uart* _uart;
  };

  struct tx_lock
  {
    tx_lock(basic_uart* uart): _uart(uart) { _uart->disable_tx_int(); }
    ~tx_lock(void) { _uart->enable_tx_int(); }

  private:
    basic_uart* _uart;
  };

private:
  ////////////////////////////////////////////////////////////////////////
  // friends
  template <typename UartT> friend inline void call_irq_handler(UartT& uart);

private:
  iocs_registers* _regs;
  irqn_type _irqn;
  uint32_t _comp_id;
  queue_type _rx_buffer;
  queue_type _tx_buffer;
};

/** Usual com port type declaration. */
typedef basic_uart<usual> usual_uart;

/** Usual com port type declaration. */
typedef basic_uart<extended> extended_uart;

namespace detail
{

/** Generic instance factory declaration. */
template <port_kind Kind, port_num Num> inline basic_uart<Kind>& uart_instance(void);

// <=8 bit

/** Returns a reference to uart0, 8bit max. */
template <> inline basic_uart<usual>& uart_instance<usual, com0>(void)
{
  //static basic_uart<port_kind::usual> port(UART, UART_IRQn, ID_UART);
  static basic_uart<usual> port(USART0, USART0_IRQn, ID_USART0);

  return port;
}

/** Returns a reference to uart1, 8bit max. */
template <> inline basic_uart<usual>& uart_instance<usual, com1>(void)
{
  static basic_uart<usual> port(USART1, USART1_IRQn, ID_USART1);

  return port;
}

/** Returns a reference to uart2, 8bit max. */
template <> inline basic_uart<usual>& uart_instance<usual, com2>(void)
{
  static basic_uart<usual> port(USART2, USART2_IRQn, ID_USART2);

  return port;
}

/** Returns a reference to uart3, 8bit max. */
template <> inline basic_uart<usual>& uart_instance<usual, com3>(void)
{
  static basic_uart<usual> port(USART3, USART3_IRQn, ID_USART3);

  return port;
}

// 9 bit

/** Returns a reference to uart0, 9bit max. */
template <> inline basic_uart<extended>& uart_instance<extended, com0>(void)
{
  static basic_uart<extended> port(USART0, USART0_IRQn, ID_USART0);

  return port;
}

/** Returns a reference to uart1, 9bit max. */
template <> inline basic_uart<extended>& uart_instance<extended, com1>(void)
{
  static basic_uart<extended> port(USART1, USART1_IRQn, ID_USART1);

  return port;
}

/** Returns a reference to uart2, 9bit max. */
template <> inline basic_uart<extended>& uart_instance<extended, com2>(void)
{
  static basic_uart<extended> port(USART2, USART2_IRQn, ID_USART2);

  return port;
}

/** Returns a reference to uart3, 9bit max. */
template <> inline basic_uart<extended>& uart_instance<extended, com3>(void)
{
  static basic_uart<extended> port(USART3, USART3_IRQn, ID_USART3);

  return port;
}

} // namespace detail

/** Comport definition.
 *
 *  @tparam Kind The kind of the port.
 *  @tparam Num The number of the port.
 *
 *  We don't use __attribute__(weak) modifier, but template specialization
 *  to make code compiled and linked only if actually used.
 */
template <port_kind Kind, port_num Num>
struct com_port
{
  /** Port kind. */
  enum { kind_of_port = static_cast<unsigned int>(Kind) };

  /** Port number */
  enum { port_no = static_cast<unsigned int>(Num) };

  /** Uart type. */
  typedef basic_uart<Kind> uart_type;

  /** Return the instance of the uart. */
  static uart_type& instance(void)
  {
    return detail::uart_instance<Kind, Num>();
  }
};

/** 8bit max, com0 type. */
typedef com_port<usual, com0> usual_port0;
/** 8bit max, com1 type. */
typedef com_port<usual, com1> usual_port1;
/** 8bit max, com2 type. */
typedef com_port<usual, com2> usual_port2;
/** 8bit max, com3 type. */
typedef com_port<usual, com3> usual_port3;

/** 9bit max, com0 type. */
typedef com_port<extended, com0> extended_port0;
/** 9bit max, com1 type. */
typedef com_port<extended, com1> extended_port1;
/** 9bit max, com2 type. */
typedef com_port<extended, com2> extended_port2;
/** 9bit max, com3 type. */
typedef com_port<extended, com3> extended_port3;

// Serial 0 Arduino doesn't provide it at all, but we do.
// Note that not all of the SAM MCU have four ports
// For this port pins 52 and 11 on Arduino board are used
#ifdef TINY_HAS_HWSERIAL0
  inline void init_serial0(void)
  {
    const PinDescription desc = {
        // USART2 (serial0) all pins
        PIOB, PIO_PB20A_TXD2 | PIO_PB21A_RXD2, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_COMBO), NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER
    };

    PIO_Configure(desc.pPort, desc.ulPinType, desc.ulPin, desc.ulPinConfiguration);
  }

# if (TINY_HAS_HWSERIAL0 == 9)
  extended_uart& serial0(void);
# else
  usual_uart& serial0(void);
# endif // TINY_HAS_HWSERIAL0 == 9
#endif // TINY_HAS_HWSERIAL0

// Serial 1
#ifdef TINY_HAS_HWSERIAL1
# if TINY_HAS_HWSERIAL1 == 9
  extended_uart& serial1(void);
# else
  usual_uart& serial1(void);
# endif // TINY_HAS_HWSERIAL1 == 9
#endif // TINY_HAS_HWSERIAL1

// Serial 2
#ifdef TINY_HAS_HWSERIAL2
# if TINY_HAS_HWSERIAL2 == 9
  extended_uart& serial2(void);
# else
  usual_uart& serial2(void);
# endif // TINY_HAS_HWSERIAL2 == 9
#endif // TINY_HAS_HWSERIAL2

// Serial 3
#ifdef TINY_HAS_HWSERIAL3
# if TINY_HAS_HWSERIAL3 == 9
  extended_uart& serial3(void);
# else
  usual_uart& serial3(void);
# endif // TINY_HAS_HWSERIAL3 == 9
#endif // TINY_HAS_HWSERIAL3

} // namespace io

} // namespace tiny

#endif // TINY_SERIAL_UART_ARDUINO_DUE_HPP_
