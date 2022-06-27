# Gerador de foto mosaico em C

Implementação de um criador de foto mosaicos feita em C como trabalho para aprovação parcial na matéria Programação II (CI1002) ofertada pelo curso de Bacharelado em Ciência da Computação da UFPR.

Especificações do trabalho: http://wiki.inf.ufpr.br/maziero/doku.php?id=prog2:fotomosaico

## Uso

Cria um mosaico da imagem de entrada a partir das pastilhas fornecidas.

Utiliza todas as imagens no formato ppm P3 ou P6.

**-i**, indica o caminho para o arquivo de entrada, sendo esse uma imagem do tipo _ppm p3_ ou _ppm p6_. Caso não fornecido, utiliza a entrada padrão _stdin_.

**-o**, indica o caminho para a imagem de saída. Caso não fornecido, utiliza a saída padrão _stdout_.

**-p**, indica o caminho para o diretório contendo as pastilhas que serão utilizadas, sendo essas noformato _ppm p3_ ou _ppm p6_. Presume-se que são todas quadradas, com o mesmo tamanho de N x N pixels. Caso não seja fornecido, utiliza o diretório padrão _./tiles/_.

Status de saída: _0_ se OK, _1_ se houve qualquer problema na execução.
