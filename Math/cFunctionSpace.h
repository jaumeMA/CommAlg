#pragma once

#include "Math/cFunctionSpaceTraits.h"
#include "Math/detail/cAlgebraImpl.h"
#include "Math/detail/cMathTypeConceptHelper.h"
#include "Math/detail/cFunctionSpaceTemplateHelper.h"
#include "Math/detail/cMathTags.h"

namespace yame
{
namespace math
{

template<set_type,set_type,callable_type>
class cFunctionSpace;

namespace detail
{

template<set_type Im, set_type Dom, callable_type Function>
struct ExtendedFunctionSpaceSet : virtual public detail::ISet<FunctionSpaceSetTraits<Im,Dom,Function>>
{
    typedef Function underlying_type;

    underlying_type get_nested_function();
    template<set_type IIm, set_type DDom>
    requires requires { mpl::is_type_constructible<Im,IIm>::value; mpl::is_type_constructible<Dom,DDom>::value; }
    static void init(underlying_type& o_value, const cFunctionSpace<IIm,DDom,Function>& i_value);
};

}

template<set_type Im, set_type Dom, callable_type Function>
class cFunctionSpace : public decltype(resolve_function_space_structure<cFunctionSpace,Function>(std::declval<Im>(),std::declval<Dom>())), public cSet<FunctionSpaceSetTraits<Im,Dom,Function>>, public detail::function_space_tag
{
public:
    typedef decltype(resolve_function_space_structure<cFunctionSpace,Function>(std::declval<Im>(),std::declval<Dom>())) function_base;
    typedef typename function_base::traits traits;
	typedef typename traits::underlying_type underlying_type;

	using cSet<FunctionSpaceSetTraits<Im,Dom,Function>>::cSet;
	using cSet<FunctionSpaceSetTraits<Im,Dom,Function>>::operator=;

    cFunctionSpace(const cFunctionSpace&) = default;
    cFunctionSpace& operator=(const cFunctionSpace&) = default;
    template<set_type IIm>
    requires ( Dom::dimension() == 0 )
    operator IIm() const;
};

template<callable_type Function, set_type Im, set_type Dom>
detail::ExtendedFunctionSpaceSet<Im,Dom,Function> underlying_function_extension_type(const Function&, const Im&,const Dom&);

template<set_type Im, set_type Dom, callable_type Function = decltype(underlying_function_type(std::declval<Im>(),std::declval<Dom>()))>
using F = cFunctionSpace<Im,Dom,Function>;

}
}

#include "Math/detail/cFunctionSpace.tpp"
