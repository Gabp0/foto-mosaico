// GRR20203895 Gabriel de Oliveira Pontarolo
// implementacao das funcoes da biblioteca args.h
// feito por Gabriel Pontarolo em 12/10/21
#define _DEFAULT_SOURCE
#include "args.h"
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "ppm_files.h"

char *_findParameter(int argc, char **argv, char *parameter, char *def)
// encontra o argumento de acordo com "parameter" e devolve um ponteiro para a string. caso nao encontre, devolve um ponteiro para a string com "def". devolve NULL no caso de erro
{
    int i;
    char *arg = malloc(sizeof(char) * FILE_NAME_MAX_SIZE);

    if (!arg)   // saida de erro
    {
        perror("Não foi possivel alocar memória para os parametros");
        return NULL;
    }

    for (i=1; i<argc; i++)  // tenta encontrar o parametro
    {
        if (!strcmp(argv[i], parameter))
        {
            strncpy(arg, argv[i + 1], FILE_NAME_MAX_SIZE);
            return arg;
        }
    }

    strncpy(arg, def, FILE_NAME_MAX_SIZE);
    
    return arg;
}

int _checkFolderPath(char *folder_path)
// teste se "folder_path" e um caminho de diretorio valido. caso seja, devolve 1. caso contrario, devolve 0
{
    DIR *dir;

    if (!(strrchr(folder_path, '/') == &folder_path[strlen(folder_path) - 1]))  // teste se o caminho do diretorio termina com "/"
    {
        if (strlen(folder_path) < FILE_NAME_MAX_SIZE - 2)
        {
            strcat(folder_path, "/");   // concatena o nome do diretorio com "/" caso haja espaco suficiente
        }
        else 
        {
            fprintf(stderr, "Caminho de diretorio %s invalido\n", folder_path);
            return EXIT_FAILURE;
        }
    }

    dir = opendir(folder_path);
    if (!dir)   // tenta abrir o diretorio
    {
        fprintf(stderr, "Nao foi possível abrir o diretório %s: ", folder_path);
        perror("");
        closedir(dir);
        return 0;
    }
    closedir(dir);

    return 1;
}

int getArgs(int argc, char **argv, struct args **arg)
// Separa os argumentos passados pela linha de comando; retorna 0 no caso de erro, 1 no caso de entrada padrao e 2 no caso de "--help".
{
    int i;

    if (argc > 7)   // saida de erro
    {
        perror("Número de argumentos invalidos");
        return 0;
    }

    for(i=0; i<argc; i++)
    {
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help"))   // help
        {
            fprintf(stderr, "Cria um mosaico da imagem de entrada a partir das pastilhas fornecidas.\n");
            fprintf(stderr, "Utiliza todas as imagens no formato ppm P3 ou P6.\n\n");
            fprintf(stderr, "   -i,                         indica o caminho para o arquivo de entrada, sendo\n");
            fprintf(stderr, "                                   esse uma imagem do tipo ppm p3 ou ppm p6. caso \n");
            fprintf(stderr, "                                   não fornecido, utiliza a entrada padrão stdin.\n");
            fprintf(stderr, "   -o,                         indica o caminho para a imagem de saída. caso não\n"); 
            fprintf(stderr, "                                   fornecido, utiliza a saída padrão stdout.\n");
            fprintf(stderr, "   -p,                         indica o caminho para o diretório contendo as\n"); 
            fprintf(stderr, "                                   pastilhas que serão utilizadas, sendo essas no\n"); 
            fprintf(stderr, "                                   formato ppm p3 ou ppm p6. presume-se que são todas\n");
            fprintf(stderr, "                                   quadradas, com o mesmo tamanho de N x N pixels. caso\n"); 
            fprintf(stderr, "                                   não seja fornecido, utiliza o diretório padrão ./tiles/.\n\n");
            fprintf(stderr, "Status de saída:\n");
            fprintf(stderr, "   0 se OK.\n   1 se houve qualquer problema na execução.\n\n");
            fprintf(stderr, "Feito por Gabriel Pontarolo em 12/10/21.\n");

            return 2;
        }
    }

    *arg = malloc(sizeof(struct args)); // aloca memoria para os argumentos
    if (!arg)   // saida de erro
    {
        perror("Falha ao alocar memória para os argumentos do programa.\n");
        return 0;
    }

    (*arg)->input = _findParameter(argc, argv, "-i", "stdin"); // input
    if (!(*arg)->input)
    {
        perror("Falha ao encontrar o input");
        return 0;
    }

    (*arg)->output = _findParameter(argc, argv, "-o", "stdout");   // output
    if (!(*arg)->input)
    {
        perror("Falha ao encontrar o output");
        return 0;
    }

    (*arg)->tiles = _findParameter(argc, argv, "-p", "tiles/");    // tiles
    if (!(*arg)->input)
    {
        perror("Falha ao encontrar o diretório de tiles");
        return 0;
    }
    if (!_checkFolderPath((*arg)->tiles))
    {
        perror("Diretorio dos tiles inválido");
        return 0;
    }


    return 1;
}

void deleteArgs(struct args *src)
// Apaga a struct args e libera o espaco de memoria.
{
    if (!src)   // saida de erro
    {
        perror("Ponteiro para a struct args invalido");
        return;
    }

    if (src->input)
    {
        free(src->input);
    }

    if (src->output)
    {
        free(src->output);
    }

    if (src->tiles)
    {
        free(src->tiles);
    }
    free(src);
    
    return;
}
