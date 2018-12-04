#pragma once

#include "Math/detail/cVectorTemplateHelper.h"
#include "Math/cVectorFunction.h"
#include "Math/cFunctionSpace.h"
#include "Math/detail/cVectorFunctionTemplateHelper.h"
#include "Math/cMathOps.h"

#define x_(_Index) _x_<_Index>()
#define x_0 x_(0)
#define x_1 x_(1)
#define x_2 x_(2)
#define x_3 x_(3)
#define x_4 x_(4)
#define x_5 x_(5)
#define x_6 x_(6)
#define x_7 x_(7)
#define x_8 x_(8)
#define x_9 x_(9)

#define DECLARE_MATH_FUNCTION_SPACE(FUNC_NAME, NESTED_FUNC_NAME) \
namespace yame \
{ \
namespace math \
{ \
static FR1 FUNC_NAME##Real = FR1(NESTED_FUNC_NAME##r); \
static FC1 FUNC_NAME##Complex = FC1(NESTED_FUNC_NAME##c); \
} \
}

namespace yame
{
namespace math
{
namespace detail
{

template<module_type Im, vector_space_type Dom>
struct ExtendedVectorFunctionSpaceSet : virtual public detail::ISet<FunctionSpaceSetTraits<Im,Dom>>
{
    typedef decltype(underlying_function_type(std::declval<Im>(),std::declval<Dom>())) underlying_type;
    typedef cFunctionSpace<Im,Dom> FinalObject;
    typedef typename Im::traits::module_traits::ring nested_im_t;

    struct const_function_constructor
    {
        const_function_constructor() = default;
        auto operator()(nested_im_t i_constantValue) const;
    };

    underlying_type get_nested_function() const;
    template<typename IIm, typename DDom>
    requires (mpl::is_type_constructible<Im,IIm>::value && mpl::is_type_constructible<Dom,DDom>::value )
    static void init(underlying_type& o_value, const cFunctionSpace<IIm,DDom>& i_value);
    template<typename ... Args>
    auto operator()(Args&& ... i_args) const;
    template<typename ... Args>
    auto eval(Args&& ...) const;

    template<size_t Index>
    requires (Index < Dom::dimension())
    static inline underlying_type _x_()
    {
        return projection<nested_im_t,Dom>(mpl::numeric_type<Index>{});
    }
    static const const_function_constructor C;
};

}

template<module_type Im, vector_space_type Dom>
detail::ExtendedVectorFunctionSpaceSet<Im,Dom> underlying_function_extension_type(const Im&,const Dom&);

template<vector_space_type Dom>
using FR = cFunctionSpace<R1,Dom>;

using FR1 = FR<R1>;
using FR2 = FR<R2>;
using FR3 = FR<R3>;

template<int N>
using FRn = FR<Rn<N>>;

template<vector_space_type Dom>
using FC = cFunctionSpace<C1,Dom>;

using FC1 = FC<C1>;
using FC2 = FC<C2>;
using FC3 = FC<C3>;

template<int N>
using FCn = FC<Cn<N>>;

}
}

DECLARE_MATH_FUNCTION_SPACE(Sin, sin);
DECLARE_MATH_FUNCTION_SPACE(Cos, cos);
DECLARE_MATH_FUNCTION_SPACE(Tan, tan);
DECLARE_MATH_FUNCTION_SPACE(Exp, exp);
DECLARE_MATH_FUNCTION_SPACE(Log, log);

#include "Math/detail/cVectorFunctionSpace.tpp"
