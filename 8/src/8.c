/*
 ============================================================================
 Name        : 8.c
 Author      : Abhishek Bakare
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "macro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	init();
	pass1();
	pass2();
	return EXIT_SUCCESS;
}

void init(){
	int i;
	for(i = 0;i < 10;i++){
		mdt[i].index = 0;
		mdt[i].insCount = 0;
		mnt[i].index = 0;
		mnt[i].kpno = 0;
		mnt[i].kptp = 0;
		mnt[i].mdtp = 0;
		mnt[i].pno = 0;
	}
}

void pass1(){
	char s1[MAX], s2[MAX], temp[MAX], ch[MAX];
	char *token;
	char delim[] = " \n";
	int insCount = 0, macroNameLine = 0, pCount = 0, kpCount = 0, pflag = 0, i , j, k;

	FILE *fpr = fopen("input.txt", "r");
	FILE *fpw = fopen("intermidiate.txt", "w");

	while(!feof(fpr)){
		fgets(s1, MAX, fpr);
		strcpy(s2, s1);
		token = strtok(s1, delim);
		if(strcmp(token, "MACRO") != 0){
			fputs(s2, fpw);
		}
		else{
			insCount = 0, macroNameLine = 0, pCount = 0, kpCount = 0, pflag = 0;
			fgets(s1, MAX, fpr);
			strcpy(s2, s1);
			token = strtok(s1, delim);
			mdt[counter].index = counter;
			while(strcmp(token, "MEND") != 0){
				if(macroNameLine == 0){
					for(i = 0;i < counter;i++){
						if(strcmp(token, mnt[i].name) == 0){
							printf("Error :: Macro with same name Found ... Illegal Operation ... Aborting!!!");
							exit(0);
						}
					}
					mdt[counter].index = counter;
					mnt[counter].mdtp = counter;
					mnt[counter].index = counter;
					mnt[counter].kptp = counter;
					strcpy(mnt[counter].name, token);
					token = strtok(NULL, delim);
					while(token != NULL){
						if(strstr(token, "=") != NULL){
							i = 0;
							while(token[i++] != '=');
							k = i;
							j = 0;
							if(token[i] == '\0'){
								strcpy(temp, "");
							}
							else{
								while(token[i] != '\0'){
									temp[j++] = token[i++];
								}
								temp[j] = '\0';
								temp[k] ='\0';
							}
							strcpy(kptab[counter].kpName[kpCount], token);
							strcpy(kptab[counter].value[kpCount++], temp);
							strcpy(ptab[counter].pName[pCount++], token);
							mnt[counter].kpno++;
						}
						else{
							mnt[counter].pno++;
							strcpy(ptab[counter].pName[pCount++], token);
						}
						token = strtok(NULL, delim);
					}
					macroNameLine = 1;
				}
				else{
					strcpy(s2, " ");
					while(token != NULL){
						pflag = 0;
						for(i = 0;i < pCount;i++){
							if(strstr(ptab[counter].pName[i], token) != NULL)
								pflag = 1;
							if(strcmp(token, ptab[counter].pName[i]) == 0 || pflag == 1){
								ch[0] = '#';
								ch[1] = i + 48;
								ch[2] = '\0';
								strcpy(token, ch);
								break;
							}
						}
						strcat(s2, token);
						strcat(s2, " ");
						token = strtok(NULL, delim);
					}
					strcpy(mdt[counter].str[insCount++], s2);
				}
				fgets(s1, MAX, fpr);
				token = strtok(s1,delim);
			}
			mdt[counter].insCount = insCount;
			counter++;
		}
	}
	drawLine
	printf("\nMDT Details :: \n");
	for(i = 0;i < counter;i++){
		printf("\n\nMDT #%d\n", mdt[i].index + 1);
		for(j = 0;j < mdt[i].insCount;j++){
			puts(mdt[i].str[j]);
		}
	}
	drawLine
	printf("\nMNT Details :: \n");
	printf("\nNo.\tName\tPno\tkpno\tKptp\tmdtp\n");
	for(i = 0;i < counter;i++){
		printf("\n%d\t%s\t%d\t%d\t%d\t%d", mnt[i].index,mnt[i].name,mnt[i].pno,mnt[i].kpno,mnt[i].mdtp,mnt[i].kptp);
	}
	drawLine
	printf("\nPTAB Details :: ");
	for(i = 0;i < counter;i++){
		printf("\n\nPTAB[%d] :: ", i + 1);
		printf("\nNo\t Name");
		for(j = 0;j < mnt[i].pno;j++){
			printf("\n%d\t%s", j + 1,ptab[i].pName[j]);
		}
	}
	drawLine
	printf("\nKPTAB Details:: ");
	for(i=0;i<counter;i++)	{
		printf("\n\nKTAB for %s:", mnt[i].name);
		printf("\nNo\t Name\tValue");
		for(j = 0;j < mnt[i].kpno;j++){
			printf("\n%d\t%s\t%s", j, kptab[i].kpName[j], kptab[i].value[j]);
		}
	}
	drawLine
	printf("\n");

	fclose(fpr);
	fclose(fpw);
}


void pass2(){
	int macroFlag = 0, tempCount = 0, i, j, k, d;
	char s1[MAX], s2[MAX], ch[10];
	char *token;
	char delim[] = " \n";

	FILE *fpr = fopen("intermidiate.txt", "r");
	FILE *fpw = fopen("output.txt", "w");

	int currCounter = 0;

	while(!feof(fpr)){
		macroFlag = 0;
		tempCount = 0;
		fgets(s1, MAX, fpr);
		strcpy(s2, s1);
		token = strtok(s1, delim);

		for(currCounter = 0;currCounter < counter;currCounter++){
			if(strcmp(token, mnt[currCounter].name) == 0){
				macroFlag = 1;
				break;
			}
		}

		if(macroFlag == 1){
			token = strtok(NULL, delim);
			while(token != NULL){
				if(strstr(token, "=") != NULL){
					i = 0;
					while(token[i++] != '=');
					k = i;
					if(token[i] == '\0'){
						strcpy(ch, "");
					}
					else{
						j = 0;
						while(token[i] != '\0')
							ch[j++] = token[i++];
						ch[j] = '\0';
						token[k] = '\0';
					}
					if(strstr(ptab[currCounter].pName[tempCount], token) == NULL){
						//if in MACRO there is parameter with default value and if it is not define at the time of calling
						strcpy(ala[currCounter].name[tempCount], ptab[currCounter].pName[tempCount]);
						strcpy(ala[currCounter].value[tempCount++],"");
						strcpy(ala[currCounter].name[tempCount], token);
						strcpy(ala[currCounter].value[tempCount++], ch);
					}
					else{
						//if parameter with defult value
						strcpy(ala[currCounter].name[tempCount], token);
						strcpy(ala[currCounter].value[tempCount++], ch);
					}
				}
				else{
					//if positional parameter
					strcpy(ala[currCounter].name[tempCount], token);
					strcpy(ala[currCounter].value[tempCount++], "");
				}
				token = strtok(NULL, delim);
			}
			if(tempCount < (mnt[currCounter].pno + mnt[currCounter].kpno)){
				printf("Error :: Less no. of argurments while calling MACRO %s.", mnt[currCounter].name);
			}
			if(tempCount > (mnt[currCounter].pno + mnt[currCounter].kpno)){
				printf("Error :: More no. of argurments while calling MACRO %s.", mnt[currCounter].name);
			}
			else{
				for(i = 0;i < mdt[currCounter].insCount;i++){
					strcpy(s2, mdt[currCounter].str[i]);
					fputs("+", fpw);
					token = strtok(s2, delim);
					while(token != NULL){
						if(token[0] == '#'){
							d = token[1] - 48;
							if(strstr(ala[currCounter].name[d], "=") == NULL){
								fputs(ala[currCounter].name[d], fpw);
							}
							else{
								fputs(ala[currCounter].value[d], fpw);
							}
						}
						else{
							fputs(token, fpw);
						}
						token = strtok(NULL, delim);
						fputs(" ", fpw);
					}
					fputs("\n", fpw);
				}
			}
		}
		else
			fputs(s2, fpw);

	}

	fclose(fpr);
	fclose(fpw);

}
