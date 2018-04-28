
typedef struct Node  *PtrToNode;
typedef PtrToNode	Position;
typedef PtrToNode	List;
typedef int 		NodeElement;

struct Node {
		Position Ahead;
		NodeElement element;
		Position Next;
};

static Position CreateListCell(List ahead,  NodeElement element);
static List CreateHead();
static void OverViewList(List head);