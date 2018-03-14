#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct MOT{
	char mn[10];
	char class[3];
	int link,length,opcode,index,flag;
}mot;

typedef struct symtab{
	char sym[10];
	int add;
	int sno;
	int size;
}sym;

typedef struct regiter{
	char reg[5];
	int code;
}reg;

reg r[4];
mot m[26];
sym  s[10];
int n=1,sym_count=0;

void display_hash(){
	int i;
	printf("INDEX\tMNE\tOPCODE\tLENGTH\tCLASS\tLINK\tFLAG\n");
	for(i=0;i<26;i++)
	{
		printf("%d\t%s\t%d\t%d\t%s\t%d\t%d\n",m[i].index,m[i].mn,m[i].opcode,m[i].length,m[i].class,m[i].link,m[i].flag );
	}
}

void hash(){
	FILE *fp;
	int i;
	char buffer[50],s1[10],s2[10],s3[10],s4[2];
	fp=fopen("mot.txt","r");
	if(fp==NULL)
		printf("file not found");
	for(i=0;i<26;i++)
	{
		m[i].link=0;
		m[i].flag=0;
		m[i].index=i;
		m[i].opcode=-2;
		strcpy(m[i].class," ");
		strcpy(m[i].mn," ");
	}
	while(fgets(buffer,50,fp))
	{
		int l;
		sscanf(buffer,"%s%s%s%s",s1,s2,s3,s4);
		l=s1[0]%65;
		if(m[l].flag==0)
		{
			strcpy(m[l].mn,s1);
			strcpy(m[l].class,s4);
			m[l].length=atoi(s3);
			m[l].opcode=atoi(s2);
			m[l].flag=1;
			n++;
		}
		else
		{
			int j=l;
			int k=l;
			while(m[j].flag!=0)
				j=(j+1)%26;
			while(m[k].link!=0)
				k=m[k].link;
			m[k].link=j;
			strcpy(m[j].mn,s1);
			strcpy(m[j].class,s4);
			m[j].length=atoi(s3);
			m[j].opcode=atoi(s2);
			m[j].flag=1;
			n++;
		}
	}
	fclose(fp);
	display_hash();
}

int search_mot(char *s){
	int l=s[0]%65;
	if(strcmp(m[l].mn,s)==0){
		return l;
	}
	else
	{
		int a=l;
		do
		{
			a=m[a].link;

			if(strcmp(m[a].mn,s)==0)
				return a;


		}while(m[a].link!=0);
	}
 	return -1;
}

int sym_search(char *d){
	int i,flag=0;
	for(i=0;i<sym_count;i++)
	{
		if(strcmp(s[i].sym,d)==0)
		{
			flag=1;
			break;
		}
	}
    	if(flag==1)
		return i;
  	else
    		return -1;


}

int reg_search(char *t){
	int i;
	for(i=0;i<n;i++)
	{//printf("%s\t%s\n",r[i].reg,t);
		if(strcmp(r[i].reg,t)==0)
		{
			break;
		}
	}
	return i;
}

void sym_display()
{
	FILE *fp;
	fp=fopen("sym.txt","w");
	int i;
	fprintf(fp,"S.no\tsym_name\tsym_size\tsym_add\n");
	for(i=0;i<sym_count;i++)
	{
		fprintf(fp,"%d\t\t\t%s\t\t\t%d\t\t\t%d\n",s[i].sno,s[i].sym,s[i].size,s[i].add);
	}
	fclose(fp);
}

void display_reg()
{
	int i;
	for(i=0;i<4;i++)
	{
		printf("%s\t%d\n",r[i].reg,r[i].code);
	}
}

