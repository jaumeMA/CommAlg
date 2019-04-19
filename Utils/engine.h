
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

#include <stdio.h>
#include "errno.h"
#include "YTL/container/cArray.h"
#include "YTL/container/cString.h"
#include "YTL/container/cQueue.h"
#include "YTL/container/cTupla.h"
#include <SDL/SDL_image.h>
#include "System/time/cTime.h"

namespace yame
{
    container::string format(unsigned char i_value);
    container::string format(char i_value);
    container::string format(unsigned short i_value);
    container::string format(short i_value);
    container::string format(unsigned int i_value);
    container::string format(int i_value);
    container::string format(float i_value);
    container::string format(double i_value);
    container::string format(unsigned long i_value);
    container::string format(long i_value);
    container::string format(const container::string& i_value);
    template<typename T, typename A>
    inline container::string format(const container::cArray<T,A>& i_value);
    template<typename T, int rank, int ... ranks>
    inline container::string format(const container::detail::cSubTuple<T,rank,ranks...>& i_value);
    template<typename T, int rank, int ... ranks>
    inline container::string format(const container::cTupla<T,rank,ranks...>& i_value);
}

#include "Utils/detail/engine.tpp"
