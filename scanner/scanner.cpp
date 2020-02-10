#include <iostream>

extern int yylex();

int main() {
    while (yylex());
}