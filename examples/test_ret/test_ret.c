int funA()
{
    return 3;
}

int funB()
{
    return 4;
}

int main()
{
    printf("ret: %d\n", funA() + funB());
    return funA() + funB();
}
