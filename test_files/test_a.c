int main(int argc, char **argv) {
    int value = 0;
    for (int i = 0; i < 100; i++) {
        if (i % 10 == 5) {
            value += i;
        }
    }
    return value;
}