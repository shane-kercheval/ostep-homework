// Same as piping `ls | wc -l` in shell
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t cpid1, cpid2;

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the first child
    cpid1 = fork();
    if (cpid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid1 == 0) {    // First child
        close(pipefd[0]);    // Close read end of pipe
        dup2(pipefd[1], STDOUT_FILENO);  // Redirect stdout to pipe
        close(pipefd[1]);    // Close the now-duplicated write end

        execlp("ls", "ls", NULL);  // Run ls
        perror("execlp");
        exit(EXIT_FAILURE);

    } else {
        // Fork the second child
        cpid2 = fork();
        if (cpid2 == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (cpid2 == 0) {    // Second child
            close(pipefd[1]);    // Close write end of pipe
            dup2(pipefd[0], STDIN_FILENO);  // Redirect stdin from pipe
            close(pipefd[0]);    // Close the now-duplicated read end

            execlp("wc", "wc", "-l", NULL);  // Run wc -l
            perror("execlp");
            exit(EXIT_FAILURE);

        } else {    // Parent process
            close(pipefd[0]);    // Close both ends of pipe
            close(pipefd[1]);
            wait(NULL);    // Wait for both children to finish
            wait(NULL);
        }
    }

    return 0;
}
