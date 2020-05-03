int brute_force_fact(int i)
{
    for (int n = 2; n < i; n++) {
        if (i % n == 0) {
            printf("%d is not prime! %d divides it!\n", i, n);
            return 0;
        }
    }

    printf("%d is prime!\n", i);
    return 0;
}

int optimization_congruence_class(int i)
{
    int j = 5;

    if (i == 2 || i == 3) {
        printf("%d is prime!\n", i);
        return 0;
    }

    if (i % 2 == 0) {
        printf("%d is not prime! 2 divides it\n", i);
        return 0;
    } else if (i % 3 == 0) {
        printf("%d is not prime! 3 divides it\n", i);
        return 0;
    } else {
        while (j * j < i) {
            if (i % j == 0 || i % (j + 2) == 0) {
                printf("%d is not prime! %d divides it!\n", i, j);
                return 0;
            }
            j = j + 6;
        }
    }

    printf("%d is prime!\n", i);
    return 0;
}

int main()
{
    for (int i = 1; i < 100; i++) {
        brute_force_fact(i);
        optimization_congruence_class(i);
    }

    return 0;
}