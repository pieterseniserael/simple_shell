#include "shell.h"

int _myhistory(info_t *info) {
    print_list(info->history);
    return 0;
}

int unset_alias(info_t *info, char *str) {
    char *equal_sign = _strchr(str, '=');
    if (!equal_sign) return 1;

    *equal_sign = '\0';
    int ret = delete_node_at_index(&(info->alias), get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
    *equal_sign = '=';

    return ret;
}

int set_alias(info_t *info, char *str) {
    char *equal_sign = _strchr(str, '=');
    if (!equal_sign) return 1;

    if (!*(equal_sign + 1)) return unset_alias(info, str);

    unset_alias(info, str);
    return add_node_end(&(info->alias), str, 0) == NULL;
}

int print_alias(list_t *node) {
    if (node) {
        char *equal_sign = _strchr(node->str, '=');
        for (char *a = node->str; a <= equal_sign; a++) {
            _putchar(*a);
        }
        _putchar('\'');
        _puts(equal_sign + 1);
        _puts("'\n");
        return 0;
    }
    return 1;
}

int _myalias(info_t *info) {
    if (info->argc == 1) {
        list_t *node = info->alias;
        while (node) {
            print_alias(node);
            node = node->next;
        }
        return 0;
    }

    for (int i = 1; info->argv[i]; i++) {
        char *equal_sign = _strchr(info->argv[i], '=');
        if (equal_sign) {
            set_alias(info, info->argv[i]);
        } else {
            print_alias(node_starts_with(info->alias, info->argv[i], '='));
        }
    }

    return 0;
}
