#include <stdio.h>
#include <stdlib.h>
#include "TMat2D.h"

struct TMat2D
{
  int nrows; // number of lines
  int ncolumns; // number of columns
  int *data; // ponteir to matrices's data;
};

/*  Descripition: This function initializes and allocates memory space foo the matrix whose line and column were passed to the criation;
 *  Input: ((int)Number of lines, (int)number of columns)
 *  Output: A pointer to the first element of matrix created;
 */
TMat2D *mat2D_create(int nrows, int ncolumns){
    TMat2D *mat;
    mat = malloc(sizeof(TMat2D));
    if (mat != NULL){
        mat->data = malloc(nrows*ncolumns*sizeof(int));
        if (mat->data != NULL){
            mat->ncolumns = ncolumns;
            mat->nrows = nrows;
            for(int i = 0; i < (ncolumns*nrows); i++)
                mat->data[i] = 0;
        } else {
            free(mat);
            return NULL;
        }
    }
    return mat;
}

/*  Descripition: This function overwrite the content of position passed;
 *  Input: (Matrix's pointer selected to inserction, line, column, (int) the value to overwrite);
 *  Output: A int that confirm or not if the command was a success;
 *          (0 = success; -1 = fail);
 */
int mat2D_set_value(TMat2D *mat, int i, int j, int val){
    int aux = (i*j)-1; // take away -1 because the vector initializes in 0, and that the user don't need to know ;) ; 
    if(mat[aux].data != NULL){
        mat->data[aux] = val;
        return SUCCESS;
    }
    else
        return INVALID_NULL_POINTER;
}

TMat2D *mat2d_increase_size(TMat2D *mat, int i, int j){
    if(mat == NULL)
        return INVALID_NULL_POINTER;
    if (i<=0)
        return INVALID_NULL_POINTER;
    if (j<=0)
        return INVALID_NULL_POINTER;
    TMat2D *aux = mat2D_create(i, j);
    for(int k=0;i<mat->nrows;i++){
        for(int f=0;j<mat->ncolumns;j++){
            int a = getvalue(mat,k,f);  //créditos: LucasAlvesUfu;
            setvalue(aux,k,f,a);
        }
    }
    mat = aux;
    free(aux);
    return mat;
}

/*  Descripition: This function return the value of requisited position;
 *  Input: (Matrix's pointer selected to inserction, line, column, (int) the value to overwrite);
 *  Output: the value of requisited position;
 */
int mat2D_get_value(TMat2D *mat, int i, int j, int *val){
    int aux = 0;
    if(i != j)
        aux = (i*j)-1; // take away -1 because the vector initializes in 0, and that the user don't need to know ;) ;
                        // but I got a problem with that -1 in position of same numeration of nrows e ncolumns, that's explain the if;  
    if(mat[i*j].data != NULL){
        return mat->data[aux];
    }
    else 
        return INVALID_NULL_POINTER;
}

/*  Descripition: This function sets random's content in matrix's positions;
 *  Input: (Matrix's pointer)
 *  Output: A int that confirm or not if the command was a success;
 *          (0 = success; -1 = fail);
 */
int mat2d_set_random(TMat2D *mat){

    for(int i = 0; i < (mat->nrows*mat->ncolumns); i++){
        mat->data[i] = (int) rand() * 5/1000;
    }
    return SUCCESS;
}

/*  Descripition: This function sum two matrices each other;
 *  Input: (Matrix'Pointer1 to sum, Matrix'Pointer2 to sum);
 *  Output: A Pointer to a new memory allocation with the sum's results;
 */
TMat2D *mat2d_sum_2_mat(TMat2D *mat1, TMat2D *mat2){
    TMat2D *sum;
    sum = mat2D_create(mat1->nrows, mat1->ncolumns);
    if((mat1->nrows == mat2->nrows) && (mat1->ncolumns == mat2->ncolumns)){
        for(int i = 0; i < (mat1->nrows*mat1->ncolumns); i++){
            sum->data[i] = mat1->data[i] + mat2->data[i];
        }
        return sum;
    }
    else
        return NULL;
}

/*  Descripition: This function multiplies two matrices each other, validating if that is possible;
 *  Input:(Matrix'Pointer1 to multiplie, Matrix'Pointer2 to multiplie);
 *  Output: A Pointer to a new memory allocation with the multiplie's results;
 */
