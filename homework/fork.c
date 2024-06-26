#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define OPEN_FLAGS (O_CREAT | O_WRONLY | O_APPEND)
#define FILE_PERMISSIONS 0644
#define MAX_TEXT_SIZE 50

// Function definition
int write_to_file(int file_descriptor, char *text) {
    int bytes_written = write(file_descriptor, text, strlen(text));
    if (bytes_written == -1) {
        perror("write");
        return -1;
    }
    return 0;
}

int main() {
    int x = 100;
    printf("x: %d\n", x);
    // open file called temp.txt
    int file_descriptor = open("temp.txt", OPEN_FLAGS, FILE_PERMISSIONS);
    if (file_descriptor == -1) {
        perror("open");
        return 1;
    }
    write_to_file(file_descriptor, "Hello, World!\n");

    int return_code = fork();
    if (return_code < 0) {
        perror("fork");
    } else if (return_code == 0) {
        // child process
        x = 50;
        printf("CHILD PID: %d\n", (int) getpid());
        printf("Child x: %d\n", x);
        char text[MAX_TEXT_SIZE];
        sprintf(text, "CHILD PID: %d\n", (int)getpid());
        write_to_file(file_descriptor, text);
        // CHATGPT:
        // In Unix-like operating systems, when a process forks, the child process inherits copies of the parent's set of open file descriptors. Each file descriptor is an independent entry in the child process, referring to the same underlying file description (which includes the file offset and file status flags).
        // So, when the child process closes a file descriptor (with close(file_descriptor);), it only closes its copy of the file descriptor. The parent process still has its own copy of the file descriptor, which remains open and can be used to write to the file. Closing a file descriptor in one process does not affect the file descriptor in another process, even if both descriptors refer to the same underlying file description.
        // This behavior allows both the parent and child processes to independently manage their own file descriptors, including closing them when they're no longer needed, without interfering with each other.
        close(file_descriptor);

    } else {
        int wait_code = wait(NULL);
        printf("PARENT PID (%d) waiting for CHILD (%d)\n", (int) getpid(), return_code);
        printf("Parent x: %d\n", x);
        char text[MAX_TEXT_SIZE];
        sprintf(text, "PARENT PID: %d\n", (int)getpid());
        write_to_file(file_descriptor, text);
        // close(file_descriptor);
    }
    close(file_descriptor);

    printf("END OF PROGRAM (%d)\n", (int) getpid());

    return 0;
}
