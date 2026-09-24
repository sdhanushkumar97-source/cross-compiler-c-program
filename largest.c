#include<stdio.h>
int main()
{
	int n,num,largest;
	printf("enter n");
	scanf("%d",&n);
	printf("enter %d numbers:\n",n);
	scanf("%d",&largest);
	for(int i=2;i<=n;i++)
	{
		scanf("%d",&num);
		if(num>largest)
		{
			largest=num;
		}
	}
	printf("largest=%d",largest);
	return 0;
}
