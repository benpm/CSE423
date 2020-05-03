int globA = 3;
int globB = 4;

// Testing callable function
int fun(int XKAD, int V) {
    int n1 = XKAD + V;
    return n1 * 80;
}

int main()
{
    // Testing complex initialization statements
    int n1 = 15 * (18 / -2) % 18;
    int n2 = n1 * n1;
    int n3 = n1 + n1 + n2 + n2;
    int DF = 8 * n2;

    // Testing nested loops of various types
    for (int i = 0; i < n2 * n1 / 2; i += 1) {
        int f = 10;
        break;
        for (int j = 0; j < n2 + n1 / 2; j += 1) {
            int x = 0;
            while ((x < n2) || !(x >= n2)) {
				int z = 10;
                int x2 = 3;
                x2 += z + x;
                n2 -= x;
                break;
            }
        }
    }

    // Testing function calls
    DF = fun(fun(DF, 101 * 2), 9);
	printf("test: %f\n", DF);

    DF = DF * globA * globB;
    // Testing conditional statements
    if (DF < (8 - (-DF))) {
        if (n2 != 10) {
            n1 *= 1;
			n1 %= 10;
            n1++;
        } else if (n1 <= 2 && n2 != 100) {
            DF += -6;
            if (DF == 0) {
                DF = 101;
            }
        } else {
            n1 /= 2;
        }
    }
    printf("n1: %d, n2: %d, n3: %d\n", n1, n2, n3);

    goto label;
    return -1;
label:
    return (n1 * 2);
}
