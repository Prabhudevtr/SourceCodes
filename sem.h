#include "threads.h"

typedef struct Semaphore
{
    int count;
    TCB_t *queue;
}Semaphore_t;

// mallocs a semaphore structure, initializes it to the InitValue and returns the pointer to the semaphore.	
Semaphore_t *CreateSem(int InputValue)
{
    Semaphore_t * sem = (Semaphore_t*)malloc(sizeof(Semaphore_t));
    if(sem==NULL)
    {
        printf("Error allocating memory for semaphore");
    }
    else
    {
        sem->count = InputValue;
        sem->queue = NewQueue();
    }
    return sem;
}

// takes a pointer to a semaphore and performs P, i.e. decrements the semaphore, and if the value is less than zero then blocks the thread in the queue associated with the semaphore.        
void P(Semaphore_t *sem)
{
    sem->count--;
    if (sem->count < 0)
    {
        TCB_t *temp;
        temp = Curr_Thread;
        Curr_Thread = DelQueue(ReadyQ);
        AddQueue(sem->queue, temp);
        swapcontext(&temp->context,&(Curr_Thread->context));
    }
}

// increments the semaphore, and if the value is 0 or negative,
//then takes a PCB out of the semaphore queue and puts it into the ReadyQ.
void V(Semaphore_t *sem)
{
    sem->count++;
    if(sem->count<=0)
    {    
        AddQueue(ReadyQ,DelQueue(sem->queue));
    }
    yield();
}



