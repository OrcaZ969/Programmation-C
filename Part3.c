#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <stdarg.h>
void q2(){
	FILE *stream=fopen("file.txt","r");
	char c;
	c=getc(stream);
	while(c!=EOF){
		printf("%c",c);
		c=getc(stream);
	}
}
void q3(FILE* newfile){
	int i;
	for(i=1;i<=4;i++){
		char name[80]="colonne";
		char index[2];
		index[0]=i+'0';//trick
		index[1]='\0';//indispensable
		strcat(name,index);
		strcat(name,".txt");
		FILE *colonne=fopen(name,"r");
		int nb=rand()%8;
		int compteur=0;
		char phrase[101];
		while(compteur<=nb){
			fgets(phrase,100,colonne);
			compteur++;
		}
		fputs(phrase,newfile);
		fclose(colonne);
	}
}
void q4(){
	int i;
	FILE *discours=fopen("discours.txt","w+");
	for(i=0;i<5;i++){
		q3(discours);
	}
	fclose(discours);
}
void printf_unsigned_int(int value){
	char buffer[20];
	int nb=0;
	while(value>0){
		buffer[nb++]=value%10+'0';
		value/=10;	
	}
	int i;
	for(i=nb-1;i>=0;i--){
		putchar(buffer[i]);
	}
	if(!nb){
		putchar('0');
	}
}
void printf_signed_int(int value){
	if(value<0){
		putchar('-');
		printf_unsigned_int(-1*value);
	}else{
		printf_unsigned_int(value);
	}
}
void printf_float(float value){
	int entier=(int) value;
	if(!entier){
		if(value<0){
			putchar('-');
		}
		putchar('0');
	}else{
		printf_signed_int(value);
	}
	putchar('.');
	float nonentier=value-(int)value;
	if(nonentier<0){
		nonentier*=-1;
	}
	//int i=1000000*nonentier;
	//printf("%d\n",(int)(nonentier*1000000));
	//printf_unsigned_int(i);
	int i;
	for(i=0;i<6;i++){
		nonentier*=10;
		int digit=nonentier;
		putchar(digit+'0');
		nonentier=nonentier-(int)nonentier;
	}
}
void print_float_list(int count,...){
	va_list ap;
	va_start(ap,count);
	int j;
	for(j=0;j<count;j++){
		printf_float(va_arg(ap,double));
		putchar('\n');
	}
	va_end(ap);	
}
void mon_printf(char *string,...){
	va_list ap;
	int i=0;
	char c;
	va_start(ap,string);
	while((c=string[i++])!='\0'){
		if(c!='%'){
			putchar(c);
		}else{
			char marqueur=string[i++];
			if(marqueur=='d'){
				printf_signed_int(va_arg(ap,int));
			}
			else if(marqueur=='u'){
				printf_unsigned_int(va_arg(ap,unsigned int));
			}
			else if(marqueur=='f'){
				printf_float(va_arg(ap,double));
			}
			else if(marqueur=='c'){
				putchar(va_arg(ap,int));
			}
			else if(marqueur=='s'){
				char* str=va_arg(ap,char*);
				int j=0;
				while(str[j]!='\0'){
					putchar(str[j++]);
				}
			}	
		}
	}	
}
int main(){
	mon_printf("texte:%s\nnb entier:%d\nnb a virgule:%f\n","bonjour",12345,3.141593);
	//print_float_list(4,3.14f,0.142857f,1.41f);
	/*FILE *bois=fopen("bois.txt","w+");
	q3(bois);
	fclose(bois);*/
	//q4();
	/*printf_unsigned_int(0);
	printf("\n");
	printf_unsigned_int(UINT_MAX);
	printf("\n");*/
	/*printf_signed_int(INT_MIN);
	printf("\n");
	printf_signed_int(INT_MAX);
	printf("\n");*/
	/*printf_float(3.56);
	printf("\n");
	printf_float(-0.000123);
	printf("\n");*/
	/*float f=1e16;
	printf("%f\n",f);
	printf_float(1e16);
	printf("\n");*/
	return 0;
}
