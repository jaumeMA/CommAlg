#pragma once

namespace yame
{

template<typename Type>
concept bool callable_type = requires { { &Type::operator() } };

}
