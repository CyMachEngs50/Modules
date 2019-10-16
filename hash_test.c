
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"
#include "hash.h"
#define MAXREG 10



bool search(person_t p*){
    if(strcmp(p->name, keyp)==0){
        return true;
}
else{
    return false;
}
}
typedef struct person{

    char name;
    int age;
    double rate;
} person_t;


person_t make_person(char *namep, int agep, double ratep){
    person_t *pp;
    if (!(pp=malloc(sizeof(person_t)))){
    printf("[Error : sorry no memeory was allocated for person pointer\n");
        return NULL;
    }
    else{
    strcpy(pp->name, namep);
    pp->age=agep;
    pp->rate=ratep;
    return pp;
}}

int main(void){
    hashtable_t *htp;
    person_t *p1, *p2, *p3;
    p1=make_person("Greg", 21, 20.0);
    p2=make_person("Bob",21, 20.0 );

    htp=hopen(10);
   if (hput(htp,(void *)p1)) == 0{
   printf("successful\n");
   }
   printf("not successfu\nl");

    happly(htp,&my_func);
    my_search_func = search;

    hsearch(htp, &my_func, p1);

    hremove(htp, &my_func, p1)


    hclose(htp);
}








}

}
