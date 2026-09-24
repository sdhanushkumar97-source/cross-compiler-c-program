#include<stdio.h>
int main()
{
	int n;
	printf("enter N");
	scanf("%d",&n);
	for(int i=1;i<n;i+=2)
	{
		printf("%d",i);
	}
	return 0;
}
