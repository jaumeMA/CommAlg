#pragma once

#include "YTL/container/cTupla.h"
#include "YTL/functional/cFunctionOps.h"
#include "Math/cVectorFunctionSpace.h"
#include "Math/detail/cMathDerivativeHelper.h"

namespace yame
{
namespace math
{
namespace detail
{

template<int ... Components, ring_type Im, vector_space_type Dom>
inline container::cTupla<scalar_function<Im,Dom>,mpl::get_num_ranks<Components...>::value> derivative(const scalar_function<Im,Dom>& i_function);

template<ring_type Im, vector_space_type Dom>
inline scalar_function<Im,Dom> derivative(const Dom& i_direction, const scalar_function<Im,Dom>& i_function);

template<int Component, int ... Components, module_type Im, vector_space_type Dom>
inline vector_function<Im,Dom> derivative(const mpl::sequence<Components...>&, const vector_function<Im,Dom>& i_function);

template<int ... Components, int ... CComponents, module_type Im, vector_space_type Dom>
requires ( mpl::get_num_ranks<Components...>::value > 1 )
inline container::cTupla<vector_function<Im,Dom>,mpl::get_num_ranks<Components...>::value> derivative(mpl::sequence<CComponents...>&, const vector_function<Im,Dom>& i_function);

template<int ... Components, module_type Im, vector_space_type Dom>
inline vector_function<Im,Dom> derivative(const mpl::sequence<Components...>&, const Dom& i_direction, const vector_function<Im,Dom>& i_function);

template<int ... Components, module_type Im, vector_space_type Dom>
inline container::cTupla<vector_function<Im,Dom>,mpl::get_num_ranks<Components...>::value> derivative(const vector_function<Im,Dom>& i_function);

template<module_type Im, vector_space_type Dom>
inline vector_function<Im,Dom> derivative(const Dom& i_direction, const vector_function<Im,Dom>& i_function);

}

template<int ... Components, module_type Im, vector_space_type Dom, callable_type Function>
inline container::cTupla<cFunctionSpace<Im,Dom,Function>,mpl::get_num_ranks<Components...>::value> derivative(const cFunctionSpace<Im,Dom,Function>& i_function);

template<module_type Im, vector_space_type Dom, callable_type Function>
inline cFunctionSpace<Im,Dom,Function> derivative(const Dom& i_direction, const cFunctionSpace<Im,Dom,Function>& i_function);

}
}

#include "Math/detail/cMathOps.tpp"
