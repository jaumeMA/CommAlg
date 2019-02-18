#pragma once

#include "Utils/cMacroHelper.h"
#include <atomic>

#ifdef _DEBUG
    #define LENT_WITH_LOGIC
#endif

namespace yame
{
namespace ytl
{

enum class Policy
{
    Shared,
    Unique
};

template<Policy>
class reference_counter;

//reference counting for shared references
template<>
class reference_counter<Policy::Shared>
{
public:
	reference_counter()
	: m_numReferences(0)
	{
	}
	reference_counter(const reference_counter& other)
	: m_numReferences(other.m_numReferences.load())
	{
	}
	~reference_counter()
	{
	}
	size_t incrementReference()
	{
        size_t currNumReferences = 0;

        do
        {
            currNumReferences = m_numReferences.load();
        }
        while(m_numReferences.compare_exchange_weak(currNumReferences,currNumReferences+1) == false);

		return currNumReferences+1;
	}
	size_t decrementReference()
	{
        size_t currNumReferences = 0;

        do
        {
            currNumReferences = m_numReferences.load();
        }
        while(m_numReferences.compare_exchange_weak(currNumReferences,currNumReferences-1) == false);

		return currNumReferences-1;
	}
	size_t getNumReferences() const
	{
		return m_numReferences.load();
	}
	bool hasReferences() const
	{
		return m_numReferences.load() > 0;
	}

private:
    std::atomic<size_t> m_numReferences;
};

//reference counting for unique references

#ifdef LENT_WITH_LOGIC

template<>
class reference_counter<Policy::Unique>
{
public:
	reference_counter()
	: m_numStrongReferences(0)
	, m_numWeakReferences(0)
	{
	}
	reference_counter(const reference_counter& other)
	: m_numStrongReferences(other.m_numStrongReferences.load())
	, m_numWeakReferences(other.m_numWeakReferences.load())
	{
	}
	~reference_counter()
	{
	}
	size_t incrementStrongReference()
	{
        size_t currNumReferences = 0;

        do
        {
            currNumReferences = m_numStrongReferences.load();
        }
        while(m_numStrongReferences.compare_exchange_weak(currNumReferences,currNumReferences+1) == false);

		return currNumReferences+1;
	}
	size_t incrementWeakReference()
	{
        size_t currNumReferences = 0;

        do
        {
            currNumReferences = m_numWeakReferences.load();
        }
        while(m_numWeakReferences.compare_exchange_weak(currNumReferences,currNumReferences+1) == false);

		return currNumReferences+1;
	}
	size_t decrementStrongReference()
	{
        size_t currNumReferences = 0;

        do
        {
            currNumReferences = m_numStrongReferences.load();
        }
        while(m_numStrongReferences.compare_exchange_weak(currNumReferences,currNumReferences-1) == false);

		return currNumReferences-1;
	}
	size_t decrementWeakReference()
	{
        size_t currNumReferences = 0;

        do
        {
            currNumReferences = m_numWeakReferences.load();
        }
        while(m_numWeakReferences.compare_exchange_weak(currNumReferences,currNumReferences-1) == false);

		return currNumReferences-1;
	}
	size_t getNumStrongReferences() const
	{
        return m_numStrongReferences.load();
	}
	bool hasStrongReferences() const
	{
        return m_numStrongReferences.load() > 0;
	}
	size_t getNumWeakReferences() const
	{
        return m_numWeakReferences.load();
	}
	bool hasWeakReferences() const
	{
        return m_numWeakReferences.load() > 0;
	}

private:
    std::atomic<size_t> m_numStrongReferences;
    std::atomic<size_t> m_numWeakReferences;
};

#else

template<>
class reference_counter<Policy::Unique>
{
public:
	reference_counter()
	: m_numStrongReferences(0)
	{
	}
	reference_counter(const reference_counter& other)
	: m_numStrongReferences(other.m_numStrongReferences.load())
	{
	}
	~reference_counter()
	{
	}
	size_t incrementStrongReference()
	{
        size_t currNumReferences = 0;

        do
        {
            currNumReferences = m_numStrongReferences.load();
        }
        while(m_numStrongReferences.compare_exchange_weak(currNumReferences,currNumReferences+1) == false);

        return currNumReferences+1;
	}
	size_t decrementStrongReference()
	{
        size_t currNumReferences = 0;

        do
        {
            currNumReferences = m_numStrongReferences.load();
        }
        while(m_numStrongReferences.compare_exchange_weak(currNumReferences,currNumReferences-1) == false);

        return currNumReferences-1;
	}
	size_t getNumStrongReferences() const
	{
        return m_numStrongReferences.load();
	}
	bool hasStrongReferences() const
	{
        return m_numStrongReferences.load() > 0;
	}

private:
    std::atomic<size_t> m_numStrongReferences;
};

#endif

typedef reference_counter<Policy::Shared> shared_reference_counter;
typedef reference_counter<Policy::Unique> unique_reference_counter;

}
}
