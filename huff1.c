#include <stdio.h>
#include <stdlib.h>
#include<limits.h>
#include<string.h>
typedef struct node
{
	int freq;
	char c;
	int code[10];
	struct node *left;
	struct node *right;
}node;

node *heap[10000];
int size;
void init()
{
	size=0;
	heap[0]=(node*)malloc(sizeof(node));
	heap[0]->freq=-INT_MAX;

}
void ins(node *ele)
{
	int now;
	size++;
	now=size;
	heap[size]=ele;
	while(heap[now/2]->freq > ele->freq)
	{
		heap[now]=heap[now/2];
		now/=2;
	}
	heap[now]=ele;
}

node *delmin()
{
	node *minele,*lastele;
	minele=heap[1];
	lastele =heap[size--];
	int child,now;
	for(now=1;now*2<=size;now=child)
	{
		child=now*2;
		if(child!=size && heap[child +1]->freq < heap[child]->freq)
		{
			child++;
		}
		if(lastele->freq > heap[child]->freq)
		{
			heap[now]=heap[child];
		}
		else
			break;

	}
	heap[now]=lastele;
	return minele;

}
void print(node *root,int arr[],int top)
{
	int i;
	if(root->left==NULL && root->right==NULL)
	{
		printf("Character %c  ||  Code ",root->c);
		for(i=0;i<top;i++)
		{
			printf("%d",arr[i]);
			root->code[i]=arr[i];
		}

	}
	if(root->left)
	{
		arr[top]=0;
		print(root->left,arr,top+1);

	}
	if(root->right)
	{
		arr[top]=1;
		print(root->right,arr,top+1);

	}
}
void print_code(node *root,int arr[],int top,int key)
{
	int i;
	if(root->left==NULL && root->right==NULL && root->c==key)
	{
		for(i=0;i<top;i++)
		{
			printf("%d",arr[i]);
		}

	}
	if(root->left)
	{
		arr[top]=0;
		print_code(root->left,arr,top+1,key);

	}
	if(root->right)
	{
		arr[top]=1;
		print_code(root->right,arr,top+1,key);

	}
}
void decode(node *root)
{
	node *temp=NULL;
	char code[20],data[20];
	int i=0,j=0;
	printf("\nEnter the data to be decoded:\n");
	scanf("%s",code);
	while(code[i]!='\0')
	{
		temp=root;
		while((temp->left!=NULL && temp->right!=NULL) && code[i]!='\0')
		{
			if(code[i]=='1')
				temp=temp->right;
			else if(code[i]=='0')
				temp=temp->left;
			i++;
		}
		if(temp->left==NULL && temp->right==NULL)
		{
			data[j++]=temp->c;
		}
		else
		{
			printf("Error");
			exit(0);
		}
	}
	data[j]='\0';
	printf("the decoded data %s",data);


}
int main(void)
{
	init();
	int n,i,j;
	printf("\nEnter the no of alphabets");
	scanf("%d",&n);
	printf("\nEnter alphabet and frequency");
	for(i=0;i<n;i++)
    	{
		node *temp=(node*)malloc(sizeof(node));
		scanf(" %c",&temp->c);
		scanf("%d",&temp->freq);
		temp->left=temp->right=NULL;
		ins(temp);
	}
	printf("\n");
	for(i=0;i<n-1;i++)
    	{
		node *left=delmin();
		node *right=delmin();
		node *temp=(node*)malloc(sizeof(node));
		temp->c='0';
		temp->left=left;
		temp->right=right;
		temp->freq=temp->left->freq + temp->right->freq;
		ins(temp);
	}
	node *tree=delmin();
	int code[512];
	char encode[10],key;
	print(tree,code,0);
	printf("\nEnter the data to be encoded:");
	scanf("%s",encode);
	printf("\nThe encoded data:\n");
	for(j=0;j<strlen(encode);j++)
	{
		key=encode[j];
		print_code(tree,code,0,key);
	}
	decode(tree);
	return EXIT_SUCCESS;
}
