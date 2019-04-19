#pragma once

#include "YTL/types/smartPtr/reference_counter.h"
#include "YTL/types/smartPtr/smart_deleter.h"
#include "YTL/types/smartPtr/lent_ptr.h"
#include "YTL/types/taggedPtr/tagged_pointer.h"

namespace yame
{
namespace ytl
{

template<typename T>
class unique_ptr
{
	template<typename>
	friend class unique_ptr;
#ifdef LENT_WITH_LOGIC
	template<typename>
	friend class lent_ptr;
#endif

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

	unique_ptr();
	unique_ptr(const mpl::null_ptr_type&);
	unique_ptr(const unique_ptr&) = delete;
	unique_ptr(unique_ptr&& other);
	template<typename TT>
	unique_ptr(unique_ptr<TT>&& other);
	~unique_ptr();
	unique_ptr& operator=(const mpl::null_ptr_type&);
	unique_ptr& operator=(unique_ptr&& other);
	unique_ptr& operator=(const unique_ptr&) = delete;
	template<typename TT>
	unique_ptr& operator=(unique_ptr<TT>&& other);
	bool operator==(const mpl::null_ptr_type&) const;
	bool operator==(const unique_ptr<T>& other) const;
	bool operator!=(const mpl::null_ptr_type&) const;
	bool operator!=(const unique_ptr<T>& other);
	T* operator->();
	const T* operator->() const;
	T& operator*();
	const T& operator*() const;
	operator bool() const;
	void clear();
	const T* getData() const;
	T* getData();

protected:
    ISmartPtrDeleter* getDeleter();
    tagged_reference_counter extract_reference_counter();
    T* extractData();
	unique_ptr(T* i_data, tagged_reference_counter i_refCounter, ISmartPtrDeleter* i_deleter = NULL);

private:
	void clearIfCounterVoid();

	tagged_reference_counter m_refCounter;
	T* m_data;
	ISmartPtrDeleter* m_deleter;
};

}
}

#include "YTL/types/smartPtr/detail/unique_ptr.tpp"
