#include<stdio.h>
#include<string.h>
#include<sys/time.h>
#include<stdlib.h>
#include<errno.h>
#include"list.h"

// 空链表是指只有一个节点
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
	while(position!=NULL && position->element != findelement){
		position=position->Next;
	}
	return position;
}

// 找到指定元素节点的前趋节点
// 使用的前提条件是前趋节点存在
static List FindPrevious(List head, NodeElement findelement)
{
	Position position_ahead = head;
	while(position_ahead->Next!=NULL&&position_ahead->Next->element!=findelement){
		position_ahead = position_ahead->Next;
	}
	return position_ahead;
}

// 删除为第一个元素;未找到需要删除的元素
// 返回链表的头指针
// free实际上只是将他的内容清空
static List Delete(List head, NodeElement deletelement)
{
	Position position=head;
	Position position_ahead=NULL;
	if(head!=NULL&&head->element==deletelement){
		free(head);
		head=NULL;
		return head;
	}
	position_ahead = FindPrevious(head,deletelement);

	if(position_ahead!=NULL){	
		position = position_ahead->Next;
		position_ahead->Next = position->Next;
		free(position);
		position = NULL;
	}
	return head;
}

static List Insert(List head, NodeElement insertelement, Position position)
{
	
}
int main()
{
	printf("hello world\n");
}