// Arduino async serial port library with nine data bits support.
//
// 2015, (c) Gk Ltd.
// MIT License


#ifndef TINY_CONTAINER_HPP_
#define TINY_CONTAINER_HPP_

#include <iterator>
#include <algorithm>
#include <initializer_list>

#include <cstddef>
#include <cstdint>

#ifdef __ICCAVR__
# include <cassert>
#else
# include <assert.h>
#endif // __ICCAVR__

namespace tiny
{

/** Static array class template.
 *
 *  @note If possible use std::array instead.
 */
template <typename T, size_t Sz>
class array
{
public:
  /** The size of the array. */
  enum { size = Sz };

public:
  /** Iterator type. */
  typedef T* iterator;

  /** Constant iterator type. */
  typedef const T* const_iterator;

  /** Element reference type. */
  typedef T& reference;

  /** Constant element type reference. */
  typedef const T& const_reference;

  /** Element value type. */
  typedef T value_type;

  /** Element pointer type. */
  typedef T* pointer;

  /** Constant element pointer type. */
  typedef const T* const_pointer;

public:
  /** Creates an array having size n and initialized by default value.
   *
   *  @param value The value to initialize the array with.
   *  @param n The size of the array.
   */
#ifdef __ICCAVR__
  #pragma diag_suppress = Pe340 // refernece to temporary is used
#endif // __ICCAVR__
  explicit array(const_reference value = T(), size_t n = Sz)
  {
    for (size_t i = 0; i < Sz; ++i)
    {
      _array[i] = i < n? value: value_type();
    }
  }
#ifdef __ICCAVR__
  #pragma diag_default = Pe340
#endif // __ICCAVR__

  /** Creates an array from the sequence.
   *
   *  @param first Iterator that designates first element in the sequence.
   *  @param last Iterator to past the last element in the sequence.
   */
  template <typename IterT>
  array(IterT first, IterT last)
  {
    const size_t srcsz = std::distance(first, last);
    
#ifdef __ICCAVR__  
  #pragma diag_suppress = Pe236 // controlling expression is constant
#endif // __ICCAVR__  
    
    assert(srcsz <= Sz && "Array<T, sz>::Array - invalid source array size");
    
#ifdef __ICCAVR__  
  #pragma diag_default = Pe236
#endif // __ICCAVR__  

#ifdef _MSC_VER
  #pragma warning (push) 
  #pragma warning (disable : 4996) // Iterator check
#endif 

    std::copy(first, last, begin());

    if (srcsz < Sz)
    {
      for (size_t i = srcsz; i < Sz; ++i)
      {
        _array[i] = T();
      }
    }

#ifdef _MSC_VER
  #pragma warning (pop) 
#endif 
  }

  /** Initializer list ctor. 
   *  
   *  @param l List of values to copy to array.
   */
  array(const std::initializer_list<T>& l)
    : array(l.begin(), l.end())
  {
    // empty
  }

  /** Copy constructor.
   *
   *  @param other Other instance of an array of the same type.
   */
  array(const array<T, Sz>& other)
  {
    std::copy(other.begin(), other.end(), begin());
  }

public:
  /** Subscript operator that returns a reference to an element. */
  reference operator[](size_t i)
  {
#ifdef __ICCAVR__  
  #pragma diag_suppress = Pe236 // conrolling expression is constant
#endif // __ICCAVR__  

    assert(i < Sz && "Array<T, sz>::operator[] - index is out of bounds");

#ifdef __ICCAVR__  
  #pragma diag_default = Pe236
#endif // __ICCAVR__      
    
    return _array[i];
  }

  /** Subscript operator that returns a const reference to an element. */
  const_reference operator[](size_t i) const
  {
#ifdef __ICCAVR__  
  #pragma diag_suppress = Pe236 // conrolling expression is constant
#endif // __ICCAVR__  
    
    assert(i < Sz && "Array<T, sz>::operator[] - index is out of bounds");

#ifdef __ICCAVR__  
  #pragma diag_default = Pe236
#endif // __ICCAVR__      
    
    return _array[i];
  }

public:
  /** The same as subscript operator that returns a reference to an element. */
  reference at(size_t i)
  {
#ifdef __ICCAVR__  
  #pragma diag_suppress = Pe236 // conrolling expression is constant
#endif // __ICCAVR__ 
    
    assert(i < Sz && "Array<T, sz>::at - index is out of bounds");

#ifdef __ICCAVR__  
  #pragma diag_default = Pe236
#endif // __ICCAVR__      
    
    return _array[i];
  }

  /** The same as subscript operator that returns a const reference to an element. */
  const_reference at(size_t i) const
  {
#ifdef __ICCAVR__  
  #pragma diag_suppress = Pe236 // conrolling expression is constant
#endif // __ICCAVR__ 
    
    assert(i < Sz && "Array<T, sz>::at - index is out of bounds");

#ifdef __ICCAVR__  
  #pragma diag_default = Pe236
#endif // __ICCAVR__      
    
    return _array[i];
  }

public:
  /** Returns iterator to the first element. */
  iterator begin(void)
  {
    return _array;
  }

