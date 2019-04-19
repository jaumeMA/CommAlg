#pragma once

#include "YTL/mpl/cTemplateHelper.h"

namespace yame
{
namespace ytl
{

template<typename ...>
class variant;

}

namespace mpl
{

template<typename T>
struct is_variant;

template<typename ... Types>
struct is_variant < ytl::variant<Types...> >
{
    static const bool value = true;
};

template<typename T>
struct is_variant
{
    static const bool value = false;
};

}
}
