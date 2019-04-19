#include "visitor_invoker.h"
#include "YTL/types/variant/detail/builtin_visitors.h"

namespace yame
{
namespace ytl
{
namespace detail
{

template<typename ... Types>
variant_impl<Types...>::variant_impl()
: m_currentType(_numTypes)
{
}
template<typename ... Types>
void variant_impl<Types...>::construct(const variant_impl<Types...>& other)
{
    m_currentType = other.m_currentType;

    if (other.m_currentType < _numTypes)
    {
        constructor_visitor<Types...> ctr(&m_storage);

        CREATE_INNER_VISITOR(ctr,Types);
        CALL_INNER_VISITOR(ctr,other);
    }
}
template<typename ... Types>
void variant_impl<Types...>::construct(variant_impl<Types...>&& other)
{
    m_currentType = other.m_currentType;

    if (other.m_currentType < _numTypes)
    {
        constructor_visitor<Types...> ctr(&m_storage);

        CREATE_INNER_VISITOR(ctr,Types);
        CALL_INNER_VISITOR(ctr,other);
    }

    other.destroy();
}
template<typename ... Types>
template<typename ... TTypes>
void variant_impl<Types...>::construct(const variant_impl<TTypes...>& other)
{
    m_currentType = other.m_currentType;

    if (other.m_currentType < _numTypes)
    {
        constructor_visitor<TTypes...> ctr(&m_storage);

        CREATE_INNER_VISITOR(ctr,TTypes);
        CALL_INNER_VISITOR(ctr,other);
    }
}
template<typename ... Types>
template<typename ... TTypes>
void variant_impl<Types...>::construct(variant_impl<TTypes...>&& other)
{
    m_currentType = other.m_currentType;

    if (other.m_currentType < _numTypes)
    {
        constructor_visitor<TTypes...> ctr(&m_storage);

        CREATE_INNER_VISITOR(ctr,TTypes);
        CALL_INNER_VISITOR(ctr,other);
    }

    other.destroy();
}
template<typename ... Types>
template<size_t Index, typename TType>
requires (mpl::is_variant<TType>::value== false)
void variant_impl<Types...>::construct(TType&& other)
{
    static_assert(Index >= 0 && Index < _numTypes, "Not found type!");

    m_currentType = Index;

    constructor_visitor<Types...>::template construct<Index>(&m_storage, mpl::forward<TType>(other));
}
template<typename ... Types>
void variant_impl<Types...>::destroy()
{
    if (m_currentType < _numTypes)
    {
        destructor_visitor<Types...> dtr(&m_storage);

        CREATE_INNER_VISITOR(dtr,Types);
        CALL_INNER_VISITOR(dtr,*this);

        m_currentType = _numTypes;
    }
}
template<typename ... Types>
variant_impl<Types...>::~variant_impl()
{
    destroy();
}
template<typename ... Types>
variant_impl<Types...>& variant_impl<Types...>::operator=(const variant_impl<Types...>& other)
{
    if (other.m_currentType < _numTypes)
    {
        if (m_currentType == other.m_currentType)
        {
            assigner_visitor<Types...> ctr(&m_storage);

            CREATE_INNER_VISITOR(ctr,Types);
            CALL_INNER_VISITOR(ctr,other);
        }
        else
        {
            destroy();

            constructor_visitor<Types...> ctr(&m_storage);

            CREATE_INNER_VISITOR(ctr,Types);
            CALL_INNER_VISITOR(ctr,other);

            m_currentType = other.m_currentType;
        }
    }
    else
    {
        destroy();
    }

    return *this;
}
template<typename ... Types>
variant_impl<Types...>& variant_impl<Types...>::operator=(variant_impl<Types...>&& other)
{
    if (other.m_currentType < _numTypes)
    {
        if (m_currentType == other.m_currentType)
        {
            assigner_visitor<Types...> ctr(&m_storage);

            CREATE_INNER_VISITOR(ctr,Types);
            CALL_INNER_VISITOR(ctr,other);
        }
        else
        {
            destroy();

            constructor_visitor<Types...> ctr(&m_storage);

            CREATE_INNER_VISITOR(ctr,Types);
            CALL_INNER_VISITOR(ctr,other);

            m_currentType = other.m_currentType;
        }
    }
    else
    {
        destroy();
    }

    other.destroy();

    return *this;
}
template<typename ... Types>
template<typename ... TTypes>
variant_impl<Types...>& variant_impl<Types...>::operator=(const variant_impl<TTypes...>& other)
{
    if (other.m_currentType < _numTypes)
    {
        if (m_currentType == other.m_currentType)
        {
            assigner_visitor<Types...> ctr(&m_storage);

            CREATE_INNER_VISITOR(ctr,TTypes);
            CALL_INNER_VISITOR(ctr,other);
        }
        else
        {
            destroy();

            constructor_visitor<Types...> ctr(&m_storage);

            CREATE_INNER_VISITOR(ctr,TTypes);
            CALL_INNER_VISITOR(ctr,other);

            m_currentType = other.m_currentType;
        }
    }
    else
    {
        destroy();
    }

    return *this;
}
template<typename ... Types>
template<typename ... TTypes>
variant_impl<Types...>& variant_impl<Types...>::operator=(variant_impl<TTypes...>&& other)
{
    if (other.m_currentType < _numTypes)
    {
        if (m_currentType == other.m_currentType)
        {
            assigner_visitor<Types...> ctr(&m_storage);

            CREATE_INNER_VISITOR(ctr,TTypes);
            CALL_INNER_VISITOR(ctr,other);
        }
        else
        {
            destroy();

            constructor_visitor<Types...> ctr(&m_storage);

            CREATE_INNER_VISITOR(ctr,TTypes);
            CALL_INNER_VISITOR(ctr,other);

            m_currentType = other.m_currentType;
        }
    }
    else
    {
        destroy();
    }

    other.destroy();

    return *this;
}
template<typename ... Types>
template<size_t Index, typename TType>
requires (mpl::is_variant<TType>::value == false)
variant_impl<Types...>& variant_impl<Types...>::assign(TType&& val)
{
    static_assert(Index >= 0 && Index < _numTypes, "Type out of bounds!");

    if (Index != m_currentType)
    {
        destroy();

        constructor_visitor<Types...>::template construct<Index>(&m_storage, mpl::forward<TType>(val));

        m_currentType = Index;
    }
    else if (m_currentType < _numTypes)
    {
        //just an assignment
        assigner_visitor<Types...>::template assign<Index>(&m_storage, mpl::forward<TType>(val));
    }

    return *this;
}

template<typename ... Types>
bool variant_impl<Types...>::operator==(const variant_impl<Types...>& other) const
{
    bool res = false;

    if (m_currentType == other.m_currentType)
    {
        if(m_currentType != _numTypes)
        {
            comparison_visitor<Types...,variant_impl<Types...> > comparator(*this);

            CREATE_INNER_VISITOR(comparator,Types);
            res = CALL_INNER_VISITOR(comparator,other);
        }
        else
        {
            //empty case, valid case (both were empty)
            res = true;
        }
    }

    return res;
}

template<typename ... Types>
bool variant_impl<Types...>::operator==(variant_impl<Types...>&& other) const
{
    bool res = false;

    if (m_currentType == other.m_currentType)
    {
        comparison_visitor<Types...,variant_impl<Types...> > comparator(*this);

        CREATE_INNER_VISITOR(comparator,Types);
        res = CALL_INNER_VISITOR(comparator,other);
    }

    return res;
}

template<typename ... Types>
bool variant_impl<Types...>::operator!=(const variant_impl<Types...>& other) const
{
    bool res = true;

    if (m_currentType == other.m_currentType)
    {
        comparison_visitor<Types...,variant_impl<Types...> > comparator(*this);

        CREATE_INNER_VISITOR(comparator,Types);
        res = !CALL_INNER_VISITOR(comparator,other);
    }

    return res;
}

template<typename ... Types>
bool variant_impl<Types...>::operator!=(variant_impl<Types...>&& other) const
{
    bool res = true;

    if (m_currentType == other.m_currentType)
    {
        comparison_visitor<Types...,variant_impl<Types...> > comparator(*this);

        CREATE_INNER_VISITOR(comparator,Types);
        res = !CALL_INNER_VISITOR(comparator,other);
    }

    return res;
}

template<typename ... Types>
template<size_t Index, typename TType>
requires (mpl::is_variant<TType>::value == false)
bool variant_impl<Types...>::compare(TType&& other) const
{
    bool res = false;

    if (m_currentType == Index)
    {
        typedef typename mpl::nth_type_of<Index, Types...>::type currType;
        typedef typename embedded_type<currType>::ref_type ref_type;

        val_retriever_visitor<currType,Types...> getter;

        CREATE_INNER_VISITOR(getter,Types);
        ref_type thisVal = CALL_INNER_VISITOR(getter,*this);

        res = (thisVal == mpl::forward<TType>(other));
    }

    return res;
}

template<typename ... Types>
template<typename TType>
typename embedded_type<TType>::ref_type variant_impl<Types...>::get() const
{
    ASSERT(is<TType>(), "Accessing non current type!");

    typedef typename embedded_type<TType>::ref_type retType;

    //ok, get it!
    embedded_type<TType> *_data = reinterpret_cast<embedded_type<TType> *>(const_cast<data_type *>(&m_storage));

    ASSERT(_data, "Accessing null data!");

    return mpl::forward<retType>(_data->get());
}

template<typename ... Types>
template<typename TType>
TType variant_impl<Types...>::extract()
{
    // do a local copy and forward it
    typedef typename embedded_type<TType>::rref_type retType;
    typedef typename embedded_type<TType>::internal_type rawType;

    //ok, get it!
    embedded_type<TType> *_data = reinterpret_cast<embedded_type<TType> *>(const_cast<data_type *>(&m_storage));

    ASSERT(_data, "Accessing null data!");

    rawType res = _data->extract();

    destroy();

    return mpl::forward<retType>(res);
}
template<typename ... Types>
bool variant_impl<Types...>::empty() const
{
    return m_currentType == _numTypes;
}
template<typename ... Types>
template<typename TType>
bool variant_impl<Types...>::is() const
{
    static_assert(mpl::is_among_types<TType, Types...>::value, "Non present type in variant");

    static const size_t isPos = mpl::nth_pos_of_type<TType, Types...>::value;

    return m_currentType == isPos;
}
template<typename ... Types>
template<size_t Pos>
typename embedded_type<typename mpl::nth_type_of<Pos,Types...>::type>::ref_type variant_impl<Types...>::get() const
{
    ASSERT(m_currentType == Pos, "Accessing non current type!");

    typedef embedded_type<typename mpl::nth_type_of<Pos,Types...>::type> embeddedType;
    typedef typename embeddedType::ref_type retType;

    //ok, get it!
    embeddedType* _data = reinterpret_cast<embeddedType*>(const_cast<data_type *>(&m_storage));

    ASSERT(_data, "Accessing null data!");

    return mpl::forward<retType>(_data->get());
}
template<typename ... Types>
template<size_t Pos>
typename mpl::nth_type_of<Pos,Types...>::type variant_impl<Types...>::extract()
{
    // do a local copy and forward it
    typedef embedded_type<typename mpl::nth_type_of<Pos,Types...>::type> embeddedType;
    typedef typename embeddedType::rref_type retType;
    typedef typename embeddedType::internal_type rawType;

    //ok, get it!
    embeddedType* _data = reinterpret_cast<embeddedType*>(const_cast<data_type *>(&m_storage));

    ASSERT(_data, "Accessing null data!");

    rawType res = _data->extract();

    destroy();

    return mpl::forward<retType>(res);
}
template<typename ... Types>
template<size_t Pos>
bool variant_impl<Types...>::is() const
{
    return m_currentType == Pos;
}
template<typename ... Types>
char variant_impl<Types...>::which() const
{
    return m_currentType;
}

template<typename ... Types>
void variant_impl<Types...>::reset()
{
    destroy();

    return;
}

template<typename ... Types>
void variant_impl<Types...>::swap(variant_impl<Types...>& other)
{
    if (m_currentType < _numTypes && other.m_currentType < _numTypes)
    {
        //as in copy construction case, just check types are the same or not
        if (m_currentType == other.m_currentType)
        {
            swaper_visitor<variant_impl<Types...>,Types...> letsSwap(other, *this);

            CREATE_INNER_VISITOR(letsSwap,Types);
            CALL_INNER_VISITOR(letsSwap,*this);
        }
        else
        {
            //mmm, we will have to reconstruct types (at least, do it with move semantics in case we may save some allocations)

            //construction of tmp
            variant_impl<Types...> tmp;
            constructor_visitor<Types...> ctr(&tmp.m_storage);
            tmp.m_currentType = m_currentType;
            CREATE_INNER_VISITOR(ctr,Types);
            CALL_INNER_VISITOR(ctr,*this);

            //reconstruction of us
            *this = other;

            //reconstruction of other
            other = tmp;
        }
    }
    else if (m_currentType < _numTypes)
    {
        //construct us with other data
        constructor_visitor<Types...> ctr(&(other.m_storage));
        CREATE_INNER_VISITOR(ctr,Types);
        CALL_INNER_VISITOR(ctr,*this);
    }
    else if (other.m_currentType < _numTypes)
    {
        //construct other with our data
        constructor_visitor<Types...> ctr(&m_storage);
        CREATE_INNER_VISITOR(ctr,Types);
        CALL_INNER_VISITOR(ctr,other);
    }

    return;
}
template<typename ... Types>
template<typename Visitor>
typename Visitor::result_type variant_impl<Types...>::apply_visitor(const Visitor& visitor)
{
    typedef typename mpl::create_range_rank<0,mpl::get_num_types<Types...>::value>::type range_seq;

    return variant_visitor_invoker<Visitor, Types...>::template invoke(range_seq{},const_cast<Visitor&>(visitor),*this);
}
template<typename ... Types>
template<typename Visitor>
typename Visitor::result_type variant_impl<Types...>::apply_visitor(const Visitor& visitor) const
{
    typedef typename mpl::create_range_rank<0,mpl::get_num_types<Types...>::value>::type range_seq;

    return variant_visitor_invoker<Visitor, Types...>::template invoke(range_seq{},visitor,*this);
}

}
}
}
