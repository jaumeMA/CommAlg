#pragma once

#include "YTL/types/smartPtr/lent_ref.h"
#include "YTL/types/smartPtr/unique_ref.h"
#include "YTL/types/smartPtr/shared_ref.h"

namespace yame
{
namespace ytl
{

template<typename T>
inline lent_ref<T> promote_to_ref(const lent_ptr<T>& other);
template<typename T>
inline unique_ref<T> promote_to_ref(unique_ptr<T>&& other);
template<typename T>
inline shared_ref<T> promote_to_ref(const shared_ptr<T>& other);

template<typename TT, typename T>
inline lent_ptr<TT> dynamic_lent_cast(const lent_ptr<T>& other);
#ifdef LENT_WITH_LOGIC
template<typename TT, typename T>
inline lent_ptr<TT> dynamic_lent_cast(const lent_ref<T>& other);
#endif
template<typename TT, typename T>
inline unique_ptr<TT> dynamic_unique_cast(unique_ptr<T>&& i_uniqueRef);
template<typename TT, typename T>
inline unique_ptr<TT> dynamic_unique_cast(unique_ref<T>&& i_uniqueRef);
template<typename TT, typename T>
inline shared_ptr<TT> dynamic_shared_cast(const shared_ptr<T>& i_sharedPtr);
template<typename TT, typename T>
inline shared_ptr<TT> dynamic_shared_cast(const shared_ref<T>& i_sharedRef);

template<typename TT, typename T>
inline lent_ptr<TT> static_lent_cast(const lent_ptr<T>& other);
#ifdef LENT_WITH_LOGIC
template<typename TT, typename T>
inline lent_ref<TT> static_lent_cast(const lent_ref<T>& other);
#endif
template<typename TT, typename T>
inline unique_ptr<TT> static_unique_cast(unique_ptr<T>&& other);
template<typename TT, typename T>
inline unique_ref<TT> static_unique_cast(unique_ref<T>&& other);
template<typename TT, typename T>
inline shared_ptr<TT> static_shared_cast(const shared_ptr<T>& other);
template<typename TT, typename T>
inline shared_ref<TT> static_shared_cast(const shared_ref<T>& other);

template<typename T>
inline lent_ptr<T> const_lent_cast(const lent_ptr<const T>& other);
#ifdef LENT_WITH_LOGIC
template<typename T>
inline lent_ref<T> const_lent_cast(const lent_ref<const T>& other);
#endif
template<typename T>
inline unique_ptr<T> const_unique_cast(unique_ptr<const T>&& other);
template<typename T>
inline unique_ref<T> const_unique_cast(unique_ref<const T>&& other);
template<typename T>
inline shared_ptr<T> const_shared_cast(const shared_ptr<const T>& other);
template<typename T>
inline shared_ref<T> const_shared_cast(const shared_ref<const T>& other);

template<typename T>
inline lent_ref<T> lend(T& other, const typename T::lendable_tag* _foo = NULL);
template<typename T>
inline lent_ptr<T> lend(unique_ptr<T>& i_uniquePtr);
template<typename T>
inline lent_ref<T> lend(unique_ref<T>& i_uniqueRef);
template<typename T>
inline lent_ptr<T> lend(shared_ptr<T>& i_sharedPtr);
template<typename T>
inline lent_ref<T> lend(shared_ref<T>& i_sharedRef);

template<typename T, typename ... Args>
inline shared_ref<T> make_shared(Args&& ... i_args);
template<typename T, typename ... Args>
inline unique_ref<T> make_unique(Args&& ... i_args);

}
}

#include "YTL/types/smartPtr/detail/smart_ptr.tpp"
