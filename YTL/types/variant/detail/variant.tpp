
#include "YTL/types/variant/detail/variant_interface.h"

namespace yame
{
namespace ytl
{

template<typename ... Types>
variant<Types...>::variant()
{
}
template<typename ... Types>
variant<Types...>::variant(const variant<Types...>& other)
{
    variant_interface_base::construct(other);
}
template<typename ... Types>
template<typename ... TTypes>
requires ( mpl::get_num_types<Types...>::value == mpl::get_num_types<TTypes...>::value )
variant<Types...>::variant(const variant<TTypes...>& other)
{
    static const bool constrCond = ( mpl::is_constructible<Types,TTypes>::value && ... );

    static_assert(constrCond, "You shall provide constructible types");

    variant_interface_base::construct(other);
}
template<typename ... Types>
template<typename TType>
requires ( mpl::is_variant<TType>::value == false )
variant<Types...>::variant(TType&& other)
{
    variant_interface_base::construct(std::forward<TType>(other));
}
template<typename ... Types>
variant<Types...>::~variant()
{

}
template<typename ... Types>
variant<Types...>& variant<Types...>::operator=(const variant<Types...>& other)
{
    variant_interface_base::operator=(other);

    return *this;
}

}
}
