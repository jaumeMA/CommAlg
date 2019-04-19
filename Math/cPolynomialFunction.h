#pragma once

#include "Math/cAffineSpace.h"
#include "Math/cScalarFunction.h"
#include "Math/cPolynomialAlgebra.h"

#define DEFINE_MATH_HIGHER_ORDER_BINARY_POLYNOMIAL_FUNCTION(NAME,OP) \
friend inline polynomial_function<Space> operator OP(const polynomial_function<Space>& i_lhs, const polynomial_function<Space>& i_rhs) \
{ \
    typedef typename polynomial_function<Space>::base_function base_function; \
    return static_cast<const base_function&>(i_lhs) OP static_cast<const base_function&>(i_rhs); \
}

#define DEFINE_MATH_HIGHER_ORDER_BINARY_POLYNOMIAL_FUNCTION_CONSTANT(NAME,OP) \
friend inline polynomial_function<Space> operator OP(const polynomial_function<Space>& i_lhs, const Im& i_rhs) \
{ \
    typedef typename polynomial_function<Space>::base_function base_function; \
    typedef ytl::constant_function<base_function> constant_function_t; \
    return static_cast<const base_function&>(i_lhs) OP constant_function_t(i_rhs); \
} \
friend inline polynomial_function<Space> operator OP(const Im& i_lhs, const polynomial_function<Space>& i_rhs) \
{ \
    typedef typename polynomial_function<Space>::base_function base_function; \
    typedef ytl::constant_function<base_function> constant_function_t; \
    return constant_function_t(i_lhs) OP static_cast<const base_function&>(i_rhs); \
}

namespace yame
{
namespace math
{
namespace detail
{

template<affine_space_type>
class polynomial_function;

template<field_type K, int N>
class polynomial_function<AKn<K,N>> : public scalar_function<K,Kn<K,N>>
{

DEFINE_MATH_HIGHER_ORDER_BINARY_POLYNOMIAL_FUNCTION(sum,+)
DEFINE_MATH_HIGHER_ORDER_BINARY_POLYNOMIAL_FUNCTION(subs,-)
DEFINE_MATH_HIGHER_ORDER_BINARY_POLYNOMIAL_FUNCTION_CONSTANT(sum,+)
DEFINE_MATH_HIGHER_ORDER_BINARY_POLYNOMIAL_FUNCTION_CONSTANT(subs,-)
DEFINE_MATH_HIGHER_ORDER_BINARY_POLYNOMIAL_FUNCTION(prod,*)
DEFINE_MATH_HIGHER_ORDER_BINARY_POLYNOMIAL_FUNCTION_CONSTANT(prod,*)

    template<template<typename> class A, int ... Indexs>
    polynomial_function(const polynomial<K,A>& i_truncatedPolynomial, const mpl::sequence<Indexs...>&);

public:
    template<affine_space_type SSpace>
    struct move_to
    {
        typedef polynomial_function<SSpace> type;
    };

    typedef K return_type;
    typedef scalar_function<K,Kn<K,N>> func_base;
    typedef typename func_base::base_function base_function;
    typedef typename base_function::func_ptr_base func_ptr_base;
    using func_base::operator();
    using func_base::clone;

    template<template<typename> class A = memory::cTypedSystemAllocator>
    polynomial_function(const polynomial<K,A>& i_polynomial);
};

}

template<affine_space_type Space>
inline detail::polynomial_function<Space> operator^(const detail::polynomial_function<Space>& i_lhs, int i_rhs)
{
    typedef typename detail::scalar_function<Im,Dom>::base_function base_function;
    return static_cast<const base_function&>(i_lhs) ^ ytl::constant_function<base_function>(i_rhs);
}
template<affine_space_type Space>
inline detail::polynomial_function<Space> operator^(int i_lhs, const detail::polynomial_function<Space>& i_rhs)
{
    typedef typename detail::scalar_function<Im,Dom>::base_function base_function;
    return ytl::constant_function<base_function>(i_lhs) ^ static_cast<const base_function&>(i_rhs);
}

}
}

#include "Math/detail/cPolynomialFunction.tpp"
