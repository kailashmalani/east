#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct MOT{
	char mn[10];
	char class[3];
	int link,length,opcode,index,flag;
}mot;

typedef struct littab{
	char lit[10];
	int add;
	int lno;

}lit;

typedef struct regiter{
	char reg[5];
	int code;
}reg;

reg r[4];
mot m[26];
lit  l[10];

int n=1,lit_count=0;

void display_hash()
{
	int i;
	printf("INDEX\tMNE\tOPCODE\tLENGTH\tCLASS\tLINK\n");
	for(i=0;i<26;i++)
	{
		printf("%d\t%s\t%d\t%d\t%s\t%d\n",m[i].index,m[i].mn,m[i].opcode,m[i].length,m[i].class,m[i].link);
	}
}

void hash()
{
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

			while(m[j].flag != 0)
				j=(j+1)%26;
			while(m[k].link != 0)
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
int search_mot(char *s)
{
	int l=s[0]%65;

	if(strcmp(m[l].mn,s)==0)
	{
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

int lit_search(char *d)
{
	int i,flag=0;
	for(i=0;i<lit_count;i++)
	{
		if(strcmp(l[i].lit,d)==0)
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

int reg_search(char *t)
{
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

void lit_display()
{
	FILE *fp;
	fp=fopen("lit.txt","w");
	int i;
	fprintf(fp,"Lit.no\tlit_name\tsym_add\n");
	for(i=0;i<lit_count;i++)
	{
		fprintf(fp,"%d\t\t\t%s\t\t\t%d\n",l[i].lno,l[i].lit,l[i].add);
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
	FILE *pool;
	int p,lc,po_ol=0;
	char buffer[50],delim[] = " \r";
	//char *result = (char *) malloc(50 * sizeof(char));

	char *token;

	char prev_class[3];
	strcpy(prev_class,"AD");
	pool=fopen("pool.txt","w");
	fp=fopen("input.txt","r");
	fp1=fopen("output.txt","w");
	while(fgets(buffer,50,fp))
	{
		printf("%s", token);
		if(strcmp(prev_class,"IS")==0)
			lc++;
		token=strtok(buffer,delim);

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
		else if(strcmp(token,"LTORG")==0)
		{ 	
			fprintf(pool, "%d\t%d\n", po_ol, lc);
			int i;
			for(i = po_ol;i < lit_count;i++){
				l[i].add = lc;
				fprintf(fp1, "%d (AD 3)\n", lc);
				lc++;
			}
			po_ol = lit_count;
		}
		else if(strcmp(token,"ORIGIN")==0)
		{
			fprintf(fp1,"%d (AD 04)\n",lc);
			token=strtok(NULL,delim);
			lc=atoi(token);
		}
		else
		{
			if(token!=NULL)
			{
				p=search_mot(token);

				if(p!=-1)
				{

					if(strcmp(token,"END")==0)
					{
						fprintf(fp1,"%d (%s %d)",lc,m[p].class,m[p].opcode);
						fprintf(pool,"%d\t%d\n",po_ol,lc);
						int i;
						for(i=po_ol;i<lit_count;i++)
						{
							l[i].add=lc;
							lc=lc+1;
						}
						po_ol=lit_count;
					}
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
								int p;

								p=lit_search(token);
								if(p==-1)
								{
									strcpy(l[lit_count].lit,token);
									l[lit_count].lno=lit_count;
									l[lit_count].add=-1;
									fprintf(fp1,"(L %d)\n",l[lit_count].lno);
									lit_count++;
								}
								else
								{
									if(l[p].add==-1)
						/*IMP*/				fprintf(fp1,"(L %d)\n",l[p].lno);
									else
									{
										strcpy(l[lit_count].lit,token);
										l[lit_count].lno=lit_count;
										fprintf(fp1,"(L %d)\n",l[lit_count].lno);
										lit_count++;
									}
								}
							}
						}
					}	
				}	
			}	
		}	

	lit_display();
	fclose(fp);
	fclose(fp1);
	fclose(pool);
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
	FILE *fp,*fp1,*f;
	char *tk;

	int ltc=0;
	char buffer[50],*token,delim[]=" \n";
	fp=fopen("output.txt","r");
	fp1=fopen("pass2.txt","w");

	while(fgets(buffer,50,fp))
	{
		token=strtok(buffer,delim);
		fprintf(fp1,"+%s",token);

	token=strtok(NULL,delim);
		int d=token[1]%65;

		token=strtok(NULL," )");

		int tt=atoi(token);
		if((d==0&&tt==3)||(d==0&&tt==2))
		{
			fprintf(fp1," %s",l[ltc].lit);
			ltc++;
		}
		else
			fprintf(fp1," %s",token);

		token=strtok(NULL," (\n");

		if(token!=NULL)
			{
			if(strcmp(token,"R")==0)
			{
				token=strtok(NULL," \n)");
				fprintf(fp1," %s",token);
				token=strtok(NULL," (\n");
				token=strtok(NULL," \n)");
				//int a=atoi(token);
				//fprintf(fp1," %d\n",l[a].add);

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

