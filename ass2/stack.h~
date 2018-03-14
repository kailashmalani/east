#ifndef STACK_H_
#define STACK_H_
#define max 30

typedef struct node
{
	char data;
	int position;
	int firstpos[10];
	int lastpos[10];
	int nullable;
	struct node *left,*right;
	int number;
}node;

typedef struct stack
{
	struct node *data;
	struct stack *next;
}stack;

stack *top=NULL;

int isempty()
{
	if(top==NULL)
		return 1;
	return 0;
}	

void push(node *temp)
{
	stack *temp1;
	temp1 = (stack *)malloc(sizeof(stack));
	
	temp1->data = temp;
	temp1->next = NULL;

	if(top==NULL)
	{
		top=temp1;
	}
	else
	{
		temp1->next=top;
		top=temp1;
	}
}

node *pop()
{
	stack *temp1;
	node *temp;
	
	temp1=top;
	temp=temp1->data;
	
	top=top->next;
	free(temp1);
	return temp;
}
#endif /* STACK_H_ */
