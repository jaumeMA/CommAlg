#pragma once

#include "YTL/container/cIterableBase.h"
#include "YTL/container/cParameterPack.h"
#include "YTL/types/variant/variant.h"

namespace yame
{
namespace container
{

template<typename ... Types>
class parameter_pack_iterable : public detail::cConstRandomAccessIterableBaseImpl<ytl::variant<typename mpl::add_reference<Types>::type ...>>
{
public:
    typedef ytl::variant<typename mpl::add_reference<Types>::type ...> value_type;
    typedef ytl::variant<typename mpl::add_constness<typename mpl::add_reference<Types>::type>::type ...> const_value_type;
    typedef detail::cConstRandomAccessIterableBaseImpl<value_type> iterable_type;
    typedef typename iterable_type::node_pointer_type node_pointer_type;
    typedef typename iterable_type::iterator_type iterator_type;
    typedef typename iterable_type::const_iterator_type const_iterator_type;
    typedef typename iterable_type::iterable_public_interface iterable_public_interface;
    typedef typename iterable_type::reference reference;
    typedef typename iterable_type::const_reference const_reference;
    static const detail::ReferenceCategory category = iterator_type::category;

    parameter_pack_iterable(parameter_pack<Types...>& i_pack);
    parameter_pack_iterable(const parameter_pack_iterable& other);

private:
    typedef typename parameter_pack<Types...>::data_offset data_offset;
    typedef char* address_type;
    static const size_t s_num_types = mpl::get_num_types<Types...>::value;

    template<int ... Indexs>
    inline const_value_type construct_values(const mpl::sequence<Indexs...>&, node_pointer_type i_currNode) const;
    template<int ... Indexs>
    inline value_type construct_values(const mpl::sequence<Indexs...>&, node_pointer_type i_currNode);
    template<size_t Index>
    inline const_value_type construct_value() const
    {
        const_value_type res;

        res.template construct<Index>(m_pack.template getValue<Index>());

        return res;
    }
    template<size_t Index>
    inline value_type construct_value()
    {
        value_type res;

        res.template construct<Index>(m_pack.template getValue<Index>());

        return res;
    }

    //const iterable implementation
    node_pointer_type getFirstElem() const override;
    node_pointer_type getLastElem() const override;
    node_pointer_type getNextElem(node_pointer_type currNode) const override;
    node_pointer_type getPrevElem(node_pointer_type currNode) const override;
    const_reference getValue(node_pointer_type) const override;
    reference getValue(node_pointer_type) override;
    node_pointer_type shiftNodeByIndex(node_pointer_type currNode, int index) const override;
    size_t getIndexOfNode(node_pointer_type node) const override;

    parameter_pack<Types...>& m_pack;
};

template<typename T>
using parameter_pack_view = cRandomAccessView<T&>;
template<typename T>
using const_parameter_pack_view = cConstRandomAccessView<T&>;

template<typename ... Types>
inline parameter_pack_iterable<Types...> make_iterable(parameter_pack<Types...>& i_pack);

}
}

#include "YTL/container/detail/cParameterPackIterable.tpp"
