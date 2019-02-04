
#include "Math/cMathOps.h"

namespace yame
{
namespace math
{
namespace detail
{

template<module_type Im, vector_space_type Dom, callable_type Function>
template<int ... Components, typename ... Args>
Im ExtendedVectorFunctionSpaceSet<Im,Dom,Function>::_eval(const mpl::sequence<Components...>&, Args&& ... i_args) const
{
    const Function& nestedFunction = this->getValue();

    return {nestedFunction.template get<Components>().eval(mpl::forward<Args>(i_args)...) ...};
}
template<module_type Im, vector_space_type Dom, callable_type Function>
typename ExtendedVectorFunctionSpaceSet<Im,Dom,Function>::underlying_type ExtendedVectorFunctionSpaceSet<Im,Dom,Function>::get_nested_function() const
{
    return this->getValue();
}
template<module_type Im, vector_space_type Dom, callable_type Function>
template<typename ... Args>
auto ExtendedVectorFunctionSpaceSet<Im,Dom,Function>::operator()(Args&& ... i_args) const
{
    typedef typename mpl::static_if<is_composition<Dom,Args...>::value,typename specialization<Im,Dom,Function>::composer,typename specialization<Im,Dom,Function>::specializer>::type caller;
    static const caller thisCaller;

	return thisCaller(static_cast<const cFunctionSpace<Im,Dom,Function>&>(*this),mpl::forward<Args>(i_args) ...);
}
template<module_type Im, vector_space_type Dom, callable_type Function>
template<typename ... Args>
auto ExtendedVectorFunctionSpaceSet<Im,Dom,Function>::eval(Args&& ... i_args) const
{
    return _eval(typename mpl::create_range_rank<0,Im::dimension()>::type{},mpl::forward<Args>(i_args) ...);
}

template<module_type Im, vector_space_type Dom, callable_type Function>
matrix<typename Im::ring,Im::dimension(),Dom::dimension()> ExtendedLinearVectorFunctionSpaceSet<Im,Dom,Function>::as_matrix() const
{
    return this->getValue().as_matrix();
}

}
}
}
