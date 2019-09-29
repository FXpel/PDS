ALL = fork partage1

ALL += partage2 exec echo-redir minisystem

ALL += piletas

all: $(ALL)

%: %.c
	gcc -Wall -Wextra -ansi -Wpedantic -g $< -o $@

fork: fork.c
# On sait qu’il y a une variable qui n’est utilisée que quand une
# certaine ligne est décommentée, donc désactive l’avertissement pour
# l’instant
	gcc -Wall -Wextra -ansi -Wpedantic -g -Wno-unused-variable $< -o $@

exec: exec.c
	gcc -Wall -Wextra -ansi -Wpedantic -g -Wno-unused-parameter -Wno-unused-but-set-variable $< -o $@

clean:
	rm -f $(ALL)
	rm -f core

.PHONY: all clean
