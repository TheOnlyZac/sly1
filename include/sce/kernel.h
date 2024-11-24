/**
 * @file kernel.h
 * 
 * @brief Control for Semaphores and Threads
 */
#ifndef KERNEL_H
#define KERNEL_H

#include "common.h"

// FlushCache modes
#define WRITEBACK_DCACHE 0
#define INVALIDATE_DCACHE 1
#define INVALIDATE_ICACHE 2
#define INVALIDATE_CACHE (INVALIDATE_DCACHE | INVALIDATE_ICACHE) /* XXX this is a bit extra, but should match SCE headers */

extern "C" {
    /**
     * @brief Thread parameters for initialization
     */
    struct ThreadParam {
        int status;             // Thread status
        void (*entry)(void *);  // Thread entry point
        void *stack;            // Stack address used by the thread (16-byte aligned)
        int stackSize;          // Stack size in bytes, must be a multiple of 16
        void *gpReg;            // GP register value
        int initPriority;       // Initial thread priority (1-127). Must be specified when creating a thread
        int currentPriority;    // Current thread priority
        unsigned int attr;      // Reserved for system use
        unsigned int option;    // Reserved for system use
        int	waitType;           // Wait type
        int	waitId;             // Semaphore ID if waitType is "semaphore"
        int	wakeupCount;        // Wakeup request count
    };

    /**
     * @brief Semaphore parameters for initialization
     */
    struct SemaParam {
        int currentCount;    // Current semaphore count
        int maxCount;        // Maximum semaphore count
        int initCount;       // Initial semaphore count
        int numWaitThreads;  // Number of threads waiting on the semaphore
        unsigned int attr;   // Semaphore attributes
        unsigned int option; // Optional user-defined data
    };

    /**
     * @brief Create a counting semaphore object.
     * 
     * @details Up to 256 semaphores can be created, 3 of which are reserved during runtime
     * initialization by `crt0.s` (2 from `_InitSys` and 1 from `InitThread`).
     * 
     * @param sparam Initial semaphore parameters
     * @return Semaphore ID on success, -1 if creation would exceed the maximum number of semaphores
     * or a negative value was passed for `sema->initCount`
     */
    int CreateSema(SemaParam *sparam);

    /**
     * @brief Get semaphore resource
     * 
     * @param sema Semaphore ID
     * @return Semaphore count on success, -1 on failure
     */
    int WaitSema(int sema);

    /**
     * @brief Release semaphore resource
     * 
     * @details If the `sid` value is 0 and there is no free space in the semaphore queue,
     * the thread at the wait queue start will be released and placed in READY state.
     * In all other cases, the value of the semaphore is incremented.
     * 
     * @param sid Semaphore ID
     * @return Semaphore ID on success, -1 on failure
     */
    int SignalSema(int sid);

    /**
     * @brief Create a new thread
     * 
     * @details The created thread is placed in a DORMANT state and not executed until the thread is started.
     * 
     * @param tparam Initial thread parameters
     * 
     * @return Thread ID on success, -1 on failure 
     */
    int CreateThread(struct ThreadParam *tparam);

    /**
     * @brief Get the ID of the calling thread.
     * 
     * @return Thread ID
     */
    int GetThreadId(void);

    /**
     * @brief Change the priority of a thread
     * 
     * @details The thread will be entered at the end of the ready queue at the corresponding priority.
     * The new priority setting will be valid until the thread is terminated or the priority is changed again. 
     * 
     * @param tid Thread ID
     * @param priority New priority (1-127)
     * 
     * @return The previous priority of the thread on success, -1 on failure
     */
    int ChangeThreadPriority(int tid, int priority);

    /**
     * @brief Flushes the cache.
     * @param mode Can be WRITEBACK_DCACHE, INVALIDATE_DCACHE, INVALIDATE_ICACHE, or INVALIDATE_CACHE
     */
    void FlushCache(int mode);
}

#endif // KERNEL_H
