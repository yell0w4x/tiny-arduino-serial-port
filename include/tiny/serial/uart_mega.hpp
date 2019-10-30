// Arduino async serial port library with nine data bits support.
//
// 2015, (c) Gk Ltd.
// MIT License

#ifndef TINY_SERIAL_UART_ARDUINO_MEGA_HPP_
#define TINY_SERIAL_UART_ARDUINO_MEGA_HPP_

#include <tiny/serial/detail/uart_defs.hpp>
#include <tiny/serial/detail/defs.hpp>

#include <tiny/container.hpp>
#include <tiny/basic.hpp>

#include <avr/io.h>

#include <inttypes.h>

/** Library root namespace. */
namespace tiny
{

/** IO Library root namespace. */
namespace io
{

/** The type of the uart. */
enum class port_kind
{
  usual,   /**< Usual com port.*/
  extended /**< 9bit supporting uart.*/
};

/** Comport number. */
enum class port_num { com0, com1, com2, com3 };

/** Port type traits, just a generic declaration. */
template <port_kind> struct port_kind_traits;

/** Usual variant, not more 8 bits support. */
template <>
struct port_kind_traits<port_kind::usual>
{
  /** Current port kind. */
  enum { kind_of_port = static_cast<unsigned int>(port_kind::usual) };

	/** The octet_type to be used. */
	typedef unsigned char octet_type;

  /** Port configuration. */
  enum class config
  {
    _5n1 = 0x00, _6n1 = 0x02, _7n1 = 0x04, _8n1 = 0x06,
    _5n2 = 0x08, _6n2 = 0x0a, _7n2 = 0x0c, _8n2 = 0x0e,
    _5e1 = 0x20, _6e1 = 0x22, _7e1 = 0x24, _8e1 = 0x26,
    _5e2 = 0x28, _6e2 = 0x2a, _7e2 = 0x2c, _8e2 = 0x2e,
    _5o1 = 0x30, _6o1 = 0x32, _7o1 = 0x34, _8o1 = 0x36,
    _5o2 = 0x38, _6o2 = 0x3a, _7o2 = 0x3c, _8o2 = 0x3e,
  };
};

/** Extended variant, 9 bits support. */
template <>
struct port_kind_traits<port_kind::extended>
{
  /** Current port kind. */
  enum { kind_of_port = static_cast<unsigned int>(port_kind::extended) };

  /** The octet_type to be used. */
  typedef unsigned short octet_type;

  /** Port configuration. */
  enum class config
  {
    _5n1 = 0x00, _6n1 = 0x02, _7n1 = 0x04, _8n1 = 0x06, _9n1 = 0x106,
    _5n2 = 0x08, _6n2 = 0x0a, _7n2 = 0x0c, _8n2 = 0x0e, _9n2 = 0x10e,
    _5e1 = 0x20, _6e1 = 0x22, _7e1 = 0x24, _8e1 = 0x26, _9e1 = 0x126,
    _5e2 = 0x28, _6e2 = 0x2a, _7e2 = 0x2c, _8e2 = 0x2e, _9e2 = 0x12e,
    _5o1 = 0x30, _6o1 = 0x32, _7o1 = 0x34, _8o1 = 0x36, _9o1 = 0x136,
    _5o2 = 0x38, _6o2 = 0x3a, _7o2 = 0x3c, _8o2 = 0x3e, _9o2 = 0x13e
  };
};

/** Usual port traits type. */
typedef port_kind_traits<port_kind::usual> usual_port_traits;

/** Extended port traits type. */
typedef port_kind_traits<port_kind::extended> extended_port_traits;

/** Baud rate constants. */
enum // baud_rate // fixme: check if conflicts with the open(buad_rate) formal arg name
{
  br_110      = 110,
  br_300      = 300,
  br_600      = 600,
  br_1200     = 1200,
  br_2400     = 2400,
  br_4800     = 4800,
  br_9600     = 9600,
  br_8738     = 8738,
  br_19200    = 19200,
  br_38400    = 38400,
  br_57600    = 57600,
  br_115200   = 115200,
  br_128000   = 128000,
  br_256000   = 256000
};

/** Uart i/o control status registers bundle. */
struct iocs_registers
{
    iocs_registers(register_ptr ubrrh,
            register_ptr ubrrl,
            register_ptr ucsra,
            register_ptr ucsrb,
            register_ptr ucsrc,
            register_ptr udr):
     ubrrh(ubrrh), ubrrl(ubrrl), ucsra(ucsra), ucsrb(ucsrb), ucsrc(ucsrc), udr(udr)
  {
    // empty
  }

