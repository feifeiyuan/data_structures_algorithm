
typedef struct Node  *PtrToNode;
typedef PtrToNode	Position;
typedef PtrToNode	List;
typedef int 		NodeElement;

static int IsEmptyOrLast(Position position);
static Position Find(List head, NodeElement findelement);
static List Delete(List head, NodeElement deletelement);

struct Node {
		NodeElement element;
		Position Next;
};