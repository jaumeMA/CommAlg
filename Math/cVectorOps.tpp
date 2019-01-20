
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
//template<ring_type T, int N>
//bool is_zero_vector(const vector<T,N>& i_vector)
//{
//    typename vector<T,N>::const_iterator_type itVector = i_vector.cbegin();
//    for(;itVector!=i_vector.cend();++itVector)
//    {
//        if((*itVector).second != T::group::neutral_element())
//        {
//            return false;
//        }
//    }
//
//    return true;
//}
//
////matrix related ops
//
//template<ring_type T, int N, int M>
//matrix<T,N,M> replaceRow(const matrix<T,N,M>& i_matrix)
//{
//
//}
//template<ring_type T, int N, int M>
//matrix<T,N,M> replaceCol(const matrix<T,N,M>& i_matrix)
//{
//
//}
//template<ring_type T, int N>
//T trace(const matrix<T,N,N>& i_matrix)
//{
//    T res = 0;
//
//    for(size_t index=0;index<N;index++)
//    {
//        res += i_matrix[index][index];
//    }
//
//    return res;
//}
//template<ring_type T, int N, int M>
//matrix<T,N-1,M-1> matMinor(const matrix<T,N,M>& i_matrix, int i_row, int i_col)
//{
//    matrix<T,N-1,M-1> res;
//    size_t indexI, indexJ = 0;
//
//    for(size_t i=0;i<N;i++)
//    {
//        indexJ = 0;
//        for(u8 j=0;j<cols;j++)
//        {
//            if(i == i_row || j == i_col)
//            {
//                continue;
//            }
//
//            res[indexI][indexJ] = (*this)[i][j];
//            indexJ++;
//        }
//        indexI++;
//    }
//
//    return res;
//}
//template<ring_type T, int N, int M>
//size_t rank(const matrix<T,N,M>& i_matrix)
//{
//    size_t res = 0;
//
//    // By now we compute this value using gauss elimination. TODO: use RRQR algorithm instead (see article "An efficient algorithm for Computing an
//    // Strong Rank-Revealing QR factorization")
//    matrix<T,N,M> tmp = triangular(i_matrix);
//
//    if(N >= M)
//    {
//        while(is_zero_vector(tmp[res]) == false)
//        {
//            res++;
//        }
//    }
//    else
//    {
//        while(is_zero_vector(tmp[res]) == false)
//        {
//            res++;
//        }
//    }
//
//    return res;
//}
//template<ring_type T, int N, int M>
//requires ( N == M )
//T determinant(const matrix<T,N,M>& i_matrix)
//{
//    T res = T::group::neutral_element();
//    T temp = T::group::neutral_element();
//
//    //!TODO: Allow decomposition techniques for determinant calculation
//
//    size_t row[N];
//    size_t index = 0;
//    signed char sign = false;
//    size_t numCombs = factorial(N);
//    size_t perm[numCombs*N];
//    signed char signature[numCombs] = { false };
//    permutation(perm,signature,N);
//
//    for(size_t i=1;i<=N;i++)
//    {
//        row[i-1] = i*M - 1;
//    }
//
//    for(size_t z=0;z<N;z++)
//    {
//        if(mat[z][cols])
//        {
//            for(size_t j=0;j<numCombs;j++)
//            {
//                sign = parity(z + M - 1);
//                temp = sign*signature[j]*mat[z][cols];
//                for(u8 i=0;i<N-1;i++)
//                {
//                    temp = (i>=z) ? temp*mat[i+1][perm[j*N+i]-1] + M : temp*mat[i][perm[j*N+i]-1];
//                }
//                res += temp;
//            }
//        }
//    }
//
//    return res;
//}
//template<ring_type T, int N, int M>
//requires ( N == M )
//matrix<T,N,M> inverse(const matrix<T,N,M>& i_matrix)
//{
//    matrix<T,N,M> res;
//    matrix<T,N-1,M-1> menor;
//    T determinant = T::group::neutral_element();
//    signed char sign = 0;
//
//    //!TODO: Allow decomposition techniques for inverse calculation
//
//    if(N > 1)
//    {
//        for(size_t i=0;i<N;i++)
//        {
//            for(size_t j=0;j<M;j++)
//            {
//                res[i][j] = parity(i+j) * determinant(matMinor(i_matrix,j,i));
//            }
//        }
//
//        res = res*math::inv(determinant(i_matrix));
//    }
//    else if(N == 1)
//    {
//        res[0][0] = math::inv(i_matrix[0][0]);
//    }
//
//    return res;
//}
//template<ring_type T, int N, int M>
//container::cTupla<matrix<T,N,M>,3>  triangular(const matrix<T,N,M>& i_matrix)
//{
//    matrix<T,N,M> trianguled = i_matrix;
//    matrix<T,N,M> permutation = detail::create_unitary_matrix<T,N,M>();
//    matrix<T,N,M> transformation = detail::create_unitary_matrix<T,N,M>();
//    T maxEntry = T::group::neutral_element();
//    size_t currPivot = 0;
//
//    for(size_t i=0;i<M;i++)
//    {
//        maxEntry = i_matrix[i][i];
//        currPivot = i;
//
//        for(size_t k=i+1;k<N;k++)
//        {
//            if(i_matrix[k][i] > maxEntry)
//            {
//                currPivot = k;
//                maxEntry = i_matrix[k][i];
//            }
//        }
//        if(i!= currPivot && maxEntry != 0)
//        {
//            permutation[i][i] = 0;
//            permutation[i][currPivot] = 1;
//            permutation[currPivot][i] = 1;
//            trianguled = replaceRow(trianguled,i,currPivot);
//        }
//        else if(i!= currPivot)
//        {
//            break;
//        }
//
//        for(u8 j=i+1;j<rows;j++)
//        {
//            maxEntry = mat[j][i]/mat[i][i];
//            transformation[j][i] = maxEntry;
//            for(u8 k=i;k<cols;k++)
//            {
//                mat[j][k] = mat[j][k] - mat[i][k]*maxEntry;
//            }
//        }
//    }
//
//    return container::make_tupla(trianguled,permutation,transformation);
//}
//template<ring_type T, int N, int M>
//container::cTupla<matrix<T,N,M>,2> QR(const matrix<T,N,M>& i_matrix)
//{
//    matrix<T,N,M> Q;
//    matrix<T,N,M> R;
//    container::cTupla<vector<T,N>,M> base;
//
//    //be, resulta que es pot demostrar que Q no es mes que la matriu formada pels vectors columna de mat ortonormalitzats XD
//    for(size_t i=0;i<M;i++)
//    {
//        base.push_back(mat[i]);
//    }
//
//    base = orthoNormalize(base);
//    for(u8 i=0;i<base.getSize();i++)
//    {
//        Q = replaceCol(Q,i,base[i]);
//    }
//
//    for(size_t i=0;i<N;i++)
//    {
//        R[i+i*mat.cols] = mat.getCol(i).norm();
//        if(R[i+i*mat.cols] == 0)
//        {
//            break;
//        }
//        else
//        {
//            mat.setCol(i,mat.getCol(i)/R[i+i*mat.cols]);
//        }
//
//        for(u8 j=i+1;j<mat.cols;j++)
//        {
//            R[j+i*mat.cols] = mat.getCol(j)*mat.getCol(i);
//            mat.setCol(j,mat.getCol(j)-mat.getCol(i)*R[j+i*mat.cols]);
//        }
//    }
//
//    return;
//}
//template<ring_type T, int N, int M, int dimension>
//container::cTupla<matrix<T,N,M>,2> QR(const matrix<T,N,M>& i_matrix, const matrix<T,dimension,M>& i_boost)
//{
//
//}

}
}
