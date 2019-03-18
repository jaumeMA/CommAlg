#pragma once

#include "Math/cVectorFunction.h"
#include "YTL/functional/detail/cFunctionTemplateHelper.h"
#include "Math/detail/cMathTypeConceptHelper.h"
#include "Math/detail/cVectorTemplateHelper.h"
#include "Math/cFunctionSpace.h"

namespace yame
{
namespace math
{
namespace detail
{

template<typename ...>
struct _is_composition;

template<>
struct _is_composition<>
{
    static const bool value = true;
};

template<typename Type,typename ... TTypes>
struct _is_composition<Type,TTypes...>
{
    static const bool value = is_function_space<Type>::value && _is_composition<TTypes...>::value;
};

template<vector_space_type Dom, typename ... Types>
struct is_composition
{
    static_assert(mpl::get_num_types<Types...>::value == Dom::dimension(), "Mismatch between construct args and types");

    static const bool value = _is_composition<typename mpl::drop_reference<Types>::type...>::value;
};

template<module_type Im, vector_space_type Dom, callable_type Function>
struct _specialization
{
    typedef typename Im::traits::module_traits::ring nested_im_t;
    typedef typename resolve_underlying_vector_space<Dom>::type nested_dom_t;
    typedef typename Function::particle_function_t particle_t;

    struct specializer
    {
    private:

        template<typename ... Types>
        using nested_vector_subspace = typename vector_subspace<Dom,mpl::get_num_types<Types...>::value - mpl::get_num_of_types_of<mpl::is_not_place_holder,Types...>::value>::type;

        template<int Component, typename ... Args>
        inline typename particle_t::template move_to<nested_im_t,nested_vector_subspace<Args...>>::type _invoke(const Function& i_func, Args&& ... i_args) const
        {
            typedef typename particle_t::template move_to<nested_im_t,nested_vector_subspace<Args...>>::type Return_t;
            const particle_t& nestedFunction = i_func.template get<Component>();

            return nestedFunction.template specialize<Return_t>(mpl::forward<Args>(i_args)...);
        }
        template<int ... Components, typename ... Args>
        inline typename Function::template move_to<Im,nested_vector_subspace<Args...>>::type invoke(const mpl::sequence<Components...>&, const Function& i_func, Args&& ... i_args) const
        {
            return { _invoke<Components>(i_func, mpl::forward<Args>(i_args)...) ...};
        }

    public:
        template<typename ... Args>
        inline typename Function::template move_to<Im,nested_vector_subspace<Args...>>::type operator()(const cFunctionSpace<Im,Dom,Function>& i_func, Args&& ... i_args) const
        {
            return invoke(typename mpl::create_range_rank<0,Im::dimension()>::type{},i_func.getValue(),mpl::forward<Args>(i_args) ...);
        }
    };
    struct composer
    {
    private:
        template<typename Type, typename ... Types, typename ... TTypes>
        inline ytl::agnostic_composed_callable<Type(TTypes...)> __invoke(const ytl::function<Type(Types...)>& i_func, const ytl::function<typename mpl::drop_constness<typename mpl::drop_reference<Types>::type>::type(TTypes...)>& ... i_funcs) const
        {
            return ytl::agnostic_composed_callable<Type(TTypes...)>(ytl::pass_by_value_functor<Type(Types...)>(i_func),i_funcs ...);
        }
        template<int Component, typename DDom, typename ... DDoms>
        inline typename particle_t::template move_to<nested_im_t,DDom>::type _invoke(const vector_function<Im,Dom>& i_func, const vector_function<typename vector_subspace<Dom,1>::type,DDom>& other, const vector_function<typename vector_subspace<Dom,1>::type,DDoms>& ... others) const
        {
            return __invoke(i_func.template get<Component>(),other.template get<Component>(),others.template get<Component>() ... );
        }
        template<int ... Components, typename DDom, typename ... DDoms>
        inline typename Function::template move_to<Im,DDom>::type invoke(const mpl::sequence<Components...>&, const vector_function<Im,Dom>& i_func, const vector_function<typename vector_subspace<Dom,1>::type,DDom>& other, const vector_function<typename vector_subspace<Dom,1>::type,DDoms>& ... others) const
        {
            return { _invoke<Components>(i_func,other,others ...) ... };
        }

    public:
        template<callable_type FFunction, vector_space_type DDom, typename ... DDoms>
        requires ( mpl::are_same_type<DDom,DDoms...>::value && Dom::dimension() == mpl::get_num_types<DDoms...>::value + 1 )
        inline cFunctionSpace<Im,DDom,typename Function::template move_to<Im,DDom>::type> operator()(const cFunctionSpace<Im,Dom,Function>& i_func, const cFunctionSpace<typename vector_subspace<Dom,1>::type,DDom,FFunction>& other, const cFunctionSpace<typename vector_subspace<Dom,1>::type,DDoms,FFunction>& ... others) const
        {
            return invoke(typename mpl::create_range_rank<0,Im::dimension()>::type{},i_func.getValue(),other.getValue(),others.getValue() ...);
        }
    };
};

template<module_type Im, vector_space_type Dom, callable_type Function>
_specialization<Im,Dom,Function> underlying_specialization_type(const detail::vector_function<Im,Dom>&);

}

template<module_type Im, vector_space_type Dom, callable_type Function>
using specialization = detail::_specialization<Im,Dom,Function>;

}
}
