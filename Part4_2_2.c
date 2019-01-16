#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
enum investissement {PRESSE,MAIRIE,REUNION,WEB,FETE};
typedef struct member_s{
	char * nom;
	char * prenom;
	enum investissement i;
	char * boisson;
}value_type_t;

void displayValue(value_type_t* value){
	printf("nom:%s\n",value->nom);
	printf("prenom:%s\n",value->prenom);
	printf("investissement:%d\n",value->i);
	printf("boisson:%s\n",value->boisson);
}

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
void displayList(struct node_s* list_head){
	struct node_s* courrent=list_head;
	if(courrent!=NULL){
		while(courrent!=NULL){
			displayValue(&courrent->value);
			courrent=courrent->suivant;
		}
	}
}

bool are_same_people(struct member_s * a_member, struct member_s * an_other){
	if(strcmp(a_member->nom,an_other->nom)) return false;
	if(strcmp(a_member->prenom,an_other->prenom)) return false;
	if(a_member->i!=an_other->i) return false;
	if(strcmp(a_member->boisson,an_other->boisson)) return false;
	return true;
}

struct node_s* remove_node(struct node_s* list_head,struct node_s* to_be_remove, bool equals_fct(struct member_s*,struct member_s*)){
	struct node_s* courrent=list_head;
	if(courrent!=NULL){
		if(equals_fct(&(to_be_remove->value),&courrent->value)){
			list_head=list_head->suivant;
			free(courrent);
			return list_head;
		}
		while(courrent!=NULL){
			if(equals_fct(&(to_be_remove->value),&(courrent->suivant->value))){
				struct node_s* delete=courrent->suivant;
				courrent->suivant=courrent->suivant->suivant;
				free(delete);
				break;
			}
		}
	}
	return list_head;	
}

int getLength(struct node_s* list_head){
	int length=0;
	struct node_s* courrent=list_head;
	if(courrent!=NULL){
		while(courrent!=NULL){
			courrent=courrent->suivant;
			length++;
		}
	}
	return length;
}
struct node_s* invert(struct node_s* list_head){
	struct node_s* courrent=list_head;
	struct node_s* newHead=list_head;
	if(courrent!=NULL){
		courrent=courrent->suivant;
		while(courrent!=NULL){
			struct node_s* ajout=(struct node_s*)malloc(sizeof(struct node_s));
			ajout->suivant=newHead;
			ajout->value=courrent->value;//value copie
			newHead=ajout;
			courrent=courrent->suivant;
		}
	}
	courrent=list_head;
	//delete all the nodes after old head node
	if(courrent!=NULL){
		courrent=courrent->suivant;
		while(courrent!=NULL){
			struct node_s* delete=courrent;
			courrent=courrent->suivant;
			free(delete);
		}
	}
	list_head->suivant=NULL;//old head node become new end node, pointing to NULL
	return newHead;
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
	value_type_t KM={"Marquet","Kevin",PRESSE,"Chouffe"};
	value_type_t J={"","Juan",REUNION,"Clara"};
	value_type_t AB={"Bocceli","Adamo",WEB,"San Pellogrino"};
	struct node_s* head=NULL;
	head=insert_node_end(head,&KM);
	insert_node_end(head,&J);
	insert_node_end(head,&AB);
	displayList(head);
	printf("\n");
	head=remove_node(head,head,are_same_people);
	displayList(head);
	printf("\n");
	head=invert(head);
	displayList(head);	
	struct node_s* courrent=head;
	if(courrent!=NULL){
		while(courrent!=NULL){
			struct node_s* delete=courrent;
			courrent=courrent->suivant;
			free(delete);
		}
	}
	//printf("%s\n",*head);
	return 0;
}
