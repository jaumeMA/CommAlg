#pragma once

#include "Math/cSet.h"
#include "Math/cAffineSpaceTraits.h"
#include "Math/detail/cMathTags.h"
#include "Math/detail/cMathTraitsConceptHelper.h"
#include "Math/detail/cMathTypeConceptHelper.h"
#include "Math/cVectorSpace.h"
#include "Math/cGroupAction.h"

#define INSTANTIATE_AFFINE_SPACE(_NAME,_SET,_VECTOR_SPACE) \
struct _NAME##_t; \
using _NAME = cAffineSpace<cAffineSpaceTraits<_SET,_VECTOR_SPACE,_NAME##_t>>; \
template<> \
const detail::right_group_action<_SET,_VECTOR_SPACE> _NAME::homogeneous_space_traits::s_action = usual_vector_space_displacement<_SET,_VECTOR_SPACE>;

namespace yame
{
namespace math
{

template<affine_space_traits_type Traits>
class cAffineSpace : public cSet<typename Traits::set_traits>, public detail::affine_space_tag
{
public:
    typedef typename Traits::vector_space vector_space;
    typedef typename Traits::homogeneous_space_traits homogeneous_space_traits;
	using cSet<typename Traits::set_traits>::cSet;
	using cSet<typename Traits::set_traits>::operator=;
	using cSet<typename Traits::set_traits>::operator!=;

    static inline constexpr size_t dimension()
    {
        return vector_space::dimension();
    }
    friend inline bool operator==(const cAffineSpace& i_lhs, const cAffineSpace& i_rhs)
    {
        typedef typename Traits::underlying_type underlying_type;

        const underlying_type& lhsValue = i_lhs.getValue();
        const underlying_type& rhsValue = i_rhs.getValue();
        return homogeneous_space_traits::action(lhsValue.first,lhsValue.second) == homogeneous_space_traits::action(rhsValue.first,rhsValue.second);
    }
    friend inline bool operator!=(const cAffineSpace& i_lhs, const cAffineSpace& i_rhs)
    {
        typedef typename Traits::underlying_type underlying_type;

        const underlying_type& lhsValue = i_lhs.getValue();
        const underlying_type& rhsValue = i_rhs.getValue();
        return homogeneous_space_traits::action(lhsValue.first,lhsValue.second) != homogeneous_space_traits::action(rhsValue.first,rhsValue.second);
    }
    friend inline cAffineSpace operator+(const cAffineSpace& i_lhs, const vector_space& i_rhs)
    {
        typedef typename Traits::underlying_type underlying_type;

        const underlying_type& thisValue = i_lhs.getValue();
        return cAffineSpace(homogeneous_space_traits::action(thisValue.first,i_rhs),i_rhs);
    }
};

template<set_type X, vector_space_type V>
static const auto usual_vector_space_displacement = [](const X& i_lhs, const V& i_rhs){ return i_lhs + i_rhs; };

INSTANTIATE_AFFINE_SPACE(AR1,R1,R1)
INSTANTIATE_AFFINE_SPACE(AR2,R2,R2)
INSTANTIATE_AFFINE_SPACE(AR3,R3,R3)

INSTANTIATE_AFFINE_SPACE(AC1,C1,C1)
INSTANTIATE_AFFINE_SPACE(AC2,C2,C2)
INSTANTIATE_AFFINE_SPACE(AC3,C3,C3)

}
}

//#include "Math/detail/cAffineSpace.tpp"
