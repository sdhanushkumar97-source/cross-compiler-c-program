#include<stdio.h>
int main()
{
	int n,sum=0;
	printf("enter n");
	scanf("%d",&n);
	for(int i=2;i<=2*n;i+=2)
	{
		sum+=i;
	}
		printf("sum=%d",sum);
		return 0;
	}
