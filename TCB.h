# include<ucontext.h>
# include<string.h>

//structure for TCB
typedef struct TCB_t
{
	int thread_id;
	ucontext_t context;
	struct TCB_t *prev;
	struct TCB_t *next; 
}TCB_t;

//TCB initialization function
void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size)
{
	 memset(tcb, '\0', sizeof(TCB_t));       
	 getcontext(&tcb->context);
	 tcb->context.uc_stack.ss_sp = stackP;
	 tcb->context.uc_stack.ss_size = (size_t) stack_size;
	 makecontext(&tcb->context, function, 0);
}

//function to return thread ID
 int getThreadId(TCB_t* thread)
{
return(thread->thread_id);
}
