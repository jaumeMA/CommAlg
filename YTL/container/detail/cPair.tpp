
namespace yame
{
namespace container
{
template<typename T, typename R>
cPair<T,R>::cPair()
: m_first(T{})
, m_second(R{})
, first(m_first)
, second(m_second)
{
}
template<typename T, typename R>
template<typename TFirst, typename TSecond>
cPair<T,R>::cPair(TFirst&& i_first, TSecond&& i_arg)
: m_first(mpl::forward<TFirst>(i_first))
, m_second(mpl::forward<TSecond>(i_arg))
, first(m_first)
, second(m_second)
{
}
template<typename T, typename R>
cPair<T,R>::cPair(const cPair<T,R>& other)
: m_first(other.m_first)
, m_second(other.m_second)
, first(m_first)
, second(m_second)
{
}
template<typename T, typename R>
cPair<T,R>::cPair(cPair<T,R>&& other)
: m_first(mpl::forward<typename mpl::static_if<mpl::is_reference<T>::value,T&,T&&>::type>(other.m_first))
, m_second(mpl::forward<typename mpl::static_if<mpl::is_reference<R>::value,R&,R&&>::type>(other.m_second))
, first(m_first)
, second(m_second)
{
}
template<typename T, typename R>
cPair<T,R>& cPair<T,R>::operator=(const cPair<T,R>& other)
{
    m_first = other.m_first;
    m_second = other.m_second;

    return *this;
}
template<typename T, typename R>
cPair<T,R>& cPair<T,R>::operator=(cPair<T,R>&& other)
{
    m_first = mpl::move(other.m_first);
    m_second = mpl::move(other.m_second);

    return *this;
}
template<typename T, typename R>
bool cPair<T,R>::operator==(const cPair<T,R>& other) const
{
    return (m_first == other.m_first) && (m_second == other.m_second);
}


template<typename T, typename R>
cPair<T,R> make_pair(T i_first, R i_second)
{
    return cPair<T,R>(mpl::forward<T>(i_first), mpl::forward<R>(i_second));
}

}
}
