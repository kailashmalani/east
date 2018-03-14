#include<stdio.h>
#include<stdlib.h>
int x[10],sol=0;

int place(int k,int i)
{
	int j;
	for(j=1;j<=k-1;j++)
	{
		if((x[j]==i) || (abs(x[j]-i)==(abs(k-j))))
			return 0;
	}
	return 1;
}


void display(int x[10],int n)
{
	int i,j;
	sol++;
	printf("Solution No: %d",sol);
	printf("\n");
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(x[j]==i)
			{
				printf("Q\t");
			}
			else
			{
				printf("-\t");
			}
		}
		printf("\n");
	}
}
void nqueen(int k,int n)
{
	int i;
	for(i=1;i<=n;i++)
	{
		if(place(k,i))
		{
			x[k]=i;
			if(k==n)
			{
				display(x,n);
			}
			else
			{
				nqueen(k+1,n);
			}
		}
	}
}



int main()
{
	int n;
	printf("Enter the size of Chess board:" );
	scanf("%d",&n);
	if(n==0 || n==2 || n==3)
	{
		printf("No Solutions Available\n");
	}
	else
	{
		nqueen(1,n);
		printf("\nThe Number of solutions are: %d",sol);
	}
	return 0;
}
