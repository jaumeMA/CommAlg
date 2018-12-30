#pragma once

#include "Math/cNumberSpaces.h"
#include <complex>

namespace yame
{
namespace math
{

inline Real sin(Real i_value)
{
    return Real(std::sin(i_value.get_raw()));
}
inline Complex sin(Complex i_value)
{
    std::complex<double> res = std::sin(std::complex<double>(i_value.real(),i_value.imag()));

    return Complex(res.real(),res.imag());
}
inline Real cos(Real i_value)
{
    return Real(std::cos(i_value.get_raw()));
}
inline Complex cos(Complex i_value)
{
    std::complex<double> res = std::cos(std::complex<double>(i_value.real(),i_value.imag()));

    return Complex(res.real(),res.imag());
}
inline Real tan(Real i_value)
{
    return Real(std::tan(i_value.get_raw()));
}
inline Complex tan(Complex i_value)
{
    std::complex<double> res = std::tan(std::complex<double>(i_value.real(),i_value.imag()));

    return Complex(res.real(),res.imag());
}
inline Real exp(Real i_value)
{
    return Real(std::exp(i_value.get_raw()));
}
inline Complex exp(Complex i_value)
{
    std::complex<double> res = std::exp(std::complex<double>(i_value.real(),i_value.imag()));

    return Complex(res.real(),res.imag());
}
inline Real log(Real i_value)
{
    return Real(std::log(i_value.get_raw()));
}
inline Complex log(Complex i_value)
{
    std::complex<double> res = std::log(std::complex<double>(i_value.real(),i_value.imag()));

    return Complex(res.real(),res.imag());
}

}
}
