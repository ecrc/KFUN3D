#include <stdio.h>
#include <new>
#include <stddef.h>
#include "matrix.h"
#include "fio.h"

using namespace fun3d;

#ifdef __cplusplus
extern "C" {
#endif

void CXX_Walk_Int(char *l, const char *h, const size_t sz, unsigned int *b)
{
  walkfbuf<unsigned int>(l, h, sz, b);
}

void CXX_Walk_Double(char *l, const char *h, const size_t sz, double *b)
{
  walkfbuf<double>(l, h, sz, b);
}

void *CXX_Matrix_Init(const size_t nnodes, const size_t nedges, const unsigned int block_size, const unsigned int nthreads, const unsigned int *n0, const unsigned int *n1)
{
  Matrix *matrix = new Matrix(nnodes, block_size, nthreads, 1, 8);
  matrix->mesh2csr(nedges, n0, n1);
  return((void *)matrix);
}

void CXX_Matrix_Delete(void *ptr)
{
  Matrix *matrix = (Matrix *) ptr;
  delete matrix;
}

void CXX_METIS(const unsigned int nparts, unsigned int *parts, void *ptr)
{
  Matrix *matrix = (Matrix *) ptr;
  printf("Number of the edge cuts, generated by METIS is: %ld\n", matrix->csr2parts(nparts, parts));
}

void CXX_Fill_alpha(const unsigned int row, const unsigned int col, const double a, const double v[], void *ptr)
{
  Matrix *matrix = (Matrix *) ptr;
  matrix->fill(row, col, a, v);
}

void CXX_Fill(const unsigned int row, const unsigned int col, const double v[], void *ptr)
{
  Matrix *matrix = (Matrix *) ptr;
  matrix->fill(row, col, v);
}

void CXX_Fill_boundary(const unsigned int row, const unsigned int col, const unsigned int n, const double v[], void *ptr)
{
  Matrix *matrix = (Matrix *) ptr;
  matrix->fill(row, col, n, v);
}

void CXX_Fill_diagonal(const unsigned int row, const unsigned int col, const double v, void *ptr)
{
  Matrix *matrix = (Matrix *) ptr;
  matrix->fill(row, col, v);
}

void CXX_Fill_Reset(void *ptr)
{
  Matrix *matrix = (Matrix *) ptr;
  matrix->fill();
}

void CXX_ILU(void *ptr)
{
  Matrix *matrix = (Matrix *) ptr;
#if 0
  matrix->ilu_YousefSaad();
#else
  matrix->ilu_Edmond();
#endif
}

void CXX_SpTRSV(const double *b, double *x, void *ptr)
{
  Matrix *matrix = (Matrix *) ptr;

#if 0
  matrix->sptrsv_YousefSaad(b, x);
  matrix->sptrsv_Jacobi(b, x);
#else
  matrix->sptrsv_LevelScheduling(b, x);
#endif
}

#ifdef __cplusplus
}
#endif