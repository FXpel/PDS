### Modèle pour vos Makefile


## Compilateur C et éditeur de liens
CC      = gcc

## Options pour la compilation du C
CFLAGS  = -Wall -Werror -ansi -pedantic
#  Spécifie la version de la norme POSIX à respecter
CFLAGS += -D_XOPEN_SOURCE=500
#  Active les informations de débogage
CFLAGS += -g

## Options de l’édition de liens
LDFLAGS  = -g

## Première cible
#  « make » sans argument construit sa première cible
#  Indiquez en dépendance le ou les binaires à construire
all: mtail tail_stupide
mtail: mtail.c
		${CC} ${CFLAGS} mtail.c -o mtail

tail_stupide: tail_stupide.c
		${CC} ${CFLAGS} tail_stupide.c -o tail_stupide

pwd: pwd.c
		${CC} ${CFLAGS} pwd.c -o pwd

## Compilation séparée
#  Le .o doit être recompilé dès que le .c ou le .h (s'il existe) change
%.o: %.c %.h
	${CC} ${CFLAGS} -c $<


clean:
	rm ./mtail
	rm ./tail_stupide
	rm -rf test/
	rm ./pwd
	rm test1.txt
	rm test2.txt
	rm test3.txt
	rm test4.txt
	rm test5.txt
	rm test6.txt
	rm test7.txt
	rm test8.txt




## Liste des pseudo-cibles
#  Ces cibles ne correspondent pas à des fichiers que l'on veut créer,
#  juste à des séquences que l'on veut pouvoir déclencher
.PHONY: all clean
