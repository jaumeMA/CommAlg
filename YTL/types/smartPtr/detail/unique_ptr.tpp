
#include "Utils/cMacroHelper.h"

namespace yame
{
namespace ytl
{

template<typename T>
unique_ptr<T>::unique_ptr()
: m_refCounter(NULL)
, m_data(NULL)
, m_deleter(NULL)
{
}
template<typename T>
unique_ptr<T>::unique_ptr(const mpl::null_ptr_type&)
: m_refCounter(NULL)
, m_data(NULL)
, m_deleter(NULL)
{
}
template<typename T>
unique_ptr<T>::unique_ptr(unique_ptr&& other)
: m_refCounter(NULL)
, m_data(NULL)
, m_deleter(other.m_deleter)
{
    std::swap(m_data,other.m_data);
    std::swap(m_refCounter,other.m_refCounter);
}
template<typename T>
template<typename TT>
unique_ptr<T>::unique_ptr(unique_ptr<TT>&& other)
: m_refCounter(NULL)
, m_data(NULL)
, m_deleter(other.m_deleter)
{
    static_assert(std::is_base_of<T,TT>::value, "You shall provide inherited classes");

    if(m_data = other.m_data)
    {
        std::swap(m_refCounter,other.m_refCounter);
    }

    other.m_data = NULL;
}
template<typename T>
unique_ptr<T>::~unique_ptr()
{
    if(m_refCounter)
    {
        m_refCounter->decrementStrongReference();

        clearIfCounterVoid();
    }
}
template<typename T>
unique_ptr<T>& unique_ptr<T>::operator=(const mpl::null_ptr_type&)
{
    if (m_refCounter)
    {
        m_refCounter->decrementStrongReference();

        clearIfCounterVoid();
    }

    return *this;
}
template<typename T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr&& other)
{
    if(m_refCounter)
    {
        m_refCounter->decrementStrongReference();

        clearIfCounterVoid();
    }

    m_deleter = other.m_deleter;
    m_data = other.m_data;
    other.m_data = NULL;
    m_refCounter = other.m_refCounter;
    other.m_refCounter = NULL;

    return *this;
}
template<typename T>
template<typename TT>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr<TT>&& other)
{
    static_assert(std::is_base_of<T,TT>::value, "You shall provide inherited classes");

    if(m_refCounter)
    {
        m_refCounter->decrementStrongReference();

        clearIfCounterVoid();
    }

    if(m_data = other.m_data)
    {
        m_deleter = other.m_deleter;
    }

    other.m_data = NULL;
    m_refCounter = other.m_refCounter;
    other.m_refCounter = NULL;

    return *this;
}
template<typename T>
bool unique_ptr<T>::operator==(const mpl::null_ptr_type&) const
{
    return m_data == NULL;
}
template<typename T>
bool unique_ptr<T>::operator==(const unique_ptr<T>& other) const
{
    if (m_data && other.m_data)
    {
        return m_data == other.m_data;
    }
    else
    {
        return false;
    }
}
template<typename T>
bool unique_ptr<T>::operator!=(const mpl::null_ptr_type&) const
{
    return m_data != NULL;
}
template<typename T>
bool unique_ptr<T>::operator!=(const unique_ptr<T>& other)
{
    if (m_data && other.m_data)
    {
        return m_data != other.m_data;
    }
    else
    {
        return true;
    }
}
template<typename T>
T* unique_ptr<T>::operator->()
{
    return m_data;
}
template<typename T>
const T* unique_ptr<T>::operator->() const
{
    return m_data;
}
template<typename T>
T& unique_ptr<T>::operator*()
{
    if(m_data == NULL)
    {
        MAKE_IT_CRASH
    }

    return *m_data;
}
template<typename T>
const T& unique_ptr<T>::operator*() const
{
    if(m_data == NULL)
    {
        MAKE_IT_CRASH
    }

    return *m_data;
}
template<typename T>
unique_ptr<T>::operator bool() const
{
    return m_data != NULL;
}
template<typename T>
void unique_ptr<T>::clear()
{
    if (m_refCounter)
    {
        m_refCounter->decrementStrongReference();

        clearIfCounterVoid();
    }
}
template<typename T>
const T* unique_ptr<T>::getData() const
{
    return m_data;
}
template<typename T>
T* unique_ptr<T>::extractData()
{
    T* res = m_data;

    m_data = NULL;

    return res;
}
template<typename T>
T* unique_ptr<T>::getData()
{
    return m_data;
}
template<typename T>
ISmartPtrDeleter* unique_ptr<T>::getDeleter()
{
    return m_deleter;
}
template<typename T>
typename unique_ptr<T>::tagged_reference_counter unique_ptr<T>::extract_reference_counter()
{
    tagged_reference_counter res;

    if(res = m_refCounter.extract())
    {
        res->decrementStrongReference();
    }

    return res;
}
template<typename T>
unique_ptr<T>::unique_ptr(T* i_data, tagged_reference_counter i_refCounter, ISmartPtrDeleter* i_deleter)
: m_data(i_data)
, m_refCounter(i_refCounter)
, m_deleter(i_deleter)
{
    m_refCounter->incrementStrongReference();
}
template<typename T>
void unique_ptr<T>::clearIfCounterVoid()
{
    if(m_refCounter->hasStrongReferences() == false)
    {
        ASSERT(m_refCounter->hasWeakReferences() == false, "Still lent references alive while destroying unique reference");

        const bool isTagged = m_refCounter.is_tagged();
        unique_reference_counter* refCounter = m_refCounter.extract_pointer();

        if (isTagged == false)
        {
            delete refCounter;
        }
        else
        {
            refCounter->~unique_reference_counter();
        }

        if(m_deleter)
        {
            m_deleter->Deallocate(const_cast<typename std::remove_const<T>::type*>(m_data));
        }
        else
        {
            ::delete(m_data);
        }

        m_data = NULL;
        m_refCounter = NULL;
    }
}

}
}
