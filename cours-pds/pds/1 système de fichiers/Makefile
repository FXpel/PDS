ALL = ordinaire

ALL += mkdir ls

ALL += cp cat seek seek2 write-printf

all: $(ALL)

ordinaire: ordinaire.c
	gcc -Wall -Wextra $< -o $@

mkdir: mkdir.c
	gcc -Wall -Wextra -ansi -pedantic $< -o $@

%: %.c
	gcc -Wall -Wextra -ansi -pedantic -D_XOPEN_SOURCE=500 $< -o $@

clean:
	rm -f $(ALL)
	rm -f core

.PHONY: all clean
