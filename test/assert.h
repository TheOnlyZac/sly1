#pragma once

#include <stdexcept>
#include <exception>

// Custom assert function that doesn't call abort
inline void assert(bool assertion)
{
    if (!assertion)
    {
        printf("Assertion failed");
        exit(1);
    }
}