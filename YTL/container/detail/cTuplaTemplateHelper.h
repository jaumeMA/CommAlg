#pragma once

namespace yame
{
namespace container
{

template<typename T, int rank, int ... ranks>
class cTupla;

namespace detail
{

template<typename T, int ... ranks>
class cTupla_impl;

}
}

namespace mpl
{

template<typename>
struct is_tupla
{
    static const bool value = false;
};
template<typename T, int ... ranks>
struct is_tupla<container::detail::cTupla_impl<T,ranks...>>
{
    static const bool value = true;
};
template<typename T, int rank, int ... ranks>
struct is_tupla<container::cTupla<T,rank,ranks...>>
{
    static const bool value = true;
};

template<typename ... Types>
struct are_tupla
{
    static const bool value = (is_tupla<Types>::value && ...);
};

}
}
