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


typedef struct person{

	char name [MAXREG];
	int age;
	double rate;
	person_t* next;
	
}person_t;


person_t* make_person(char* namep, int agep, double ratep){

	if (!(cp=malloc(sizeof(car_t)))){                        
    printf("[Error : no memory was allocated to list of cars pointer]\n");                      
    return NULL;
	}
	
  person_t *pp;
	pp->next = NULL;
	strcpy(pp->name, namep);
	pp->age=agep;
	pp->rate=ratep;
	return pp;

}

int main (void){

	queue_t *qp;
	person_t *pp;

	qp=qopen();
	pp=make_person("Greg", 21, 20.0);
	qput(qp,(void*)pp);
	pp=(person_t*)qget();
	
}
