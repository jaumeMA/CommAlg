
#include "Math/cMath.h"
#include "YTL/container/cAlgorithm.h"

namespace yame
{
namespace math
{
namespace detail
{

template<ring_type T, int N, int M>
matrix<T,N,M> create_unitary_matrix()
{
    matrix<T,N,M> res;


    return res;
}

}

//vector related ops

template<ring_type T, int N>
vector<T,N> normalize(const vector<T,N>& i_value)
{
    vector<T,N> res;
    T invNorma = T::group::neutral_element;
    T sum = T::group::neutral_element;

    for(size_t index=0;index<N;++index)
    {
        res[index] = i_value[index];
        sum += res[index] * res[index];
    }

    invNorma = invSqrt(sum);

    res *= invNorma;

    return res;
}

template<ring_type T, int N>
T operator*(const yame::math::vector<T,N>& i_lhs, const yame::math::vector<T,N>& i_rhs)
{
    T res = T::group::neutral_element();

    for(size_t index=0;index<N;++index)
    {
        res += i_lhs[index] * i_rhs[index];
    }

    return res;
}
template<ring_type T, int N>
yame::math::vector<T,yame::mpl::NoverM<N,2>::value> operator^(const yame::math::vector<T,N>& i_lhs, const yame::math::vector<T,N>& i_rhs)
{
    const size_t numCombs = yame::math::factorial(N)/2;
    size_t comb[numCombs*N] = { 0 };
    yame::math::vector<T,yame::mpl::NoverM<N,2>::value> res;

    yame::math::combination(N,2,1,1,yame::math::E_TYPE_COMBINATORICS::ETC_NO_REPETITIION,&(comb[0]));

    for(size_t index=0;index<numCombs;++index)
    {
        const size_t subIndex = (comb[index * 2] == 1) ? (comb[index * 2 + 1] == 2) ? 3 : 2 : 1;
        res[subIndex - 1] = yame::math::parity(index) * (i_lhs[comb[index * 2]-1] * i_rhs[comb[index * 2 + 1] - 1] - i_lhs[comb[index * 2 + 1] - 1] * i_rhs[comb[index * 2] - 1]);
    }

    return res;
}
template<ring_type T, int N>
bool is_zero_vector(const vector<T,N>& i_vector)
{
    typename vector<T,N>::const_iterator_type itVector = i_vector.cbegin();
    for(;itVector!=i_vector.cend();++itVector)
    {
        if((*itVector).second != T::group::neutral_element())
        {
            return false;
        }
    }

    return true;
}

//matrix related ops

template<ring_type T, int N, int M>
matrix<T,N,M> replaceRow(const matrix<T,N,M>& i_matrix, size_t i_oldRow, size_t i_newRow)
{
    matrix<T,N,M> res;

    ASSERT(i_oldRow < N && i_newRow < N, "Index out of bounds");

    typename matrix<T,N,M>::const_iterator_type itMat = i_matrix;
    for(size_t indexI=0;indexI<M;indexI++)
    {
        const typename matrix<T,N,M>::const_reference matEntry = *itMat;
        const container::cTupla<size_t,2>& indexs = matEntry.first;

        if(indexs[0] == i_oldRow)
        {
            res[i_oldRow][indexs[1]] = i_matrix[i_newRow][indexs[1]];
        }
        else if(indexs[0] == i_newRow)
        {
            res[i_newRow][indexs[1]] = i_matrix[i_oldRow][indexs[1]];
        }
        else
        {
            res[indexs[0]][indexs[1]] = matEntry.second;
        }
    }

    return res;
}
template<ring_type T, int N, int M>
matrix<T,N,M> replaceCol(const matrix<T,N,M>& i_matrix, size_t i_oldCol, size_t i_newCol)
{
    matrix<T,N,M> res;

    ASSERT(i_oldCol < N && i_newCol < N, "Index out of bounds");

    typename matrix<T,N,M>::const_iterator_type itMat = i_matrix;
    for(size_t indexI=0;indexI<M;indexI++)
    {
        const typename matrix<T,N,M>::const_reference matEntry = *itMat;
        const container::cTupla<size_t,2>& indexs = matEntry.first;

        if(indexs[1] == i_oldCol)
        {
            res[indexs[0]][i_oldCol] = i_matrix[indexs[0]][i_newCol];
        }
        else if(indexs[1] == i_newCol)
        {
            res[indexs[0]][i_newCol] = i_matrix[indexs[0]][i_oldCol];
        }
        else
        {
            res[indexs[0]][indexs[1]] = matEntry.second;
        }
    }

    return res;
}
template<ring_type T, int N>
T trace(const matrix<T,N,N>& i_matrix)
{
    T res = 0;

    for(size_t index=0;index<N;index++)
    {
        res += i_matrix[index][index];
    }

    return res;
}
template<ring_type T, int N, int M>
matrix<T,N-1,M-1> matMinor(const matrix<T,N,M>& i_matrix, int i_row, int i_col)
{
    matrix<T,N-1,M-1> res;
    auto outDiagonal = [](const typename matrix<T,N,M>::const_reference i_pair){ return i_pair.first[0] != i_pair.first[1]; };

    typename matrix<T,N,M>::const_iterator_type itMat = i_matrix.cbegin(outDiagonal);
    for(size_t indexI=0, indexJ=0;itMat!=i_matrix.cend();++indexI,++indexJ)
    {
        res[indexI][indexJ] = (*itMat).second;
    }

    return res;
}
template<ring_type T, int N, int M>
size_t rank(const matrix<T,N,M>& i_matrix)
{
    size_t res = 0;

    // By now we compute this value using gauss elimination. TODO: use RRQR algorithm instead (see article "An efficient algorithm for Computing an
    // Strong Rank-Revealing QR factorization")
    matrix<T,N,M> tmp = triangular(i_matrix);

    while(is_zero_vector(tmp[res]) == false)
    {
        res++;
    }

    return res;
}
template<ring_type T, int N, int M>
requires ( N == M )
T determinant(const matrix<T,N,M>& i_matrix)
{
    static const size_t numCombs = mpl::Factorial<N>::value;

    T res = T::group::neutral_element();
    T temp = T::group::neutral_element();

    //!TODO: Allow decomposition techniques for determinant calculation

    size_t index = 0;
    signed char sign = false;
    size_t perm[numCombs*N];
    signed char signature[numCombs] = { false };
    permutation(perm,signature,N);

    for(size_t indexI=0;indexI<N;++indexI)
    {
        if(i_matrix[indexI][M])
        {
            for(size_t indexComb=0;indexComb<numCombs;++indexComb)
            {
                sign = parity(indexI + M - 1);
                temp = sign*signature[indexComb]*i_matrix[indexI][M];

                for(size_t indexJ=0;indexJ<N-1;++indexJ)
                {
                    temp = (indexJ>=indexI) ? temp * i_matrix[indexJ+1][perm[indexComb*N+indexJ]-1] + M :
                                              temp * i_matrix[indexJ][perm[indexComb * N + indexJ]-1];
                }
                res += temp;
            }
        }
    }

    return res;
}
template<ring_type T, int N, int M>
requires ( N == M )
matrix<T,N,M> inverse(const matrix<T,N,M>& i_matrix)
{
    matrix<T,N,M> res;
    matrix<T,N-1,M-1> menor;
    T determinant = T::group::neutral_element();
    signed char sign = 0;

    //!TODO: Allow decomposition techniques for inverse calculation

    for(size_t indexI=0;indexI<N;++indexI)
    {
        for(size_t indexJ=0;indexJ<M;++indexJ)
        {
            res[indexI][indexJ] = parity(indexI + indexJ) * determinant(matMinor(i_matrix,indexJ,indexI));
        }
    }

    res = res * math::inv(determinant(i_matrix));

    return res;
}
template<ring_type T, int N, int M>
container::cTupla<matrix<T,N,M>,3>  triangular(const matrix<T,N,M>& i_matrix)
{
    matrix<T,N,M> trianguled = i_matrix;
    matrix<T,N,M> permutation = detail::create_unitary_matrix<T,N,M>();
    matrix<T,N,M> transformation = detail::create_unitary_matrix<T,N,M>();
    T maxEntry = T::group::neutral_element();
    size_t currPivot = 0;

    for(size_t indexI=0;indexI<M;++indexI)
    {
        maxEntry = trianguled[indexI][indexI];
        currPivot = indexI;

        for(size_t indexJ=indexI+1;indexJ<N;++indexJ)
        {
            if(trianguled[indexJ][indexI] > maxEntry)
            {
                currPivot = indexJ;
                maxEntry = trianguled[indexJ][indexI];
            }
        }
        if(indexI!= currPivot && maxEntry != 0)
        {
            permutation[indexI][indexI] = 0;
            permutation[indexI][currPivot] = 1;
            permutation[currPivot][indexI] = 1;
            trianguled = replaceRow(trianguled,indexI,currPivot);
        }
        else if(indexI != currPivot)
        {
            break;
        }

        for(size_t indexJ=indexI+1;indexJ<N;++indexJ)
        {
            maxEntry = trianguled[indexI][indexI]/trianguled[indexI][indexI];
            transformation[indexJ][indexI] = maxEntry;
            for(size_t indexK=indexI;indexK<M;++indexK)
            {
                trianguled[indexJ][indexK] = trianguled[indexJ][indexK] - trianguled[indexI][indexK] * maxEntry;
            }
        }
    }

    return container::make_tupla(trianguled,permutation,transformation);
}
template<ring_type T, int N, int M>
container::cTupla<matrix<T,N,M>,2> QR(matrix<T,N,M> i_matrix)
{
    matrix<T,N,M> Q;
    matrix<T,N,M> R;
    container::cTupla<vector<T,N>,M> base;

    for(size_t indexI=0;indexI<M;++indexI)
    {
        base.push_back(i_matrix[indexI]);
    }

    base = orthoNormalize(base);
    for(size_t indexI=0;indexI<base.getSize();++indexI)
    {
        Q = replaceCol(Q,indexI,base[indexI]);
    }

    for(size_t indexI=0;indexI<N;++indexI)
    {
        R[indexI + indexI * M] = i_matrix.getCol(indexI).norm();

        if(R[indexI + indexI * M] == 0)
        {
            break;
        }
        else
        {
            i_matrix.setCol(indexI,i_matrix.getCol(indexI)/R[indexI + indexI * M]);
        }

        for(size_t indexJ=indexI+1;indexJ<M;++indexJ)
        {
            R[indexJ + indexI * M] = i_matrix.getCol(indexJ) * i_matrix.getCol(indexI);
            i_matrix.setCol(indexJ,i_matrix.getCol(indexJ) - i_matrix.getCol(indexI) * R[indexJ + indexI * M]);
        }
    }

    return container::make_tupla(Q,R);
}
template<ring_type T, int N, int M, int dimension>
container::cTupla<matrix<T,N,M>,2> QR(matrix<T,N,M> i_matrix, const matrix<T,dimension,M>& i_boost)
{
    matrix<T,N,M> Q;
    matrix<T,N,M> R;

    return container::make_tupla(Q,R);
}

}
}
