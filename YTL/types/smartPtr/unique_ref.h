#pragma once

#include "YTL/types/smartPtr/unique_ptr.h"

namespace yame
{
namespace ytl
{

template<typename T>
class unique_ref : public unique_ptr<T>
{
    template<typename TT>
    friend class unique_ptr;
    template<typename TT, typename ... Args>
    friend unique_ref<TT> make_unique_ref(Args&& ...);
    template<typename TT>
    friend unique_ref<TT> promote_to_ref(unique_ptr<TT>&& other);
    template<typename TTT, typename TT>
    friend unique_ptr<TTT> dynamic_unique_cast(unique_ptr<TT>&& other);
    template<typename TTT, typename TT>
    friend unique_ptr<TTT> static_unique_cast(unique_ptr<TT>&& other);
    template<typename TTT, typename TT>
    friend unique_ptr<TTT> dynamic_unique_cast(unique_ref<TT>&& other);
    template<typename TTT, typename TT>
    friend unique_ref<TTT> static_unique_cast(unique_ref<TT>&& other);
    template<typename TT>
    friend unique_ptr<TT> const_unique_cast(unique_ptr<const TT>&& other);
    template<typename TT>
    friend unique_ref<TT> const_unique_cast(unique_ref<const TT>&& other);
	template<typename TT>
	friend lent_ptr<TT> lend(unique_ptr<TT>& i_uniqueRef);

public:
	typedef tagged_pointer<unique_reference_counter> tagged_reference_counter;
    using unique_ptr<T>::operator==;
    using unique_ptr<T>::operator!=;
    using unique_ptr<T>::operator=;
    using unique_ptr<T>::operator*;
    using unique_ptr<T>::operator->;
    using unique_ptr<T>::getData;

    unique_ref(T *pData, tagged_reference_counter referenceCounter, ISmartPtrDeleter* i_deleter = NULL);
    unique_ref(T *pData, ISmartPtrDeleter* i_deleter = NULL);
    unique_ref(unique_ref<T>&& other);
    unique_ref(const unique_ref&) = delete;
    template<typename TT>
    unique_ref(TT *pData, ISmartPtrDeleter* deleter=NULL);
    template<typename TT>
    unique_ref(unique_ref<TT>&& other);
    unique_ref& operator=(const unique_ref&) = delete;
    unique_ref& operator=(unique_ref&& other);

private:
    using unique_ptr<T>::extract_reference_counter;
    using unique_ptr<T>::getDeleter;
};

}
}

#include "YTL/types/smartPtr/detail/unique_ref.tpp"
