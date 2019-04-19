#pragma once

#include "YTL/container/detail/cIterablePackIterableImpl.h"
#include "YTL/container/cParameterPack.h"
#include "YTL/types/smartPtr/lent_ptr.h"

namespace yame
{
namespace container
{
namespace detail
{

template<template <typename> class Iterable, typename  Traits>
using cConstIterablePackIterable = Iterable<Traits>;

template<template<typename> class Iterable, typename ... Types>
struct IterablePackIterableTraits
{
    typedef parameter_pack<Types ...> type_pack;
    typedef parameter_pack<ytl::lent_ref<typename Iterable<Types>::iterable_private_interface> ...> iterable_pack;
    typedef parameter_pack<typename Iterable<Types>::node_pointer_type ...> private_node_type;
    typedef typename mpl::add_pointer<private_node_type>::type private_node_pointer_type;
    static const size_t numIterables = mpl::get_num_types<Types...>::value;
    typedef Iterable<type_pack> iterable_type;
    static const ReferenceCategory category = iterable_type::category;
	typedef typename iterable_type::iterable_public_interface iterable_public_interface;
	typedef typename iterable_type::iterable_private_interface iterable_private_interface;
    typedef typename iterable_public_interface::iterator_type iterator_type;
    typedef typename iterable_public_interface::const_iterator_type const_iterator_type;
	typedef typename iterator_type::raw_type raw_type;
	typedef typename iterator_type::value_type value_type;
	typedef typename iterator_type::pointer_type pointer_type;
	typedef typename iterator_type::node_pointer_type node_pointer_type;
	typedef typename iterator_type::reference reference;
	typedef typename iterator_type::const_reference const_reference;
};

template<template<typename> class Iterable, typename ... Types>
struct ReversableIterablePackIterableTraits : IterablePackIterableTraits<Iterable,Types...>
{
    typedef parameter_pack<Types ...> type_pack;
    typedef Iterable<type_pack> iterable_type;
    typedef typename iterable_type::reverse_iterator_type reverse_iterator_type;
    typedef typename iterable_type::const_reverse_iterator_type const_reverse_iterator_type;
};

}

//const pack iterable
template<typename ... Types>
using cConstInputIterablePackIterable = detail::cConstIterablePackIterable<detail::cInputIterablePackIterableImpl,detail::IterablePackIterableTraits<detail::cConstInputIterableBaseImpl,Types...>>;
template<typename ... Types>
using cConstForwardIterablePackIterable = detail::cConstIterablePackIterable<detail::cForwardIterablePackIterableImpl,detail::IterablePackIterableTraits<detail::cConstForwardIterableBaseImpl,Types...>>;
template<typename ... Types>
using cConstBidirectionalIterablePackIterable = detail::cConstIterablePackIterable<detail::cBidirectionalIterablePackIterableImpl,detail::ReversableIterablePackIterableTraits<detail::cConstBidirectionalIterableBaseImpl,Types...>>;
template<typename ... Types>
using cConstRandomAccessIterablePackIterable = detail::cConstIterablePackIterable<detail::cRandomAccessIterablePackIterableImpl,detail::ReversableIterablePackIterableTraits<detail::cConstRandomAccessIterableBaseImpl,Types...>>;

}
}
