#pragma once

namespace yame
{
namespace math
{

template<module_type Im, vector_space_type Dom>
inline vector_base kernel(const LF<Im,Dom>& i_appl);

}
}

#include "Math/detail/cFunctionSpaceOps.tpp"
