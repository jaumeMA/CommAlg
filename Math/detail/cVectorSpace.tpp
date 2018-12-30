
#include "Utils/engine.h"

namespace yame
{

template<typename T, int N>
container::string format(const math::vector<T,N>& i_value)
{
    return format(i_value.getValue());
}

template<typename T, int N, int M>
container::string format(const math::matrix<T,N,M>& i_value)
{
    return format(i_value.getValue());
}

}
