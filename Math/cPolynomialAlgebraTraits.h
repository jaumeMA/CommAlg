/*This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#pragma once

#include "YTL/container/cString.h"
#include "Math/cPolynomial.h"
#include "Math/detail/cSetInterface.h"
#include "Math/detail/cMathTypeConceptHelper.h"
#include "YTL/container/cContainerView.h"

namespace yame
{
namespace math
{

template<set_traits_type Traits>
struct PolynomialSetExtended : virtual public detail::ISet<Traits>
{
    typedef typename Traits::underlying_type underlying_type;
    typedef typename underlying_type::value_type value_type;
    typedef typename underlying_type::key_type key_type;
    typedef typename Traits::ring_type ring_type;
    typedef container::cBidirectionalView<ring_type> view_type;

    template<typename ... Degrees>
    ring_type& at(Degrees ... degrees);
    template<typename ... Degrees>
    const ring_type& at(Degrees ... degrees) const;
    ring_type& incognita(size_t index);
    const ring_type& incognita(size_t index) const;
    size_t getNumMonomials() const;
    value_type& operator[](size_t i_index);
    const value_type& operator[](size_t i_index) const;
    const underlying_type& get_raw() const;
    view_type view() const;
};

template<set_type T, template<typename> class A>
struct PolynomialSetTraits
{
    typedef T ring_type;
	typedef cPolynomial<T,A> underlying_type;
    typedef typename underlying_type::MapNode particle;

    static const particle& access(const underlying_type& i_value, size_t i_index);
    static particle& access(underlying_type& i_value, size_t i_index);
    static void init(underlying_type& o_value);
    static void init(underlying_type& o_value, const underlying_type& i_value);
    static void init(underlying_type& o_value, underlying_type&& i_value);
    static void deinit(underlying_type& o_value);
    static void assign(underlying_type& o_value, const underlying_type& i_value);
    static void assign(underlying_type& o_value, underlying_type&& i_value);
    static bool cmp(const underlying_type& i_lhs, const underlying_type& i_rhs);
    static container::string format(const underlying_type& i_value);

    static container::string formatMonomial(size_t i_varCounter, size_t i_expCounter, const cPolynomialValue<T,A>& i_polyValue);

    typedef PolynomialSetExtended<PolynomialSetTraits<T,A>> extended_structure;
};


template<group_type T, template<typename> class A>
struct PolynomialGroupTraits
{
    typedef PolynomialSetTraits<T,A> set_traits;
    typedef set_traits set;
	typedef typename set_traits::underlying_type underlying_type;
    typedef typename underlying_type::value_type value_type;
    typedef typename underlying_type::const_lvaluereference const_lvaluereference;
	static const underlying_type neutral_element;
	static const bool is_commutative = true;

	static void sum(underlying_type& o_res, const underlying_type& i_lhs,const underlying_type& i_rhs);
	static void inv(underlying_type& o_res, const underlying_type& value);

    static value_type sum(const_lvaluereference i_lhs, const_lvaluereference i_rhs);
    static value_type subs(const_lvaluereference i_lhs, const_lvaluereference i_rhs);
    static value_type inv(const_lvaluereference i_value);
};

template<ring_type T, template<typename> class A>
struct PolynomialModuleTraits
{
    typedef PolynomialGroupTraits<T,A> group_traits;
	typedef typename group_traits::underlying_type underlying_type;
    typedef typename underlying_type::value_type value_type;
    typedef typename underlying_type::const_lvaluereference const_lvaluereference;
    typedef T ring;
	static const bool is_leftModule = true;
	static const bool is_rightModule = true;

    static void modProd(underlying_type& o_res, const ring& i_lhs, const underlying_type& i_rhs);
    static void modProd(underlying_type& o_res, const underlying_type& i_lhs, const ring& i_rhs);

    static value_type mult(const_lvaluereference i_lhs, const_lvaluereference i_rhs);
    static value_type mult(const_lvaluereference i_lhs, const T& coeff);
};

template<ring_type T, template<typename> class A>
struct PolynomialAlgebraTraits
{
    typedef PolynomialModuleTraits<T,A> module_traits;
    typedef typename module_traits::group_traits group_traits;
	typedef typename module_traits::underlying_type underlying_type;
    typedef typename underlying_type::value_type value_type;
    typedef T ring;

	static void algProd(underlying_type& o_res, const underlying_type& i_lhs, const underlying_type& i_rhs);
};

}
}

#include "Math/detail/cPolynomialAlgebraTraits.tpp"
