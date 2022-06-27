# GRR20203895 Gabriel de Oliveira Pontarolo

CFLAGS = --std=c99 -Wall
LDLIBS = -lm

objects = main.o ppm_files.o args.o rgb_color.o

# default
all: mosaico

# ligacao
mosaico: $(objects)
	cc -o mosaico $(objects) $(LDLIBS)	

# compilacao
main.o: main.c ppm_files.h rgb_color.h args.h
ppm_files.o: ppm_files.c ppm_files.h rgb_color.h
args.o: args.c args.h
rgb_color.o: rgb_color.c rgb_color.h

# depuracao
debug: CFLAGS += -DDEBUG -g
debug: all

# remove arquivos temporarios
clean:
	-rm -f $(objects) *~

# remove tudo que nao for codigo fonte
purge: clean
	-rm -f mosaico
