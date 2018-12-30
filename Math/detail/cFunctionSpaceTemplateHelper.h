#pragma once

#include "Math/detail/cMathTypeConceptHelper.h"
#include "Math/cFunctionSpaceTraits.h"
#include "Math/detail/cAlgebraImpl.h"

namespace yame
{
namespace math
{

template<template <set_type,set_type,callable_type> typename F, callable_type Function, group_type Im, set_type Dom>
detail::cGroupImpl<FunctionSpaceGroupTraits<Im,Dom,Function>,F<Im,Dom,Function>> resolve_function_space_structure(const Im&,const Dom&);

template<template <set_type,set_type,callable_type> typename F, callable_type Function, module_type Im, set_type Dom>
detail::cModuleImpl<FunctionSpaceModuleTraits<Im,Dom,Function>,F<Im,Dom,Function>> resolve_function_space_structure(const Im&,const Dom&);

template<template <set_type,set_type,callable_type> typename F, callable_type Function, field_type Im, set_type Dom>
detail::cModuleImpl<FunctionSpaceModuleTraits<Im,Dom,Function>,F<Im,Dom,Function>> resolve_function_space_structure(const Im&,const Dom&);

IS_STRUCTURE(function_space)

}
}
