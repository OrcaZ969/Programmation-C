#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct word_s{
	char * mot;
	int taille;
}value_type_t;

struct node_s{
	value_type_t value;
	struct node_s* suivant;
};

struct node_s* insert_node_end(struct node_s* list_head,value_type_t* value){
	if(list_head==NULL){
		list_head=(struct node_s*)malloc(sizeof(struct node_s));
		list_head->value=*value;
		list_head->suivant=NULL;
		return list_head;
	}else{
		struct node_s* courrent=list_head;
		while(courrent->suivant!=NULL){
			courrent=courrent->suivant;
		}
		struct node_s* nouveau=(struct node_s*)malloc(sizeof(struct node_s));
		nouveau->value=*value;
		nouveau->suivant=NULL;
		courrent->suivant=nouveau;
		return nouveau;
	}
}
int getLength(struct node_s* list_head){
	int length=0;
	struct node_s* courrent=list_head;
	if(courrent!=NULL){
		while(courrent->suivant!=NULL){
			courrent=courrent->suivant;
			length++;
		}
	}
	return length;
}
void convertLowerCase(char* str){
	int i;
	char c=str[i];
	int length=strlen(str);
	for(i=0;i<length;i++){
		str[i]=tolower(str[i]);	
	}
}
int main(){
	FILE *stream=fopen("discours.txt","r");
	char c;
	int length=0;
	char mot[100];
	struct node_s* head=NULL;
	int nbJe=0,nbNous=0,nbVous=0;
	while((c=getc(stream))!=EOF){
		if(c!=' '&&c!=','&&c!='.'&&c!='\n'){
			mot[length++]=c;
		}else{
			char* ajout=(char*)malloc(sizeof(char)*(length+1));
			int j;
			for(j=0;j<length;j++){
				ajout[j]=mot[j];
			}
			ajout[length]='\0';
			convertLowerCase(ajout);
			value_type_t* value=(value_type_t*)malloc(sizeof(value_type_t));
			value->mot=ajout;
			if(!strcmp(ajout,"je")) nbJe++;
			if(!strcmp(ajout,"nous")) nbNous++;
			if(!strcmp(ajout,"vous")) nbVous++;
			value->taille=length;
			if(head==NULL){
				printf("%s\n",(head=insert_node_end(head,value))->value.mot);
				//attention to the difference between formal parameter and effective parameter
			}else{
				printf("%s\n",insert_node_end(head,value)->value.mot);
			}
			length=0;
			if(c==','||c=='.'){
				c=getc(stream);
			}
		}
	}
	printf("nb de mot dans ce discours:%d\n",getLength(head));
	printf("nb de 'je':%d\n",nbJe);
	printf("nb de 'nous':%d\n",nbNous);
	printf("nb de 'vous':%d\n",nbVous);
	return 0;
}
