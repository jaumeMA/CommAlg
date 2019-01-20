#pragma once

namespace yame
{
namespace container
{

template<typename, int ...>
class cTupla;

}

namespace mpl
{

template<typename>
struct is_tupla
{
    static const bool value = false;
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

template<typename,int ...>
struct compute_tupla_indexs;

template<typename T, int rank>
struct compute_tupla_indexs<T,rank>
{
    template<int Index, int ... rranks>
    static inline void _set(const T* i_origin, const T* i_currPos, container::cTupla<size_t,rranks...>& o_res)
    {
        o_res[Index] = static_cast<size_t>(i_currPos - i_origin);
    }
    static inline container::cTupla<size_t,1> of(const T* i_origin, const T* i_currPos)
    {
        return container::cTupla<size_t,1>( { static_cast<size_t>(i_currPos - i_origin) } );
    }
};

template<typename T, int rank, int ... ranks>
struct compute_tupla_indexs<T,rank,ranks...>
{
    template<int Index, int ... rranks>
    static inline void _set(const T* i_origin, const T* i_currPos, container::cTupla<size_t,rranks...>& o_res)
    {
        const size_t currIndex = static_cast<size_t>(i_currPos - i_origin) / rank;
        const size_t currReference = currIndex * mpl::Prod<ranks...>::value;
        const T* newOrigin = i_origin + currReference;
        const T* newCurrPos = i_currPos - currReference;

        o_res[Index] = currIndex;

        compute_tupla_indexs<T,ranks...>::template _set<Index + 1>(newOrigin,newCurrPos,o_res);
    }
    static inline container::cTupla<size_t,mpl::get_num_ranks<ranks...>::value+1> of(const T* i_origin, const T* i_currPos)
    {
        container::cTupla<size_t,mpl::get_num_ranks<ranks...>::value+1> res;

        _set<0>(i_origin,i_currPos,res);

        return res;
    }
};

}
}
