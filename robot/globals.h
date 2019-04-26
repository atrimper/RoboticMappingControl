#ifndef GLOBALS_H
#define GLOBALS_H

#include "mbed.h"
#include "rtos.h"

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
extern uint32_t lidarDistance;
extern volatile bool useImu;

#endif /* GLOBALS_H */