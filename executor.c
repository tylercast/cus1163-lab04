// executor.c
#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int execute_command(char *command, char **args) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return -1;
    }

    if (pid == 0) {
        execvp(command, args);
        perror("execvp");
        _exit(1);
    }

    int status;
    pid_t w = waitpid(pid, &status, 0);
    if (w == -1) {
        perror("waitpid");
        return -1;
    }

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    } else {
        return -1;
    }
}
