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

all: mcat-scd mcat-lib mcat-osync tac

mcat-scd: mcat-scd.o
	$(CC) $(LDFLAGS) -o $@ $^

tac: tac.o
	$(CC) $(LDFLAGS) -o $@ $^
mcat-lib: mcat-lib.o
	$(CC) $(LDFLAGS) -o $@ $^

mcat-osync: mcat-osync.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o
	rm -rf ./tac
	rm -rf ./mcat-scd
	rm -rf ./mcat-lib
	rm -rf ./mcat-osync
	rm -rf test/
	rm -rf *.dat
	rm -rf *.png
