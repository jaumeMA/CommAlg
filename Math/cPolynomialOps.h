#pragma once

#include "Math/cPolynomialAlgebra.h"
#include "Math/cMonomial.h"
#include "Math/cVectorSpace.h"
#include "Math/cMathOps.h"

namespace yame
{
namespace math
{
namespace detail
{

template<template<typename> class A, ring_type T>
inline polynomial<T,A> createPolyFromMonomial(const cMonomial<T>& i_monomial);

template<size_t Component, ring_type T, template<typename> class A>
cPolynomialValue<T,A> derivative(const cPolynomialValue<T,A>& i_subPoly, size_t currDepth);

template<size_t Component, ring_type T, template<typename> class A>
container::detail::cMultiMapImpl<cPolynomialValue<T,A>,signed short,container::cAVLtree,A,container::MultiBalancer<container::cAVLtree>::Balancer> derivative(const container::detail::cMultiMapImpl<cPolynomialValue<T,A>,signed short,container::cAVLtree,A,container::MultiBalancer<container::cAVLtree>::Balancer>& i_subPoly);

template<template<typename> class A, typename Im, typename Dom>
struct taylor
{
static const size_t s_dimension = Dom::dimension();

template<size_t,typename=void>
struct expansion;

template<size_t Component,typename Foo>
struct expansion
{
static void is(const scalar_function<Im,Dom>& i_function, const ytl::function<void(const scalar_function<Im,Dom>&, const container::cTupla<size_t,Dom::dimension()>&)>& o_sink, const container::cTupla<size_t,Dom::dimension()>& i_indexes, int currOrder);
};

template<typename Foo>
struct expansion<Dom::dimension()-1,Foo>
{
static void is(const scalar_function<Im,Dom>& i_function, const ytl::function<void(const scalar_function<Im,Dom>&, const container::cTupla<size_t,Dom::dimension()>&)>& o_sink, container::cTupla<size_t,Dom::dimension()> i_localIndexes, int currOrder);
};

static const size_t k_maxDerivativeOrder = 5;
};

template<ring_type Im, vector_space_type Dom, template<typename> class A = memory::cTypedSystemAllocator>
requires ( math::is_metric_space<Dom>::value )
polynomial<Im,A> _taylorSeries(const scalar_function<Im,Dom>& i_function, const Dom& i_point);

template<int ... Components, module_type Im, vector_space_type Dom, template<typename> class A = memory::cTypedSystemAllocator>
requires ( requires { Im::dimension(); }  && math::is_metric_space<Dom>::value )
container::cTupla<polynomial<typename Im::traits::module_traits::ring,A>,Im::dimension()> _taylorSeries(const mpl::sequence<Components...>&, const vector_function<Im,Dom>& i_function, const Dom& i_point);

}

template<ring_type T, template<typename> class A>
inline yame::container::cArray<yame::math::polynomial<T,A>> grobnerBase(const yame::container::cArray<yame::math::polynomial<T,A>>& i_ideal, const ytl::function<bool(yame::math::cMonomial<T>,yame::math::cMonomial<T>)>& i_compOp = &cMonomial<T>::lexMoreComparison);

template<size_t ... Components, ring_type T, template<typename> class A>
inline container::cTupla<polynomial<T,A>, mpl::get_num_ranks<Components...>::value> derivative(const polynomial<T,A>& i_poly);

template<module_type Im, vector_space_type Dom, callable_type Function, template<typename> class A = memory::cTypedSystemAllocator>
requires ( requires { Im::dimension(); }  && math::is_metric_space<Dom>::value )
inline container::cTupla<polynomial<typename Im::traits::module_traits::ring,A>,Im::dimension()> taylorSeries(const cFunctionSpace<Im,Dom,Function>& i_function, const Dom& i_point);

template<ring_type T, template<typename> class A>
inline polynomial<T,A> truncate(const polynomial<T,A>& other, size_t i_dim);

template<ring_type T>
inline yame::math::polynomial<T> operator+(const yame::math::cMonomial<T>& i_lhs, const yame::math::cMonomial<T>& i_rhs);
template<ring_type T, template<typename> class A>
inline yame::math::polynomial<T,A> operator+(const yame::math::polynomial<T,A>& i_lhs, const yame::math::cMonomial<T>& i_rhs);
template<ring_type T, template<typename> class A>
inline const yame::math::polynomial<T,A>& operator+=(yame::math::polynomial<T,A>& i_lhs, const yame::math::cMonomial<T>& i_rhs);
template<ring_type T, template<typename> class A>
inline yame::math::polynomial<T,A> operator+(const yame::math::cMonomial<T>& i_lhs, const yame::math::polynomial<T,A>& i_rhs);
template<ring_type T, template<typename> class A>
inline yame::math::polynomial<T,A> operator-(const yame::math::polynomial<T,A>& i_lhs, const yame::math::cMonomial<T>& i_rhs);
template<ring_type T, template<typename> class A>
inline const yame::math::polynomial<T,A>& operator-=(yame::math::polynomial<T,A>& i_lhs, const yame::math::cMonomial<T>& i_rhs);
template<ring_type T, template<typename> class A>
inline yame::math::polynomial<T,A> operator-(const yame::math::cMonomial<T>& i_lhs, const yame::math::polynomial<T,A>& i_rhs);
template<ring_type T, template<typename> class A>
inline yame::math::polynomial<T,A> operator*(const yame::math::polynomial<T,A>& i_lhs, const yame::math::cMonomial<T>& i_rhs);
template<ring_type T, template<typename> class A>
inline const yame::math::polynomial<T,A>& operator*=(yame::math::polynomial<T,A>& i_lhs, const yame::math::cMonomial<T>& i_rhs);
template<ring_type T, template<typename> class A>
inline yame::math::polynomial<T,A> operator*(const yame::math::cMonomial<T>& i_lhs, const yame::math::polynomial<T,A>& i_rhs);
template<ring_type T, template<typename> class A>
inline yame::container::cArray<yame::math::polynomial<T,A>> operator/(yame::math::polynomial<T,A> i_lhs, const yame::container::cArray<yame::math::polynomial<T,A>>& i_rhs);
template<ring_type T, template<typename> class A>
inline yame::math::polynomial<T,A> operator^(yame::math::polynomial<T,A> i_lhs, size_t i_rhs);

}

template<math::ring_type T, template<typename> class A>
container::string format(const math::polynomial<T,A>& i_value);

}

#include "Math/detail/cPolynomialOps.tpp"
