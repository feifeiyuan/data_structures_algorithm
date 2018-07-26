#include <stdio.h>
#include <error.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
 
#define ERROR  -22
 
#define DEBUG	0

int main()
{
	int arr[] = {3,1,4, 6, 2, 0};
	int i = 0, j = 0, k = 0;
	int size = sizeof(arr)/sizeof(arr[0]);
	printf("%d\n", size);
	int insert = 0;
	for(i=1; i<size; i++){
		insert = arr[i];
		for(j=i; j>0; j--){
			if(insert<arr[j-1]){
				arr[j] = arr[j-1];
			}else{
				break;
			}
		}
		arr[j] = insert;
	}
	
	for(i=0; i<size; i++){
		printf("%d\t", arr[i]);
	}
	printf("\n");
}