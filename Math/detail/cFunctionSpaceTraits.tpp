
namespace yame
{
namespace math
{

template<set_type Im, set_type Dom>
void FunctionSpaceSetTraits<Im,Dom>::init(underlying_type& o_value)
{
    //nothing to be done (alreay handled by function destructor)
}
template<set_type Im, set_type Dom>
void FunctionSpaceSetTraits<Im,Dom>::init(underlying_type& o_value, const underlying_type& i_value)
{
    o_value = i_value;
}
template<set_type Im, set_type Dom>
template<typename ... Args>
requires ( mpl::is_constructible<typename FunctionSpaceSetTraits<Im,Dom>::underlying_type,Args...>::value )
void FunctionSpaceSetTraits<Im,Dom>::init(underlying_type& o_value, Args&& ... i_args)
{
    o_value = underlying_type(mpl::forward<Args>(i_args) ...);
}
template<set_type Im, set_type Dom>
void FunctionSpaceSetTraits<Im,Dom>::deinit(underlying_type& o_value)
{
    //nothing to be done (alreay handled by function destructor)
}
template<set_type Im, set_type Dom>
void FunctionSpaceSetTraits<Im,Dom>::assign(underlying_type& o_value, const underlying_type& i_value)
{
    o_value = i_value;
}
template<set_type Im, set_type Dom>
bool FunctionSpaceSetTraits<Im,Dom>::cmp(const underlying_type& i_lhs, const underlying_type& i_rhs)
{
    //???
}

template<group_type Im, set_type Dom>
void FunctionSpaceGroupTraits<Im,Dom>::sum(underlying_type& o_res, const underlying_type& i_lhs,const underlying_type& i_rhs)
{
    o_res = i_lhs + i_rhs;
}
template<group_type Im, set_type Dom>
void FunctionSpaceGroupTraits<Im,Dom>::inv(underlying_type& o_res, const underlying_type& i_value)
{
    o_res = -i_value;
}

template<module_type Im, set_type Dom>
void FunctionSpaceModuleTraits<Im,Dom>::modProd(underlying_type& o_res, const ring& i_lhs, const underlying_type& i_rhs)
{
    o_res = constant_function<Im,Dom>{i_lhs} * i_rhs;
}
template<module_type Im, set_type Dom>
void FunctionSpaceModuleTraits<Im,Dom>::modProd(underlying_type& o_res, const underlying_type& i_lhs, const ring& i_rhs)
{
    o_res = i_lhs * constant_function<Im,Dom>{i_rhs};
}

}
}
