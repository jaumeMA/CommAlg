#pragma once

#include "Math/detail/cMathTypeConceptHelper.h"
#include "YTL/functional/detail/cFunctionConceptHelper.h"

namespace yame
{
namespace math
{

template<vector_space_type Im, vector_space_type Dom, callable_type Function>
struct FunctionSpaceSetTraits
{
    typedef Function underlying_type;
    typedef decltype(underlying_function_extension_type(std::declval<Function>(), std::declval<Im>(),std::declval<Dom>())) extended_structure;

	static void init(underlying_type& o_value);
	static void init(underlying_type& o_value, const underlying_type& i_value);
//	static void init(underlying_type& o_value, const detail::linear_vector_function<Im,Dom>& i_value);
    template<typename ... Args>
    requires ( mpl::are_type_of<mpl::is_base_of_function,Args...>::value )
    static void init(underlying_type& o_value, const Args& ... i_args);
	static void deinit(underlying_type& o_value);
    static void assign(underlying_type& o_value, const underlying_type& i_value);
    static bool cmp(const underlying_type& i_lhs, const underlying_type& i_rhs);
};

template<vector_space_type Im, vector_space_type Dom, callable_type Function>
struct FunctionSpaceGroupTraits
{
    typedef FunctionSpaceSetTraits<Im,Dom,Function> set_traits;
	typedef typename set_traits::underlying_type underlying_type;
	static underlying_type neutral_element;
	static constexpr bool is_commutative = Im::isCommutative();

	static void sum(underlying_type& res, const underlying_type& i_lhs,const underlying_type& i_rhs);
	static void inv(underlying_type& res, const underlying_type& value);
};

template<vector_space_type Im, vector_space_type Dom, callable_type Function>
struct FunctionSpaceModuleTraits
{
    typedef FunctionSpaceGroupTraits<Im,Dom,Function> group_traits;
	typedef typename group_traits::underlying_type underlying_type;
    typedef typename Im::ring ring;
	static constexpr bool is_leftModule = Im::isLeftModule();
	static constexpr bool is_rightModule = Im::isRightModule();

    static void modProd(underlying_type& o_res, const ring& i_lhs, const underlying_type& i_rhs);
    static void modProd(underlying_type& o_res, const underlying_type& i_lhs, const ring& i_rhs);
};

}
}

#include "Math/detail/cFunctionSpaceTraits.tpp"
