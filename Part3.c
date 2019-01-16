#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <stdarg.h>
#include <time.h>
void q2read(){
	char name[100];
	printf("file to display:");
	scanf("%s",name);
	strcat(name,".txt");
	FILE *stream=fopen(name,"r");
	if(stream){
		char c;
		c=fgetc(stream);
		while(c!=EOF){
			printf("%c",c);
			c=getc(stream);
		}
	}
	fclose(stream);
}
void q2write(){
	char name[100];
	printf("file to write:");
	scanf("%s",name);
	strcat(name,".txt");
	FILE *stream=fopen(name,"w");
	char ligne[101];
	fgets(ligne,100,stdin);
	while(strcmp(ligne,"fin\n")){
		fputs(ligne,stream);	
		fgets(ligne,100,stdin);
	}
	fclose(stream);
}
void q3(FILE* newfile){
	int i;
	//srand((unsigned)time(NULL));//!!!!
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
		//printf("-2:%d\n",phrase[strlen(phrase)-2]);-> \n
		//printf("-1:%d\n",phrase[strlen(phrase)-1]);-> \r
		//printf("-0:%d\n",phrase[strlen(phrase)]);  -> \0
		phrase[strlen(phrase)-2]=' ';
		phrase[strlen(phrase)-1]='\0';
		fputs(phrase,newfile);
		fclose(colonne);
	}
}
void q4(){
	int i;
	FILE *discours=fopen("discours.txt","w+");
	srand((unsigned)time(NULL));
	for(i=0;i<5;i++){
		q3(discours);
	}
	fclose(discours);
}
void printf_unsigned_int(unsigned int value){
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
	long entier=(long) (value);
	if(!entier){
		if(value<0){
			putchar('-');
		}
		putchar('0');
	}else{
		if(entier<0){
			entier*=-1;
		}
		char buffer[20];
		int nb=0;
		while(entier>0){
			buffer[nb++]=entier%10+'0';
			entier/=10;	
		}
		int i;
		for(i=nb-1;i>=0;i--){
			putchar(buffer[i]);
		}
		if(!nb){
			putchar('0');
		}
		//printf_signed_int(entier);
		//precision lost because of int casting
	}
	putchar('.');
	float nonentier=value-(long)value;
	if(nonentier<0){
		nonentier*=-1;
	}
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
	q4();	
	//mon_printf("texte:%s\nnb entier:%d\nnb a virgule:%f\n","bonjour",12345,3.141593);
	//print_float_list(4,3.14f,0.142857f,1.41f);
	/*FILE *bois=fopen("bois.txt","w+");
	q3(bois);
	fclose(bois);*/
	//q2write();
	//q2read();
	/*printf_unsigned_int(0);
	printf("\n");
	printf_unsigned_int(UINT_MAX);
	printf("\n");*/
	/*printf_signed_int(INT_MIN);
	printf("\n");
	printf_signed_int(INT_MAX);
	printf("\n");*/
	/*printf("%f\n",3.56f);
	printf_float(3.56);
	printf("\n");
	printf("%f\n",-0.000123f);
	printf_float(-0.000123);
	printf("\n");
	printf("%f\n",1e16f);
	printf_float(1e16);
	printf("\n");*/
	return 0;
}
