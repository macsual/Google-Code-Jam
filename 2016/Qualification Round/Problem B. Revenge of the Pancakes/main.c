#include <stdio.h>
#include <string.h>

static int fix(char * const pancakes);

int
main(void)
{
    int i, T;
    char pancakes[100 + 1];
    char *p;

    scanf("%u", &T);
    (void)getchar();    /* consume newline */

    for (i = 0u; i < T; i++) {
        (void)fgets(pancakes, sizeof pancakes, stdin);
        p = strchr(pancakes, '\n');
        if (p)
            *p = '\0';

        printf("Case #%u: %u\n", i + 1, fix(pancakes));
    }

    return 0;
}

static int
fix(char * const pancakes)
{
    char * p = pancakes;

    if ('+' == *p) {
        while ('+' == *p)
            p++;

        if ('\0' == *p)
            return 0;
        else {
            for (p = pancakes; '+' == *p ; p++)
                *p = '-';

            return 1 + fix(pancakes);
        }
    }
    else {
        while ('-' == *p)
            p++;

        if ('\0' == *p)
            return 1;
        else {
            for (p = pancakes; '-' == *p ; p++)
                *p = '+';

            return 1 + fix(pancakes);
        }
    }
}
