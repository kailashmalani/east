%token ID NUM IF THEN ELSE
%right '='
%left '+' '-'
%left '*' '/'
%left UMINUS
%%

S: IF '('E')' {lab1();} THEN E ';' {lab2();} ELSE E ';' {lab3();}
 ;
E: V '=' {push();} E{code_assign();}
 | E '+' {push();} E{code_gen();}
 | E '-' {push();} E{code_gen();} 
 | E '*' {push();} E{code_gen();} 
 | E '/' {push();} E{code_gen();}
 | '('E')'
 | '-' {push();} E{code_umin();} %prec UMINUS
 | V 
 |NUM {push();}
 ;
V: ID {push();}
 ;
%%


#include "lex.yy.c"
#include <stdio.h>
#include<ctype.h>

int ltop=0,lnum=0,top=0;
char st[100][10];
char temp[3]="t";
char i_[2]="0";
int label[10];

int main()
{
	printf("Enter the Expression:\n");
	yyparse();
}

push()
{
	strcpy(st[++top],yytext);
}

code_gen()
{
	strcpy(temp,"t");
	strcat(temp,i_);
	printf("\n%s = %s %s %s",temp,st[top-2],st[top-1],st[top]);
	top-=2;
	strcpy(st[top],temp);
	i_[0]++;
}

code_umin()
{
	strcpy(temp,"t");
	strcat(temp,i_);
	printf("\n%s = -%s",temp,st[top]);
	top--;
	strcpy(st[top],temp);
	i_[0]++;
}

code_assign()
{
	printf("\n%s = %s",st[top-2],st[top]);
	top-=2;
}

lab1()
{
	strcpy(temp,"t");
	strcat(temp,i_);
	lnum++;
	printf("\n%s = not %s",temp,st[top]);
	printf("\nif %s goto L%d",temp,lnum);
	label[++ltop]=lnum;
	i_[0]++;
} 

lab2()
{
	int x;
	lnum++;
	x = label[ltop--];
	printf("\ngoto L%d",lnum);
	printf("\nL%d",x);
	label[++ltop]=lnum;
}

lab3()
{
	int y;
	y = label[ltop--];
	printf("\nL%d",y);
}

int yywrap()
{
	return 1;
}

int yyerror()
{
}    
