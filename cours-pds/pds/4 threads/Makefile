ALL := thread-création
ALL += partage
ALL += visupiles
ALL += adaptation
ALL += adaptation-join
ALL += adaptation-detach

ALL += compteurs
ALL += compteurs-sem
ALL += compteurs-mutex

ALL += thread-exit

ALL += prodcons-mut-cond

ALL += sighandler
ALL += arrêt-thread-sig
ALL += arrêt-thread-cancel

ALL += compteurs-mutex-recursif

all: $(ALL)

# Édition de liens
%: %.o
	gcc $^ -o $@ -pthread

compteurs-mutex-recursif.o: compteurs-mutex-recursif.c
# La constante PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP n’est normalisée
# par POSIX, on active _GNU_SOURCE pour y avoir accès
	gcc -Wall -Wextra -ansi -pedantic -Wno-unused-parameter -D_XOPEN_SOURCE=500 -D_GNU_SOURCE -c -g $< -pthread

# Compilation
%.o: %.c
	gcc -Wall -Wextra -ansi -pedantic -Wno-unused-parameter -D_XOPEN_SOURCE=500 -c -g $< -pthread

%: %.c

clean:
	rm -f $(ALL)

.PHONY: all clean

