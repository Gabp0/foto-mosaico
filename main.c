// GRR20203895 Gabriel de Oliveira Pontarolo
// Programacao II, trabalho 1: fotomosaico 
// Feito por Gabriel de Oliveira Pontarolo em 10/10/21
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "ppm_files.h"
#include "rgb_color.h"
#include "args.h"

void freeHeap(struct ppm_image *input_img, struct args *arg, struct ppm_image **tiles, struct rgb *tiles_mean_color, int tiles_num)
// libera a mem alocada
{
    int i;

    if (input_img)  // imagem base
    {
        deletePpmStruct(input_img);
    }

    if (arg)    // argumentos do programa
    {
        deleteArgs(arg);
    }

    for (i=0; i<tiles_num; i++) // tiles
    {
        if (tiles[i])
        {
            deletePpmStruct(tiles[i]);
        }
    }
    free(tiles);

    if (tiles_mean_color)
    {
        free(tiles_mean_color); 
    }

    return;
}

int main(int argc, char **argv)
{
    struct args *arg = NULL;                // argumentos passados pela linha de comando
    struct ppm_image *input_img = NULL;     // imagem base
    struct ppm_image **tiles_array = NULL;  // array para os tiles
    struct rgb *tiles_mean_color = NULL;    // array para a cor media dos tiles
    int tiles_num = 0;                      // quantidade de tiles 
    int tiles_size = 0;                     // tamanho de cada tile
    
    int i, j;                              
    int aux, ex;

    ex = getArgs(argc, argv, &arg);  // separa os argumentos
    if (!ex) // saida de erro
    {
        perror("Falha ao ler os argumentos");
        freeHeap(input_img, arg, tiles_array, tiles_mean_color, tiles_num);
        exit(EXIT_FAILURE);
    }
    else if(ex == 2)
    {
        exit(EXIT_SUCCESS);
    }
    fprintf(stderr, "Input: %s\nOutput: %s\nTiles: %s\n", arg->input, arg->output, arg->tiles);

    fprintf(stderr, "Lendo a imagem base\n");
    input_img = openPpm(arg->input); // abre a imagem de input
    if (! input_img)    // saida de erro
    {
        perror("Nao foi possível abrir a imagem base");
        freeHeap(input_img, arg, tiles_array, tiles_mean_color, tiles_num);
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "A imagem base e PPM %s, %d x %d pixels\n", input_img->type, input_img->width, input_img->height);

    fprintf(stderr, "Lendo o diretorio de tiles\n");
    tiles_array = openPpmFolder(arg->tiles, &tiles_num); // diretorio de tiles
    if ((! tiles_array) || (tiles_num < 1)) // saida de erro
    {
        perror("Nao foi possível abrir o diretório dos tiles");
        freeHeap(input_img, arg, tiles_array, tiles_mean_color, tiles_num);
        exit(EXIT_FAILURE);
    }
    tiles_size = tiles_array[0]->height;
    fprintf(stderr, "%d tiles lidos\nO tamanho dos tiles e %d x %d pixels\n", tiles_num, tiles_size, tiles_size);

    fprintf(stderr, "Calculando a cor media dos tiles\n");
    tiles_mean_color = malloc(sizeof(struct rgb) * tiles_num);  // aloca mem para a cor media dos tiles
    if (!tiles_mean_color)  // saida de erro
    {
        perror("Nao foi possível alocar memoria para a cor media dos tiles");
        freeHeap(input_img, arg, tiles_array, tiles_mean_color, tiles_num);
        exit(EXIT_FAILURE);
    }
    for (i=0; i<tiles_num; i++) // calcula cor media dos tiles
    {
        tiles_mean_color[i] = averageBlockColor(tiles_array[i]->values, tiles_size, 0, 0, tiles_size-1, tiles_size-1);
    }

    fprintf(stderr, "Substituindo os blocos da imagem pelos tiles\n");
    for (i=0; i<input_img->height; i += tiles_size) // substitui os blocos da imagem pelos tiles
    {
        for (j=0; j<input_img->width; j += tiles_size)
        {
            aux = lesserColorDistance(averageBlockColor(input_img->values, input_img->width, i, j, i+tiles_size-1, j+tiles_size-1), tiles_mean_color, tiles_num);
            ex = imageCopy(input_img, tiles_array[aux], i, j);
            if((aux < 0) || (!ex))  // saida de erro
            {
                perror("Nao foi possível substituir os blocos da imagem base");
                freeHeap(input_img, arg, tiles_array, tiles_mean_color, tiles_num);
                exit(EXIT_FAILURE);
            }  
        }
    }

    fprintf(stderr, "Criando o arquivo de saida\n");    
    ex = createPpmFile(input_img, arg->output); // arquivo de saida
    if (!ex) // saida de erro
    {
        perror("Nao foi possivel criar o arquivo de saida");    
        freeHeap(input_img, arg, tiles_array, tiles_mean_color, tiles_num);
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "Feito\n");
    freeHeap(input_img, arg, tiles_array, tiles_mean_color, tiles_num);
    exit(EXIT_SUCCESS);    
}