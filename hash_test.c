#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "hash.h"
#include "queue.h"


typedef struct person_t{                                                                                     int age;                                                                                                   double rate;                                                                                               char name [10];
} person_t;                                                                                                                                                                    
             

bool search(void* p, const void* keyp){
	person_t *temp;
	temp = (person_t *)p;
	if (strcmp(temp->name, keyp)==0){
		return true;
  }
	return false;
}

void myfunc(person_t* person){
	person->rate= 2*person->rate;
}

person_t* make_person(char *namep, int agep, double ratep){
	person_t *pp;
	if (!(pp=(person_t*)malloc(sizeof(person_t)))){
		printf("[Error : sorry no memeory was allocated for person pointer\n");
		return NULL;
	}
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
	person_t *htp;
	person_t *Louis, *John, *Bob, *Tim, *Cynthia, *Jeruto, *person;
 
	Louis= make_person("Louis", 21, 30.0);
	John= make_person("John", 22, 20.0);
	Bob=make_person("Bob",20, 60.0 );
	Tim=make_person("Tim",28, 90.0 );
	Cynthia=make_person("Cynthia",21, 20.0 );
	Jeruto=make_person("Jeruto",21, 30.0 );

			 
	htp=hopen(10);
	person= hremove(htp, search,"Louis", mystrlen("Louis"));    // remove from empty hashtable.               
  if (person != NULL){                                                                                    
    printf("Name: %s, Rate: %f",person->name,person->rate);                                               
  }                                                                                                        
  else{
		printf("Cannot remove from empty hashtable\n");                                            
  }  
	
	hput(htp, (void *)Louis,Louis->name,mystrlen(Louis->name)); // put to an empty hashtable
	hput(htp,(void *)John,John->name,mystrlen(John->name));    // put to a non-empty hashtable.
	hput(htp,(void *)Bob,Bob->name,mystrlen(Bob->name));
	hput(htp,(void *)Tim,Tim->name,mystrlen(Tim->name));
	hput(htp,(void *)Cynthia,Cynthia->name,mystrlen(Cynthia->name));
	hput(htp,(void *)Jeruto,Jeruto->name,mystrlen(Jeruto->name));

  happly(htp, (void*) myfunc);                                                                                      

	
	person=(person_t*)hsearch(htp, search,"Louis",mystrlen("Louis"));  // search for an element
	if (person != NULL){
		printf("Found %s, Rate: %f\n",person->name,person->rate);
	}else{
		printf("Louis not found during hsearch\n");
	}
	                                                                                                         
  person=(person_t*)hsearch(htp, search,"Louis",mystrlen("Paul"));  // search for an non existent element.
  if (person != NULL){                                                                                     
    printf("Name: %s, Rate: %f\n",person->name,person->rate);                                              
  }else{                                                                                                   
    printf("Paul not found during hsearch\n");                                                           
  }                    
	person= hremove(htp, search,"John", mystrlen("John"));    // remove from hashtable.
	if (person != NULL){                                                                                     
    printf("Removed: %s, Rate: %f\n",person->name,person->rate);                                                
  }                                                                                                        
  else{                                                                                                    
    printf("could not remove John\n");                                                        
  }     
	person=(person_t*)hsearch(htp, search,"John",mystrlen("John"));
	if (person != NULL){
		printf("Name: %s, Rate: %f",person->name,person->rate);
	}
	else{
		printf("John not found\n");
	}

	
	hclose(htp);
}

