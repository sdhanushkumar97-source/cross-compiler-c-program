#include<stdio.h>
int main()
{
	int n,r=0,num=0;
	printf("enter n");
	scanf("%d",&n);
	while(n!=0)
	{
		r=n%10;
		num=num*10+r;
		n=n/10;
	}
	printf("the reverse number=%d",num);
}
