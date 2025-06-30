/*============================================================================*/
/* DETERMINA OS RETÂNGULOS ENVOLVENTES DE BLOBS EM UMA MÁSCARA BINÁRIA        */
/*----------------------------------------------------------------------------*/
/* Autor: Bogdan T. Nassu                                                     */
/*============================================================================*/

#ifndef __TRABALHO3_H
#define __TRABALHO3_H

/*============================================================================*/

#include "imagem.h"

/*============================================================================*/
/* Um tipo simples, usado para representar uma coordenada. */
typedef struct
{
    int x;
    int y;
} Coordenada;

/* Um tipo simples, usado para representar um retângulo envolvente. */
typedef struct
{
    Coordenada tl; // top-left.
    Coordenada br; // bottom-right
} Rect;

/*============================================================================*/
/* Função central do trabalho. */

Rect* encontraFuros (Imagem1C* mask, int* n_furos);

/*============================================================================*/
#endif /* __TRABALHO3_H */
