#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

/* Commande qui exécute ls -al /tmp, ou autre chose, suivant ce que
 * l’on décommente */

int main(int argc, char *argv[], char *envp[]) {
    char *argv_ls[4];
    argv_ls[0] = "ls";
    argv_ls[1] = "-al";
    argv_ls[2] = "/tmp";
    argv_ls[3] = (char*)NULL;

    /* execlp("ls", "ls", "-al", "/tmp", (char *)NULL); */
    /* execl("ls", "ls", "-al", "/tmp", (char *)NULL); */
    /* execl("partage1", "ls", "-al", "/tmp", (char *)NULL); */
    /* execl("/bin/ls", "ls", "-al", "/tmp", (char *)NULL); */

    /* execve("/bin/ls", argv_ls, envp); */

    /* execl("script.sh", "script.sh", (char *)NULL); */

    execl("/tmp", "/tmp", (char *)NULL);

    perror("exec");
    assert(0);

    return 0;
}
