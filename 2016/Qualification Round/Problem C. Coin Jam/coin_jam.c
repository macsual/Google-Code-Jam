#include <stdio.h>      /* size_t, scanf, printf */
#include <stdint.h>     /* uint32_t */
#include <math.h>       /* sqrt */
#include <string.h>     /* strlen */

static unsigned long long getdivisor(unsigned long long n);
static unsigned long long tobase10(uint32_t n, int base);
static int bintostr(uint32_t num, size_t n, char *s);

static const unsigned long long powers3[32] = {
    1853020188851841ULL, 617673396283947ULL, 205891132094649ULL,
    68630377364883ULL, 22876792454961ULL, 7625597484987ULL, 2541865828329ULL,
    847288609443ULL,282429536481ULL, 94143178827ULL, 31381059609ULL,
    10460353203ULL, 3486784401ULL, 1162261467ULL, 387420489ULL, 129140163ULL,
    43046721ULL, 14348907ULL, 4782969ULL, 1594323ULL, 531441ULL, 177147ULL,
    59049ULL, 19683ULL, 6561ULL, 2187ULL, 729ULL, 243ULL, 81ULL, 27ULL, 9ULL,
    3};

static const unsigned long long powers4[32] = {
    18446744073709551616ULL, 4611686018427387904ULL, 1152921504606846976ULL,
    288230376151711744ULL, 72057594037927936ULL, 18014398509481984ULL,
    4503599627370496ULL, 1125899906842624ULL, 281474976710656ULL,
    70368744177664ULL, 17592186044416ULL, 4398046511104ULL, 1099511627776ULL,
    274877906944ULL, 68719476736ULL, 17179869184ULL, 4294967296ULL,
    1073741824ULL, 268435456ULL, 67108864ULL, 16777216ULL, 4194304ULL,
    1048576ULL, 262144ULL, 65536ULL, 16384ULL, 4096ULL, 1024ULL, 256ULL,
    64ULL, 16ULL, 4};

static const unsigned long long powers5[32] = {
    23283064365386962890625ULL, 4656612873077392578125ULL,
    931322574615478515625ULL, 186264514923095703125ULL,
    37252902984619140625ULL, 7450580596923828125ULL, 1490116119384765625ULL,
    298023223876953125ULL, 59604644775390625ULL, 11920928955078125ULL,
    2384185791015625ULL, 476837158203125ULL, 95367431640625ULL,
    19073486328125ULL, 3814697265625ULL, 762939453125ULL, 152587890625ULL,
    30517578125ULL, 6103515625ULL, 1220703125ULL, 244140625ULL, 48828125ULL,
    9765625ULL, 1953125ULL, 390625ULL, 78125ULL, 15625ULL, 3125ULL, 625ULL,
    125ULL, 25ULL, 5};

static const unsigned long long powers6[32] = {
    7958661109946400884391936ULL, 1326443518324400147398656ULL,
    221073919720733357899776ULL, 36845653286788892983296ULL,
    6140942214464815497216ULL, 1023490369077469249536ULL,
    170581728179578208256ULL, 28430288029929701376ULL,
    4738381338321616896ULL, 789730223053602816ULL, 131621703842267136ULL,
    21936950640377856ULL, 3656158440062976ULL, 609359740010496ULL,
    101559956668416ULL, 16926659444736ULL, 2821109907456ULL, 470184984576ULL,
    78364164096ULL, 13060694016ULL, 2176782336ULL, 362797056ULL, 60466176ULL,
    10077696ULL, 1679616ULL, 279936ULL, 46656ULL, 7776ULL, 1296ULL, 216ULL,
    36ULL, 6};

static const unsigned long long powers7[32] = {
    1104427674243920646305299201ULL, 157775382034845806615042743ULL,
    22539340290692258087863249ULL, 3219905755813179726837607ULL,
    459986536544739960976801ULL, 65712362363534280139543ULL,
    9387480337647754305649ULL, 1341068619663964900807ULL,
    191581231380566414401ULL, 27368747340080916343ULL, 3909821048582988049ULL,
    558545864083284007ULL, 79792266297612001ULL, 11398895185373143ULL,
    1628413597910449ULL, 232630513987207ULL, 33232930569601ULL,
    4747561509943ULL, 678223072849ULL, 96889010407ULL,
    13841287201ULL, 1977326743ULL, 282475249ULL, 40353607ULL, 5764801ULL,
    823543ULL, 117649ULL, 16807ULL, 2401ULL, 343ULL, 49ULL, 7};

static const unsigned long long powers8[32] = {
    79228162514264337593543950336ULL, 9903520314283042199192993792ULL,
    1237940039285380274899124224ULL, 154742504910672534362390528ULL,
    19342813113834066795298816ULL, 2417851639229258349412352ULL,
    302231454903657293676544ULL, 37778931862957161709568ULL,
    4722366482869645213696ULL, 590295810358705651712ULL,
    73786976294838206464ULL, 9223372036854775808ULL, 1152921504606846976ULL,
    144115188075855872ULL, 18014398509481984ULL, 2251799813685248ULL,
    281474976710656ULL, 35184372088832ULL, 4398046511104ULL, 549755813888ULL,
    68719476736ULL, 8589934592ULL, 1073741824ULL, 134217728ULL, 16777216ULL,
    2097152ULL, 262144ULL, 32768ULL, 4096ULL, 512ULL, 64ULL, 8};

