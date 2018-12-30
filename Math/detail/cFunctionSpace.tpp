#pragma once

namespace yame
{
namespace math
{


template<set_type Im, set_type Dom, callable_type Function>
template<set_type IIm>
requires ( Dom::dimension() == 0 )
cFunctionSpace<Im,Dom,Function>::operator IIm() const
{
    return this->getValue();
}

}
}
