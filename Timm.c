#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "TImg.h"
#include "TStack.h"
#include "TStckpt.h"
#include "Timm.h"

void verify_format(char argv[], char aux[]); // função auxiliar de verificação de extensão;
TImg *read_imm_file(char file[]); // função auxiliar de leitura de arquivos em formato imm;
TImg *read_txt_file(char file[]); // função auxiliar de leitura de arquivos em formato txt;
int segment_2_imm(char *file, char *bin, int thr); // funcção auxiliar de segmentação/conversão de arquivos imm;
int segment_2_txt(char *file, char *bin, int thr); // funcção auxiliar de segmentação/conversão de arquivos txt;
int write_imm(TImg *img, char *file); // função auxiliar de escrita em arquivos imm;
int write_text(TImg *img, char *file); // função auxiliar de escrita em arquivos txt;
int find_cc(char *file1, char *file2); // função auxiliar para localização de componentes conexos de uma imagem;
int lab_escape(char *file1, char *file2); // função auxiliar para localização da saída de uma imagem-labirinto;

int imm_open_file(char *argv){
    char aux[4];
    verify_format(argv, aux);
    TImg *img;
    if(!strcmp(aux, "txt")){
        img = read_txt_file(argv); // criando a matriz a partir do arquivo.txt;
        if(img == NULL){ // se o file1 não for nem txt nem imm, vai entrar neste if e retornar erro;
            return INVALID_NULL_POINTER;
        }
        img_print_matrix(img); // printando a matriz utilizada;
        img_free(img); // desalocando a matriz utilizada;
        return SUCCESS;
    }
    else if(!strcmp(aux, "imm")){
        img = read_imm_file(argv); // criando a matriz a partir do arquivo.txt;
        if(img == NULL){ // se o file1 não for nem txt nem imm, vai entrar neste if e retornar erro;
            return INVALID_NULL_POINTER;
        }
        img_print_matrix(img); // printando a matriz utilizada;
        img_free(img); // desalocando a matriz utilizada;
        return SUCCESS;
    }
    else{
        return INVALID_FORMAT_FILE;
    }
}

int imm_convert(char *file, char *bin){
    char bin1[4];
    int i;
    verify_format(bin, bin1); // verificação da extensao do primeiro arquivo;
    if(!strcmp(bin1, "txt")){   // conversao de imm para txt, ou de txt para txt, a verificação da extensao do segundo arquivo ocorre dentro da funcao auxiliar;
        i = segment_2_txt(file, bin, NULL_CODE); // esta função está com nome de "segment" pois a função foi modularizada de forma a evitar repetição de codigo dentro do programa;
        if(!i){
            return SUCCESS;
        }else{
            return INVALID_FORMAT_FILE;
        }
    }
    else if(!strcmp(bin1, "imm")){  // conversao de imm para txt, ou de imm para imm, a verificação da extensao do segundo arquivo ocorre dentro da funcao auxiliar;
        i = segment_2_imm(file, bin, NULL_CODE); // esta função está com nome de "segment" pois a função foi modularizada de forma a evitar repetição de codigo dentro do programa;
        if(!i){
            return SUCCESS;
        }else{
            return INVALID_FORMAT_FILE;
        }
    }
    else{
        return INVALID_FORMAT_FILE;
    }
}

int imm_segment(char *file, char *file2, int thr){
    char f[4];
    int i;
    verify_format(file2, f);  // verificando o formato do primeiro arquivo, que servirá de base para limiarização;

    if(!strcmp(f, "txt")){  // segmentacao de txt para txt, ou de txt para imm, a verificação da extensao do segundo arquivo ocorre na função auxiliar;
        i = segment_2_txt(file, file2, thr);
        if(!i){
            return SUCCESS;
        }else{
            return INVALID_FORMAT_FILE;
        }
    }else if(!strcmp(f, "imm")){  // segmentacao de imm para imm, ou de imm para txt, a verificação da extensao do segundo arquivo ocorre na função auxiliar;
        i = segment_2_imm(file, file2, thr);
        if(!i){
            return SUCCESS;
        }else{
            return INVALID_FORMAT_FILE;
        }
    }
    else{
        return INVALID_FORMAT_FILE;
    }
    return SUCCESS;
}

