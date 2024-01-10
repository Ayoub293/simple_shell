#include "shell.h"

/**
 * bfree - Frees a pointer and sets it to NULL.
 * @ptr: Address of the pointer to free
 *
 * Returns: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
    if (ptr != NULL && *ptr != NULL)
    {
        free(*ptr);
        *ptr = NULL;
        return 1;
    }
    return 0;
}
