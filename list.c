#include<stdio.h>
#include<string.h>
#include<sys/time.h>
#include<stdlib.h>
#include<errno.h>
#include"list.h"

static int IsEmptyOrLast(Position position)
{
	if(position==NULL){
		fprintf(stderr, "position is NULL\n");
		return EINVAL;
	}
	return (position->Next == NULL);
}

// 链表有0个元素; 链表有1个元素; 链表有n个元素，n>=2
// 找到返回元素位置，否则返回NULL
static Position Find(List head, NodeElement findelement)
{
	Position position=head;
	IsEmptyOrLast(position);
	while(position!=NULL && position->element != findelement){
		position=position->Next;
	}
	return position;
}

// 删除为第一个元素;未找到需要删除的元素
// 返回链表的头指针
static List Delete(List head, NodeElement deletelement)
{
	Position position=head;
	Position position_ahead=NULL;
	Position position_next=NULL;
	IsEmptyOrLast(position);
	if(position!=NULL&&position->element==deletelement){
		free(head);
		head=NULL;
		return head;
	}
	while(position!=NULL && position->element!=deletelement){
		position_ahead=position;
		position=position->Next;
	}
	if(position_ahead!=NULL){
		position_next = position->Next;
		position_ahead->Next = position_next;
		free(position);
		position = NULL;
	}
	return head;
}
int main()
{
	printf("hello world\n");
}