/* queuetest.c --- a scaffold for testing the functionality of the methods outlined in queue.h
 * 
 * 
 * Author: Gregory Macharia
 * Created: Sun Oct 13 17:59:16 2019 (-0400)
 * Version: 
 * 
 * Description: tests all the possible cases for the queue methods to validate the interface.
 * 
 */
#include <stdio.h>
#include "queue.h"
#include <string.h>
#include <stdlib.h>
#define MAXREG 10

typedef struct person {
	char name [MAXREG];
	int age;
	double rate;
} person_t;

void double_rate(person_t* person){                                                                     
  person->rate= 2*person->rate;                                                                            
}

bool search(person_t *p, const char keyp[MAXREG]){
  if (strcmp(p->name, keyp)==0){                                                
    return true;                                                                             
  }
	else return false;
}
person_t* make_person(char* namep, int agep, double ratep){
	person_t *pp;
	if (!(pp=malloc(sizeof(person_t)))){                        
    printf("[Error : no memory was allocated to list of cars pointer]\n");                      
    return NULL;
	}
	strcpy(pp->name, namep);
	pp->age=agep;
	pp->rate=ratep;
	return pp;
}

int main (void){
	person_t *qp;
	person_t *Greg,*Bob, *person, *Graham, *Cynthia;
  //bool fn = bool (*fn)(void* elementp, const void* keyp);
	//fn= (bool*) search;
	Greg=make_person("Greg", 21, 20.0);
	Bob=make_person("Bob", 21, 20.0);
	Graham=make_person("Graham", 20, 40.0);
	Cynthia=make_person("Cynthia", 19, 50.0); 
	
	qp=qopen();
	person=(person_t*)qget(qp);   // get from empty queue.
	if (person ==NULL){
		printf("cannot get from empty list.\n");
	}		
	person=(person_t*)qremove(qp, (void*)search, "Greg");
	if (person ==NULL){                                                                                          
    printf("cannot remove from empty list.\n");                                                              }
	else { printf("got from front of queue: %s\n", person->name);}
	qput(qp,(void*)Greg);  // put to empty queue
	qput(qp,(void*)Bob);  // put to a non empty queue
	person=(person_t*)qsearch(qp, (void*)search, "Bob");  // search for element.
	if (person != NULL){
		printf("found %s\n", person->name);
	}
	else {
		printf("found no one with name Bob\n");
	}
	person=(person_t*)qremove(qp,(void*) search, "Greg");  // remove from queue.
	if  (person != NULL){
		printf("removed %s\n", person->name);
	}
	else{
		printf("no one called Greg to remove");
	}
	person=(person_t*)qget(qp);   // get from queue
	if (person ==NULL){                                                                                     
    printf("cannot get from empty list.\n");                                                               
  }
	else{
		printf("got from front of queue: %s\n", person->name);
	}
	qput(qp,(void*) Graham); 
	qapply(qp,(void*) double_rate);  // apply a function.
	person=(person_t*)qsearch(qp,(void*) search, "Graham");
	if (person != NULL){
		printf("found %s rate: %f \n", person->name, person->rate);
	}
  else {
		printf("found no one with name Graham\n");
	}     
	qclose(qp); //close queue.
}
