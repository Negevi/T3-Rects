/*============================================================================*/
/* TRABALHO: BOUNDING BOXES DE FUROS                                          */
/*----------------------------------------------------------------------------*/
/* Autor: Bogdan T. Nassu                                                     */
/*============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include "trabalho3.h"

/*============================================================================*/

void gray2RGB (Imagem1C* in, Imagem3C* out);
void desenhaRect (Imagem3C* img, Rect rect);

/*============================================================================*/

char* ARQUIVOS [] =
{
    "img/1_furos.bmp",
    "img/2_furos.bmp",
    "img/3_furos.bmp",
    "img/4_furos.bmp",
    "img/5_furos.bmp",
    "img/6_furos.bmp",
    "img/7_furos.bmp",
    "img/8_furos.bmp",
    "img/9_furos.bmp",
    "img/10_furos.bmp",
};

#define N_ARQUIVOS 10

/*============================================================================*/

int main ()
{
    int i, i_teste, n_boxes;
    Imagem1C* img; // Imagem de entrada.
    Imagem3C* out; // Imagem de saída.
    Rect* bboxes; // Retângulos envolventes.
    char nome_saida [128]; // String usada para salvar as saídas.

    // Para cada arquivo...
    for (i_teste = 0; i_teste < N_ARQUIVOS; i_teste++)
    {
        printf ("%s\n", ARQUIVOS [i_teste]);
        img = abreImagem1C (ARQUIVOS [i_teste]);
        if (!img)
        {
            printf ("Nao conseguiu abrir %s\n", ARQUIVOS [i_teste]);
            return (1);
        }

        bboxes = encontraFuros (img, &n_boxes);

        // Mostra.
        out = criaImagem3C (img->largura, img->altura);
        gray2RGB (img, out);
        if (bboxes)
        {
            for (i = 0; i < n_boxes; i++)
                desenhaRect (out, bboxes [i]);
        }

        sprintf (nome_saida, "%d_furos.bmp", i_teste+1);
        salvaImagem3C (out, nome_saida);

        // Cleanup.
        destroiImagem3C (out);
        destroiImagem1C (img);
        if (bboxes)
            free (bboxes);
    }

    return (0);
}

/*----------------------------------------------------------------------------*/
/*** Converte uma imagem em escala de cinza para RGB. */

void gray2RGB (Imagem1C* in, Imagem3C* out)
{
    int i, j, channel;

    for (channel = 0; channel < 3; channel++)
        for (i = 0; i < in->altura; i++)
            for (j = 0; j < in->largura; j++)
                out->dados [channel][i][j] = in->dados [i][j];
}

/*----------------------------------------------------------------------------*/
/*** Desenha um rect na imagem. CUIDADO: não testa se as coordenadas são
  válidas! */

void desenhaRect (Imagem3C* img, Rect rect)
{
    int i;

    // Top/Bottom.
    for (i = rect.tl.x; i <= rect.br.x; i++)
    {
        img->dados [0][rect.tl.y][i] = 255;
        img->dados [1][rect.tl.y][i] = 0;
        img->dados [2][rect.tl.y][i] = 0;

        img->dados [0][rect.br.y][i] = 255;
        img->dados [1][rect.br.y][i] = 0;
        img->dados [2][rect.br.y][i] = 0;
    }

    // Left/Right.
    for (i = rect.tl.y; i <= rect.br.y; i++)
    {
        img->dados [0][i][rect.tl.x] = 255;
        img->dados [1][i][rect.tl.x] = 0;
        img->dados [2][i][rect.tl.x] = 0;

        img->dados [0][i][rect.br.x] = 255;
        img->dados [1][i][rect.br.x] = 0;
        img->dados [2][i][rect.br.x] = 0;
    }
}

/*============================================================================*/