int imm_cc(char *file1, char *file2){
    char f[4];
    int i = find_cc(file1, file2);
    if(!i){
        return SUCCESS;
    }else{
        return INVALID_FORMAT_FILE;
    }
}

int imm_lab(char *file1, char *file2){
    char f[4];
    int i;
    verify_format(file1, f);
    if(!strcmp(f, "txt")){

    } else if(!strcmp(f, "imm")){

    }
    printf("Okay, -lab labindo fora da main ;w;\n");
    return 0;
}

void verify_format(char argv[], char aux[]){
    TStack *st;
    st = stack_create();
    for(int i = 0; i < strlen(argv); i++){
        stack_push(st, argv[i]);
    }
    aux[3] = '\0';
    for(int i = 2; i >= 0; i--){
        stack_top(st, &aux[i]);
        stack_pop(st);
    }
    stack_free(st);
}

TImg *read_txt_file(char file[]){ // funcao de abrir um arquivo de texto;
    FILE *tf;
    TImg *img;
    tf = fopen(file, "r");
    if(tf == NULL){
        return NULL;
    }
    char p = '0';
    int lin = 0, col = 1;
    while(p != EOF){  // while rodando até o fim do arquivo para contar as linhas e colunas do arquivo para alocar o TAD de imagem;
        p = fgetc(tf);
        if(p == '\n' || p == EOF){  // verificacao de linhas;
            lin++; 
        }
        if(lin == 0 && p == '\t'){  // verificacao de colunas. Só será executado na primeira linha;
            col++;
        }
    }
    rewind(tf);
    img = img_create(lin, col);
    if(img == NULL){ // se o file1 não for nem txt nem imm, vai entrar neste if e retornar erro;
        return NULL;
    }
    char value[] = "000";
    int i = 0, j = 0, val = 0;
    int v1 = 0, v2 = 0, v3 = 0, v4 = 0; 
    p = '0';  // setando a variavel com zero para que a ultima leitura da variavel nao interfira no funcionamento do codigo;    
    while(p != EOF){  // o while verifica primeiro e depois lê o caractere;
        p = fgetc(tf);
        
        if((p != '\t' && p != EOF && p != '\n')){ // casos onde se leu caracteres de pixel;
            value[val] = p;
            val++;
        }
        if((p == '\t' || p == EOF || p == '\n')){ // casos onde foi encontrado o espaçamento de pixel, ou o fim do arquivo, o caso de EOF é verificado pois o ultimo pixel ficaria sem ser setado caso contrario ( ler comentario ao lado do while);
            if(val == 3 || val == 4){
                v1 = value[0] - '0'; v2 = value[1] - '0'; v3 = value[2] - '0';  // casos onde se leu 3 caracteres de pixel;
            }
            else if(val == 2){
                v1 = 0; v2 = value[0] - '0'; v3 = value[1] - '0'; // casos onde se leu 2 caracteres de pixel;
            }
            else if(val == 1){
                v1 = 0; v2 = 0; v3 = value[0] - '0'; // casos onde se leu apenas 1 caractere de pixel;
            }
            v4 = (v1*100) + (v2*10) + (v3*1); // os pixels foram lidos como caractere, então deve-se convertê-los novamente ao seu valor de acordo com a casa decimal;            
            img_set_value(img, i, j, v4);
            val = 0;
            value[0] = '0'; value[1] = '0'; value[2] = '0';  // zerando o vetor novamente para que o proximo pixel nao seja afetado(casos onde o pixel possui valor menor à 100, por exemplo);
            j++;
        }
    }
    fclose(tf);
    return img;
}

