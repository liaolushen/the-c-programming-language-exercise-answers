#include <unistd.h>
#include <fcntl.h>

#define BUFSIZ 1024

int main(int argc, char const *argv[]) {
    int fd;
    void filecopy(int fd_in, int fd_out);
    if (argc == 1) {
        filecopy(STDIN_FILENO, STDOUT_FILENO);
    } else {
        while (--argc > 0) {
            if ((fd = open(*++argv, O_RDONLY, 0)) != -1) {
                filecopy(fd, STDOUT_FILENO);
                close(fd);
            }
        }
    }
}

void filecopy(int fd_in, int fd_out) {
    char buf[BUFSIZ];
    int n;
    while ((n = read(fd_in, buf, BUFSIZ)) > 0) {
        write(fd_out, buf, n);
    }
}
