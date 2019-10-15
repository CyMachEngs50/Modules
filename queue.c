/* queue.c --- a module that implements a generic queue 
 * 
 * 
 * Author: Gregory Macharia
 * Created: Sun Oct 13 17:02:59 2019 (-0400)
 * Version: 
 * 
 * Description: A module that implements all the public methods that are in queue.h with an associate Makefile. the queue should be able to hold generic elements. 
 * 
 */
#include <stdint.h>
#include <stdlib.h>

typedef void queue{
	void* front;
	void* back;
	int size;
}queue_t;


/* create an empty queue */
queue_t* qopen(void){
 if (!(cp=malloc(sizeof(car_t)))){                                             
    printf("[Error : no memory was allocated to list of cars pointer]\n");  
    return NULL;                                                             
  }
 queue_t *qp;
 qp->front=NULL;
 qp->back=NULL;
 qp->size=0;
 return qp;
}

/* deallocate a queue. frees everything in it */
void qclose(queue_t *qp){

}

/* put element at the end of the queue
 *returns 0 if successfull; non zero if otherwise
 */
int32_t qput(queue_t *qp, void *elementp){
	if (qp->size=0){
	qp->front=elementp;
	qp->back=elementp;
	}
	else{
		qp->back->next=elementp;
		qp->back=elementp;
		qp->size+= 1;
	}
}

/* get the first first element from queue, removing it from the queue */
void* qget(queue_t *qp){
	void* tempfront=qp->front;
	qp->front=front->next;
	tempfront->next=NULL;
	qp->size -=1;
	return tempfront;
}

/* apply a function to every element of the queue */
void* qapply(queue_t *qp, void (*fn)(void* elementp)){
	void* p;
	
  for (p=qp->front; p!=NULL; p=p->next){                                                                       
    fn(p);
	}
}

/* search a queue using a supplied boolean function                                             
 * skeyp -- a key to search for                                                                 
 * searchfn -- a function applied to every element of the queue                                 
 *          -- elementp - a pointer to an element                                               
 *          -- keyp - the key being searched for (i.e. will be                                  
 *             set to skey at each step of the search                                           
 *          -- returns TRUE or FALSE as defined in bool.h                                       
 * returns a pointer to an element, or NULL if not found                                        
 */
void* qsearch(queue_t *qp, bool (*searchfn)(void* elementp, const void* keyp), const void* skeyp){

}

/* search a queue using a supplied boolean function (as in qsearch),                            
 * removes the element from the queue and returns a pointer to it or                            
 * NULL if not found                                                                            
 */

void* qremove(queue_t *qp, bool (*searchfn)(void* elementp, const void* keyp), const void* skeyp){

}

/* concatenatenates elements of q2 into q1                                                      
 * q2 is dealocated, closed, and unusable upon completion                                       
 */
void qconcat(queue_t *q1p, queue_t *q2p){
	if (q1p->size==0 && q2p->size>0){
		q1p->front=q2p->front;
		q1p->back=q2p->back;
		q1p->size = q2p->size;
	}
	if (q1p->size>0 && q2p->size>0){
		q1p->back->next=q2p->front;
		q1p->back=q2p->back;
		q1p->size += q2p->size;
	}
}

