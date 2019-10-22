
/* queue.c --- a module that implements a generic queue 
 * 
 * 
 * Author: Gregory Macharia and Cynthia Jeruto
 * Created: Sun Oct 13 17:02:59 2019 (-0400)
 * Version: 
 * 
 * Description: A module that implements all the public methods that are in queue.h with an associate Makefile. the queue should be able to hold generic elements. 
 * 
 */
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "queue.h"

typedef struct node_t {                                                                        
  struct node_t *next;                                                                        
  void* data;                                                                                 
} node_t;

typedef struct iqueue_t{
	node_t *front;
	node_t *back;
	int size;
}iqueue_t;

static node_t* create_node(void){
	node_t *np;	
	if (!(np=(node_t*)malloc(sizeof(node_t)))){                                             
    printf("[Error : no memory was allocated to list of cars pointer]\n");  
    return NULL;                                                             
  }
 np->next=NULL;
 np->data=NULL;
 return np;
}

/* create an empty queue */
queue_t* qopen(void){
	iqueue_t *iqp;	
	if (!(iqp=(iqueue_t*)malloc(sizeof(iqueue_t)))){                                             
    printf("[Error : no memory was allocated to list of cars pointer]\n");  
    return NULL;                                                             
  }
 iqp->front=NULL;
 iqp->back=NULL;
 iqp->size=0;
 return (queue_t*)iqp;
}

/* deallocate a queue. frees everything in it */
void qclose(queue_t *qp){
  iqueue_t *iqp= (iqueue_t*) qp;                                                                           
  node_t *p=iqp->front;
	node_t *s=NULL;
	while (p!=NULL){
		s=p->next;
		free(p->data);
    free(p);
		p=s;
	} 
	free(iqp);
}

/* put element at the end of the queue
 *returns 0 if successfull; non zero if otherwise
 */
int32_t qput(queue_t *qp, void *elementp){
  iqueue_t *iqp= (iqueue_t*) qp;                                                                           
	int32_t i=1;	 
	node_t *np=create_node(); 
	np->data=elementp;
	if (iqp->size==0){
		iqp->front=np;
		iqp->back=np;
		i=0;
	}
	else{
		iqp->back->next=np;
		iqp->back=np;
		i=0;
	}
	iqp->size+= 1;
	return i;
}

/* get the first first element from queue, removing it from the queue */
void* qget(queue_t *qp){
	iqueue_t *iqp= (iqueue_t*) qp;                                                                        
	if (iqp->size >0){
		node_t *tempfront=iqp->front;
 		iqp->front=iqp->front->next;
	  tempfront->next=NULL;
		iqp->size -=1;
		return tempfront->data;
	}
	else{
		return NULL;
	}
}

/* apply a function to every element of the queue */
void qapply(queue_t *qp, void (*fn)(void* elementp)){
	node_t *np;
	iqueue_t *iqp= (iqueue_t*) qp;                                                                         
  for (np=iqp->front; np!=NULL; np=np->next){
		fn(np->data);
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
	node_t *np;
	iqueue_t *iqp= (iqueue_t*) qp;
	for (np=iqp->front; np!=NULL; np=np->next){
			if(searchfn(np->data, skeyp)==true){
				return np->data;
		}
	}
	return NULL;
}

/* search a queue using a supplied boolean function (as in qsearch),                            
 * removes the element from the queue and returns a pointer to it or                            
 * NULL if not found                                                                            
 */

void* qremove(queue_t *qp, bool (*searchfn)(void* elementp, const void* keyp), const void* skeyp){
	node_t *prevp;
	node_t *np;
	iqueue_t *iqp= (iqueue_t*) qp;                                                                        
	prevp=iqp->front;
	if (iqp->size == 0){
		return NULL;
	}
	if (iqp->size == 1){
		if(searchfn(iqp->front->data, skeyp)==true){
			node_t *tempfront=iqp->front;
			iqp->front = NULL;                                                                                            
			iqp->back = NULL;                                                                                             
			iqp->size -= 1;
			return tempfront->data;
		}
	}
	else{
		prevp=iqp->front;
		if(searchfn(iqp->front->data, skeyp)==true){
			node_t *tempfront=iqp->front;                                                                                
			iqp->front=iqp->front->next;                                      
			tempfront->next=NULL;                                                                       
			iqp->size -= 1;
			return tempfront->data;
		}
		for (np=iqp->front->next; np!=NULL; np=np->next){
			if(searchfn(np->data, skeyp)==true){
			  prevp->next=np->next;
				np->next=NULL;
				iqp->size -= 1;
				return np->data;                                                                                           
			}                                                                                                         
			prevp=np; 
		}
	}
	return NULL;
}

/* concatenatenates elements of q2 into q1                                                      
 * q2 is dealocated, closed, and unusable upon completion              */

void qconcat(queue_t *q1p, queue_t *q2p){
	iqueue_t *iq1p= (iqueue_t*) q1p;
	iqueue_t *iq2p= (iqueue_t*) q2p; 
	if (iq1p->size==0 && iq2p->size>0){
		iq1p->front=iq2p->front;
		iq1p->back=iq2p->back;
		iq1p->size = iq2p->size;
	}
	if (iq1p->size>0 && iq2p->size>0){
		iq1p->back->next=iq2p->front;
		iq1p->back=iq2p->back;
		iq1p->size += iq2p->size;
	}
}

