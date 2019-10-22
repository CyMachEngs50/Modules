/* listTest.c --- test functionality of the list.c module
 *
 *
 * Author: CynthiaJeruto
 * Created: Tue Oct  8 21:21:48 2019 (-0400)
 * Version: 1.0
 *
 * Description: will call allthe functions defined in list.h and implemenmted in list.c returning values O if successful and 1 if otherwise
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <string.h>



static car_t* create_car(char* plate, float price, int year) {
  car_t *cp;//initializing the lsit..creating a heap
  if (!(cp=malloc(sizeof(car_t)))){
    printf("[Error : no memory was allocated to list of cars pointer]\n");
		return NULL;
	}
  printf("price for car %lf\n",price);
  cp->next=NULL;
  strcpy(cp->plate, plate);
  cp->price=price;
  cp->year=year;
	return cp;
}

static void myfunc(car_t* car){
      car->price= 2*car->price;
}

int main(void){
	car_t *car1, *car2, *car3;
	car1=create_car("kaa", 5000.00, 2019);
	car2=create_car("kab", 200000.00, 2003);
	car3=create_car("kac", 1000000.00, 2015);

	lput(car1);
	printf("put car1!\n");
	lput(car2);
	printf("put car2!\n");
	lput(car3);
	printf("put car3!\n");
	car_t *car=lremove("kac");
	printf("Returned car plate : %s\n",car->plate);

	lapply(&myfunc);
    car_t *cart1=lremove("kac");
    if (cart1 !=NULL){
        printf("Removed car plate %s price : %lf\n",cart1->plate,cart1->price);
    }else{
      printf("not removed..\n");
    }
    free(car1);
    free(car2);
    free(car3);

}

