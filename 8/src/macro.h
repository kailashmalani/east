/*
 * macro.h
 *
 *  Created on: 18-Apr-2017
 *      Author: abhishek
 */

#ifndef MACRO_H_
#define MACRO_H_

#define MAX 200
#define drawLine printf("\n-----------------------------------------------------------------\n");

struct MDT{
	int index;
	char str[10][MAX];
	int insCount;
};

struct MNT{
	int index;
	char name[MAX];
	int pno;
	int kpno;
	int mdtp;
	int kptp;
};

struct KPTAB{
	char kpName[10][MAX];
	char value[10][MAX];
};

struct PTAB{
	char pName[10][MAX];
};

struct ALA{
	char name[10][MAX];
	char value[10][MAX];
};

struct MDT mdt[10];
struct MNT mnt[10];
struct KPTAB kptab[10];
struct PTAB ptab[10];
struct ALA ala[10];
int counter = 0;

void init();
void pass1();
void pass2();

#endif /* MACRO_H_ */
