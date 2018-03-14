%token NUM
%left '+' '-'
%left '*' '/'
%left UMINUS
%%

start: exp			{printf("\nREsult:%d",$$);}
     ;
exp: exp '+' exp {$$ = $1+$3;}
   |exp '-' exp {$$ = $1-$3;}
   |exp '*' exp {$$ = $1*$3;}
   |exp '/' exp {$$ = $1/$3;}
   |'-' exp {$$=-$2;} %prec UMINUS
   | '(' exp ')'   {$$=$2;}
   | NUM
   ;

%%

#include "lex.yy.c"
#include<stdio.h>
#include<ctype.h>

int main()
{
	printf("Enter the Expression:\n");
	yyparse();
}
int yywrap()
{
	return 1;
}
int yyerror()
{
}

   
