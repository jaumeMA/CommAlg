#pragma once

#include "YTL/mpl/cFunctionTemplateHelper.h"
#include "Math/cVectorSpace.h"
#include "Math/detail/cStdMathOps.h"
#include <utility>
#include "YTL/functional/detail/cFunctionConceptHelper.h"
#include "YTL/functional/cFunction.h"
#include "YTL/functional/cFunctionOps.h"

namespace yame
{
namespace math
{
namespace detail
{

template<set_type Im, set_type Dom>
ytl::function<Im(Dom)> resolve_underlying_function_type(const Im&, const Dom&);

template<set_type Im, set_type Dom>
class scalar_function : public decltype(resolve_underlying_function_type(std::declval<Im>(),std::declval<Dom>())), decltype(resolve_function_operators(std::declval<Im>(),std::declval<Dom>()))
{
public:
    template<set_type IIm, set_type DDom>
    struct move_to
    {
        typedef scalar_function<IIm,DDom> type;
    };

    typedef Im return_type;
    typedef decltype(resolve_underlying_function_type(std::declval<Im>(),std::declval<Dom>())) base_function;
    typedef typename base_function::func_ptr_base func_ptr_base;
    using base_function::base_function;
    using base_function::operator();
    using base_function::clone;

    scalar_function() = default;
    scalar_function(const Dom& i_constValue);
    scalar_function(const base_function& i_base);
    static scalar_function<Im,Dom> clone(const func_ptr_base* i_funcPtr);

    //Im operator()(const Dom& i_point) const;
    scalar_function& operator=(const Dom& i_constValue);

    template<callable_type Return, typename ... Args>
    Return specialize(Args&& ... i_args) const;
};

template<typename Return,typename ... Types>
ytl::detail::free_function_impl<Return,Types...> free_function_type(const ytl::function<Return(Types...)>&);

template<set_type Im, set_type Dom>
using free_function_impl = decltype(free_function_type(std::declval<scalar_function<Im,Dom>>()));

template<typename Functor,typename Return,typename ... Types>
ytl::detail::functor_impl<Functor,Return,Types...> functor_type(const ytl::function<Return(Types...)>&);

template<typename Functor,typename Im, set_type Dom>
using functor_impl = decltype(functor_type<Functor>(std::declval<scalar_function<Im,Dom>>()));

template<set_type Im, set_type Dom, int ... Indexs>
inline Im _eval(const mpl::sequence<Indexs...>&, const scalar_function<Im,Dom>& i_function, const Dom& i_point);
template<set_type Im, set_type Dom>
inline Im eval(const scalar_function<Im,Dom>& i_function, const Dom& i_point);
template<set_type Im, set_type Dom, typename ... Args>
inline Im eval(const scalar_function<Im,Dom>& i_function, Args&& ... i_args);

}

template<set_type Im, set_type Dom>
using constant_function = ytl::constant_function<typename detail::scalar_function<Im,Dom>::base_function>;

template<set_type Im, set_type Dom>
using projection_function = ytl::projection_function<typename detail::scalar_function<Im,Dom>::base_function>;

template<set_type Im, set_type Dom>
class apply_function : public detail::scalar_function<Im,Dom>
{
    typedef typename detail::scalar_function<Im,Dom> func_base;
    typedef typename func_base::base_function homogeneous_callable_t;

    template<typename Return,typename ... Types>
    apply_function(const Dom& i_applyValue, const ytl::function<Return(Types...)>*)
    : func_base([i_applyValue](Types ... i_args){ return Return(i_applyValue * Dom{mpl::forward<Types>(i_args) ...});})
    {}
public:
    apply_function(const Dom& i_applyValue)
    : apply_function(i_applyValue,reinterpret_cast<const homogeneous_callable_t*>(NULL))
    {}
};


template<module_type Im, set_type Dom>
detail::scalar_function<typename Im::traits::module_traits::ring,Dom> underlying_function_type(const Im&, const Dom&);

template<set_type Im, set_type Dom>
detail::scalar_function<Im,Dom> underlying_function_type(const Im&, const Dom&);

template<ring_type Im, vector_space_type Dom>
inline detail::scalar_function<Im,Dom> operator^(const detail::scalar_function<Im,Dom>& i_lhs, int i_rhs)
{
    typedef typename detail::scalar_function<Im,Dom>::base_function base_function;
    return static_cast<const base_function&>(i_lhs) ^ ytl::constant_function<base_function>(i_rhs);
}
template<ring_type Im, vector_space_type Dom>
inline detail::scalar_function<Im,Dom> operator^(int i_lhs, const detail::scalar_function<Im,Dom>& i_rhs)
{
    typedef typename detail::scalar_function<Im,Dom>::base_function base_function;
    return ytl::constant_function<base_function>(i_lhs) ^ static_cast<const base_function&>(i_rhs);
}

}
}


#include "Math/detail/cScalarFunctionOps.h"
#include "Math/detail/cScalarFunction.tpp"

