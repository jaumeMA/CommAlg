#pragma once

#include "Math/cAffineSpace.h"
#include "Math/cAffineFunction.h"
#include "Math/cFunctionSpace.h"

namespace yame
{
namespace math
{
namespace detail
{

template<affine_space_type Im, affine_space_type Dom, callable_type Function>
struct ExtendedAffineFunctionSpaceSet
{
    typedef typename Im::vector_space::ring ring;
    typedef typename Dom::set dom_set;

public:
    template<size_t Index>
    requires (Index < Dom::dimension())
    static inline affine_function<Im,Dom> _x_()
    {
        static const projection_function<ring,Dom> s_componentFunction(mpl::numeric_type<Index>{});

        return s_componentFunction;
    }
    matrix<ring,Im::dimension(),Dom::dimension()+1> as_matrix(const dom_set& i_origin) const;
};

}

template<affine_space_type Im, affine_space_type Dom>
using AF = F<Im,Dom,detail::affine_function<Im,Dom>>;

template<affine_space_type Dom>
using AFR = AF<AR1,Dom>;

using AFR1 = AFR<AR1>;
using AFR2 = AFR<AR2>;
using AFR3 = AFR<AR3>;

template<affine_space_type Dom>
using AFC = AF<AC1,Dom>;

using AFC1 = AFC<AC1>;
using AFC2 = AFC<AC2>;
using AFC3 = AFC<AC3>;

}
}

#include "Math/detail/cAffineFunctionSpace.tpp"
