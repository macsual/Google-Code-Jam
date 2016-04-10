#include <stdio.h>

int
main (void)
{
    unsigned int    i, j, k, l, len;
    unsigned int    sp_indices[999];
    int             buf[1000 + 999 + 1]; /* letters, max spaces, newline */
    unsigned int    N;

    scanf ("%u", &N);

    (void)getchar ();       /* consume newline */

    for (i = 0; i < N; i++) {
        len = 0;
        k = 0;
        do {
            buf[len] = getchar ();

            len++;

            if (' ' == buf[len - 1]) {
                sp_indices[k] = len - 1;
                k++;
            }
        } while (buf[len - 1] != '\n');

        printf("Case #%u: ", i + 1);

        if (k) { /* multiple words */
            /* the last word */
            for (l = sp_indices[k - 1] + 1; l < len - 1; l++)
                putchar (buf[l]);

            putchar ((int)' ');

            /* the words in between the last and first */
            for (j = k - 1; j > 0; j--) {
                for (l = sp_indices[j - 1] + 1; l < sp_indices[j]; l++)
                    putchar (buf[l]);

                putchar ((int)' ');
            }

            /* the first word */
            for (l = 0; l < sp_indices[0]; l++)
                putchar (buf[l]);
        }
        else { /* one word */
            for (l = 0; l < len - 1; l++)
                putchar (buf[l]);
        }

        putchar ((int)'\n');
    }

    return 0;
}
