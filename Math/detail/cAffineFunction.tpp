
namespace yame
{
namespace math
{
namespace detail
{

template<affine_space_type Im, affine_space_type Dom>
affine_function<Im,Dom>::affine_function(const set_function_t& i_originFunction, const vector_function_t& i_vectorFunction)
: m_function(i_originFunction,i_vectorFunction)
{
}
template<affine_space_type Im, affine_space_type Dom>
Im affine_function<Im,Dom>::eval(const Dom& i_point) const
{
    return Im(m_function.first.eval(i_point.get_set_component()),m_function.second.eval(i_point.get_vector_space_component()));
}
template<affine_space_type Im, affine_space_type Dom>
template<module_type IIm>
requires (Dom::dimension() == 0)
affine_function<Im,Dom>::operator IIm() const
{
    return IIm(m_function.first.eval(),m_function.second.eval());
}
template<affine_space_type Im, affine_space_type Dom>
const typename affine_function<Im,Dom>::set_function_t& affine_function<Im,Dom>::get_set_function() const
{
    return m_function.first;
}
template<affine_space_type Im, affine_space_type Dom>
const typename affine_function<Im,Dom>::vector_function_t& affine_function<Im,Dom>::get_vector_function() const
{
    return m_function.second;
}
template<affine_space_type Im, affine_space_type Dom>
matrix<typename Im::vector_space::ring,Im::dimension(),Dom::dimension()+1> affine_function<Im,Dom>::as_matrix(const dom_set& i_origin) const
{
    return _as_matrix(typename mpl::create_range_rank<0,Im::dimension()>::type{});
}
template<affine_space_type Im, affine_space_type Dom>
template<int ... Components>
matrix<typename Im::vector_space::ring,Im::dimension(),Dom::dimension()+1> affine_function<Im,Dom>::_as_matrix(const mpl::sequence<Components...>&, const dom_set& i_origin) const
{
    return { m_function.second.template get<Components>().as_vector() ..., m_function.first(i_origin) };
}

}
}
}
