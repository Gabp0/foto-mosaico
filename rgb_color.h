// GRR20203895 Gabriel de Oliveira Pontarolo
// Biblioteca para manipulacao de cores em formato rgb
// Feito por Gabriel Pontarolo em 11/10/21
#ifndef __RGBC__
#define __RGBC__

struct rgb
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

struct rgb averageBlockColor(struct rgb *rgb_color_block, int width, int is, int js, int ie, int je); // Calcula a cor media de uma matriz de struct rgb a partir das coordenadas (js, is) ate (je, ie). 
float colorDistance(struct rgb a, struct rgb b);    // Retorna a distancia entre duas cores usando o metodo redmean.
int lesserColorDistance(struct rgb src, struct rgb *rgb_array, int array_size); // Retorna o indice do elemento do vetor rgb_array com a menor distancia de cor em relacao a src. Retorna -1 no caso de erro.

#endif