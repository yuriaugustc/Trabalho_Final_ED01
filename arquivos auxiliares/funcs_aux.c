/*
    Arquivo para guardar funcoes criadas nao utilizadas que talvez venham a ser (ou nao)


void convert_dec_2_bin(int dec, int *bin){ //criei essa funcao achando que precisava converter para binario antes de usar fwrite ;-;
    int aux = 0, j = 0, vet[9];
    *bin = 0;
    while(dec != 0 && dec != 1){ // este while serve para achar a representação binaria, separando cada digito em uma posição do vetor para saber o tamanho do digito;
        aux = dec % 2;
        dec = dec / 2;
        vet[j] = aux;
        j++;
    }
    vet[j] = dec;
    for(int i = j; i >= 0; i--){    // este for serve para colocar os digitos em suas devidas casaa decimais;
        *bin += (vet[i] * trunc(pow(10, i)));  //truncate pois estava com problemas de arredondamento, por exemplo o caso 255 ficaria em 11111110;
    }
}

void convert_bin_2_dec(int bin, int *dec){ 
    int count = 0;
    int vet[9], i = 0;
    *dec = 0;
    while(bin > 9){         // laço para separar o digitos binarios e contá-los;
        count++;
        vet[i] = bin % 10;
        bin /= 10;
        i++;
    }
    vet[i] = bin;
    for(int j = 0; j <= i; j++){        // este for serve para potenciar os digitos separados devidamente em suas posicoes;
        *dec += (vet[j] * pow(2, j));
    }
}

*/