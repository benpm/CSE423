int globalA = 78123 * 88 - (-0 + 371 % 138);
int globalB = 222222;

int funA(int x, int y, int z)
{
    int i = x + x;
    int j = y * (x + -z);
    int k = i * j * j;
    if (z == 0) {
        z = 1;
    }
    j = y * (x % -z);
    //printf("funA(%d, %d, %d)\n", x, y, z);
    for (int zzzz = 0; zzzz != globalB; zzzz += 2) {
        if ((i < j) && (j == k || i >= k)) {
            i += 10;
            globalA -= 7;
        } else {
            i += 2;
            globalA += 10 * globalB;
        }
        if (i > 100) {
            //printf("funA exit 1\n");
            if (k + x - z + globalB != 0) {
                return i * j / (k + x - z + globalB);
            } else {
                return i * j + (k + x - z + globalA);
            }
        }
        if (i < -100) {
            //printf("funA exit 2\n");
            globalB -= 2;
            break;
        }
        if (i == 0) {
            //printf("funA exit 3\n");
            globalA *= globalB + i;
            goto AAAAHHHH;
        }
    }
    return z * (-i * j);
    AAAAHHHH:
    return globalA + globalB;
}

int funB(int f)
{
    f -= 1;
    if (f >= 10 && f < 23) {
        //printf("funB 1\n");
        return funB(f / 2) + funA(-123, 23, f * 2 * f - f);
    } else if (f < 10 && f > -10) {
        //printf("funB 2\n");
        return globalA + 69;
    } else if (f < 10 && f > -100) {
        int z = 100;
        f += f * f;
        //printf("funB 3\n");
        while (z != (z * 0)) {
            z -= funA(10, 20, f);
            if (z < 10) {
                for (int g = f; g < f * 2; g += 1) {
                    z += 420 % z + funA(2, 2, 2);
                }
                return 0;
            } else {
                return globalA * 1 * 123;
            }
        }
    } else {
        //printf("funB 4\n");
        if (f != 0) {
            return f * f + (0 - (-globalB));
        }
    }
    //printf("funB 5\n");
    return funB(f - 1);
}

int main()
{
    int accum = 0;
    for (int i = -100; i < 100; i += 1) {
        for (int j = -100; j < 100; j += 1) {
            for (int k = -100; k < 100; k += 1) {
                int val = funA(i, j, k);
                //printf("funA(%d, %d, %d) = %d\n", i, j, k, val);
                accum += val;
            }
        }
    }
    for (int i = -100; i < 100; i += 1) {
        int val = funB(i);
        //printf("funB(%d) = %d\n", i, val);
        accum += val;
    }
    return accum; // should return 19
}