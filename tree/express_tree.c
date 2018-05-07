#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>
#include "tree.h"

static DoubleTree CreatExpressTree(char *express)
{
	unsigned int len = strlen(express);
	DoubleTree statck[len];
	int top = 0;
	for(char *p=express; p!=express+len;p++){
		DoubleTree tree = (DoubleTree)malloc(sizeof(struct DoubleTreeNode));
		if(tree==NULL){
			fprintf(stderr,"%s: there is no space", __func__);
			return NULL;
		}
		if(*p=='+'||*p=='-'||*p=='*'||*p=='/'){
			DoubleTree tree_right = statck[--top];
			DoubleTree tree_left = statck[--top];
			statck[top] = tree;
			statck[top]->element = *p;
			statck[top]->LeftNode = tree_left;
			statck[top]->RightNode = tree_right;
			
		}else{
			statck[top] = tree;
			statck[top]->element = *p;
			statck[top]->LeftNode = NULL;
			statck[top]->RightNode = NULL;
		}
		top++;
	}
	return statck[0];
}

static void LastOverview(DoubleTree tree)
{
	if(tree){
		LastOverview(tree->LeftNode);
		LastOverview(tree->RightNode);
		printf("%c ", tree->element);
	}
	return;
}

int main(void)
{
	DoubleTree tree = NULL;
	char express[] = "ab+cde+**";
	tree = CreatExpressTree(express);
	LastOverview(tree);
	return 0;
}