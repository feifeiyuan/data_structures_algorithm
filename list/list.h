
typedef struct Node  *PtrToNode;
typedef PtrToNode	Position;
typedef PtrToNode	List;
typedef int 		NodeElement;

struct Node {
		NodeElement element;
		Position Next;
};

extern Position CreateListCell(List ahead,  NodeElement element);
extern List CreateHead();
extern void OverViewList(List head);