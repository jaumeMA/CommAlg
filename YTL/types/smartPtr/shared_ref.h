#pragma once

#include "YTL/types/smartPtr/shared_ptr.h"

namespace yame
{
namespace ytl
{

template<typename T>
class shared_ref : public shared_ptr<T>
{
    template<typename TT>
    friend class shared_ptr;
    template<typename TT, typename ... Args>
    friend shared_ptr<TT> make_shared_ptr(Args&& ...);
    template<typename TT, typename ... Args>
    friend shared_ref<TT> make_shared_ref(Args&& ...);
    template<typename TT>
    friend shared_ref<TT> promote_to_ref(shared_ptr<TT>&&);
    template<typename TTT, typename TT>
    friend shared_ptr<TTT> dynamic_shared_cast(shared_ptr<TT>&&);
    template<typename TTT, typename TT>
    friend shared_ptr<TTT> static_shared_cast(shared_ptr<TT>&&);
    template<typename TTT, typename TT>
    friend shared_ptr<TTT> dynamic_shared_cast(shared_ref<TT>&&);
    template<typename TTT, typename TT>
    friend shared_ref<TTT> static_shared_cast(shared_ref<TT>&&);
    template<typename TT>
    friend shared_ptr<TT> const_shared_cast(shared_ptr<const TT>&&);
    template<typename TT>
    friend shared_ref<TT> const_shared_cast(shared_ref<const TT>&&);
	template<typename TT>
	friend lent_ref<TT> lend(shared_ref<TT>&);

public:
	typedef tagged_pointer<shared_reference_counter> tagged_reference_counter;
    using shared_ptr<T>::operator==;
    using shared_ptr<T>::operator!=;
    using shared_ptr<T>::operator=;
    using shared_ptr<T>::operator*;
    using shared_ptr<T>::operator->;
    using shared_ptr<T>::getData;

    shared_ref(T *pData, tagged_reference_counter referenceCounter, ISmartPtrDeleter* i_deleter = NULL);
    shared_ref(T *pData, ISmartPtrDeleter* i_deleter = NULL);
    shared_ref(shared_ref<T>&& other);
    shared_ref(const shared_ref&) = delete;
    template<typename TT>
    shared_ref(shared_ref<TT>&& other);
    shared_ref& operator=(const shared_ref&) = delete;

private:
    using shared_ptr<T>::extract_reference_counter;
    using shared_ptr<T>::getDeleter;
};

}
}

#include "YTL/types/smartPtr/detail/shared_ref.tpp"
