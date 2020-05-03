int refun(int x) {
    x += 3;
    if (x < 1239) {
        refun(x * 2);
    }
    return x;
}

int main()
{
    printf("refun(10): %d\n", refun(10));
    return refun(1);
}