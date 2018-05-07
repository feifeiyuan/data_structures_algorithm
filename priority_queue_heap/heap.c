#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>

#include "heap.h"

static PriorityHeap Initialize(int MaxElement)
{
	PriorityHeap head = NULL;
	head =(PriorityHeap)malloc(sizeof(*head));
	if(head==NULL){
		fprintf(stderr, "there is no space\n");
		return NULL;
	}
	memset(head,0,sizeof(*head));
	
	head->element = (ElementType *)malloc(MaxElement*sizeof(ElementType));
	if(head->element==NULL){
		fprintf(stderr, "there is no space\n");
		return NULL;
	}
	memset(head->element, 0, sizeof(ElementType)*MaxElement);
	head->capacity = MaxElement;
	head->size = 0;
	
}

int main()
{
	
}
