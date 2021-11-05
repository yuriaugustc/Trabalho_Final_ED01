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

int convert_bin_2_txt(char *bin, char *file, int thr){  // funcao nao esta em pleno funcionamento, verificar o que houve;
    TImg *img = open_imm_file(bin);
    if(img == NULL){
        //printf("aqui fml");
        return INVALID_NULL_POINTER;
    }
    FILE *tf = fopen(file, "w");
    if(tf == NULL){
        //printf("nao, eh aqui fml");
        return INVALID_NULL_POINTER;
    }
    int value = 0, lin = 0, col = 0, i = 0, j = 0;                 
    lin = img_get_line(img);   // obtendo o numero de linhas do arquivo;
    col = img_get_columns(img); // obtendo o numero de colunas do arquivo;
    for(i = 0; i < lin; i++){   
        for(j = 0; j < col; j++){
            img_get_value(img, i, j, &value);
            if(thr == -1){  // re-utilização de codigo, -1 é um codigo nulo para o comando open utilizar a mesma funcao sem sofrer limiarizacao;
                fprintf(tf, "%d", value);
            }else{
                if(value > thr){   // thresholding : se é maior que thr, acessa o endereco de uma variavel com valor 1 e escreve no arquivo;
                    fprintf(tf, "1");    
                }
                else{     // thresholding : se é menor que thr, acessa o endereco de uma variavel com valor 0 e escreve no arquivo;
                    fprintf(tf, "0");
                }
            }
            if(j+1 != col)
                fprintf(tf,"\t"); // controle para separar os pixels por coluna e não acabar inserindo um \t na ultima coluna. Isso estava fazendo com que a impressao de um arquivo txt repetisse a ultima coluna;
        }
        if(i+1 != lin)
            fprintf(tf,"\n"); // controle para criar uma nova linha somente até a ultima linha do arquivo. Isso estava criando uma linha a mais durante a conversao;
    }
    img_free(img); // desalocando o TADImg;
    fclose(tf);  // fechando o arquivo;
    return SUCCESS;
}

int convert_txt_2_bin(char *file, char *bin, int thr){ // funcao nao esta em pleno funcionamento, verificar o que houve;
    int v0 = 0, v1 = 1;
    TImg *img = open_txt_file(file);
    if(img == NULL){
        return INVALID_NULL_POINTER;
    }
    FILE *bf = fopen(bin, "wb");
    if(bf == NULL){
        return INVALID_NULL_POINTER;
    }
    int lin = 0, col = 0, value = 0, i = 0, j = 0;                 
    lin = img_get_line(img);   // obtendo o numero de linhas do arquivo;
    fwrite(&lin, sizeof(int), 1, bf);  // inserindo o numero de linhas no inicio do arquivo binario;
    col = img_get_columns(img);  // obtendo o numero de colunas do arquivo;
    fwrite(&col, sizeof(int), 1, bf);  // inserindo o numero de colunas no inicio do arquivo binario;
    for(i = 0; i < lin; i++){   
        for(j = 0; j < col; j++){
            img_get_value(img, i, j, &value);
            if(thr == -1){   // re-utilização de codigo, -1 é codigo nulo para o comando open utilizar a mesma funcao sem sofrer limiarizacao;
                fwrite(&value, sizeof(int), 1, bf);
            }else{
                if(value > thr){    // thresholding : se é maior que thr, acessa o endereco de uma variavel com valor 1 e escreve no arquivo;
                    fwrite(&v1, sizeof(int), 1, bf);    // fiquei na duvida se caso eu inserisse dentro do fwrite o valor "1", se ele funcionaria ou se ele procuraria o que está no endereço 1;
                }else{   // thresholding : se é menor que thr, acessa o endereco de uma variavel com valor 0 e escreve no arquivo;
                    fwrite(&v0, sizeof(int), 1, bf);    // mesma duvida do fwrite anterior;
                }
            }
        }
    }
    img_free(img); // desalocando o TADImg;
    fclose(bf);  // fechando o arquivo;
    return SUCCESS;
}

*/