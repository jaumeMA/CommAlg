
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

#include "YTL/container/detail/cTupla_impl.h"
#include "YTL/container/cContainerView.h"
#include "YTL/container/cIterableBase.h"
#include "YTL/container/detail/cTupla_storage.h"

namespace yame
{
namespace container
{

template<typename T, int ... ranks>
class cTupla;

template<typename T, int rank, int ... ranks>
class cTupla<T,rank,ranks...> : public detail::cTuplaStorage<T,PROD_RANKS(rank,ranks)>, public detail::cConstRandomAccessIterableBaseImpl<cPair<cTupla<size_t,mpl::get_num_ranks<ranks...>::value + 1>,T&>>
{
    static_assert(mpl::is_const<T>::value == false && mpl::is_reference<T>::value == false, "Const/ reference types are not supported");
    static const size_t       m_rank=PROD_RANKS(rank,ranks);

    template<typename,int ...>
    friend class cTupla;

public:
    typedef T value_type;
    typedef cPair<cTupla<size_t,mpl::get_num_ranks<ranks...>::value + 1>,T&> iterator_pair;
    typedef detail::cConstRandomAccessIterableBaseImpl<iterator_pair> iterable_type;
    typedef typename iterable_type::node_pointer_type node_pointer_type;
    typedef typename iterable_type::iterator_type iterator_type;
    typedef typename iterable_type::const_iterator_type const_iterator_type;
    typedef typename iterable_type::iterable_public_interface iterable_public_interface;
    typedef typename iterable_type::reference reference;
    typedef typename iterable_type::const_reference const_reference;
    static const detail::ReferenceCategory category = iterator_type::category;
    typedef typename detail::cTuplaStorage<T,PROD_RANKS(rank,ranks)>::primitive_type primitive_type;

    cTupla();
    cTupla(const cTupla<T,rank,ranks...>& other);
    template<typename TT>
    requires (mpl::is_constructible<T,TT>::value )
    cTupla(const detail::cSubTuple<TT,rank,ranks...>& other);
    template<typename TT>
    requires (mpl::is_constructible<T,TT>::value )
    cTupla(const cTupla<TT,rank,ranks...>& other);
    template<typename TT>
    requires (mpl::is_constructible<T,TT>::value )
    cTupla(const std::initializer_list<TT>& i_tupleList);
    ~cTupla();
    detail::cSubTuple<T,ranks...> operator[](size_t index);
    detail::cSubTuple<const T,ranks...> operator[](size_t index) const;
    cTupla<T,rank,ranks...>& operator=(const cTupla<T,rank,ranks...>& other);
    template<typename TT>
    requires (mpl::is_constructible<T,TT>::value )
    cTupla<T,rank,ranks...>& operator=(const cTupla<TT,rank,ranks...>& other);
    operator detail::cSubTuple<T,rank,ranks...>();
    operator detail::cSubTuple<const T,rank,ranks...>() const;
    size_t getSize() const override;

private:
    //const iterable implementation
    node_pointer_type getFirstElem() const override;
    node_pointer_type getLastElem() const override;
    node_pointer_type getNextElem(node_pointer_type currNode) const override;
    node_pointer_type getPrevElem(node_pointer_type currNode) const override;
    const_reference getValue(node_pointer_type) const override;
    reference getValue(node_pointer_type) override;
    node_pointer_type shiftNodeByIndex(node_pointer_type currNode, int index) const override;
    size_t getIndexOfNode(node_pointer_type node) const override;
};

template<typename T, int rank>
class cTupla<T,rank> : public detail::cTuplaStorage<T,rank>, public detail::cConstRandomAccessIterableBaseImpl<cPair<cTupla<size_t,1>,T&>>
{
    static_assert(mpl::is_const<T>::value == false && mpl::is_reference<T>::value == false, "Const/ reference types are not supported");
    static const size_t       m_rank=rank;

    template<typename,int ...>
    friend class cTupla;

public:
    typedef T value_type;
    typedef cPair<cTupla<size_t,1>,T&> iterator_pair;
    typedef detail::cConstRandomAccessIterableBaseImpl<iterator_pair> iterable_type;
    typedef typename iterable_type::node_pointer_type node_pointer_type;
    typedef typename iterable_type::iterator_type iterator_type;
    typedef typename iterable_type::const_iterator_type const_iterator_type;
    typedef typename iterable_type::iterable_public_interface iterable_public_interface;
    typedef typename iterable_type::reference reference;
    typedef typename iterable_type::const_reference const_reference;
    static const detail::ReferenceCategory category = iterator_type::category;
    typedef typename detail::cTuplaStorage<T,rank>::primitive_type primitive_type;
    using detail::cTuplaStorage<T,rank>::operator[];

    cTupla();
    cTupla(const cTupla<T,rank>& other);
    template<typename TT>
    requires (mpl::is_constructible<T,TT>::value )
    cTupla(const detail::cSubTuple<TT,rank>& other);
    template<typename TT>
    requires (mpl::is_constructible<T,TT>::value )
    cTupla(const cTupla<TT,rank>& other);
    template<typename TT>
    requires (mpl::is_constructible<T,TT>::value )
    cTupla(const std::initializer_list<TT>& i_tupleList);
    ~cTupla();
    cTupla<T,rank>& operator=(const cTupla<T,rank>& other);
    template<typename TT>
    requires (mpl::is_constructible<T,TT>::value )
    cTupla<T,rank>& operator=(const cTupla<TT,rank>& other);
    operator detail::cSubTuple<T,rank>();
    operator detail::cSubTuple<const T,rank>() const;
    template<typename TT>
    requires ( rank==1 && mpl::is_same_type<T,TT>::value )
    operator TT&();
    template<typename TT>
    requires ( rank==1 && mpl::is_same_type<T,TT>::value )
    operator const TT&() const;
    size_t getSize() const override;

private:
    //const iterable implementation
    node_pointer_type getFirstElem() const override;
    node_pointer_type getLastElem() const override;
    node_pointer_type getNextElem(node_pointer_type currNode) const override;
    node_pointer_type getPrevElem(node_pointer_type currNode) const override;
    const_reference getValue(node_pointer_type) const override;
    reference getValue(node_pointer_type) override;
    node_pointer_type shiftNodeByIndex(node_pointer_type currNode, int index) const override;
    size_t getIndexOfNode(node_pointer_type node) const override;
};

template<typename T>
using tupla_view = cRandomAccessView<T&>;
template<typename T>
using const_tupla_view = cConstRandomAccessView<T&>;

template<typename T, int ... ranks, typename Arg, typename ... Args>
requires( mpl::are_same_type<Arg,Args...>::value )
cTupla<T,ranks...> make_tupla(Args&& ... i_args);

}
}

#include "detail/cTupla.tpp"
