#include "shell.h"

int is_interactive(info_t *info) {
    return isatty(STDIN_FILENO) && info->readfd <= 2;
}

int is_delimiter(char c, char *delimiters) {
    while (*delimiters) {
        if (*delimiters == c) {
            return 1;
        }
        delimiters++;
    }
    return 0;
}

int is_alpha_character(int c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int convert_to_int(char *s) {
    int sign = 1, flag = 0, output = 0;
    unsigned int result = 0;

    for (int i = 0; s[i] != '\0' && flag != 2; i++) {
        if (s[i] == '-') {
            sign *= -1;
        }

        if (s[i] >= '0' && s[i] <= '9') {
            flag = 1;
            result = result * 10 + (s[i] - '0');
        } else if (flag == 1) {
            flag = 2;
        }
    }

    output = (sign == -1) ? -result : result;
    return output;
}
