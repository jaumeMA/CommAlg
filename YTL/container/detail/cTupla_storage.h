#pragma once

#include <initializer_list>
#include "YTL/mpl/cTemplateHelper.h"
#include "YTL/types/embedded_type/embedded_type.h"

#define PRIMITIVE_TYPE(T) typename yame::mpl::get_primitive_type<T,yame::mpl::has_base_type<T>::value>::type
#define DEFINE_PRIMITIVE_TYPE(T) typedef PRIMITIVE_TYPE(T) primitive_type

namespace yame
{
namespace container
{
namespace detail
{

template<typename T, int totalRank>
class cTuplaStorage
{
public:
    DEFINE_PRIMITIVE_TYPE(T);

    cTuplaStorage();
    cTuplaStorage(const cTuplaStorage<T,totalRank>& other);
    cTuplaStorage(cTuplaStorage<T,totalRank>&& other);
    template<typename TT>
    cTuplaStorage(const TT* i_ref);
    template<typename TT>
    cTuplaStorage(const std::initializer_list<TT>& other);
    ~cTuplaStorage();
    cTuplaStorage& operator=(const cTuplaStorage<T,totalRank>& other);
    cTuplaStorage& operator=(cTuplaStorage<T,totalRank>&& other);
    bool operator==(const cTuplaStorage<T,totalRank>& other) const;
    bool operator!=(const cTuplaStorage<T,totalRank>& other) const;
    template<int Index>
    inline T& get();
    template<int Index>
    inline const T& get() const;
    T& operator[](size_t i_index);
    const T& operator[](size_t i_index) const;
    primitive_type* address(size_t i_index = 0);
    const primitive_type* address(size_t i_index = 0) const;
    inline bool isAddressInside(const void* i_address, size_t i_bottomOffset, size_t i_topOffset) const;

    template<typename TT, int ... Indexs>
    static inline void construct_tupla(const mpl::sequence<Indexs...>&, T* i_dest, const TT* i_source);
    template<typename TT, int ... Indexs>
    static inline void assign_tupla(const mpl::sequence<Indexs...>&, T* i_dest, const TT* i_source);

private:
    template<int ... Indexs>
    requires ( mpl::is_default_constructible<T>::value )
    inline void default_construct_tupla(const mpl::sequence<Indexs...>&);
    template<int ... Indexs, typename ... Args>
    inline void construct_tupla(const mpl::sequence<Indexs...>&, Args&& ... i_args);
    template<typename TT, int ... Indexs>
    inline void construct_tupla(const mpl::sequence<Indexs...>&, const TT* i_ref);
    template<typename TT, int ... Indexs>
    inline void construct_tupla(const mpl::sequence<Indexs...>&, const std::initializer_list<TT>& other);
    template<typename TT, int ... Indexs>
    inline void construct_tupla(const mpl::sequence<Indexs...>&, const cTuplaStorage<TT,totalRank>& other);
    template<typename TT, int ... Indexs>
    inline void construct_tupla(const mpl::sequence<Indexs...>&, cTuplaStorage<TT,totalRank>&& other);
    template<typename TT, int ... Indexs>
    inline void assign_tupla(const mpl::sequence<Indexs...>&, const cTuplaStorage<TT,totalRank>& other);
    template<typename TT, int ... Indexs>
    inline void assign_tupla(const mpl::sequence<Indexs...>&, cTuplaStorage<TT,totalRank>&& other);
    template<int ... Indexs>
    inline bool compare_tupla(const mpl::sequence<Indexs...>&, const cTuplaStorage<T,totalRank>& other) const;

    template<typename Arg>
    static inline bool construct(void* i_address, Arg&& i_val)
    {
        return ytl::embedded_type<T>::construct(i_address,i_val);
    }
    template<typename Arg>
    static inline bool assign(void* i_address, Arg&& i_val)
    {
        return ytl::embedded_type<T>::assign(i_address,i_val);
    }
    static inline bool destruct(void* i_address)
    {
        return ytl::embedded_type<T>::destroy(i_address);
    }
    static inline bool compare(void* i_address, const T& i_value)
    {
        return ytl::embedded_type<T>::compare(i_address,i_value);
    }
    static inline typename ytl::embedded_type<T>::ref_type _get(const void* i_address)
    {
        return reinterpret_cast<ytl::embedded_type<T> *>(const_cast<void*>(i_address))->get();
    }
    static inline typename ytl::embedded_type<T>::rref_type extract(void* i_address)
    {
        return reinterpret_cast<ytl::embedded_type<T> *>(i_address)->extract();
    }

    typedef typename std::aligned_storage<sizeof(T) * totalRank, std::alignment_of<T>::value>::type data_type;
    data_type	m_storage;
};

}
}
}

#include "YTL/container/detail/cTupla_storage.tpp"
