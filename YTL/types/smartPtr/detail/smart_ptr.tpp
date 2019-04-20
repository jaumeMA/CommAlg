
namespace yame
{
namespace ytl
{

template<typename T>
lent_ref<T> promote_to_ref(const lent_ptr<T>& other)
{
#ifdef LENT_WITH_LOGIC
    return lent_ref<T>(other.getData(), other.getReferenceCounter());
#else
    return other;
#endif
}
template<typename T>
unique_ref<T> promote_to_ref(unique_ptr<T>&& other)
{
    tagged_pointer<unique_reference_counter> referenceCounter = other.extract_reference_counter();
    ISmartPtrDeleter* deleter = other.getDeleter();
    T* pData = other.extractData();

    return unique_ref<T>(pData,referenceCounter,deleter);
}
template<typename T>
shared_ref<T> promote_to_ref(const shared_ptr<T>& other)
{
    tagged_pointer<unique_reference_counter> referenceCounter = other.extract_reference_counter();
    ISmartPtrDeleter* deleter = other.getDeleter();
    T* pData = other.extractData();

    return shared_ref<T>(other.getData(),other.getReferenceCounter(),other.getDeleter());
}

template<typename TT, typename T>
lent_ptr<TT> dynamic_lent_cast(const lent_ptr<T>& other)
{
    static_assert(std::is_polymorphic<T>::value, "You shall work with polymprphic classes, try providing virtual destructor");

#ifdef LENT_WITH_LOGIC
    if(T* pData = other.getData())
    {
        if(TT* innerData = rtti::dynamicCast<TT>(pData))
        {
            return lent_ref<TT>(innerData, other.getReferenceCounter());
        }
        else
        {
            return null_ptr;
        }
    }
    else
    {
        return null_ptr;
    }
#else
    if(other)
    {
        return rtti::dynamicCast<TT>(other);
    }
    else
    {
        return NULL;
    }
#endif
}
#ifdef LENT_WITH_LOGIC

template<typename TT, typename T>
lent_ptr<TT> dynamic_lent_cast(const lent_ref<T>& other)
{
    static_assert(std::is_polymorphic<T>::value, "You shall work with polymprphic classes, try providing virtual destructor");

    ASSERT(other.getData(), "You shall provide a non empty pointer as ref");

    if(TT* innerData = rtti::dynamicCast<TT>(other.getData()))
    {
        return lent_ref<TT>(innerData, other.getReferenceCounter());
    }
    else
    {
        return null_ptr;
    }
}
#endif
template<typename TT, typename T>
unique_ptr<TT> dynamic_unique_cast(unique_ptr<T>&& i_uniqueRef)
{
	unique_ptr<TT> res;

	if (TT* tData = dynamic_cast<TT*>(i_uniqueRef.m_data))
	{
		unique_ref<TT> res(tData,i_uniqueRef.m_refCounter);

		i_uniqueRef.m_data = NULL;
		i_uniqueRef.m_refCounter = NULL;

        return std::move(res);
	}
	else
	{
        return null_ptr;
	}
}
template<typename TT, typename T>
unique_ptr<TT> dynamic_unique_cast(unique_ref<T>&& i_uniqueRef)
{
	unique_ptr<TT> res;

	if (TT* tData = dynamic_cast<TT*>(i_uniqueRef.m_data))
	{
		unique_ref<TT> res(tData,i_uniqueRef.m_refCounter);

		i_uniqueRef.m_data = NULL;
		i_uniqueRef.m_refCounter = NULL;

        return std::move(res);
	}
	else
	{
        return null_ptr;
	}
}
template<typename TT, typename T>
shared_ptr<TT> dynamic_shared_cast(const shared_ptr<T>& i_sharedPtr)
{
	if (TT* tData = dynamic_cast<TT*>(i_sharedPtr.m_data))
	{
		return shared_ptr<TT>(tData,i_sharedPtr.m_refCounter);
	}
	else
	{
		return null_ptr;
	}
}
template<typename TT, typename T>
shared_ptr<TT> dynamic_shared_cast(const shared_ref<T>& i_sharedRef)
{
	if (TT* tData = dynamic_cast<TT*>(i_sharedRef.m_data))
	{
		return shared_ptr<TT>(tData,i_sharedRef.m_refCounter);
	}
	else
	{
		return null_ptr;
	}
}

template<typename TT, typename T>
lent_ptr<TT> static_lent_cast(const lent_ptr<T>& other)
{
#ifdef LENT_WITH_LOGIC
    if(T* pData = other.getData())
    {
        TT* innerData = static_cast<TT*>(pData);

        return lent_ref<TT>(innerData, other.getReferenceCounter());
    }
    else
    {
        return null_ptr;
    }
#else
    return rtti::staticCast<TT>(other);
#endif
}
#ifdef LENT_WITH_LOGIC
template<typename TT, typename T>
lent_ref<TT> static_lent_cast(const lent_ref<T>& other)
{
    ASSERT(other.getData(), "You shall provide a non empty pointer as ref");

    const TT* innerData = static_cast<const TT*>(other.getData());

    return lent_ref<TT>(const_cast<T*>(innerData), other.getReferenceCounter());
}
#endif
template<typename TT, typename T>
unique_ptr<TT> static_unique_cast(unique_ptr<T>&& other)
{
    static_assert(mpl::is_base_of<T,TT>::value || mpl::is_base_of<TT,T>::value, "You shall provide related classes by inheritance");
    static_assert(std::is_polymorphic<T>::value, "You shall work with polymprphic classes, try providing virtual destructor");

    if(T* pData = other.extractData())
    {
        TT* innerData = rtti::staticCast<TT>(pData);
        tagged_pointer<unique_reference_counter> referenceCounter = other.extract_reference_counter();
        ISmartPtrDeleter* deleter = other.getDeleter();

        return unique_ref<TT>(innerData, referenceCounter, deleter);
    }
    else
    {
        return null_ptr;
    }
}
template<typename TT, typename T>
unique_ref<TT> static_unique_cast(unique_ref<T>&& other)
{
    tagged_pointer<unique_reference_counter> referenceCounter = other.extract_reference_counter();
    ISmartPtrDeleter* deleter = other.getDeleter();
    TT* innerData = rtti::staticCast<TT>(other.extractData());

    return unique_ref<TT>(innerData, referenceCounter, deleter);
}
template<typename TT, typename T>
shared_ptr<TT> static_shared_cast(const shared_ptr<T>& other)
{
    static_assert(mpl::is_base_of<T,TT>::value || mpl::is_base_of<TT,T>::value, "You shall provide related classes by inheritance");
    static_assert(std::is_polymorphic<T>::value, "You shall work with polymprphic classes, try providing virtual destructor");

    if(TT* innerData = rtti::staticCast<TT>(other.getData()))
    {
        tagged_pointer<unique_reference_counter> referenceCounter = other.getReferenceCounter();
        ISmartPtrDeleter* deleter = other.getDeleter();

        return shared_ref<TT>(innerData, referenceCounter, deleter);
    }
    else
    {
        return null_ptr;
    }
}
template<typename TT, typename T>
shared_ref<TT> static_shared_cast(const shared_ref<T>& other)
{
    static_assert(mpl::is_base_of<T,TT>::value || mpl::is_base_of<TT,T>::value, "You shall provide related classes by inheritance");
    static_assert(std::is_polymorphic<T>::value, "You shall work with polymprphic classes, try providing virtual destructor");

    TT* innerData = rtti::staticCast<TT>(other.getData());
    tagged_pointer<unique_reference_counter> referenceCounter = other.getReferenceCounter();
    ISmartPtrDeleter* deleter = other.getDeleter();

    return shared_ref<TT>(innerData, referenceCounter, deleter);
}

template<typename T>
lent_ptr<T> const_lent_cast(const lent_ptr<const T>& other)
{
#ifdef LENT_WITH_LOGIC
    if(const T* pData = other.getData())
    {
        T* innerData = const_cast<T*>(pData);

        return lent_ref<T>(innerData, other.getReferenceCounter());
    }
    else
    {
        return null_ptr;
    }
#else
    if(other)
    {
        return const_cast<T*>(other);
    }
    else
    {
        return NULL;
    }
#endif
}
#ifdef LENT_WITH_LOGIC
template<typename T>
lent_ref<T> const_lent_cast(const lent_ref<const T>& other)
{
    ASSERT(other.getData(), "You shall provide a non empty ref");
    T* innerData = const_cast<T*>(other.getData());

    return lent_ref<T>(innerData, other.lend());
}
#endif
template<typename T>
unique_ptr<T> const_unique_cast(unique_ptr<const T>&& other)
{
    if(const T* pData = other.extractData())
    {
        tagged_pointer<unique_reference_counter> referenceCounter = other.extract_reference_counter();
        ISmartPtrDeleter* deleter = other.getDeleter();
        T* innerData = const_cast<T*>(pData);

        return unique_ptr<T>(innerData, referenceCounter, deleter);
    }
    else
    {
        return null_ptr;
    }
}
template<typename T>
unique_ref<T> const_unique_cast(unique_ref<const T>&& other)
{
    const T* pData = other.extractData();
    ASSERT(pData, "You shall provide a non empty ref");
    tagged_pointer<unique_reference_counter> referenceCounter = other.extract_reference_counter();
    ISmartPtrDeleter* deleter = other.getDeleter();
    T* innerData = const_cast<T*>(pData);

    other.clear();

    return unique_ref<T>(innerData, referenceCounter, deleter);
}
template<typename T>
shared_ptr<T> const_shared_cast(const shared_ptr<const T>& other)
{
    if(const T* pData = other.extractData())
    {
        tagged_pointer<unique_reference_counter> referenceCounter = other.extract_reference_counter();
        ISmartPtrDeleter* deleter = other.getDeleter();
        T* innerData = const_cast<T*>(pData);

        return shared_ptr<T>(other.getData(),other.getReferenceCounter(),other.getDeleter());
    }
    else
    {
        return null_ptr;
    }
}
template<typename T>
shared_ref<T> const_shared_cast(const shared_ref<const T>& other)
{
    if(const T* pData = other.extractData())
    {
        tagged_pointer<unique_reference_counter> referenceCounter = other.extract_reference_counter();
        ISmartPtrDeleter* deleter = other.getDeleter();
        T* innerData = const_cast<T*>(pData);

        return shared_ref<T>(other.getData(),other.getReferenceCounter(),other.getDeleter());
    }
    else
    {
        return null_ptr;
    }
}

template<typename T>
lent_ref<T> lend(T& other, const typename T::lendable_tag* _foo)
{
#ifdef LENT_WITH_LOGIC
    typedef typename mpl::drop_constness<T>::type no_const_type;
    no_const_type& otherNoConst = const_cast<no_const_type&>(other);

    return lent_ref<T>(&otherNoConst,otherNoConst.ref_from_this());
#else
    typedef typename mpl::drop_constness<T>::type no_const_type;

    return const_cast<no_const_type*>(&other);
#endif
}
template<typename T>
lent_ptr<T> lend(unique_ptr<T>& i_uniquePtr)
{
#ifdef LENT_WITH_LOGIC
	return lent_ptr<T>(i_uniquePtr.getData(),i_uniquePtr.getReferenceCounter());
#else
    return i_uniquePtr.getData();
#endif
}
template<typename T>
lent_ref<T> lend(unique_ref<T>& i_uniqueRef)
{
#ifdef LENT_WITH_LOGIC
	return lent_ref<T>(i_uniqueRef.getData(),i_uniqueRef.getReferenceCounter());
#else
    return i_uniqueRef.getData();
#endif
}
template<typename T>
lent_ptr<T> lend(shared_ptr<T>& i_sharedPtr)
{
#ifdef LENT_WITH_LOGIC
	return lent_ptr<T>(i_sharedPtr.getData(),i_sharedPtr.getReferenceCounter());
#else
    return i_sharedPtr.getData();
#endif
}
template<typename T>
lent_ref<T> lend(shared_ref<T>& i_sharedRef)
{
#ifdef LENT_WITH_LOGIC
	return lent_ref<T>(i_sharedRef.getData(),i_sharedRef.getReferenceCounter());
#else
    return i_sharedRef.getData();
#endif
}

template<typename T, typename ... Args>
shared_ref<T> make_shared(Args&& ... i_args)
{
	char* allocatedMemory = reinterpret_cast<char*>(malloc(sizeof(T) + sizeof(shared_reference_counter)));

 	T* allocatedObject = new (allocatedMemory) T(mpl::forward<Args>(i_args) ...);

	shared_reference_counter* refCounter = new (allocatedMemory + sizeof(T)) shared_reference_counter();

	return shared_ref<T>(allocatedObject,tagged_pointer<shared_reference_counter>(refCounter,0x01));
}

template<typename T, typename ... Args>
unique_ref<T> make_unique(Args&& ... i_args)
{
	char* allocatedMemory = reinterpret_cast<char*>(malloc(sizeof(T) + sizeof(unique_reference_counter)));

 	T* allocatedObject = new (allocatedMemory) T(mpl::forward<Args>(i_args) ...);

	unique_reference_counter* refCounter = new (allocatedMemory + sizeof(T)) unique_reference_counter();

	return unique_ref<T>(allocatedObject,tagged_pointer<unique_reference_counter>(refCounter,0x01));
}

}
}
