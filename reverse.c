#include<stdio.h>
int main()
	{
		int n,pal,r,m;
		printf("enter n");
		scanf("%d",&n);
		m = n;
		while(n!=0)
		{
			r=n%10;
			pal=pal*10+r;
			n=n/10;
			
		}
		if(m==pal)
		{
			printf("the given number is palindrome");
		}
		else
		{
			printf("the given number is not a palindrome");
		}
	}
