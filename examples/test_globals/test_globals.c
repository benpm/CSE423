int v = 1 + 2 * 3;
int x = 7 / (12 * 6);
int z = 13;

int fun()
{
    v += 9;
    x += 1 + v;
    z += 3 + x;
    return v;
}

int main()
{
    v += 2;
    x = 3;
    for (int i = 0; i < 7; i++) {
        x += fun();
    }
    printf("v: %d, x: %d, z: %d\n", v, x, z);
    return v + x + z;
}