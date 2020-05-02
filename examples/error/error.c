int foo() {
    int n;
    int d; // Warning: unused variable d
    int n = 10; // Error: variable n redeclared
    break; // Error: break not inside loop
    for (int n = 1; n < 10; n++) { // Warning: variable n shadowed
        d = 5;
    }
    while (n < 12) {
        if (n > 11) {
            break;
        }
    }
    return n;
}

char bar() { // Warning: unused function bar
    return 'c';
}

int fun(int d) { // Warning: unused parameter
    if (d > 12) {
        return; // Error: return has no value
    }
    return 4;
}

int a = 5;

int main() {
    float a; // Warning: variable a shadowed
    int b = 10, c = 11; // Warning: unused variable c
    int d = a + b; // Warning: uninitialized variable a
    fun(1, 2); // Error: incorrect number of parameters
    d = b + fun;
    goto bar;
bar:
    goto foo; // Error: undefined label
    d(); // Error: improper use of symbol d
    return foo() * d + e; // Error: e not declared
}
