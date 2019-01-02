#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<inttypes.h>
int intNotInitialized;
int intInitialized=0;

//const* unsigned int MAX_SIZE=5;
#define MAX_SIZE 5

typedef int matrix [MAX_SIZE][MAX_SIZE];

enum mois {Jan,Feb,Mar,Avr,Mai,Jun,Jui,Aou,Sep,Oct,Nov,Dec};

typedef struct{
	int year;
	enum mois month;
	int day;
}birthday;

typedef struct{
	int id;
	birthday b;
	char boissonPreferee[20];
	char nom[20];
}student;


int main();

void q1(){
	printf("%p\n",&main);
}

void q2(){
	intNotInitialized=42;
	intInitialized=5;
	int* addresseNot=&intNotInitialized;
	int* addresseInit=&intInitialized;
	printf("la valeur de intNotInitialized:	%d\n",intNotInitialized);	
	printf("l'addresse de intNotInitialized:%p\n",addresseNot);
	printf("la valeur de intInitialized:	%d\n",intInitialized);
	printf("l'addresse de intInitialized:	%p\n",addresseInit);
	*addresseNot=43;
	*addresseInit=6;
	printf("après la modification:\n");
	printf("la valeur de intNotInitialized:	%d\n",intNotInitialized);	
	printf("la valeur de intInitialized:	%d\n",intInitialized);
}

void q5(){
	int localeNot;
	int localeInit=0;
	printf("la valeur de localeNot:		%d\n",localeNot);	
	printf("l'addresse de localeNot:	%p\n",&localeNot);
	printf("la valeur de localeInit:	%d\n",localeInit);
	printf("l'addresse de localeInit:	%p\n",&localeInit);
}

void q6(int size){
	int all_elements[size];
	printf("%ld\n",sizeof(all_elements));
}

void q8(int (*a)[5],int size){
	//int (*a)[5]:	a pointer which points an array containing 5 int
	//int *a [5]:	a array which contains 5 pointer of int
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			printf("%d	",a[i][j]);
		}
		printf("\n");
	}
}

void q9(){
	char * my_string="<-_->";
	printf("%s\n",my_string);
	char * pt=my_string; 
	while(*pt!='\0'){
		printf("%c.",*pt);
		pt++;
	}
	printf("\n");
}

void q11(){
	char* my_string="<-_->";
	for(int i=0;i<strlen(my_string);i++){
		printf("%c.",my_string[i]);	
	}
	printf("\n");
}

void q12(){
	char myString[50];
	scanf("%s",myString);
	int i=strtoimax(myString,NULL,10);
	printf("%d\n",i);
	printf("%d\n",i%4);
}

int TP_strcmp(const char* s1,const char* s2)
{
	int ret=0;
	int i=0;
	while(s1[i]!='\0'&&s2[i]!='\0'){
		if(s1[i]!=s2[i]){
			ret=s1[i]-s2[i];
			break;
		}
		i++;
	}
	if(!ret){
		if(s1[i]!='\0') ret=1;
		if(s2[i]!='\0') ret=-1;
	}
	return ret;
}

void q14(){
	int tab[5][7];
	int* tab_addr=&tab;
	int* tab_point=tab;
	int* tab_point_elt=&tab[0];
	printf("tab_addr:	%p\n",tab_addr);
	printf("tab_point:	%p\n",tab_point);
	printf("tab_point_elt:	%p\n",tab_point_elt);
	printf("tab[2][2]		%d\n",tab[2][2]);
	printf("tab[1][5]		%d\n",tab[1][5]);
	printf("*tab_point_elt+12	%d\n",*(tab_point_elt+12));
}

void q20(){
	int A[]={12,23,34,45,56,67,78,89,90};
	int *P;
	P=A;
	int i1=*P+2;		//14
	int i2=*(P+2);		//34
	int* a1= &A[4]-3;	//A[1]
	int* a2=A+3;		//A[3]
	int i3=&A[7]-P;		//7
	int* a3=P+(*P-10);	//A[2]
	int i4=*(P+*(P+8)-A[7]);//23
	int i=0;
	for(i=0;i<9;i++){
		printf("A[%d]:%p\n",i,&A[i]);
	}
	printf("i1:%d\n",i1);
	printf("i2:%d\n",i2);
	printf("a1:%p\n",a1);
	printf("a2:%p\n",a2);
	printf("i3:%d\n",i3);
	printf("a3:%p\n",a3);
	printf("i4:%d\n",i4);
}
void q26()
{
	/*int var=0; 4=var;
	(var+1)=4;*/
	/*int arr[]={1,2};
	int* p=&arr[0];
	*(p+1)=10;*/
	/*int var=10;
	int* addr=&(var+1);*/
	/*typedef enum color{red,green,blue} color;
	color c;
	c=green;
	blue=green;*/
	/*int var=0;
	&var=40;*/
}
int fois_deux(int a)
{
	return 2*a;
}
void appliquer_tableau(int pfunc(int),int* tab,int size)
{
	int i;
	for(i=0;i<size;i++){
		tab[i]=pfunc(tab[i]);
	}
}
int superieur(int a,int b){
	if(a>b) return 1;
	else if(a<b) return -1;	
	else return 0;
}
int inferieur(int a,int b){
	if(a<b) return 1;
	else if(a>b) return -1;	
	else return 0;
}
void tri(int* t, int n,int(* compare)(int,int))
{
	int i, i_max, j, tmp;
	for(i=0 ; i < n-1 ; i++) {
		i_max=i;
		for(j=i; j<n; j++) {
			if(compare(t[j],t[i_max])==1) {
				i_max=j;
			}
		}
	tmp = t[i_max];
	t[i_max] = t[i];
	t[i] = tmp;
	}
}
int main(int argc,char * argv[]){
	/*int arr[]={1,2,3,4,5};
	appliquer_tableau(fois_deux,arr,5);*/
	int arr[]={3,8,7,5,4};
	tri(arr,5,inferieur);
	int i;
	for(i=0;i<5;i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
	//matrix mymatrix;
	//int number_of_elements=atoi(argv[1]);
	//q6(number_of_elements);
	//q8(mymatrix,MAX_SIZE);
	//student fetard [3];
	//printf("%d\n",fetard[0].b.month);
	q26();
	//printf("%d\n",TP_strcmp("hello","hello"));
	//printf("%d\n",TP_strcmp("hello world","hello"));
	//printf("%d\n",TP_strcmp("chris evans","chris pratt"));
	/*int i;
	for(i=0;i<argc;i++){
		printf("%s\n",argv[i]);
	}*/
	/*if(argv[1]){
		long int li=strtol(argv[1],NULL,10);
		int i;
		for(i=0;i<li;i++){
			printf("*");
		}
		printf("\n");
	}else{
		printf("no number\n");
	}*/
	return 0;
}
