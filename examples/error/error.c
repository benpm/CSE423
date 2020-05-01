// Error: function main undefined

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
int foo2() {
    int a;
    int b = 10, c = 11; // Warning: unused variable c
    int d = a + b; // Warning: uninitialized variable a
    goto bar;
bar:
    d(); // Error: improper use of symbol d
    return foo() * d + e; // Error: e not declared
}
