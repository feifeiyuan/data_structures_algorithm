#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>
#include "tree.h"

static DoubleTree CreateTree()
{
	int ch;
	DoubleTree tree = NULL;
	scanf("%d", &ch);
	if(ch==0){
		tree = NULL;
	}else{
		tree = (DoubleTree)malloc(sizeof(struct DoubleTreeNode));
		if(tree==NULL){
			fprintf(stderr, "there is no space\n");
			return NULL;
		}
		tree->element = ch;
		tree->LeftNode = CreateTree();//会先将所有的左子树建立好
		tree->RightNode = CreateTree();//递归补充又子树
	}
	return tree;
}

static void PreTraverse(DoubleTree tree)
{
	if(tree){
		printf("%d\n", tree->element);
		PreTraverse(tree->LeftNode);
		PreTraverse(tree->RightNode);
	}
}

static void MidTraverse(DoubleTree tree)
{
	if(tree){
		if(tree->LeftNode)
			MidTraverse(tree->LeftNode);
		printf("%d\n", tree->element);
		if(tree->RightNode)
			MidTraverse(tree->RightNode);
	}
	return;
}


static void LastTravese(DoubleTree tree)
{
	if(tree){
		if(tree->LeftNode)
			LastTravese(tree->LeftNode);
		if(tree->RightNode)
			LastTravese(tree->RightNode);
		printf("%d\n", tree->element);
	}
	return ;
}



int main()
{
	DoubleTree tree=NULL;
	tree = CreateTree();
	//printf("tree is NULL %d\n", tree==NULL);
	PreTraverse(tree);
	printf("\n");
	MidTraverse(tree);
	printf("\n");
	LastTravese(tree);
	if(tree){
		printf("element is %d\n", tree->element);
		if(tree->LeftNode)
			printf("left element is %d\n", tree->LeftNode->element);
		if(tree->RightNode)
			printf("right element is %d\n", tree->RightNode->element);
		else{
			printf("tree->RightNode is NULL %D\n", tree->RightNode==NULL);
		}
	}
	return 0;
}


