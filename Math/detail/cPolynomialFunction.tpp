
namespace yame
{
namespace math
{
namespace detail
{

template<field_type K, int N>
template<template<typename> class A, int ... Indexs>
polynomial_function<AKn<K,N>>::polynomial_function(const polynomial<K,A>& i_truncatedPolynomial, const mpl::sequence<Indexs...>&)
: scalar_function<K,Kn<K,N>>([i_truncatedPolynomial](typename mpl::transform_index_type<Indexs>::template to<K>::type ... i_args){ return eval(i_truncatedPolynomial, i_args...); })
{
}
template<field_type K, int N>
template<template<typename> class A>
polynomial_function<AKn<K,N>>::polynomial_function(const polynomial<K,A>& i_polynomial)
: polynomial_function(truncate(i_polynomial,N),0)
{
}

}
}
}
