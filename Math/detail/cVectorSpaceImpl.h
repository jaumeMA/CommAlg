#pragma once

#include "Math/detail/cAlgebraImpl.h"
#include "Math/detail/cMathTraitsConceptHelper.h"
#include "Math/detail/cMathTags.h"

namespace yame
{
namespace math
{
namespace detail
{

template<vector_space_traits_type Traits, typename FinalObject>
class cVectorSpaceImpl : public cModuleImpl<typename Traits::module_traits,FinalObject>, public vector_space_tag
{
public:
    static inline constexpr size_t dimension()
    {
        return Traits::Dimension;
    }
    static inline FinalObject base(size_t i_index)
    {
        return Traits::module_traits::base(i_index);
    }
	typedef typename Traits::underlying_type underlying_type;
	typedef typename Traits::particle particle;
    typedef typename Traits::field field;
    typedef typename cModuleImpl<typename Traits::module_traits,FinalObject>::group group;
};

NESTED_STRUCTURE_ACQUIRER(cVectorSpaceImpl,vector_space_traits_type)

}

}

}

#include "Math/detail/cVectorSpaceImpl.tpp"
