/**
 * @file ladel_submatrix.h
 * @author Ben Hermans
 * @brief Routines to produce submatrices from a given submatrix. For now, only a selection of columns is supported.
 */

#ifndef LADEL_SUBMATRIX_H
#define LADEL_SUBMATRIX_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "ladel_types.h"

/**
 * Returns a matrix that is a selection of columns of @a M, that is @f$out = M(:,cols)@f$.
 * 
 * @param M         Input matrix
 * @param cols      List of columns to put in the submatrix
 * @param nb_cols   Number of columns to take (size of cols)
 * @return          @f$M(:,cols)@f$
 */ 
ladel_sparse_matrix *ladel_column_submatrix(const ladel_sparse_matrix *M, 
                                            const ladel_int           *cols, 
                                            ladel_int                 nb_cols);

#ifdef __cplusplus
}
#endif 

#endif /* LADEL_SUBMATRIX_H */