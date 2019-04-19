#pragma once

namespace yame
{
namespace ytl
{
namespace detail
{

template<typename Variant, size_t TypePos, typename ... Types>
class _variant_interface;

template<typename Variant, size_t TypePos, typename ... Types>
class _variant_interface : public _variant_interface<Variant,TypePos-1,Types...>
{
    typedef typename mpl::nth_type_of<TypePos-1,Types...>::type CurrType;
    typedef typename mpl::drop_constness<typename mpl::drop_reference<CurrType>::type>::type rawType;
    typedef _variant_interface<Variant,TypePos-1,Types...> variant_base_t;

public:
    using variant_base_t::_variant_interface;
    using variant_base_t::operator=;
    using variant_base_t::operator==;
    using variant_base_t::operator!=;
    using variant_base_t::construct;
    using variant_base_t::get;
    using variant_base_t::extract;
    using variant_base_t::empty;
    using variant_base_t::is;
    using variant_base_t::which;
    using variant_base_t::reset;
    using variant_base_t::swap;
    using variant_base_t::apply_visitor;

    _variant_interface() = default;
    template<typename T>
    requires ( mpl::is_same_type<T,typename mpl::nth_type_of<TypePos-1,Types...>::type>::value )
    _variant_interface(T&& other);
    template<typename T>
    requires ( mpl::is_same_type<T,typename mpl::nth_type_of<TypePos-1,Types...>::type>::value )
    _variant_interface& operator=(T&& other);
    bool operator==(const rawType& other) const;
    bool operator==(rawType&& other) const;
};

template<typename Variant, typename ... Types>
class _variant_interface<Variant,0,Types...> : public Variant
{
public:
    using Variant::operator=;
    using Variant::operator==;
    using Variant::operator!=;
    using Variant::construct;
    using Variant::get;
    using Variant::extract;
    using Variant::empty;
    using Variant::is;
    using Variant::which;
    using Variant::reset;
    using Variant::swap;
    using Variant::apply_visitor;

    _variant_interface() = default;
};

}

template<typename Variant, typename ... Types>
class variant_interface : public detail::_variant_interface<Variant,mpl::get_num_types<Types...>::value,Types...>
{
    typedef detail::_variant_interface<Variant,mpl::get_num_types<Types...>::value,Types...> variant_base_t;

public:
    using variant_base_t::_variant_interface;
    using variant_base_t::operator=;
    using variant_base_t::operator==;
    using variant_base_t::operator!=;
    using variant_base_t::construct;
    using variant_base_t::get;
    using variant_base_t::extract;
    using variant_base_t::empty;
    using variant_base_t::is;
    using variant_base_t::which;
    using variant_base_t::reset;
    using variant_base_t::swap;
    using variant_base_t::apply_visitor;
};

}
}

#include "YTL/types/variant/detail/variant_interface.tpp"
