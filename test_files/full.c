// Testing callable function
float fun(float XKAD, float V) {
    float n1 = XKAD + V;
    return n1 * 80;
}

int main()
{
    // Testing complex initialization statements
    int n1 = 15 * (18 / -2) % 18;
    int n2 = n1 * n1;
    float DF = 0.8 * 3.16;
    char G = 'G';

    // Testing nested loops of various types
    for (int i = 0; i < n2 * n1 / 2; i += 1) {
        for (int j = 0; j < n2 + n1 / 2; j += 1) {
            int x = 0;
            while (x < n2) {
                x += x;
                break;
            }
        }
        break;
    }

    // Testing function calls
    DF = fun(fun(DF, 0.101 * 2), 0.9);

    // Testing conditional statements
    if (DF < (0.8 - (-DF))) {
        if (n2 != 10) {
            G = 'H';
            n1 *= 1;
            n1++;
        } else if (n1 <= 2 && (G == 'H' || n2 != 100)) {
            DF += -.6;
            if (DF == 0.00000) {
                DF = 1.01;
            }
        } else if (G >= 'H') {
            n2 -= 16;
            n2--;
        } else {
            n1 /= 2;
        }
    }

    return (n1 * 2);
}
