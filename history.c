#include "shell.h"

char *get_history_file(info_t *info) {
    char *home_dir = _getenv(info, "HOME=");
    if (!home_dir) {
        return NULL;
    }

    char *filename = malloc(_strlen(home_dir) + _strlen(HIST_FILE) + 2);
    if (!filename) {
        free(home_dir);
        return NULL;
    }

    _strcpy(filename, home_dir);
    _strcat(filename, "/");
    _strcat(filename, HIST_FILE);

    free(home_dir);
    return filename;
}

int write_history(info_t *info) {
    char *filename = get_history_file(info);
    if (!filename) {
        return -1;
    }

    int fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);

    if (fd == -1) {
        return -1;
    }

    for (list_t *node = info->history; node; node = node->next) {
        _putsfd(node->str, fd);
        _putfd('\n', fd);
    }

    _putfd(BUF_FLUSH, fd);
    close(fd);

    return 1;
}

int read_history(info_t *info) {
    char *filename = get_history_file(info);
    if (!filename) {
        return 0;
    }

    int fd = open(filename, O_RDONLY);
    free(filename);

    if (fd == -1) {
        return 0;
    }

    struct stat st;
    if (fstat(fd, &st) == -1 || st.st_size < 2) {
        close(fd);
        return 0;
    }

    char *buf = malloc(st.st_size + 1);
    if (!buf) {
        close(fd);
        return 0;
    }

    ssize_t rdlen = read(fd, buf, st.st_size);
    buf[st.st_size] = '\0';
    close(fd);

    if (rdlen <= 0) {
        free(buf);
        return 0;
    }

    int last = 0;
    int linecount = 0;

    for (int i = 0; i < st.st_size; i++) {
        if (buf[i] == '\n') {
            buf[i] = '\0';
            build_history_list(info, buf + last, linecount++);
            last = i + 1;
        }
    }

    if (last != st.st_size) {
        build_history_list(info, buf + last, linecount++);
    }

    free(buf);

    info->histcount = linecount;

    while (info->histcount-- >= HIST_MAX) {
        delete_node_at_index(&(info->history), 0);
    }

    renumber_history(info);

    return info->histcount;
}

int build_history_list(info_t *info, char *buf, int linecount) {
    list_t *node = NULL;

    if (info->history) {
        node = info->history;
    }

    add_node_end(&node, buf, linecount);

    if (!info->history) {
        info->history = node;
    }

    return 0;
}

int renumber_history(info_t *info) {
    list_t *node = info->history;
    int count = 0;

    while (node) {
        node->num = count++;
        node = node->next;
    }

    return info->histcount = count;
}
