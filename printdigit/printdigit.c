
#include<stdio.h>
#include<string.h>
#include<sys/time.h>
#include<math.h>

static int printdigt(int num)
{
	if( num>=0 && num<10 ){
		printf("%d", num);
		return 0;
	}
	return -1;
}
static int printout(int num)
{
	if(num<10){
		printdigt(num);
	}else{
		printout(num/10);
		printdigt(num%10);
	}
	return 0;
}
int main()
{
	float num=-7895.89;
	int ret=0;
	if(num<0){
		//printf("-");
		num*=-1;
	}
	float num_ft=num-(int)num;
	int num_ft_sw=0;
	int num_it = (int)num;

	if(num_ft==0){
		printout(num);
	}else{
		printout(num_it);
		printf(".");
		printdigt((int)num_ft*pow(10,3));
	}
	putchar('\n');
	return 0;
}
