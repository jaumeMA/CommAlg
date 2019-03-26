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
class vector_function : protected container::cTupla<scalar_function<typename Im::ring,Dom>,Im::dimension()>
{
    typedef container::cTupla<scalar_function<typename Im::ring,Dom>,Im::dimension()> base;
    template<int ... Indexs>
    vector_function(const mpl::sequence<Indexs...>&, const matrix<typename Dom::field,Im::dimension(),Dom::dimension()>& i_linearValue);

public:
    template<module_type IIm, vector_space_type DDom>
    struct move_to
    {
        typedef vector_function<IIm,DDom> type;
    };

    typedef scalar_function<typename Im::ring,Dom> particle_function_t;

    typedef typename scalar_function<typename Im::ring,Dom>::base_function base_function;
    typedef typename base_function::func_ptr_base func_ptr_base;
    using base::base;
    using base::operator[];
    using base::get;
    using base::operator=;
    using base::operator==;
    using base::operator!=;

    vector_function() = default;
    template<typename ... Args>
    vector_function(const Args& ... i_args);
    vector_function(const matrix<typename Dom::field,Im::dimension(),Dom::dimension()>& i_linearValue);
    vector_function& operator=(const matrix<typename Dom::field,Im::dimension(),Dom::dimension()>& i_linearValue);
	inline Im operator()(const Dom& i_point) const;
	template<module_type IIm>
    requires (Dom::dimension() == 0)
	operator IIm() const;

private:
    template<int ... Components, int ... Indexs>
    Im _eval(const mpl::sequence<Components...>&, const mpl::sequence<Indexs...>&, const Dom& i_point) const;
    template<int ... Components>
    Im _eval(const mpl::sequence<Components...>&) const;
};

template<int ... Components, module_type Im , vector_space_type Dom>
inline Im eval(const mpl::sequence<Components...>&);
template<module_type Im , vector_space_type Dom, typename ... Args>
inline Im eval(const vector_function<Im,Dom>& i_function, Args&& ... i_args);

}

template<module_type Im, vector_space_type Dom>
requires requires{ { Im::dimension() } }
detail::vector_function<Im,Dom> underlying_function_type(const Im&, const Dom&);

}
}

#include "Math/detail/cVectorFunction.tpp"
