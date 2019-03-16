#pragma once

#include "YTL/functional/cFunction.h"
#include "Math/detail/cMathTypeConceptHelper.h"

#define DECLARE_MATH_FUNCTION(FUNC_NAME, NESTED_FUNC_NAME) \
template<ring_type Im, vector_space_type Dom> \
class FUNC_NAME##_function_t : public detail::scalar_function<Im,Dom> \
{ \
public: \
    Im operator()(const Dom& i_point) const \
    { \
        return detail::scalar_function<Im,Dom>::operator()(i_point); \
    } \
    FUNC_NAME##_function_t() \
    : detail::scalar_function<Im,Dom>(&NESTED_FUNC_NAME) \
    {} \
}; \
static FUNC_NAME##_function_t<Real,R1> FUNC_NAME##r = FUNC_NAME##_function_t<Real,R1>(); \
static FUNC_NAME##_function_t<Complex,C1> FUNC_NAME##c = FUNC_NAME##_function_t<Complex,C1>(); \

#define DEFINE_MATH_HIGHER_ORDER_BINARY_FUNCTION(NAME,OP) \
friend inline scalar_function<Im,Dom> operator OP(const scalar_function<Im,Dom>& i_lhs, const scalar_function<Im,Dom>& i_rhs) \
{ \
    typedef typename scalar_function<Im,Dom>::base_function base_function; \
    return static_cast<const base_function&>(i_lhs) OP static_cast<const base_function&>(i_rhs); \
}

#define DEFINE_MATH_HIGHER_ORDER_BINARY_FUNCTION_CONSTANT(NAME,OP) \
friend inline scalar_function<Im,Dom> operator OP(const scalar_function<Im,Dom>& i_lhs, const Im& i_rhs) \
{ \
    typedef typename scalar_function<Im,Dom>::base_function base_function; \
    typedef ytl::constant_function<typename scalar_function<Im,Dom>::base_function> constant_function_t; \
    return static_cast<const base_function&>(i_lhs) OP constant_function_t(i_rhs); \
} \
friend inline scalar_function<Im,Dom> operator OP(const Im& i_lhs, const scalar_function<Im,Dom>& i_rhs) \
{ \
    typedef typename scalar_function<Im,Dom>::base_function base_function; \
    typedef ytl::constant_function<typename scalar_function<Im,Dom>::base_function> constant_function_t; \
    return constant_function_t(i_lhs) OP static_cast<const base_function&>(i_rhs); \
}

namespace yame
{
namespace math
{
namespace detail
{

template<set_type Im, set_type Dom>
struct set_function_operators
{
};

template<group_type Im, set_type Dom>
struct group_function_operators : public set_function_operators<Im,Dom>
{
DEFINE_MATH_HIGHER_ORDER_BINARY_FUNCTION(sum,+)
DEFINE_MATH_HIGHER_ORDER_BINARY_FUNCTION(subs,-)
DEFINE_MATH_HIGHER_ORDER_BINARY_FUNCTION_CONSTANT(sum,+)
DEFINE_MATH_HIGHER_ORDER_BINARY_FUNCTION_CONSTANT(subs,-)
};

template<ring_type Im, set_type Dom>
struct ring_function_operators : group_function_operators<Im,Dom>
{
DEFINE_MATH_HIGHER_ORDER_BINARY_FUNCTION(prod,*)
DEFINE_MATH_HIGHER_ORDER_BINARY_FUNCTION(pow,^)
DEFINE_MATH_HIGHER_ORDER_BINARY_FUNCTION_CONSTANT(prod,*)
DEFINE_MATH_HIGHER_ORDER_BINARY_FUNCTION_CONSTANT(pow,^)
};

template<field_type Im, set_type Dom>
struct field_function_operators : ring_function_operators<Im,Dom>
{
DEFINE_MATH_HIGHER_ORDER_BINARY_FUNCTION(div,/)
DEFINE_MATH_HIGHER_ORDER_BINARY_FUNCTION_CONSTANT(div,/)
};

template<set_type Im, set_type Dom>
set_function_operators<Im,Dom> resolve_function_operators(const Im&, const Dom&);
template<group_type Im, set_type Dom>
group_function_operators<Im,Dom> resolve_function_operators(const Im&, const Dom&);
template<ring_type Im, set_type Dom>
ring_function_operators<Im,Dom> resolve_function_operators(const Im&, const Dom&);
template<field_type Im, set_type Dom>
field_function_operators<Im,Dom> resolve_function_operators(const Im&, const Dom&);

}

DECLARE_MATH_FUNCTION(sin, yame::math::sin);
DECLARE_MATH_FUNCTION(cos, yame::math::cos);
DECLARE_MATH_FUNCTION(tan, yame::math::tan);
DECLARE_MATH_FUNCTION(exp, yame::math::exp);
DECLARE_MATH_FUNCTION(log, yame::math::log);
}
}