TImg *read_imm_file(char file[]){ 
    FILE *bf;
    bf = fopen(file, "rb");
    if(bf == NULL){
        return NULL;
    }
    int lin = 0;
    fread(&lin,sizeof(int), 1, bf);  // lendo o numero de linhas do arquivo binario, gravado por padrao no primeiro bloco de memoria do arquivo.
    int col = 0;
    fread(&col,sizeof(int), 1, bf);  // lendo o numero de colunas do arquivo binario, gravado por padrao no segundo bloco de memoria do arquivo;
    TImg *img = img_create(lin, col); 
    if(img == NULL){ // se o file1 não for nem txt nem imm, vai entrar neste if e retornar erro;
        return NULL;
    }
    int aux = 0, i = 0, j = 0;
    for(i = 0; i < lin; i++){
        for(j = 0; j < col; j++){
            fread(&aux,sizeof(int), 1, bf); // lendo o bloco de memoria correspondente ao pixel;
            img_set_value(img, i, j, aux);  // inserindo o numero decimal no tad de imagem;
        }
    }
    return img;
}

int write_imm(TImg *img, char *file){ // funcao modularizada de escrita em arquivo binario
    if(img == NULL){ // se o file1 não for nem txt nem imm, vai entrar neste if e retornar erro;
        return INVALID_NULL_POINTER;
    }
    FILE *bf = fopen(file, "wb");
    if(bf == NULL){
        return INVALID_NULL_POINTER;
    }
    int lin = 0, col = 0, value = 0, i = 0, j = 0;  // criando variaveis auxiliares de linha e colunas pois a originais estao sendo usadas no for aninhado;                 
    lin = img_get_line(img);  // obtendo o numero de linhas do arquivo;
    fwrite(&lin, sizeof(int), 1, bf); // inserindo o numero de linhas no inicio do arquivo binario;
    col = img_get_columns(img); // obtendo o numero de colunas do arquivo;
    fwrite(&col, sizeof(int), 1, bf); // inserindo o numero de colunas no inicio do arquivo binario;
    for(i = 0; i < lin; i++){   
        for(j = 0; j < col; j++){
            img_get_value(img, i, j, &value);
            fwrite(&value, sizeof(int), 1, bf);
        }
    }
    fclose(bf);
    return SUCCESS;
}

int write_text(TImg *img, char *file){ // funcao modularizada de escrita em arquivo texto
    if(img == NULL){ // se o file1 não for nem txt nem imm, vai entrar neste if e retornar erro;
        return INVALID_NULL_POINTER;
    }
    FILE *tf = fopen(file, "w");
    if(tf == NULL){
        return INVALID_NULL_POINTER;
    }
    int value = 0, lin = 0, col = 0, i = 0, j = 0;                 
    lin = img_get_line(img);   // obtendo o numero de linhas do arquivo;
    col = img_get_columns(img); // obtendo o numero de colunas do arquivo;
    for(i = 0; i < lin; i++){   
        for(j = 0; j < col; j++){
            img_get_value(img, i, j, &value);
            fprintf(tf, "%d", value);
            if(j+1 != col) // controle para separar os pixels por coluna e não acabar inserindo um \t na ultima coluna. Isso estava fazendo com que a impressao de um arquivo txt repetisse a ultima coluna;
                fprintf(tf,"\t");
        }
        if(i+1 != lin)
            fprintf(tf,"\n"); // controle para criar uma nova linha somente até a ultima linha do arquivo. Isso estava criando uma linha a mais durante a conversao;
    }
    fclose(tf);  // fechando o arquivo;
    return SUCCESS;
}

