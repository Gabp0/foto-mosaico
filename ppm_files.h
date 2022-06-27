// GRR20203895 Gabriel de Oliveira Pontarolo
// Biblioteca para manipulacao de arquivos .ppm
// feito por Gabriel Pontarolo em 10/10/21
#ifndef __PPMF__
#define __PPMF__

#define FILE_NAME_MAX_SIZE 256
#define PPM_TYPE_STR_SIZE 2

#include "rgb_color.h"

struct ppm_image
{
    char file_name[FILE_NAME_MAX_SIZE + 1];
    char type[PPM_TYPE_STR_SIZE + 1];
    int width;
    int height;
    int color_max;
    struct rgb *values;
};

struct ppm_image *openPpm(char *image_name);    // Abre um arquivo de imagem ppm tipo p3 ou p6, copia para uma struct ppm_image e fecha o arquivo. Retorna um ponteiro para a struct ou NULL no caso de erro. 
int createPpmFile(struct ppm_image *img_content, char *file_name);  // Cria um arquivo de imagem ppm, copia o conteúdo da struct ppm_image e fecha o arquivo. retorna 1 caso de sucesso, 0 caso contrario.
int imageCopy(struct ppm_image *img_dest, struct ppm_image *img_src, int is, int js);   //  Copia a imagem src para dentro da imagem dest a partir das coordenadas is (linha) e js (coluna). Retorna 1 no caso de sucesso, 0 caso contrário.
struct ppm_image **openPpmFolder(char *folder_name, int *array_size);   // Cria um arquivo ppm com o conteudo da struct. Retorna 1 no caso de sucesso, 0 caso contrário.
void deletePpmStruct(struct ppm_image *src);    // Apaga a struct ppm_image e libera o espaco de memoria. 

#endif