#pragma once

#include "Utils/rtti/TypeInfo.h"
#include <typeinfo>
#include "YTL/types/variant/static_visitor.h"

//macro for type pointers
#define __RTTI_EXPAND_METHOD_POINTER_TYPE(_MEMBER) \
    decltype(&_rtti_method_class::_MEMBER)
#define _RTTI_EXPAND_METHOD_POINTER_TYPE_TWOORMORE(_MEMBER) \
    __RTTI_EXPAND_METHOD_POINTER_TYPE(_MEMBER),
#define _RTTI_EXPAND_METHOD_POINTER_TYPE_ONE(_MEMBER) \
    __RTTI_EXPAND_METHOD_POINTER_TYPE(_MEMBER)
#define _RTTI_EXPAND_METHOD_POINTER_TYPE_(_QUANT,_MEMBER) \
    _RTTI_EXPAND_METHOD_POINTER_TYPE_##_QUANT(_MEMBER)
#define _RTTI_EXPAND_METHOD_POINTER_TYPE(_QUANT,_MEMBER) \
    _RTTI_EXPAND_METHOD_POINTER_TYPE_(_QUANT,_MEMBER)
#define RTTI_EXPAND_METHOD_POINTER_TYPE(_INDEX,_MEMBER) \
    _RTTI_EXPAND_METHOD_POINTER_TYPE(QUANTITY(_INDEX),_MEMBER)

//macro for name x types decl
#define __RTTI_EXPAND_MEMBER_NAME_TYPE_DECL(_MEMBER) \
    yame::container::cPair<yame::container::string,decltype(&_rtti_member_class::_MEMBER)>
#define _RTTI_EXPAND_MEMBER_NAME_TYPE_DECL_TWOORMORE(_MEMBER) \
    __RTTI_EXPAND_MEMBER_NAME_TYPE_DECL(_MEMBER),
#define _RTTI_EXPAND_MEMBER_NAME_TYPE_DECL_ONE(_MEMBER) \
    __RTTI_EXPAND_MEMBER_NAME_TYPE_DECL(_MEMBER)
#define _RTTI_EXPAND_MEMBER_NAME_TYPE_DECL_(_QUANT,_MEMBER) \
    _RTTI_EXPAND_MEMBER_NAME_TYPE_DECL_##_QUANT(_MEMBER)
#define _RTTI_EXPAND_MEMBER_NAME_TYPE_DECL(_QUANT,_MEMBER) \
    _RTTI_EXPAND_MEMBER_NAME_TYPE_DECL_(_QUANT,_MEMBER)
#define RTTI_EXPAND_MEMBER_NAME_TYPE_DECL(_INDEX,_MEMBER) \
    _RTTI_EXPAND_MEMBER_NAME_TYPE_DECL(QUANTITY(_INDEX),_MEMBER)

