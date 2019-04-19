
namespace yame
{
namespace ytl
{

template<typename T>
unique_ref<T>::unique_ref(T *pData, tagged_reference_counter referenceCounter, ISmartPtrDeleter* i_deleter)
: unique_ptr<T>(pData,referenceCounter,i_deleter)
{
}
template<typename T>
unique_ref<T>::unique_ref(T *pData, ISmartPtrDeleter* i_deleter)
: unique_ptr<T>(pData,make_tagged_pointer<unique_reference_counter>(0),i_deleter)
{
}
template<typename T>
unique_ref<T>::unique_ref(unique_ref<T>&& other)
: unique_ptr<T>(mpl::move(other))
{
}
template<typename T>
template<typename TT>
unique_ref<T>::unique_ref(TT *pData, ISmartPtrDeleter* deleter)
: unique_ptr<T>(pData,deleter)
{
}
template<typename T>
template<typename TT>
unique_ref<T>::unique_ref(unique_ref<TT>&& other)
: unique_ptr<T>(mpl::move(other))
{
}
template<typename T>
unique_ref<T>& unique_ref<T>::operator=(unique_ref&& other)
{
    unique_ptr<T>::operator=(mpl::move(other));

    return *this;
}

}
}
