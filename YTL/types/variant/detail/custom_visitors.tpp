
#include "Utils/engine.h"

namespace yame
{
namespace ytl
{

template<typename T>
void formatter_visitor::operator()(T&& i_value)
{
    yame::container::string str = yame::format(i_value);

    printf("formatting: %s\n",str.getStr());
}

}
}
