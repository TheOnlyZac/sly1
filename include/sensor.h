#ifndef SENSOR_H
#define SENSOR_H

#include "common.h"
#include <so.h>

struct SENSOR : public SO
{
    undefined1 unknown[12];
    // ...
};

// ...

#endif // SENSOR_H