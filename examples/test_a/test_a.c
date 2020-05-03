int main() {
    int i = 0;
    int j = i;
    int k = 10;
    i = i + k;
    j = i + 7;
    k = 4 + 20;

    printf("i: %d, j: %d, k: %d\n", i, j, k);

    return i;
}