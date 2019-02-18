
namespace yame
{
namespace math
{


template<typename Traits>
const typename AffineSpaceExtendedAccess<Traits>::set& AffineSpaceExtendedAccess<Traits>::get_set_component() const
{
    const underlying_type& thisValue = this->getValue();

    return thisValue.first;
}
template<typename Traits>
const typename AffineSpaceExtendedAccess<Traits>::vector_space& AffineSpaceExtendedAccess<Traits>::get_vector_space_component() const
{
    const underlying_type& thisValue = this->getValue();

    return thisValue.second;
}

template<set_type X, vector_space_type V, typename Tag>
void cAffineSpaceSetTraits<X,V,Tag>::init(underlying_type& o_value)
{
    //already handled by X
}
template<set_type X, vector_space_type V, typename Tag>
void cAffineSpaceSetTraits<X,V,Tag>::init(underlying_type& o_value, const underlying_type& i_value)
{
    o_value = i_value;
}
template<set_type X, vector_space_type V, typename Tag>
void cAffineSpaceSetTraits<X,V,Tag>::init(underlying_type& o_value, const V& i_point)
{
    o_value = underlying_type(X{},i_point);
}
template<set_type X, vector_space_type V, typename Tag>
void cAffineSpaceSetTraits<X,V,Tag>::init(underlying_type& o_value, const X& i_origin, const V& i_point)
{
    o_value = underlying_type(i_origin,i_point);
}
template<set_type X, vector_space_type V, typename Tag>
template<vector_space_type W>
requires ( mpl::is_same_type<V,W>::value && (mpl::is_same_type<X,V>::value == false) )
void cAffineSpaceSetTraits<X,V,Tag>::init(underlying_type& o_value, const W& i_value)
{
    o_value = i_value.getValue();
}
template<set_type X, vector_space_type V, typename Tag>
void cAffineSpaceSetTraits<X,V,Tag>::deinit(underlying_type& o_value)
{
    //already handled by X
}
template<set_type X, vector_space_type V, typename Tag>
void cAffineSpaceSetTraits<X,V,Tag>::assign(underlying_type& o_value, const underlying_type& i_value)
{
    o_value = i_value;
}
template<set_type X, vector_space_type V, typename Tag>
bool cAffineSpaceSetTraits<X,V,Tag>::cmp(const underlying_type& i_lhs, const underlying_type& i_rhs)
{
    return s_action.eval(i_lhs.first,i_lhs.second) == s_action.eval(i_rhs.first,i_rhs.second);
}
template<set_type X, vector_space_type V, typename Tag>
X cAffineSpaceSetTraits<X,V,Tag>::action(const X& i_lhs, const V& i_rhs)
{
    return s_action.eval(i_lhs,i_rhs);
}

}
}
