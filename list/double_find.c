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
	position = CreateListCell(head, 2);
	position = CreateListCell(position, 3);
	position = CreateListCell(position, 4);
	position = CreateListCell(position, 5);
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

int main()
{
	List head1 = CreateList1();
	List head2 = CreateList2();
	OverViewList(head1);
	printf("\n");
	OverViewList(head2);
}
 