//macro for name x types impl
#define __RTTI_EXPAND_MEMBER_NAME_TYPE_IMPL(_MEMBER) \
    yame::container::make_pair(yame::container::string(#_MEMBER),&_rtti_member_class::_MEMBER)
#define _RTTI_EXPAND_MEMBER_NAME_TYPE_IMPL_TWOORMORE(_MEMBER) \
    __RTTI_EXPAND_MEMBER_NAME_TYPE_IMPL(_MEMBER),
#define _RTTI_EXPAND_MEMBER_NAME_TYPE_IMPL_ONE(_MEMBER) \
    __RTTI_EXPAND_MEMBER_NAME_TYPE_IMPL(_MEMBER)
#define _RTTI_EXPAND_MEMBER_NAME_TYPE_IMPL_(_QUANT,_MEMBER) \
    _RTTI_EXPAND_MEMBER_NAME_TYPE_IMPL_##_QUANT(_MEMBER)
#define _RTTI_EXPAND_MEMBER_NAME_TYPE_IMPL(_QUANT,_MEMBER) \
    _RTTI_EXPAND_MEMBER_NAME_TYPE_IMPL_(_QUANT,_MEMBER)
#define RTTI_EXPAND_MEMBER_NAME_TYPE_IMPL(_INDEX,_MEMBER) \
    _RTTI_EXPAND_MEMBER_NAME_TYPE_IMPL(QUANTITY(_INDEX),_MEMBER)

//macro for member name x typeinfo
#define ___RTTI_EXPAND_MEMBER_TYPE_INFO(_MEMBER) \
    yame::container::make_pair(yame::container::string(#_MEMBER),yame::rtti::detail::_getTypeInfo<decltype(_rtti_member_class::_MEMBER)>(NULL))
#define __RTTI_EXPAND_MEMBER_TYPE_INFO(_MEMBER) \
    ___RTTI_EXPAND_MEMBER_TYPE_INFO(_MEMBER)
#define _RTTI_EXPAND_MEMBER_TYPE_INFO_TWOORMORE(_MEMBER) \
    __RTTI_EXPAND_MEMBER_TYPE_INFO(_MEMBER),
#define _RTTI_EXPAND_MEMBER_TYPE_INFO_ONE(_MEMBER) \
    __RTTI_EXPAND_MEMBER_TYPE_INFO(_MEMBER)
#define _RTTI_EXPAND_MEMBER_TYPE_INFO_(_QUANT,_MEMBER) \
    _RTTI_EXPAND_MEMBER_TYPE_INFO_##_QUANT(_MEMBER)
#define _RTTI_EXPAND_MEMBER_TYPE_INFO(_QUANT,_MEMBER) \
    _RTTI_EXPAND_MEMBER_TYPE_INFO_(_QUANT,_MEMBER)
#define RTTI_EXPAND_MEMBER_TYPE_INFO(_INDEX,_MEMBER) \
    _RTTI_EXPAND_MEMBER_TYPE_INFO(QUANTITY(_INDEX),_MEMBER)

//macro for names
#define ___RTTI_EXPAND_MEMBER_NAME(_MEMBER) \
    #_MEMBER
#define __RTTI_EXPAND_MEMBER_NAME(_MEMBER) \
    ___RTTI_EXPAND_MEMBER_NAME(_MEMBER)
#define _RTTI_EXPAND_MEMBER_NAME_TWOORMORE(_MEMBER) \
    __RTTI_EXPAND_MEMBER_NAME(_MEMBER),
#define _RTTI_EXPAND_MEMBER_NAME_ONE(_MEMBER) \
    __RTTI_EXPAND_MEMBER_NAME(_MEMBER)
#define _RTTI_EXPAND_MEMBER_NAME_(_QUANT,_MEMBER) \
    _RTTI_EXPAND_MEMBER_NAME_##_QUANT(_MEMBER)
#define _RTTI_EXPAND_MEMBER_NAME(_QUANT,_MEMBER) \
    _RTTI_EXPAND_MEMBER_NAME_(_QUANT,_MEMBER)
#define RTTI_EXPAND_MEMBER_NAME(_INDEX,_MEMBER) \
    _RTTI_EXPAND_MEMBER_NAME(QUANTITY(_INDEX),_MEMBER)

//macro for pair of method address
#define __RTTI_EXPAND_METHOD_ADDRESS(_MEMBER) \
    reinterpret_cast<void (_rtti_method_class::*)()>(&_rtti_method_class::_MEMBER)
#define _RTTI_EXPAND_METHOD_ADDRESS_TWOORMORE(_MEMBER) \
    __RTTI_EXPAND_METHOD_ADDRESS(_MEMBER),
#define _RTTI_EXPAND_METHOD_ADDRESS_ONE(_MEMBER) \
    __RTTI_EXPAND_METHOD_ADDRESS(_MEMBER)
#define _RTTI_EXPAND_METHOD_ADDRESS_(_QUANT, _MEMBER) \
    _RTTI_EXPAND_METHOD_ADDRESS_##_QUANT(_MEMBER)
#define _RTTI_EXPAND_METHOD_ADDRESS(_QUANT, _MEMBER) \
    _RTTI_EXPAND_METHOD_ADDRESS_(_QUANT, _MEMBER)
#define RTTI_EXPAND_METHOD_ADDRESS(_INDEX, _MEMBER) \
    _RTTI_EXPAND_METHOD_ADDRESS(QUANTITY(_INDEX),_MEMBER)

#define PUBLISH_RTTI_TYPE_MEMBERS(_TYPE,...) \
    typedef _TYPE _rtti_member_class; \
    typedef yame::container::parameter_pack<FOREACH(RTTI_EXPAND_MEMBER_NAME_TYPE_DECL,  __VA_ARGS__)> rtti_members_t; \
    friend const yame::rtti::TypeInfo* yame::rtti::detail::_getTypeInfo<_TYPE>(typename _TYPE::rtti_members_t*); \
    friend inline const yame::container::cArray<yame::container::cPair<yame::container::string,const yame::rtti::TypeInfo*>>& __get_rtti_members_type_info(const _TYPE*) \
    { \
        static const yame::container::cArray<yame::container::cPair<yame::container::string,const yame::rtti::TypeInfo*>> __rtti_member_type_info = { FOREACH(RTTI_EXPAND_MEMBER_TYPE_INFO, __VA_ARGS__ ) }; \
        \
        return __rtti_member_type_info; \
    } \
    friend inline rtti_members_t& __get_rtti_members_pack(const _TYPE*) \
    { \
       static rtti_members_t __rtti_members_pack = rtti_members_t(FOREACH(RTTI_EXPAND_MEMBER_NAME_TYPE_IMPL,  __VA_ARGS__)); \
       \
        return __rtti_members_pack; \
    } \

#define PUBLISH_RTTI_TYPE_METHODS(_TYPE,...) \
    typedef _TYPE _rtti_method_class; \
    typedef yame::container::parameter_pack<FOREACH(RTTI_EXPAND_METHOD_POINTER_TYPE,  __VA_ARGS__)> rtti_methods; \
    typedef void (_rtti_method_class::*rtti_agnostic_func_pointer_type)(); \
    friend inline size_t __get_rtti_method_pos(const _TYPE*, const yame::container::string& i_methodName) \
    { \
        static const size_t __rtti_num_method_types = yame::mpl::get_parameter_pack_num_types<_TYPE::rtti_methods>::value; \
        static const yame::container::string __rtti_method_names[__rtti_num_method_types] = { FOREACH(RTTI_EXPAND_MEMBER_NAME,__VA_ARGS__) }; \
        \
        for(size_t methodIndex=0;methodIndex<__rtti_num_method_types;++methodIndex) \
        { \
            if(i_methodName == __rtti_method_names[methodIndex]) \
            { \
                return methodIndex; \
            } \
        } \
        \
        return -1; \
    } \
    friend inline rtti_agnostic_func_pointer_type __get_rtti_method_address(const _TYPE* i_foo, const yame::container::string& i_methodName) \
    { \
        static rtti_agnostic_func_pointer_type rtti_methods[] = { FOREACH(RTTI_EXPAND_METHOD_ADDRESS,__VA_ARGS__)}; \
        \
        const size_t methodPos = __get_rtti_method_pos(i_foo,i_methodName); \
       \
        return (methodPos != -1) ? rtti_methods[methodPos] : NULL; \
    }

#define PUBLISH_RTTI_TYPE_INFO(_TYPE) \
    template<typename ... Bases> \
    friend inline const yame::rtti::TypeInfo* __get_rtti_##_TYPE##_info_deps(const _TYPE*, const yame::container::parameter_pack<Bases...>*, const yame::container::cArray<yame::container::cPair<yame::container::string,const yame::rtti::TypeInfo*>>& i_members) \
    { \
        static const yame::rtti::TypeInfo __rtti_type_info(#_TYPE,yame::rtti::detail::getNextTypeId<_TYPE>(),{yame::rtti::detail::_getTypeInfo<Bases>(NULL)...},i_members); \
        \
        return &__rtti_type_info; \
    } \
    friend inline const yame::rtti::TypeInfo* __get_rtti_type_info(const _TYPE* i_ptr, const yame::container::cArray<yame::container::cPair<yame::container::string,const yame::rtti::TypeInfo*>>& i_members) \
    { \
        static const yame::rtti::TypeInfo* __rtti_type_info = __get_rtti_##_TYPE##_info_deps(i_ptr,reinterpret_cast<const _TYPE::rtti_base*>(NULL),i_members); \
        \
        return __rtti_type_info; \
    }

namespace yame
{
namespace rtti
{
namespace detail
{

template<typename T, typename TT>
inline const TypeInfo* __get_rtti_type_info(const T*,const TT&);
template<typename T>
inline const TypeInfo* _getTypeInfo(typename T::rtti_members_t*);
template<typename T>
inline const TypeInfo* _getTypeInfo(...);

template<typename T>
class member_address_visitor : public ytl::static_visitor<size_t T::*>
{
public:
    member_address_visitor(const container::string& i_memberName);

    template<typename TT>
    size_t T::* operator()(const container::cPair<container::string,TT T::*>& i_value) const;

private:
    const container::string m_memberName;
};

template<typename T, typename Visitor>
class member_pass_by_reference_visitor : public ytl::static_visitor<typename Visitor::result_type>
{
public:
    member_pass_by_reference_visitor(T& i_currObj, const Visitor& i_nestedVisitor);

    template<typename TT>
    typename Visitor::result_type operator()(const container::cPair<container::string,TT T::*>& i_value) const;

private:
    T& m_currObject;
    const Visitor& m_nestedVisitor;
};

}

template<typename T, typename Visitor>
inline void visit_members(T* i_ptr, Visitor& i_visitor);
template<typename T, typename Visitor>
inline void visit_members(T* i_ptr, const Visitor& i_visitor);
template<typename TT, typename T>
inline TT& access(T* i_ptr, const yame::container::string& i_memberName);
template<typename TT, typename T>
inline const TT& access(const T* i_ptr, const yame::container::string& i_memberName);
template<typename Return, typename T, typename ... Args>
inline Return execute(T* i_ptr, const yame::container::string& i_methodName, Args&& ... i_args);
template<typename Return, typename T, typename ... Args>
inline Return execute(const T* i_ptr, const yame::container::string& i_methodName, Args&& ... i_args);
template<typename T>
inline TypeInfo getTypeInfo();

}
}

#include "Utils/rtti/detail/TypeAccess.tpp"