static const unsigned long long powers9[32] = {
    3433683820292512484657849089281ULL, 381520424476945831628649898809ULL,
    42391158275216203514294433201ULL, 4710128697246244834921603689ULL,
    523347633027360537213511521ULL, 58149737003040059690390169ULL,
    6461081889226673298932241ULL, 717897987691852588770249ULL,
    79766443076872509863361ULL, 8862938119652501095929ULL,
    984770902183611232881ULL, 109418989131512359209ULL,
    12157665459056928801ULL, 1350851717672992089ULL, 150094635296999121ULL,
    16677181699666569ULL, 1853020188851841ULL, 205891132094649ULL,
    22876792454961ULL, 2541865828329ULL, 282429536481ULL, 31381059609ULL,
    3486784401ULL, 387420489ULL, 43046721ULL, 4782969ULL, 531441ULL, 59049ULL,
    6561ULL, 729ULL, 81ULL, 9};

static const unsigned long long powers10[32] = {
    100000000000000000000000000000000ULL, 10000000000000000000000000000000ULL,
    1000000000000000000000000000000ULL, 100000000000000000000000000000ULL,
    10000000000000000000000000000ULL, 1000000000000000000000000000ULL,
    100000000000000000000000000ULL, 10000000000000000000000000ULL,
    1000000000000000000000000ULL, 100000000000000000000000ULL,
    10000000000000000000000ULL, 1000000000000000000000ULL,
    100000000000000000000ULL, 10000000000000000000ULL, 1000000000000000000ULL,
    100000000000000000ULL, 10000000000000000ULL, 1000000000000000ULL,
    100000000000000ULL, 10000000000000ULL, 1000000000000ULL, 100000000000ULL,
    10000000000ULL, 1000000000ULL, 100000000ULL, 10000000ULL, 1000000ULL,
    100000ULL, 10000ULL, 1000ULL, 100ULL, 10};

int
main(void)
{
    unsigned long i;
    unsigned j;
    unsigned index, count;
    unsigned long permutations;         /* maximum of 2^32 - 2*/
    unsigned T = 1u, N, J;
    unsigned long long divisors[9];
    char jamcoin_str[32 + 1];
    uint32_t jamcoin;

    (void)getchar();       /* consume T */
    (void)getchar();       /* consume newline */

    scanf("%u %u", &N, &J);

    puts("Case #1:");

    jamcoin = 1u;                   /* jamcoins must end with 1 */
    jamcoin |= 1u << (N - 1);       /* jamcoins must begin with 1 */
    permutations = 1u << (N - 2u);  /* 2^(N - 2), -2 as first and last are fixed */
    count = 0u;
    for (i = 0u; i < permutations; i++) {
        for (j = 2u; j <= 10u; j++) {
            index = j - 2u;
            divisors[index] = getdivisor(tobase10(jamcoin, j));
            if (0u == divisors[index])
                break; /* inner for loop */
        }

        if (j < 10u || divisors[8] == 0u) {
            jamcoin += 2; /* 2 is 10 in binary */

            continue; /* outer for loop */
        }
        else {
            (void)bintostr(jamcoin, sizeof jamcoin_str, jamcoin_str);
            printf("%s ", jamcoin_str);
            for (j = 0u; j < 8u; j++)
                printf("%llu ", divisors[j]);

            printf("%llu\n", divisors[8]);
            
            count++;
            if (count == J)
                break; /* outer for loop */

            jamcoin += 2;
        }
    }

    return 0;
}

static unsigned long long
tobase10(uint32_t n, int base)
{
    unsigned i;
    unsigned bit;
    unsigned long long result;
    const unsigned long long *a;

    switch (base) {
        case 2:
            return n;
            break;
        case 3:
            a = powers3;
            break;
        case 4:
            a = powers4;
            break;
        case 5:
            a = powers5;
            break;
        case 6:
            a = powers6;
            break;
        case 7:
            a = powers7;
            break;
        case 8:
            a = powers8;
            break;
        case 9:
            a = powers9;
            break;
        case 10:
            a = powers10;
            break;
    }

    /* skip leading zeroes */
    i = 0u;
    for (bit = 1u << (8 * sizeof n) - 1; bit != 0u; bit >>= 1u) {
        if (n & bit) {
            i++;
            break;
        }

        i++;
    }

    result = 1u; /* jamcoin must end with 1 and any base to 0 is 1 */
    for (bit; bit != 1u; bit >>= 1u) {
        if (n & bit)
            result += a[i];
        i++;
    }

    return result;
}

static unsigned long long
getdivisor(unsigned long long n)
{
    unsigned long long i;
    unsigned long long sqroot = (unsigned long long)sqrt((double)n) + 1;

    for (i = 2u; i <= sqroot; i++)
        if (n % i == 0)
            return i;

    if (i = sqroot)
        return 0u;
}

/* num is the binary number to be converted to a human readable string, n is
 * the size of parameter s, the null terminated C string which is used to store
 * the binary representation.
 */
static int
bintostr(uint32_t num, size_t n, char * s)
{
    int i, n_bits;

    unsigned bit;

    /* the number of bits required to represent the unsigned num in memory that
     * has the same magnitude as parameter n.
     */
    n_bits = 8 * sizeof num;

    /* this check ensures that string s is large enough to store num's binary
     * representation.
     * 1 is subtracted from n to discard the terminating null character from
     * this calculation.
     */
    if (n - 1 < n_bits)
        return -1;

    /* skip leading zeroes */
    for (bit = 1u << n_bits - 1; bit != 0u; bit >>= 1u)
        if (num & bit)
            break;

    i = 0;
    for (bit; bit != 0u; i++) {
        s[i] = (num & bit) ? '1' : '0';
        bit >>= 1u;
    }

    s[i] = '\0';

    return 0;
}
