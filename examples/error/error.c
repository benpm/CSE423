int foo() {
    int n;
    int d;
    int n = 10; // Error: variable redeclared
    for (int n = 1; n < 10; n++) { // Warning; variable shadowed
        d = 5;
    }
phoo: // Warning: unused label
    return n;
}

// Warning: unused function
char bar() {
    return 'c';
}

int fun(int d) {
    return d;
}

int main() {
    int a;
    int b = 10, c = 11; // Warning: unused variable c
    int d = a + b; // Warning: uninitialized variable a
    fun(1, 2); // Error: incorrect number of parameters
    goto bar;
bar:
    goto foo; // Error: undefined label
    d(); // Error: improper use of symbol d
    return foo() * d + e; // Error: e not declared
}
