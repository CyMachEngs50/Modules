/* queue.c --- 
 * 
 * 
 * Author: Gregory Macharia
 * Created: Tue Oct 15 10:36:17 2019 (-0400)
 * Version: 
 * 
 * Description: 
 * 
 */
/* queue.c --- 
 * 
 * 
 * Author: Gregory Macharia
 * Created: Tue Oct 15 10:35:58 2019 (-0400)
 * Version: 
 * 
 * Description: 
 * 
 */
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
#include <stdbool.h>
#include <stdio.h>

typedef struct node_t {                                                                        
  struct node_t *next;                                                                        
  void* data;                                                                                 
} node_t;

typedef struct queue_t{
	node_t *front;
	node_t *back;
	int size;
}queue_t;

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
	queue_t *qp;	
	if (!(qp=(queue_t*)malloc(sizeof(queue_t)))){                                             
    printf("[Error : no memory was allocated to list of cars pointer]\n");  
    return NULL;                                                             
  }
 qp->front=NULL;
 qp->back=NULL;
 qp->size=0;
 return (queue_t*)qp;
}

/* deallocate a queue. frees everything in it */
void qclose(queue_t *qp){
  node_t *p=qp->front;
	node_t *s=NULL;
	while (p!=NULL){
		s=p->next;
		free(p->data);
    free(p);
		p=s;
	} 
	free(qp);
	
}

/* put element at the end of the queue
 *returns 0 if successfull; non zero if otherwise
 */
int32_t qput(queue_t *qp, void *elementp){
	int32_t i=1;	 
	node_t *np=create_node(); 
	np->data=elementp;
	if (qp->size==0){
		qp->front=np;
		qp->back=np;
		i=0;
	}
	else{
		qp->back->next=np;
		qp->back=np;
		i=0;
	}
	qp->size+= 1;
	return i;
}

/* get the first first element from queue, removing it from the queue */
void* qget(queue_t *qp){
	if (qp->size >0){
		node_t *tempfront=qp->front;
 		qp->front=qp->front->next;
	  tempfront->next=NULL;
		qp->size -=1;
		printf("returned first in!\n"); 
		return tempfront->data;
	}
	else{
		printf("Cannot get from an empty queue!\n");
		return NULL;
	}
}

/* apply a function to every element of the queue */
void* qapply(queue_t *qp, void (*fn)(void* elementp)){
	node_t *np;
  for (np=qp->front; np!=NULL; np=np->next){
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
	for (np=qp->front; np!=NULL; np=np->next){
			if(searchfn(np->data, skeyp)==true){
				printf("found!\n");
				return np->data;
		}
	}
	printf("Not found!\n");
	return NULL;
}

/* search a queue using a supplied boolean function (as in qsearch),                            
 * removes the element from the queue and returns a pointer to it or                            
 * NULL if not found                                                                            
 */

void* qremove(queue_t *qp, bool (*searchfn)(void* elementp, const void* keyp), const void* skeyp){
	node_t *prevp;
	node_t *np;
	prevp=qp->front;
	if (qp->size == 0){
		printf("Cannot remove from an empty list!\n");
		return NULL;
	}
	if (qp->size == 1){
		if(searchfn(qp->front->data, skeyp)==true){
			node_t *tempfront=qp->front;
			qp->front = NULL;                                                                                            
			qp->back = NULL;                                                                                             
			qp->size -= 1;
			printf("queue is now empty!\n"); 
			return tempfront->data;
		}
	}
	else{
		prevp=qp->front;
		if(searchfn(qp->front->data, skeyp)==true){
			node_t *tempfront=qp->front;                                                                                
			qp->front=qp->front->next;                                      
			tempfront->next=NULL;                                                                       
			qp->size -= 1;
			printf("Removed at front!\n");
			return tempfront->data;
		}
		for (np=qp->front->next; np!=NULL; np=np->next){
			if(searchfn(np->data, skeyp)==true){
			  prevp->next=np->next;
				np->next=NULL;
				qp->size -= 1;
				printf("Removed at middle!\n"); 
				return np->data;                                                                                           
			}                                                                                                         
			prevp=np; 
		}
	}
	printf("Cannot remove: Nothing matched the key!\n"); 
 	return NULL;
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

