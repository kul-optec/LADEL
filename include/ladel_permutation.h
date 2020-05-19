#ifndef LADEL_PERMUTATION_H
#define LADEL_PERMUTATION_H

#include "ladel_types.h"

void ladel_permute_vector(ladel_double *x, ladel_int *p, ladel_int size, ladel_double *y);

void ladel_inverse_permute_vector(ladel_double *x, ladel_int *pinv, ladel_int size, ladel_double *y);

void ladel_invert_permutation_vector(ladel_int *p, ladel_int *pinv, ladel_int size);

void ladel_permute_symmetric_matrix(ladel_sparse_matrix *M, ladel_int *p, ladel_sparse_matrix *Mpp, ladel_work* work);

void ladel_permute_sparse_vector(ladel_sparse_matrix *x, ladel_int col, ladel_int *p, ladel_work *work);

#endif /*LADEL_PERMUTATION_H*/