TMat2D *mat2d_mult_2_mat(TMat2D *mat1, TMat2D *mat2){
    TMat2D *mult;
    if(mat1->ncolumns == mat2->nrows){
        mult = mat2D_create(mat1->nrows, mat2->ncolumns);
        for(int i = 1; i <= mat1->ncolumns; i++){
            for(int j = 1; j <= mat2->nrows; j++){
                mult->data[i-1] += mat1->data[(j*i)-1] * mat2->data[(i*j)-1];
            }
        }
    return mult;
    }
    else
        return NULL;
}

/*  Descripition: This function multiplies a matrix by a number;
 *  Input:(Matrix'Pointer1 to multiplie, value to multiplies each position of matrix);
 *  Output: A Pointer to a new memory allocation with the multiplie's results;
 */
TMat2D *mat2d_mult_mat_const(TMat2D *mat1, int value){
    TMat2D *mult;
    if(mat1 != NULL){
        mult = mat2D_create(mat1->nrows, mat1->ncolumns);
        for(int i = 0; i < (mat1->nrows*mat1->ncolumns); i++){
            mult->data[i] = mat1->data[i] * value;
        }
    return mult;
    }
    else
        return NULL;
}

/*  Descripition: This function get the value of matrix's trace;
 *  Input:(Matrix'Pointer1 to calculate);
 *  Output: matrix's trace value;
 */
int mat2d_find_trace(TMat2D *mat1){
    int value = 0;
    int aux = (mat1->nrows*mat1->ncolumns);

    if(mat1 != NULL){
        for(int i = 0; i < aux; i++){
            if(mat1->data[i*i] < aux)
                value += mat1->data[i*i];
        }
    return value;
    }
    else
        return INVALID_NULL_POINTER;
}

/*  Descripition: This function sum the value of matrix's lines;
 *  Input:(Matrix'Pointer1 to calculate);
 *  Output: matrix's lines value;
 */
int mat2d_sum_lines(TMat2D *mat){
    int aux = (mat->nrows*mat->ncolumns);
    int value = 0;

    if(mat != NULL){
        for(int i = 0; i < aux; i++){
            value += mat->data[i];
        }
        return value;
    }
    else
        return INVALID_NULL_POINTER;
}

/*  Descripition: This function sum the value of matrix's columns;
 *  Input:(Matrix'Pointer1 to calculate);
 *  Output: matrix's columns value;
 */
int mat2d_sum_columns(TMat2D *mat){
    int aux = (mat->nrows*mat->ncolumns);
    int value = 0.0;

    if(mat != NULL){
        for(int i = 0; i < aux; i++){
            value += mat->data[i];
        }
        return value;
    }
    else
        return INVALID_NULL_POINTER;
}

/*  Descripition: This function return the value of matrix's lines;
 *  Input:(Matrix'Pointer1 to calculate);
 *  Output: matrix's lines value;
 */
int mat2d_get_line(TMat2D *mat){
    if(mat != NULL)
        return mat->nrows;
    else
        return INVALID_NULL_POINTER;
}

/*  Descripition: This function return the value of matrix's columns;
 *  Input:(Matrix'Pointer1 to calculate);
 *  Output: matrix's columns value;
 */
int mat2d_get_columns(TMat2D *mat){
    if(mat != NULL)
        return mat->ncolumns;
    else
        return INVALID_NULL_POINTER;
}

/*  Descripition: This function print the content of matrix informed; 
 *  Input: The matrix's pointer;
 *  Output: The matrix's content; 
 */
void mat2d_print_matrix(TMat2D *mat){
    for(int i = 0; i < (mat->nrows*mat->ncolumns); i++){
        printf("%.2lf ", mat->data[i]);
    }
}

/*  Descripition: This function deallocate the matrix's memory; 
 *  Input: The matrix's pointer;
 *  Output: A int that confirm or not if the command was a success;
 *          (0 = success; -1 = fail)
 */
int mat2D_free(TMat2D *mat){
    if(mat == NULL){
        return INVALID_NULL_POINTER;
    }
    else{
        free(mat);
        return SUCCESS;
    }
}