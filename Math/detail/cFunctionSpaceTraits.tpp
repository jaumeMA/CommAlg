
namespace yame
{
namespace math
{

template<set_type Im, set_type Dom, callable_type Function>
void FunctionSpaceSetTraits<Im,Dom,Function>::init(underlying_type& o_value)
{
    //nothing to be done (alreay handled by function destructor)
}
template<set_type Im, set_type Dom, callable_type Function>
void FunctionSpaceSetTraits<Im,Dom,Function>::init(underlying_type& o_value, const underlying_type& i_value)
{
    o_value = i_value;
}
template<set_type Im, set_type Dom, callable_type Function>
template<typename ... Args>
requires ( mpl::are_type_of<mpl::is_base_of_function,Args...>::value )
void FunctionSpaceSetTraits<Im,Dom,Function>::init(underlying_type& o_value, const Args& ... i_args)
{
    o_value = underlying_type( { i_args ... } );
}
template<set_type Im, set_type Dom, callable_type Function>
void FunctionSpaceSetTraits<Im,Dom,Function>::deinit(underlying_type& o_value)
{
    //nothing to be done (alreay handled by function destructor)
}
template<set_type Im, set_type Dom, callable_type Function>
void FunctionSpaceSetTraits<Im,Dom,Function>::assign(underlying_type& o_value, const underlying_type& i_value)
{
    o_value = i_value;
}
template<set_type Im, set_type Dom, callable_type Function>
bool FunctionSpaceSetTraits<Im,Dom,Function>::cmp(const underlying_type& i_lhs, const underlying_type& i_rhs)
{
    //???
}

template<group_type Im, set_type Dom, callable_type Function>
void FunctionSpaceGroupTraits<Im,Dom,Function>::sum(underlying_type& o_res, const underlying_type& i_lhs,const underlying_type& i_rhs)
{
    o_res = i_lhs + i_rhs;
}
template<group_type Im, set_type Dom, callable_type Function>
void FunctionSpaceGroupTraits<Im,Dom,Function>::inv(underlying_type& o_res, const underlying_type& i_value)
{
    o_res = -i_value;
}

template<module_type Im, set_type Dom, callable_type Function>
void FunctionSpaceModuleTraits<Im,Dom,Function>::modProd(underlying_type& o_res, const ring& i_lhs, const underlying_type& i_rhs)
{
    o_res = constant_function<Im,Dom>{i_lhs} * i_rhs;
}
template<module_type Im, set_type Dom, callable_type Function>
void FunctionSpaceModuleTraits<Im,Dom,Function>::modProd(underlying_type& o_res, const underlying_type& i_lhs, const ring& i_rhs)
{
    o_res = i_lhs * constant_function<Im,Dom>{i_rhs};
}

}
}
