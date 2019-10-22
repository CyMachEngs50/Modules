/*
 * hash.c -- implements a generic hash table as an indexed set of queues.
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hash.h"
#include "queue.c"

#define MAXNM 80                                                                                     
#define MAXREG 10   

typedef struct hnode_t {                                                                            
  struct queue_t *q;
  uint32_t index;                                                                                      
} hnode_t;

typedef struct ihashtable_t{                                                                          
  hnode_t *firstnode;                                                                               
  int hsize;                                                                                         
} ihashtable_t;                                                                                       
                    
/*
 * SuperFastHash() -- produces a number between 0 and the tablesize-1.
 *
 * The following (rather complicated) code, has been taken from Paul
 * Hsieh's website under the terms of the BSD license. It's a hash
 * function used all over the place nowadays, including Google Sparse
 * Hash.
 */
#define get16bits(d) (*((const uint16_t *) (d)))

static uint32_t SuperFastHash (const char *data,int len,uint32_t tablesize) {
  uint32_t hash = len, tmp;
  int rem;
	
  if (len <= 0 || data == NULL)
		return 0;
  rem = len & 3;
  len >>= 2;
  /* Main loop */
  for (;len > 0; len--) {
    hash  += get16bits (data);
    tmp    = (get16bits (data+2) << 11) ^ hash;
    hash   = (hash << 16) ^ tmp;
    data  += 2*sizeof (uint16_t);
    hash  += hash >> 11;
  }
  /* Handle end cases */
  switch (rem) {
  case 3: hash += get16bits (data);
    hash ^= hash << 16;
    hash ^= data[sizeof (uint16_t)] << 18;
    hash += hash >> 11;
    break;
  case 2: hash += get16bits (data);
    hash ^= hash << 11;
    hash += hash >> 17;
    break;
  case 1: hash += *data;
    hash ^= hash << 10;
    hash += hash >> 1;
  }
  /* Force "avalanching" of final 127 bits */
  hash ^= hash << 3;
  hash += hash >> 5;
  hash ^= hash << 4;
  hash += hash >> 17;
  hash ^= hash << 25;
  hash += hash >> 6;
  return hash % tablesize;
}

static hnode_t* create_hnode(uint32_t index){
	hnode_t *kv;
	if (!(kv=(hnode_t*)malloc(sizeof(hnode_t)))){
    printf("[Error : no memory was allocated to hash table nodes]\n");
    return NULL;
  }
	kv->q=qopen();
  kv->index=index;
  return kv;
}

//function to use in happly

//static void my_func(person_t* p1){
//    p1->age = 2*p1->age;
//
//}
//opening a hash table with initial size hsize
hashtable_t *hopen(uint32_t hsize){
	ihashtable_t *htp;
	if(!(htp=malloc(sizeof(ihashtable_t)))){
		printf("[Error:no memory was allocated to the table\n");
    return NULL;
	}
	for (uint32_t i=0 ; i < hsize: i++){
		create_hnode(i);
	}
	htp->hsize=hsize;
	return (hashtable*) htp;	
}

///* hclose -- closes a hash table */
void hclose(hashtable_t *htp){
	 for (uint32_t i=0 ; i < hsize: i++){                                                             
		 free(htp[]);   
	hnode_t *p=htp->firstnode;
  hnode_t *s= NULL;
  while (p!=NULL){
		s=p->next;
		qclose(p->q);
		free(p->ke
		
	//	free(htp);
	//	htp = NULL;
	
}


//
///* hput -- puts an entry into a hash table under designated key                 * returns 0 for success; non-zero otherwise                                    */
int32_t hput(hashtable_t *htp, void *ep, const char *key, int keylen){

	int value=0;
	if (htp != NULL && key != NULL && ep != NULL){
		//geeting the hash index
		int32_t hash_index  = SuperFastHash ( key, keylen, htp->hsize);  //return ht%size
		kvnode_t *hnode=create_hnode();
		kvnode_t *prev;
		if (htp->first==NULL){
			queue_t *qp = qopen();
			qput(qp,ep);
			hnode->q=qp;
			hnode->key=hash_index;
			htp->first=hnode;
			}else{
			for (hnode=htp->first; hnode->key !=MAXREG-1; hnode=hnode->down){
					if (hnode->key==hash_index){
						if (hnode->q == NULL){
							queue_t *qp = qopen();
							qput(qp,ep);
							hnode->q=qp;
							hnode->key=hash_index;
							if (prev->key < hnode->key){
								prev->down=hnode;
							}else{
								hnode->down=prev;
							}
							if (htp->first->key>hnode->key){
								hnode->down=htp->first;
								htp->first=hnode;
							}
						}else{
							qput(hnode->q,ep);
						}
						break;
					}
					prev=hnode;
				}
			}
		}
	
		return value; //0 if successfull
}
/* happly -- applies a function to every entry in hash table */
void happly(hashtable_t *htp, void (*fn)(void* ep)){
	printf("entered here 0\n");
	kvnode_t *hnode;
	for (hnode=htp->first; hnode->key !=MAXREG-1; hnode=hnode->down){
		if (hnode->q != NULL){
			qapply(hnode->q,fn);
		}
	}
	
}

/* hsearch -- searchs for an entry under a designated key using a
 * designated search fn -- returns a pointer to the entry or null if
 * not found
 */
void *hsearch(hashtable_t *htp, bool (*searchfn)(void* elementp, const void* searchkeyp),const char *key, int32_t keylen){
	
	int32_t hash_index  = SuperFastHash ( key, keylen, htp->hsize); 
	kvnode_t *hnode;
	for (hnode=htp->first; hnode->key !=MAXREG-1; hnode=hnode->down){

		if (hnode->key==hash_index){
			if (hnode->q != NULL){
				
				return qsearch(hnode->q, searchfn, key);
			} 
		}
	}
	printf("Not Found element to hashmap %d \n",hash_index);
	return NULL;
}
/* hremove -- removes and returns an entry under a designated key
 * using a designated search fn -- returns a pointer to the entry or
 * NULL if not found
 */
void *hremove(hashtable_t *htp,bool (*searchfn)(void* elementp, const void* searchkeyp),const char *key, int32_t keylen){
	int32_t hash_index  = SuperFastHash (key, keylen, htp->hsize);  //return ht%size
	kvnode_t *hnode;
	for (hnode=htp->first; hnode->key !=MAXREG-1; hnode=hnode->down){
		if (hnode->key==hash_index){
			if (hnode->q == NULL){
				printf("Element not found");
				return NULL;
			}else{
				person_t *person=(person_t*)qremove(hnode->q,searchfn,key);
				return person;
			}
		}
	}
	printf("Found element to hashmap %d \n",hash_index);
	
	return NULL;
}


////
