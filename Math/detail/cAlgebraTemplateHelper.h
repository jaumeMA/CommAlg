#pragma once

#include <utility>
#include "Math/detail/cMathTags.h"

#define NESTED_STRUCTURE_ACQUIRER(_STRUCTURE,_STRUCTURE_CONCEPT) \
template<typename FinalObject> \
struct underlying_structure_type<_STRUCTURE,FinalObject> \
{ \
 \
private: \
template<typename Traits, typename FFinalObject> \
requires _STRUCTURE_CONCEPT<Traits> && requires { mpl::is_same_type<FFinalObject,FinalObject>::value; } \
static const _STRUCTURE<Traits,FFinalObject>& _resolver(const _STRUCTURE<Traits,FFinalObject>&); \
 \
public: \
    typedef typename ::yame::mpl::drop_reference<typename ::yame::mpl::drop_constness<decltype(_resolver(std::declval<FinalObject>()))>::type>::type type; \
};

#define IS_STRUCTURE(_STRUCTURE_NAME) \
template<typename T> \
struct is_##_STRUCTURE_NAME \
{ \
    typedef typename mpl::drop_constness<typename mpl::drop_reference<T>::type>::type raw_type; \
    \
    static constexpr bool _is(const detail::_STRUCTURE_NAME##_tag*) \
    { \
        return true; \
    } \
    static constexpr bool _is(...) \
    { \
        return false; \
    } \
 \
 \
    static const bool value = _is(mpl::instantiatePointer<const raw_type>::value); \
};

namespace yame
{
namespace math
{
namespace detail
{

template<template<typename,typename> class, typename FinalObject>
struct underlying_structure_type
{
    static_assert(sizeof(FinalObject)==0,"Missing sepcialization for this template");
};

}

IS_STRUCTURE(set)
IS_STRUCTURE(group)
IS_STRUCTURE(module)
IS_STRUCTURE(ring)
IS_STRUCTURE(division_ring)
IS_STRUCTURE(field)
IS_STRUCTURE(algebra)
IS_STRUCTURE(vector_space)
IS_STRUCTURE(metric_space)

}
}
