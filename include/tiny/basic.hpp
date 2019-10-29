// Arduino async serial port library with nine data bits support.
//
// 2015, (c) Gk Ltd.
// MIT License


#ifndef TINY_BASIC_HPP_
#define TINY_BASIC_HPP_

#include <tiny/detail/auto_sense.hpp>

#include <iterator>
#include <bitset>

#include <stdint.h>

namespace tiny
{

#ifdef bit
# undef bit
#endif // bit

#ifdef TINY_ARDUINO_MEGA
//# include <avr/io.h>
typedef uint8_t reg_type;
#elif defined(TINY_ARDUINO_DUE)
//# include <chip.h>
typedef uint32_t reg_type;
#endif // TINY_ARDUINO_MEGA

/** Control and status register type. */
typedef volatile reg_type register_type;

/** Pointer to control and status register type. */
typedef register_type* /*const*/ register_ptr;

/** The size of the register in bits. */
enum { register_width = sizeof(register_type) * 8 };

/** The type representing register bits. */
typedef std::bitset<register_width> register_bits_type;

/** Returns the mask for the given bit no. */
template <typename ResultT>
inline ResultT mask(size_t pos) { return static_cast<ResultT>(1 << pos); }

/** Returns the mask for the given bit no. */
inline register_type mask(size_t pos) { return mask<register_type>(pos); }

#ifdef TINY_ARDUINO_MEGA

/** Reads the register bit.
 *
 *  @param r Register address.
 *  @param pos Position of the bit where 0 is lsb.
 *  @return r & (1 << bit_pos)
 */
inline size_t bit(register_ptr r, size_t pos)
{
	return *r & (1 << pos);
}

/** Reads the register bit.
 *
 *  @param r Register address.
 *  @param pos Position of the bit where 0 is lsb.
 *  @return r & (1 << bit_pos)
 */
inline size_t bit(register_type r, size_t pos)
{
  return r & (1 << pos);
}

/** Tests whether bit is set or clear.
 *
 *  @param r Register address.
 *  @param pos Position of the bit where 0 is lsb.
 *  @return True if set, false if clear.
 */
template <typename T>
inline bool is_bit(T r, size_t pos)
{
	return bit(r, pos) != 0;
}

/** Sets the register bit. */
inline void set_bit(register_ptr r, size_t pos)
{
	*r |= mask(pos);
}

/** Sets the register bit. */
inline void set_bit(register_type& r, size_t pos)
{
  r |= mask(pos);
}

/** Clears the register bit. */
inline void clear_bit(register_ptr r, size_t pos)
{
	*r &= ~mask(pos);
}

/** Clears the register bit. */
inline void clear_bit(register_type& r, size_t pos)
{
  r &= ~mask(pos);
}

/** Sets the register bit. */
template <typename T>
inline void set_bit(T& r, size_t pos, bool value)
{
	if (value) { set_bit(r, pos); } else { clear_bit(r, pos); }
}

/** Returns the value of bits specified. */
inline size_t bits_value(register_ptr r, const register_bits_type& mask)
{
	register_type msk = static_cast<register_type>(mask.to_ulong());
	size_t v 					= *r & msk;

	for (; msk && (msk & 1) == 0; msk >>= 1) { v >>= 1; }

	return v;
}

/** Returns the value of bits specified. */
inline size_t bits_value(register_type r, const register_bits_type& mask)
{
  register_type msk = static_cast<register_type>(mask.to_ulong());
  size_t v          = r & msk;

  for (; msk && (msk & 1) == 0; msk >>= 1) { v >>= 1; }

  return v;
}

#elif defined(TINY_ARDUINO_DUE)

/** Reads the register bit.
 *
 *  @param r Register address.
 *  @param pos Position of the bit where 0 is lsb.
 *  @return r & (1 << bit_pos)
 */
inline size_t bit(register_type r, register_type mask)
{
  return r & mask;
}

/** Tests whether bit is set or clear.
 *
 *  @param r Register address.
 *  @param pos Position of the bit where 0 is lsb.
 *  @return True if set, false if clear.
 */
template <typename T>
inline bool is_bit(T r, register_type mask)
{
  return bit(r, mask) != 0;
}

/** Sets the register bit. */
inline void set_bit(register_type& r, register_type mask)
{
  r |= mask;
}

#endif // TINY_ARDUINO_MEGA

} // namespace tiny

#endif // TINY_BASIC_HPP_
