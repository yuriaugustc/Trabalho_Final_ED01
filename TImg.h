#ifndef _TImgh_
#define _TImgh_

#define SUCCESS 0
#define INVALID_NULL_POINTER -1
#define OUT_OF_MEMORY -2
#define OUT_OF_RANGE -3
#define ELEM_NOT_FOUND -4
#define EMPTY_FILE -5

typedef struct TImg TImg; 

TImg *img_create(int nrows, int ncolumns);
int img_free(TImg *mat);

int img_set_value(TImg *mat, int i, int j, int val);
int img_get_value(TImg *mat, int i, int j, int *val);
int img_set_random(TImg *mat);
TImg *img_sum_2_mat(TImg *mat1, TImg *mat2);
TImg *img_mult_2_mat(TImg *mat1, TImg *mat2);
TImg *img_mult_mat_const(TImg *mat1, int value);
int img_find_trace(TImg *mat1);
int img_sum_lines(TImg *mat);
int img_sum_columns(TImg *mat);
int img_get_line(TImg *mat);
int img_get_columns(TImg *mat);
void img_print_matrix(TImg *mat);

#endif