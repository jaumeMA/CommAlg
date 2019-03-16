#pragma once

#include "Math/cLinearFunction.h"
#include "YTL/container/cTupla.h"

namespace yame
{
namespace math
{
namespace detail
{

template<module_type Im , vector_space_type Dom>
class linear_vector_function : protected container::cTupla<linear_function<typename Im::ring,Dom>,Im::dimension()>
{
    typedef linear_function<typename Im::ring,Dom> linear_function_t;
    typedef container::cTupla<linear_function_t,Im::dimension()> base;
    friend Im eval(const linear_vector_function<Im,Dom>&,const Dom&);

    template<int ... Indexs>
    linear_vector_function(const mpl::sequence<Indexs...>&, const matrix<typename Dom::field,Im::dimension(),Dom::dimension()>& i_linearValue);

public:
    template<module_type IIm, vector_space_type DDom>
    struct move_to
    {
        typedef linear_vector_function<IIm,DDom> type;
    };

    typedef linear_function<typename Im::ring,Dom> particle_function_t;
    typedef typename scalar_function<typename Im::ring,Dom>::base_function base_function;
    typedef typename base_function::func_ptr_base func_ptr_base;
    using base::base;
    using base::operator[];
    using base::get;
    using base::operator=;
    using base::operator==;
    using base::operator!=;

    linear_vector_function() = default;
    linear_vector_function(const matrix<typename Dom::field,Im::dimension(),Dom::dimension()>& i_linearValue);
    linear_vector_function& operator=(const matrix<typename Dom::field,Im::dimension(),Dom::dimension()>& i_linearValue);
	inline Im operator()(const Dom& i_point) const;
	template<module_type IIm>
    requires (Dom::dimension() == 0)
	operator IIm() const;
    matrix<typename Im::ring,Im::dimension(),Dom::dimension()> as_matrix() const;

private:
    template<int ... Components, int ... Indexs>
    requires(mpl::get_num_ranks<Components...>::value == Im::dimension() && mpl::get_num_ranks<>::value == Dom::dimension() )
    inline Im _eval(const mpl::sequence<Components...>&, const mpl::sequence<Indexs...>&, const Dom& i_point) const;
    template<int ... Components>
    inline Im _eval(const mpl::sequence<Components...>&) const;
    template<int ... Components>
    requires(mpl::get_num_ranks<Components...>::value == Im::dimension() )
    inline matrix<typename Im::ring,Im::dimension(),Dom::dimension()> _as_matrix(const mpl::sequence<Components...>&) const;
};

}

template<module_type Im, vector_space_type Dom>
detail::linear_vector_function<Im,Dom> underlying_linear_function_type(const Im&, const Dom&);

}
}

#include "Math/detail/cLinearVectorFunction.tpp"
