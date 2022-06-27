# Gerador de foto mosaico em C

Implementação de um criador de foto mosaicos feita em C como trabalho para aprovação parcial na matéria Programação II (CI1002) ofertada pelo curso de Bacharelado em Ciência da Computação da UFPR.

Especificações do trabalho: http://wiki.inf.ufpr.br/maziero/doku.php?id=prog2:fotomosaico

## Uso

Cria um mosaico da imagem de entrada a partir das pastilhas fornecidas.
Utiliza todas as imagens no formato ppm P3 ou P6.\n
\n
\t   -i,                         indica o caminho para o arquivo de entrada, sendo
                                   esse uma imagem do tipo ppm p3 ou ppm p6. caso
                                   não fornecido, utiliza a entrada padrão stdin.\n
\t   -o,                         indica o caminho para a imagem de saída. caso não
                                   fornecido, utiliza a saída padrão stdout.\n
\t   -p,                         indica o caminho para o diretório contendo as
                                   pastilhas que serão utilizadas, sendo essas no
                                   formato ppm p3 ou ppm p6. presume-se que são todas
                                   quadradas, com o mesmo tamanho de N x N pixels. caso
                                   não seja fornecido, utiliza o diretório padrão ./tiles/.\n
\n
Status de saída:
   0 se OK.
   1 se houve qualquer problema na execução.
