#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fds[2];
    unsigned int val;
    assert(pipe(fds) != -1);

    switch (fork()) {
    case -1:
        exit(EXIT_FAILURE);

    case 0:                    /* Fils */
        val = 0x12345678;
        assert(write(fds[1], &val, sizeof(unsigned int)) == sizeof(unsigned int));
        printf("Fils se termine, val = %x\n", val);

        exit(EXIT_SUCCESS);

    default:                   /* Père */
        sleep(5);
        printf("Père commence, val = %x\n", val);
        assert(read(fds[0], &val, sizeof(unsigned int)) == sizeof(unsigned int));
        printf("Père termine, val = %x\n", val);
    }

    return 0;
}
