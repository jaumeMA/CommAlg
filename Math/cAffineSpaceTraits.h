#pragma once

#include "Math/cGroupAction.h"
#include "YTL/functional/detail/cFunctionConceptHelper.h"

namespace yame
{
namespace math
{

template<typename Traits>
struct AffineSpaceExtendedAccess : virtual public detail::ISet<Traits>
{
    //TO BE DEFINED
};

template<set_type X, vector_space_type V>
struct cAffineSpaceSetTraits
{
    typedef container::cPair<X,V> underlying_type;

    typedef AffineSpaceExtendedAccess<cAffineSpaceSetTraits<X,V>> extended_structure;
    static void init(underlying_type& o_value);
    static void init(underlying_type& o_value, const underlying_type& i_value);
    static void init(underlying_type& o_value, const V& i_point);
    static void init(underlying_type& o_value, const X& i_origin, const V& i_point);
    template<vector_space_type W>
    requires ( mpl::is_same_type<V,W>::value && (mpl::is_same_type<X,V>::value == false) )
    static void init(underlying_type& o_value, const W& i_value);
    static void deinit(underlying_type& o_value);
    static void assign(underlying_type& o_value, const underlying_type& i_value);
    static bool cmp(const underlying_type& i_lhs, const underlying_type& i_rhs);
};

template<set_type X, vector_space_type V, typename Tag>
struct cAffineHomogeneousSpaceTraits
{
    typedef cAffineSpaceSetTraits<X,V> set_traits;
    typedef typename set_traits::underlying_type underlying_type;

    static X action(const X& i_lhs, const V& i_rhs);

    static const detail::right_group_action<X,V> s_action;
};

template<set_type X, vector_space_type V, typename Tag>
struct cAffineSpaceTraits
{
    typedef V vector_space;
    typedef X set;
    typedef cAffineHomogeneousSpaceTraits<X,V,Tag> homogeneous_space_traits;
    typedef typename homogeneous_space_traits::set_traits set_traits;
    typedef typename set_traits::underlying_type underlying_type;
};

}
}

#include "Math/detail/cAffineSpaceTraits.tpp"
