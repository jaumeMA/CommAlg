
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

#include "YTL/mpl/cTemplateHelper.h"
#include "YTL/container/detail/cTupla_storage.h"

#define SIGNATURE(T,dim) typename yame::mpl::create_function_signature<T,dim>::template is<>::type
#define BASE_TYPE(T) T
#define DEFINE_BASE_TYPE(T) typedef BASE_TYPE(T) base_type
#define SQUARE_TUPLE(T,rank,m) mpl::append_dim<T,m,rank,yame::container::cTupla>::template is<>::type
#define PROD_RANKS(rank,ranks) mpl::Prod<rank,ranks...>::value
#define DIM_TUPLE(rank,ranks) mpl::get_num_ranks<rank,ranks...>::value
#define PROD_TUPLE(T,rank,ranks,rankOther,ranksOther) cTupla<T,rank,ranks...,rankOther,ranksOther...>
#define SUM_TUPLE(T,rank,ranks,rankOther,ranksOther) cTupla<T,rank+rankOther,ranks...>
#define SUB_TUPLE(T,ranks) \
    typename mpl::get_sub_tuple<T,container::detail::cSubTuple,ranks...>::type

#define FUNCTION_CALL(T,rank) typename function_call<T,rank>::template is<>

namespace yame
{
namespace container
{
namespace detail
{

template<typename, int ...>
class cTupla;

template<typename, int ...>
class cSubTuple;
template<typename, int>
class cTuplaStorage;

template<typename T, int rank, int ... ranks>
class cSubTuple<T,rank,ranks...>
{
    static const size_t m_rank=mpl::Prod<rank,ranks...>::value;

    template<typename, int ...>
    friend class cTupla;
    template<typename, int ...>
    friend class cSubTuple;
    template<typename, int>
    friend class cTuplaStorage;

public:
    cSubTuple<T,rank,ranks...>();
    cSubTuple<T,rank,ranks...>(const cSubTuple<T,rank,ranks...>& other) = delete;
    cSubTuple<T,rank,ranks...>(cSubTuple<T,rank,ranks...>&& other);
    cSubTuple<T,rank,ranks...>(T* ref);
    cSubTuple<T,ranks...> operator[](size_t index);
    cSubTuple<const T,ranks...> operator[](size_t index) const;
    template<typename TT>
    requires ( mpl::is_constructible<T,TT>::value )
    cSubTuple<T,rank,ranks...>& operator=(const cSubTuple<TT,rank,ranks...>& other);
    template<typename Arg>
    cSubTuple<T,rank,ranks...>& operator=(Arg&& i_arg);
    explicit operator bool() const;
    T* _get_reference();
    const T* _get_reference() const;

private:
    T* m_ref;
};

template<typename T, int rank>
class cSubTuple<T,rank>
{
    template<typename, int ...>
    friend class cTupla;
    template<typename, int>
    friend class cTuplaStorage;

public:
    cSubTuple<T,rank>();
    cSubTuple<T,rank>(const cSubTuple<T,rank>& other) = delete;
    cSubTuple<T,rank>(cSubTuple<T,rank>&& other);
    explicit cSubTuple<T,rank>(T* ref);
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    template<typename TT>
    requires ( mpl::is_constructible<T,TT>::value )
    cSubTuple<T,rank>& operator=(const cSubTuple<TT,rank>& other);
    template<typename Arg>
    cSubTuple<T,rank>& operator=(Arg&& i_arg);
    explicit operator bool() const;
    T* _get_reference();
    const T* _get_reference() const;

private:
    T *m_ref;
};

}
}
}

#include "cTupla_impl.tpp"
