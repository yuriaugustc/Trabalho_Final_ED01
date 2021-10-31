#include <stdio.h>
#include <stdlib.h>
#include "TImg.h"

struct TImg
{
  int nrows; // number of lines
  int ncolumns; // number of columns
  unsigned int *data; // ponteir to matrices's data;
};

/*  Descripition: This function initializes and allocates memory space foo the matrix whose line and column were passed to the criation;
 *  Input: ((int)Number of lines, (int)number of columns)
 *  Output: A pointer to the first element of matrix created;
 */
TImg *img_create(int nrows, int ncolumns){
    if(nrows <= 0 || ncolumns <= 0){
        return NULL;
    }
    TImg *mat;
    mat = (TImg*) malloc(sizeof(TImg));
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
    return mat;
    }
    else{
        free(mat);
        return NULL;
    }
}

/*  Descripition: This function overwrite the content of position passed;
 *  Input: (Matrix's pointer selected to inserction, line, column, (int) the value to overwrite);
 *  Output: A int that confirm or not if the command was a success;
 *          (0 = success; -1 = fail);
 */
int img_set_value(TImg *mat, int i, int j, int val){
    if(mat == NULL){
        return INVALID_NULL_POINTER;
    }
    else{
        /*if(i == 0 && j != 0){
            i = 1;
        }
        if(j == 0 && i != 0){
            j = 1;
        }
        int aux = (i*j); */
        int a = i*mat->nrows+j;
        mat->data[a] = val;
        return SUCCESS;
    }
}

TImg *img_increase_size(TImg *mat, int i, int j){
    if(mat == NULL)
        return NULL;
    if (i<=0)
        return NULL;
    if (j<=0)
        return NULL;
    TImg *aux = img_create(i, j);
    for(int k = 0; k < mat->nrows; k++){
        for(int f = 0; f < mat->ncolumns; f++){
            int a; 
            img_get_value(mat, k, f, &a);
            img_set_value(aux, k, f, a);
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
int img_get_value(TImg *mat, int i, int j, int *val){
    if(mat != NULL){
        int aux = 0;
        i -= 1; // take away -1 because the vector initializes in 0, and that the user don't need to know ;) ;
        j -= 1; // take away -1 because the vector initializes in 0, and that the user don't need to know ;) ;
        aux = (i*j);   
        *val =  mat->data[aux];
        return SUCCESS;
    }
    else 
        return INVALID_NULL_POINTER;
}

/*  Descripition: This function sets random's content in matrix's positions;
 *  Input: (Matrix's pointer)
 *  Output: A int that confirm or not if the command was a success;
 *          (0 = success; -1 = fail);
 */
int img_set_random(TImg *mat){
    if(mat == NULL){
        return INVALID_NULL_POINTER;
    }
    else{
        for(int i = 0; i < (mat->nrows*mat->ncolumns); i++){
            mat->data[i] = (int) rand() * 5/1000;
        }
        return SUCCESS;
    }
}

/*  Descripition: This function sum two matrices each other;
 *  Input: (Matrix'Pointer1 to sum, Matrix'Pointer2 to sum);
 *  Output: A Pointer to a new memory allocation with the sum's results;
 */
TImg *img_sum_2_mat(TImg *mat1, TImg *mat2){
    TImg *sum;
    sum = img_create(mat1->nrows, mat1->ncolumns);
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
TImg *img_mult_2_mat(TImg *mat1, TImg *mat2){
    TImg *mult;
    if(mat1->ncolumns == mat2->nrows){
        mult = img_create(mat1->nrows, mat2->ncolumns);
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
TImg *img_mult_mat_const(TImg *mat1, int value){
    TImg *mult;
    if(mat1 != NULL){
        mult = img_create(mat1->nrows, mat1->ncolumns);
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
int img_find_trace(TImg *mat1){
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
int img_sum_lines(TImg *mat){
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
int img_sum_columns(TImg *mat){
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
int img_get_line(TImg *mat){
    if(mat != NULL)
        return mat->nrows;
    else
        return INVALID_NULL_POINTER;
}

/*  Descripition: This function return the value of matrix's columns;
 *  Input:(Matrix'Pointer1 to calculate);
 *  Output: matrix's columns value;
 */
int img_get_columns(TImg *mat){
    if(mat != NULL)
        return mat->ncolumns;
    else
        return INVALID_NULL_POINTER;
}

/*  Descripition: This function print the content of matrix informed; 
 *  Input: The matrix's pointer;
 *  Output: The matrix's content; 
 */
void img_print_matrix(TImg *mat){
    for(int i = 0; i < (mat->nrows*mat->ncolumns); i++){
       if(mat->data[i] == -1){
           printf("\n");
           i++;
       }
       printf("%d ", mat->data[i]);
    }
}

/*  Descripition: This function deallocate the matrix's memory; 
 *  Input: The matrix's pointer;
 *  Output: A int that confirm or not if the command was a success;
 *          (0 = success; -1 = fail)
 */
int img_free(TImg *mat){
    if(mat == NULL){
        return INVALID_NULL_POINTER;
    }
    else{
        free(mat);
        return SUCCESS;
    }
}