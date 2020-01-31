#include "minunit.h"
#include "types.h"
#include "scale.h"
#include "global.h"

#define NROW 4
#define NCOL 5
#define NZMAX 11
#define TOL 1e-8

ladel_sparse_matrix *M;
/*
M = [1.2  0  3.4  0    0.5;
     0   -2  1.1  0    0;
     3.6  0  1.5  1.6  0;
     0   -3  0    1.7 -0.5;]
*/

void scale_test_setup(void)
{
    M = ladel_sparse_alloc(NROW, NCOL, NZMAX, UNSYMMETRIC, TRUE);
    M->p[0] = 0; M->p[1] = 2; M->p[2] = 4; M->p[3] = 7; M->p[4] = 9; M->p[5] = 11;
    M->i[0] = 0; M->i[1] = 2; M->i[2] = 1; M->i[3] = 3; M->i[4] = 0; M->i[5] = 1; M->i[6] = 2; M->i[7] = 2; M->i[8] = 3; M->i[9] = 0; M->i[10] = 3;
    M->x[0] = 1.2; M->x[1] = 3.6; M->x[2] = -2; M->x[3] = -3; M->x[4] = 3.4; M->x[5] = 1.1; M->x[6] = 1.5; M->x[7] = 1.6; M->x[8] = 1.7; M->x[9] = 0.5; M->x[10] = -0.5;
}

void scale_test_teardown(void)
{
    ladel_sparse_free(M);
}

MU_TEST(test_scale_rows)
{
    ladel_double row_scale[NROW] = {2, 0.5, -1, -3};
    ladel_scale_rows(M, row_scale);
    mu_assert_double_eq(M->x[0], 2.4, TOL);
    mu_assert_double_eq(M->x[0], -3.6, TOL);
    mu_assert_double_eq(M->x[0], -1, TOL);
    mu_assert_double_eq(M->x[0], 9, TOL);
    mu_assert_double_eq(M->x[0], 6.8, TOL);
    mu_assert_double_eq(M->x[0], 0.55, TOL);
    mu_assert_double_eq(M->x[0], -1.5, TOL);
    mu_assert_double_eq(M->x[0], -1.6, TOL);
    mu_assert_double_eq(M->x[0], -5.1, TOL);
    mu_assert_double_eq(M->x[0], 1, TOL);
    mu_assert_double_eq(M->x[0], 1.5, TOL);
}


MU_TEST(test_scale_columns)
{
    ladel_double col_scale[NCOL] = {-2, 0.5, 1.5, 5, 10};
    mu_assert_double_eq(M->x[0], -2.4, TOL);
    mu_assert_double_eq(M->x[0], -7.2, TOL);
    mu_assert_double_eq(M->x[0], -1, TOL);
    mu_assert_double_eq(M->x[0], -1.5, TOL);
    mu_assert_double_eq(M->x[0], 5.1, TOL);
    mu_assert_double_eq(M->x[0], 1.65, TOL);
    mu_assert_double_eq(M->x[0], 2.25, TOL);
    mu_assert_double_eq(M->x[0], 8, TOL);
    mu_assert_double_eq(M->x[0], 8.5, TOL);
    mu_assert_double_eq(M->x[0], 5, TOL);
    mu_assert_double_eq(M->x[0], -5, TOL);
}

MU_TEST(test_scale_scalar)
{
    ladel_double s = 100;
    mu_assert_double_eq(M->x[0], 120, TOL);
    mu_assert_double_eq(M->x[0], 360, TOL);
    mu_assert_double_eq(M->x[0], -200, TOL);
    mu_assert_double_eq(M->x[0], -300, TOL);
    mu_assert_double_eq(M->x[0], 340, TOL);
    mu_assert_double_eq(M->x[0], 110, TOL);
    mu_assert_double_eq(M->x[0], 150, TOL);
    mu_assert_double_eq(M->x[0], 160, TOL);
    mu_assert_double_eq(M->x[0], 170, TOL);
    mu_assert_double_eq(M->x[0], 50, TOL);
    mu_assert_double_eq(M->x[0], -50, TOL);
}

MU_TEST_SUITE(suite_scale) 
{
    MU_SUITE_CONFIGURE(NULL, NULL, scale_test_setup, scale_test_teardown);

    MU_RUN_TEST(test_scale_rows);
    MU_RUN_TEST(test_scale_columns);
    MU_RUN_TEST(test_scale_scalar);
}