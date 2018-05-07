
typedef int  TreeElement;
typedef struct SearchTreeNode * PtrToNode;
typedef PtrToNode SearchTree;

struct SearchTreeNode {
	TreeElement element;
	PtrToNode    RightNode;	
	PtrToNode	 LeftNode; 
};
