#pragma once

#include "Math/detail/cMathTraitsConceptHelper.h"
#include "Math/detail/cMathTags.h"

namespace yame
{
namespace math
{
namespace detail
{

template<vector_space_traits_type Traits, typename FinalObject>
class cAffineSpaceImpl : virtual public ISet<typename Traits::set_traits>, public affine_space_tag
{
public:
    static inline constexpr size_t dimension()
    {
        return Traits::Dimension;
    }
	typedef typename Traits::underlying_type underlying_type;
	typedef typename Traits::particle particle;
    typedef typename cModuleImpl<typename Traits::module_traits,FinalObject>::group group;
};

}
}
}
