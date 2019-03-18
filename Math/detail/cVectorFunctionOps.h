#pragma once

#define DECLARE_MATH_FUNCTION_SPACE(FUNC_NAME, NESTED_FUNC_NAME) \
static VFR1 FUNC_NAME##Real = VFR1(NESTED_FUNC_NAME##r); \
static VFC1 FUNC_NAME##Complex = VFC1(NESTED_FUNC_NAME##c); \
template<module_type Im, vector_space_type Dom> \
static VF<Im,Dom> FUNC_NAME = VF<Im,Dom>(NESTED_FUNC_NAME##_function_t<typename Im::ring,Dom>());

namespace yame
{
namespace math
{

DECLARE_MATH_FUNCTION_SPACE(Sin, sin);
DECLARE_MATH_FUNCTION_SPACE(Cos, cos);
DECLARE_MATH_FUNCTION_SPACE(Tan, tan);
DECLARE_MATH_FUNCTION_SPACE(Exp, exp);
DECLARE_MATH_FUNCTION_SPACE(Log, log);

}
}
