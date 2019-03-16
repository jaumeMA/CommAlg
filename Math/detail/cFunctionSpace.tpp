#pragma once

namespace yame
{
namespace math
{
namespace detail
{

template<set_type Im, set_type Dom, callable_type Function>
template<typename ... Args>
auto ExtendedFunctionSpaceSet<Im,Dom,Function>::operator()(Args&& ... i_args) const
{
    return eval(this->getValue(),mpl::forward<Args>(i_args)...);
}

}

template<set_type Im, set_type Dom, callable_type Function>
template<set_type IIm>
requires ( Dom::dimension() == 0 )
cFunctionSpace<Im,Dom,Function>::operator IIm() const
{
    return this->getValue();
}

}
}
