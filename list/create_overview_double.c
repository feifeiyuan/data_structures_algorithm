#include<stdio.h>
#include<string.h>
#include<sys/time.h>
#include<stdlib.h>
#include<errno.h>
#include"double_list.h"

static Position CreateListCell(List ahead,  NodeElement element){
	Position position = NULL;
	position  = (Position)malloc(sizeof(struct Node));
	if(position==NULL){
		fprintf(stderr, "there is no space\n");
		return NULL;
	}
	position->element = element;
	ahead->Next = position;
	position->Ahead = ahead;
	position->Next = NULL;
	return position;
}

static List CreateHead()
{
	List head = NULL;
	Position position = NULL;
	head  = (Position)malloc(sizeof(struct Node));
	if(head==NULL){
		fprintf(stderr, "there is no space\n");
		return NULL;
	}
	head->element = 0;
	head->Next = NULL;
	return head;
}

static void OverViewList(List tail)
{
	Position position = tail;
	while(position!=NULL){
		printf("element is %d\n", position->element);
		position = position->Ahead;
	}
}

static Position CreateList1()
{
	List head =  CreateHead();
	Position position = NULL;
	position = CreateListCell(head, 1);
	position = CreateListCell(position, 2);
	position = CreateListCell(position, 3);
	position = CreateListCell(position, 4);
	position = CreateListCell(position, 6);
	return position;
}

int main()
{
	List tail = CreateList1();
	OverViewList(tail);
	
}
 
