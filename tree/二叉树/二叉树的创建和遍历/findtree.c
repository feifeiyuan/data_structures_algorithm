#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <time.h>

typedef struct FindTree * Tree;

#define ERROR		-22

struct FindTree{
		int element;
		Tree	left;
		Tree	right;
};


static int get_rand()
{
	int num = 0;
	num = 1+(rand()%100);
	return num;
}

static int InsertTree(Tree tree, Tree root)
{
	if(tree==NULL||root==NULL){
		//fprintf(stderr, "%s should not be null\n", __func__);
		return ERROR;
	}
	if(tree->element>=root->element){
		if(InsertTree(tree, root->right)<0){
			root->right = tree;
		}
	}else{
		if(InsertTree(tree, root->left)<0){
			root->left = tree;
		}
	}
	return 0;
}

static int CreatTree(Tree root, int element)
{
	Tree tree = NULL;
	if(root==NULL){
		fprintf(stderr, "%s should not be null\n", __func__);
		return ERROR;
	}
	tree = (Tree)malloc(sizeof(*tree));
	if(tree==NULL){
		fprintf(stderr, "there is no space\n");
		return ERROR;
	}
	tree->element = element;
	//printf("%s:%d\n", __func__, tree->element);
	tree->left = NULL;
	tree->right = NULL;
	
	// find correct location
	InsertTree(tree, root);
	
	return 0;
}

static int MiddleView(Tree tree)
{
	if(tree==NULL){
		//fprintf(stderr, "%s should not be null\n", __func__);
		return ERROR;	
	}
	printf("%d\n", tree->element);
	//printf("%d\n", (tree->left==NULL));
	MiddleView(tree->left);
	MiddleView(tree->right);
	return 0;
}


int main()
{
	Tree root = NULL;
	srand(time(NULL));
	
	root = (Tree)malloc(sizeof(*root));
	if(root==NULL){
		fprintf(stderr, "there is no space\n");
		return ERROR;
	}
	root->element = 3;
	root->left = NULL;
	root->right = NULL;
	
	CreatTree(root, 2);
	CreatTree(root, 4);
	CreatTree(root, 5);
	CreatTree(root, 1);
	
	MiddleView(root);
}