  register_ptr ubrrh, ubrrl, ucsra, ucsrb, ucsrc, udr;
};

#ifndef TINY_SERIAL_DEF_BUF_SIZE
# define TINY_SERIAL_DEF_BUF_SIZE 16
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
 *  @tparam PortKindTraits Port kind traits.
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

//  /** Port kind. */
//  enum { kind_of_port = kind_traits_type::kind_of_port };

public:
  /** Creates an uart. */
  basic_uart(const iocs_registers& regs):
    _regs(regs),
    _written(false),
    _is_9_bits(false)
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
  void open(unsigned long baud_rate = br_9600, config_type config = config_type::_8n1)
  {
    _written = false;
    // baud rate settings
    const unsigned short ubrr = (F_CPU / (16 * baud_rate)) - 1;
    *_regs.ubrrh              = ubrr >> 8 & 0xff;
    *_regs.ubrrl              = ubrr & 0xff;

    unsigned short tmp_conf = static_cast<unsigned short>(config);
    //set the data bits, parity, and stop bits
 #if defined(__AVR_ATmega8__)
    tmp_conf |= 0x80; // select UCSRC register (shared with UBRRH)
 #endif

    close();

    _is_9_bits = (tmp_conf & 0x100) != 0;
    if (_is_9_bits)
    {
      set_bit(_regs.ucsrb, UCSZ2);
    }

    *_regs.ucsrc = tmp_conf & 0xff;

    set_bit(_regs.ucsrb, RXEN);
    set_bit(_regs.ucsrb, TXEN);
    set_bit(_regs.ucsrb, RXCIE);
    //clear_bit(_regs.ucsrb, UDRIE); // disable DR empty interrupt
  }

  /** Closes port. */
  void close(void)
  {
    *_regs.ucsrb = 0;
    _rx_buffer.clear();
    _tx_buffer.clear();
  }

  /** Whether port opened. */
  bool opened(void) const
  {
    return is_bit(_regs.ucsrb, RXEN) || is_bit(_regs.ucsrb, TXEN);
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
    // If the buffer and the data register is empty, just write the byte
    // to the data register and be done. This shortcut helps
    // significantly improve the effective datarate at high (>
    // 500kbit/s) bitrates, where interrupt overhead becomes a slowdown.
    tx_lock lock(this);
    if (_tx_buffer.empty() && can_write())
    {
      // fixme: 9bit resolve statically
      write_port(octet);
      set_bit(_regs.ucsra, TXC0);
      return true;
    }

    // fixme: If interrupts disabled it won't work

    // We don't wait for the room in the buffer (unlike original code)
    // and just returns 0 (zero). If client would like to wait
    // it can do it by itself using the loop: while (!async_write(x));

    if (!_tx_buffer.can_push()) { return false; }

    _tx_buffer.push(octet);
    _written = true;

    return true;
  }

  /** Returns currently configured stop bits. */
  size_t stop_bits(void) const
  {
    return int(is_bit(_regs.ucsrc, USBS)) + 1;
  }

  /** Returns currently set parity mode. */
  //parity_t parity(void) const {}

  /** Returns the data bits currently set. */
  size_t data_bits(void) const
  {
    return (*_regs.ucsrc & (mask(UCSZ0) | mask(UCSZ1)))
      | (*_regs.ucsrb & mask(UCSZ2)) + 5;
  }

//////////////////////////////////////////////////////////////////////////
// private stuff

private:
  typedef queue<octet_type, buffer_size> queue_type;
  typedef basic_uart<Kind, buffer_size, kind_traits_type> this_type;

private:
  basic_uart(const this_type&); // inhibit copy
  this_type& operator=(const this_type&);

private:
  /** Returns registers bundle associated with the uart. */
  const iocs_registers& registers(void) const { return _regs; }

