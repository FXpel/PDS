#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* Version maison de la fonction system */
int minisystem(char *cmd) {
    pid_t pid;
    int r, status;

    switch (pid = fork()) {
    case -1:
        exit(EXIT_FAILURE);

    case 0:                    /* Fils */
        execl("/bin/sh", "sh", "-c", cmd, (char *) NULL);
        assert(0);

    default:                   /* Père */
        r = waitpid(pid, &status, 0);
        assert(r != -1);
        return status;
    }
}

int main() {
    int status;

    status = minisystem("ls -al");

    if(WIFEXITED(status))
        printf("Exit avec %d\n", WEXITSTATUS(status));

    return 0;
}
