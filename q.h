#include <stdio.h>
#include <stdlib.h>
#include "TCB.h"

//Create new TCB item,allocates memory,returns a pointer to the new TCB element 
TCB_t *NewItem()
{
        TCB_t *newItem;
 	newItem = (TCB_t *)malloc(sizeof(TCB_t));
	newItem->next=NULL;
	newItem->prev=NULL;
	return newItem;
}

//creates an empty Queue and return pointer to Head
//This head pointer will not hold the first element in Queue,
//rather will point to the first element in Queue,
//if there are no elements in the Queue the head points to itself.
//As explained in the class.
TCB_t *NewQueue()
{
        TCB_t *newQueue;
        newQueue = (TCB_t *)malloc(sizeof(TCB_t));
	newQueue->next=newQueue;
	newQueue->prev=newQueue;
	return newQueue;
}

//Adds the Queue item pointed by the "item" to the Queue pointed by the "Head".
void AddQueue(TCB_t *Head, TCB_t *item)
{
  TCB_t* temp=NULL;
  //Checks whether queue is empty
  if(Head->next==Head)
  {
      Head->next=item;
      Head->prev=item;
      item->next=Head;
      item->prev=Head;
  }
  else
  {
      temp = Head->prev;
      temp->next =item;
      item->prev=temp;
      Head->prev=item;
      item->next=Head;
  }
}

//Deletes an item from "Head" and returns a pointer to the deleted item. 
TCB_t* DelQueue(TCB_t *Head)
{
	TCB_t *temp=NULL;	
        // check for empty queue
	if(Head==Head->next || Head==NULL)
	{
                printf("Queue is empty,flag error");
		return NULL;               //error is handled in run function.
	}

		temp=Head->next;
		Head->next=temp->next;
		Head->next->prev=Head;
	
	return temp;
}