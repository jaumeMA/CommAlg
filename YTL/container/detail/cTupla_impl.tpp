
#include "System/cException.h"
#include "YTL/container/cAlgorithm.h"

namespace yame
{
namespace container
{
namespace detail
{

template<typename T, int rank, int ... ranks>
cSubTuple<T,rank,ranks...>::cSubTuple()
: m_ref(NULL)
{
}
template<typename T, int rank, int ... ranks>
cSubTuple<T,rank,ranks...>::cSubTuple(cSubTuple<T,rank,ranks...>&& other)
: m_ref(other.m_ref)
{
    other.m_ref = NULL;
}
template<typename T, int rank, int ... ranks>
cSubTuple<T,rank,ranks...>::cSubTuple(T* ref)
: m_ref(ref)
{
}
template<typename T, int rank, int ... ranks>
cSubTuple<T,ranks...> cSubTuple<T,rank,ranks...>::operator[](size_t index)
{
    ASSERT(index<rank,"Index out of bounds");

    return cSubTuple<T,ranks...>(m_ref + index);
}
template<typename T, int rank, int ... ranks>
cSubTuple<const T,ranks...> cSubTuple<T,rank,ranks...>::operator[](size_t index) const
{
    ASSERT(index<rank,"Index out of bounds");

    return cSubTuple<T,ranks...>(m_ref + index);
}
template<typename T, int rank, int ... ranks>
template<typename TT>
requires ( mpl::is_constructible<T,TT>::value )
cSubTuple<T,rank,ranks...>& cSubTuple<T,rank,ranks...>::operator=(const cSubTuple<TT,rank,ranks...>& other)
{
    static const int s_localTotalRank = PROD_RANKS(rank,ranks);
    typedef typename mpl::create_range_rank<0,s_localTotalRank>::type range_rank_t;

    ASSERT(m_ref && other.m_ref, "Dereferencing void tuple");

    cTuplaStorage<T,s_localTotalRank>::assign_tupla(range_rank_t{},m_ref,other.m_ref);

    return *this;
}
template<typename T, int rank, int ... ranks>
template<typename Arg>
cSubTuple<T,rank,ranks...>& cSubTuple<T,rank,ranks...>::operator=(Arg&& i_arg)
{
    static const int s_localTotalRank = PROD_RANKS(rank,ranks);
    typedef typename mpl::create_range_rank<0,s_localTotalRank>::type range_rank_t;

    ASSERT(m_ref, "Dereferencing void tuple");

    cTuplaStorage<T,s_localTotalRank>::assign_tupla(range_rank_t{},m_ref,i_arg.address());

    return *this;
}
template<typename T, int rank, int ... ranks>
cSubTuple<T,rank,ranks...>::operator bool() const
{
    return m_ref != NULL;
}
template<typename T, int rank, int ... ranks>
T* cSubTuple<T,rank,ranks...>::_get_reference()
{
    return m_ref;
}
template<typename T, int rank, int ... ranks>
const T* cSubTuple<T,rank,ranks...>::_get_reference() const
{
    return m_ref;
}

template<typename T, int rank>
cSubTuple<T,rank>::cSubTuple()
{
    m_ref = NULL;
}
template<typename T, int rank>
cSubTuple<T,rank>::cSubTuple(cSubTuple<T,rank>&& other)
: m_ref(other.m_ref)
{
    other.m_ref = NULL;
}
template<typename T, int rank>
cSubTuple<T,rank>::cSubTuple(T* ref)
{
    m_ref = ref;
}
template<typename T, int rank>
T& cSubTuple<T,rank>::operator[](size_t index)
{
    return *(m_ref + index);
}
template<typename T, int rank>
const T& cSubTuple<T,rank>::operator[](size_t index) const
{
    return *(m_ref + index);
}
template<typename T, int rank>
template<typename TT>
requires ( mpl::is_constructible<T,TT>::value )
cSubTuple<T,rank>& cSubTuple<T,rank>::operator=(const cSubTuple<TT,rank>& other)
{
    typedef typename mpl::create_range_rank<0,rank>::type range_rank_t;

    ASSERT(m_ref && other.m_ref, "Dereferencing void tuple");

    cTuplaStorage<T,rank>::assign_tupla(range_rank_t{},m_ref,other.m_ref);

    return *this;
}
template<typename T, int rank>
template<typename Arg>
cSubTuple<T,rank>& cSubTuple<T,rank>::operator=(Arg&& i_arg)
{
    typedef typename mpl::create_range_rank<0,rank>::type range_rank_t;

    ASSERT(m_ref, "Dereferencing void tuple");

    cTuplaStorage<T,rank>::assign_tupla(range_rank_t{},m_ref,i_arg.address());

    return *this;
}
template<typename T, int rank>
cSubTuple<T,rank>::operator bool() const
{
    return m_ref != NULL;
}
template<typename T, int rank>
T* cSubTuple<T,rank>::_get_reference()
{
    return m_ref;
}
template<typename T, int rank>
const T* cSubTuple<T,rank>::_get_reference() const
{
    return m_ref;
}

}
}
}