int segment_2_imm(char *file, char *file2, int thr){ //esta funcao tambem é utilizada na convert, com um valor thr de limiarização nulo, definido como NULL_CODE, que não sofre limiarização;
    char f[4];
    TImg *img = NULL, *aux = NULL;
    verify_format(file, f);  // verificando o formato do nome especificado para arquivo de saida(se for .imm, abre um arquivo para escrita em binario, se nao, em texto)
    if(!strcmp(f, "txt")){  // caso de conversao/segmentacao de imm para txt;
        img = read_txt_file(file);
    }else if(!strcmp(f, "imm")){   // caso de conversao/segmentacao de imm para imm;
        img = read_imm_file(file);
    }
    if(img == NULL){ // se o file1 não for nem txt nem imm, vai entrar neste if e retornar erro;
        return INVALID_NULL_POINTER;
    }
    int lin = 0, col = 0, value = 0, i = 0, j = 0;  // criando variaveis auxiliares de linha e colunas pois a originais estao sendo usadas no for aninhado;                 
    lin = img_get_line(img);  // obtendo o numero de linhas do arquivo;
    col = img_get_columns(img); // obtendo o numero de colunas do arquivo;
    aux = img_create(lin, col);
    if(aux == NULL){
        return INVALID_NULL_POINTER;
    }
    if(img == NULL){ // se o file1 não for nem txt nem imm, vai entrar neste if e retornar erro;
        return INVALID_NULL_POINTER;
    }
    for(i = 0; i < lin; i++){   
        for(j = 0; j < col; j++){
            img_get_value(img, i, j, &value);
            if(thr == NULL_CODE){     // re-utilização de codigo, NULL_CODE é codigo nulo para o comando convert utilizar a mesma funcao sem sofrer limiarizacao;
                img_set_value(aux, i, j, value);
            }else{
                if(value > thr){   // thresholding : se é maior que thr, escreve no arquivo o valor 1 no lugar do pixel;
                    img_set_value(aux, i, j, 1);
                }else{      // thresholding : se é menor que thr, escreve no arquivo o valor 0 no lugar do pixel;
                    img_set_value(aux, i, j, 0);
                }
            }
        }
    }
    write_imm(aux, file2); // funcao modularizada de escrita em arquivo binario;
    img_free(aux);  // desalocando o TADImg auxiliar;
    img_free(img); // desalocando o TADImg;
    return SUCCESS;
}

int segment_2_txt(char *file, char *file2, int thr){ //esta funcao tambem é utilizada na convert, com um valor thr de limiarização nulo, definido como NULL_CODE, que não sofre limiarização;
    char f[4];
    TImg *img = NULL, *aux = NULL;
    verify_format(file, f);  // verificando o formato do nome especificado para arquivo de saida(se for .imm, abre um arquivo para escrita em binario, se nao, em texto)
    if(!strcmp(f, "txt")){  // caso de segmentacao de txt para txt;
        img = read_txt_file(file);
    }else if(!strcmp(f, "imm")){   // caso de segmentacao de txt para imm;
        img = read_imm_file(file);
    }
    if(img == NULL){ // se o file1 não for nem txt nem imm, vai entrar neste if e retornar erro; //
        return INVALID_NULL_POINTER;
    }
    int value = 0, lin = 0, col = 0, i = 0, j = 0;                 
    lin = img_get_line(img);   // obtendo o numero de linhas do arquivo;
    col = img_get_columns(img); // obtendo o numero de colunas do arquivo;
    aux = img_create(lin, col);
    if(aux == NULL){
        return INVALID_NULL_POINTER;
    }
    for(i = 0; i < lin; i++){   
        for(j = 0; j < col; j++){
            img_get_value(img, i, j, &value);
            if(thr == NULL_CODE){  // re-utilização de codigo, NULL_CODE é um codigo nulo para o comando convert utilizar a mesma funcao sem sofrer limiarizacao;
                img_set_value(aux, i, j, value);
            }else{
                if(value > thr){   // thresholding : se é maior que thr, acessa o endereco de uma variavel com valor 1 e escreve no arquivo;
                    img_set_value(aux, i, j, 1);    
                }
                else{     // thresholding : se é menor que thr, acessa o endereco de uma variavel com valor 0 e escreve no arquivo;
                    img_set_value(aux, i, j, 0);
                }
            }
        }
    }
    write_text(aux, file2);
    img_free(aux);
    img_free(img); // desalocando o TADImg;
    return SUCCESS;
}

