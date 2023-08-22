#include "shell.h"

void _eputs(char *str) {
    if (!str) return;

    int i = 0;
    while (str[i] != '\0') {
        _eputchar(str[i]);
        i++;
    }
}

int _eputchar(char c) {
    static int i = 0;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE) {
        write(2, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH) {
        buf[i++] = c;
    }
    return 1;
}

int _putfd(char c, int fd) {
    static int i = 0;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE) {
        write(fd, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH) {
        buf[i++] = c;
    }
    return 1;
}

int _putsfd(char *str, int fd) {
    int chars_written = 0;

    if (!str) return chars_written;

    while (*str) {
        chars_written += _putfd(*str++, fd);
    }
    return chars_written;
}
