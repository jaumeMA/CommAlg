#pragma once

#include "YTL/functional/cComposedCallable.h"

#define DEFINE_HIGHER_ORDER_UNARY_FUNCTION(NAME,OP) \
namespace yame \
{ \
namespace ytl \
{ \
template<typename Return> \
struct NAME##_unary_op\
{ \
    typedef decltype((OP std::declval<const Return>())) inner_return; \
    NAME##_unary_op() = default; \
    inner_return operator()(Return i_value) const \
    { \
        return OP i_value; \
    } \
}; \
template<typename ...> \
class NAME##_callable_t; \
 \
template<typename Return, typename ... Types> \
class NAME##_callable_t<Return(Types...)> : public yame::ytl::composed_callable<NAME##_unary_op<Return>,Types...> \
{ \
public: \
    NAME##_callable_t(const yame::ytl::function<Return(Types...)>& i_func) \
    : yame::ytl::composed_callable<NAME##_unary_op<Return>,Types...>(NAME##_unary_op<Return>(),i_func) \
    {} \
}; \
template<typename Return, typename ... Types> \
yame::ytl::function<Return(Types...)> operator OP(const yame::ytl::function<Return(Types...)>& i_function) \
{ \
    return yame::ytl::NAME##_callable_t<Return(Types...)>(i_function); \
} \
} \
}

#define DEFINE_HIGHER_ORDER_BINARY_FUNCTION(NAME,OP) \
namespace yame \
{ \
namespace ytl \
{ \
template<typename Return> \
struct NAME##_binary_op\
{ \
    typedef decltype((*reinterpret_cast<const Return*>(NULL) OP *reinterpret_cast<const Return*>(NULL))) inner_return; \
    NAME##_binary_op() = default; \
    inner_return operator()(Return i_lhs, Return i_rhs) const \
    { \
        return i_lhs OP i_rhs; \
    } \
}; \
template<typename...> \
class NAME##_callable_t; \
 \
template<typename Return, typename ... Types> \
class NAME##_callable_t<Return(Types...)> : public yame::ytl::composed_callable<NAME##_binary_op<Return>,Types...> \
{ \
public: \
    NAME##_callable_t(const yame::ytl::function<Return(Types...)>& i_lhs, const yame::ytl::function<Return(Types...)>& i_rhs) \
    : yame::ytl::composed_callable<NAME##_binary_op<Return>,Types...>(NAME##_binary_op<Return>(),i_lhs,i_rhs) \
    {} \
}; \
template<typename Return, typename ... Types> \
yame::ytl::function<Return(Types...)> operator OP(const yame::ytl::function<Return(Types...)>& i_lhs, const yame::ytl::function<Return(Types...)>& i_rhs) \
{ \
    if(i_lhs != null_ptr && i_rhs != null_ptr) \
    { \
        return yame::ytl::NAME##_callable_t<Return(Types...)>(i_lhs, i_rhs); \
    } \
    else if(i_lhs != null_ptr) \
    { \
        return i_lhs; \
    } \
    else \
    { \
        return i_rhs; \
    } \
} \
} \
}


DEFINE_HIGHER_ORDER_UNARY_FUNCTION(not,!)
DEFINE_HIGHER_ORDER_UNARY_FUNCTION(neg,-)
DEFINE_HIGHER_ORDER_BINARY_FUNCTION(and,&&)
DEFINE_HIGHER_ORDER_BINARY_FUNCTION(sum,+)
DEFINE_HIGHER_ORDER_BINARY_FUNCTION(subs,-)
DEFINE_HIGHER_ORDER_BINARY_FUNCTION(prod,*)
DEFINE_HIGHER_ORDER_BINARY_FUNCTION(div,/)
DEFINE_HIGHER_ORDER_BINARY_FUNCTION(pow,^)

namespace yame
{
namespace ytl
{

template<typename>
class constant_function;

template<typename Return, typename ... Types>
class constant_function<function<Return(Types...)>> : public function<Return(Types...)>
{
public:
    template<typename Constant>
    struct constant_functor_t
    {
        constant_functor_t(const Constant& i_constantValue)
        : m_constantValue(i_constantValue)
        {}
        Constant operator()(Types ... i_args) const
        {
            return m_constantValue;
        }
        Constant getConstant() const
        {
            return m_constantValue;
        }
    private:
        const Constant m_constantValue;
    };
    typedef constant_functor_t<Return> return_constant_functor_t;
    typedef constant_functor_t<int> integer_constant_functor_t;

    constant_function(const Return& i_constantValue)
    : function<Return(Types...)>(return_constant_functor_t(i_constantValue))
    {}
    constant_function(int i_constantValue)
    : function<Return(Types...)>(integer_constant_functor_t(i_constantValue))
    {}
};

template<typename>
class projection_function;

template<typename Return, typename ... Types>
requires (mpl::get_num_types<Types...>::value > 0)
class projection_function<function<Return(Types...)>> : public function<Return(Types...)>
{
public:
    struct projection_functor_t
    {
        typedef Return(* acquirer_arg_t)(Types...);
        static const size_t s_numTypes = mpl::get_num_types<Types...>::value;

        projection_functor_t(size_t i_component)
        : m_component(i_component)
        {
        }
        inline Return operator()(Types ... i_args) const
        {
            typedef typename mpl::create_range_rank<0,s_numTypes>::type range_seq;
            return (*(acquire_arg_acquirer(range_seq{},m_component)))(mpl::forward<Types>(i_args) ...);
        }
        size_t getComponent() const
        {
            return m_component;
        }
    private:
        template<int ... Indexs>
        static inline acquirer_arg_t acquire_arg_acquirer(const mpl::sequence<Indexs...>&, size_t i_component)
        {
            static const acquirer_arg_t s_acquire_arg[s_numTypes] = { &_forward_arg<Indexs> ...};

            return s_acquire_arg[i_component];
        }
        template<size_t Component>
        static inline Return _forward_arg(Types ... i_args)
        {
            return Return(mpl::nth_val_of<Component>(mpl::forward<Types>(i_args)...));
        }

        const size_t m_component;
    };
    template<size_t Component>
    projection_function(const mpl::numeric_type<Component>& i_numType)
    : function<Return(Types...)>(projection_functor_t(Component))
    {}
};

//shift free operator for currying the function
template<typename Return>
inline yame::ytl::curried_function<Return>& operator<<(yame::ytl::curried_function<Return>& i_lhs, const yame::ytl::function<Return()>& i_rhs);

template<typename Return, typename Type, typename ... Types>
inline yame::ytl::curried_function<Return,Type,Types...>& operator<<(yame::ytl::curried_function<Return,Type,Types...>& i_lhs, const yame::ytl::function<Return(Type,Types...)>& i_rhs);

}
}

#include "YTL/functional/detail/cFunctionOps.tpp"