  /** Returns const iterator to the first element. */
  const_iterator begin(void) const
  {
    return _array;
  }

  /** Returns iterator to the past the last element. */
  iterator end(void)
  {
    return _array + Sz;
  }

  /** Returns const iterator to the past the last element. */
  const_iterator end(void) const
  {
    return _array + Sz;
  }

  /** Assigns a value to the array.
   *
   *  @param value An value to be assigned to every element in the array.
   */
  void assign(const T& val = T())
  {
    std::fill(begin(), end(), val);
  }

  /** Assigns a sequence to the array.
   *
   *  @param first Iterator that designates first element in the sequence.
   *  @param last Iterator to past the last element in the sequence.
   */
  template <typename IterT>
  void assign(IterT first, IterT last)
  {
    assert(std::distance(first, last) <= Sz &&
           "Array<T, sz>::assign - invalid source array size");

    std::copy(first, last, begin());
  }

  /** Assigns a sequence to the array.
   *
   *  Checks the room before copy and cut the tail if necessary.
   *
   *  @param first Iterator that designates first element in the sequence.
   *  @param last Iterator to past the last element in the sequence.
   */
  template <typename IterT>
  void safe_assign(IterT first, IterT last)
  {
    if (static_cast<size_t>(std::distance(first, last)) > Sz)
    {
      last = first + Sz;
    }

    std::copy(first, last, begin());
  }

  /** Returns a C string.
   *
   *  @note Just assigns zero to last element of the array and returns pointer
   *    to the first element.
   */
  const_pointer c_str(void) const
  {
    _array[Sz - 1] = 0;

    return _array;
  };

//////////////////////////////////////////////////////////////////////////
// private stuff

private:
  mutable T _array[Sz];
};

/** Array equality operator. */
template <typename T, size_t szl, typename U, size_t szr>
bool operator==(const array<T, szl> &l, const array<U, szr> &r)
{
  bool res = false;
  
  if (szl == szr)
  {
    res = true;
    
    for (size_t i = 0; i < szl; ++i)
    {
      if (l[i] != r[i])
      {
        res = false;
        break;
      }
    }
  }
       
  return res;
}

/** Array inequality operator. */
template <typename T, size_t szl, typename U, size_t szr>
bool operator!=(const array<T, szl> &l, const array<U, szr> &r)
{
  return !(l == r);  
}

/** Simple bitset.
 *
 *  @tparam sz The size of the bit set in bits.
 *
 *  @note If stl provides bits set use provided instead.
 *  @note LSB has 0 (zero) index.
 */
template <size_t Sz>
class bitset
{
public:
  /** Creates bit set.
   *
   *  @param bits Initial bits value.
   */
  explicit bitset(unsigned long bits = 0): _bits(bits) { /*empty*/ }
  
  /** Constructs bit set instance from other bit set instance type. */
  template <size_t OtherSize>
  explicit bitset(const bitset<OtherSize>& bits): _bits(bits.toulong()) { /*empty*/ }
  
public:
  /** Returns bit value by the given index.
   *
   *  @note LSB has 0 (zero) index.
   */
  bool get(size_t i) const
  {
    return i < Sz? static_cast<bool>(_bits >> i & 1): false;
  }

  /** Sets the value of the bit.
   *
   *  @param i Index of the bit.
   *  @param value New bit value.
   */
  void set(size_t i, bool value = true)
  {
    if (i < Sz)
    {
      value? _bits |= 1 << i: _bits &= ~(1 << i);
    }
  }
  
  /** Returns bit set packed to unsigned long. */
  unsigned long to_ulong(void) const { return _bits & 0xffffffff >> (sizeof(_bits) * 8 - Sz); }

  /** @deprecated Use assign instead. */
  void from_ulong(unsigned long bits) { assign(bits); }

  /** Assigned new value to bit set. */
  void assign(unsigned long bits) { _bits = bits; }
  
