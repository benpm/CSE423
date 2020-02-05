#include <stdio.h>

int main (  ) {
    int 3foo = 2;
    @@`@ // invalid
    // @@@ valid
    `@@``@ //invalid
    // ``` // VALID

    // VALID
    int \
    three \
    = \
    2;
}