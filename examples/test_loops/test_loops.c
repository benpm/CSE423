int main()
{
    int x = 3;
    for (int i = 0; i < 13; i++) {
        x += x * i;
        for (int j = 0; j < 56; j += 2) {
            int z = 2;
            x -= j;
            while (z < 100) {
                z += x * x;
            }
            x += z % j;
        }
    }
    return x;
}