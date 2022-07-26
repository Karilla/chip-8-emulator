
#include <stdlib.h>
#include <stdio.h>
#include "state.h"

int main(int argc, char *argv[])
{
    printf("Bonjour ");
    State state;
    init_state(&state);
    print_state(&state);
    return 0;
}