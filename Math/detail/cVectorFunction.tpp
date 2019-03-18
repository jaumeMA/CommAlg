
namespace yame
{
namespace math
{
namespace detail
{

template<module_type Im , vector_space_type Dom>
template<int ... Indexs>
vector_function<Im,Dom>::vector_function(const mpl::sequence<Indexs...>&, const matrix<typename Dom::field,Im::dimension(),Dom::dimension()>& i_linearValue)
: base( { Dom(i_linearValue.template get<Indexs>()) ...} )
{
}
template<module_type Im , vector_space_type Dom>
template<typename ... Args>
vector_function<Im,Dom>::vector_function(const Args& ... i_args)
: base( { i_args ...} )
{
}
template<module_type Im , vector_space_type Dom>
vector_function<Im,Dom>::vector_function(const matrix<typename Dom::field,Im::dimension(),Dom::dimension()>& i_linearValue)
: vector_function(typename mpl::create_range_rank<0,Im::dimension()>::type{},i_linearValue)
{
}
template<module_type Im , vector_space_type Dom>
vector_function<Im,Dom>& vector_function<Im,Dom>::operator=(const matrix<typename Dom::field,Im::dimension(),Dom::dimension()>& i_linearValue)
{
    base::operator=(i_linearValue.getValue());

    return *this;
}
template<module_type Im , vector_space_type Dom>
Im vector_function<Im,Dom>::operator()(const Dom& i_point) const
{
    return _eval(typename mpl::create_range_rank<0,Im::dimension()>::type{},typename mpl::create_range_rank<0,Dom::dimension()>::type{},i_point);
}
template<module_type Im , vector_space_type Dom>
template<int ... Components, int ... Indexs>
Im vector_function<Im,Dom>::_eval(const mpl::sequence<Components...>&, const mpl::sequence<Indexs...>&, const Dom& i_point) const
{
    return { eval(this->template get<Components>(),i_point.template get<Indexs>() ...) ...};
}
template<module_type Im , vector_space_type Dom>
template<int ... Components>
Im vector_function<Im,Dom>::_eval(const mpl::sequence<Components...>&) const
{
    return { eval(this->template get<Components>()) ...};
}
template<module_type Im , vector_space_type Dom>
template<module_type IIm>
requires (Dom::dimension() == 0)
vector_function<Im,Dom>::operator IIm() const
{
    return _eval(typename mpl::create_range_rank<0,Im::dimension()>::type{});
}

template<int ... Components, module_type Im , vector_space_type Dom, typename ... Args>
Im eval(const mpl::sequence<Components...>&, const vector_function<Im,Dom>& i_function, Args&& ... i_args)
{
    return { eval(i_function.template get<Components>(),mpl::forward<Args>(i_args) ...) ...};
}
template<module_type Im , vector_space_type Dom, typename ... Args>
Im eval(const vector_function<Im,Dom>& i_function, Args&& ... i_args)
{
    return eval(typename mpl::create_range_rank<0,Im::dimension()>::type{},i_function,mpl::forward<Args>(i_args) ...);
}

}
}
}