int find_cc(char *file1, char *file2){
    char f[4];
    TImg *img = NULL, *rot = NULL; // img de imagem original, rot de imagem rotulada;
    TStckpt *cc = stckpt_create();
    point pt, pt2;
    verify_format(file1, f);  // verificando o formato do nome especificado para arquivo de saida(se for .imm, abre um arquivo para escrita em binario, se nao, em texto)
    if(!strcmp(f, "txt")){  // caso de segmentacao de txt para txt;
        img = read_txt_file(file1);
    }else if(!strcmp(f, "imm")){   // caso de segmentacao de txt para imm;
        img = read_imm_file(file1);
    }
    if(img == NULL){ // se o file1 não for nem txt nem imm, vai entrar neste if e retornar erro;
        return INVALID_NULL_POINTER;
    }
    int value = 0, value2 = 0, lin = 0, col = 0, i = 0, j = 0, k = 1, label = 1, a = 0;
    int v1 = 0, v2 = 0, v3 = 0, v4 = 0; // variáveis auxiliares para receber valor das posições vizinhas ao ponto em analise;                 
    lin = img_get_line(img);   // obtendo o numero de linhas do arquivo;
    col = img_get_columns(img); // obtendo o numero de colunas do arquivo;
    rot = img_create(lin, col); // meu image_create já zera as posições por padrão;
    if(rot == NULL){
        return INVALID_NULL_POINTER;
    }
    for(i = 1; i < lin-1; i++){   
        for(j = 1; j < col-1; j++){
            img_get_value(img, i, j, &value);
            img_get_value(rot, i, j, &value2);
            if(value == 1 && value2 == 0){
                pt.i = i;
                pt.j = j;
                img_set_value(rot, i, j, label);
                stckpt_push(cc, pt);
                while(a != EMPTY_LIST){ // variavel "a" auxiliar para verificar se a pilha esta vazia ou nao;
                    a = stckpt_top(cc, &pt2);
                    a = stckpt_pop(cc);
                    while(k != -2){
                        img_get_value(img, (pt2.i)+k, pt2.j, &v1); // verifica os vizinhos horizontais na imagem orignal;
                        img_get_value(rot, (pt2.i)+k, pt2.j, &v2); // verifica os vizinhos horizontais na imagem rotulada;
                        img_get_value(img, pt2.i, (pt2.j)+k, &v3); // verifica os vizinhos verticais na imagem orignal;
                        img_get_value(rot, pt2.i, (pt2.j)+k, &v4); // verifica os vizinhos verticais na imagem rotulada;
                        if(v1 == 1 && v2 == 0){ // adiciona na pilha as cordenadas que são iguais à 1 na imagem original*; *se eu entendi direito, a segunda verificação é para nao se repetir posições;
                            pt2.i += k;
                            img_set_value(rot, pt2.i, pt2.j, label);
                            stckpt_push(cc, pt2);
                        }
                        if(v3 == 1 && v4 == 0){ // adiciona na pilha as cordenadas que são iguais à 1 na imagem original*; *se eu entendi direito, a segunda verificação é para nao se repetir posições;
                            pt2.j += k;
                            img_set_value(rot, pt2.i, pt2.j, label);
                            stckpt_push(cc, pt2);
                        }
                        k--;
                        if(k == 0){ // somando novamente a variavel k, para que o laço não acesse a posição em que já estamos trabalhando;
                            k--;
                        }
                    } // while
                    k = 1;
                } // while
                label++;
                a = 0;
            } // if
        }
    }
    char f2[4];
    verify_format(file2, f2);
    if(!strcmp(f2, "txt")){
        write_text(rot, file2);
    }else if(!strcmp(f2, "imm")){
        write_imm(rot, file2);
    }
    else{
        return INVALID_FORMAT_FILE;
    }
    stckpt_free(cc);
    img_free(img);
    img_free(rot);
    return SUCCESS;
}

