#pragma once

#include <stdexcept>

// Custom assert function that doesn't call abort
inline void assert(bool assertion)
{
    if (!assertion)
    {
        printf("Assertion failed");
        exit(1);
    }
}