
#include "YTL/functional/cComposedCallable.h"
#include "Math/cMathTemplateHelper.h"
#include "Math/detail/cMetricSpaceImpl.h"
#include "Math/cVectorOps.h"

namespace yame
{
namespace math
{
namespace detail
{

template<int ... Components, ring_type Im, vector_space_type Dom>
container::cTupla<scalar_function<Im,Dom>,mpl::get_num_ranks<Components...>::value> derivative(const scalar_function<Im,Dom>& i_function)
{
    static_assert(mpl::get_num_ranks<Components...>::value <= Dom::dimension(), "Deriving more than can be done");
    static_assert(mpl::check_monotonic_range<Components...>::cond, "You shall provide a monotonically increasing components");

    return { detail::derivative_helper::derivative<Components>(i_function) ... };
}

template<ring_type Im, vector_space_type Dom>
scalar_function<Im,Dom> derivative(const Dom& i_direction, const scalar_function<Im,Dom>& i_function)
{
    typedef typename mpl::create_range_rank<0,Dom::dimension()>::type rangeSeq;

    return detail::derivative_helper::derivative(rangeSeq(), i_direction, i_function);
}

template<int Component, int ... Components, module_type Im, vector_space_type Dom>
vector_function<Im,Dom> derivative(const mpl::sequence<Components...>&, const vector_function<Im,Dom>& i_function)
{
    return vector_function<Im,Dom>(detail::derivative_helper::derivative<Component>(i_function.template get<Components>()) ...);
}

template<int ... Components, int ... CComponents, module_type Im, vector_space_type Dom>
requires ( mpl::get_num_ranks<Components...>::value > 1 )
container::cTupla<vector_function<Im,Dom>,mpl::get_num_ranks<Components...>::value> derivative(const mpl::sequence<CComponents...>& i_seq, const vector_function<Im,Dom>& i_function)
{
    return { derivative<Components>(i_seq,i_function) ...};
}

template<int ... Components, module_type Im, vector_space_type Dom>
vector_function<Im,Dom> derivative(const mpl::sequence<Components...>& i_seq, const Dom& i_direction, const vector_function<Im,Dom>& i_function)
{
    typedef typename mpl::create_range_rank<0,Dom::dimension()>::type rangeSeq;

    return { detail::derivative_helper::derivative(rangeSeq(), i_direction, i_function.template get<Components>()) ... };
}

template<int ... Components, module_type Im, vector_space_type Dom>
container::cTupla<vector_function<Im,Dom>,mpl::get_num_ranks<Components...>::value> derivative(const vector_function<Im,Dom>& i_function)
{
    static_assert(mpl::get_num_ranks<Components...>::value <= Dom::dimension(), "Deriving more than can be done");
    static_assert(mpl::check_monotonic_range<Components...>::cond, "You shall provide a monotonically increasing components");

    return derivative<Components...>(typename mpl::create_range_rank<0,Im::dimension()>::type{},i_function);
}

template<module_type Im, vector_space_type Dom>
vector_function<Im,Dom> derivative(const Dom& i_direction, const vector_function<Im,Dom>& i_function)
{
    typedef typename mpl::create_range_rank<0,Dom::dimension()>::type rangeSeq;

    return derivative(typename mpl::create_range_rank<0,Im::dimension()>::type{},i_function);
}

}

template<int ... Components, module_type Im, vector_space_type Dom>
container::cTupla<cFunctionSpace<Im,Dom>,mpl::get_num_ranks<Components...>::value> derivative(const cFunctionSpace<Im,Dom>& i_function)
{
    static_assert(mpl::get_num_ranks<Components...>::value <= Dom::dimension(), "Deriving more than can be done");
    static_assert(mpl::check_monotonic_range<Components...>::cond, "You shall provide a monotonically increasing components");

    return { cFunctionSpace<Im,Dom>(detail::derivative<Components>(typename mpl::create_range_rank<0,Im::dimension()>::type{},i_function.getValue())) ... };
}

template<module_type Im, vector_space_type Dom>
cFunctionSpace<Im,Dom> derivative(const Dom& i_direction, const cFunctionSpace<Im,Dom>& i_function)
{
    return detail::derivative(typename mpl::create_range_rank<0,Im::dimension()>::type{},i_direction, i_function.getValue());
}

}
}
