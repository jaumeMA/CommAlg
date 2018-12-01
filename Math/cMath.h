
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

#include <math.h>
#include <cstring>
#include <cstdlib>
#include <cstdarg>
#include "Utils/cBitUtilities.h"
#include <cmath>

namespace yame
{
namespace math
{
enum E_TYPE_COMBINATORICS
{
    ETC_REPETITION,
    ETC_NO_REPETITIION,
    ETC_COUNT
};
enum E_TYPE_DCFT
{
    ETD_TYPEII,
    ETD_TYPEIV,
    ETD_COUNT
};
enum E_COMPONENT_LETTER
{
    ECL_X,
    ECL_Y,
    ECL_Z,
    ECL_W,
    ECL_COUNT
};
enum E_ORDER
{
EPO_LEX,
EPO_GRLEX,
EPO_GREVLEX,
EPO_COUNT
};


#define DEG2RAD(deg) (deg)*M_PI/180
#define FLOAT_FTOI_MAGIC_NUM (float)(3<<21)
#define IT_FTOI_MAGIC_NUM (0x4ac00000)


inline unsigned int FastFloatToInt(float f)
{
    f += FLOAT_FTOI_MAGIC_NUM;
    return (*((int*)&f) - IT_FTOI_MAGIC_NUM)>>1;
}
inline bool even(unsigned char number)
{
    return (number&0x01)==0;
}
inline bool odd(unsigned char number)
{
    return !even(number);
}
inline bool even(unsigned short number)
{
    return (number&0x01)==0;
}
inline bool odd(unsigned short number)
{
    return !even(number);
}
inline bool even(unsigned int number)
{
    return (number&0x01)==0;
}
inline bool odd(unsigned int number)
{
    return !even(number);
}
inline signed char parity(unsigned int number)
{
    signed char res = ((number&0x01) == 1) ? -1 : 1;
    return res;
}
inline signed char sign(signed char number)
{
    signed char res = ((number&(1<<7)) == 0) ? 1 : -1;
    return res;
}
inline signed short sign(signed short number)
{
    signed short res = ((number&(1<<15)) == 0) ? 1 : -1;
    return res;
}
inline signed char sign(int number)
{
    signed char res = ((number&(1<<31)) == 0) ? 1 : -1;
    return res;
}
inline unsigned char abs(char number)
{
    unsigned char res = number & ~(1<<7);
    return res;
}
inline unsigned short abs(signed short number)
{
    unsigned short res = number & ~(1<<15);
    return res;
}
inline unsigned int abs(int number)
{
    unsigned int res = number & ~(1<<31);
    return res;
}
inline unsigned int nextPowerOf2(unsigned int number)
{
    if (number != 0)
    {
        unsigned int res = number - 1;

        res |= res >> 1;
        res |= res >> 2;
        res |= res >> 4;
        res |= res >> 8;
        res |= res >> 16;

        res++;

        return res;
    }
    else
    {
        return 1;
    }
}
inline unsigned int powerOf2BitPos(unsigned int number)
{
    if (number != 0)
    {
        const unsigned char firstNonZeroBit = (sizeof(unsigned int) << 3) - __builtin_clz(number);

        return ((number & (number -1)) == 0) ? firstNonZeroBit : firstNonZeroBit + 1;
    }
    else
    {
        return 0;
    }
}
inline bool powerOf2(unsigned int number)
{
    return (number != 0)&&((number&(number-1))==0);
}
inline float invSqrt(float number)
{
    float numHalf = 0.5f*number;
    int numInt = *(int*)&number;
    numInt = 0x5f3759d5 - (numInt >> 1);
    number = *(float*)&numInt;
    number = number*(1.5f - numHalf*number*number);
    number = number*(1.5f - numHalf*number*number);
    number = number*(1.5f - numHalf*number*number);

    return number;
}
inline float inv(float number)
{
    unsigned int *numInt = (unsigned int *)&number;
    *numInt = 0x7F000000 - *numInt;

    return number;
}
inline unsigned int factorial(const unsigned int& number)
{
    unsigned int res = 0;

    if(number <= 1)
        res = 1;
    else
        res = number*factorial(number-1);

    return res;
}
inline unsigned int product(unsigned char rank, unsigned char val, ...)
{
    unsigned int res = val;
    va_list args;
    va_start(args,val);

    for(unsigned short i=1;i<rank;i++)
    {
        res *= va_arg(args,int);
    }
    va_end(args);

    return res;
}
inline unsigned short NoverM(unsigned short N, unsigned short M)
{
    unsigned short res = 1;

    if(N>M)
    {
        res = factorial(N)/(factorial(M)*factorial(N-M));
    }

    return res;
}
inline void sort(unsigned short *list, unsigned short length)
{
    unsigned short counter = 0;
    unsigned short temp = 0;

    for(unsigned short i=0;i<length;i++)
    {
        for(signed short j=i-1;j>=0;j--)
        {
            if(list[i]>list[(unsigned short)j])
            {
                break;
            }
            counter++;
        }
        temp = list[i-counter];
        list[i-counter] = list[i];
        list[i] = temp;
        counter = 0;
    }
}
inline void permutation(unsigned char *perm, signed char *sign, unsigned char number, unsigned char level=3)
{
    unsigned int factLevel = factorial(level-1);
    unsigned int factNumber = factorial(number);
    unsigned char counter = level-1;
    signed char shift = -1;
    unsigned char numInv = 0;

    if(level == 3)
    {
        *perm = 1;
        *(perm+1) = 2;
        *(perm+number) = 2;
        *(perm+number+1) = 1;
        sign[0] = 1;
        sign[1] = -1;
    }

    if(level <= number)
    {
        unsigned char *currPerm = (unsigned char *)malloc(factNumber*number*sizeof(unsigned char));
        memcpy(currPerm,perm,factNumber*number*sizeof(unsigned char));
        signed char *currSign = (signed char *)malloc(factNumber*sizeof(signed char));
        memcpy(currSign,sign,factNumber*sizeof(signed char));

        for(unsigned short i=0;i<factLevel;i++)
        {
            for(unsigned char j=0;j<level;j++)
            {
                sign[j+i*level] = currSign[i];
                memcpy(perm+number*(j+i*level),currPerm+i*number,sizeof(unsigned char)*number);
            }
        }

        memcpy(currPerm,perm,factNumber*number*sizeof(unsigned char));

        for(unsigned short i=0;i<level*factLevel;i++)
        {
            sign[i] *= parity((unsigned int)numInv);
            if(i%level == 0 && i > 0)
                shift *= -1;
            for(unsigned char j=counter;j<number-1;j++)
                *(perm + i*number + j + 1) = *(currPerm + i*number + j);

            *(perm + i*number + counter) = level;

            if((counter > 0 && shift == -1) || (counter < number-1 && shift == 1))
            {
                numInv -= shift;
                counter += shift;
            }
        }
        level += 1;
        free(currPerm);
        free(currSign);
        //recursivitat
        permutation(perm,sign,number,level);
    }

    return;
}
inline void combination(unsigned short number, unsigned short subNumber, unsigned short currNumber, unsigned short level, E_TYPE_COMBINATORICS type, unsigned short *comb)
{
    unsigned short factPrev = 0;
    unsigned short factAcc = 0;

    if(number>=subNumber && number>0)
    {
        for(unsigned short i=0;i<number-(currNumber-1)-(subNumber-level);i++)
        {
            factPrev = factorial(number-currNumber-i)/(factorial(subNumber-level)*factorial(number+level-(subNumber+currNumber+i)));
            for(unsigned short j=0;j<factPrev;j++)
            {
                comb[j*subNumber+subNumber*factAcc] = i+currNumber;
            }
            if(level < subNumber)
            {
                combination(number,subNumber,currNumber+1+i,level+1,type,comb+1+subNumber*factAcc);
            }
            factAcc += factPrev;
        }
    }

    return;
}
inline void ballsInBoxes(unsigned char balls, unsigned char boxes, unsigned short *comb)
{
    unsigned short numCombs = NoverM(balls+boxes-1,boxes-1);
    unsigned short totalSize = (numCombs+1)*boxes;
    unsigned short lastBox = 0;

    memset(comb,0,totalSize*sizeof(unsigned short));

    if(balls > 0 && boxes > 0)
    {
        unsigned short *localComb = (unsigned short *)malloc(totalSize*sizeof(unsigned short));

        combination(balls+boxes-1,boxes-1,1,1,ETC_NO_REPETITIION,localComb);

        for(unsigned short i=0;i<numCombs;i++)
        {
            sort(localComb+i*(boxes-1),boxes-1);
            lastBox = 0;
            for(unsigned short j=0;j<boxes-1;j++)
            {
                comb[i*boxes+j] = localComb[i*(boxes-1)+j] - lastBox - 1;
                lastBox = localComb[i*(boxes-1)+j];
            }
            //Valgrind says there is an invalid read here
            comb[(i+1)*boxes-1] = balls + boxes - 1 - localComb[i*(boxes-1)+boxes-1-1];
        }

        free(localComb);
    }

    return;
}
inline void expansion(unsigned short *exp, unsigned char rank, unsigned char val, ...)
{
    unsigned int dim = val;
    unsigned char *rankVector = (unsigned char *)malloc(rank*sizeof(unsigned char));
    unsigned char shift = 0;
    unsigned int counter = 1;

    va_list args;
    va_start(args,val);
    rankVector[0] = val;

    for(unsigned short i=1;i<rank;i++)
    {
        rankVector[i] = va_arg(args,int);
        dim *= rankVector[i];
    }
    va_end(args);

    memset(exp,0,dim*rank*sizeof(unsigned short));

    while(counter < dim)
    {
        memcpy(exp+counter*rank,exp+(counter-1)*rank,rank*sizeof(unsigned short));

        if(exp[counter*rank+shift]+1 < rankVector[shift])
        {
            exp[counter*rank+shift] += 1;
        }
        else
        {
            do
            {
                shift++;
            }
            while(exp[counter*rank+shift]+1 >= rankVector[shift]);
            exp[counter*rank+shift] += 1;
            //we reset the lower part of teh expansion
            memset(exp+counter*rank,0,shift*sizeof(unsigned short));
            shift = 0;
        }
        counter++;
    }
    free(rankVector);

    return;
}
inline unsigned int squarePow(unsigned int number)
{
    return (1<<number);
}
inline unsigned int logBase(unsigned int base, unsigned int n)
{
    unsigned int res = 0;

    if(base == 2)
    {
        const unsigned int b[] = {0x2, 0xC, 0xF0, 0xFF00, 0xFFFF0000};
        const unsigned int S[] = {1, 2, 4, 8, 16};
        int i;

        for (i = 4; i >= 0; i--) // unroll for speed...
        {
          if (n & b[i])
          {
            n >>= S[i];
            res |= S[i];
          }
        }
    }
    else if(base == 10)
    {


    }
    else
        res = (unsigned int)(log(n)/log(base));

    return res;
}
inline unsigned int getByteRepresentation(unsigned int number, unsigned char*& byteRep)
{
    unsigned int counter = 0;

    if(byteRep)
    {
        unsigned int remain = 0;
        unsigned int localDiv = 0;
        bool done = false;

        while(!done)
        {
            localDiv = number/256;
            remain = number - 256*(localDiv);
            byteRep[counter++] = remain;
            number = localDiv;
            done = number == 0;
        }
    }

    return counter;
}
inline float fastSqrt(float x)
{
    unsigned int t = *(unsigned int*)&x;

    t -= 0x3f800000;
    t >>= 1;
    t += 0x3f800000;

    return *(float*)&t;
}
inline unsigned int intSqrt(unsigned int number)
{
    unsigned int res = 0;

    unsigned int arrelTemp = 0;
    unsigned short bit = 1;
    unsigned char counter = 0;

    while(1)
    {
        if(static_cast<unsigned int>(bit<<counter)>=number)
        {
            break;
        }

        counter++;
    }

    res = squarePow(static_cast<unsigned int>(counter/2));
    bit = squarePow(static_cast<unsigned int>(counter/2));

    for(unsigned short j=static_cast<unsigned int>(counter/2);j>=0;j--)
    {
        arrelTemp = res | bit;
        if(arrelTemp*arrelTemp > number)
            arrelTemp = arrelTemp & ~bit;
        bit>>=1;
        res = arrelTemp;
    }

    return res;
}
inline void solveSeconGradeEq(float A, float B, float C, float rootA, float rootB)
{//here we solve a second grade equation given by: Ax^2 + Bx + C = 0

    rootA = (-B + sqrt(B*B - 4*A*C))*inv(2*A);
    rootB = (-B - sqrt(B*B - 4*A*C))*inv(2*A);

    return;
}
inline unsigned int gcd(unsigned int numberA, unsigned int numberB)
{
    unsigned int res = 0;
    if(numberA != numberB)
    {
        unsigned int a = (numberA > numberB) ? numberA : numberB;
        unsigned int b = (numberA < numberB) ? numberA : numberB;
        unsigned int remainder = 1;

        while(remainder != 0)
        {
            res = remainder;
            remainder = a%b;
            a = b;
            b = remainder;
        }
    }
    else
        res = numberA;

    return res;
}
inline unsigned int lcm(unsigned int numberA, unsigned int numberB)
{
    unsigned int res = 0;
    if(numberA != numberB)
    {
        unsigned int a = (numberA > numberB) ? numberA : numberB;
        unsigned int b = (numberA < numberB) ? numberA : numberB;

        res = (a/gcd(a,b))*b;
    }
    else
        res = numberA;

    return res;
}
inline unsigned int phiEuler(unsigned int n)
{
    unsigned int res = 1;

    for(unsigned short count = 2;count<n;count++)
        if(gcd(count,n)==1)
            res *= count;

    return res;
}
inline unsigned int mod(unsigned int p, int n)
{
    unsigned int res = 0;

    while(n<0)
        n += p;

    n %= p;

    return res;
}
inline bool isPrime(unsigned int n)
{
    bool res = true;
    bool sortir = false;
    unsigned int s = 0;
    unsigned int r = 0;
    unsigned int a = 0;
    unsigned int y = 0;
    unsigned short j = 0;
    unsigned int temp = n-1;
    unsigned int counter;

    while(temp%2==0)
        temp /= 2;
    r = temp;
    s = (n-1)/temp;

    for(unsigned char k=0;k<20&&!sortir;k++)
    {
        a = 2 + rand()%(n-2);
        y = a;
        counter = 0;
        while(counter < r-1)
        {
            y *= a;
            y %= n;
            counter++;
        }
        if(y!=1 && y!=n-1)
        {
            j = 1;
            while(j <= s-1 && y != n-1 && !sortir)
            {
                y = (y*y)%n;
                if(y == 1)
                {
                    sortir = true;
                    res = false;
                }
                else
                    j++;
            }
            if(y != n-1)
            {
                res = false;
                sortir = true;
            }
        }
    }

    return res;
}
inline double fastExp(double a)
{
    const double expA = 1048576/M_LN2;
    const double expB = 6081;
    union expUnion
    {
            double d;
            struct
            {
#ifdef LITTLE_ENDIAN
                int j, i;
#else
                int i, j;
#endif
            } n;
    } res;

    //remember that in unions the space of memory reserved for it can be named by, in this case, d and i,j
    res.n.j = 0;
    res.n.i = (int)(expA*a + (1072692348 - expB));

    return res.d;
}
inline double fastPow(double a, double b)
{
    union
    {
            double d;
            struct
            {
#ifdef LITTLE_ENDIAN
                int j, i;
#else
                int i, j;
#endif
            } n;
    }res;

    //remember that in unions the space of memory reserved for it can be named by, in this case, d and i,j
    res = {a};
    res.n.i = (int)(b * (res.n.i - 1072632447) + 1072632447);
    res.n.j = 0;

    return res.d;
}

}//namespace math

//general case
template<typename T>
inline T max(T a, T b, ...)
{
    return (a < b) ? b : a;
}
template<typename T>
inline T min(T a, T b, ...)
{
    return (a < b) ? a : b;
}

}//namespace yame
