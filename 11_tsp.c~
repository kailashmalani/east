#include<stdio.h>

int t=0,row,col,s[10],n,g[10][10];

int allvisited(int s[10])
{
	int i;
	for(i=1;i<=n;i++)
	{
		if(s[i]==0)
		{
			return 0;
		}
	}
	return 1;
}

int rowmin(int cost[10][10],int i)
{
	int j;
	int min = 32767;
	for(j=1;j<=n;j++)
	{
		if(cost[i][j]<min)
			min=cost[i][j];
	}
	return min;
}

int colmin(int cost[10][10],int i)
{
	int j;
	int min = 32767;
	for(j=1;j<=n;j++)
	{
		if(cost[j][i]<min)
			min=cost[j][i];
	}
	return min;
}

void rowred(int cost[10][10])
{
	int i,j,rmin;
	row=0;
	for(i=1;i<=n;i++)
	{
		rmin=rowmin(cost,i);
		if(rmin!=32767)
			row = row + rmin;
		for(j=1;j<=n;j++)
		{
			if(cost[i][j]!=32767)
				cost[i][j] = cost[i][j] - rmin;
		}
	}
}

void colred(int cost[10][10])
{
	int i,j,cmin;
	col=0;
	for(i=1;i<=n;i++)
	{
		cmin=colmin(cost,i);
		if(cmin!=32767)
			col = col + cmin;
		for(j=1;j<=n;j++)
		{
			if(cost[j][i]!=32767)
				cost[j][i] = cost[j][i] - cmin;
		}
	}
}

int checkbounds(int par,int child,int cost[10][10])
{
	int tcost[10],i,j,reduced[10][10];
	tcost[1]=t;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			reduced[i][j]=cost[i][j];
		}
	}
	for(j=1;j<=n;j++)
	{
		reduced[par][j] = 32767;
	}
	for(i=1;i<=n;i++)
	{
		reduced[i][child] = 32767;
	}
	reduced[child][1] = 32767;
	rowred(reduced);
	colred(reduced);
	tcost[child] = tcost[par] + row + col + cost[par][child];
	return tcost[child];
}

int main()
{
	int i,j,k=1,m=2,cost[10][10];
	int ecost[10],l,min,path[10];
	printf("Enter the Number of cities to travel:" );
	scanf("%d",&n);
	printf("Enter the distance matrix:");
	for(i=1;i<n+1;i++)
	{
		for(j=1;j<n+1;j++)
		{
			scanf("%d",&g[i][j]);
		}
	}
	printf("\n");
	printf("The distance matrix is:");
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			printf("%d ",g[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	s[1]=1;
	path[1]=1;
	for(i=2;i<n+1;i++)
		s[i]=0;

	for(i=1;i<n+1;i++)
	{
		for(j=1;j<n+1;j++)
		{
			cost[i][j]=g[i][j];
		}
	}
	rowred(cost);
	colred(cost);
	t = row + col;	
	while(!allvisited(s))
	{
		l=k;
		for(i=1;i<=n;i++)
		{
			if(s[i]==0)
			{
				ecost[i]=checkbounds(k,i,cost);
			}
		}
		min = 32767;
		for(i=1;i<=n;i++)
		{
			if(s[i]==0)
			{
				if(ecost[i]<min)
				{
					min=ecost[i];
					k=i;
				}
			}
		}
		s[k] = 1;
		path[m++] = k;
		for(j=1;j<=n;j++)
			cost[l][j] = 32767;
		for(j=1;j<=n;j++)
			cost[j][k] = 32767;
		cost[k][1] = 32767;
		rowred(cost);
		colred(cost);
	}
	printf("\nThe Shortest Path to travel all the cities: ");
	for(i=1;i<=n;i++)
	{
		printf("%d->",path[i]);
	}
	printf("1");
	printf("\nThe minimum cost required to travel all the cities is: %d",ecost[n]);
	printf("\n");
	return 0;
}
