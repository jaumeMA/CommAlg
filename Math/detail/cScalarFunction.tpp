
namespace yame
{
namespace math
{
namespace detail
{

template<set_type Im, set_type Dom>
scalar_function<Im,Dom>::scalar_function(const Dom& i_constValue)
: base_function(apply_function<Im,Dom>(i_constValue))
{
}
template<set_type Im, set_type Dom>
scalar_function<Im,Dom>::scalar_function(const base_function& i_base)
: base_function(i_base)
{
}
template<set_type Im, set_type Dom>
scalar_function<Im,Dom> scalar_function<Im,Dom>::clone(const func_ptr_base* i_funcPtr)
{
    scalar_function<Im,Dom> res;

    if(i_funcPtr != NULL)
    {
        res.clone(*i_funcPtr);
    }

    return res;
}
//template<set_type Im, set_type Dom>
//Im scalar_function<Im,Dom>::operator()(const Dom& i_point) const
//{
//    typedef typename mpl::create_range_rank<0,Dom::dimension()>::type typeSeq;
//
//    return _eval(typeSeq(),i_point);
//}
template<set_type Im, set_type Dom>
scalar_function<Im,Dom>& scalar_function<Im,Dom>::operator=(const Dom& i_constValue)
{
    base_function::operator=(apply_function<Im,Dom>{i_constValue});

    return *this;
}
template<set_type Im, set_type Dom>
template<callable_type Return, typename ... Args>
Return scalar_function<Im,Dom>::specialize(Args&& ... i_args) const
{
    return base_function::operator()(mpl::forward<Args>(i_args) ...);
}

template<set_type Im, set_type Dom, int ... Indexs>
Im _eval(const mpl::sequence<Indexs...>&, const scalar_function<Im,Dom>& i_function, const Dom& i_point)
{
    return eval(static_cast<typename scalar_function<Im,Dom>::base_function>(i_function),i_point.template get<Indexs>() ...);
}
template<set_type Im, set_type Dom>
Im eval(const scalar_function<Im,Dom>& i_function, const Dom& i_point)
{
    typedef typename mpl::create_range_rank<0,Dom::dimension()>::type typeSeq;
    return _eval(typeSeq{},i_function,i_point);
}
template<set_type Im, set_type Dom, typename ... Args>
Im eval(const scalar_function<Im,Dom>& i_function, Args&& ... i_args)
{
    return i_function.getFuncPtr()->operator()(mpl::forward<Args>(i_args)...);
}

}
}
}

