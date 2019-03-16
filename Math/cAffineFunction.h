#pragma once

#include "Math/detail/cMathTypeConceptHelper.h"
#include "YTL/container/cPair.h"
#include "Math/cLinearVectorFunction.h"

#define DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(NAME,OP) \
friend inline affine_function<Im,Dom> operator OP(const affine_function<Im,Dom>& i_lhs, const affine_function<Im,Dom>& i_rhs) \
{ \
    return affine_function<Im,Dom>(i_lhs.get_set_function() OP i_rhs.get_set_function(),i_lhs.get_vector_function() OP i_rhs.get_vector_function()); \
}

namespace yame
{
namespace math
{
namespace detail
{

template<affine_space_type Im, affine_space_type Dom>
class affine_function
{
    friend Im eval(const affine_function<Im,Dom>& i_function, const Dom& i_point);

public:
    typedef typename Dom::vector_space dom_vector_space;
    typedef typename Dom::set dom_set;
    typedef typename Im::vector_space im_vector_space;
    typedef typename Im::set im_set;
    typedef linear_vector_function<typename Im::vector_space,typename Dom::vector_space> vector_function_t;
    typedef scalar_function<typename Im::set,typename Dom::set> set_function_t;

    template<affine_space_type IIm, affine_space_type DDom>
    struct move_to
    {
        typedef affine_function<IIm,DDom> type;
    };

    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(sum,+)
    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(subs,-)

    affine_function() = default;
    affine_function(const set_function_t& i_originFunction, const vector_function_t& i_vectorFunction);
    inline const set_function_t& get_set_function() const;
    inline const vector_function_t& get_vector_function() const;
	inline Im operator()(const Dom& i_point) const;
	template<module_type IIm>
    requires (Dom::dimension() == 0)
	inline operator IIm() const;
    inline matrix<typename Im::vector_space::ring,Im::dimension(),Dom::dimension()+1> as_matrix(const dom_set& i_origin) const;

private:
    template<int ... Components>
    inline matrix<typename Im::vector_space::ring,Im::dimension(),Dom::dimension()+1> _as_matrix(const mpl::sequence<Components...>&, const dom_set& i_origin) const;

    container::cPair<set_function_t,vector_function_t> m_function;
};

}

template<affine_space_type Im, affine_space_type Dom>
detail::affine_function<Im,Dom> underlying_function_type(const Im&, const Dom&);

}
}

#include "Math/detail/cAffineFunction.tpp"
