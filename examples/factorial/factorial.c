int main() {
    int fact = 1, n = 10;
    if (n < 0) {
        return -1; //printf("Error! Factorial of a negative number doesn't exist.");
    } else {
        for (int i = 1; i <= n; ++i) {
            fact *= i;
        }
        return fact; //printf("Factorial of %d = %d", n, fact);
    }
    return 0;
}
