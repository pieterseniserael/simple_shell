#include "shell.h"

int _myexit(info_t *info) {
    int exit_status = 0;

    if (info->argv[1]) {
        exit_status = _erratoi(info->argv[1]);
        if (exit_status == -1) {
            info->status = 2;
            print_error(info, "Illegal number: ");
            _eputs(info->argv[1]);
            _eputchar('\n');
            return 1;
        }
        info->err_num = exit_status;
        return -2;
    }

    info->err_num = -1;
    return -2;
}

int _mycd(info_t *info) {
    char buffer[1024];
    char *new_dir = NULL;
    int chdir_ret;

    char *current_dir = getcwd(buffer, sizeof(buffer));
    if (!current_dir)
        _puts("TODO: >>getcwd failure emsg here<<\n");

    if (!info->argv[1]) {
        new_dir = _getenv(info, "HOME=");
        if (!new_dir)
            chdir_ret = chdir((new_dir = _getenv(info, "PWD=")) ? new_dir : "/");
        else
            chdir_ret = chdir(new_dir);
    } else if (_strcmp(info->argv[1], "-") == 0) {
        new_dir = _getenv(info, "OLDPWD=");
        if (!new_dir) {
            _puts(current_dir);
            _putchar('\n');
            return 1;
        }
        _puts(new_dir);
        _putchar('\n');
        chdir_ret = chdir(new_dir ? new_dir : "/");
    } else {
        new_dir = info->argv[1];
        chdir_ret = chdir(new_dir);
    }

    if (chdir_ret == -1) {
        print_error(info, "can't cd to ");
        _eputs(new_dir);
        _eputchar('\n');
    } else {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, sizeof(buffer)));
    }

    return 0;
}

int _myhelp(info_t *info) {
    _puts("help call works. Function not yet implemented \n");
    return 0;
}