/*int lab_escape(char *file1, char *file2){
    char f[4];
    TImg *img, *lab;
    TStckpt *labesc = stckpt_create();
    point pt, pt2;
    verify_format(file1, f);  // verificando o formato do nome especificado para arquivo de saida(se for .imm, abre um arquivo para escrita em binario, se nao, em texto)
    if(!strcmp(f, "txt")){  // caso de segmentacao de txt para txt;
        img = read_txt_file(file1);
    }else if(!strcmp(f, "imm")){   // caso de segmentacao de txt para imm;
        img = read_imm_file(file1);
    }
    if(img == NULL){ // se o file1 não for nem txt nem imm, vai entrar neste if e retornar erro;
        return INVALID_NULL_POINTER;
    }
    int value = 0, value2 = 0, lin = 0, col = 0, i = 0, j = 0, k = 1, label = 1, a = 0;
    int v1 = 0, v2 = 0, v3 = 0, v4 = 0; // variáveis auxiliares para receber valor das posições vizinhas ao ponto em analise;                 
    lin = img_get_line(img);   // obtendo o numero de linhas do arquivo;
    col = img_get_columns(img); // obtendo o numero de colunas do arquivo;
    lab = img_create(lin, col); // meu image_create já zera as posições por padrão;
    if(lab == NULL){
        return INVALID_NULL_POINTER;
    }
    for(j = 0; j < col; j++){   
        for(i = 0; i < lin; i++){
            img_get_value(img, i, j, &value);
            //img_get_value(lab, i, j, &value2);
            if(value == 1 && value2 == 0){
                pt.i = i;
                pt.j = j;
                img_set_value(lab, i, j, label);
                stckpt_push(labesc, pt);
                while(a != EMPTY_LIST){ // variavel "a" auxiliar para verificar se a pilha esta vazia ou nao;
                    a = stckpt_top(labesc, &pt2);
                    a = stckpt_pop(labesc);
                    while(k != -2){
                        img_get_value(img, (pt2.i)+k, pt2.j, &v1); // verifica os vizinhos horizontais na imagem orignal;
                        img_get_value(lab, (pt2.i)+k, pt2.j, &v2); // verifica os vizinhos horizontais na imagem rotulada;
                        img_get_value(img, pt2.i, (pt2.j)+k, &v3); // verifica os vizinhos verticais na imagem orignal;
                        img_get_value(lab, pt2.i, (pt2.j)+k, &v4); // verifica os vizinhos verticais na imagem rotulada;
                        if(v1 == 1 && v2 == 0){ // adiciona na pilha as cordenadas que são iguais à 1 na imagem original*; *se eu entendi direito, a segunda verificação é para nao se repetir posições;
                            pt2.i += k;
                            img_set_value(lab, pt2.i, pt2.j, label);
                            stckpt_push(labesc, pt2);
                        }
                        if(v3 == 1 && v4 == 0){ // adiciona na pilha as cordenadas que são iguais à 1 na imagem original*; *se eu entendi direito, a segunda verificação é para nao se repetir posições;
                            pt2.j += k;
                            img_set_value(lab, pt2.i, pt2.j, label);
                            stckpt_push(labesc, pt2);
                        }
                        k--;
                        if(k == 0){ // somando novamente a variavel k, para que o laço não acesse a posição em que já estamos trabalhando;
                            k--;
                        }
                    } // while
                    k = 1;
                } // while
                label++;
            } // if
        }
    }
    char f2[4];
    verify_format(file2, f2);
    if(!strcmp(f2, "txt")){
        write_text(lab, file2);
    }else if(!strcmp(f2, "imm")){
        write_imm(lab, file2);
    }
    else{
        return INVALID_FORMAT_FILE;
    }
    stckpt_free(labesc);
    img_free(img);
    img_free(lab);
    return SUCCESS;
}*/