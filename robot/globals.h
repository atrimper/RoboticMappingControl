#ifndef GLOBALS_H
#define GLOBALS_H

#include "mbed.h"

/**
 * Hardware declarations. Initializations will be in main.cpp
 */
extern Serial pc;
extern BusOut led;
extern DigitalIn pb;

/**
 * Data declarations. Initializations will be in main.cpp
 */
extern int* obstacles;
extern int trajectoryLength;
extern int* trajectory;

#endif /* GLOBALS_H */