
#include "Math/cPolynomialIterable.h"
#include "Math/cPolynomialOps.h"
#include "YTL/container/cAlgorithm.h"

namespace yame
{
namespace math
{

template<ring_type T, template<typename> class A>
polynomial<T,A>::polynomial()
: cSet<PolySetTraits>(static_cast<const cSet<PolySetTraits>&>(group::neutral_element()))
{
}
template<ring_type T, template<typename> class A>
polynomial<T,A>::polynomial(const cMonomial<T>& i_monomial)
: polynomial(detail::createPolyFromMonomial<A>(i_monomial))
{
}
template<ring_type T, template<typename> class A>
polynomial<T,A>::polynomial(const polynomial<T,A>& other)
: cSet<PolySetTraits>(other.getValue())
{
}
template<ring_type T, template<typename> class A>
polynomial<T,A>::polynomial(polynomial<T,A>&& other)
: cSet<PolySetTraits>(other.extractValue())
{
}
template<ring_type T, template<typename> class A>
polynomial<T,A>& polynomial<T,A>::operator=(const polynomial<T,A>& other)
{
    this->setValue(other.getValue());

    return *this;
}
template<ring_type T, template<typename> class A>
polynomial<T,A>& polynomial<T,A>::operator=(polynomial<T,A>&& other)
{
    this->setValue(mpl::move(other.getValue()));

    return *this;
}

template<ring_type T, template<typename> class A, typename ... Args>
requires ( mpl::are_same_type<T,Args...>::value )
T eval(const polynomial<T,A>& i_poly, Args&& ... i_args)
{
    typedef typename mpl::create_range_rank<0,mpl::get_num_types<Args...>::value>::type range_seq_t;

    return _eval(i_poly,range_seq_t{},mpl::forward<Args>(i_args) ...);
}
template<ring_type T, template<typename> class A, int ... Indexs, typename ... Args>
requires ( mpl::are_same_type<T,Args...>::value && mpl::get_num_ranks<Indexs...>::value == mpl::get_num_types<Args...>::value )
T _eval(const polynomial<T,A>& i_poly, const mpl::sequence<Indexs...>&, Args&& ... i_args)
{
    T res = T::group_type::neutral_element();

    cPolynomialIterable<T,A> polyIterable(i_poly);
    typename cPolynomialIterable<T,A>::const_iterator_type itPoly = polyIterable.begin();
    for(;itPoly!=polyIterable.end();++itPoly)
    {
        const cMonomial<T> currMonomial = *itPoly;
        const container::cTupla<T,mpl::get_num_ranks<Indexs...>::value> poweredArgs({ i_args ^ currMonomial.getPowerOfIndex(Indexs) ... });

        res += prod(poweredArgs);
    }

    return res;
}

}
}

