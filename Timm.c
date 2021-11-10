#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "TImg.h"
#include "TStack.h"
#include "TStckpt.h"
#include "Timm.h"

// declaração das funções auxiliares (por questões de organização, optei por manter as funções auxiliares ao fim do código)
void verify_format(char argv[], char aux[]); // função auxiliar de verificação de extensão;
TImg *read_imm_file(char file[]); // função auxiliar de leitura de arquivos em formato imm;
TImg *read_txt_file(char file[]); // função auxiliar de leitura de arquivos em formato txt;
int write_imm(TImg *img, char *file); // função auxiliar de escrita em arquivos imm;
int write_text(TImg *img, char *file); // função auxiliar de escrita em arquivos txt;
int seg_conv_2(char *file, char *bin, int thr); // função auxiliar de segmentação/conversão de arquivos imm/txt;
int find_cc(char *file1, char *file2); // função auxiliar para localização de componentes conexos de uma imagem;
int lab_escape(char *file1, char *file2); // função auxiliar para localização da saída de uma imagem-labirinto;

// início das funções primárias

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
    int i = seg_conv_2(file, bin, NULL_CODE); 
    if(!i){
        return SUCCESS;
    }else{
        return INVALID_FORMAT_FILE;
    }
}

int imm_segment(char *file, char *file2, int thr){
    char f[4];
    int i = seg_conv_2(file, file2, thr);
    if(!i){
        return SUCCESS;
    }else{
        return INVALID_FORMAT_FILE;
    }
}

int imm_cc(char *file1, char *file2){ 
    int i = find_cc(file1, file2);
    if(!i){
        return SUCCESS;
    }else{
        return INVALID_FORMAT_FILE;
    }
}

int imm_lab(char *file1, char *file2){
    int i = lab_escape(file1, file2);
    if(!i){
        return SUCCESS;
    }else{
        return INVALID_FORMAT_FILE;
    }
}

//  inicio das funções auxiliares;

void verify_format(char *argv, char *aux){
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

TImg *read_txt_file(char *file){ // funcao de abrir um arquivo de texto;
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
        else if((p == '\t' || p == EOF || p == '\n')){ // casos onde foi encontrado o espaçamento de pixel, ou o fim do arquivo, o caso de EOF é verificado pois o ultimo pixel ficaria sem ser setado caso contrario ( ler comentario ao lado do while);
            if(val == 3 || val == 4){
                v1 = value[0] - '0'; v2 = value[1] - '0'; v3 = value[2] - '0';  // casos onde se leu 3 caracteres de pixel;
            }
            else if(val == 2){
                v1 = 0; v2 = value[0] - '0'; v3 = value[1] - '0'; // casos onde se leu 2 caracteres de pixel;
            }
            else if(val == 1){
                v1 = 0; v2 = 0; v3 = value[0] - '0'; // casos onde se leu apenas 1 caractere de pixel;
            }
            v4 = (v1*100) + (v2*10) + v3; // os pixels foram lidos como caractere, então deve-se convertê-los novamente ao seu valor de acordo com a casa decimal;            
            img_set_value(img, i, j, v4);
            val = 0;
            value[0] = '0'; value[1] = '0'; value[2] = '0';  // zerando o vetor novamente para que o proximo pixel nao seja afetado(casos onde o pixel possui valor menor à 100, por exemplo);
            j++; // incrementando as colunas;
        }
    }
    fclose(tf);
    return img;
}

