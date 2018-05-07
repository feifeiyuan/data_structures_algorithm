typedef char ElementType;
typedef struct HeapStruct * HeapNode;
typedef	HeapNode	PriorityHeap;


struct HeapStruct{
	int capacity;
	int size;
	ElementType	*element;
};