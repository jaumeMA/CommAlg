
namespace yame
{
namespace math
{
namespace detail
{

template<affine_space_type Im, affine_space_type Dom, callable_type Function>
matrix<typename Im::vector_space::ring,Im::dimension(),Dom::dimension()+1> ExtendedAffineFunctionSpaceSet<Im,Dom,Function>::as_matrix(const dom_set& i_origin) const
{
    return this->getValue().as_matrix(i_origin);
}

}
}
}
