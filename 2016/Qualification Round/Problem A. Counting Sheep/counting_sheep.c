#include <stdio.h>

int
main(void)
{
    unsigned i;
    unsigned T;
    unsigned long long N;
    unsigned long long *y;
    unsigned long long multiple;
    unsigned digits_seen;
    const unsigned all_digits_seen_flag = (1u << 10) - 1;
    char num_str[1000] = "";
    const char *str;

    scanf("%u", &T);

    for (i = 0; i < T; i++) {
        scanf("%llu", &N);

        if (0ull == N) {
            printf("Case #%u: INSOMNIA\n", i + 1);
            continue;
        }

        digits_seen = 0u;
        *num_str = '\0';
        y = NULL;
        for (multiple = N; /* ad infinitum */; multiple += N) {
            (void)snprintf(num_str, sizeof num_str, "%llu", multiple);

            for (str = num_str; *str; str++) {
                digits_seen |= 1 << (*str - (int)'0');

                if (all_digits_seen_flag == digits_seen) {
                    y = &multiple;
                    break; /* inner for loop */
                }
            }

            if (y == &multiple)
                break; /* outer for loop */
        }

        printf("Case #%u: %llu\n", i + 1, *y);
    }

    return 0;
}
