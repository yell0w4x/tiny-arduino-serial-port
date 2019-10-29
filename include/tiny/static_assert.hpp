// Arduino async serial port library with nine data bits support.
//
// 2015, (c) Gk Ltd.
// MIT License


#ifndef TINY_STATIC_ASSERT_HPP_
#define TINY_STATIC_ASSERT_HPP_

/** Library root namespace.  */
namespace tiny
{

template <bool Value> struct static_assert;

template <> struct static_assert<true> { enum { value = 1 }; };

} // namespace tiny

/** Static assertion. */
#define STATIC_ASSERT(V) typedef tiny::static_assert<V> static_assert_typedef_;

#endif // TINY_STATIC_ASSERT_HPP_