void pass1()
{
	FILE *fp;
	FILE *fp1;
	
	int p,lc;
	char buffer[50],delim[] = " \n";
	//char *result = (char *) malloc(50 * sizeof(char));

	char *token;

	char prev_class[3];
	strcpy(prev_class,"AD");

	fp=fopen("input.txt","r");
	fp1=fopen("output.txt","w");

	while(fgets(buffer,50,fp))
	{
		if(strcmp(prev_class,"IS") == 0)
			lc++;
		token=strtok(buffer,delim);
		//printf("%s\n",token);
		if(strcmp(token,"START")==0)
		{
			p=search_mot(token);
			strcpy(prev_class,m[p].class);
			token = strtok(NULL, delim);
			if(token!=NULL)
			{

				lc=atoi(token);
				fprintf(fp1,"%d (%s %d) (C %d)\n",lc,m[p].class,m[p].opcode,lc);


			}
		}
		else if(strcmp(token,"STOP")==0)
		{
			p=search_mot(token);
			fprintf(fp1,"%d (%s %d)\n",lc,m[p].class,m[p].opcode);
			strcpy(prev_class,m[p].class);

		}

		else
		{
			p=search_mot(token);

			if(p != -1){
				if(strcmp(token,"END")==0)
					fprintf(fp1,"%d (%s %d)",lc,m[p].class,m[p].opcode);
				else
					fprintf(fp1,"%d (%s %d) ",lc,m[p].class,m[p].opcode);

				strcpy(prev_class,m[p].class);
				token=strtok(NULL,delim);

				if(token!=NULL)
				{ 
					 int f;
					f=reg_search(token);
					fprintf(fp1,"(R %d) ",r[f].code);
					token=strtok(NULL,delim);
					if(token!=NULL)
					{
						int q;
						q=sym_search(token);
						if(q==-1)
						{
							s[sym_count].sno=sym_count;
							strcpy(s[sym_count].sym,token);
							s[sym_count].size=1;
							s[sym_count].add=-1;
							fprintf(fp1,"(S %d)\n",s[sym_count].sno);
							sym_count++;
						}
						else
						{
							fprintf(fp1,"(S %d)\n",s[q].sno);
						}
					}
				}
			}

			else
			{
				int q;
				q=sym_search(token);
				if(q==-1)
				{
					s[sym_count].sno=sym_count;
					strcpy(s[sym_count].sym,token);
					s[sym_count].size=1;
					s[sym_count].add=lc;
					sym_count++;
				}
				else
				{
					s[q].add=lc;
				}

				token=strtok(NULL,delim);

				if(token!=NULL)
				{

					 int p;
					 p=search_mot(token);
					 if(p!=-1)
					 {
					 	if(strcmp(token,"EQU")==0)
					 	{
							p=search_mot(token);
							fprintf(fp1,"%d (%s %d)\n",lc,m[p].class,m[p].opcode);
							strcpy(prev_class,m[p].class);
							int p1;
							token=strtok(NULL,delim);
							p1=sym_search(token);

/*IMP**IMP**IMP**IMP**IMP**IMP**IMP**IMP*/			if(q!=-1)
								s[q].add=s[p1].add;
								else
								s[sym_count-1].add=s[p1].add;
						}
						else
						{
						 	fprintf(fp1,"%d (%s %d) ",lc,m[p].class,m[p].opcode);

						 	strcpy(prev_class,m[p].class);
						 	if(strcmp(m[p].class,"DL")==0)
						 	{
								if(strcmp(m[p].mn,"DC")==0)
								{
									token=strtok(NULL,delim);

									fprintf(fp1,"(C %s)\n",token);

									if(q!=-1)
										s[q].add=lc;
									else
/*IMP**IMP**IMP**IMP**IMP**IMP**IMP**IMP*/					s[sym_count-1].add=lc;
									lc++;

								}

								else
								{
									token=strtok(NULL,delim);
									fprintf(fp1,"(C %s)\n",token);
									int w=atoi(token);
									if(q!=-1)
										s[q].add=lc;
									else
										s[sym_count-1].add=lc;

									lc=lc+w;

								}
						 	}



						 	token=strtok(NULL,delim);
							if(token!=NULL)
							{
								int f;
								f=reg_search(token);
								fprintf(fp1,"(R %d) ",r[f].code);
								token=strtok(NULL,delim);
								if(token!=NULL)
								{
									int q;
									q=sym_search(token);
									if(q==-1)
									{
										s[sym_count].sno=sym_count;
										strcpy(s[sym_count].sym,token);
										s[sym_count].size=1;
										s[sym_count].add=-1;
										fprintf(fp1,"(S %d)",s[sym_count].sno);

										sym_count++;
									}
									else
									{
										fprintf(fp1,"(S %d)\n",s[q].sno);
									}

								}
							}
	 					}
					}
				}

			}

			}

	}

	sym_display();
	fclose(fp);
	fclose(fp1);
}

void regi()
{ 
	char buffer[10],delim[]=" \n";
	int i=0;
	char *token;
	for(i=0;i<4;i++)
	{
		strcpy(r[i].reg,"");
	}
	i=0;
	FILE *fp2=fopen("reg.txt","r");
	while(fgets(buffer,10,fp2))
	{
		token=strtok(buffer,delim);
		strcpy(r[i].reg,token);

		token=strtok(NULL,delim);
		r[i].code=atoi(token);


		i++;
	}
	fclose(fp2);
	display_reg();
}

void pass2()
{
	FILE *fp,*fp1;
	char buffer[50],*token,delim[]=" \n";
	fp=fopen("output.txt","r");
	fp1=fopen("pass2.txt","w");
	while(fgets(buffer,50,fp))
	{
		token=strtok(buffer,delim);
		fprintf(fp1,"+%s\t",token);

		token=strtok(NULL,delim);
		fprintf(fp1," %c",token[4]);

		token=strtok(NULL," \n");
		token=strtok(NULL," (\n");
//	fprintf(fp1," %s",token);

	if(token!=NULL)
	{
	if(strcmp(token,"R")==0)
	{
		token=strtok(NULL," \n)");
		fprintf(fp1," %s",token);
		token=strtok(NULL," (\n");
		token=strtok(NULL," \n)");
		int a=atoi(token);
		fprintf(fp1," %d\n",s[a].add);

	}
	else
			fprintf(fp1,"\n");
	}
	else
		fprintf(fp1,"\n");
	}
}
int main()
{
	hash();

	regi();

	pass1();
	pass2();
	return 0;
}

