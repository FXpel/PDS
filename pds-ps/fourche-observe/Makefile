# Les règles de compilation peuvent utiliser les variables suivantes
# Consultez la documentation de make pour en savoir plus (et en
# trouver d’autres)
#
# $@  Le nom de la cible
# $<  Le nom de la première dépendance
# $^  La liste des dépendances

CC      = gcc

CFLAGS  = -Wall -Wextra -ansi -pedantic
CFLAGS += -D_XOPEN_SOURCE=500
CFLAGS += -g

all: multif ex6

multif-scd: mcat-multif.o
	$(CC) $(LDFLAGS) -o $@ $^

ex6: ex6.o
	$(CC) $(LDFLAGS) -o $@ $^


%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o
	rm -rf ./multif
	rm -rf ./ex6
	rm -rf *.png