TImg *read_imm_file(char *file){ 
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

int seg_conv_2(char *file, char *file2, int thr){ //esta funcao tambem é utilizada na convert, com um valor thr de limiarização nulo, definido como NULL_CODE, que não sofre limiarização;
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
    char f2[4];
    verify_format(file2, f2);
    if(!strcmp(f2, "imm"))
        write_imm(aux, file2);
    else if(!strcmp(f2, "txt"))
        write_text(aux, file2);
    img_free(aux);  // desalocando o TADImg auxiliar;
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
    for(i = 1; i < lin-1; i++){   // for percorrendo a imagem da esquerda para a direita, de cima para baixo em busca de componentes conexos;
        for(j = 1; j < col-1; j++){ // variaveis começando em 1 e controle de for com -1, 
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
    verify_format(file2, f2);   // verificação do formato especificado no arquivo de saida para fazer a escrita;
    if(!strcmp(f2, "txt")){
        write_text(rot, file2); // caso de escrita em arquivo texto;
    }else if(!strcmp(f2, "imm")){
        write_imm(rot, file2);  // caso de escrita em arquivo binário;
    }
    else{
        return INVALID_FORMAT_FILE;
    }
    stckpt_free(cc); // desalocando a pilha utilizada;
    img_free(img);  // desalocando a imagem original utilizada;
    img_free(rot);  // desalocando a imagem rotulada utilizada;
    return SUCCESS;
}

int lab_escape(char *file1, char *file2){
    char f[4];
    TImg *img = NULL, *lab = NULL; // img de imagem original, rot de imagem rotulada;
    TStckpt *lab_esc = stckpt_create();
    point pt;
    verify_format(file1, f);  // verificando o formato do nome especificado para arquivo de saida(se for .imm, abre um arquivo para escrita em binario, se nao, em texto)
    if(!strcmp(f, "txt")){  // caso de segmentacao de txt para txt;
        img = read_txt_file(file1);
    }else if(!strcmp(f, "imm")){   // caso de segmentacao de txt para imm;
        img = read_imm_file(file1);
    }
    if(img == NULL){ // se o file1 não for nem txt nem imm, vai entrar neste if e retornar erro;
        return INVALID_NULL_POINTER;
    }
    int lin = img_get_line(img), col = img_get_columns(img); // variaveis para inicialização da imagem de escape do labirinto;
    lab = img_create(lin, col);
    if(lab == NULL){
        return INVALID_NULL_POINTER;
    }
    int value = 0, cima = 0, baixo = 0, esquerda = 0, direita = 0, label = 2; // variaveis de utilização no for;
    int v1= 0, v2 = 0, v3 = 0, v4 = 0, it = 0;
    for(int i = 0; i < lin; i++){ // for em busca da entrada do labirinto, percorrendo apenas a primeira coluna;
        img_get_value(img, i, 0, &value); // lendo o primeiro valor de cada linha;
        if(value == 1){
            img_set_value(img, i, 0, label); // como é o primeiro pixel, já é inserido na imagem com escape do labirinto;
            stckpt_push(lab_esc, pt); // adicionando o pixel de entrada do labirinto na pilha;
            img_set_value(img, i, 1, label); // adicionando o segundo ponto na pilha automatico por ja saber que o labirinto segue à esquerda;
            stckpt_push(lab_esc, pt);
            while((pt.j)+1 != col){ // enquanto não encontra o pixel de saida, localizado na ultima coluna, o while percorre todos os caminhos;
                stckpt_top(lab_esc, &pt);
                img_get_value(img, (pt.i)-1, pt.j, &cima); // verificação de vizinhos do pixel adicionado na pilha;
                img_get_value(lab, (pt.i)-1, pt.j, &v1); // verificação de pixel já lido na imagem com escape do labirinto;
                img_get_value(img, (pt.i)+1, pt.j, &baixo); // verificação de vizinhos do pixel adicionado na pilha;
                img_get_value(lab, (pt.i)+1, pt.j, &v2); // verificação de pixel já lido na imagem com escape do labirinto;
                img_get_value(img, pt.i, (pt.j)-1, &esquerda); // verificação de vizinhos do pixel adicionado na pilha;
                img_get_value(lab, pt.i, (pt.j)-1, &v3); // verificação de pixel já lido na imagem com escape do labirinto;
                img_get_value(img, pt.i, (pt.j)+1, &direita); // verificação de vizinhos do pixel adicionado na pilha;
                img_get_value(lab, pt.i, (pt.j)+1, &v4); // verificação de pixel já lido na imagem com escape do labirinto;
                if(cima == 1 && v1 == 0){ // se o pixel vizinho acima tem valor 1 na imagem original, sua posição é inserida na pilha;
                    pt.i -= 1;
                    img_set_value(img, pt.i, pt.j, label);
                    img_set_value(lab, pt.i, pt.j, label);
                    stckpt_push(lab_esc, pt);
                    break;
                }
                if(baixo == 1 && v2 == 0){ // se o pixel vizinho abaixo tem valor 1 na imagem original, sua posição é inserida na pilha;
                    pt.i += 1;
                    img_set_value(img, pt.i, pt.j, label);
                    img_set_value(lab, pt.i, pt.j, label);
                    stckpt_push(lab_esc, pt);
                    break;
                }
                if(esquerda == 1 && v3 == 0){ // se o pixel vizinho à esquerda tem valor 1 na imagem original, sua posição é inserida na pilha;
                    pt.j -= 1;
                    img_set_value(img, pt.i, pt.j, label);
                    img_set_value(lab, pt.i, pt.j, label);
                    stckpt_push(lab_esc, pt);
                    break;
                }
                if(direita == 1 && v4 == 0){ // se o pixel vizinho à direita tem valor 1 na imagem original, sua posição é inserida na pilha;
                    pt.j += 1;
                    img_set_value(img, pt.i, pt.j, label);
                    img_set_value(lab, pt.i, pt.j, label);
                    stckpt_push(lab_esc, pt);
                    break;
                }
                stckpt_pop(lab_esc); // removendo o beco sem saida da pilha;
            } // while
        } // if
    } // for
    char f2[4];
    verify_format(file2, f2); // verificação do formato do arquivo à ser criado, para chamar a função de escrita correta;
    if(!strcmp(f2, "txt")){
        write_text(img, file2); // escrita em texto;
    }else if(!strcmp(f2, "imm")){
        write_imm(img, file2);  // escrita em imm;
    }
    else{
        return INVALID_FORMAT_FILE; // caso o nome especificado não seja no formato compativel, retorna codigo de erro;
    }
    stckpt_free(lab_esc); // liberando a memoria alocada para a pilha auxiliar;
    img_free(img); // liberando memoria da imagem auxiliar com a imagem original;
    img_free(lab); // liberando memoria da imagem auxiliar com o escape do labirinto;

    return SUCCESS;
}