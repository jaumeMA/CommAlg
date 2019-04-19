
#include "YTL/container/cParameterPackIterable.h"

namespace yame
{
namespace rtti
{
namespace detail
{

inline TypeId _getNextTypeId()
{
    static TypeId s_currTypeId = 0;

    return s_currTypeId++;
}
template<typename T>
TypeId getNextTypeId()
{
    static TypeId s_currTypeId = _getNextTypeId();

    return s_currTypeId++;
}
template<typename T, typename TT>
const TypeInfo* __get_rtti_type_info(const T*,const TT&)
{
    static const TypeInfo builtinTypeInfo = TypeInfo(yame::container::string(typeid(T).name()),getNextTypeId<T>(), {}, {});

    return &builtinTypeInfo;
}
template<typename T>
const TypeInfo* _getTypeInfo(typename T::rtti_members_t*)
{
    return __get_rtti_type_info(static_cast<const T*>(NULL),__get_rtti_members_type_info(static_cast<const T*>(NULL)));
}
template<typename T>
const TypeInfo* _getTypeInfo(...)
{
    typedef yame::container::cArray<yame::container::cPair<yame::container::string,const yame::rtti::TypeInfo*>> __rtti_members;
    return __get_rtti_type_info(static_cast<const T*>(NULL),__rtti_members{});
}

template<typename T>
member_address_visitor<T>::member_address_visitor(const container::string& i_memberName)
: m_memberName(i_memberName)
{
}
template<typename T>
template<typename TT>
size_t T::* member_address_visitor<T>::operator()(const container::cPair<container::string,TT T::*>& i_value) const
{
    if(m_memberName == i_value.first)
    {
        return reinterpret_cast<size_t T::*>(i_value.second);
    }
    else
    {
        return 0;
    }
};

template<typename T, typename Visitor>
member_pass_by_reference_visitor<T,Visitor>::member_pass_by_reference_visitor(T& i_currObj, const Visitor& i_nestedVisitor)
: m_currObject(i_currObj)
, m_nestedVisitor(i_nestedVisitor)
{
}
template<typename T, typename Visitor>
template<typename TT>
typename Visitor::result_type member_pass_by_reference_visitor<T,Visitor>::operator()(const container::cPair<container::string,TT T::*>& i_value) const
{
    return m_nestedVisitor.operator()(container::make_pair<container::string,typename mpl::add_reference<TT>::type>(i_value.first,m_currObject.*i_value.second));
}

}

template<typename T, typename Visitor>
void visit_members(T* i_ptr, Visitor& i_visitor)
{
    if(i_ptr)
    {
        detail::member_pass_by_reference_visitor<T,Visitor> memberRefVisitor(*i_ptr,i_visitor);
        auto memberIterable = container::make_iterable(__get_rtti_members_pack(static_cast<const T*>(NULL)));
        typedef decltype(memberIterable) member_pack_iterable;

        typename member_pack_iterable::iterator_type itMember = memberIterable.begin();
        for(;itMember!=memberIterable.end();++itMember)
        {
            typename member_pack_iterable::value_type currValue = *itMember;

            currValue.apply_visitor(memberRefVisitor);
        }
    }
}
template<typename T, typename Visitor>
void visit_members(T* i_ptr, const Visitor& i_visitor)
{
    if(i_ptr)
    {
        detail::member_pass_by_reference_visitor<T,const Visitor> memberRefVisitor(*i_ptr,i_visitor);
        auto memberIterable = container::make_iterable(__get_rtti_members_pack(static_cast<const T*>(NULL)));
        typedef decltype(memberIterable) member_pack_iterable;

        typename member_pack_iterable::const_iterator_type itMember = memberIterable.cbegin();
        for(;itMember!=memberIterable.cend();++itMember)
        {
            typename member_pack_iterable::value_type currValue = *itMember;

            currValue.apply_visitor(memberRefVisitor);
        }
    }
}

template<typename TT, typename T>
TT& access(T* i_ptr, const yame::container::string& i_memberName)
{
    auto memberIterable = container::make_iterable(__get_rtti_members_pack(static_cast<const T*>(NULL)));
    typedef decltype(memberIterable) member_pack_iterable;

    typename member_pack_iterable::iterator_type itMember = memberIterable.begin();
    detail::member_address_visitor<T> memberVisitor(i_memberName);

    for(;itMember!=memberIterable.end();++itMember)
    {
        typename member_pack_iterable::value_type currValue = *itMember;

        if(size_t T::* memberAddress = currValue.apply_visitor(memberVisitor))
        {
            return i_ptr->*reinterpret_cast<TT T::*>(memberAddress);
        }
    }

    return *reinterpret_cast<TT*>(0xDEAD);
}
template<typename TT, typename T>
const TT& access(const T* i_ptr, const yame::container::string& i_memberName)
{
    auto memberIterable = container::make_iterable(__get_rtti_members_pack(static_cast<const T*>(NULL)));
    typedef decltype(memberIterable) member_pack_iterable;

    typename member_pack_iterable::const_iterator_type itMember = memberIterable.cbegin();
    detail::member_address_visitor<T> memberVisitor(i_memberName);

    for(;itMember!=memberIterable.cend();++itMember)
    {
        typename member_pack_iterable::const_value_type currValue = *itMember;

        if(size_t T::* memberAddress = currValue.apply_visitor(memberVisitor))
        {
            return i_ptr->*reinterpret_cast<TT T::*>(memberAddress);
        }
    }

    return *reinterpret_cast<const TT*>(0xDEAD);
}
template<typename Return, typename T, typename ... Args>
Return execute(T* i_ptr, const yame::container::string& i_methodName, Args&& ... i_args)
{
    typedef Return (T::*rtti_func_pointer_type)(Args...); \

    if(rtti_func_pointer_type methodPtr = reinterpret_cast<rtti_func_pointer_type>(__get_rtti_method_address(static_cast<const T*>(NULL),i_methodName)))
    {
        return (i_ptr->*methodPtr)(mpl::forward<Args>(i_args)...);
    }
    else
    {
        return *reinterpret_cast<Return*>(0xDEAD);
    }
}
template<typename Return, typename T, typename ... Args>
Return execute(const T* i_ptr, const yame::container::string& i_methodName, Args&& ... i_args)
{
    typedef Return (T::*const rtti_func_pointer_type)(Args...); \

    if(rtti_func_pointer_type methodPtr = reinterpret_cast<rtti_func_pointer_type>(__get_rtti_method_address(static_cast<const T*>(NULL),i_methodName)))
    {
        return (i_ptr->*methodPtr)(mpl::forward<Args>(i_args)...);
    }
    else
    {
        return *reinterpret_cast<Return*>(0xDEAD);
    }
}
template<typename T>
TypeInfo getTypeInfo()
{
    static const TypeInfo* res = detail::_getTypeInfo<T>(NULL);

    return *res;
}

}
}

