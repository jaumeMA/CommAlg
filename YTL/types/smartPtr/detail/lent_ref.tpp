
namespace yame
{
namespace ytl
{

#ifdef LENT_WITH_LOGIC

template<typename T>
lent_ref<T>::lent_ref(T* i_data, tagged_reference_counter i_refCounter)
: lent_ptr<T>(i_data,i_refCounter)
{
}
template<typename T>
template<typename TT>
lent_ref<T>::lent_ref(const lent_ref<TT>& other)
: lent_ptr<T>(other)
{
}
template<typename T>
template<typename TT>
lent_ref<T>::lent_ref(lent_ref<TT>&& other)
: lent_ptr<T>(mpl::move(other))
{
}
template<typename T>
template<typename TT>
lent_ref<T>::lent_ref(const unique_ref<TT>& other)
: lent_ptr<T>(mpl::move(other))
{
}
template<typename T>
lent_ref<T>::lent_ref(T *pData, enable_ref_from_this& referenceCounter)
: lent_ptr<T>(pData,referenceCounter.getRefCounter())
{
}

#endif

}
}
