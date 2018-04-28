#include<stdio.h>
#include<string.h>
#include<sys/time.h>
#include<stdlib.h>
#include<errno.h>
#include"list.h"

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
	position = CreateListCell(head, 3);
	position = CreateListCell(position, 4);
	position = CreateListCell(position, 6);
	position = CreateListCell(position, 8);
	position = CreateListCell(position, 9);
	return head;
}

static Position FindPosition(Position position, NodeElement element)
{
	// static 将时间复杂度由m×n变成了m+n
	static NodeElement index = 0;
	while( position!=NULL && index!=element){
		position = position->Next;
		index++;
	}
	return position;
}

static void PrintLots(List l, List p)
{
	struct timeval start, end;
	float timeuse = 0.0;
	gettimeofday(&start,  NULL);
	Position p1 = p;
	Position l1 = l;
	while(p1!=NULL){
		// 因为链表是不连续空间，所以不能直接通过指针的运算来找到第几个元素
		l1 = FindPosition(l1, p1->element);
		if(l1!=NULL){
			printf("find data is %d\n", l1->element);
		}
		p1 = p1->Next;
	}
	gettimeofday(&end, NULL);
	timeuse = ((end.tv_sec - start.tv_sec)*1000000 + end.tv_usec - start.tv_usec)/1000;
	printf("timeuse is %f\n", timeuse);
}

static void swip(Position position_ahead, Position position)
{
	Position position_next = position->Next;
	position->Next = position->Next->Next;
	position_next->Next = position;
	position_ahead->Next = position_next;
	
}

int main()
{
	List head1 = CreateList1();
	List head2 = CreateList2();
	OverViewList(head1);
	printf("\n");
	OverViewList(head2);
	printf("\n");
	PrintLots(head2, head1);
	swip(head1, head1->Next);
	OverViewList(head1);
	return 0;
}
 