  /** Returns the size of the array. */
  inline size_t size(void) const { return Sz; }


//////////////////////////////////////////////////////////////////////////
// private stuff

private:
  uint32_t _bits;
};

template <size_t Sz>
bool operator==(const bitset<Sz>& lhs, const bitset<Sz>& rhs)
{
  return lhs.to_ulong() == rhs.to_ulong();
}

namespace detail
{

// efficient variants
template <size_t Capacity, typename IndexT>
inline size_t inc_index(volatile IndexT &i)
{
	if (i < Capacity - 1) { ++i; } else { i = 0; }

	return i;
}

// power of 2 specs
template <> inline size_t inc_index<0x10, size_t>(volatile size_t &i) { return ++i &= 0x0f; }
template <> inline size_t inc_index<0x20, size_t>(volatile size_t &i) { return ++i &= 0x1f; }
template <> inline size_t inc_index<0x30, size_t>(volatile size_t &i) { return ++i &= 0x2f; }
template <> inline size_t inc_index<0x40, size_t>(volatile size_t &i) { return ++i &= 0x3f; }
template <> inline size_t inc_index<0x80, size_t>(volatile size_t &i) { return ++i &= 0x7f; }
template <> inline size_t inc_index<0x100, size_t>(volatile size_t &i) { return ++i &= 0xff; }
template <> inline size_t inc_index<0x200, size_t>(volatile size_t &i) { return ++i &= 0x1ff; }
template <> inline size_t inc_index<0x400, size_t>(volatile size_t &i) { return ++i &= 0x3ff; }

} // namespace detail

/** Ring buffer queue.
 *
 *  @tparam T The type of the object to store in queue.
 *  @tparam Capacity Capacity of the queue.
 *  @tparam IndexT The type of item pointers.
 *
 *  @note Use power of two of the Capacity value to have optimized queue indexing.
 *  @note Actual size of queue is Capacity - 1 due to last element is
 *    used to distinct empty and non-empty queue.
 */
template <typename T, size_t Capacity, typename IndexT = size_t>
class queue
{
public:
  /** Static queue size. */
  enum { capacity = Capacity };

public:
  /** Stored value type. */
  typedef T value_type;

  /** Inner container type. */
  typedef array<T, Capacity> container_type;

  /** Item pointer. */
  typedef typename container_type::pointer pointer;

  /** Item pointer. */
  typedef typename container_type::const_pointer const_pointer;

  /** Item reference. */
  typedef typename container_type::reference reference;

  /** Item const reference. */
  typedef typename container_type::const_reference const_reference;

public:
  /** Creates the queue instance.
   *
   *  @param push_if_overflow If true the head can advance the tail.
   *  @note If push_if_overflow is true the queue is thread unsafe.
   *    It's necessary to provide extra synchronization of inserting
   *    and removing operations.
   */
  explicit queue(bool push_if_overflow = false):
    _tail(0), 
    _head(0),
    _push_if_overflow(push_if_overflow)
  {
    /* empty */
  }

public:
  /** Returns a const reference to the internal container. */
  const container_type& storage(void) const { return _array; }
  
  /** Pushes item into the queue.
   *
   *  @param item An item to push.
   *  @return If item is pushed returns true otherwise false.
   */
  bool push(const T& item)
  {
    if (can_push())
    {
      _array[_head] = item;
      // increment head
      inc_head();
      return true;
    }

    return false;
  }

  /** Returns pointer to const element. */
  const T* front(void) const
  {
    return empty()? nullptr: &_array[_tail];
  }

  /** Removes an element from the tail. */
  T pop(void)
  {
    if (!empty())
    {
    	const T el = _array[_tail];
      inc_index(_tail);
      return el;
    }

    return T();
  }

  /** Clears the queue. */
  void clear(void)
  {
    _tail = _head = 0;
  }

  /** Whether queue is empty. */
  bool empty(void) const
  {
    return _tail == _head;
  }

  /** Whether room in the queue. */
  bool can_push(void) const
  {
#ifdef __ICCAVR__
  #pragma diag_suppress = Pe340 // reference to temporary is used
#endif // __ICCAVR__

    IndexT tmp_head = _head;
    inc_index(tmp_head);

    return _push_if_overflow || (tmp_head != _tail);

#ifdef __ICCAVR__
  #pragma diag_default = Pe340
#endif // __ICCAVR__
  }

  /** Returns a designation whether overwriting allowed. */
  bool push_if_overflow(void) const
  {
    return _push_if_overflow;
  }

  /** Allows or disallow overwrite. */
  void push_if_overflow(bool c)
  {
    _push_if_overflow = c;
  }
  
  /** The size of the elements are currently stored. */
  size_t size(void) const
  {
    return _head < _tail? Capacity - (_tail - _head): _head - _tail;
  }

//////////////////////////////////////////////////////////////////////////
// private stuff

private:
  IndexT inc_index(volatile IndexT &i) const
  {
  	return detail::inc_index<capacity>(i);
  }

  //---------------------------------------------------------------------------
  void inc_head(void)
  {
#ifdef __ICCAVR__
  #pragma diag_suppress = Pe340 // reference to temporary is used
#endif // __ICCAVR__

    IndexT tmp_head = _head;
    inc_index(tmp_head);

    if (_push_if_overflow)
    {
      // cyclic queue
      if (tmp_head == _tail)
      {
        pop();
      }

      _head = tmp_head;
    } else
    {
      // non cyclic queue
      if (tmp_head != _tail)
      {
        inc_index(_head);
      }
    }

#ifdef __ICCAVR__
  #pragma diag_default = Pe340
#endif // __ICCAVR__
  }

private:
  container_type _array;
  volatile IndexT _tail;
  volatile IndexT _head;
  volatile bool _push_if_overflow;
};

} // namespace tiny

#endif // TINY_CONTAINER_H_
