#pragma once

#include "YTL/container/cParameterPack.h"

namespace yame
{
namespace mpl
{

template<template<typename...> class, typename, typename ...>
struct create_callable;

template<template<typename...> class Callable, typename Return, typename ... Types>
struct create_callable<Callable,Return,container::parameter_pack<Types...>>
{
    typedef Callable<Return(Types...)> type;
};

template<template<typename...> class Callable, typename Return, typename ... Types>
struct create_callable
{
    typedef Callable<Return(Types...)> type;
};

template<typename Functor, typename Return, typename ... Types>
struct lambda_evaluator
{
    lambda_evaluator(const Functor& i_functor)
    : m_functor(i_functor)
    {}

    Return operator()(Types ... i_args) const
    {
        return eval(m_functor,mpl::forward<Types>(i_args) ...);
    }

    const Functor& m_functor;
};
template<typename Functor, typename Return, typename ... Types>
struct lambda_caller
{
    lambda_caller(const Functor& i_functor)
    : m_functor(i_functor)
    {}

    Return operator()(Types ... i_args) const
    {
        return (m_functor)(mpl::forward<Types>(i_args) ...);
    }

    const Functor& m_functor;
};

}
}
