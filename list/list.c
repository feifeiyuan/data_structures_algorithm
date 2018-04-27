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

// 默认的是插入指定节点之后
static List Insert(List head, NodeElement insertelement, Position position)
{
	Position position_insert = NULL;
	Position position_next = NULL;
	position_insert = (Position)malloc(sizeof(struct Node));
	if(position_insert==NULL){
		fprintf(stderr,"%s:there is some error during malloc", __func__);
		return NULL;
	}
	position_insert->element = insertelement;
	if(!IsEmptyOrLast(position)){
		position_next = position->Next;
		position_insert->Next = position_next;
		position->Next = position_insert;
	}else{
		position->Next = position_insert;
	}
	return head;
}

static void DeleteList(List head)
{
	Position position = head;
	Position position_delete = NULL;
	while(position!=NULL){
		position_delete = position;
		position = position->Next;
		free(position_delete);
		position_delete = NULL;
	}
}

static Position CreateListCell(List ahead,  NodeElement element){
	Position position = NULL;
	position  = (Position)malloc(sizeof(struct Node));
	if(position==NULL){
		fprintf(stderr, "there is no space\n");
		return NULL;
	}
	position->element = element;
	ahead->Next = position;
	position->Next = NULL;
	return position;
}

static void OverViewList(List head){
	Position position = head;
	while(position!=NULL){
		printf("element is %d\n", position->element);
		position = position->Next;
	}
}

int main()
{
	List head=NULL;
	Position position = NULL;
	head  = (Position)malloc(sizeof(struct Node));
	if(head==NULL){
		fprintf(stderr, "there is no space\n");
		return -1;
	}
	head->element = 0;
	head->Next = NULL;
	
	position = CreateListCell(head, 1);
	position = CreateListCell(position, 2);
	OverViewList(head);
}