  /** Whether receiver available for read. */
  bool can_read(void) const
  {
    //UCSRA & 1 << RXC
    return is_bit(_regs.ucsra, RXC);
  }

  /** Whether transmitter available for write. */
  bool can_write(void) const
  {
    // UCSRA & 1 << UDRE
    return is_bit(_regs.ucsra, UDRE);
  }

  //-----------------------------------------------------------------------------
  inline void write_octet(octet_type octet) const
  {
    *_regs.udr = octet;
  }

  //-----------------------------------------------------------------------------
  inline octet_type read_octet(void) const
  {
    return *_regs.udr;
  }

  //-----------------------------------------------------------------------------
  inline void write_ninth_bit(bool value) const
  {
    set_bit(_regs.ucsrb, TXB8, value);
  }

  //-----------------------------------------------------------------------------
  inline bool read_ninth_bit(void) const
  {
    return is_bit(_regs.ucsrb, RXB8);
  }

  //-----------------------------------------------------------------------------
  inline octet_type read_ninetet(void) const
  {
    const bool n           = read_ninth_bit();
    const octet_type octet = read_octet();

    if (!n) { return octet; }

    return octet | mask<octet_type>(8);
  }

  //-----------------------------------------------------------------------------
  inline void write_ninetet(octet_type ninetet) const
  {
    write_ninth_bit(ninetet & 0x100);
    write_octet(ninetet & 0xff);
  }

  //-----------------------------------------------------------------------------
  inline octet_type read_port(void) const
  {
    return _is_9_bits? read_ninetet(): read_octet();
  }

  //-----------------------------------------------------------------------------
  inline void write_port(octet_type word) const
  {
    _is_9_bits? write_ninetet(word): write_octet(word);
  }

  //-----------------------------------------------------------------------------
  inline void enable_rx_int(bool state = true) const
  {
    set_bit(_regs.ucsrb, RXCIE, state);
  }

  //-----------------------------------------------------------------------------
  inline void disable_rx_int(void) const
  {
    enable_rx_int(false);
  }

  //-----------------------------------------------------------------------------
  // enables/disables tx complete interrupt
  inline void enable_tx_int(bool state = true) const
  {
    set_bit(_regs.ucsrb, UDRIE, state);
  }

  //-----------------------------------------------------------------------------
  inline void disable_tx_int(void) const
  {
    enable_tx_int(false);
  }

  //-----------------------------------------------------------------------------
  inline bool is_parity_ok(void) const
  {
    return !is_bit(_regs.ucsra, UPE0);
  }

  //-----------------------------------------------------------------------------
  // interrupt handlers
  void handle_rx_complete_irq(void)
  {
    // first check for parity error
    if (is_parity_ok())
    {
      // read after
      const octet_type c = read_port();
      // No Parity error, read byte and store it in the buffer if there is room
      _rx_buffer.push(c);
    } else
    {
      // discard byte if parity error
      read_port();
    }
  }

