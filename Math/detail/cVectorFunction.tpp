
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
Im vector_function<Im,Dom>::eval(const Dom& i_point) const
{
    return _eval(typename mpl::create_range_rank<0,Im::dimension()>::type{},typename mpl::create_range_rank<0,Dom::dimension()>::type{},i_point);
}
template<module_type Im , vector_space_type Dom>
template<int ... Components, int ... Indexs>
Im vector_function<Im,Dom>::_eval(const mpl::sequence<Components...>&, const mpl::sequence<Indexs...>&, const Dom& i_point) const
{
    return { this->template get<Components>().eval(i_point.template get<Indexs>() ...) ...};
}
template<module_type Im , vector_space_type Dom>
template<int ... Components>
Im vector_function<Im,Dom>::_eval(const mpl::sequence<Components...>&) const
{
    return { this->template get<Components>().eval() ...};
}
template<module_type Im , vector_space_type Dom>
template<module_type IIm>
requires (Dom::dimension() == 0)
vector_function<Im,Dom>::operator IIm() const
{
    return _eval(typename mpl::create_range_rank<0,Im::dimension()>::type{});
}

}
}
}
