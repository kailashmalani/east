#include<stdio.h>
#include<stdlib.h>

int g[10][10],t=0,flag,n,x[10];

void nextvalue(int k)
{
	int j;
	do
	{
		x[k]=(x[k]+1)%(n+1);
		if(x[k]==0)
			return;
		if(g[x[k-1]][x[k]]!=0)
		{
			for(j=1;j<=k-1;j++)
			{
				if(x[j]==x[k])
					break;
			}
			if(j==k)
			{
				if((k<n) || ((k==n) && (g[x[n]][x[1]]!=0)))
					return;
			}
		}
	}while(1);
}
void hamil()
{
	int i,k=2;
	while(1)
	{
		nextvalue(k);
		if(x[k]!=0)
		{
			if(k==n)
			{
				flag=1;
				if(t==0)
				{
					printf("The hamiltonian path is:\n");
					t=1;
				}
				for(i=1;i<=n;i++)
				{
					printf("%d->",x[i]);
				}
				printf("\n");
			}
			k=k+1;
		}
		else
		{
			k=k-1;
		}
		if(k==1)
		{
			break;
		}
	}
}
int main()
{
	int i,j,k,l;
	printf("Enter the number of vertices: ");
	scanf("%d",&n);
	printf("\nEnter the %d x %d matrix: \n",n,n);
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			scanf("%d",&g[i][j]);
		}		
	}
	printf("Entered Matrix is:\n");
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			printf("%d ",g[i][j]);
		}
		printf("\n");		
	}
	for(l=1;l<=n;l++)
	{
		x[1]=l;
		for(k=2;k<=n;k++)
		{
			x[k]=0;
		}
		hamil();
		if(flag==0)
		{
			printf("\nNo hamiltonian path present from vertex %d",l);
		}
	}
	printf("\n");
	return 0;		
}
