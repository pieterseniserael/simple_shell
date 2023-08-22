#include "shell.h"

int _erratoi(char *s) {
    unsigned long int result = 0;
    int i;

    if (*s == '+') s++;

    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            result *= 10;
            result += (s[i] - '0');
            if (result > INT_MAX) return -1;
        } else {
            return -1;
        }
    }
    return result;
}

void print_error(info_t *info, char *estr) {
    _eputs(info->fname);
    _eputs(": ");
    print_d(info->line_count, STDERR_FILENO);
    _eputs(": ");
    _eputs(info->argv[0]);
    _eputs(": ");
    _eputs(estr);
}

int print_d(int input, int fd) {
    int count = 0;
    char sign = 0;
    unsigned int _abs_, current;

    int (*__putchar)(char) = (fd == STDERR_FILENO) ? _eputchar : _putchar;

    if (input < 0) {
        _abs_ = -input;
        sign = '-';
        __putchar('-');
        count++;
    } else {
        _abs_ = input;
    }

    current = _abs_;
    for (int i = 1000000000; i > 1; i /= 10) {
        if (_abs_ / i) {
            __putchar('0' + current / i);
            count++;
        }
        current %= i;
    }
    __putchar('0' + current);
    count++;

    return count;
}

char *convert_number(long int num, int base, int flags) {
    static char buffer[50];
    char *array = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0) {
        n = -num;
        sign = '-';
    }

    ptr = &buffer[49];
    *ptr = '\0';

    do {
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    if (sign) *--ptr = sign;
    return ptr;
}

void remove_comments(char *buf) {
    for (int i = 0; buf[i] != '\0'; i++) {
        if (buf[i] == '#' && (!i || buf[i - 1] == ' ')) {
            buf[i] = '\0';
            break;
        }
    }
}
