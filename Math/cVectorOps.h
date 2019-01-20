#pragma once

#include "Math/cVectorSpace.h"

namespace yame
{
namespace math
{
namespace detail
{

template<ring_type T, int N, int M>
matrix<T,N,M> create_unitary_matrix();

}

//vector related ops

template<ring_type T, int N>
static const vector<T,N> zero_vector;
template<ring_type T, int N>
static const vector<T,N> unitary_vector;

template<ring_type T, int N>
vector<T,N> normalize(const vector<T,N>& i_value);
template<ring_type T, int N>
T operator*(const vector<T,N>& i_lhs, const vector<T,N>& i_rhs);
template<ring_type T, int N>
vector<T,yame::mpl::NoverM<N,2>::value> operator^(const vector<T,N>& i_lhs, const vector<T,N>& i_rhs);
//template<ring_type T, int N>
//bool is_zero_vector(const vector<T,N>& i_vector);
//template<ring_type T, int N>
//container::cArray<vector<T,N>> orthoNormalize(const container::cArray<vector<T,N>>& i_base);
//
////matrix related ops
//
//template<ring_type T, int N, int M>
//matrix<T,N,M> replaceRow(const matrix<T,N,M>& i_matrix, size_t i_row, const vector<T,M>& i_newRow);
//template<ring_type T, int N, int M>
//matrix<T,N,M> replaceCol(const matrix<T,N,M>& i_matrix, size_t i_col, const vector<T,N>& i_newCol);
//template<ring_type T, int N>
//T trace(const matrix<T,N,N>& i_matrix);
//template<ring_type T, int N, int M>
//matrix<T,N-1,M-1> matMinor(const matrix<T,N,M>& i_matrix, int i_row, int i_col);
//template<ring_type T, int N, int M>
//size_t rank(const matrix<T,N,M>& i_matrix);
//template<ring_type T, int N, int M>
//T determinant(const matrix<T,N,M>& i_matrix);
//template<ring_type T, int N, int M>
//matrix<T,N,M> inverse(const matrix<T,N,M>& i_matrix);
//template<ring_type T, int N, int M>
//container::cTupla<matrix<T,N,M>,3>  triangular(const matrix<T,N,M>& i_matrix);
//template<ring_type T, int N, int M>
//container::cTupla<matrix<T,N,M>,2> QR(const matrix<T,N,M>& i_matrix);
//template<ring_type T, int N, int M, int dimension>
//container::cTupla<matrix<T,N,M>,2> QR(const matrix<T,N,M>& i_matrix, const matrix<T,dimension,M>& i_boost);
////void LUP(cMatrix<T,rows,cols> mat, cMatrix<T,rows,cols> &L, cMatrix<T,rows,cols> &U, cMatrix<T,rows,cols> &P);
////void LUP(cMatrix<T,rows,cols> &L, cMatrix<T,rows,cols> &U, cMatrix<T,rows,cols> &P);
////void LDU(cMatrix<T,rows,cols> mat, cMatrix<T,rows,cols> &L, cMatrix<T,rows,cols> &U, cMatrix<T,rows,cols> &D);
////void LDU(cMatrix<T,rows,cols> &L, cMatrix<T,rows,cols> &U, cMatrix<T,rows,cols> &D);
//template<ring_type T, int N, int M>
//matrix<T,N,M> Cholesky(const matrix<T,N,M>& i_matrix);
//template<ring_type T, int N, int M, int dimension>
//matrix<T,N,M> Cholesky(const matrix<T,N,M>& i_matrix, const matrix<T,dimension,M>& i_boost);
////static void SVD(cMatrix<T,rows,cols> mat, cMatrix<T,rows,rows> &U, cMatrix<T,rows,cols> &S, cMatrix<T,rows,cols> V);
////void SVD(cMatrix<T,rows,rows> &U, cMatrix<T,rows,cols> &S, cMatrix<T,rows,cols> V);
//template<ring_type T, int N, int M>
//container::cArray<container::cPair<double,vector<T,M>>> getEigen(const matrix<T,N,M>& i_matrix);
//template<ring_type T, int N>
//bool isPositive(const matrix<T,N,N>& i_matrix);
//template<ring_type T, int N, int M>
//bool isHermitian(const matrix<T,N,M>& i_matrix);

}
}

#include "Math/cVectorOps.tpp"
