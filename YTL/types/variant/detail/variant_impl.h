
/*This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#pragma once

#include "YTL/types/embedded_type/embedded_type.h"
#include "YTL/mpl/cVariantTemplateHelper.h"

#define CREATE_INNER_VISITOR(_visitor,_types) \
    typedef typename mpl::create_range_rank<0,mpl::get_num_types<_types...>::value>::type _range_seq_t; \
    typedef variant_visitor_invoker<decltype(_visitor),_types...> _variant_visitor_t;

#define CALL_INNER_VISITOR(_visitor,_variant) \
    _variant_visitor_t::template invoke(_range_seq_t{},_visitor,_variant); \

namespace yame
{
namespace ytl
{
namespace detail
{

template<typename ... Types>
class variant_impl
{
    template<typename ...>
    friend class variant_impl;
    template<typename,typename ...>
    friend class variant_visitor_invoker;

public:
    variant_impl();
    void construct(const variant_impl<Types...>& other);
    void construct(variant_impl<Types...>&& other);
    template<typename ... TTypes>
    void construct(const variant_impl<TTypes...>& other);
    template<typename ... TTypes>
    void construct(variant_impl<TTypes...>&& other);
    template<size_t Index, typename TType>
    requires ( mpl::is_variant<TType>::value == false )
    void construct(TType&& other);
    void destroy();
    ~variant_impl();
    variant_impl<Types...>& operator=(const variant_impl<Types...>& other);
    variant_impl<Types...>& operator=(variant_impl<Types...>&& other);
    template<typename ... TTypes>
    variant_impl<Types...>& operator=(const variant_impl<TTypes...>& other);
    template<typename ... TTypes>
    variant_impl<Types...>& operator=(variant_impl<TTypes...>&& other);
    template<size_t Index, typename TType>
    requires (mpl::is_variant<TType>::value == false)
    variant_impl<Types...>& assign(TType&& val);
    bool operator==(const variant_impl<Types...>& other) const;
    bool operator==(variant_impl<Types...>&& other) const;
    bool operator!=(const variant_impl<Types...>& other) const;
    bool operator!=(variant_impl<Types...>&& other) const;
    template<size_t Index, typename TType>
    requires (mpl::is_variant<TType>::value == false)
    bool compare(TType&& other) const;
    template<typename TType>
    typename embedded_type<TType>::ref_type get() const;
    template<typename TType>
    TType extract();
    template<typename TType>
    bool is() const;
    template<size_t Pos>
    typename embedded_type<typename mpl::nth_type_of<Pos,Types...>::type>::ref_type get() const;
    template<size_t Pos>
    typename mpl::nth_type_of<Pos,Types...>::type extract();
    template<size_t Pos>
    bool is() const;
    bool empty() const;
    char which() const;
    void reset();
    void swap(variant_impl<Types...>& other);
    template<typename Visitor>
    typename Visitor::result_type apply_visitor(const Visitor& visitor);
    template<typename Visitor>
    typename Visitor::result_type apply_visitor(const Visitor& visitor) const;

private:
    static const int _numTypes = mpl::get_num_types<Types...>::value;
    typedef typename mpl::max_size_of<embedded_type<Types>...>::type dominantType;

    typedef typename std::aligned_storage<sizeof(dominantType), std::alignment_of<dominantType>::value>::type data_type;
    data_type	m_storage;
    char		m_currentType;
};

}
}
}

#include "YTL/types/variant/detail/variant_impl.tpp"
