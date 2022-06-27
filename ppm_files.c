// GRR20203895 Gabriel de Oliveira Pontarolo
// implementacao das funcoes da biblioteca ppm_files.h
// feito por Gabriel Pontarolo em 10/10/21
#define _DEFAULT_SOURCE
#include "ppm_files.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void _openPpmP3(struct ppm_image *img_content, FILE *img_file)
// le o conteudo de uma imagem ppm tipo p3 e guarda na matriz img_content->values
{
    int i;
    int j;

    for (i=0; i<img_content->height; i++)
    {
        for (j=0; j<img_content->width; j++)
        {
            fscanf(img_file, "%hhu", &(img_content->values[(i * img_content->width) + j].r));
            fscanf(img_file, "%hhu", &(img_content->values[(i * img_content->width) + j].g));
            fscanf(img_file, "%hhu", &(img_content->values[(i * img_content->width) + j].b));
        }
    }
}

void _openPpmP6(struct ppm_image *img_content, FILE *img_file)
// le o conteudo de uma imagem ppm tipo p6 e guarda na matriz img_content->values
{

    getc(img_file);
    fread(img_content->values, sizeof(struct rgb), img_content->height * img_content->width, img_file);

}

struct ppm_image *openPpm(char *image_name)
// Abre uma imagem ppm, copia o conteudo para uma struct ppm_image e fecha a imagem. Retorna o ponteiro para a struct ou NULL em caso de erro.
{
    
    FILE *img_file;
    struct ppm_image *img_content;

    if (!strcmp(image_name, "stdin"))   // entrada padrao
    {
        img_file = stdin;
    }
    else
    {
        img_file = fopen(image_name, "r"); // abre o arquivo
    }

    if (! img_file) // saida de erro
    {
        perror("Falha ao abrir o arquivo");
        return NULL;
    }

    img_content = malloc(sizeof(struct ppm_image)); // aloca mem para a struct
    if (! img_content)  // saida de erro
    {
        perror("Falha ao alocar memória para a struct");
        fclose(img_file);
        return NULL;
    }

    // le o cabecalho
    strncpy(img_content->file_name, image_name, FILE_NAME_MAX_SIZE + 1); // nome
    fscanf(img_file, "%s", img_content->type);  // p3 ou p6
    fscanf(img_file, "%d", &(img_content->width)); // largura
    fscanf(img_file, "%d", &(img_content->height)); // altura
    fscanf(img_file, "%d", &(img_content->color_max)); // altura

    img_content->values = malloc(sizeof(struct rgb) * img_content->width * img_content->height);  // aloca mem para o conteudo da img
    if (!img_content->values)   // saida de erro
    {
        perror("Falha ao alocar memória para a struct");
        fclose(img_file);
        free(img_content);
        return NULL;
    }

    if(!strcmp(img_content->type, "P3")) // caso tipo de ppm seja p3
    {
        _openPpmP3(img_content, img_file);
    }
    else if(!strcmp(img_content->type, "P6")) // caso tipo de ppm seja p6
    {
        _openPpmP6(img_content, img_file);
    }
    else // saida de erro
    {
        perror("Formato da imagem inválido");
        fclose(img_file);
        free(img_content);
        return NULL;
    }

    fclose(img_file);
    return img_content;
}

int _scandirFilter(const struct dirent *file)
// filtro para a funcao scandir
{
    if (!file)  // caso ponteiro seja null
    {
        return 0;
    }

    if ((! strcmp(file->d_name, ".")) || (! strcmp(file->d_name, "..")))    // caso seja diretorio "." ou ".."
    {
        return 0;
    }

    return 1;
}

