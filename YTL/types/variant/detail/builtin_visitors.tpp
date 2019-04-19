
namespace yame
{
namespace ytl
{
namespace detail
{

template<typename ... Types>
template<typename Type>
template<typename TType>
void constructor_visitor<Types...>::_constructor<Type>::construct(void* address, TType&& val)
{
    static_assert(mpl::is_among_types<Type, Types...>::value, "Constructing type non present in variant types!");

    new(address)embedded_type<Type>(mpl::forward<TType>(val));

    return;
}
template<typename ... Types>
constructor_visitor<Types...>::constructor_visitor(void* address)
: m_address(address)
{
    ASSERT(m_address, "Providing null address to visitor");
}
template<typename ... Types>
template<size_t _pos, typename Type>
void constructor_visitor<Types...>::construct(void* address, Type&& val)
{
    static_assert(_pos >= 0 && _pos < mpl::get_num_types<Types...>::value, "Type out of bounds!");

    typedef typename mpl::nth_type_of<_pos, Types...>::type TType;

    _constructor<TType>::template construct<Type>(address, mpl::forward<Type>(val));

    return;
}
template<typename ... Types>
template<typename Type>
void constructor_visitor<Types...>::operator()(Type&& other)
{
    static_assert(mpl::is_among_types<Type, Types...>::value, "Not present type!");

    new(m_address)embedded_type<Type>(mpl::forward<Type>(other));

    return;
}

template<typename ... Types>
destructor_visitor<Types...>::destructor_visitor(void *address)
: m_address(address)
{
    ASSERT(m_address, "Providing null address to visitor");
}
template<typename ... Types>
template<typename Type>
void destructor_visitor<Types...>::operator()(Type&&)
{
    static_assert(mpl::is_among_types<Type, Types...>::value, "Not present type!");

    embedded_type<Type>::destroy(m_address);

    return;
}
template<typename ... Types>
template<size_t _pos>
void destructor_visitor<Types...>::destroy()
{
    static_assert(_pos >= 0 && _pos < mpl::get_num_types<Types...>::value, "Type out of bounds!");

    typedef typename mpl::nth_type_of<_pos,Types...>::type Type;

    embedded_type<Type>::destroy(m_address);

    return;
}

template<typename ... Types>
template<typename Type>
template<typename TType>
void assigner_visitor<Types...>::_assigner<Type>::assign(void* address, TType&& val)
{
    static_assert(mpl::is_among_types<Type, Types...>::value, "Assigning type non present in variant types!");
    //static_assert(jtl::mpl::detail::is_among_constructible_types<TType, Types...>::value, "Cannot assign any variant types with forwarded value!");

    embedded_type<Type>::assign(address, mpl::forward<TType>(val));

    return;
}
template<typename ... Types>
assigner_visitor<Types...>::assigner_visitor(void* address)
: m_address(address)
{
}
template<typename ... Types>
template<size_t _pos, typename Type>
void assigner_visitor<Types...>::assign(void* address, Type&& val)
{
    typedef typename mpl::nth_type_of<_pos, Types...>::type TType;

    _assigner<TType>::template assign<Type>(address, mpl::forward<Type>(val));

    return;
}

template<typename ... Types>
template<typename Type>
void assigner_visitor<Types...>::operator()(Type&& other)
{
    static_assert(mpl::is_among_types<Type, Types...>::value, "Not present type!");

    embedded_type<Type>::assign(m_address, mpl::forward<Type>(other));

    return;
}

template<typename retType, typename ... Types>
typename embedded_type<retType>::ref_type val_retriever_visitor<retType,Types...>::operator()(typename embedded_type<retType>::ref_type val)
{
    typedef typename embedded_type<retType>::ref_type ref_type;

    return mpl::forward<ref_type>(val);
}
template<typename retType, typename ... Types>
template<typename Type>
typename embedded_type<retType>::ref_type val_retriever_visitor<retType,Types...>::operator()(Type&& val, rawType* _foo)
{
    ASSERT(false, "You shouldnt reach this point!");

    return mpl::forward<typename embedded_type<retType>::ref_type>(*_foo);
}

template<typename Variant, typename ... Types>
swaper_visitor<Variant,Types...>::swaper_visitor(Variant& _thisVariant, Variant& _otherVariant)
: m_thisVariant(_thisVariant)
, m_otherVariant(_otherVariant)
{
}
template<typename Variant, typename ... Types>
template<typename Type>
void swaper_visitor<Variant,Types...>::operator()(Type&& otherVal)
{
    static_assert(mpl::is_among_types<Type, Types...>::value, "Not present type!");

    typedef typename embedded_type<Type>::ref_type ref_type;

    val_retriever_visitor<Types...,ref_type> getter;

    //this reference here is ok by reference collapsing
    CREATE_INNER_VISITOR(getter,Types);
    ref_type thisVal = CALL_INNER_VISITOR(getter,m_thisVariant);

    embedded_type<Type>::swap(&m_thisVariant.m_storage, mpl::forward<ref_type>(thisVal), &m_otherVariant.m_storage, mpl::forward<Type>(otherVal));

    return;
}

template<typename Variant, typename ... Types>
comparison_visitor<Variant,Types...>::comparison_visitor(const Variant& _variant)
: static_visitor<bool>()
, m_variant(_variant)
{
}
template<typename Variant, typename ... Types>
template<typename Type>
bool comparison_visitor<Variant,Types...>::operator()(Type&& otherVal)
{
    typedef typename embedded_type<Type>::ref_type ref_type;

    val_retriever_visitor<ref_type> getter;

    //this reference here is ok by reference collapsing
    CREATE_INNER_VISITOR(getter,Types);
    ref_type thisVal = CALL_INNER_VISITOR(getter,m_variant);

    return thisVal == mpl::forward<Type>(otherVal);
}

}
}
}
