/**
 * @file thread.h
 * 
 * @brief Semaphore, Thread, and Critical Section utilities
 */
#ifndef THREAD_H
#define THREAD_H

#include "common.h"

/**
 * @brief Details for a critical section
 */
struct CRITSECT
{
    int cEnter;
    int thread;
    int sema;
};

/**
 * @brief Create a semaphore.
 * 
 * @param initCount Initial count.
 * @param maxCount Maximum count.
 * @return The semaphore ID.
 */
int SemaCreate(int initCount, int maxCount);

/**
 * @brief Initialize a critical section.
 * 
 * @param pcritsect Critical section.
 */
void InitCritSect(CRITSECT* pcritsect);

/**
 * @brief Enter a critical section.
 * 
 * @param pcritsect Critical section.
 */
void EnterCritSect(CRITSECT* pcritsect);

/**
 * @brief Leave a critical section.
 * 
 * @param pcritsect Critical section.
 */
void LeaveCritSect(CRITSECT* pcritsect);

/**
 * @brief Initialize parameters for a rendering thread.
 */
void StartupThread();

extern CRITSECT g_athread;

#endif // THREAD_H
