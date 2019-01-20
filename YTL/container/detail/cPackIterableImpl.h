#pragma once

#include "YTL/container/cIterableBase.h"
#include "YTL/container/cParameterPack.h"
#include "YTL/container/cContainerView.h"
#include "System/memory/cMemoryPool.h"

namespace yame
{
namespace container
{
namespace detail
{

extern const memory::cMemoryPool& k_pairAllocator;

template<typename Traits>
class cPackIterableImpl : public Traits::iterable_type
{
    typedef typename Traits::iterable_pack iterable_pack;
    typedef typename Traits::private_node_type private_node_type;
    typedef typename Traits::private_node_pointer_type private_node_pointer_type;
    typedef typename Traits::node_pointer_type node_pointer_type;

public:
    typedef typename Traits::iterator_type iterator_type;
    typedef typename Traits::const_iterator_type const_iterator_type;
	typedef typename Traits::value_type value_type;
	typedef typename Traits::pointer_type pointer_type;
	typedef typename Traits::reference reference;
	typedef typename Traits::const_reference const_reference;

    cPackIterableImpl(const iterable_pack& i_iterables);
    template<typename ... IIterables>
    cPackIterableImpl(IIterables&& ... i_iterables);

protected:
    inline private_node_pointer_type createNode(const private_node_type& i_pack) const;
    inline void deleteNode(private_node_pointer_type i_node) const;
    template<int Index>
    requires ( Index < Traits::numIterables )
    inline auto& get_nth_iterable();
    template<int Index>
    requires ( Index < Traits::numIterables )
    inline const auto& get_nth_iterable() const;
    template<int ... Indexs>
    inline bool is_any_end(private_node_pointer_type i_node) const;
    template<typename NodePointer>
    inline bool is_head(const NodePointer* i_nodePointer) const
    {
        return i_nodePointer == this->getHead();
    }

private:

    //private interface implementation
    node_pointer_type getFirstElem() const override;
    node_pointer_type getNextElem(node_pointer_type currNode) const override;
    node_pointer_type acquireNode(node_pointer_type i_node) const override;
    void releaseNode(node_pointer_type i_node) const override;
    const_reference getValue(node_pointer_type currNode) const override;
    reference getValue(node_pointer_type currNode) override;

    template<int ... Indexs>
    inline node_pointer_type _getFirstElem(const mpl::sequence<Indexs...>&) const;
    template<int ... Indexs>
    inline node_pointer_type _getNextElem(const mpl::sequence<Indexs...>&, node_pointer_type i_currNode) const;
    template<int ... Indexs>
    const_reference _getValue(const mpl::sequence<Indexs...>&, node_pointer_type i_currNode) const;
    template<int ... Indexs>
    reference _getValue(const mpl::sequence<Indexs...>&, node_pointer_type i_currNode);

    iterable_pack m_iterables;
};

template<typename Traits>
class cInputPackIterableImpl : public cPackIterableImpl<Traits>
{
    typedef cPackIterableImpl<Traits> base_type;
    typedef typename Traits::node_pointer_type node_pointer_type;

public:
    typedef typename base_type::iterator_type iterator_type;
    typedef typename base_type::const_iterator_type const_iterator_type;
	typedef typename base_type::value_type value_type;
	typedef typename base_type::pointer_type pointer_type;
	typedef typename base_type::reference reference;
	typedef typename base_type::const_reference const_reference;

    using base_type::base_type;
    using base_type::begin;
    using base_type::end;
    using base_type::cbegin;
    using base_type::cend;
    using base_type::getSize;
    using base_type::empty;
};

template<typename Traits>
using cForwardPackIterableImpl = cInputPackIterableImpl<Traits>;

template<typename Traits>
class cBidirectionalPackIterableImpl : public cForwardPackIterableImpl<Traits>
{
    typedef cForwardPackIterableImpl<Traits> base_type;
    typedef typename Traits::private_node_pointer_type private_node_pointer_type;
	typedef typename Traits::node_pointer_type node_pointer_type;

public:
    typedef typename base_type::iterator_type iterator_type;
    typedef typename base_type::const_iterator_type const_iterator_type;
	typedef typename base_type::value_type value_type;
	typedef typename base_type::pointer_type pointer_type;
	typedef typename base_type::reference reference;
	typedef typename base_type::const_reference const_reference;
    typedef typename Traits::reverse_iterator_type reverse_iterator_type;
    typedef typename Traits::const_reverse_iterator_type const_reverse_iterator_type;

    using base_type::base_type;
    using base_type::begin;
    using base_type::end;
    using base_type::cbegin;
    using base_type::cend;
    using base_type::getSize;
    using base_type::empty;

protected:
    node_pointer_type getLastElem() const override;
    node_pointer_type getPrevElem(node_pointer_type currNode) const override;

    template<int ... Indexs>
    inline node_pointer_type _getLastElem(const mpl::sequence<Indexs...>&) const;
    template<int ... Indexs>
    inline node_pointer_type _getPrevElem(const mpl::sequence<Indexs...>&, node_pointer_type i_currNode) const;
};

template<typename Traits>
class cRandomAccessPackIterableImpl : public cBidirectionalPackIterableImpl<Traits>
{
    typedef cBidirectionalPackIterableImpl<Traits> base_type;
    typedef typename Traits::private_node_pointer_type private_node_pointer_type;
	typedef typename Traits::node_pointer_type node_pointer_type;

public:
    typedef typename base_type::iterator_type iterator_type;
    typedef typename base_type::const_iterator_type const_iterator_type;
	typedef typename base_type::value_type value_type;
	typedef typename base_type::pointer_type pointer_type;
	typedef typename base_type::reference reference;
	typedef typename base_type::const_reference const_reference;

    using base_type::base_type;
    using base_type::begin;
    using base_type::end;
    using base_type::rbegin;
    using base_type::rend;
    using base_type::cbegin;
    using base_type::cend;
    using base_type::crbegin;
    using base_type::crend;
    using base_type::getSize;
    using base_type::empty;

private:
    size_t getIndexOfNode(node_pointer_type node) const override;
    node_pointer_type shiftNodeByIndex(node_pointer_type node, int val) const override;

    template<int ... Indexs>
    inline node_pointer_type _shiftNodeByIndex(const mpl::sequence<Indexs...>&, node_pointer_type i_currNode, int val) const;
};

}
}
}

#include "YTL/container/detail/cPackIterableImpl.tpp"
