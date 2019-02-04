#pragma once

#include "YTL/mpl/cFunctionTemplateHelper.h"
#include "YTL/functional/cFunction.h"
#include "Math/cVectorSpace.h"
#include "Math/detail/cStdMathOps.h"
#include <utility>
#include "YTL/functional/detail/cFunctionConceptHelper.h"
#include "YTL/functional/cFunctionOps.h"

#define DECLARE_MATH_FUNCTION(FUNC_NAME, NESTED_FUNC_NAME) \
namespace yame \
{ \
namespace math \
{ \
template<ring_type Im, vector_space_type Dom> \
class FUNC_NAME##_function_t : public detail::scalar_function<Im,Dom> \
{ \
public: \
FUNC_NAME##_function_t() \
: detail::scalar_function<Im,Dom>(&NESTED_FUNC_NAME) \
{} \
}; \
static FUNC_NAME##_function_t<Real,R1> FUNC_NAME##r = FUNC_NAME##_function_t<Real,R1>(); \
static FUNC_NAME##_function_t<Complex,C1> FUNC_NAME##c = FUNC_NAME##_function_t<Complex,C1>(); \
} \
} \

#define DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(NAME,OP) \
friend inline scalar_function<Im,Dom> operator OP(const scalar_function<Im,Dom>& i_lhs, const scalar_function<Im,Dom>& i_rhs) \
{ \
    typedef typename scalar_function<Im,Dom>::base_function base_function; \
    return static_cast<const base_function&>(i_lhs) OP static_cast<const base_function&>(i_rhs); \
}

#define DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION_CONSTANT(NAME,OP) \
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

template<ring_type Im, vector_space_type Dom>
class scalar_function : public mpl::homogeneous_callable<ytl::function,Im,typename Dom::particle,Dom::dimension()>::type
{
public:
    template<ring_type IIm, vector_space_type DDom>
    struct move_to
    {
        typedef scalar_function<IIm,DDom> type;
    };

    typedef Im return_type;
    typedef typename mpl::homogeneous_callable<ytl::function,Im,typename Dom::particle,Dom::dimension()>::type base_function;
    typedef typename base_function::func_ptr_base func_ptr_base;
    using base_function::base_function;
    using base_function::operator();
    using base_function::eval;
    using base_function::clone;

    inline friend scalar_function<Im,Dom> operator^(const scalar_function<Im,Dom>& i_lhs, int i_rhs)
    {
        return static_cast<const base_function&>(i_lhs) ^ ytl::integer_constant_function<base_function>(i_rhs);
    }
    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(sum,+)
    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(subs,-)
    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(prod,*)
    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(div,/)
    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(pow,^)

    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION_CONSTANT(sum,+)
    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION_CONSTANT(subs,-)
    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION_CONSTANT(prod,*)
    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION_CONSTANT(div,/)
    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION_CONSTANT(pow,^)

    scalar_function() = default;
    scalar_function(const Dom& i_constValue);
    scalar_function(const base_function& i_base);
	Im eval(const Dom& i_point) const;
    static scalar_function<Im,Dom> clone(const func_ptr_base* i_funcPtr);
    template<callable_type Return, typename ... Args>
    Return specialize(Args&& ... i_args) const;

    scalar_function& operator=(const Dom& i_constValue);

private:
    template<int ... Indexs>
    inline Im _eval(const mpl::sequence<Indexs...>&, const Dom& i_point) const;
};

template<typename Return,typename ... Types>
ytl::detail::free_function_impl<Return,Types...> free_function_type(const ytl::function<Return(Types...)>&);

template<ring_type Im, vector_space_type Dom>
using free_function_impl = decltype(free_function_type(std::declval<scalar_function<Im,Dom>>()));

template<typename Functor,typename Return,typename ... Types>
ytl::detail::functor_impl<Functor,Return,Types...> functor_type(const ytl::function<Return(Types...)>&);

template<typename Functor,typename Im, vector_space_type Dom>
using functor_impl = decltype(functor_type<Functor>(std::declval<scalar_function<Im,Dom>>()));

}

template<ring_type Im, vector_space_type Dom>
using constant_function = ytl::constant_function<typename detail::scalar_function<Im,Dom>::base_function>;

template<ring_type Im, vector_space_type Dom>
using integer_constant_function = ytl::integer_constant_function<typename detail::scalar_function<Im,Dom>::base_function>;

template<ring_type Im, vector_space_type Dom>
using projection_function = ytl::projection_function<typename detail::scalar_function<Im,Dom>::base_function>;

template<ring_type Im, vector_space_type Dom>
class apply_function : public detail::scalar_function<Im,Dom>
{
    typedef typename detail::scalar_function<Im,Dom> func_base;
    typedef typename mpl::homogeneous_callable<ytl::function,Im,typename Dom::particle,Dom::dimension()>::type homogeneous_callable_t;

    template<typename Return,typename ... Types>
    apply_function(const Dom& i_applyValue, const ytl::function<Return(Types...)>*)
    : func_base([i_applyValue](Types ... i_args){ return Return(i_applyValue * Dom{mpl::forward<Types>(i_args) ...});})
    {}
public:
    apply_function(const Dom& i_applyValue)
    : apply_function(i_applyValue,reinterpret_cast<const homogeneous_callable_t*>(NULL))
    {}
};


template<module_type Im, vector_space_type Dom>
detail::scalar_function<typename Im::traits::module_traits::ring,Dom> underlying_function_type(const Im&, const Dom&);

template<ring_type Im, vector_space_type Dom>
detail::scalar_function<Im,Dom> underlying_function_type(const Im&, const Dom&);

}
}

DECLARE_MATH_FUNCTION(sin, yame::math::sin);
DECLARE_MATH_FUNCTION(cos, yame::math::cos);
DECLARE_MATH_FUNCTION(tan, yame::math::tan);
DECLARE_MATH_FUNCTION(exp, yame::math::exp);
DECLARE_MATH_FUNCTION(log, yame::math::log);

#include "Math/detail/cScalarFunction.tpp"

