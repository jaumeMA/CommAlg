#pragma once

#include "YTL/types/variant/static_visitor.h"

namespace yame
{
namespace ytl
{
namespace detail
{

template<typename ... Types>
struct constructor_visitor : public static_visitor<void>
{
    typedef constructor_visitor t_visitor;

    template<typename Type>
    struct _constructor;

    template<typename Type>
    struct _constructor
    {
        template<typename TType>
        static void construct(void* address, TType&& val);
    };

    constructor_visitor(void *address = NULL);

    template<size_t _pos, typename Type>
    static void construct(void* address, Type&& val);

    template<typename Type>
    void operator()(Type&& visit);

private:
    void* m_address;
};

template<typename ... Types>
struct destructor_visitor : public static_visitor<void>
{
    typedef destructor_visitor t_visitor;

    destructor_visitor(void *address = NULL);

    template<typename Type>
    void operator()(Type&&);

    template<size_t _pos>
    void destroy();

private:
    void* m_address;
};

template<typename ... Types>
struct assigner_visitor : public static_visitor<void>
{
    typedef assigner_visitor t_visitor;

    template<typename Type>
    struct _assigner
    {
        template<typename TType>
        static void assign(void* address, TType&& val);
    };

    assigner_visitor(void *address = nullptr);

    template<size_t _pos, typename Type>
    static void assign(void* address, Type&& val);

    template<typename Type>
    void operator()(Type&& visit);

private:
    void* m_address;
};

template<typename retType, typename ... Types>
struct val_retriever_visitor : public static_visitor<typename embedded_type<retType>::ref_type>
{
    typedef val_retriever_visitor t_visitor;
    typedef typename mpl::drop_constness<typename embedded_type<retType>::internal_type>::type rawType;

    typename embedded_type<retType>::ref_type operator()(typename embedded_type<retType>::ref_type val);

    //for the rest of unsused types
    template<typename Type>
    typename embedded_type<retType>::ref_type operator()(Type&& val, rawType* _foo = 0);
};

template<typename Variant, typename ... Types>
struct swaper_visitor : public static_visitor<void>
{
    typedef swaper_visitor t_visitor;

    swaper_visitor(Variant& _thisVariant, Variant& _otherVariant);

    template<typename Type>
    void operator()(Type&& otherVal);

private:
    Variant& m_thisVariant;
    Variant& m_otherVariant;
};

template<typename Variant, typename ... Types>
struct comparison_visitor : public static_visitor<bool>
{
    typedef comparison_visitor t_visitor;

    comparison_visitor(const Variant& _variant);

    template<typename Type>
    bool operator()(Type&& otherVal);

private:
    const Variant& m_variant;
};

}
}
}

#include "YTL/types/variant/detail/builtin_visitors.tpp"
