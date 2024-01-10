#include "shell.h"

/**
 * @brief Buffers chained commands.
 *
 * @param info Parameter struct.
 * @param buf Address of the buffer.
 * @param len Address of the length variable.
 * @return Bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
    ssize_t bytes_read = 0;
    size_t len_p = 0;

    if (!*len) {
        free(*buf);
        *buf = NULL;
        signal(SIGINT, sigintHandler);

#if USE_GETLINE
        bytes_read = getline(buf, &len_p, stdin);
#else
        bytes_read = _getline(info, buf, &len_p);
#endif

        if (bytes_read > 0) {
            if ((*buf)[bytes_read - 1] == '\n') {
                (*buf)[bytes_read - 1] = '\0'; /* Remove trailing newline */
                bytes_read--;
            }

            info->linecount_flag = 1;
            remove_comments(*buf);
            build_history_list(info, *buf, info->histcount++);

            *len = bytes_read;
            info->cmd_buf = buf;
        }
    }

    return bytes_read;
}

/**
 * @brief Gets a line minus the newline.
 *
 * @param info Parameter struct.
 * @return Bytes read.
 */
ssize_t get_input(info_t *info)
{
    static char *buf; /* The ';' command chain buffer */
    static size_t i, j, len;
    ssize_t bytes_read = 0;
    char **buf_p = &(info->arg), *p;

    _putchar(BUF_FLUSH);
    bytes_read = input_buf(info, &buf, &len);

    if (bytes_read == -1) { /* EOF */
        return -1;
    }

    if (len) { /* We have commands left in the chain buffer */
        j = i; /* Initialize new iterator to the current buf position */
        p = buf + i; /* Get pointer for return */

        check_chain(info, buf, &j, i, len);

        while (j < len) { /* Iterate to semicolon or end */
            if (is_chain(info, buf, &j)) {
                break;
            }

            j++;
        }

        i = j + 1; /* Increment past nulled ';' */

        if (i >= len) { /* Reached end of buffer? */
            i = len = 0; /* Reset position and length */
            info->cmd_buf_type = CMD_NORM;
        }

        *buf_p = p; /* Pass back pointer to the current command position */
        return _strlen(p); /* Return length of the current command */
    }

    *buf_p = buf; /* Else not a chain, pass back buffer from _getline() */
    return bytes_read; /* Return length of buffer from _getline() */
}

/**
 * @brief Reads a buffer.
 *
 * @param info Parameter struct.
 * @param buf Buffer.
 * @param i Size.
 *
 * @return Bytes read.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
    ssize_t bytes_read = 0;

    if (*i) {
        return 0;
    }

    bytes_read = read(info->readfd, buf, READ_BUF_SIZE);

    if (bytes_read >= 0) {
        *i = bytes_read;
    }

    return bytes_read;
}

/**
 * @brief Gets the next line of input from STDIN.
 *
 * @param info Parameter struct.
 * @param ptr Address of pointer to buffer, preallocated or NULL.
 * @param length Size of preallocated ptr buffer if not NULL.
 * @return Bytes read.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t bytes_read = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;

    if (p && length) {
        bytes_read = *length;
    }

    if (i == len) {
        i = len = 0;
    }

    bytes_read = read_buf(info, buf, &len);

    if (bytes_read == -1 || (bytes_read == 0 && len == 0)) {
        return -1;
    }

    c = _strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;

    new_p = _realloc(p, bytes_read, p ? bytes_read + k : k + 1);

    if (!new_p) { /* MALLOC FAILURE! */
        if (p) {
            free(p);
        }

        return -1;
    }

    if (bytes_read) {
        _strncat(new_p, buf + i, k - i);
    } else {
        _strncpy(new_p, buf + i, k - i + 1);
    }

    bytes_read += k - i;
    i = k;
    p = new_p;

    if (length) {
        *length = bytes_read;
    }

    *ptr = p;

    return bytes_read;
}

/**
 * @brief Blocks ctrl-C.
 *
 * @param sig_num The signal number.
 * @return void.
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
    _puts("\n$ ");
    _putchar(BUF_FLUSH);
}
