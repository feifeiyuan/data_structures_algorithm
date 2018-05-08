#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>

#include "heap.h"

static PriorityHeap Initialize(int MaxElement)
{
	PriorityHeap heap = NULL;
	heap =(PriorityHeap)malloc(sizeof(*heap));
	if(heap==NULL){
		fprintf(stderr, "there is no space\n");
		return NULL;
	}
	memset(heap,0,sizeof(*heap));
	
	heap->element = (ElementType *)malloc((MaxElement+1)*sizeof(ElementType));
	if(heap->element==NULL){
		fprintf(stderr, "there is no space\n");
		return NULL;
	}
	memset(heap->element, 0, sizeof(ElementType)*(MaxElement+1));
	heap->capacity = MaxElement;
	heap->size = 0;
	return heap;
}

static void Insert(ElementType x, PriorityHeap heap)
{
	int i = 0;
	//size的值是在这里发生变化的
	//printf("++heap->size is %d\n", ++heap->size);
	//printf("heap->size++ is %d\n", heap->size++);
	//printf("x is %d\n", x);
	for(i=++heap->size;heap->element[i/2]>x;i/=2){
		//printf("before: heap->size is %d\t heap->element[%d] is %d\n", heap->size, i, heap->element[i]);
		heap->element[i] = heap->element[i/2];
		//printf("after: heap->size is %d\t heap->element[%d] is %d\n", heap->size, i, heap->element[i]);
	}
	heap->element[i] = x;
	return ;
}

int main()
{
	PriorityHeap heap = NULL;
	heap = Initialize(30);
	int ar[] = { 32, 21, 16, 24, 31, 19, 68, 65, 26, 13 };  
	int i = 0;
	for ( i = 0; i < sizeof(ar)/sizeof(ar[0]); i++ ){
        Insert( ar[i], heap);
	}
	for(i=0;i<heap->size;i++){
		printf("%d\t", heap->element[i]);
	}
}
