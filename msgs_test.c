//CSE531 
//Project-4
//Authors
//Prabhudev Terakanambi Rajendra(1215112821) and Divya Madhuri Reddy Gurram (1215129071)

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "msgs.h"

static int global_message = 0;
static int portno;
static int server_count;
static int client_count;
int activeServerPort[50]={0};
Semaphore_t *mutex;

void server(){
	int i,serverPort,serverno;

        P(mutex);
        serverPort = portno++;
        serverno = server_count++;
        activeServerPort[serverno]=serverPort;
        V(mutex);

        
	Message_t data;
        for (i=0;i<N;i++)
                {
                    data.message[i]=0;
                }
        data.reply_port=0;
	
	while(1){
		receive(serverPort,&data);
                printf("\nServer received data on port %d from client port %d\n",serverPort,data.reply_port);
		printf("Data received = ");
                for (i=0;i<N;i++)
                {
                    printf("%d\t",data.message[i]);
                    data.message[i] = data.message[i] +i;
                }
                printf("\n");
                sleep(1);
                send(data.reply_port,&data);
                printf("\nServer sending data to client port %d from server port %d\n",data.reply_port,serverPort);
				printf("Data sent = ");
				printf("\t");
                for (i=0;i<N;i++)
                {
                    printf("%d\t",data.message[i]);
                }
                printf("\n");
	}
}

void client(){
	int i, local_message,clientPort,sendPort,clientno;
        P(mutex);
        clientPort = portno++;
        clientno = client_count++;
        V(mutex);

        
	Message_t data;
        for (i=0;i<N;i++)
                {
                    data.message[i]=global_message;
                }
        global_message++;
        data.reply_port=clientPort;
	
	while(1){
                sendPort = activeServerPort[rand()%server_count];
                send(sendPort,&data);
                printf("\nClient sending data to server port %d from client port %d\n",sendPort,clientPort);
		printf("Data sent = ");
                for (i=0;i<N;i++)
                {
                    printf("\t%d",data.message[i]);
                }
                printf("\n");
                sleep(1);
		receive(clientPort,&data);
                printf("\nClient received data on port %d from server port %d\n",clientPort,sendPort);
		printf("Data received = ");
                for (i=0;i<N;i++)
                {
                    printf("%d\t",data.message[i]);
                    data.message[i] = data.message[i] +i;
                }
                printf("\n");

	}

}

int main()
{
	init_port();
	mutex = CreateSem(1);
	start_thread(server);
	printf("server 1 created\n");
	start_thread(server);
	printf("server 2 created\n");
        start_thread(client);
	printf("client 1 created\n");
	start_thread(client);
	printf("client 2 created\n");
	start_thread(client);
	printf("client 3 created\n");
    
   	run();
	while(1){
		sleep(1);
	}
    return 0;
}