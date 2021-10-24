#ifndef _TMat2Dh_
#define _TMat2Dh_

#define SUCCESS 0
#define INVALID_NULL_POINTER -1
#define OUT_OF_MEMORY -2
#define OUT_OF_RANGE -3
#define ELEM_NOT_FOUND -4
#define EMPTY_FILE -5

typedef struct TMat2D TMat2D; 

TMat2D *mat2D_create(int nrows, int ncolumns);
int mat2D_free(TMat2D *mat);

int mat2D_set_value(TMat2D *mat, int i, int j, int val);
int mat2D_get_value(TMat2D *mat, int i, int j, int *val);
int mat2d_set_random(TMat2D *mat);
TMat2D *mat2d_sum_2_mat(TMat2D *mat1, TMat2D *mat2);
TMat2D *mat2d_mult_2_mat(TMat2D *mat1, TMat2D *mat2);
TMat2D *mat2d_mult_mat_const(TMat2D *mat1, int value);
int mat2d_find_trace(TMat2D *mat1);
int mat2d_sum_lines(TMat2D *mat);
int mat2d_sum_columns(TMat2D *mat);
int mat2d_get_line(TMat2D *mat);
int mat2d_get_columns(TMat2D *mat);
void mat2d_print_matrix(TMat2D *mat);

#endif