struct ppm_image **openPpmFolder(char *folder_name, int *array_size)
// Acessa um diretorio de imagens ppm e copia o conteudo de cada uma para um array de ponteiros para struct ppm_image. Retorna o ponteiro para o array ou NULL no caso de erro
{
    struct dirent **name_list;
    struct ppm_image **ppm_array;
    char aux[FILE_NAME_MAX_SIZE];
    int dir_size;
    int i;

    dir_size = scandir(folder_name, &name_list, _scandirFilter, alphasort); // abre o diretorio
    if (dir_size < 0)  // saida de erro
    {
        perror("Falha ao acessar o diretório");
        return NULL;
    }

    ppm_array = malloc(sizeof(struct ppm_image*) * dir_size);   // aloca mem para o array de ponteiros
    if (!ppm_array) // saida de erro
    {
        perror("Falha ao alocar memória para o array de imagems");
        return NULL;
    }

    for (i=0; i<dir_size; i++)
    {
        sprintf(aux, "%s%s", folder_name, name_list[i]->d_name); // concatena o nome do diretorio com o nome da imagem
        ppm_array[i] = openPpm(aux); // copia o conteudo das imagens para o array
        if (!ppm_array[i])  // saida de erro
        {
            perror("Falha ao abrir o arquivo");
            return NULL;
        }
        free(name_list[i]);
    }
    free(name_list);

    *array_size = dir_size;
    return ppm_array;
}

void _createPpmFileP3(struct ppm_image *img_content, FILE *img_file)
// copia o conteudo da imagem da struct para o arquivo com o formato p3
{
    int i;
    int j;

    for (i=0; i<img_content->height; i++)
    {
        for (j=0; j<img_content->width; j++)
        {
            fprintf(img_file, "%u ", img_content->values[(i * img_content->width) + j].r);
            fprintf(img_file, "%u ", img_content->values[(i * img_content->width) + j].g);
            fprintf(img_file, "%u ", img_content->values[(i * img_content->width) + j].b);
        }
        fprintf(img_file, "\n");
    }
}

int createPpmFile(struct ppm_image *img_content, char *file_name)
// Cria um arquivo ppm com o conteudo da struct. Retorna 1 no caso de sucesso, 0 caso contrário.
{
    FILE *img_file;

    if (!strcmp(file_name, "stdout"))
    {
        img_file = stdout;
    }
    else
    {
        img_file = fopen(file_name, "w");   // cria o arquivo de saida
    }
    if (! img_file) // saida de erro
    {
        perror("Falha ao abrir o arquivo");
        return 0;
    }


    fprintf(img_file, "%s\n%d %d\n%d\n", img_content->type, img_content->width, img_content->height, img_content->color_max);   // cabecalho

    if (!strcmp(img_content->type, "P3"))   // caso formato seja p3
    {
        _createPpmFileP3(img_content, img_file);
    }
    else if (!strcmp(img_content->type, "P6")) // caso formato seja p6
    {
        fwrite(img_content->values, sizeof(struct rgb), img_content->height * img_content->width, img_file);
    }

    fclose(img_file);
    return 1;
}

int imageCopy(struct ppm_image *img_dest, struct ppm_image *img_src, int is, int js)
// Copia a imagem src para dentro da imagem dest a partir das coordenadas is (linha) e js (coluna). Retorna 1 no caso de sucesso, 0 caso contrário.
{

    int i=0;
    int j=0;

    if ((img_dest->height < img_src->height) || (img_dest->width < img_src->width) || (img_dest->height < is) || (img_dest->width < js))
    {   // saida de erro
        perror("Tamanho da imagem inválido");
        return 0;
    }

    for (i=0; i<img_src->height; i++)
    {
        for (j=0; j<img_src->width; j++)
        {
            if ((img_dest->height > (i + is)) && (img_dest->width > (j + js)))
            {
                img_dest->values[((i + is) * img_dest->width) + (j + js)] = img_src->values[(i * img_src->width) + j];
            }
        }
    }

    return 1;
}

void deletePpmStruct(struct ppm_image *src)
// Apaga a struct ppm_image e libera o espaco de memoria. 
{
    if (!src)   // saida de erro
    {
        perror("Ponteiro para a struct ppm_image invalido");
        return;
    }

    if (src->values)
    {
        free(src->values);
    }
    free(src);

    return;
}