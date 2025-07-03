/*=========================================================================================================*/
/* Código desenvolvido por: Gustavo Olsson Felchner, Chan Hong Lik, Nicolas Lisboa Lemke, Aliny Ventura do Nascimento da Silva*/
#include "trabalho3.h"
#include <stdlib.h>

/*=========================================================================================================*/
/*Protótipos das funções utilizadas:*/
Rect encontraRect(unsigned char** dados, int y, int x);
int encontraLeft(unsigned char** dados, int y, int x);
int encontraRight(unsigned char** dados, int y, int x);
int encontraBottom(unsigned char** dados, int y, int x);
void preencherFuro(unsigned char** dados, int y, int x, int* ymax, int* xmax, int* xmin);
unsigned char** copiaDados(Imagem1C* mask);
void destroiCopia(unsigned char** dados, int altura);
/*=========================================================================================================*/
Rect* encontraFuros(Imagem1C* mask, int* n_furos) {
    unsigned char** dados_copia;
    dados_copia = copiaDados(mask); // Copia de mask para ser utilizada como referencia

    int furos = 0;
    Rect* retangulos;

    for(int y = 1; y < mask->altura; y++) {
        for(int x = 1; x < mask->largura; x++) {
            if(dados_copia[y][x] > 127) { //se for furo
                furos++;
                if(furos == 1)
                    retangulos = (Rect*) malloc (sizeof(Rect));
                else
                    retangulos = (Rect*) realloc(retangulos, sizeof(Rect)*furos);

                retangulos[furos-1] = encontraRect(dados_copia, y, x);

            }
        }
    }

    *n_furos = furos;

    if(furos == 0)
        return NULL;

    destroiCopia(dados_copia, mask->altura);
    return retangulos;
}

Rect encontraRect(unsigned char** dados, int y, int x) {
    Rect retangulo;
    int ymax = -1, xmax = 0, xmin = -1;

    Coordenada tl, br;
    preencherFuro(dados, y, x, &ymax, &xmax, &xmin);

    tl.y = y; //    y do ponto já é o y máximo
    tl.x = xmin;
    br.y = ymax;
    br.x = xmax;

    retangulo.tl = tl;
    retangulo.br = br;


    return retangulo;
}

void preencherFuro(unsigned char** dados, int y, int x, int* ymax, int* xmax, int* xmin) {
    if(dados[y][x] > 127){ //verificando se é furo
        if(x > *xmax)
            *xmax = x;
        if(x < *xmin || *xmin == -1)
            *xmin = x;
        if(y > *ymax || *ymax == -1)
            *ymax = y;

        dados[y][x] = 0;
        preencherFuro(dados, y-1, x, ymax, xmax, xmin);
        preencherFuro(dados, y+1, x, ymax, xmax, xmin);
        preencherFuro(dados, y, x+1, ymax, xmax, xmin);
        preencherFuro(dados, y, x-1, ymax, xmax, xmin);

    }
}

unsigned char** copiaDados(Imagem1C* mask) {
    unsigned char** copia = malloc(sizeof(unsigned char*) * mask->altura);
        for(int i = 0; i < mask->altura; i++) {
            copia[i] = malloc(sizeof(unsigned char) * mask->largura);
            for(int j = 0; j < mask->largura; j++) {
                copia[i][j] = mask->dados[i][j];
            }
        }
    return copia;
}

void destroiCopia(unsigned char** dados, int altura) {
    for(int i = 0; i < altura; i++) {
        free(dados[i]);
    }
    free(dados);
}
