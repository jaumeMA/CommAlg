#pragma once

#include "Math/detail/cVectorTemplateHelper.h"
#include "Math/cVectorFunction.h"
#include "Math/cLinearVectorFunction.h"
#include "Math/cFunctionSpace.h"
#include "Math/detail/cVectorFunctionTemplateHelper.h"

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
static VFR1 FUNC_NAME##Real = VFR1(NESTED_FUNC_NAME##r); \
static VFC1 FUNC_NAME##Complex = VFC1(NESTED_FUNC_NAME##c); \
template<module_type Im, vector_space_type Dom> \
static VF<Im,Dom> FUNC_NAME = VF<Im,Dom>(NESTED_FUNC_NAME##_function_t<typename Im::ring,Dom>());\
} \
}

namespace yame
{
namespace math
{
namespace detail
{

template<module_type Im, vector_space_type Dom, callable_type Function>
struct ExtendedVectorFunctionSpaceSet : virtual public detail::ISet<FunctionSpaceSetTraits<Im,Dom,Function>>
{
    typedef Function underlying_type;
    typedef cFunctionSpace<Im,Dom,Function> FinalObject;
    typedef typename Im::traits::module_traits::ring nested_im_t;
private:
    template<int ... Components, typename ... Args>
    Im _eval(const mpl::sequence<Components...>&, Args&& ... i_args) const;

public:
    underlying_type get_nested_function() const;
    template<typename IIm, typename DDom>
    requires (mpl::is_type_constructible<Im,IIm>::value && mpl::is_type_constructible<Dom,DDom>::value )
    static void init(underlying_type& o_value, const cFunctionSpace<IIm,DDom,Function>& i_value);
    template<typename ... Args>
    auto operator()(Args&& ... i_args) const;

    template<size_t Index>
    requires (Index < Dom::dimension())
    static inline linear_function<nested_im_t,Dom> _x_()
    {
        static const projection_function<nested_im_t,Dom> s_componentFunction(mpl::numeric_type<Index>{});

        return s_componentFunction;
    }
};

template<module_type Im, vector_space_type Dom, callable_type Function>
struct ExtendedLinearVectorFunctionSpaceSet : public ExtendedVectorFunctionSpaceSet<Im,Dom,Function>
{
public:
    using ExtendedVectorFunctionSpaceSet<Im,Dom,Function>::get_nested_function;
    using ExtendedVectorFunctionSpaceSet<Im,Dom,Function>::operator();
    using ExtendedVectorFunctionSpaceSet<Im,Dom,Function>::_x_;

    matrix<typename Im::ring,Im::dimension(),Dom::dimension()> as_matrix() const;
};

}

template<module_type Im, vector_space_type Dom>
detail::ExtendedVectorFunctionSpaceSet<Im,Dom,detail::vector_function<Im,Dom>> underlying_function_extension_type(const detail::vector_function<Im,Dom>&, const Im&,const Dom&);

template<module_type Im, vector_space_type Dom>
detail::ExtendedLinearVectorFunctionSpaceSet<Im,Dom,detail::linear_vector_function<Im,Dom>> underlying_function_extension_type(const detail::linear_vector_function<Im,Dom>&, const Im&,const Dom&);

//linear and non linear vector functions

template<module_type Im, vector_space_type Dom>
using VF = F<Im,Dom,detail::vector_function<Im,Dom>>;

template<vector_space_type Dom>
using VFR = VF<R1,Dom>;

using VFR1 = VFR<R1>;
using VFR2 = VFR<R2>;
using VFR3 = VFR<R3>;

template<int N>
using VFRn = VFR<Rn<N>>;

template<vector_space_type Dom>
using VFC = VF<C1,Dom>;

using VFC1 = VFC<C1>;
using VFC2 = VFC<C2>;
using VFC3 = VFC<C3>;

template<int N>
using VFCn = VFC<Cn<N>>;

//linear vector functions

template<module_type Im, vector_space_type Dom>
using LF = F<Im,Dom,detail::linear_vector_function<Im,Dom>>;

template<vector_space_type Dom>
using LFR = LF<R1,Dom>;

using LFR1 = LFR<R1>;
using LFR2 = LFR<R2>;
using LFR3 = LFR<R3>;

template<int N>
using LFRn = LFR<Rn<N>>;

template<vector_space_type Dom>
using LFC = LF<C1,Dom>;

using LFC1 = LFC<C1>;
using LFC2 = LFC<C2>;
using LFC3 = LFC<C3>;

template<int N>
using LFCn = LFC<Cn<N>>;

}
}

DECLARE_MATH_FUNCTION_SPACE(Sin, sin);
DECLARE_MATH_FUNCTION_SPACE(Cos, cos);
DECLARE_MATH_FUNCTION_SPACE(Tan, tan);
DECLARE_MATH_FUNCTION_SPACE(Exp, exp);
DECLARE_MATH_FUNCTION_SPACE(Log, log);

#include "Math/detail/cVectorFunctionSpace.tpp"
