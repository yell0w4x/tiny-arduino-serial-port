// Arduino async serial port library with nine data bits support.
//
// 2015, (c) Gk Ltd.
// MIT License


#ifndef TINY_SERIAL_UTILS_HPP_
#define TINY_SERIAL_UTILS_HPP_

#include <tiny/container.hpp>

#include <iterator>
#include <algorithm>

#include <cstddef>

/** Library root namespace. */
namespace tiny
{

/** IO Library root namespace. */
namespace io
{

/** Writes array of data into the port.
 *
 *  @tparam UartT Uart type.
 *  @param uart Uart instance.
 *  @param data Pointer to first element of the array
 *  @param size The Size of the array.
 *
 *  @return Returns the bytes number actually written.
 */
template <typename UartT, typename OctetT>
inline size_t async_write(UartT& uart, const OctetT* data, size_t size)
{
  for (size_t i = 0; i < size; ++i)
  {
    if (!uart.async_write(static_cast<typename UartT::octet_type>(data[i])))
    {
      return i;
    }
  }

  return size;
}

///** Writes array of data into the port.
// *
// *  @tparam UartT Uart type.
// *  @param uart Uart instance.
// *  @param data Pointer to first element of the array
// *  @param size The Size of the array.
// *
// *  @return Returns the bytes number actually written.
// */
//template <typename UartT>
//inline size_t async_write(UartT& uart,
//                          const typename UartT::octet_type* data,
//                          size_t size)
//{
//  return async_write(uart, data, size);
//
////  for (size_t i = 0; i < size; ++i)
////  {
////    if (!uart.async_write(data[i]))
////    {
////      return i;
////    }
////  }
////
////  return size;
//}

/** Writes array of data into the port.
 *
 *  @tparam UartT Uart type.
 *  @param uart Uart instance.
 *  @param data Pointer to first element of the array
 *  @param size The Size of the array.
 *
 *  @return Returns the bytes number actually written.
 */
template <typename UartT, typename OctetT, size_t Sz>
inline size_t async_write(UartT& uart,
                          const array<OctetT, Sz>& data)
{
  return async_write(uart, &*data.begin(), data.size);
}

/** Writes c-string into port. */
template <typename UartT>
inline size_t async_write(UartT& uart, const char* c_str)
{
  const char* p = c_str;
  for (; *p != 0; ++p)
  {
    typedef typename UartT::octet_type octet_type;

    if (!uart.async_write(static_cast<octet_type>(*p)))
    {
      return std::distance(c_str, p);
    }
  }

  return std::distance(c_str, p);
}

} // namespace io

} // namespace tiny

#endif // TINY_SERIAL_UTILS_HPP_
