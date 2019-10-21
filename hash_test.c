
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"
#include "hash.h"




static bool search(void* p, const void* keyp){
	person_t *temp;
	temp = (person_t *)p;
	printf("i was called\n");
	if (strcmp(temp->name, keyp)==0){
		 return true;
  }
	return false;
}

static void myfunc(person_t* person){
      person->rate= 2*person->rate;
}


static person_t* make_person(char *namep, int agep, double ratep){
    person_t *pp;
    if (!(pp=malloc(sizeof(person_t)))){
       printf("[Error : sorry no memeory was allocated for person pointer\n");
        return NULL;
    }

    pp->next=NULL;
    strcpy(pp->name, namep);
    pp->age=agep;
    pp->rate=ratep;
    return pp;
}

static int mystrlen(char *p){
  int len;
  for (len=0; *p!='\0'; p++){
       len++;
       }

  return len;
}

int main(void){
    hashtable_t *htp;
    person_t *p1, *p2, *p3,*p4,*p5,*p6,*p7,*person;
    p1= make_person("Louis", 21, 30.0);
    p2= make_person("John", 22, 20.0);
    p3=make_person("Bob",20, 60.0 );
    p4=make_person("Tim",28, 90.0 );
    p5=make_person("Cynthia",21, 20.0 );
    p6=make_person("Jeruto",21, 30.0 );
    p7=make_person("Jerutoh",18, 50.0 );

    htp=hopen(10);
    printf("executed upto here\n");
		// happly(htp,&myfunc);
	 

    hput(htp,(void *)p2,p2->name,mystrlen(p2->name));
    hput(htp,(void *)p3,p3->name,mystrlen(p3->name));
    hput(htp,(void *)p4,p4->name,mystrlen(p4->name));
    hput(htp,(void *)p5,p5->name,mystrlen(p5->name));
    hput(htp,(void *)p6,p6->name,mystrlen(p6->name));
    hput(htp,(void *)p7,p7->name,mystrlen(p7->name));
    printf("added all items\n");
		
		//	bool mysearch_ret = search(p2, "John");
    person=(person_t*)hsearch(htp,&search,"Louis",mystrlen("Louis"));
		if (person != NULL){
			printf("Name: %s, Rate: %f\n",person->name,person->rate);
			}else{
			printf("Person not found\n");
		}
		//hremove(htp,&search,"John", keylen);
		//person=(person_t*)hsearch(htp,&search,"John",keylen);
		//if (person != NULL){
		//printf("Name: %s, Rate: %f",person->name,person->rate);
		//}else{
		//printf("Person not found");
		//}

    //hclose(htp);
}

