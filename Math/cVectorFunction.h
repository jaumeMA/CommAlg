#pragma once

#include "Math/cScalarFunction.h"
#include <utility>

namespace yame
{
namespace math
{
namespace detail
{

template<module_type Im , vector_space_type Dom>
class vector_function : protected container::cTupla<scalar_function<typename Im::traits::module_traits::ring,Dom>,Im::dimension()>
{
    typedef scalar_function<typename Im::traits::module_traits::ring,Dom> scalar_function_t;
    typedef container::cTupla<scalar_function_t,Im::dimension()> base;

public:
    typedef typename scalar_function<typename Im::traits::module_traits::ring,Dom>::base_function base_function;
    typedef typename base_function::func_ptr_base func_ptr_base;
    using base::base;
    using base::operator[];
    using base::get;
    using base::operator=;
    using base::operator==;
    using base::operator!=;

    template<size_t Component>
    inline static const scalar_function_t& get_scalar_function(const vector_function& i_func);
	inline Im eval(const Dom& i_point) const;

private:
    template<int ... Components, int ... Indexs>
    inline Im _eval(const mpl::sequence<Components...>&, const mpl::sequence<Indexs...>&, const Dom& i_point) const;
};

}

template<module_type Im, vector_space_type Dom>
requires requires{ { Im::dimension() } }
detail::vector_function<Im,Dom> underlying_function_type(const Im&, const Dom&);

}
}

#include "Math/detail/cVectorFunction.tpp"
