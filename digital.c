#include<stdio.h>
int main()
{
	int n,r=0,sum=0;
	printf("enter n");
	scanf("%d",&n);
	while(n!=0)
	{
		r = n/10;
		n = n/10;
		
			sum = sum+r;
	}
		
		printf(" %d",sum);
	
	return 0;
}
