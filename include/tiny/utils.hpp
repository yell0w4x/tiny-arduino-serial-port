// Arduino async serial port library with nine data bits support.
//
// 2015, (c) Gk Ltd.
// MIT License


#ifndef TINY_UTILS_HPP_
#define TINY_UTILS_HPP_

#include <functional>

namespace tiny
{

/** Binds a member function. */
template <typename Fn>
class mem_fun_binder : public
  std::unary_function<typename Fn::argument_type, typename Fn::result_type>
{
public:
  typedef std::unary_function<typename Fn::argument_type, typename Fn::result_type> base_type;
  typedef typename base_type::argument_type argument_type;
  typedef typename base_type::result_type result_type;

public:
  mem_fun_binder(Fn op, argument_type objptr): 
    _op(op),
    _objptr(objptr)
  {}

public:
  typename Fn::result_type operator()(void)
  {
    return _op(_objptr);
  }

private:
  Fn _op;
  argument_type _objptr;
};

//-----------------------------------------------------------------------------
template <typename Fn>
mem_fun_binder<Fn> mem_fun_bind(Fn op, typename Fn::argument_type objptr)
{
  return mem_fun_binder<Fn>(op, objptr);
}

} // namespace tiny

#endif // TINY_UTILS_H_
