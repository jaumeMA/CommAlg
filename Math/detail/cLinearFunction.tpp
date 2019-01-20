
namespace yame
{
namespace math
{
namespace detail
{

template<ring_type Im, vector_space_type Dom>
linear_function<Im,Dom>::linear_function(const base_function& i_base)
: func_base(i_base)
{
}
template<ring_type Im, vector_space_type Dom>
linear_function<Im,Dom>::linear_function(const Dom& i_value)
: func_base(apply_function<Im,Dom>(i_value))
{
}
template<ring_type Im, vector_space_type Dom>
linear_function<Im,Dom>::linear_function(const projection_function<Im,Dom>& i_component)
: func_base(i_component)
{
}
template<ring_type Im, vector_space_type Dom>
linear_function<Im,Dom>::linear_function(const constant_function<Im,Dom>& i_constValue)
: func_base(i_constValue)
{
}
template<ring_type Im, vector_space_type Dom>
linear_function<Im,Dom> linear_function<Im,Dom>::clone(const func_ptr_base* i_funcPtr)
{
    linear_function<Im,Dom> res;

    if(i_funcPtr != NULL)
    {
        res.clone(*i_funcPtr);
    }

    return res;
}
template<ring_type Im, vector_space_type Dom>
linear_function<Im,Dom>& linear_function<Im,Dom>::operator=(const Dom& i_value)
{
    func_base::operator=(i_value);

    return *this;
}
template<ring_type Im, vector_space_type Dom>
template<callable_type Return, typename ... Args>
Return linear_function<Im,Dom>::specialize(Args&& ... i_args) const
{
    return Return(base_function::operator()(mpl::forward<Args>(i_args) ...));
}
template<ring_type Im, vector_space_type Dom>
vector<Im,Dom::dimension()> linear_function<Im,Dom>::as_vector() const
{
    return _as_vector(typename mpl::create_range_rank<0,Dom::dimension()>::type{});
}
template<ring_type Im, vector_space_type Dom>
template<int ... Indexs>
vector<Im,Dom::dimension()> linear_function<Im,Dom>::_as_vector(const mpl::sequence<Indexs...>&) const
{
    static const Dom s_bases[Dom::dimension()] = { Dom::base(Indexs) ... };

    //recover components by applying basis over netsed function
    return _as_vector(s_bases[Indexs] ...);
}
template<ring_type Im, vector_space_type Dom>
template<typename ... Args>
requires ( mpl::get_num_types<Args...>::value == Dom::dimension() && mpl::are_same_type<Dom,Args...>::value )
vector<Im,Dom::dimension()> linear_function<Im,Dom>::_as_vector(const Args& ... i_bases) const
{
    return { func_base::eval(i_bases) ...};
}

}
}
}
