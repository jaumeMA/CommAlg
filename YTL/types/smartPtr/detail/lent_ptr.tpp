
#include "Utils/cMacroHelper.h"
#include "YTL/mpl/cTemplateHelper.h"
#include "Utils/rtti/rtti.h"

namespace yame
{
namespace ytl
{

#ifdef LENT_WITH_LOGIC

template<typename T>
lent_ptr<T>::lent_ptr(T* i_data, tagged_reference_counter i_refCounter)
: m_refCounter(i_refCounter)
, m_data(i_data)
{
    if (m_refCounter)
    {
        m_refCounter->incrementWeakReference();
    }
}
template<typename T>
lent_ptr<T>::lent_ptr()
: m_refCounter(NULL)
, m_data(NULL)
{
}
template<typename T>
lent_ptr<T>::lent_ptr(const lent_ptr& other)
: m_refCounter(NULL)
, m_data(NULL)
{
    m_data = other.m_data;

    if(m_refCounter = other.m_refCounter)
    {
        m_refCounter->incrementWeakReference();
    }
}
template<typename T>
lent_ptr<T>::lent_ptr(lent_ptr&& other)
: m_refCounter(NULL)
, m_data(NULL)
{
    mpl::swapItems(m_data,other.m_data);
    mpl::swapItems(m_refCounter,other.m_refCounter);
}
template<typename T>
template<typename TT>
lent_ptr<T>::lent_ptr(const lent_ptr<TT>& other)
: m_refCounter(NULL)
, m_data(NULL)
{
    static_assert(mpl::is_base_of<T,TT>::value, "You shall provide inherited classes");

    m_data = other.m_data;

    if(m_refCounter = other.m_refCounter)
    {
        m_refCounter->incrementWeakReference();
    }
}
template<typename T>
template<typename TT>
lent_ptr<T>::lent_ptr(lent_ptr<TT>&& other)
: m_refCounter(NULL)
, m_data(NULL)
{
    static_assert(mpl::is_base_of<T,TT>::value, "You shall provide inherited classes");

    if(m_data = dynamic_cast<T*>(other.m_data))
    {
        mpl::swapItems(m_refCounter,other.m_refCounter);
    }

    other.m_data = NULL;
}
template<typename T>
template<typename TT>
lent_ptr<T>::lent_ptr(const unique_ptr<TT>& other)
: m_refCounter(NULL)
, m_data(NULL)
{
    static_assert(mpl::is_same_type<T,TT>::value || mpl::is_base_of<T,TT>::value, "You shall provide inherited classes");

    m_data = other.m_data;

    if(m_refCounter = other.m_refCounter)
    {
        m_refCounter->incrementWeakReference();
    }
}
template<typename T>
lent_ptr<T>::~lent_ptr()
{
    if(m_refCounter)
    {
        m_refCounter->decrementWeakReference();
    }
}
template<typename T>
lent_ptr<T>& lent_ptr<T>::operator=(const mpl::null_ptr_type&)
{
    if (m_refCounter.empty() == false)
    {
        m_refCounter->decrementWeakReference();
    }

    return *this;
}
template<typename T>
lent_ptr<T>& lent_ptr<T>::operator=(const lent_ptr& other)
{
    if(m_refCounter)
    {
        m_refCounter->decrementWeakReference();
    }

    m_data = other.m_data;

    if(m_refCounter = other.m_refCounter)
    {
        m_refCounter->incrementWeakReference();
    }

    return *this;
}
template<typename T>
lent_ptr<T>& lent_ptr<T>::operator=(lent_ptr&& other)
{
    if(m_refCounter)
    {
        m_refCounter->decrementWeakReference();
    }

    m_data = other.m_data;
    other.m_data = NULL;
    m_refCounter = other.m_refCounter;
    other.m_refCounter = NULL;

    return *this;
}
template<typename T>
template<typename TT>
lent_ptr<T>& lent_ptr<T>::operator=(const lent_ptr<TT>& other)
{
    static_assert(mpl::is_base_of<TT,T>::value, "You shall provide inherited classes");

    if(m_refCounter)
    {
        m_refCounter->decrementWeakReference();
    }

    m_data = other.m_data;

    if(m_refCounter = other.m_refCounter)
    {
        m_refCounter->incrementWeakReference();
    }

    return *this;
}
template<typename T>
template<typename TT>
lent_ptr<T>& lent_ptr<T>::operator=(lent_ptr<TT>&& other)
{
    static_assert(mpl::is_base_of<TT,T>::value, "You shall provide inherited classes");

    if(m_refCounter)
    {
        m_refCounter->decrementWeakReference();
    }

    m_data = other.m_data;

    other.m_data = NULL;
    m_refCounter = other.m_refCounter;
    other.m_refCounter = NULL;

    return *this;
}
template<typename T>
template<typename TT>
lent_ptr<T>& lent_ptr<T>::operator=(const unique_ptr<TT>& other)
{
    static_assert(mpl::is_base_of<T,TT>::value, "You shall provide inherited classes");

    if(m_refCounter)
    {
        m_refCounter->decrementWeakReference();
    }

    m_data = other.m_data;
    m_refCounter = other.m_refCounter;

    if (m_refCounter)
    {
        m_refCounter->incrementWeakReference();
    }

    return *this;
}
template<typename T>
bool lent_ptr<T>::operator==(mpl::null_ptr_type) const
{
    return m_data == NULL;
}
template<typename T>
bool lent_ptr<T>::operator==(const lent_ptr<T>& other) const
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
bool lent_ptr<T>::operator!=(mpl::null_ptr_type) const
{
    return m_data != NULL;
}
template<typename T>
bool lent_ptr<T>::operator!=(const lent_ptr<T>& other)
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
T* lent_ptr<T>::operator->()
{
    return m_data;
}
template<typename T>
const T* lent_ptr<T>::operator->() const
{
    return m_data;
}
template<typename T>
T& lent_ptr<T>::operator*()
{
    if(m_data == NULL)
    {
        MAKE_IT_CRASH
    }

    return *m_data;
}
template<typename T>
const T& lent_ptr<T>::operator*() const
{
    if(m_data == NULL)
    {
        MAKE_IT_CRASH
    }

    return *m_data;
}
template<typename T>
lent_ptr<T>::operator bool() const
{
    return m_data != NULL;
}
template<typename T>
void lent_ptr<T>::clear()
{
    m_data = NULL;

    if (m_refCounter)
    {
        m_refCounter->decrementWeakReference();

        m_refCounter = NULL;
    }
}
template<typename T>
T* lent_ptr<T>::getData()
{
    return m_data;
}
template<typename T>
const T* lent_ptr<T>::getData() const
{
    return m_data;
}
template<typename T>
typename lent_ptr<T>::tagged_reference_counter lent_ptr<T>::getReferenceCounter() const
{
    return m_refCounter;
}

#endif

}
}
