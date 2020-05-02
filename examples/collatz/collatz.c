int collatz(int i)
{
    int iters = 0;
    while (i != 1) {
        if (i % 2 == 0) {
            i = i / 2;
        } else {
            i = 3 * i + 1;
        }
        iters++;
    }

    return iters;
}

int main()
{
    for (int i = 1; i < 100; i++) {
        printf("%d: %d\n", i, collatz(i));
    }

    return collatz(100);
}