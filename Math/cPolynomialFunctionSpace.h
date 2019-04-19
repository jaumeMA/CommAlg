#pragma once

#include "Math/cAffineSpace.h"
#include "Math/cPolynomialFunction.h"
#include "Math/cFunctionSpace.h"
#include "Math/cPolynomialAlgebra.h"

namespace yame
{
namespace math
{
namespace detail
{

template<affine_space_type>
class ExtendedPolynomialFunctionSpaceSet;

template<field_type K, int N>
struct ExtendedPolynomialFunctionSpaceSet<AKn<K,N>>
{
public:
    template<size_t Index>
    requires (Index < N)
    static inline polynomial_functio<Space> _x_()
    {
        static const projection_function<K,Kn<N>> s_componentFunction(mpl::numeric_type<Index>{});

        return s_componentFunction;
    }
    operator polynomial<K>() const;
};

}

template<field_type K, int N>
detail::ExtendedPolynomialFunctionSpaceSet<AKn<K,N>> underlying_function_extension_type(const detail::polynomial_function<AKn<K,N>>&, const K&,const Kn<K,N>&);

template<field_type K, int N>
using PF = F<K,Kn<K,N>,detail::polynomial_function<AKn<K,N>>>;

using PFR1 = PF<AR1>;
using PFR2 = PF<AR2>;
using PFR3 = PF<AR3>;

using PFC1 = PF<AC1>;
using PFC2 = PF<AC2>;
using PFC3 = PF<AC3>;

}
}

#include "Math/detail/cPolynomialFunctionSpace.tpp"
