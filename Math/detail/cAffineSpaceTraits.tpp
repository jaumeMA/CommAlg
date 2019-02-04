
namespace yame
{
namespace math
{

template<set_type X, vector_space_type V>
void cAffineSpaceSetTraits<X,V>::init(underlying_type& o_value)
{
    //already handled by X
}
template<set_type X, vector_space_type V>
void cAffineSpaceSetTraits<X,V>::init(underlying_type& o_value, const underlying_type& i_value)
{
    o_value = i_value;
}
template<set_type X, vector_space_type V>
void cAffineSpaceSetTraits<X,V>::init(underlying_type& o_value, const V& i_point)
{
    o_value = underlying_type(X{},i_point);
}
template<set_type X, vector_space_type V>
void cAffineSpaceSetTraits<X,V>::init(underlying_type& o_value, const X& i_origin, const V& i_point)
{
    o_value = underlying_type(i_origin,i_point);
}
template<set_type X, vector_space_type V>
template<vector_space_type W>
requires ( mpl::is_same_type<V,W>::value && (mpl::is_same_type<X,V>::value == false) )
void cAffineSpaceSetTraits<X,V>::init(underlying_type& o_value, const W& i_value)
{
    o_value = i_value.getValue();
}
template<set_type X, vector_space_type V>
void cAffineSpaceSetTraits<X,V>::deinit(underlying_type& o_value)
{
    //already handled by X
}
template<set_type X, vector_space_type V>
void cAffineSpaceSetTraits<X,V>::assign(underlying_type& o_value, const underlying_type& i_value)
{
    o_value = i_value;
}
template<set_type X, vector_space_type V>
bool cAffineSpaceSetTraits<X,V>::cmp(const underlying_type& i_lhs, const underlying_type& i_rhs)
{
    return i_lhs == i_rhs;
}

template<set_type X, vector_space_type V, typename Tag>
X cAffineHomogeneousSpaceTraits<X,V,Tag>::action(const X& i_lhs, const V& i_rhs)
{
    return s_action(i_lhs,i_rhs);
}

}
}
