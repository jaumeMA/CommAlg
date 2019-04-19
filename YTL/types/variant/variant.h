
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

#include "YTL/types/variant/detail/variant_interface.h"

namespace yame
{
namespace ytl
{
template<typename ... Types>
class variant : public variant_interface<detail::variant_impl<Types...>, Types...>
{
    static_assert(mpl::get_num_types<Types...>::value > 0, "You have to provide at least one type to variant");
    static_assert(mpl::get_num_types<Types...>::value < 255, "You cannot provide more than 255 types to a variant!");

    typedef variant_interface<detail::variant_impl<Types...>, Types...> variant_interface_base;

public:
    using variant_interface_base::variant_interface;
    using variant_interface_base::operator=;
    using variant_interface_base::operator==;
    using variant_interface_base::operator!=;
    using variant_interface_base::construct;
    using variant_interface_base::get;
    using variant_interface_base::extract;
    using variant_interface_base::empty;
    using variant_interface_base::is;
    using variant_interface_base::which;
    using variant_interface_base::reset;
    using variant_interface_base::swap;
    using variant_interface_base::apply_visitor;

    variant();
    variant(const variant<Types...>& other);
    template<typename ... TTypes>
    requires ( mpl::get_num_types<Types...>::value == mpl::get_num_types<TTypes...>::value )
    variant(const variant<TTypes...>& other);
    template<typename TType>
    requires ( mpl::is_variant<TType>::value == false )
    variant(TType&& other);
    ~variant();
    variant<Types...>& operator=(const variant<Types...>& other);
};
}

namespace mpl
{

template<typename ... Types>
struct add_constness<ytl::variant<Types...>>
{
    typedef ytl::variant<typename mpl::add_constness<Types>::type ...> type;
};

}
}

#include "YTL/types/variant/detail/variant.tpp"
