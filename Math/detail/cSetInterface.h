#pragma once

#include "Math/detail/cMathTraitsConceptHelper.h"

namespace yame
{
namespace math
{

template<set_traits_type Traits>
class cSet;

namespace detail
{

template<set_traits_type Traits>
class ISet
{
    friend cSet<Traits>;

public:
	typedef typename Traits::underlying_type underlying_type;

    virtual cSet<Traits>& operator=(const cSet<Traits>& other) = 0;
    virtual cSet<Traits>& operator=(cSet<Traits>&& other) = 0;
    virtual cSet<Traits>& operator=(const underlying_type& i_value) = 0;
    virtual cSet<Traits>& operator=(underlying_type&& i_value) = 0;
    virtual const underlying_type& getValue() const = 0;

protected:
    virtual underlying_type& getValue() = 0;
    virtual void setValue(const underlying_type& i_value) = 0;
};

}
}
}
