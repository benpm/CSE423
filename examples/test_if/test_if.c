int main()
{
    int x = 3;
    if (x < 3) {
        x = x + 1;
        x = x + x + 4;
        if (x < 3) {
            x = x - 100;
        }
        if (x > 3) {
            x = x + 1234;
        }
    }
    if (x > 3) {
        x = x + 7;
        x = x + x + 4;
        if (x < 3) {
            x = x - 100;
        }
        if (x > 3) {
            x = x + 1234;
        }
    }
    if (x == 3) {
        x = x + x + 4;
        if (x < 3) {
            x = x - 100;
        }
        if (x > 3) {
            x = x + 1234;
        }
    }

    printf("x: %d\n", x);

    return x;
}