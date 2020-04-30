int refun(int x) {
    x += 3;
    if (x < 1239) {
        refun(x * 2);
    }
    return x;
}

int main()
{
    return refun(1);
}