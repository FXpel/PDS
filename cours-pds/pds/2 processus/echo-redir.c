#include <assert.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/* Commande équivalente à echo abcd > /tmp/a */

int main() {
    int fd, r;

    switch (fork()) {
    case -1:
        exit(EXIT_FAILURE);

    case 0:                    /* Fils */
        fd = open("/tmp/a", O_WRONLY | O_CREAT | O_TRUNC, 0666);
        assert(fd != -1);
        r = dup2(fd, STDOUT_FILENO);
        assert(r != -1);
        close(fd);

        execl("/bin/echo", "echo", "abcd", (char *) NULL);

        assert(0);
    }

    return 0;
}
