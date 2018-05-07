#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>
#include "tree.h"

static SearchTree CreateTree(void)
{
	SearchTree tree = NULL;
	int element = 0;
	scanf("%d", &element);
	if(element!=-1){
		tree = (SearchTree)malloc(sizeof(*tree));
		if(tree==NULL){
			fprintf(stderr,"there is no space\n");
			return NULL;
		}
		tree->element = element;
		tree->LeftNode = CreateTree();
		tree->RightNode = CreateTree();
	}
	return tree;
}

static void MidOverview(SearchTree tree)
{
	if(tree){
		printf("\t%d", tree->element);
		MidOverview(tree->LeftNode);
		MidOverview(tree->RightNode);
	}
	return;
}

// 想要改变指针的值还是需要将他作为返回值，不然就是传入二级指针
static SearchTree MakeEmpty(SearchTree tree)
{
	if(tree){
		MakeEmpty(tree->LeftNode);
		MakeEmpty(tree->RightNode);
		free(tree);
		tree = NULL;
	}
	return tree;
}

// 实际上这样会将所有的节点都遍历一遍而忽略了查找二叉树的特点
// 以root为界限开始区分两者
static SearchTree FindNode(TreeElement element, SearchTree tree)
{
	SearchTree ret_tree = NULL;
	if (tree){
		if(element==tree->element){
			ret_tree = tree;
			return ret_tree;
		}
		
		ret_tree = FindNode(element, tree->LeftNode);
		ret_tree = FindNode(element, tree->RightNode);
	}
	return ret_tree;
}

// 抓住了查找二叉树的特点，可以更加精确的进行查找
static SearchTree Find(TreeElement element, SearchTree tree)
{
	if(tree){
		if(tree->element==element){
			return tree;
		}else if(tree->element>element){
			return Find(element, tree->LeftNode);
		}else{
			return Find(element, tree->RightNode);
		}
	}
	return NULL;
}

// 将尾递归转换成赋值和goto语句
static SearchTree FindNoLoop(TreeElement element, SearchTree tree)
{
next:
	if(tree){
		if(tree->element==element){
			return tree;
		}else{
			if(tree->element>element)
				tree = tree->LeftNode;
			else
				tree = tree->RightNode;
			goto next;
		}
	}
	return NULL;	
}

static SearchTree FindMax(SearchTree tree)
{
next:
	if(tree){
		if(tree->RightNode == NULL)
			return tree;
		tree = tree->RightNode;
		goto next;
	}
	return tree;
}

static SearchTree FindMin(SearchTree tree)
{
	if(tree){
		if(tree->LeftNode == NULL)
			return tree;
		return FindMin(tree->LeftNode);
	}
	return NULL;
}

static SearchTree CreateTreeCell(TreeElement element)
{
	SearchTree tree = NULL;
	tree = (SearchTree)malloc(sizeof(*tree));
	if(tree==NULL){
		fprintf(stderr,"there is no space\n");
		return NULL;
	}
	tree->element= element;
	tree->RightNode = NULL;
	tree->LeftNode = NULL;
	return tree;
}
static SearchTree Insert(TreeElement element, SearchTree tree)
{
	if(tree){
		if(element>tree->element){
			if(tree->RightNode==NULL){
				tree->RightNode = CreateTreeCell(element);
			}else{
				Insert(element, tree->RightNode);
			}
		}else{
			if(tree->LeftNode==NULL){
				tree->LeftNode = CreateTreeCell(element);
			}else{
				Insert(element, tree->LeftNode);
			}
		}
		return tree;
	}
	return NULL;
}

static SearchTree InsertNode(TreeElement element, SearchTree tree)
{
	if(tree==NULL){
		
		tree = (SearchTree)malloc(sizeof(*tree));
		if(tree==NULL){
			fprintf(stderr,"there is no space\n");
			return NULL;
		}
		tree->element= element;
		tree->RightNode = NULL;
		tree->LeftNode = NULL;
	}else if(element>tree->element){
		//需要将返回值指向tree->RightNode
		tree->RightNode = InsertNode(element, tree->RightNode);
	}else{
		// 需要将返回值指向tree->LeftNode
		tree->LeftNode = InsertNode(element, tree->LeftNode);
	}
	return tree;
}
static SearchTree Delete(TreeElement element, SearchTree tree)
{
	#if 0
	if(tree){
		if(element>tree->element){
			tree->RightNode = Delete(element, tree->RightNode);
		}else if(element<tree->element){
			tree->LeftNode = Delete(element, tree->LeftNode);
		}else{

			if(tree->RightNode!=NULL&&tree->LeftNode!=NULL){
				SearchTree tree_min = FindMin(tree->RightNode);
				if(tree_min){
					printf("tree->element is %d\n", tree->element);
					tree->element = tree_min->element;
					tree->RightNode = Delete(tree_min->element, tree->RightNode);
				}
			}else{
				SearchTree tree_temp = tree;
				if(tree->RightNode){
					tree = tree->RightNode;
				}else if(tree->LeftNode){
					tree = tree->LeftNode;
				}
				if(tree==tree_temp){//两个指针同时指向同一块内存，需要将其置为NULL
					tree = NULL;
				}
				free(tree_temp);
				tree_temp = NULL;
			}
		}
		return tree;
	}
	#endif
	SearchTree find_tree = Find(element, tree);
	if(find_tree){
		if(find_tree->RightNode!=NULL&&find_tree->LeftNode!=NULL){
			SearchTree tree_min = FindMin(find_tree->RightNode);
			if(tree_min){
				printf("tree->element is %d\n", find_tree->element);
				find_tree->element = tree_min->element;
				find_tree->RightNode = Delete(tree_min->element, find_tree->RightNode);
			}
		}else{
			SearchTree tree_temp = find_tree;
			if(find_tree->RightNode){
				find_tree = find_tree->RightNode;
			}else if(find_tree->LeftNode){
				find_tree = find_tree->LeftNode;
			}
			//两个指针同时指向同一块内存，需要将其置为NULL
			if(find_tree==tree_temp){
				free(tree_temp);
				tree_temp = NULL;
				find_tree = NULL;
			}else{
				free(tree_temp);
				tree_temp = NULL;
			}

			if(tree_temp)
				printf("tree_temp is %d\n", tree_temp->element);
			if(find_tree)
				printf("find_tree is %d\n", find_tree->element);
		}
		return tree;
	}
	return NULL;
}
int main()
{
	SearchTree tree = NULL;
	SearchTree search_tree = NULL;
	SearchTree find_tree = NULL;
	SearchTree find_tail = NULL;
	tree = CreateTree();
	
	//tree = InsertNode(5,tree);
	//MidOverview(tree);
	
	tree = Delete(4, tree);
	MidOverview(tree);
	
#if 0
	find_tree = FindMin(tree);
	if(find_tree){
		printf("find %d\n", find_tree->element);
	}
	//MidOverview(tree);
	//tree = MakeEmpty(tree);
	//printf("tree is NULL %d\n", tree==NULL);
	//MidOverview(tree);
	search_tree = FindNode(4, tree);
	if(search_tree){
		printf("find node %d\n", search_tree->element);
	}
	find_tree = Find(4, tree);
	if(find_tree){
		printf("find %d\n", find_tree->element);
	}
	find_tail = FindNoLoop(4, tree);
	if(find_tail){
		printf("tail %d\n", find_tail->element);
	}
#endif
	
	return 0;
}