#include "shell.h"

/**
 * _memset - Fills the first n bytes of the memory area pointed to by s with
 *           the constant byte b.
 * @s: Pointer to the memory area.
 * @b: The byte to fill the memory area with.
 * @n: The number of bytes to be filled.
 * Return: A pointer to the memory area s.
 */
char *_memset(char *s, char b, unsigned int n)
{
    for (unsigned int i = 0; i < n; ++i)
    {
        s[i] = b;
    }
    return s;
}

/**
 * ffree - Frees an array of strings and the array itself.
 * @pp: The array of strings.
 */
void ffree(char **pp)
{
    if (pp == NULL)
    {
        return;
    }

    char **temp = pp;
    while (*pp != NULL)
    {
        free(*pp++);
    }
    free(temp);
}

/**
 * _realloc - Reallocates the memory block pointed to by ptr.
 * @ptr: Pointer to the previous memory block.
 * @old_size: The old size of the memory block.
 * @new_size: The new size of the memory block.
 * Return: A pointer to the reallocated memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    if (ptr == NULL)
    {
        return malloc(new_size);
    }

    if (new_size == 0)
    {
        free(ptr);
        return NULL;
    }

    if (new_size == old_size)
    {
        return ptr;
    }

    char *new_ptr = malloc(new_size);
    if (new_ptr == NULL)
    {
        return NULL;
    }

    unsigned int min_size = old_size < new_size ? old_size : new_size;
    while (min_size-- > 0)
    {
        new_ptr[min_size] = ((char *)ptr)[min_size];
    }

    free(ptr);
    return new_ptr;
}
