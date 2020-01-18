#include <Scanner.hpp>

int main() {
    Scanner scanner;
    std::string source = 
        "int main() {"
        "    return 0;"
        "}";
    scanner.tokenize(source);
    return 0;
}