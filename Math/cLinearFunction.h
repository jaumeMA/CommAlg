#pragma once

#include "Math/cScalarFunction.h"

#define DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(NAME,OP) \
friend inline linear_function<Im,Dom> operator OP(const linear_function<Im,Dom>& i_lhs, const linear_function<Im,Dom>& i_rhs) \
{ \
    return static_cast<const base_function&>(i_lhs) OP static_cast<const base_function&>(i_rhs); \
}
#define DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION_CONSTANT(NAME,OP) \
friend inline linear_function<Im,Dom> operator OP(const linear_function<Im,Dom>& i_lhs, const typename Dom::ring& i_rhs) \
{ \
    return static_cast<const base_function&>(i_lhs) OP constant_function<typename Dom::ring,Dom>(i_rhs); \
} \
friend inline linear_function<Im,Dom> operator OP(const typename Dom::ring& i_lhs, const linear_function<Im,Dom>& i_rhs) \
{ \
    return constant_function<typename Dom::ring,Dom>(i_lhs) OP static_cast<const base_function&>(i_rhs); \
}

namespace yame
{
namespace math
{
namespace detail
{

template<ring_type Im, vector_space_type Dom>
class linear_function : public scalar_function<Im,Dom>
{
    template<ring_type IIm, vector_space_type DDom>
    friend class linear_function;

public:
    template<ring_type IIm, vector_space_type DDom>
    struct move_to
    {
        typedef linear_function<IIm,DDom> type;
    };

    typedef Im return_type;
    typedef scalar_function<Im,Dom> func_base;
    typedef typename func_base::base_function base_function;
    typedef typename base_function::func_ptr_base func_ptr_base;
    using func_base::operator();
    using func_base::eval;
    using func_base::clone;

    linear_function() = default;
    linear_function(const Dom& i_value);
    linear_function(const projection_function<Im,Dom>& i_component);
    linear_function(const constant_function<Im,Dom>& i_constValue);
    static linear_function<Im,Dom> clone(const func_ptr_base* i_funcPtr);
    linear_function& operator=(const Dom& i_value);
    template<callable_type Return, typename ... Args>
    Return specialize(Args&& ... i_args) const;
    vector<Im,Dom::dimension() + 1> as_vector() const;

    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(sum,+)
    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(subs,-)
    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION_CONSTANT(sum,+)
    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION_CONSTANT(subs,-)
    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION_CONSTANT(prod,*)

private:
    linear_function(const base_function& i_base);
    template<int ... Indexs>
    inline vector<Im,Dom::dimension() + 1> _as_vector(const mpl::sequence<Indexs...>&) const;
    template<typename ... Args>
    requires ( mpl::get_num_types<Args...>::value == Dom::dimension() && mpl::are_same_type<Dom,Args...>::value )
    inline vector<Im,Dom::dimension() + 1> _as_vector(const Args& ... i_bases) const;
};

}

template<ring_type Im, vector_space_type Dom>
detail::linear_function<Im,Dom> underlying_linear_function_type(const Im&, const Dom&);

}
}

#include "Math/detail/cLinearFunction.tpp"
