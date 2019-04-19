
namespace yame
{
namespace container
{
namespace detail
{

template<typename Traits>
typename cIterablePackIterableImpl<Traits>::private_node_pointer_type cIterablePackIterableImpl<Traits>::createNode(const private_node_type& i_pack) const
{
    return new (k_pairAllocator.allocate(1, sizeof(private_node_type))) private_node_type(i_pack);
}
template<typename Traits>
void cIterablePackIterableImpl<Traits>::deleteNode(private_node_pointer_type i_node) const
{
    k_pairAllocator.deallocate(i_node);
}
template<typename Traits>
template<int Index>
requires ( Index < Traits::numIterables )
auto& cIterablePackIterableImpl<Traits>::get_nth_iterable()
{
    return m_iterables.template getValue<Index>();
}
template<typename Traits>
template<int Index>
requires ( Index < Traits::numIterables )
const auto& cIterablePackIterableImpl<Traits>::get_nth_iterable() const
{
    return m_iterables.template getValue<Index>();
}
template<typename Traits>
template<int ... Indexs>
bool cIterablePackIterableImpl<Traits>::is_any_end(private_node_pointer_type i_node) const
{
    static const node_pointer_type s_head = this->getHead();

    return (is_head(i_node->template getValue<Indexs>()) || ...);
}
template<typename Traits>
template<int ... Indexs>
typename cIterablePackIterableImpl<Traits>::node_pointer_type cIterablePackIterableImpl<Traits>::_getFirstElem(const mpl::sequence<Indexs...>&) const
{
    return reinterpret_cast<node_pointer_type>(createNode(make_parameter_pack(m_iterables.template getValue<Indexs>()->getFirstElem() ...)));
}
template<typename Traits>
template<int ... Indexs>
typename cIterablePackIterableImpl<Traits>::node_pointer_type cIterablePackIterableImpl<Traits>::_getNextElem(const mpl::sequence<Indexs...>&, node_pointer_type i_currNode) const
{
    private_node_pointer_type currNodePointer = reinterpret_cast<private_node_pointer_type>(i_currNode);

    currNodePointer->template setValues<Indexs...>(m_iterables.template getValue<Indexs>()->getNextElem(currNodePointer->template getValue<Indexs>()) ...);

    return (is_any_end<Indexs...>(currNodePointer)) ? this->getHead() : reinterpret_cast<node_pointer_type>(currNodePointer);
}
template<typename Traits>
cIterablePackIterableImpl<Traits>::cIterablePackIterableImpl(const iterable_pack& i_iterables)
: m_iterables(i_iterables)
{
}
template<typename Traits>
template<typename ... IIterables>
cIterablePackIterableImpl<Traits>::cIterablePackIterableImpl(IIterables&& ... i_iterables)
: m_iterables(ytl::lend(static_cast<typename mpl::drop_reference<IIterables>::type::iterable_private_interface&>(i_iterables)) ...)
{
}
template<typename Traits>
typename cIterablePackIterableImpl<Traits>::node_pointer_type cIterablePackIterableImpl<Traits>::getFirstElem() const
{
    typedef typename mpl::create_range_rank<0,Traits::numIterables>::type rangeSeq;

    return sendNodeToIterator<node_pointer_type>(_getFirstElem(rangeSeq{}));
}
template<typename Traits>
typename cIterablePackIterableImpl<Traits>::node_pointer_type cIterablePackIterableImpl<Traits>::getNextElem(node_pointer_type currNode) const
{
    typedef typename mpl::create_range_rank<0,Traits::numIterables>::type rangeSeq;

    return sendNodeToIterator<node_pointer_type>(_getNextElem(rangeSeq{},currNode));
}
template<typename Traits>
typename cIterablePackIterableImpl<Traits>::node_pointer_type cIterablePackIterableImpl<Traits>::acquireNode(node_pointer_type i_node) const
{
    if(i_node != iterator_type::m_pHead)
    {
        private_node_pointer_type currNode = receiveNodeFromIterator<private_node_pointer_type>(i_node);

        return createNode(*currNode);
    }
    else
    {
        return i_node;
    }
}
template<typename Traits>
void cIterablePackIterableImpl<Traits>::releaseNode(node_pointer_type i_node) const
{
    if(i_node != iterator_type::m_pHead)
    {
        private_node_pointer_type currNode = receiveNodeFromIterator<private_node_pointer_type>(i_node);

        deleteNode(currNode);
    }
}
template<typename Traits>
typename cIterablePackIterableImpl<Traits>::const_reference cIterablePackIterableImpl<Traits>::getValue(node_pointer_type currNode) const
{
    typedef typename mpl::create_range_rank<0,Traits::numIterables>::type rangeSeq;

    return _getValue(rangeSeq{},currNode);
}
template<typename Traits>
typename cIterablePackIterableImpl<Traits>::reference cIterablePackIterableImpl<Traits>::getValue(node_pointer_type currNode)
{
    typedef typename mpl::create_range_rank<0,Traits::numIterables>::type rangeSeq;

    return _getValue(rangeSeq{},currNode);
}
template<typename Traits>
template<int ... Indexs>
typename cIterablePackIterableImpl<Traits>::const_reference cIterablePackIterableImpl<Traits>::_getValue(const mpl::sequence<Indexs...>&, node_pointer_type i_currNode) const
{
    private_node_pointer_type currPack = receiveNodeFromIterator<private_node_pointer_type>(i_currNode);

    return make_parameter_pack(m_iterables.template getValue<Indexs>()->getValue(currPack->template getValue<Indexs>()) ...);
}
template<typename Traits>
template<int ... Indexs>
typename cIterablePackIterableImpl<Traits>::reference cIterablePackIterableImpl<Traits>::_getValue(const mpl::sequence<Indexs...>&, node_pointer_type i_currNode)
{
    private_node_pointer_type currPack = receiveNodeFromIterator<private_node_pointer_type>(i_currNode);

    return make_parameter_pack(m_iterables.template getValue<Indexs>()->getValue(currPack->template getValue<Indexs>()) ...);
}

template<typename Traits>
typename cBidirectionalIterablePackIterableImpl<Traits>::node_pointer_type cBidirectionalIterablePackIterableImpl<Traits>::getLastElem() const
{
    typedef typename mpl::create_range_rank<0,Traits::numIterables>::type rangeSeq;

    return sendNodeToIterator<node_pointer_type>(_getLastElem(rangeSeq{}));
}
template<typename Traits>
typename cBidirectionalIterablePackIterableImpl<Traits>::node_pointer_type cBidirectionalIterablePackIterableImpl<Traits>::getPrevElem(node_pointer_type currNode) const
{
    typedef typename mpl::create_range_rank<0,Traits::numIterables>::type rangeSeq;

    return sendNodeToIterator<node_pointer_type>(_getPrevElem(rangeSeq{},currNode));
}
template<typename Traits>
template<int ... Indexs>
typename cBidirectionalIterablePackIterableImpl<Traits>::node_pointer_type cBidirectionalIterablePackIterableImpl<Traits>::_getLastElem(const mpl::sequence<Indexs...>&) const
{
    return reinterpret_cast<node_pointer_type>(this->createNode(make_parameter_pack(this->template get_nth_iterable<Indexs>()->getLastElem() ...)));
}
template<typename Traits>
template<int ... Indexs>
typename cBidirectionalIterablePackIterableImpl<Traits>::node_pointer_type cBidirectionalIterablePackIterableImpl<Traits>::_getPrevElem(const mpl::sequence<Indexs...>&, node_pointer_type i_currNode) const
{
    private_node_pointer_type currNodePointer = reinterpret_cast<private_node_pointer_type>(i_currNode);

    currNodePointer->template setValues<Indexs...>(this->template get_nth_iterable<Indexs>()->getPrevElem(currNodePointer->template getValue<Indexs>()) ...);
    const bool reach_end = this->template is_any_end<Indexs...>(currNodePointer);

    return (reach_end) ? this->getHead() : reinterpret_cast<node_pointer_type>(currNodePointer);
}

template<typename Traits>
size_t cRandomAccessIterablePackIterableImpl<Traits>::getIndexOfNode(node_pointer_type node) const
{
    private_node_pointer_type currNodePointer = reinterpret_cast<private_node_pointer_type>(node);

    //by construction all of them have the same offset (we dont allow desynchronized packs)
    return this->template get_nth_iterable<0>()->getIndexOfNode(currNodePointer->template getValue<0>());
}
template<typename Traits>
typename cRandomAccessIterablePackIterableImpl<Traits>::node_pointer_type cRandomAccessIterablePackIterableImpl<Traits>::shiftNodeByIndex(node_pointer_type node, int val) const
{
    typedef typename mpl::create_range_rank<0,Traits::numIterables>::type rangeSeq;

    return sendNodeToIterator<node_pointer_type>(_shiftNodeByIndex(rangeSeq{},node,val));
}
template<typename Traits>
template<int ... Indexs>
typename cRandomAccessIterablePackIterableImpl<Traits>::node_pointer_type cRandomAccessIterablePackIterableImpl<Traits>::_shiftNodeByIndex(const mpl::sequence<Indexs...>&, node_pointer_type i_currNode, int val) const
{
    private_node_pointer_type currNodePointer = reinterpret_cast<private_node_pointer_type>(i_currNode);

    currNodePointer->template setValues<Indexs...>(this->template get_nth_iterable<Indexs>()->shiftNodeByIndex(currNodePointer->template getValue<Indexs>(),val) ...);

    return reinterpret_cast<node_pointer_type>(currNodePointer);
}

}
}
}
