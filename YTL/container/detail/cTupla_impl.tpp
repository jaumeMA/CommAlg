
#include "System/cException.h"
#include "YTL/container/cAlgorithm.h"

namespace yame
{
namespace container
{
namespace detail
{
template<typename T, int rank, int ... ranks>
void cSubTuple<T,rank,ranks...>::reference_tuple(const cSubTuple<T,rank,ranks...>& other)
{
    for(size_t i=0;i<rank;i++)
    {
        m_subTuple[i].reference_tuple(other.m_subTuple[i]);
    }
}
template<typename T, int rank, int ... ranks>
void cSubTuple<T,rank,ranks...>::reference_tuple(void* ref)
{
    for(size_t i=0;i<rank;i++)
    {
        T* newRef = static_cast<T *>(ref)+i*mpl::Prod<ranks...>::value;

        m_subTuple[i].reference_tuple(static_cast<void *>(newRef));
    }
}
template<typename T, int rank, int ... ranks>
cSubTuple<T,rank,ranks...>::cSubTuple()
{
    for(size_t i=0;i<rank;i++)
    {
        m_subTuple[i] = cSubTuple<T,ranks...>();
    }
}
template<typename T, int rank, int ... ranks>
cSubTuple<T,rank,ranks...>::cSubTuple(const cTupla_impl<T,rank,ranks...>& other)
{
    for(size_t i=0;i<rank;i++)
    {
        m_subTuple[i] = cSubTuple<T,ranks...>(other.m_subTuple[i]);
    }
}
template<typename T, int rank, int ... ranks>
cSubTuple<T,rank,ranks...>::cSubTuple(void *ref)
{
    for(size_t i=0;i<rank;i++)
    {
        T* newRef = static_cast<T *>(ref)+i*mpl::Prod<ranks...>::value;

        m_subTuple[i].reference_tuple(static_cast<void *>(newRef));
    }
}
template<typename T, int rank, int ... ranks>
SUB_TUPLE(T,ranks)& cSubTuple<T,rank,ranks...>::operator[](size_t index)
{
    ASSERT(index<rank,"Index out of bounds");

    SUB_TUPLE(T,ranks) &res = m_subTuple[index];

    return res;
}
template<typename T, int rank, int ... ranks>
SUB_TUPLE(T,ranks) cSubTuple<T,rank,ranks...>::operator[](size_t index) const
{
    SUB_TUPLE(T,ranks) res;

    if(index < rank)
    {
        res = m_subTuple[index];
    }

    return res;
}
template<typename T, int rank, int ... ranks>
size_t cSubTuple<T,rank,ranks...>::getDim() const
{
    return 1 + mpl::get_num_ranks<ranks...>::value;
}
template<typename T, int rank, int ... ranks>
size_t cSubTuple<T,rank,ranks...>::getRank() const
{
    return rank;
}
template<typename T, int rank, int ... ranks>
cSubTuple<T,rank,ranks...>& cSubTuple<T,rank,ranks...>::operator=(const cSubTuple<T,rank,ranks...>& other)
{
    for(size_t i=0;i<rank;i++)
    {
        m_subTuple[i] = other.m_subTuple[i];
    }

    return *this;
}

template<typename T>
void cSubTuple<T>::reference_tuple(const cSubTuple<T>& other)
{
    m_ref = other.m_ref;
}
template<typename T>
void cSubTuple<T>::reference_tuple(void *ref)
{
    m_ref = static_cast<T *>(ref);
}
template<typename T>
cSubTuple<T>::cSubTuple()
{
    m_ref = NULL;
}
template<typename T>
cSubTuple<T>::cSubTuple(void* ref)
{
    m_ref = static_cast<T *>(ref);
}
template<typename T>
cSubTuple<T>::operator T&()
{
    return *m_ref;
}
template<typename T>
cSubTuple<T>::operator const T&() const
{
    return *m_ref;
}
template<typename T>
T& cSubTuple<T>::operator[](size_t index)
{
    ASSERT(index==0, "Index out of bounds");

    return *m_ref;
}
template<typename T>
const T& cSubTuple<T>::operator[](size_t index) const
{
    ASSERT(index==0, "Index out of bounds");

    return *m_ref;
}
template<typename T>
size_t cSubTuple<T>::getDim() const
{
    return 1;
}
template<typename T>
size_t cSubTuple<T>::getRank() const
{
    return 1;
}
template<typename T>
cSubTuple<T>& cSubTuple<T>::operator=(const cSubTuple<T>& other)
{
    if(m_ref && other.m_ref)
    {
        *m_ref = *(other.m_ref);
    }

    return *this;
}
template<typename T>
cSubTuple<T>& cSubTuple<T>::operator=(const T& other)
{
    *m_ref = other;

    return *this;
}

template<typename T, int rank, int ... ranks>
cSubTuple<cSubTuple<T,rank,ranks...> >::cSubTuple()
{
}
template<typename T, int rank, int ... ranks>
cSubTuple<cSubTuple<T,rank,ranks...> >::cSubTuple(void *ref)
: m_subTuple(ref)
{
}
template<typename T, int rank, int ... ranks>
cSubTuple<cSubTuple<T,rank,ranks...> >::operator cSubTuple<T,rank,ranks...>&()
{
    return m_subTuple;
}
template<typename T, int rank, int ... ranks>
cSubTuple<cSubTuple<T,rank,ranks...> >::operator const cSubTuple<T,rank,ranks...>&() const
{
    return m_subTuple;
}
template<typename T, int rank, int ... ranks>
SUB_TUPLE(T,ranks)& cSubTuple<cSubTuple<T,rank,ranks...> >::operator[](size_t index)
{
    ASSERT(index<rank, "Index out of bounds!");

    return m_subTuple[index];
}
template<typename T, int rank, int ... ranks>
SUB_TUPLE(T,ranks) cSubTuple<cSubTuple<T,rank,ranks...> >::operator[](size_t index) const
{
    ASSERT(index<rank, "Index out of bounds!");
    SUB_TUPLE(T,ranks) res = m_subTuple[index];

    return res;
}
template<typename T, int rank, int ... ranks>
size_t cSubTuple<cSubTuple<T,rank,ranks...> >::getDim() const
{
    return 1 + mpl::get_num_ranks<ranks...>::value;
}
template<typename T, int rank, int ... ranks>
size_t cSubTuple<cSubTuple<T,rank,ranks...> >::getRank() const
{
    return rank;
}
template<typename T, int rank, int ... ranks>
cSubTuple<cSubTuple<T,rank,ranks...> >& cSubTuple<cSubTuple<T,rank,ranks...> >::operator=(const cSubTuple<cSubTuple<T,rank,ranks...> >& other)
{
    m_subTuple = other.m_subTuple;

    return *this;
}
template<typename T, int rank, int ... ranks>
cSubTuple<cSubTuple<T,rank,ranks...> >& cSubTuple<cSubTuple<T,rank,ranks...> >::operator=(const cSubTuple<T,rank,ranks...>& other)
{
    m_subTuple = other;

    return *this;
}
template<typename T, int rank, int ... ranks>
void cSubTuple<cSubTuple<T,rank,ranks...> >::reference_tuple(const cSubTuple<cSubTuple<T,rank,ranks...> >& other)
{
    m_subTuple.reference_tuple(other.m_subTuple);

    return;
}
template<typename T, int rank, int ... ranks>
void cSubTuple<cSubTuple<T,rank,ranks...> >::reference_tuple(void* ref)
{
    m_subTuple.reference_tuple(ref);

    return;
}

template<typename T, int rank, int ... ranks>
cTupla_impl<T,rank,ranks...>::cTupla_impl()
: cTuplaStorage<T,PROD_RANKS(rank,ranks)>()
{
    reference_tuple();
}
template<typename T, int rank, int ... ranks>
cTupla_impl<T,rank,ranks...>::cTupla_impl(T *values)
: cTuplaStorage<T,PROD_RANKS(rank,ranks)>()
{
    reference_tuple();

    memcpy(&(this->m_tupla[0]),values,m_rank*sizeof(T));
}
template<typename T, int rank, int ... ranks>
template<typename ... Args>
cTupla_impl<T,rank,ranks...>::cTupla_impl(const T& arg, Args&& ... i_args)
{
    reference_tuple();

    yame::initialize(*this, {arg, mpl::forward<Args>(i_args) ...});
}
template<typename T, int rank, int ... ranks>
template<typename ... Args>
cTupla_impl<T,rank,ranks...>::cTupla_impl(T&& arg, Args&& ... i_args)
{
    reference_tuple();

    yame::initialize(*this, {mpl::move(arg), mpl::forward<Args>(i_args) ...});
}
template<typename T, int rank, int ... ranks>
cTupla_impl<T,rank,ranks...>::cTupla_impl(const cTupla_impl<T,rank,ranks...>& other)
: cTuplaStorage<T,PROD_RANKS(rank,ranks)>()
{
    reference_tuple();

    //and then initialize
    for(size_t i=0;i<rank;i++)
    {
        m_subTuple[i] = other.m_subTuple[i];
    }
}
template<typename T, int rank, int ... ranks>
cTupla_impl<T,rank,ranks...>::cTupla_impl(const cSubTuple<T,rank,ranks...>& other)
: cTuplaStorage<T,PROD_RANKS(rank,ranks)>()
{
    reference_tuple();

    //and then initialize
    for(size_t i=0;i<rank;i++)
    {
        m_subTuple[i] = other.m_subTuple[i];
    }
}
template<typename T, int rank, int ... ranks>
template<typename TT>
cTupla_impl<T,rank,ranks...>::cTupla_impl(const std::initializer_list<TT>& i_tupleList)
: cTuplaStorage<T,PROD_RANKS(rank,ranks)>()
{
    reference_tuple();

    yame::initialize(*this, i_tupleList);
}
template<typename T, int rank, int ... ranks>
cTupla_impl<T,rank,ranks...>::~cTupla_impl()
{
}
template<typename T, int rank, int ... ranks>
void cTupla_impl<T,rank,ranks...>::reference_tuple()
{
    primitive_type* ref = this->getTupla();
    int delta = mpl::Prod<ranks...>::value * mpl::total_rank<T>::value;

    for(size_t i=0;i<rank;i++)
    {
        m_subTuple[i].reference_tuple(cSubTuple<T,ranks...>(static_cast<void *>(ref + i*delta)));
    }

    return;
}
template<typename T, int rank, int ... ranks>
SUB_TUPLE(T,ranks)& cTupla_impl<T,rank,ranks...>::operator[](size_t index)
{
    SUB_TUPLE(T,ranks) &res = m_subTuple[index];

    ASSERT(index < rank,"Index out of bounds");

    return res;
}
template<typename T, int rank, int ... ranks>
const SUB_TUPLE(T,ranks)& cTupla_impl<T,rank,ranks...>::operator[](size_t index) const
{
    const SUB_TUPLE(T,ranks) &res = m_subTuple[index];

    ASSERT(index < rank,"Index out of bounds");

    return res;
}
template<typename T, int rank, int ... ranks>
cTupla_impl<T,rank,ranks...>& cTupla_impl<T,rank,ranks...>::operator=(const cTupla_impl<T,rank,ranks...>& other)
{
    for(size_t i=0;i<rank;i++)
    {
        m_subTuple[i] = other.m_subTuple[i];
    }

    return *this;
}
template<typename T, int rank, int ... ranks>
bool cTupla_impl<T,rank,ranks...>::operator==(const cTupla_impl<T,rank,ranks...>& other) const
{
    bool res = false;

    //tuples are used for number storage, so for the sake of speed we can directly compare memory contents of m_tuple

    res = memcmp(&(this->m_tupla[0]),&(other.m_tupla[0]),m_rank*sizeof(T))==0;

    return res;
}
template<typename T, int rank, int ... ranks>
bool cTupla_impl<T,rank,ranks...>::operator!=(const cTupla_impl<T,rank,ranks...>& other) const
{
    return !operator==(other);
}
template<typename T, int rank, int ... ranks>
size_t cTupla_impl<T,rank,ranks...>::getDim() const
{
    return m_dim;
}
template<typename T, int rank, int ... ranks>
size_t cTupla_impl<T,rank,ranks...>::getTotalRank() const
{
    return m_rank;
}
template<typename T, int rank, int ... ranks>
size_t cTupla_impl<T,rank,ranks...>::getRank() const
{
    return rank;
}
template<typename T, int rank, int ... ranks>
const typename cTupla_impl<T,rank,ranks...>::primitive_type* cTupla_impl<T,rank,ranks...>::getAsPtr() const
{
    return this->getTupla();
}
template<typename T, int rank, int ... ranks>
size_t cTupla_impl<T,rank,ranks...>::getSize() const
{
    return m_rank;
}
template<typename T, int rank, int ... ranks>
typename cTupla_impl<T,rank,ranks...>::node_pointer_type cTupla_impl<T,rank,ranks...>::getFirstElem() const
{
    return detail::sendNodeToIterator<node_pointer_type>(const_cast<primitive_type*>(this->getTupla()));
}
template<typename T, int rank, int ... ranks>
typename cTupla_impl<T,rank,ranks...>::node_pointer_type cTupla_impl<T,rank,ranks...>::getLastElem() const
{
    return detail::sendNodeToIterator<node_pointer_type>(const_cast<primitive_type*>(this->getTupla()) + m_rank - 1);
}
template<typename T, int rank, int ... ranks>
typename cTupla_impl<T,rank,ranks...>::node_pointer_type cTupla_impl<T,rank,ranks...>::getNextElem(node_pointer_type currNode) const
{
    if(this->isAddressInside(currNode,0,1))
    {
        return detail::sendNodeToIterator<node_pointer_type>(detail::receiveNodeFromIterator<primitive_type*>(currNode) + 1);
    }
    else
    {
        return iterable_type::m_pHead;
    }
}
template<typename T, int rank, int ... ranks>
typename cTupla_impl<T,rank,ranks...>::node_pointer_type cTupla_impl<T,rank,ranks...>::getPrevElem(node_pointer_type currNode) const
{
    if(this->isAddressInside(currNode,1,0))
    {
        return detail::sendNodeToIterator<node_pointer_type>(detail::receiveNodeFromIterator<value_type*>(currNode) - 1);
    }
    else
    {
        return iterable_type::m_pHead;
    }
}
template<typename T, int rank, int ... ranks>
typename cTupla_impl<T,rank,ranks...>::const_reference cTupla_impl<T,rank,ranks...>::getValue(node_pointer_type i_currNode) const
{
    return *detail::receiveNodeFromIterator<const value_type*>(i_currNode);
}
template<typename T, int rank, int ... ranks>
typename cTupla_impl<T,rank,ranks...>::reference cTupla_impl<T,rank,ranks...>::getValue(node_pointer_type i_currNode)
{
    return *detail::receiveNodeFromIterator<value_type*>(i_currNode);
}
template<typename T, int rank, int ... ranks>
typename cTupla_impl<T,rank,ranks...>::node_pointer_type cTupla_impl<T,rank,ranks...>::shiftNodeByIndex(node_pointer_type currNode, int index) const
{
    return (index >= 0 && index < m_rank) ? detail::sendNodeToIterator<node_pointer_type>(const_cast<primitive_type*>(this->getTupla()) + index ): iterable_type::m_pHead;
}
template<typename T, int rank, int ... ranks>
size_t cTupla_impl<T,rank,ranks...>::getIndexOfNode(node_pointer_type node) const
{
    if(this->isAddressInside(node,0,0))
    {
        return detail::receiveNodeFromIterator<value_type*>(node) - reinterpret_cast<value_type*>(const_cast<primitive_type*>(this->getTupla()));
    }
    else
    {
        return -1;
    }
}
template<typename T, int rank, int ... ranks>
template<int Index, int ... Indexs>
T& cTupla_impl<T,rank,ranks...>::get()
{
    static_assert(Index < rank, "Index out of bounds");

    return this->m_tupla[Index];
}
template<typename T, int rank, int ... ranks>
template<int Index, int ... Indexs>
const T& cTupla_impl<T,rank,ranks...>::get() const
{
    static_assert(Index < rank, "Index out of bounds");

    return this->m_tupla[Index];
}

template<typename T>
cTupla_impl<T,1>::cTupla_impl()
: cTuplaStorage<T,1>()
{
    reference_tuple();
}
template<typename T>
cTupla_impl<T,1>::cTupla_impl(const cTupla_impl<T,1>& other)
: cTuplaStorage<T,1>()
{
    reference_tuple();

    m_subTuple = other.m_subTuple;
}
template<typename T>
cTupla_impl<T,1>::cTupla_impl(T value)
: cTuplaStorage<T,1>()
{
    reference_tuple();

    m_subTuple = value;
}
template<typename T>
template<typename TT>
cTupla_impl<T,1>::cTupla_impl(const std::initializer_list<TT>& i_tupleList)
: cTuplaStorage<T,1>()
{
    ASSERT(i_tupleList.size() == 1, "Index out of bounds");

    reference_tuple();

    yame::initialize(*this, i_tupleList);
}
template<typename T>
T& cTupla_impl<T,1>::operator[](size_t index)
{
    ASSERT(index == 0,"Index out of bounds");

    return m_subTuple;
}
template<typename T>
const T& cTupla_impl<T,1>::operator[](size_t index) const
{
    ASSERT(index == 0,"Index out of bounds");

    return m_subTuple;
}
template<typename T>
cTupla_impl<T,1>::operator T&()
{
    return m_subTuple;
}
template<typename T>
cTupla_impl<T,1>::operator const T&() const
{
    return m_subTuple;
}
template<typename T>
cTupla_impl<T,1>& cTupla_impl<T,1>::operator=(const cTupla_impl<T,1>& other)
{
    m_subTuple = other.m_subTuple;

    return *this;
}
template<typename T>
bool cTupla_impl<T,1>::operator==(const cTupla_impl<T,1>& other) const
{
    return m_subTuple==other.m_subTuple;
}
template<typename T>
bool cTupla_impl<T,1>::operator!=(const cTupla_impl<T,1>& other) const
{
    return m_subTuple!=other.m_subTuple;
}
template<typename T>
size_t cTupla_impl<T,1>::getDim() const
{
    return 0;
}
template<typename T>
size_t cTupla_impl<T,1>::getRank() const
{
    return 1;
}
template<typename T>
size_t cTupla_impl<T,1>::getTotalRank() const
{
    return 1;
}
template<typename T>
const typename cTupla_impl<T,1>::primitive_type* cTupla_impl<T,1>::getAsPtr() const
{
    return this->getTupla();
}
template<typename T>
template<int Index>
T& cTupla_impl<T,1>::get()
{
    static_assert(Index==0,"Index out of bounds");

    return m_subTuple;
}
template<typename T>
template<int Index>
const T& cTupla_impl<T,1>::get() const
{
    static_assert(Index==0,"Index out of bounds");

    return m_subTuple;
}
template<typename T>
void cTupla_impl<T,1>::reference_tuple()
{
    m_subTuple.reference_tuple(cSubTuple<T>(static_cast<void *>(this->getTupla())));

    return;
}
template<typename T>
size_t cTupla_impl<T,1>::getSize() const
{
    return 1;
}
template<typename T>
typename cTupla_impl<T,1>::node_pointer_type cTupla_impl<T,1>::getFirstElem() const
{
    return detail::sendNodeToIterator<node_pointer_type>(const_cast<primitive_type*>(this->getTupla()));
}
template<typename T>
typename cTupla_impl<T,1>::node_pointer_type cTupla_impl<T,1>::getLastElem() const
{
    return detail::sendNodeToIterator<node_pointer_type>(const_cast<primitive_type*>(this->getTupla()) + m_rank - 1);
}
template<typename T>
typename cTupla_impl<T,1>::node_pointer_type cTupla_impl<T,1>::getNextElem(node_pointer_type currNode) const
{
    return iterable_type::m_pHead;
}
template<typename T>
typename cTupla_impl<T,1>::node_pointer_type cTupla_impl<T,1>::getPrevElem(node_pointer_type currNode) const
{
    return iterable_type::m_pHead;
}
template<typename T>
typename cTupla_impl<T,1>::const_reference cTupla_impl<T,1>::getValue(node_pointer_type i_currNode) const
{
    return *detail::receiveNodeFromIterator<const value_type*>(i_currNode);
}
template<typename T>
typename cTupla_impl<T,1>::reference cTupla_impl<T,1>::getValue(node_pointer_type i_currNode)
{
    return *detail::receiveNodeFromIterator<value_type*>(i_currNode);
}
template<typename T>
typename cTupla_impl<T,1>::node_pointer_type cTupla_impl<T,1>::shiftNodeByIndex(node_pointer_type currNode, int index) const
{
    return (index == 0) ? detail::sendNodeToIterator<node_pointer_type>(const_cast<primitive_type*>(this->getTupla())) : iterable_type::m_pHead;
}
template<typename T>
size_t cTupla_impl<T,1>::getIndexOfNode(node_pointer_type node) const
{
    if(detail::receiveNodeFromIterator<value_type*>(node) == reinterpret_cast<value_type*>(const_cast<primitive_type*>(this->getTupla())))
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

}
}
}
