
namespace yame
{
namespace math
{
namespace detail
{

template<module_type Im , vector_space_type Dom>
template<size_t Component>
const typename vector_function<Im,Dom>::scalar_function_t& vector_function<Im,Dom>::get_scalar_function(const vector_function& i_func)
{
    return i_func.template get<Component>();
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

}
}
}
