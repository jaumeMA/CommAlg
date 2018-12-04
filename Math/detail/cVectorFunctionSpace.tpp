
namespace yame
{
namespace math
{
namespace detail
{

template<module_type Im, vector_space_type Dom>
const typename ExtendedVectorFunctionSpaceSet<Im,Dom>::const_function_constructor ExtendedVectorFunctionSpaceSet<Im,Dom>::C = typename ExtendedVectorFunctionSpaceSet<Im,Dom>::const_function_constructor();

template<module_type Im, vector_space_type Dom>
auto ExtendedVectorFunctionSpaceSet<Im,Dom>::const_function_constructor::operator()(nested_im_t i_constantValue) const
{
    return vector_function<nested_im_t,Dom>(constant_function<nested_im_t,Dom>(i_constantValue));
}

template<module_type Im, vector_space_type Dom>
typename ExtendedVectorFunctionSpaceSet<Im,Dom>::underlying_type ExtendedVectorFunctionSpaceSet<Im,Dom>::get_nested_function() const
{
    return this->getValue();
}
template<module_type Im, vector_space_type Dom>
template<typename ... Args>
auto ExtendedVectorFunctionSpaceSet<Im,Dom>::operator()(Args&& ... i_args) const
{
    typedef typename mpl::static_if<is_composition<Dom,Args...>::value,typename specialization<Im,Dom>::composer,typename specialization<Im,Dom>::specializer>::type caller;
    static const caller thisCaller;

	return thisCaller(static_cast<const cFunctionSpace<Im,Dom>&>(*this),mpl::forward<Args>(i_args) ...);
}
template<module_type Im, vector_space_type Dom>
template<typename ... Args>
auto ExtendedVectorFunctionSpaceSet<Im,Dom>::eval(Args&& ... i_args) const
{
    return this->getValue().eval(mpl::forward<Args>(i_args)...);
}

}
}
}
