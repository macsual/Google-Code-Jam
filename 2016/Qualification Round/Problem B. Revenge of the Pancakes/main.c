#include <stdio.h>

static int fix(char * const pancakes);

int
main(void)
{
    int i, T;
    char pancakes[100 + 1];

    scanf("%u", &T);
    (void)getchar();    /* consume newline */

    for (i = 0; i < T; i++)
        printf("Case #%u: %u\n", i + 1,
                fix(fgets(pancakes, sizeof pancakes, stdin)));

    return 0;
}

static int
fix(char * const pancakes)
{
    char * p = pancakes;

    if ('+' == *p) {
        while ('+' == *p)
            p++;

        if ('\0' == *p || '\n' == *p)
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

        if ('\0' == *p || '\n' == *p)
            return 1;
        else {
            for (p = pancakes; '-' == *p ; p++)
                *p = '+';

            return 1 + fix(pancakes);
        }
    }
}
