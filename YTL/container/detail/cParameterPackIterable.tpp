
namespace yame
{
namespace container
{

template<typename ... Types>
parameter_pack_iterable<Types...>::parameter_pack_iterable(parameter_pack<Types...>& i_pack)
: m_pack(i_pack)
{
}
template<typename ... Types>
parameter_pack_iterable<Types...>::parameter_pack_iterable(const parameter_pack_iterable& other)
: m_pack(other.m_pack)
{
}
template<typename ... Types>
typename parameter_pack_iterable<Types...>::node_pointer_type parameter_pack_iterable<Types...>::getFirstElem() const
{
    typedef typename mpl::nth_type_of<0,Types...>::type retType;

    return detail::sendNodeToIterator<node_pointer_type>(PACK_STORAGE_ADDRESS(m_pack.m_storage));
}
template<typename ... Types>
typename parameter_pack_iterable<Types...>::node_pointer_type parameter_pack_iterable<Types...>::getLastElem() const
{
    return detail::sendNodeToIterator<node_pointer_type>(PACK_STORAGE_ADDRESS(m_pack.m_storage) + data_offset::at(s_num_types-1));
}
template<typename ... Types>
typename parameter_pack_iterable<Types...>::node_pointer_type parameter_pack_iterable<Types...>::getNextElem(node_pointer_type currNode) const
{
    const address_type currNodeChar = detail::receiveNodeFromIterator<address_type>(currNode);

    const size_t typeOffset = data_offset::index(currNodeChar - PACK_STORAGE_ADDRESS(m_pack.m_storage));

    if(typeOffset >= 0 && typeOffset < s_num_types - 1)
    {
        return detail::sendNodeToIterator<node_pointer_type>(PACK_STORAGE_ADDRESS(m_pack.m_storage) + data_offset::at(typeOffset + 1));
    }
    else
    {
        return iterable_type::m_pHead;
    }
}
template<typename ... Types>
typename parameter_pack_iterable<Types...>::node_pointer_type parameter_pack_iterable<Types...>::getPrevElem(node_pointer_type currNode) const
{
    const address_type currNodeChar = detail::receiveNodeFromIterator<address_type>(currNode);

    const size_t typeOffset = data_offset::index(currNodeChar - PACK_STORAGE_ADDRESS(m_pack.m_storage));

    if(typeOffset > 0 && typeOffset < s_num_types)
    {
        return detail::sendNodeToIterator<node_pointer_type>(PACK_STORAGE_ADDRESS(m_pack.m_storage) + data_offset::at(typeOffset - 1));
    }
    else
    {
        return iterable_type::m_pHead;
    }
}
template<typename ... Types>
template<int ... Indexs>
typename parameter_pack_iterable<Types...>::const_value_type parameter_pack_iterable<Types...>::construct_values(const mpl::sequence<Indexs...>&, node_pointer_type i_currNode) const
{
    typedef const_value_type(parameter_pack_iterable<Types...>::* const funcType)() const;

    static const funcType funcTable[s_num_types] = { &parameter_pack_iterable<Types...>::construct_value<Indexs> ... };

    const address_type currNodeChar = detail::receiveNodeFromIterator<address_type>(i_currNode);

    const size_t typeOffset = data_offset::index(currNodeChar - PACK_STORAGE_ADDRESS(m_pack.m_storage));

    return (this->*funcTable[typeOffset])();
}
template<typename ... Types>
template<int ... Indexs>
typename parameter_pack_iterable<Types...>::value_type parameter_pack_iterable<Types...>::construct_values(const mpl::sequence<Indexs...>&, node_pointer_type i_currNode)
{
    typedef value_type(parameter_pack_iterable<Types...>::*funcType)();

    static const funcType funcTable[s_num_types] = { &parameter_pack_iterable<Types...>::construct_value<Indexs> ... };

    const address_type currNodeChar = detail::receiveNodeFromIterator<address_type>(i_currNode);

    const size_t typeOffset = data_offset::index(currNodeChar - PACK_STORAGE_ADDRESS(m_pack.m_storage));

    return (this->*funcTable[typeOffset])();
}
template<typename ... Types>
typename parameter_pack_iterable<Types...>::const_reference parameter_pack_iterable<Types...>::getValue(node_pointer_type i_currNode) const
{
    return construct_values(typename mpl::create_range_rank<0,s_num_types>::type{},i_currNode);
}
template<typename ... Types>
typename parameter_pack_iterable<Types...>::reference parameter_pack_iterable<Types...>::getValue(node_pointer_type i_currNode)
{
    return construct_values(typename mpl::create_range_rank<0,s_num_types>::type{},i_currNode);
}
template<typename ... Types>
typename parameter_pack_iterable<Types...>::node_pointer_type parameter_pack_iterable<Types...>::shiftNodeByIndex(node_pointer_type currNode, int index) const
{
    const address_type currNodeChar = detail::receiveNodeFromIterator<address_type>(currNode);

    const size_t typeOffset = data_offset::index(currNodeChar - PACK_STORAGE_ADDRESS(m_pack.m_storage));

    if(typeOffset >= 0 && typeOffset < s_num_types - index)
    {
        return detail::sendNodeToIterator<node_pointer_type>(PACK_STORAGE_ADDRESS(m_pack.m_storage) + data_offset::at(typeOffset + index));
    }
    else
    {
        return iterable_type::m_pHead;
    }
}
template<typename ... Types>
size_t parameter_pack_iterable<Types...>::getIndexOfNode(node_pointer_type i_currNode) const
{
    const address_type currNodeChar = detail::receiveNodeFromIterator<address_type>(i_currNode);

    return data_offset::index(currNodeChar - PACK_STORAGE_ADDRESS(m_pack.m_storage));
}

template<typename ... Types>
parameter_pack_iterable<Types...> make_iterable(parameter_pack<Types...>& i_pack)
{
    return parameter_pack_iterable<Types...>(i_pack);
}


}
}
