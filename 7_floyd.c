#include<stdio.h>
#include<stdlib.h>

int min(int a,int b)
{
	if(a>b)
		return b;
	else
		return a;
}

int main()
{
	int d[10][10],g[10][10],w[10][10];
	int i,j,k,n;
	
	printf("Enter the Number of vertice:");
	scanf("%d",&n);
	printf("Enter the distance matrix:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&g[i][j]);
		}
	}
	printf("\nEntered matrix:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ",g[i][j]);
		}
		printf("\n");
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			d[i][j]=g[i][j];
			if(g[i][j]>0)
			{
				w[i][j]=1;
			}
			else
			{
				w[i][j]=0;
			}
		}
	}

	printf("\nThe adjacency matrix:\n");

	for (i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d\t",w[i][j]);
		}
		printf("\n");


	}
	printf("By using WARSHALL's Algorithm:\n");
	for (k=0;k<n;k++)
	{
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				w[i][j]=(w[i][j] || (w[i][k] && w[k][j]));
			}
		}
		printf("A (%d)\n", k);
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				printf("%d\t",w[i][j]);
			}
			printf("\n");

		}

	}
	printf("<--------------------------------------------->\n");
	printf("<--------------------------------------------->\n");
	printf("<--------------------------------------------->\n");
	printf("the entered weighted matrix is:\n");
	for (i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d\t",g[i][j]);
		}
		printf("\n");

	}
	
	printf("By using FLLOYD's Algorithm:\n");
	for (k=0;k<n;k++)
	{
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				d[i][j]=min(d[i][j],(d[i][k] + d[k][j]));
			}
		}
		printf("D (%d)\n", k);
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				printf("%d\t",d[i][j]);
			}
			printf("\n");

		}

	}
	printf("the shortest paths between the vertices are:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if (i!=j)
				printf("(%d , %d) -> %d\n",i+1,j+1,d[i][j]);

		}

	}
	return 0;
}
