
#include "YTL/types/variant/detail/variant_impl.h"

namespace yame
{
namespace ytl
{
namespace detail
{

template<typename Variant, size_t TypePos, typename ... Types>
template<typename T>
requires ( mpl::is_same_type<T,typename mpl::nth_type_of<TypePos-1,Types...>::type>::value )
_variant_interface<Variant,TypePos,Types...>::_variant_interface(T&& other)
{
    Variant::template construct<TypePos>(mpl::forward<T>(other));
}
template<typename Variant, size_t TypePos, typename ... Types>
template<typename T>
requires ( mpl::is_same_type<T,typename mpl::nth_type_of<TypePos-1,Types...>::type>::value )
_variant_interface<Variant,TypePos,Types...>& _variant_interface<Variant,TypePos,Types...>::operator=(T&& other)
{
    Variant::template assign<TypePos>(mpl::forward<T>(other));

    return *this;
}
template<typename Variant, size_t TypePos, typename ... Types>
bool _variant_interface<Variant,TypePos,Types...>::operator==(const rawType& other) const
{
    return Variant::template compare<TypePos>(other);
}
template<typename Variant, size_t TypePos, typename ... Types>
bool _variant_interface<Variant,TypePos,Types...>::operator==(rawType&& other) const
{
    return Variant::template compare<TypePos>(mpl::move(other));
}

}
}
}
