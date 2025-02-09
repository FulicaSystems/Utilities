#include <iostream>

#define CHKLK_OVERRIDE_NEW_OP
#include "checkleak.hpp"

#include <Windows.h>

int main()
{
    CHKLK_INIT
    CHKLK_ENTRY_SNAP

    // TODO : find a better way for rng (https://stackoverflow.com/a/322995)
    srand(static_cast<unsigned>(time(0)));

    CHKLK_EXIT_SNAP
    CHKLK_DIFF_VERBOSE

    // int* a = new int;
    CHKLK_APP
    return 0;
}
