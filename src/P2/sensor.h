#pragma once
#include <util.h>

typedef unsigned char byte;

enum class SENSORS
{
    // todo
};

// todo rewrite struct
struct SENSOR
{
    undefined4 field_0x0;
    int field_0x4;
    int field_0x8;
    char padding[0x57c];
    SENSORS sensors;
    float tSensors;
    SENSORS sensorsInitial;
    int coidTrigger;
    undefined4 field_0x598;
    undefined4 field_0x59c;
    undefined4 field_0x5a0;
    undefined4 field_0x5a4;
    int coidNoTrigger;
    undefined4 field_0x5ac;
    undefined4 field_0x5b0;
    undefined4 field_0x5b4;
    undefined4 field_0x5b8;
    int ccidTrigger;
    undefined4 field_0x5c0;
    undefined4 field_0x5c4;
    undefined4 field_0x5c8;
    undefined4 field_0x5cc;
    int ccidNoTrigger;
    undefined4 field_0x5d4;
    undefined4 field_0x5d8;
    undefined4 field_0x5dc;
    undefined4 field_0x5e0;
    int fTriggerAll;
    float dtEnabling;
    float dtDisabling;
    int fRemainDisabledIndefinite;
    undefined4 field_0x5f4;
    undefined4 field_0x5f8;
    float svtRestore;
};
