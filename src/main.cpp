#include <fstream>
#include <streambuf>
#include <Scanner.hpp>

int main() {
    Scanner scanner;
    std::ifstream fileStream("../test_files/test_a.c");
    std::string source((std::istreambuf_iterator<char>(fileStream)),
                        std::istreambuf_iterator<char>());
    scanner.tokenize(source);
    return 0;
}