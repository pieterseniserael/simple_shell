#include "shell.h"

char *_strncpy(char *dest, char *src, int n) {
    char *s = dest;

    for (int i = 0; src[i] != '\0' && i < n - 1; i++) {
        dest[i] = src[i];
    }
    if (i < n) {
        for (int j = i; j < n; j++) {
            dest[j] = '\0';
        }
    }
    return s;
}

char *_strncat(char *dest, char *src, int n) {
    char *s = dest;

    int i = 0;
    while (dest[i] != '\0') {
        i++;
    }
    int j = 0;
    while (src[j] != '\0' && j < n) {
        dest[i++] = src[j++];
    }
    if (j < n) {
        dest[i] = '\0';
    }
    return s;
}

char *_strchr(char *s, char c) {
    while (*s != '\0') {
        if (*s == c) {
            return s;
        }
        s++;
    }
    return NULL;
}
