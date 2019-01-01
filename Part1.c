#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>
void q1()
{
	char c=0xFF;
	printf("%c\n",c);
	if(c==-1) printf("signed\n");
	else printf("unsigned\n");
}

void q2()
{
	int i;
	signed int si;
	unsigned int usi;
	printf("size of a int:			%ld bytes\n",sizeof(i));
	printf("size of a signed int:		%ld bytes\n",sizeof(si));
	printf("size of a unsigned int:		%ld bytes\n",sizeof(usi));
	//the return type of sizeof() function is long unsigned int!
	printf("the max value of a (signed)int:	%d\n",INT_MAX);
	printf("the min value of a (signed)int:	%d\n",INT_MIN);
	printf("the max value of a unsigned int:%u\n",UINT_MAX);
	printf("the min value of a unsigned int:%u\n",UINT_MAX+1); 
}

void q3()
{
	uint8_t super,bof,naze,superman,sousleau;
	super=0x11;
	bof=0b1010;
	naze=8;
	superman=0b10110;
	sousleau=0x2;
	printf("super:		%d\n",super);
	printf("bof:		%d\n",bof);
	printf("naze:		%d\n",naze);
	printf("superman:	%d\n",superman);
	printf("sousleau:	%d\n",sousleau);

}

void q4()
{	
	long l;
	long long ll;
	printf("size of a long:			%ld bytes\n",sizeof(l));
	printf("size of a long long:		%ld bytes\n",sizeof(ll));
}
void q5()
{
	signed char sc=SCHAR_MAX+1;
	unsigned char uc=UCHAR_MAX+1;
	printf("the max+1 of a signed char:	%d\n",sc);
	printf("the max+1 of a unsigned char:	%d\n",uc);
}
void q6()
{
	int i=INT_MAX+1;
	printf("the max+1 of a int:	%d\n",i);
}
void q7()
{
	uint32_t a,b= 4000000000,c= 500000000,d=0;
	a=(b+c)-d;
	printf("a:%d\n",a);
}
void q8()
{
	if (sizeof(int) < -1)
	printf("Bizarre, bizarre ... ??\n");
	else
	printf ("Tout semble normal\n");
}
void q9()
{
	int i=3.14;
	float f=3.14;
	double d=3.14;
	float lf=3.14159265358979328462264338327;
	double ld=3.14159265358979328462264338327;
	printf("3.14	int:	%d\n",i);
	printf("3.14	float:	%f\n",f);
	printf("3.14	double:	%f\n",d);
	printf("long 	float:	%f\n",lf);
	printf("long 	double:	%f\n",ld);
}
void q10()
{
	int i=3.14;
	float f=3.14;
	double d=3.14;
	float lf=3.14159265358979328462264338327;
	double ld=3.14159265358979328462264338327;
	printf("3.14	int:	%d\n",i);
	printf("3.14	float:	%.29f\n",f);
	printf("3.14	double:	%.29f\n",d);
	printf("long 	float:	%.29f\n",lf);
	printf("long 	double:	%.29f\n",ld);
}
void q11()
{
	printf("size of a bool:	%ld byte\n",sizeof(bool));
	printf("value of true:	%d\n",true);
	printf("value of false:	%d\n",false);
}
void q12()
{
	char mychar = 'A';
	int val = mychar + 10;
	printf("val = %d char = %c\n", val,val);
}
void q13()
{
	uint16_t a = 413;
	uint16_t b = 64948;
	fprintf(stdout, "%u\n", (a - b));
}
void q14()
{
	uint16_t a = 413;
	uint16_t b = 64948;
	uint16_t c=a-b;
	fprintf(stdout, "%u\n", c);
}
void q15()
{
	long a = 8000000002;
	float b = 2;
	long c = a / b;
	printf("res : %li\n", c);
	printf("res : %f\n",a/b);
}
void q16()
{
	long l=142857142857;
	float f=0;
	printf("l+f : %f\n",l+f);
}
void q17()
{
	int i=1.618;
	printf("i : %d\n",i);
}
void q19()
{
	char c=42;
	int i=(char)c;
	printf("i: %d\n",i);
	i=42;
	c=(char)i;
	printf("c: %c\n",c);
}
void q20()
{
	int i=-42;
	unsigned int u=(unsigned int)i;
	printf("unsigend int: %u\n",u);
	int ii=0x2a3b;
	char c=(char)ii;
	printf("char : %c\n",c);
}
void q21()
{
	char A=3;
	int B=4;
	float C=A/B;
	printf("C: %f\n",C);
	C=(float)A/(float)B;
	printf("C: %f\n",C);
}
void printRoomsState(uint32_t allRooms)
{
	int index=0;
	while(index<32){
		printf("%d: %d	",index++,allRooms%2);
		allRooms%2?
			printf("Occupé\n"):printf("Non occupé\n");
		allRooms=allRooms>>1;
	}
}
uint32_t roomGoesOccupied(uint32_t allRooms,unsigned int roomNb)
{
	uint32_t operand=1<<roomNb;
	return operand|allRooms;
}
bool isOccupied(uint32_t allRooms,unsigned int roomNb)
{
	return (allRooms>>roomNb)%2;
}
uint32_t roomGoesEmpty(uint32_t allRooms,unsigned int roomNb)
{
	uint32_t operand=1<<roomNb;
	return (~operand)&allRooms;
}
void q29()
{
	enum scrutin_e1 {MAJORITAIRE_UNI1,MAJORITAIRE_PLURI1,PROPORTIONNEL1,MIXTE1};
	printf("scrutin_e1: %d %d %d %d\n",MAJORITAIRE_UNI1,MAJORITAIRE_PLURI1,PROPORTIONNEL1,MIXTE1);	
	enum scrutin_e2 {MAJORITAIRE_UNI2=2,MAJORITAIRE_PLURI2=8,PROPORTIONNEL2=42,MIXTE2=12};
	printf("scrutin_e2: %d %d %d %d\n",MAJORITAIRE_UNI2,MAJORITAIRE_PLURI2,PROPORTIONNEL2,MIXTE2);	
	enum scrutin_e3 {MAJORITAIRE_UNI3=4,MAJORITAIRE_PLURI3,PROPORTIONNEL3,MIXTE3};
	printf("scrutin_e3: %d %d %d %d\n",MAJORITAIRE_UNI3,MAJORITAIRE_PLURI3,PROPORTIONNEL3,MIXTE3);	
}
void q30()
{	
	enum semaine {LUNDI=1,MARDI,MERDREDI,JEUDI,VENDREDI,SAMEDI,DIMANCHE};
}
void appreciate(int note)
{
	switch (note) {
		case 12:
			printf("12 ! Passable ");
			break;
		case 18:
			printf("18 ! Super ! ");
		case 6:
			printf("6 ! Naze ");
			break;
		case 8:
			printf("8 ! Mieux que naze ");
			break;
		case 10:
			printf("10 ! Presque passable ");
			break;
		default:
			printf("%d ! Pas prevu par le de-qui-corrige", note);
			//break;
	}
	printf("\n");
}
void q32(int n)
{
	if(!n){
		printf("Ga\n");
	}
	while(n>0){
		switch(n%4){
			case 0:
				printf("Ga ");
				break;
			case 1:
				printf("Bu ");
				break;
			case 2:
				printf("Zo ");
				break;
			case 3:
				printf("Meu ");
		}
		n/=4;
	}
	printf("\n");
}
int main()
{
	q32(3);
	q32(6);
	q32(11);
	q32(42);
	return 0;
}
