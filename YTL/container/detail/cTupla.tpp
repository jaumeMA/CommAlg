
#include "YTL/container/detail/cTuplaTemplateHelper.h"

namespace yame
{
namespace container
{

template<typename T, int rank, int ... ranks>
cTupla<T,rank,ranks...>::cTupla()
: detail::cTuplaStorage<T,PROD_RANKS(rank,ranks)>()
{
}
template<typename T, int rank, int ... ranks>
cTupla<T,rank,ranks...>::cTupla(const cTupla<T,rank,ranks...>& other)
: detail::cTuplaStorage<T,PROD_RANKS(rank,ranks)>(other)
{
}
template<typename T, int rank, int ... ranks>
template<typename TT>
requires ( mpl::is_constructible<T,TT>::value )
cTupla<T,rank,ranks...>::cTupla(const detail::cSubTuple<TT,rank,ranks...>& other)
: detail::cTuplaStorage<T,PROD_RANKS(rank,ranks)>(other._get_reference())
{
}
template<typename T, int rank, int ... ranks>
template<typename TT>
requires ( mpl::is_constructible<T,TT>::value )
cTupla<T,rank,ranks...>::cTupla(const std::initializer_list<TT>& i_tupleList)
: detail::cTuplaStorage<T,PROD_RANKS(rank,ranks)>(i_tupleList)
{
}
template<typename T, int rank, int ... ranks>
template<typename TT>
requires (mpl::is_constructible<T,TT>::value )
cTupla<T,rank,ranks...>::cTupla(const cTupla<TT,rank,ranks...>& other)
: detail::cTuplaStorage<T,PROD_RANKS(rank,ranks)>(other)
{
}
template<typename T, int rank, int ... ranks>
cTupla<T,rank,ranks...>::~cTupla()
{
}
template<typename T, int rank, int ... ranks>
detail::cSubTuple<T,ranks...> cTupla<T,rank,ranks...>::operator[](size_t index)
{
    static const size_t s_scale = mpl::Prod<ranks...>::value;

    ASSERT(index < rank,"Index out of bounds");

    return detail::cSubTuple<T,ranks...>(this->address(index * s_scale));
}
template<typename T, int rank, int ... ranks>
detail::cSubTuple<const T,ranks...> cTupla<T,rank,ranks...>::operator[](size_t index) const
{
    static const size_t s_scale = mpl::Prod<ranks...>::value;

    ASSERT(index < rank,"Index out of bounds");

    return detail::cSubTuple<const T,ranks...>(this->address(index * s_scale));
}
template<typename T, int rank, int ... ranks>
cTupla<T,rank,ranks...>& cTupla<T,rank,ranks...>::operator=(const cTupla<T,rank,ranks...>& other)
{
    detail::cTuplaStorage<T,m_rank>::operator=(other);

    return *this;
}
template<typename T, int rank, int ... ranks>
template<typename TT>
requires (mpl::is_constructible<T,TT>::value )
cTupla<T,rank,ranks...>& cTupla<T,rank,ranks...>::operator=(const cTupla<TT,rank,ranks...>& other)
{
    detail::cTuplaStorage<T,m_rank>::operator=(other);

    return *this;
}
template<typename T, int rank, int ... ranks>
cTupla<T,rank,ranks...>::operator detail::cSubTuple<T,rank,ranks...>()
{
    return detail::cSubTuple<T,rank,ranks...>(this->address());
}
template<typename T, int rank, int ... ranks>
cTupla<T,rank,ranks...>::operator detail::cSubTuple<const T,rank,ranks...>() const
{
    return detail::cSubTuple<const T,rank,ranks...>(this->address());
}
template<typename T, int rank, int ... ranks>
size_t cTupla<T,rank,ranks...>::getSize() const
{
    return m_rank;
}
template<typename T, int rank, int ... ranks>
typename cTupla<T,rank,ranks...>::node_pointer_type cTupla<T,rank,ranks...>::getFirstElem() const
{
    return detail::sendNodeToIterator<node_pointer_type>(const_cast<primitive_type*>(this->address()));
}
template<typename T, int rank, int ... ranks>
typename cTupla<T,rank,ranks...>::node_pointer_type cTupla<T,rank,ranks...>::getLastElem() const
{
    return detail::sendNodeToIterator<node_pointer_type>(const_cast<primitive_type*>(this->address(m_rank - 1)));
}
template<typename T, int rank, int ... ranks>
typename cTupla<T,rank,ranks...>::node_pointer_type cTupla<T,rank,ranks...>::getNextElem(node_pointer_type currNode) const
{
    primitive_type* currIterator = detail::receiveNodeFromIterator<primitive_type*>(currNode);

    if(this->isAddressInside(currIterator,0,1))
    {
        return detail::sendNodeToIterator<node_pointer_type>(currIterator + 1);
    }
    else
    {
        return iterable_type::m_pHead;
    }
}
template<typename T, int rank, int ... ranks>
typename cTupla<T,rank,ranks...>::node_pointer_type cTupla<T,rank,ranks...>::getPrevElem(node_pointer_type currNode) const
{
    primitive_type* currIterator = detail::receiveNodeFromIterator<primitive_type*>(currNode);

    if(this->isAddressInside(currIterator,0,1))
    {
        return detail::sendNodeToIterator<node_pointer_type>(currIterator - 1);
    }
    else
    {
        return iterable_type::m_pHead;
    }
}
template<typename T, int rank, int ... ranks>
typename cTupla<T,rank,ranks...>::const_reference cTupla<T,rank,ranks...>::getValue(node_pointer_type i_currNode) const
{
    cTupla<size_t,mpl::get_num_ranks<ranks...>::value + 1> indexs;
    primitive_type* currIterator = detail::receiveNodeFromIterator<primitive_type*>(i_currNode);

    //construct a tuple from this number

    return iterator_pair(indexs,*currIterator);
}
template<typename T, int rank, int ... ranks>
typename cTupla<T,rank,ranks...>::reference cTupla<T,rank,ranks...>::getValue(node_pointer_type i_currNode)
{
    primitive_type* currIterator = detail::receiveNodeFromIterator<primitive_type*>(i_currNode);

    return iterator_pair(mpl::compute_tupla_indexs<T,rank,ranks...>::of(this->address(),currIterator),*currIterator);
}
template<typename T, int rank, int ... ranks>
typename cTupla<T,rank,ranks...>::node_pointer_type cTupla<T,rank,ranks...>::shiftNodeByIndex(node_pointer_type currNode, int index) const
{
    return (index >= 0 && index < m_rank) ? detail::sendNodeToIterator<node_pointer_type>(const_cast<primitive_type*>(this->address(index)) ): iterable_type::m_pHead;
}
template<typename T, int rank, int ... ranks>
size_t cTupla<T,rank,ranks...>::getIndexOfNode(node_pointer_type node) const
{
    return detail::receiveNodeFromIterator<primitive_type*>(node) - this->address();
}

template<typename T, int rank>
cTupla<T,rank>::cTupla()
: detail::cTuplaStorage<T,rank>()
{
}
template<typename T, int rank>
cTupla<T,rank>::cTupla(const cTupla<T,rank>& other)
: detail::cTuplaStorage<T,rank>(other)
{
}
template<typename T, int rank>
template<typename TT>
requires (mpl::is_constructible<T,TT>::value )
cTupla<T,rank>::cTupla(const detail::cSubTuple<TT,rank>& other)
: detail::cTuplaStorage<T,rank>(other._get_reference())
{
}
template<typename T, int rank>
template<typename TT>
requires ( mpl::is_constructible<T,TT>::value )
cTupla<T,rank>::cTupla(const std::initializer_list<TT>& i_tupleList)
: detail::cTuplaStorage<T,rank>(i_tupleList)
{
}
template<typename T, int rank>
template<typename TT>
requires (mpl::is_constructible<T,TT>::value )
cTupla<T,rank>::cTupla(const cTupla<TT,rank>& other)
: detail::cTuplaStorage<T,rank>(other)
{
}
template<typename T, int rank>
cTupla<T,rank>::~cTupla()
{
}
template<typename T, int rank>
cTupla<T,rank>& cTupla<T,rank>::operator=(const cTupla<T,rank>& other)
{
    detail::cTuplaStorage<T,m_rank>::operator=(other);

    return *this;
}
template<typename T, int rank>
template<typename TT>
requires (mpl::is_constructible<T,TT>::value )
cTupla<T,rank>& cTupla<T,rank>::operator=(const cTupla<TT,rank>& other)
{
    detail::cTuplaStorage<T,m_rank>::operator=(other);

    return *this;
}
template<typename T, int rank>
cTupla<T,rank>::operator detail::cSubTuple<T,rank>()
{
    return detail::cSubTuple<T,rank>(this->address());
}
template<typename T, int rank>
cTupla<T,rank>::operator detail::cSubTuple<const T,rank>() const
{
    return detail::cSubTuple<const T,rank>(this->address());
}
template<typename T, int rank>
size_t cTupla<T,rank>::getSize() const
{
    return m_rank;
}
template<typename T, int rank>
typename cTupla<T,rank>::node_pointer_type cTupla<T,rank>::getFirstElem() const
{
    return detail::sendNodeToIterator<node_pointer_type>(const_cast<primitive_type*>(this->address(0)));
}
template<typename T, int rank>
typename cTupla<T,rank>::node_pointer_type cTupla<T,rank>::getLastElem() const
{
    return detail::sendNodeToIterator<node_pointer_type>(const_cast<primitive_type*>(this->address(m_rank - 1)));
}
template<typename T, int rank>
typename cTupla<T,rank>::node_pointer_type cTupla<T,rank>::getNextElem(node_pointer_type currNode) const
{
    primitive_type* currIterator = detail::receiveNodeFromIterator<primitive_type*>(currNode);

    if(this->isAddressInside(currIterator,0,1))
    {
        return detail::sendNodeToIterator<node_pointer_type>(currIterator + 1);
    }
    else
    {
        return iterable_type::m_pHead;
    }
}
template<typename T, int rank>
typename cTupla<T,rank>::node_pointer_type cTupla<T,rank>::getPrevElem(node_pointer_type currNode) const
{
    primitive_type* currIterator = detail::receiveNodeFromIterator<primitive_type*>(currNode);

    if(this->isAddressInside(currIterator,0,1))
    {
        return detail::sendNodeToIterator<node_pointer_type>(currIterator - 1);
    }
    else
    {
        return iterable_type::m_pHead;
    }
}
template<typename T, int rank>
typename cTupla<T,rank>::const_reference cTupla<T,rank>::getValue(node_pointer_type i_currNode) const
{
    primitive_type* currIterator = detail::receiveNodeFromIterator<primitive_type*>(i_currNode);

    return iterator_pair(mpl::compute_tupla_indexs<T,rank>::of(this->address(),currIterator),*currIterator);
}
template<typename T, int rank>
typename cTupla<T,rank>::reference cTupla<T,rank>::getValue(node_pointer_type i_currNode)
{
    primitive_type* currIterator = detail::receiveNodeFromIterator<primitive_type*>(i_currNode);

    return iterator_pair(mpl::compute_tupla_indexs<T,rank>::of(this->address(),currIterator),*currIterator);
}
template<typename T, int rank>
typename cTupla<T,rank>::node_pointer_type cTupla<T,rank>::shiftNodeByIndex(node_pointer_type currNode, int index) const
{
    return (index >= 0 && index < m_rank) ? detail::sendNodeToIterator<node_pointer_type>(const_cast<primitive_type*>(this->address(index)) ): iterable_type::m_pHead;
}
template<typename T, int rank>
size_t cTupla<T,rank>::getIndexOfNode(node_pointer_type node) const
{
    return detail::receiveNodeFromIterator<primitive_type*>(node) - this->address();
}
template<typename T, int rank>
template<typename TT>
requires ( rank==1 && mpl::is_same_type<T,TT>::value )
cTupla<T,rank>::operator TT&()
{
    detail::cTuplaStorage<T,m_rank>::template get<0>();
}
template<typename T, int rank>
template<typename TT>
requires ( rank==1 && mpl::is_same_type<T,TT>::value )
cTupla<T,rank>::operator const TT&() const
{
    detail::cTuplaStorage<T,m_rank>::template get<0>();
}

template<typename T, int ... ranks, typename Arg, typename ... Args>
requires( mpl::are_same_type<Arg,Args...>::value )
cTupla<T,ranks...> make_tupla(Arg&& i_arg, Args&& ... i_args)
{
    return cTupla<Arg,mpl::get_num_types<Args...>::value + 1>(mpl::forward<Arg>(i_arg), mpl::forward<Args>(i_args) ...);
}

}
}

