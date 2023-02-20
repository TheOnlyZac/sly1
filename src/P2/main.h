#pragma once

static int g_chpzArgs;
static char** g_aphzArgs;

static int g_cframe;

int main(int cphzArgs, char* aphzArgs[]);
void Startup();
void MainDebug(); // temp, called by main to show that everything's working
