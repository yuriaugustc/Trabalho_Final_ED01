#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "TImg.h"

int main(){
    TImg *mat, *mat1, *mat2;
    int line, column, aux;
    int value;

    printf("Initalizing the matrices in memory...\n");
    Sleep(2200);
    mat = img_create(2,3);
    if(mat != NULL)
        printf("Everything went well with the first matrix(2,3) :D Yaay!\n\n");
    else
        printf("Something went wrong with the first(2,3) matrix :(\n\n");
    Sleep(2200);
    mat1 = img_create(3,2);
    if(mat1 != NULL)
        printf("Everything went well with the second matrix(3,2) :D Yaay!\n\n");
    else
        printf("Something went wrong with the second matrix(3,2) :(\n\n");
    Sleep(2200);
    mat2 = img_create(1,5);
        if(mat2 != NULL)
        printf("Everything went well with the third matrix(1,5) :D Yaay!\n\n");
    else
        printf("Something went wrong with the third matrix(1,5) :(\n\n");
    Sleep(2200);
    printf("Now let's give randoms values to the matrices...\n\n");
    Sleep(2200);
    aux = img_set_random(mat);
    if(aux == 0)
        printf("The first matrix's random fill was a success :) Yaay!\n\n");
    else
        printf("Something went wrong with first matrix's random fill :(\n\n");
    Sleep(2200);
    aux = img_set_random(mat1);
    if(aux == 0)
        printf("The second matrix's random fill was a success :) Yaay!\n\n");
    else
        printf("Something went wrong with second matrix's random fill :(\n\n");
    Sleep(2200);
    aux = img_set_random(mat2);
    if(aux == 0)
        printf("The third matrix's random fill was a success :) Yaay!\n\n");
    else
        printf("Something went wrong with third matrix's random fill :(\n\n");
    Sleep(500);
    printf("Let's see the values...");
    Sleep(1500);
    printf("\n\nMatrix number 1:\n");
    img_print_matrix(mat);
    Sleep(2200);
    printf("\n\nMatrix number 2:\n");
    img_print_matrix(mat1);
    Sleep(2200);
    printf("\n\nMatrix number 3:\n");
    img_print_matrix(mat2);
    printf("\n\n");
    Sleep(2200);
    printf("let's do now some few changes...\n\n");
    Sleep(2200);
    printf("Choose some position in matrix 1 to change (choose a line and next a column): ");
    scanf("%d%d", &line, &column);
    printf("Now choose some value to overwrite: ");
    scanf("%d", &value);
    aux = img_set_value(mat,line,column, value);
    Sleep(2200);
    printf("Let's see now if it got right: \n\n");
    Sleep(1000);
    if(aux == 0){
        printf("Did work! Let's see the change: \n");
        img_print_matrix(mat);
    }
    else
        printf("Ops... You don't code so well as you think :(\n\n");
    Sleep(2200);
    printf("\nSo... after all basic tests have been success, let's now try the operations.\n\n");
    Sleep(2200);
    printf("We will now sum the first matrix with the second, expecting a error, because they aren't the same size.\n");
    Sleep(5000);
    TImg *sum = img_sum_2_mat(mat, mat1);
    if(sum == NULL)
        printf("Yes! It fails with success! That's weird, but happier! XD\n");
    else
        printf("Ops... This test should go wrong, but he got right, I'm confused. :s\n");
    Sleep(2200);
    printf("\nAfter so many confused success, let's try the really operation. Let's create a matrix with same size as third matrix.\n");
    Sleep(5000);
    TImg *a = mat2; 
    sum = img_sum_2_mat(mat2, a);
    if(sum == NULL)
        printf("In that case, the operation should goes right. this is bad :/\n ");
    else
        printf("Yaay, did work! Let's see the matrix to analise:\n");
    Sleep(1000);
    img_print_matrix(sum);
    printf("\nLet's take advantage and test the destroy function.\n");
    aux = img_free(a);
    if(aux == 0)
        printf("Yeah, It's working.\n");
    else
        printf("Shit, didin't work.\n");
    img_free(sum);
    Sleep(2000);
    printf("\nNow let's try the multiplication:\n");
    printf("Sending first and second matrix to test, expecting success this time.\n");
    Sleep(2000); 
    TImg *mult = img_mult_2_mat(mat, mat1);
    if(mult == NULL)
        printf("\nThis is bad :/\n ");
    else
        printf("\nOkay, working. That function give me much hardship. Let's analise: \n");
    img_print_matrix(mult);
    img_free(mult);
    printf("\n\nMoving foward, we will multiplie a matrix by a constant.\n");
    Sleep(2200);
    printf("\nPic a number to multiplie by the second matrix: ");
    scanf("%d", &value);
    TImg *mul = img_mult_mat_const(mat1, value);
    printf("\nNow let's see the result: \n");
    img_print_matrix(mul);
    img_free(mul);
    printf("\nLet's find the trace of first matrix:\n");
    double trace = img_find_trace(mat);
    if(trace != -1)
        printf("\nSeeing the result: %d\n", trace);
    else
        printf("\nSome went wrong, you should give up. :/\n");
    Sleep(2000);
    printf("\nLet's find now the second matrix's lines sum:\n");
    double lines = img_sum_lines(mat1);
    if(lines != -1)
        printf("\nSeeing the result: %d\n", lines);
    else
        printf("\nSome went wrong, you won't made of that. :x\n");
    Sleep(2000);
    printf("\nLet's find now the second matrix's columns sum:\n");
    double columns = img_sum_columns(mat1);
    if(columns != -1)
        printf("\nSeeing the result: %d\n", columns);
    else
        printf("\nYou should rethink of your college. :/\n");
    Sleep(2000);
    printf("\nLet's find now the third matrix's lines number:\n");
    int gline = img_get_line(mat2);
    if(gline != -1)
        printf("\nSeeing the result: %d\n", gline);
    else
        printf("\nYou are suck coding, something got wrong. -.-\n");
    Sleep(2000);
    printf("\nLet's find now the third matrix's columns number:\n");
    int gcolumn = img_get_columns(mat2);
    if(gcolumn != -1)
        printf("\nSeeing the result: %d\n", gcolumn);
    else
        printf("\nOMG you are the worst, missing something like that... .-.\n");
    Sleep(2000);
    printf("\nFinally, we finished! Let's deallocate the matrices and go home XD\n");
    Sleep(4000);
    printf("\nDeallocating the first matrix...\n");
    Sleep(2000);
    aux = img_free(mat);
    if(aux == 0)
        printf("\nFirst matrix deallocate with success! ;)\n");
    else
        printf("\nIt didn't work. You are suck even this, omg... X(\n");
    Sleep(2000);
    printf("\nDeallocating the second matrix...\n");
    Sleep(2000);
    aux = img_free(mat1);
    if(aux == 0)
        printf("\nSecond matrix deallocate with success! ;)\n");
    else
        printf("\nIt didn't work. You are suck even this, omg... X(\n");
    Sleep(2000);
    printf("\nDeallocating the third matrix...\n");
    Sleep(2000);
    aux = img_free(mat2);
    if(aux == 0)
        printf("\nThird matrix deallocate with success! ;)\n");
    else
        printf("\nIt didn't work. You are suck even this, omg... X(\n");
    Sleep(2000);
    printf("\n\nThat's all folks! \n");
    Sleep(1500);
    return 0;
}