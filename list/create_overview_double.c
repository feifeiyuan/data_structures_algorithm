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
	head->Ahead = NULL;
	head->Next = NULL;
	return head;
}

// 传入的指针应该也只是被copy了一份
static void OverViewList(List tail)
{
	Position position = tail;
	while(position!=NULL){
		printf("element is %d\n", position->element);
		position = position->Next;
	}
	return;
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
	return head;
}


static Position CreateList2()
{
	List head =  CreateHead();
	Position position = NULL;
	position = CreateListCell(head, 2);
	position = CreateListCell(position, 4);
	position = CreateListCell(position, 6);
	position = CreateListCell(position, 9);
	position = CreateListCell(position, 10);
	return head;
}

static void swip(Position ahead, Position position)
{
	Position position_next = position->Next;
	position->Next = position_next->Next;
	position_next->Next->Ahead = position;
	ahead->Next = position_next;
	position_next->Ahead = ahead;
	position_next->Next = position;
	position->Ahead = position_next;
}

static void CommonData(List head1, List head2)
{
	Position position1 = head1;
	Position position2 = head2;
	int flag = 0;
	while(position1!=NULL){
		while(position2!=NULL){
			flag = 0;
			if(position1->element == position2->element){
				flag = 1;
				printf("position1->element is %d\n", position1->element);
			}else if(position1->element < position2->element){
				break;
			}
			position2 = position2->Next;
		}
		position1 = position1->Next;
	}
	return;
}

static void CommonDataForAll(List head1, List head2)
{
	Position position1 = head1;
	Position position2 = head2;
	while(position1!=NULL){
		while(position2!=NULL){
			if(position1->element <= position2->element){
				break;
			}
			position2 = position2->Next;
		}
		if(position1->element != position2->element){
			printf("head->element is %d\n", position1->element);
		}
		position1 = position1->Next;
	}
	printf("end");
	return;
}

static void AllData(List head)
{
	while(head!=NULL){
		printf("head->element is %d\n", head->element);
		head = head->Next;
	}
	
}

int main()
{
	List head1 = CreateList1();
	OverViewList(head1); 
	printf("\n");
	List head2 = CreateList2();
	OverViewList(head2);
	printf("\n");
	//CommonData(head1, head2);
	AllData(head2);
	CommonDataForAll(head1, head2);
	//printf("\n");
	//swip(head1->Next, head1->Next->Next);
	//OverViewList(head1);
	return 0;
}
 
