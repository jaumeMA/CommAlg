
#define TUPLA_STORAGE_ADDRESS(_STORAGE) reinterpret_cast<T*>(const_cast<decltype(_STORAGE)*>(&_STORAGE))

namespace yame
{
namespace container
{
namespace detail
{

template<typename T, int totalRank>
cTuplaStorage<T,totalRank>::cTuplaStorage()
{
    typedef typename mpl::create_range_rank<0,totalRank>::type range_rank_t;

    default_construct_tupla(range_rank_t{});
}
template<typename T, int totalRank>
cTuplaStorage<T,totalRank>::cTuplaStorage(const cTuplaStorage<T,totalRank>& other)
{
    typedef typename mpl::create_range_rank<0,totalRank>::type range_rank_t;

    construct_tupla(range_rank_t{},other);
}
template<typename T, int totalRank>
cTuplaStorage<T,totalRank>::cTuplaStorage(cTuplaStorage<T,totalRank>&& other)
{
    typedef typename mpl::create_range_rank<0,totalRank>::type range_rank_t;

    construct_tupla(range_rank_t{},mpl::move(other));
}
template<typename T, int totalRank>
template<typename TT>
cTuplaStorage<T,totalRank>::cTuplaStorage(const TT* i_ref)
{
    typedef typename mpl::create_range_rank<0,totalRank>::type range_rank_t;

    construct_tupla(range_rank_t{},i_ref);
}
template<typename T, int totalRank>
template<typename TT>
cTuplaStorage<T,totalRank>::cTuplaStorage(const std::initializer_list<TT>& other)
{
    typedef typename mpl::create_range_rank<0,totalRank>::type range_rank_t;

    construct_tupla(range_rank_t{},other);
}
template<typename T, int totalRank>
cTuplaStorage<T,totalRank>::~cTuplaStorage()
{
    typedef typename mpl::create_range_rank<0,totalRank>::type range_rank_t;

    destruct_tupla(range_rank_t{});
}
template<typename T, int totalRank>
cTuplaStorage<T,totalRank>& cTuplaStorage<T,totalRank>::operator=(const cTuplaStorage<T,totalRank>& other)
{
    typedef typename mpl::create_range_rank<0,totalRank>::type range_rank_t;

    assign_tupla(range_rank_t{},other);

    return *this;
}
template<typename T, int totalRank>
cTuplaStorage<T,totalRank>& cTuplaStorage<T,totalRank>::operator=(cTuplaStorage<T,totalRank>&& other)
{
    typedef typename mpl::create_range_rank<0,totalRank>::type range_rank_t;

    assign_tupla(range_rank_t{},mpl::move(other));

    return *this;
}
template<typename T, int totalRank>
template<int Index>
T& cTuplaStorage<T,totalRank>::get()
{
    return _get(TUPLA_STORAGE_ADDRESS(m_storage) + Index);
}
template<typename T, int totalRank>
template<int Index>
const T& cTuplaStorage<T,totalRank>::get() const
{
    return _get(TUPLA_STORAGE_ADDRESS(m_storage) + Index);
}
template<typename T, int totalRank>
T& cTuplaStorage<T,totalRank>::operator[](size_t i_index)
{
    return _get(TUPLA_STORAGE_ADDRESS(m_storage) + i_index);
}
template<typename T, int totalRank>
const T& cTuplaStorage<T,totalRank>::operator[](size_t i_index) const
{
    return _get(TUPLA_STORAGE_ADDRESS(m_storage) + i_index);
}
template<typename T, int totalRank>
typename cTuplaStorage<T,totalRank>::primitive_type* cTuplaStorage<T,totalRank>::address(size_t i_index)
{
    return TUPLA_STORAGE_ADDRESS(m_storage) + i_index;
}
template<typename T, int totalRank>
const typename cTuplaStorage<T,totalRank>::primitive_type* cTuplaStorage<T,totalRank>::address(size_t i_index) const
{
    return TUPLA_STORAGE_ADDRESS(m_storage) + i_index;
}
template<typename T, int totalRank>
bool cTuplaStorage<T,totalRank>::operator==(const cTuplaStorage<T,totalRank>& other) const
{
    typedef typename mpl::create_range_rank<0,totalRank>::type range_rank_t;

    return compare_tupla(range_rank_t{},other);
}
template<typename T, int totalRank>
bool cTuplaStorage<T,totalRank>::operator!=(const cTuplaStorage<T,totalRank>& other) const
{
    typedef typename mpl::create_range_rank<0,totalRank>::type range_rank_t;

    return compare_tupla(range_rank_t{},other) == false;
}
template<typename T, int totalRank>
bool cTuplaStorage<T,totalRank>::isAddressInside(const void* i_address, size_t i_bottomOffset, size_t i_topOffset) const
{
    static const primitive_type* formattedStorage = reinterpret_cast<const primitive_type*>(&(this->m_storage));
    const primitive_type* address = reinterpret_cast<const primitive_type*>(i_address);

    return address >= (formattedStorage + i_bottomOffset) && address < (formattedStorage + totalRank - i_topOffset);
}
template<typename T, int totalRank>
template<typename TT, int ... Indexs>
void cTuplaStorage<T,totalRank>::construct_tupla(const mpl::sequence<Indexs...>&, T* i_dest, const TT* i_source)
{
    (construct(i_dest + Indexs,*(i_source + Indexs)) && ...);
}
template<typename T, int totalRank>
template<int ... Indexs>
void cTuplaStorage<T,totalRank>::destruct_tupla(const mpl::sequence<Indexs...>&)
{
    (destruct(TUPLA_STORAGE_ADDRESS(m_storage) + Indexs) && ...);
}
template<typename T, int totalRank>
template<typename TT, int ... Indexs>
void cTuplaStorage<T,totalRank>::assign_tupla(const mpl::sequence<Indexs...>&, T* i_dest, const TT* i_source)
{
    (assign(i_dest + Indexs,*(i_source + Indexs)) && ...);
}
template<typename T, int totalRank>
template<typename TT, int ... Indexs>
void cTuplaStorage<T,totalRank>::construct_tupla(const mpl::sequence<Indexs...>&, const std::initializer_list<TT>& other)
{
    (construct(TUPLA_STORAGE_ADDRESS(m_storage) + Indexs,*(other.begin() + Indexs)) && ...);
}
template<typename T, int totalRank>
template<int ... Indexs>
requires ( mpl::is_default_constructible<T>::value )
void cTuplaStorage<T,totalRank>::default_construct_tupla(const mpl::sequence<Indexs...>&)
{
    (construct(TUPLA_STORAGE_ADDRESS(m_storage) + Indexs, T{}) && ...);
}
template<typename T, int totalRank>
template<int ... Indexs, typename ... Args>
void cTuplaStorage<T,totalRank>::construct_tupla(const mpl::sequence<Indexs...>&, Args&& ... i_args)
{
    (construct(TUPLA_STORAGE_ADDRESS(m_storage) + Indexs,mpl::forward<Args>(i_args)) && ...);
}
template<typename T, int totalRank>
template<typename TT, int ... Indexs>
void cTuplaStorage<T,totalRank>::construct_tupla(const mpl::sequence<Indexs...>&, const TT* i_ref)
{
    (construct(TUPLA_STORAGE_ADDRESS(m_storage) + Indexs, *(i_ref + Indexs)) && ...);
}
template<typename T, int totalRank>
template<typename TT, int ... Indexs>
void cTuplaStorage<T,totalRank>::construct_tupla(const mpl::sequence<Indexs...>&, const cTuplaStorage<TT,totalRank>& other)
{
    (construct(TUPLA_STORAGE_ADDRESS(m_storage) + Indexs,other.get<Indexs>()) && ...);
}
template<typename T, int totalRank>
template<typename TT, int ... Indexs>
void cTuplaStorage<T,totalRank>::construct_tupla(const mpl::sequence<Indexs...>&, cTuplaStorage<TT,totalRank>&& other)
{
    (construct(TUPLA_STORAGE_ADDRESS(m_storage) + Indexs,mpl::move(other.get<Indexs>())) && ...);
}
template<typename T, int totalRank>
template<typename TT, int ... Indexs>
void cTuplaStorage<T,totalRank>::assign_tupla(const mpl::sequence<Indexs...>&, const cTuplaStorage<TT,totalRank>& other)
{
    (assign(TUPLA_STORAGE_ADDRESS(m_storage) + Indexs,other.get<Indexs>()) && ...);
}
template<typename T, int totalRank>
template<typename TT, int ... Indexs>
void cTuplaStorage<T,totalRank>::assign_tupla(const mpl::sequence<Indexs...>&, cTuplaStorage<TT,totalRank>&& other)
{
    (assign(TUPLA_STORAGE_ADDRESS(m_storage) + Indexs,mpl::move(other.get<Indexs>())) && ...);
}
template<typename T, int totalRank>
template<int ... Indexs>
bool cTuplaStorage<T,totalRank>::compare_tupla(const mpl::sequence<Indexs...>&, const cTuplaStorage<T,totalRank>& other) const
{
    return (compare(TUPLA_STORAGE_ADDRESS(m_storage) + Indexs,other.get<Indexs>()) && ...);
}

}
}
}
