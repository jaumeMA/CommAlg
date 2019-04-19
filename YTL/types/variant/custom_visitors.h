#pragma once

namespace yame
{
namespace ytl
{

struct formatter_visitor : public static_visitor<void>
{
    template<typename Type>
    void operator()(Type&& i_value);
};

}
}

#include "YTL/types/variant/detail/custom_visitors.tpp"
