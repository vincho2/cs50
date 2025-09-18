#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    long size = strtod(argv[1], NULL);
    char *toto = malloc(size * 1000000);

    if (toto == NULL)
    {
        printf("Heap overflow\n");
    }
    else
    {
        printf("pointer : %p\n", toto);
    }
    free(toto);

    long size_2 = get_long("chunk size: ");
    char *toto2 = malloc(size_2 * 1000000);

    if (toto2 == NULL)
    {
        printf("Heap overflow\n");
    }
    else
    {
        printf("pointer : %p\n", toto2);
    }
    free(toto2);
}

