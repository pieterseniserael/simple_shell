#include "shell.h"

int main(int argc, char **argv) {
    info_t info;
    initialize_info(&info);

    if (argc == 2) {
        int fd = open(argv[1], O_RDONLY);
        if (fd == -1) {
            if (errno == EACCES)
                return 126;
            if (errno == ENOENT) {
                print_error(argv[0], "Can't open ", argv[1], "\n");
                return 127;
            }
            return EXIT_FAILURE;
        }
        info.readfd = fd;
    }

    populate_env_list(&info);
    read_history(&info);
    shell_loop(&info, argv);
    
    write_history(&info);
    free_info(&info);
    if (!interactive(&info) && info.status)
        exit(info.status);
    
    return info.status;
}

void shell_loop(info_t *info, char **argv) {
    ssize_t r = 0;
    int builtin_ret = 0;

    while (r != -1 && builtin_ret != -2) {
        clear_info(info);
        print_prompt(info);
        r = get_input(info);
        if (r != -1) {
            set_info(info, argv);
            builtin_ret = find_builtin(info);
            if (builtin_ret == -1)
                find_and_execute_command(info);
        } else if (interactive(info))
            print_newline();
        free_info(info, 0);
    }
}

int find_builtin(info_t *info) {
    // Same implementation as before
}

void find_and_execute_command(info_t *info) {
    char *path = NULL;
    int i, word_count;

    info->path = info->argv[0];
    if (info->linecount_flag == 1) {
        info->line_count++;
        info->linecount_flag = 0;
    }

    word_count = count_words(info->arg);
    if (word_count == 0)
        return;

    path = find_executable_path(info, _getenv(info, "PATH="), info->argv[0]);
    if (path) {
        info->path = path;
        execute_command(info);
    } else {
        if ((interactive(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/')
            && is_command(info, info->argv[0]))
            execute_command(info);
        else if (*(info->arg) != '\n') {
            info->status = 127;
            print_error(info, "not found\n");
        }
    }
}

void execute_command(info_t *info) {
    pid_t child_pid = fork();
    
    if (child_pid == -1) {
        print_error("Error:", strerror(errno), "\n");
        return;
    }
    
    if (child_pid == 0) {
        if (execve(info->path, info->argv, get_environ(info)) == -1) {
            handle_execution_error(info);
        }
    } else {
        wait_and_update_status(info);
    }
}
}
