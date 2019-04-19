
#include "Utils/rtti/TypeAccess.h"

namespace yame
{
namespace rtti
{

template<typename T, typename Visitor>
void visit_members(ytl::unique_ref<T>& i_uniqueRef, Visitor& i_visitor)
{
    return rtti::visit_members(i_uniqueRef.getData(),i_visitor);
}
template<typename T, typename Visitor>
void visit_members(ytl::unique_ref<T>& i_uniqueRef, const Visitor& i_visitor)
{
    return rtti::visit_members(i_uniqueRef.getData(),i_visitor);
}
template<typename T, typename TT>
T& access(ytl::unique_ref<TT>& i_smartPtr, const yame::container::string& i_memberName)
{
    return rtti::access<T>(i_smartPtr.getData(),i_memberName);
}
template<typename T, typename TT>
const T& access(const ytl::unique_ref<TT>& i_smartPtr, const yame::container::string& i_memberName)
{
    return rtti::access<T>(i_smartPtr.getData(),i_memberName);
}
template<typename Return, typename T, typename ... Args>
Return execute(ytl::unique_ref<T>& i_smartPtr, const yame::container::string& i_memberName, Args&& ... i_args)
{
    return rtti::execute<Return>(i_smartPtr.getData(),i_memberName,mpl::forward<Args>(i_args)...);
}
template<typename Return, typename T, typename ... Args>
Return execute(const ytl::unique_ref<T>& i_smartPtr, const yame::container::string& i_memberName, Args&& ... i_args)
{
    return rtti::execute<Return>(i_smartPtr.getData(),i_memberName,mpl::forward<Args>(i_args)...);
}

#ifdef LENT_WITH_LOGIC

template<typename T, typename Visitor>
void visit_members(ytl::lent_ref<T>& i_lentRef, Visitor& i_visitor)
{
    return rtti::visit_members(i_lentRef.getData(),i_visitor);
}
template<typename T, typename Visitor>
void visit_members(ytl::lent_ref<T>& i_lentRef, const Visitor& i_visitor)
{
    return rtti::visit_members(i_lentRef.getData(),i_visitor);
}
template<typename T, typename TT>
T& access(ytl::lent_ref<TT>& i_smartPtr, const yame::container::string& i_memberName)
{
    return rtti::access<T>(i_smartPtr.getData(),i_memberName);
}
template<typename T, typename TT>
const T& access(const ytl::lent_ref<TT>& i_smartPtr, const yame::container::string& i_memberName)
{
    return rtti::access<T>(i_smartPtr.getData(),i_memberName);
}
template<typename Return, typename T, typename ... Args>
Return execute(ytl::lent_ref<T>& i_smartPtr, const yame::container::string& i_memberName, Args&& ... i_args)
{
    return rtti::execute<Return>(i_smartPtr.getData(),i_memberName,mpl::forward<Args>(i_args)...);
}
template<typename Return, typename T, typename ... Args>
Return execute(const ytl::lent_ref<T>& i_smartPtr, const yame::container::string& i_memberName, Args&& ... i_args)
{
    return rtti::execute<Return>(i_smartPtr.getData(),i_memberName,mpl::forward<Args>(i_args)...);
}

#endif

template<typename T, typename Visitor>
void visit_members(ytl::shared_ref<T>& i_sharedRef, Visitor& i_visitor)
{
    return rtti::visit_members(i_sharedRef.getData(),i_visitor);
}
template<typename T, typename Visitor>
void visit_members(ytl::shared_ref<T>& i_sharedRef, const Visitor& i_visitor)
{
    return rtti::visit_members(i_sharedRef.getData(),i_visitor);
}
template<typename T, typename TT>
T& access(ytl::shared_ref<TT>& i_smartPtr, const yame::container::string& i_memberName)
{
    return rtti::access<T>(i_smartPtr.getData(),i_memberName);
}
template<typename T, typename TT>
const T& access(const ytl::shared_ref<TT>& i_smartPtr, const yame::container::string& i_memberName)
{
    return rtti::access<T>(i_smartPtr.getData(),i_memberName);
}
template<typename Return, typename T, typename ... Args>
Return execute(ytl::shared_ref<T>& i_smartPtr, const yame::container::string& i_memberName, Args&& ... i_args)
{
    return rtti::execute<Return>(i_smartPtr.getData(),i_memberName,mpl::forward<Args>(i_args)...);
}
template<typename Return, typename T, typename ... Args>
Return execute(const ytl::shared_ref<T>& i_smartPtr, const yame::container::string& i_memberName, Args&& ... i_args)
{
    return rtti::execute<Return>(i_smartPtr.getData(),i_memberName,mpl::forward<Args>(i_args)...);
}

}
}
