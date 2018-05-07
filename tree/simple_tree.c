#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>
#include "tree.h"

static void PrintTree(Tree tree, int index)
{
	if(tree){
		while(index--){
			printf("        ");
		}
		printf("%s\n", tree->element);
	}
}

// 算得上是先序排序
static void ListDirTree(Tree tree, int index)
{
	PrintTree(tree, index);
	Tree tree_node = tree->FirstChild;
	while(tree_node){
		ListDirTree(tree_node, index+1);
		//printf("index is %d\n", index);
		tree_node = tree_node->NextSibling;
	}
}

static Tree CreateRootTree()
{
	Tree tree =  (Tree)malloc(sizeof(struct TreeNode));
	if(tree==NULL){
		fprintf(stderr,"%s there is no space during malloc struct TreeNode\n", __func__);
		return NULL;
	}

	tree->element = (TreeElement)malloc(sizeof(sizeof(char)*100));
	if(tree->element == NULL){
		fprintf(stderr,"%s there is no space during malloc tree->element\n", __func__);
		return NULL;
	}
	strcpy(tree->element, "usr");
	tree->FirstChild = NULL;
	tree->NextSibling = NULL;
	return tree;
}

static PtrToNode AddressToPtr(char * address, Tree tree)
{
	char *end = strchr(address,'/');//查找/第一次出现的位置
	PtrToNode PtrSameLevel = NULL;
	if(end==NULL){//直接插入当前节点,这是递归的基准情形
		return tree;
	}
	
	// 找到树的源头
	char *next = strchr(end+1,'/');
	char temp_file[100];
	if(next!=NULL){
		int index=0;
		for(char *p=end+1; p!=next;p++){
			temp_file[index]=*p;
			index++;
		}
		temp_file[index]='\0';	
	}else{
		strcpy(temp_file, end+1);
	}
	
	
	//printf("temp_file is %s\n", temp_file);
	if(tree->FirstChild){
		//printf("tree->FirstChild->element is %s\n", tree->FirstChild->element);
		PtrToNode child = tree->FirstChild;
		// 优先查找第一个孩子，然后查找兄弟姐妹
		if(strcmp(child->element,temp_file)==0){
			
			PtrSameLevel = child;
			return AddressToPtr(end+1, PtrSameLevel);
		}
			
		while(child->NextSibling){
			child = child->NextSibling;	
			if(strcmp(child->element,temp_file)==0){
				break;
			}
		}
		
		if(child){
			PtrSameLevel = child;
			return AddressToPtr(end+1, PtrSameLevel);
		}else{
			return NULL;
		}
	}else{
		printf("tree->FirstChild is NULL\n");
		return NULL;
	}
}

static void Insert(char * address, char *filename, Tree tree)
{
	PtrToNode ptrtonode = AddressToPtr(address+1, tree); //找到应该插入的位置
	PtrToNode NewNode = (PtrToNode)malloc(sizeof(struct TreeNode));
	if(NewNode==NULL){
		fprintf(stderr,"%s there is no space during malloc struct TreeNode\n", __func__);
		return;
	}
	NewNode->FirstChild =NULL;
	NewNode->NextSibling = NULL;
	NewNode->element = (TreeElement)malloc(sizeof(char)*100);
	if(NewNode->element==NULL){
		fprintf(stderr,"%s there is no space during malloc tree->element\n", __func__);
		return;
	}
	strcpy(NewNode->element, filename);
	
	PtrToNode child = ptrtonode->FirstChild;
	if(child==NULL){//优先插入第一个孩子
		ptrtonode->FirstChild = NewNode;//这里一定是tree->FirstChild,不能是child,因为child是NULL
	}else{
		// 然后插入兄弟姐妹
		while(child->NextSibling){//找到最后一个兄弟
			child = child->NextSibling;
		}
		child->NextSibling = NewNode;
	}
}

// 后续排序
static void ListDirTreeAfter(Tree tree, int index)
{
	
	Tree tree_node = tree->FirstChild;
	while(tree_node){
		//ListDirTree(tree_node, index+1);
		printf("%s\n", tree_node->element);
		tree_node = tree_node->NextSibling;
	}
	printf("father is %s\n", tree->element);
	if(tree->FirstChild){
		ListDirTreeAfter(tree->FirstChild, 0);
	}else{
		while(tree->NextSibling){
			ListDirTreeAfter(tree->NextSibling, 0);
			tree = tree->NextSibling;
		}
	}
	printf("\n");
}

int main()
{
	Tree tree=CreateRootTree();
	
	Insert("/usr", "aaa(1)", tree);  
	Insert("/usr", "bbb(2)", tree);  
	Insert("/usr", "ccc(3)", tree); 
	Insert("/usr", "ddd(4)", tree);
	Insert("/usr", "eee(5)", tree);
	Insert("/usr/eee(5)", "wanger(1)", tree);
	Insert("/usr/bbb(2)", "zhangsan(6)", tree); 
	Insert("/usr/bbb(2)/zhangsan(6)", "lisi(7)", tree); 
	Insert("/usr/bbb(2)/zhangsan(6)/lisi(8)", "lisi1(1)", tree); 
	Insert("/usr/bbb(2)/zhangsan(6)/lisi(8)", "lisi2(1)", tree); 
	Insert("/usr/ccc(3)", "lisi(1)", tree); 	
	ListDirTree(tree,0);
	printf("\n");
	ListDirTreeAfter(tree,0);
	return 0;
}


