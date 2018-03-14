#include<stdio.h>
#include<stdlib.h>

int n;
int padding(int n)
{
	int an=1,ori=n,lp=0,i;
	if(n==1)
		return 1;
	while(n>1)
	{
		lp++;
		n=n/2;
	}
	for(i=0;i<lp;i++)
	{
		an=an*2;
	}
	if(an==ori)
		return ori;
	else
		return an*2;
}
void strassen(int a[n][n],int b[n][n],int c[n][n],int size)
{
	int p1[size/2][size/2],p2[size/2][size/2],p3[size/2][size/2],p4[size/2][size/2],p5[size/2][size/2],p6[size/2][size/2],p7[size/2][size/2];
	int t1[size/2][size/2],t2[size/2][size/2];
	int i,j;
	
	if(size>=2)
	{
	
		for(i=0;i<size/2;i++)
		{
			for(j=0;j<size/2;j++)
			{
				t1[i][j] = a[i][j];
			}
		}
		for(i=0;i<size/2;i++)
		{
			for(j=0;j<size/2;j++)
			{
				t2[i][j] = b[i][j+size/2] - b[i+size/2][j+size/2];
			}
		}

		n=size/2;
		strassen(t1,t2,p1,size/2);

		for(i=0;i<size/2;i++)
		{
			for(j=0;j<size/2;j++)
			{
				t1[i][j] = a[i][j]+a[i][j+size/2];
			}
		}
		for(i=0;i<size/2;i++)
		{
			for(j=0;j<size/2;j++)
			{
				t2[i][j] = b[i+size/2][j+size/2];
			}
		}

		n=size/2;
		strassen(t1,t2,p2,size/2);

		for(i=0;i<size/2;i++)
		{
			for(j=0;j<size/2;j++)
			{
				t1[i][j] = a[i+size/2][j]+a[i+size/2][j+size/2];
			}
		}
		for(i=0;i<size/2;i++)
		{
			for(j=0;j<size/2;j++)
			{
				t2[i][j] = b[i][j];
			}
		}

		n=size/2;
		strassen(t1,t2,p3,size/2);

		for(i=0;i<size/2;i++)
		{
			for(j=0;j<size/2;j++)
			{
				t1[i][j] = a[i+size/2][j+size/2];
			}
		}
		for(i=0;i<size/2;i++)
		{
			for(j=0;j<size/2;j++)
			{
				t2[i][j] = b[i+size/2][j] - b[i][j];
			}
		}

		n=size/2;
		strassen(t1,t2,p4,size/2);

		for(i=0;i<size/2;i++)
		{
			for(j=0;j<size/2;j++)
			{
				t1[i][j] = a[i][j]+a[i+size/2][j+size/2];
			}
		}
		for(i=0;i<size/2;i++)
		{
			for(j=0;j<size/2;j++)
			{
				t2[i][j] = b[i][j] + b[i+size/2][j+size/2];
			}
		}

		n=size/2;
		strassen(t1,t2,p5,size/2);

		for(i=0;i<size/2;i++)
		{
			for(j=0;j<size/2;j++)
			{
				t1[i][j] = a[i][j+size/2]-a[i+size/2][j+size/2];
			}
		}
		for(i=0;i<size/2;i++)
		{
			for(j=0;j<size/2;j++)
			{
				t2[i][j] = b[i+size/2][j] + b[i+size/2][j+size/2];
			}
		}

		n=size/2;
		strassen(t1,t2,p6,size/2);

		for(i=0;i<size/2;i++)
		{
			for(j=0;j<size/2;j++)
			{
				t1[i][j] = a[i][j] - a[i+size/2][j];
			}
		}
		for(i=0;i<size/2;i++)
		{
			for(j=0;j<size/2;j++)
			{
				t2[i][j] = b[i][j] + b[i][j+size/2];
			}
		}

		n=size/2;
		strassen(t1,t2,p7,size/2);
	
	
		for(i=0;i<size/2;i++)
		{
			for(j=0;j<size/2;j++)
			{
				c[i][j] = p4[i][j]+p5[i][j]+p6[i][j]-p2[i][j];
				c[i][j+size/2] = p1[i][j] + p2[i][j];
				c[i+size/2][j] = p3[i][j] + p4[i][j];
				c[i+size/2][j+size/2] = p1[i][j] + p5[i][j] - p3[i][j] -p7[i][j];
			}
		}
	}
	else
	{
		c[0][0] = a[0][0]*b[0][0];
	} 
}

int main()
{
	int i,j,temp;
	printf("Enter the size of A and B: ");
	scanf("%d",&n);
	temp=n;
	n=padding(n);
	int a[n][n],b[n][n],c[n][n];
	printf("\nEnter the elements of matrix A:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("\nNO[%d][%d]: ",i,j);
			scanf("%d",&a[i][j]);
		}
		for(j=temp;j<n;j++)
		{
			a[i][j]=0;
		}
	}
	for(i=temp;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			a[i][j]=0;
		}
	}
	printf("\nEnter the elements of matrix B:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("\nNO[%d][%d]: ",i,j);
			scanf("%d",&b[i][j]);
		}
		for(j=temp;j<n;j++)
		{
			b[i][j]=0;
		}
	}
	for(i=temp;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			b[i][j]=0;
		}
	}
	strassen(a,b,c,n);
	printf("\nThe Matrix A:\n");
	for(i=0;i<temp;i++)
	{
		for(j=0;j<temp;j++)
		{
			printf("%d\t",a[i][j]);
		}
		printf("\n");
	}
	printf("\nThe Matrix B:\n");
	for(i=0;i<temp;i++)
	{
		for(j=0;j<temp;j++)
		{
			printf("%d\t",b[i][j]);
		}
		printf("\n");
	}
	printf("\nThe Matrix C:\n");
	for(i=0;i<temp;i++)
	{
		for(j=0;j<temp;j++)
		{
			printf("%d\t",c[i][j]);
		}
		printf("\n");
	}
	return 0;
}			
