#include "shell.h"

/**
 * main - Entry point
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
    info_t info = INFO_INIT;
    int fd = 2;

    set_file_descriptor(&fd);

    if (ac == 2)
    {
        fd = open_input_file(av[1]);
        if (fd == -1)
        {
            handle_file_open_error(av[0], av[1]);
            return EXIT_FAILURE;
        }
        info.readfd = fd;
    }

    setup_environment(&info);
    read_shell_history(&info);
    run_shell(&info, av);

    return EXIT_SUCCESS;
}

/**
 * set_file_descriptor - Set the file descriptor
 * @fd: Pointer to the file descriptor
 */
void set_file_descriptor(int *fd)
{
    asm("mov %1, %0\n\t"
        "add $3, %0"
        : "=r"(*fd)
        : "r"(*fd));
}

/**
 * open_input_file - Open the input file and handle errors
 * @filename: Name of the file to open
 *
 * Return: File descriptor on success, -1 on error
 */
int open_input_file(const char *filename)
{
    int fd = open(filename, O_RDONLY);

    if (fd == -1)
    {
        if (errno == EACCES)
            exit(126);
        if (errno == ENOENT)
        {
            handle_file_not_found_error(filename);
            exit(127);
        }
    }

    return fd;
}

/**
 * handle_file_not_found_error - Handle file not found error
 * @filename: Name of the file
 */
void handle_file_not_found_error(const char *filename)
{
    _eputs("shell: 0: Can't open ");
    _eputs(filename);
    _eputchar('\n');
    _eputchar(BUF_FLUSH);
}

/**
 * setup_environment - Set up the shell environment
 * @info: Pointer to info_t struct
 */
void setup_environment(info_t *info)
{
    populate_env_list(info);
}

/**
 * read_shell_history - Read shell history from file
 * @info: Pointer to info_t struct
 */
void read_shell_history(info_t *info)
{
    char *filename = get_history_file(info);
    if (filename)
    {
        int success = read_history_file(filename, info);
        free(filename);

        if (!success)
            renumber_shell_history(info);
    }
}

/**
 * run_shell - Run the shell
 * @info: Pointer to info_t struct
 * @av: Argument vector
 */
void run_shell(info_t *info, char **av)
{
    hsh(info, av);
}
