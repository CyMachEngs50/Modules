/* list.c --- module that implements list.h
 *
 *
 * Author: CynthiaJeruto
 * Created: Thu Oct  3 14:39:13 2019 (-0400)
 * Version: 1.0
 *
 * Description:implements all the functions that are in list.h with an associated Makefile. your modeule should hide the list of cars internally with the global declaration "static car_t *front=NULL;" The list has no order, can use put and get.
 *
 */
#include "list.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
/*allocating memory to the list */
static car_t *front=NULL;

/* put(): place a car at the beginning of the list
 * returns 0 if successful; nonzero otherwise
 */
int32_t lput(car_t *car_pointer){
	if (front==NULL){
		front=car_pointer;
	}
	else{
		car_pointer->next=front->next;
		front->next=car_pointer;
	}
	return 0;
}

/* get(): remove and return the first car in the list;
 * return NULL if the list is empty
 */
car_t* lget(){
	car_t *temp;
	if (front==NULL){
		temp = NULL;
	}
	else{
		temp=front->next;
		front->next=front->next->next;
	}
	return temp;
}

/* apply a function to every car in the list */
void lapply(void (*fn)(car_t *cp)){
	car_t *p;
	for (p=front; p!=NULL; p=p->next){
	    fn(p);
	}
}
/* remove(): find, remove, and return any car with
 * the designated plate; return NULL if not present
 */

car_t *lremove(char *platep){
	car_t *p,*f;
	f=NULL;
	if (strcmp(front->next->plate, platep) ==0){
	    f=front->next;
		front->next=f->next;
	}else{
		for (p=front->next; p!=NULL; p=p->next){
			if (strcmp(p->plate, platep) == 0){
				f->next = p->next;
			}
			f = p;
			break;
		}
	}
	return f;
}

