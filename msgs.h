#include "sem.h"
#define N 10
typedef struct Message
{
    int message[10];
    int reply_port;
}Message_t;

//uses strategy 2, one mutex one producer and one consumer per port.
typedef struct Port
{
    Message_t msg[10];
    Semaphore_t *mutex,*full,*empty;
    int rear;
    int front;
}Port_t;

Port_t port[100];

void init_port()
{
    for (int i = 0; i<100;i++)
    { 
        port[i].rear = port[i].front=0;
        port[i].mutex = CreateSem(1);
        port[i].full = CreateSem(0);
        port[i].empty = CreateSem(10);
    }
}

void send(int server_Port, Message_t *buffer)
{
    P(port[server_Port].empty);
    P(port[server_Port].mutex);
    for(int i =0; i<N;i++)
    {
        port[server_Port].msg[port[server_Port].rear]= *buffer;
    } 
    port[server_Port].rear = (port[server_Port].rear+1)%N;
    V(port[server_Port].mutex);
    V(port[server_Port].full);
}

void receive(int server_Port, Message_t *buffer)
{
    P(port[server_Port].full);
    P(port[server_Port].mutex);
    *buffer = port[server_Port].msg[port[server_Port].front]; 
    port[server_Port].front = (port[server_Port].front+1)%N;
    V(port[server_Port].mutex);
    V(port[server_Port].empty);
}
