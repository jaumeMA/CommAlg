
namespace yame
{
namespace ytl
{

template<typename T>
shared_ref<T>::shared_ref(T *pData, tagged_reference_counter referenceCounter, ISmartPtrDeleter* i_deleter)
: shared_ptr<T>(pData,referenceCounter,i_deleter)
{
    ASSERT(pData != NULL, "You are constructing shared reference with null pointer");
}
template<typename T>
shared_ref<T>::shared_ref(T *pData, ISmartPtrDeleter* i_deleter)
: shared_ptr<T>(pData,make_tagged_pointer<shared_reference_counter>(0),i_deleter)
{
    ASSERT(pData != NULL, "You are constructing shared reference with null pointer");
}
template<typename T>
shared_ref<T>::shared_ref(shared_ref<T>&& other)
: shared_ptr<T>(mpl::move(other))
{
}
template<typename T>
template<typename TT>
shared_ref<T>::shared_ref(shared_ref<TT>&& other)
: shared_ptr<T>(mpl::move(other))
{
}

}
}
