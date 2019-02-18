#include "Math/cNumberOps.h"
#include <cmath>
#include <complex>

namespace yame
{
namespace math
{

Rational operator^(const Rational& i_lhs, const Rational& i_rhs)
{
    const double power = static_cast<double>(i_rhs.numerator()) / static_cast<double>(i_rhs.denominator());
    return Rational{std::pow(i_lhs.numerator(),power),std::pow(i_rhs.denominator(),power)};
}
Real operator^(const Real& i_lhs, const Real& i_rhs)
{
    return Real(std::pow(i_lhs.get_raw(),i_rhs.get_raw()));
}
Complex operator^(const Complex& i_lhs, const Complex& i_rhs)
{
    const std::complex<double> res = std::pow(std::complex<double>(i_lhs.real(),i_lhs.imag()),std::complex<double>(i_rhs.real(),i_rhs.imag()));
    return Complex(res.real(),res.imag());
}

}
}