  //-----------------------------------------------------------------------------
  void handle_tx_udr_empty_irq(void)
  {
    // If interrupts are enabled, there must be more data in the output
    // buffer. Send the next byte.
    assert(!_tx_buffer.empty() && " - Tx buffer can't be empty!");

    //if (_tx_buffer.empty()) { return; }

    write_port(_tx_buffer.pop());

    // clear the TXC bit -- "can be cleared by writing a one to its bit
    // location". This makes sure flush() won't return until the bytes
    // actually got written
    clear_bit(_regs.ucsra, TXC);

    if (_tx_buffer.empty())
    {
      // Buffer empty, so disable interrupts
      disable_tx_int();
    }
  }

// original declaration

//  extern "C" void __vector_25 (void) __attribute__ ((signal,used, externally_visible));
//  void __vector_25 (void)
//  {
//  }

//  static void __vector_25 (void) __attribute__ ((signal, used, externally_visible))
//  {
//    typedef basic_uart<Kind, BufferSize, PortKindTraitsT> this_type;
//    this_type* thiz = 0;
//
//    thiz->handle_rx_complete_irq();
//  }

//  template <port_num PortNum>
//  static void vector_25(void) __attribute__ ((signal, used, externally_visible));

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
  template <typename UartT> friend inline void call_rx_handler(UartT& uart);
  template <typename UartT> friend inline void call_tx_handler(UartT& uart);

private:
  iocs_registers _regs;
  bool _written; // fixme: remove written
  bool _is_9_bits; // fixme: resolve statically
  queue_type _rx_buffer;
  queue_type _tx_buffer;
};

/** Usual com port type declaration. */
typedef basic_uart<port_kind::usual> usual_uart;

/** Usual com port type declaration. */
typedef basic_uart<port_kind::extended> extended_uart;

namespace detail
{

// forward for eclipse syntax parser
/** Generic instance factory declaration. */
template <port_kind Kind, port_num Num> inline basic_uart<Kind>& uart_instance(void);

} // namespace detail

#include <tiny/serial/detail/uart.ipp>

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
typedef com_port<port_kind::usual, port_num::com0> usual_port0;
/** 8bit max, com1 type. */
typedef com_port<port_kind::usual, port_num::com1> usual_port1;
/** 8bit max, com2 type. */
typedef com_port<port_kind::usual, port_num::com2> usual_port2;
/** 8bit max, com3 type. */
typedef com_port<port_kind::usual, port_num::com3> usual_port3;

/** 9bit max, com0 type. */
typedef com_port<port_kind::extended, port_num::com0> extended_port0;
/** 9bit max, com1 type. */
typedef com_port<port_kind::extended, port_num::com1> extended_port1;
/** 9bit max, com2 type. */
typedef com_port<port_kind::extended, port_num::com2> extended_port2;
/** 9bit max, com3 type. */
typedef com_port<port_kind::extended, port_num::com3> extended_port3;

// Serial 0
#ifdef TINY_HAS_HWSERIAL0
# if !defined(UBRRH) && !defined(UBRR0H)
#   error "It seems there is no hardware uart0 available"
# endif // !defined(UBRRH) && !defined(UBRR0H)

# if (TINY_HAS_HWSERIAL0 == 9)
  extended_uart& serial0(void);
# else
  usual_uart& serial0(void);
# endif // TINY_HAS_HWSERIAL0 == 9
#endif // TINY_HAS_HWSERIAL0

// Serial 1
#ifdef TINY_HAS_HWSERIAL1
# if !defined(UBRR1H)
#   error "It seems there is no hardware uart1 available"
# endif // !defined(UBRR1H)

# if TINY_HAS_HWSERIAL1 == 9
  extended_uart& serial1(void);
# else
  usual_uart& serial1(void);
# endif // TINY_HAS_HWSERIAL1 == 9
#endif // TINY_HAS_HWSERIAL1

// Serial 2
#ifdef TINY_HAS_HWSERIAL2
# if !defined(UBRR2H)
#   error "It seems there is no hardware uart2 available"
# endif // !defined(UBRR2H)

# if TINY_HAS_HWSERIAL2 == 9
  extended_uart& serial2(void);
# else
  usual_uart& serial2(void);
# endif // TINY_HAS_HWSERIAL2 == 9
#endif // TINY_HAS_HWSERIAL2

// Serial 3
#ifdef TINY_HAS_HWSERIAL3
# if !defined(UBRR3H)
#   error "It seems there is no hardware uart3 available"
# endif // !defined(UBRR3H)

# if TINY_HAS_HWSERIAL3 == 9
  extended_uart& serial3(void);
# else
  usual_uart& serial3(void);
# endif // TINY_HAS_HWSERIAL3 == 9
#endif // TINY_HAS_HWSERIAL3

} // namespace io

} // namespace tiny

//extern void serialEventRun(void) __attribute__((weak));

#endif // TINY_SERIAL_UART_ARDUINO_MEGA_HPP_
