// GRR20203895 Gabriel de Oliveira Pontarolo
// Biblioteca para manipulacao dos argumentos do programa principal
// Feito por Gabriel Pontarolo em 12/10/21
#ifndef __ARGS__
#define __ARGS__

struct args {
    char *input;
    char *output;
    char *tiles;
};

int getArgs(int argc, char **argv, struct args **arg); // Separa os argumentos passados pela linha de comando; retorna 0 no caso de erro, 1 no caso de entrada padrao e 2 no caso de "--help".
void deleteArgs(struct args *src); // Apaga a struct args e libera o espaco de memoria.

#endif