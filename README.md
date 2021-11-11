# Trabalho_Final_ED01

Trabalho Final da matéria de Estrutura de Dados

Este Trabalho consiste em um programa operavel em linha de comando que trabalha com entrada e saida de imagens em tons de cinza, convertidas em arquivo de texto, 
visualizadas em forma de matriz com pixels de 0 à 255, sendo 0 um tom mais escuro e 255 um tom mais claro.

Este Trabalho tinha como objetivo implementar cinco funções, sendo as mesmas:
* imm - chamada do programa *

-open - Abrir e printar no console os valores lidos do arquivo, utilizando um TAD implementado durante a disciplina para trabalhar com matriz de forma linear, 
utilizando ponteiros e alocação dinâmica;

-convert - Converter um arquivo de entrada em um arquivo de saida especificado, como por exemplo, de .txt para .imm (.imm é a extensao que o programa 
interpretada arquivos binarios);

-segment - Realiza thresholding em uma imagem especificada;

-cc - Busca e rotula componentes conexos em uma imagem limiarizada;

-lab - Recebe uma imagem limiarizada(0 representa as paredes do labirinto e 1 o caminho percorrivel) contendo um labirinto e devolve um arquivo de imagem 
com o caminho de saida destacado em numeros 2;

O programa possui tratamento de erros, em casos de:

- comando nao existente escrito;
- arquivo não suportado;
- arquivos inexistentes;
- nomenclaturas erradas;


ERROS CONTIDOS NA ENTREGA FINAL:

- Modularização de Codigos: Funções contém códigos que deveria ser tratados em funções especificas. Funções devidamente organizadas têm apenas o especifico 
para o que a função foi criada inicialmente.
- comando -cc com problemas: Imagens com mais de 20 linhas sofrem modificação de posição de componentes conexos, são movidos uma coluna para a esquerda;
