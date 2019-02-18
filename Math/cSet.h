#pragma once

#include "Math/detail/cSetInterface.h"
#include "Math/cMathTemplateHelper.h"
#include "Math/detail/cMathTags.h"
#include "Math/detail/cMathTraitsConceptHelper.h"

namespace yame
{
namespace math
{

template<set_traits_type Traits>
class cSet : virtual public detail::ISet<Traits>, public inherit_extended_structure<Traits>::type
{
    template<set_traits_type>
    friend class cSet;
    typedef typename inherit_extended_structure<Traits>::type extended_set;
public:
    typedef Traits traits;
	typedef typename Traits::underlying_type underlying_type;
    using extended_set::extended_set;
    using extended_set::operator=;

	cSet(const underlying_type& i_value);
	cSet(const cSet<Traits>& other);
	cSet(cSet<Traits>&& other);
    template<set_traits_type TTraits>
    requires (mpl::is_base_of<Traits, TTraits>::value)
    cSet(const cSet<TTraits>& other);
    template<typename ... Args>
//    requires requires(typename Traits::underlying_type& o_value, Args&& ... i_args) {{ Traits::init(o_value,i_args...) }}
    cSet(const Args& ... i_args);
    ~cSet();

    cSet<Traits>& operator=(const cSet<Traits>& other) override;
    cSet<Traits>& operator=(cSet<Traits>&& other) override;
    cSet<Traits>& operator=(const underlying_type& i_value) override;
    cSet<Traits>& operator=(underlying_type&& i_value) override;
    const underlying_type& getValue() const override;
    underlying_type& getValue() override;

protected:
    void setValue(const underlying_type& i_value) override;
    underlying_type&& extractValue();

private:
	underlying_type m_value;
};

}

}

#include "Math/detail/cSet.tpp"
