// GRR20203895 Gabriel de Oliveira Pontarolo
// implmentacao das funcoes da biblioteca rgb_color.h
// feito por Gabriel Pontarolo em 11/10/21
#include "rgb_color.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct rgb averageBlockColor(struct rgb *rgb_color_block, int width, int is, int js, int ie, int je)
// Calcula a cor media de uma matriz de struct rgb a partir das coordenadas (js, is) ate (je, ie). 
{
    int i;
    int j;
    int size = 0;

    float average_r = 0;
    float average_g = 0;
    float average_b = 0;

    struct rgb average;

    for (i=is; i<=ie; i++)
    {
        for (j=js; j<=je; j++)  // soma o quadrado de cada cor
        {
            average_r += pow(rgb_color_block[(i * width) + j].r, 2);
            average_g += pow(rgb_color_block[(i * width) + j].g, 2);
            average_b += pow(rgb_color_block[(i * width) + j].b, 2);

            size++;
        }
    }

    // raiz da media de cada cor
    average.r = sqrt(average_r/size);
    average.g = sqrt(average_g/size);
    average.b = sqrt(average_b/size);

    return average;
}

float colorDistance(struct rgb a, struct rgb b)
// Retorna a distancia entre duas cores usando o metodo redmean.
{
    float dR = b.r - a.r;   // delta R
    float dG = b.g - a.g;   // delta G
    float dB = b.b - a.b;   // delta B

    float rm = (a.r + b.r) / 2; // R medio

    return sqrt((2 + (rm/256)) * (dR * dR) + (4 * (dG * dG)) + ((2 + ((255 - rm)/256)) * (dB * dB)));
}

int lesserColorDistance(struct rgb src, struct rgb *rgb_array, int array_size)
// Retorna o indice do elemento do vetor rgb_array com a menor distancia de cor em relacao a src. Retorna -1 no caso de erro.
{
    int i;
    int lesser_cd;
    int lesser_cd_i;
    int aux;

    if (array_size < 1) // saida de erro
    {
        perror("Tamanho do vetor rgb invalido");
        return -1;
    }
    if (!rgb_array)
    {
        perror("Ponteiro para o vetor rgb invalido");
        return -1;
    }

    lesser_cd = colorDistance(src, rgb_array[0]);
    lesser_cd_i = 0;
    for (i=1; i<array_size; i++)    // encontra a menor distancia de cor no array
    {
        aux = colorDistance(src, rgb_array[i]);
        if (aux < lesser_cd)
        {
            lesser_cd = aux;
            lesser_cd_i = i;
        }
    }

    return lesser_cd_i;
}