
namespace yame
{
namespace ytl
{
namespace detail
{

template<typename visitor, typename ... Types>
template<size_t TypeIndex>
typename visitor::result_type variant_visitor_invoker<visitor, Types...>::inner_invoke(visitor& _visitor, const variant_impl<Types...>& var)
{
    typedef typename mpl::nth_type_of<TypeIndex,Types...>::type CurrType;
    typedef typename embedded_type<CurrType>::ref_type ref_type;

    return _visitor.operator()(std::forward<ref_type>(var.template get<TypeIndex>()));
}
template<typename visitor, typename ... Types>
template<size_t TypeIndex>
typename visitor::result_type variant_visitor_invoker<visitor, Types...>::inner_invoke(visitor& _visitor, variant_impl<Types...>& var)
{
    typedef typename mpl::nth_type_of<TypeIndex,Types...>::type CurrType;
    typedef typename embedded_type<CurrType>::ref_type ref_type;

    return _visitor.operator()(std::forward<ref_type>(var.template get<TypeIndex>()));
}
template<typename visitor, typename ... Types>
template<size_t TypeIndex>
typename visitor::result_type variant_visitor_invoker<visitor, Types...>::outer_invoke(visitor& _visitor, const variant_impl<Types...>& var)
{
    typedef typename mpl::nth_type_of<TypeIndex,Types...>::type CurrType;
    typedef typename embedded_type<CurrType>::ref_type ref_type;

    return _visitor.operator()(std::forward<ref_type>(var.template get<TypeIndex>()));
}
template<typename visitor, typename ... Types>
template<size_t TypeIndex>
typename visitor::result_type variant_visitor_invoker<visitor, Types...>::outer_invoke(visitor& _visitor, variant_impl<Types...>& var)
{
    typedef typename mpl::nth_type_of<TypeIndex,Types...>::type CurrType;
    typedef typename embedded_type<CurrType>::ref_type ref_type;

    return _visitor.operator()(std::forward<ref_type>(var.template get<TypeIndex>()));
}

template<typename visitor, typename ... Types>
template<int ... TypeIndexs>
typename visitor::result_type variant_visitor_invoker<visitor, Types...>::invoke(const mpl::sequence<TypeIndexs...>&, const visitor& _visitor, const variant_impl<Types...>& var)
{
    typedef result_type(*funcType)(visitor&, const variant_impl<Types...>&);

    static const funcType funcTable[_numTypes] = { &variant_visitor_invoker<visitor, Types...>::outer_invoke<TypeIndexs> ... };

    return (*funcTable[var.m_currentType])(const_cast<visitor&>(_visitor), var);
}
template<typename visitor, typename ... Types>
template<int ... TypeIndexs>
typename visitor::result_type variant_visitor_invoker<visitor, Types...>::invoke(const mpl::sequence<TypeIndexs...>&, const visitor& _visitor, variant_impl<Types...>& var)
{
    typedef result_type(*funcType)(visitor&, variant_impl<Types...>&);

    static const funcType funcTable[_numTypes] = { &variant_visitor_invoker<visitor, Types...>::outer_invoke<TypeIndexs> ... };

    return (*funcTable[var.m_currentType])(const_cast<visitor&>(_visitor), var);
}

}
}
}
