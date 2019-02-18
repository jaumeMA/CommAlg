#pragma once

#include "Math/cNumberSpaces.h"

namespace yame
{
namespace math
{

Rational operator^(const Rational& i_lhs, const Rational& i_rhs);
Real operator^(const Real& i_lhs, const Real& i_rhs);
Complex operator^(const Complex& i_lhs, const Complex& i_rhs);
template<int P>
inline Zp<P> operator^(const Zp<P>& i_lhs, const Zp<P>& i_rhs);

}
}

#include "Math/detail/cNumberOps.tpp"
