#pragma once

#include "YTL/functional/cFunction.h"
#include "Math/detail/cMathTypeConceptHelper.h"

namespace yame
{
namespace math
{
namespace detail
{

template<group_type G, set_type X>
using left_group_action = ytl::function<X(const G&, const X&)>;

template<set_type X, group_type G>
using right_group_action = ytl::function<X(const X&, const G&)>;

}
}
}
