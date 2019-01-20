#pragma once

#include "YTL/mpl/cIteratorTemplateHelper.h"

namespace yame
{
namespace mpl
{

template<typename,typename...>
struct iterable_circular_dep_compliant;

template<typename Traits>
struct iterable_circular_dep_compliant<Traits>
{
    static bool checkCircularDep(const typename Traits::forwarded_iterable_private_interface& thisObject)
    {
        return false;
    }
};

template<typename Traits, typename Iterable,typename ... Iterables>
struct iterable_circular_dep_compliant<Traits,Iterable,Iterables...>
{
    static bool checkCircularDep(const typename Traits::forwarded_iterable_private_interface& thisObject, const Iterable& i_iterable, const Iterables& ... i_iterables)
    {
        return static_cast<const void *>(&thisObject) == static_cast<const void*>(&i_iterable) || iterable_circular_dep_compliant<Traits,Iterables...>::checkCircularDep(thisObject, i_iterables...);
    }
};

template<typename,typename...>
struct iterable_iterator_compliant;

template<typename Traits>
struct iterable_iterator_compliant<Traits>
{
    static const bool value = true;
};

template<typename Traits, typename Iterator,typename ... Iterators>
struct iterable_iterator_compliant<Traits,Iterator,Iterators...>
{
    static const bool value = mpl::is_base_of<typename Traits::iterator_type, Iterator>::value
                                && iterable_iterator_compliant<Traits,Iterators...>::value;
};

template<typename,container::detail::ReferenceCategory...>
struct iterable_category_compliant;

template<typename Traits>
struct iterable_category_compliant<Traits>
{
    static const bool value = true;
};

template<typename Traits,container::detail::ReferenceCategory category,container::detail::ReferenceCategory ... categories>
struct iterable_category_compliant<Traits,category,categories...>
{
    static const bool value = (Traits::forwarded_category == container::detail::ReferenceCategory::Value ||
                                (Traits::forwarded_category == container::detail::ReferenceCategory::ConstReference && category != container::detail::ReferenceCategory::Value) ||
                                (Traits::forwarded_category == container::detail::ReferenceCategory::NonConstReference && category == container::detail::ReferenceCategory::NonConstReference))
                                && iterable_category_compliant<Traits,categories...>::value;
};

template<typename,typename ...>
struct iterable_constness_compliant;

template<typename Traits>
struct iterable_constness_compliant<Traits>
{
    static const bool value = true;
};

template<typename Traits,typename Iterable,typename ... Iterables>
struct iterable_constness_compliant<Traits,Iterable,Iterables...>
{
    static const bool value = (Traits::iterable_public_interface::is_const == true || Iterable::is_const == false)
                                && iterable_constness_compliant<Traits,Iterables...>::value;
};

}
}
