#pragma once

#include "YTL/types/smartPtr/lent_ptr.h"

namespace yame
{
namespace ytl
{

#ifdef LENT_WITH_LOGIC

template<typename T>
class lent_ref : public lent_ptr<T>
{
	typedef tagged_pointer<lent_reference_counter> tagged_reference_counter;
    template<typename TT>
    friend lent_ref<TT> promote_to_ref(const lent_ptr<TT>& other);
    template<typename TTT, typename TT>
    friend lent_ptr<TTT> dynamic_lent_cast(const lent_ptr<TT>& other);
    template<typename TTT, typename TT>
    friend lent_ptr<TTT> static_lent_cast(const lent_ptr<TT>& other);
    template<typename TTT, typename TT>
    friend lent_ptr<TTT> dynamic_lent_cast(const lent_ref<TT>& other);
    template<typename TTT, typename TT>
    friend lent_ref<TTT> static_lent_cast(const lent_ref<TT>& other);
    template<typename TT>
    friend lent_ptr<TT> const_lent_cast(const lent_ptr<const TT>& other);
    template<typename TT>
    friend lent_ref<TT> const_lent_cast(const lent_ref<const TT>& other);

	lent_ref(T* i_data, tagged_reference_counter i_refCounter);

public:
    using lent_ptr<T>::getData;
    using lent_ptr<T>::getReferenceCounter;
    using lent_ptr<T>::operator==;
    using lent_ptr<T>::operator!=;
    using lent_ptr<T>::operator*;
    using lent_ptr<T>::operator->;
    using lent_ptr<T>::operator=;

    template<typename TT>
    lent_ref(const lent_ref<TT>& other);
    template<typename TT>
    lent_ref(lent_ref<TT>&& other);
    template<typename TT>
    lent_ref(const unique_ref<TT>& other);
    lent_ref(T *pData, enable_ref_from_this& referenceCounter);
};

#else

template<typename T>
using lent_ref = T*;

#endif

}
}

#include "YTL/types/smartPtr/detail/lent_ref.tpp"
