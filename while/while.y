%token ID WHILE NUM
%right '='
%left '+' '-'
%left '*' '/'
%left UMINUS
%%

S: WHILE  {lab1();} '('E')' {lab2();} E ';' {lab3();}
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

int ltop=0,lnum=1,top=0;
char st[100][10];
char temp[3]="t";
char i_[2]="0";
int label[10];
int start=1;

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
	printf("\nL%d:",lnum++);
}
lab2()
{
	strcpy(temp,"t");
	strcat(temp,i_);
	printf("\n%s = not %s",temp,st[top]);
	printf("\nif %s goto L%d",temp,lnum);
	i_[0]++;
} 

lab3()
{
	printf("\ngoto L%d",start);
	printf("\nL%d",lnum);
}

int yywrap()
{
	return 1;
}

int yyerror()
{
}    
