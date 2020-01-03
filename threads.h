#include "q.h"
#define STACK_SIZE 8192 //stack size

static TCB_t* ReadyQ=NULL;      
static TCB_t* Curr_Thread;
static int count;          //global variable to update thread_id

//creates thread and returns pointer to the newly created thread.
//Return type TCB_t to keep track of threads created and their ID's
TCB_t* start_thread(void (*function)(void))
{
    TCB_t *newThread;
    newThread = NewItem();
    void *stack = malloc(STACK_SIZE);
    init_TCB(newThread,function,stack,STACK_SIZE);
    count++;
    printf("Thread %d is created\n",count);
    if(ReadyQ==NULL)
    {
       ReadyQ = NewQueue();
    }
      newThread->thread_id = count;
      AddQueue(ReadyQ,newThread);
    return(newThread);
}

void run()
{
    Curr_Thread = DelQueue(ReadyQ);
    if (Curr_Thread == NULL)
    {
        printf("Queue is empty,flag error");
    }
    else
    {
    	ucontext_t parent;
    	getcontext(&parent);//gets the current context	
    	swapcontext(&parent,&(Curr_Thread->context));//swaps main with the first thread function
    }  
}

void yield()
{
    TCB_t *Prev_Thread;
    AddQueue(ReadyQ,Curr_Thread);
    Prev_Thread= Curr_Thread;
    Curr_Thread = DelQueue(ReadyQ);	
    swapcontext(&Prev_Thread->context,&(Curr_Thread->context));//swaps current context with the next context in the queue
}