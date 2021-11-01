#include <stdio.h>
#include <math.h>
#include <string.h>

int main(){

    printf("<< Conversor binário-decimal >>\n");
    printf("Entre com o numero de bits: \n");
    int dec = 255;
    int aux, bin = 0, j = 0;
    int v1[9];

    while(dec != 0 && dec != 1){
        aux = dec % 2;
        dec = dec / 2;
        v1[j] = aux;
        j++;
    }
    v1[j] = dec;
    for(int i = j; i >= 0; i--){
        bin += v1[i] * trunc(pow(10, i));
    }
    printf("numero binario: %d\n", bin);
    int count = 0;
    int vet[9], i = 0;
    dec = 0;
    while(bin > 9){ // laço para separar o digitos binarios e contá-los;
        count++;
        vet[i] = bin % 10;
        bin /= 10;
        i++;
    }
    vet[i] = bin;
    for(int j = 0; j <= i; j++){ // este for serve para potenciar os digitos separados devidamente em suas posicoes;
        dec += (vet[j] * pow(2, j));
    }
    printf("Em decimal novamente: %d", dec);
    return 0;
}