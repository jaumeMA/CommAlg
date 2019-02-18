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
    typedef typename Traits::set set;
    typedef typename Traits::vector_space vector_space;
    typedef typename Traits::underlying_type underlying_type;

    inline const set& get_set_component() const;
    inline const vector_space& get_vector_space_component() const;
};

template<set_type X, vector_space_type V, typename Tag>
struct cAffineSpaceSetTraits
{
    typedef container::cPair<X,V> underlying_type;
    typedef V vector_space;
    typedef X set;

    typedef AffineSpaceExtendedAccess<cAffineSpaceSetTraits<X,V,Tag>> extended_structure;
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

    static X action(const X& i_lhs, const V& i_rhs);

    static const detail::right_group_action<X,V> s_action;
};

template<set_type X, vector_space_type V, typename Tag>
struct cAffineSpaceTraits
{
    typedef V vector_space;
    typedef X set;
    typedef cAffineSpaceSetTraits<X,V,Tag> set_traits;
    typedef typename set_traits::underlying_type underlying_type;
};

}
}

#include "Math/detail/cAffineSpaceTraits.tpp"
