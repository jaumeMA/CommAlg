
namespace yame
{
namespace math
{

template<set_traits_type Traits>
cSet<Traits>::cSet(const cSet<Traits>& other)
{
    Traits::init(m_value, other.m_value);
}
template<set_traits_type Traits>
cSet<Traits>::cSet(cSet<Traits>&& other)
{
    Traits::init(m_value, mpl::move(other.m_value));
}
template<set_traits_type Traits>
template<set_traits_type TTraits>
requires (mpl::is_base_of<Traits, TTraits>::value)
cSet<Traits>::cSet(const cSet<TTraits>& other)
{
    Traits::init(m_value, other.m_value);
}
template<set_traits_type Traits>
cSet<Traits>::cSet(const underlying_type& i_value)
{
    Traits::init(m_value, i_value);
}
template<set_traits_type Traits>
template<typename ... Args>
//requires requires(typename Traits::underlying_type& o_value, Args&& ... i_args) {{ Traits::init(o_value,i_args ...) }}
cSet<Traits>::cSet(const Args& ... i_args)
{
    Traits::init(m_value, i_args ...);
}
template<set_traits_type Traits>
cSet<Traits>::~cSet()
{
    Traits::deinit(m_value);
}
template<set_traits_type Traits>
const typename cSet<Traits>::underlying_type& cSet<Traits>::getValue() const
{
    return m_value;
}
template<set_traits_type Traits>
typename cSet<Traits>::underlying_type&& cSet<Traits>::extractValue()
{
    return mpl::move(m_value);
}
template<set_traits_type Traits>
typename cSet<Traits>::underlying_type& cSet<Traits>::getValue()
{
    return m_value;
}
template<set_traits_type Traits>
void cSet<Traits>::setValue(const underlying_type& i_value)
{
    Traits::assign(m_value, i_value);
}
template<set_traits_type Traits>
cSet<Traits>& cSet<Traits>::operator=(const cSet<Traits>& other)
{
    Traits::assign(m_value, other.m_value);

    return *this;
}
template<set_traits_type Traits>
cSet<Traits>& cSet<Traits>::operator=(cSet<Traits>&& other)
{
    Traits::assign(m_value, other.m_value);

    return *this;
}
template<set_traits_type Traits>
cSet<Traits>& cSet<Traits>::operator=(const underlying_type& i_value)
{
    Traits::assign(m_value, i_value);

    return *this;
}
template<set_traits_type Traits>
cSet<Traits>& cSet<Traits>::operator=(underlying_type&& i_value)
{
    Traits::assign(m_value, mpl::move(i_value));

    return *this;
}

}

}
