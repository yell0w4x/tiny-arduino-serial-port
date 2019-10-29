// Arduino async serial port library with nine data bits support.
//
// 2015, (c) Gk Ltd.
// MIT License


#ifndef TINY_SERIAL_H_
#define TINY_SERIAL_H_

namespace tiny
{

enum class baud_rate
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

template <typename octet_type>
struct serial
{
  virtual void open(baud_rate baud) = 0;
  virtual size_t available() const = 0;
  virtual octet_type read() = 0;
  virtual void write(octet_type b) = 0;
};

using serial8b = tiny::serial<uint8_t>;
using serial9b = tiny::serial<uint16_t>;

#ifdef GMOCK_INCLUDE_GMOCK_GMOCK_H_

template <typename octet_type>
struct mock_serial : serial<octet_type>
{
  MOCK_METHOD1(open, void(baud_rate baud));
  MOCK_CONST_METHOD0(available, size_t());
  MOCK_METHOD0_T(read, octet_type());
  MOCK_METHOD1_T(write, void(octet_type b));
};

using mock_serial8b = mock_serial<uint8_t>;
using mock_serial9b = mock_serial<uint16_t>;

#endif // #ifdef GMOCK_INCLUDE_GMOCK_GMOCK_H_

} // namespace tiny

#endif /* TINY_SERIAL_H_ */
