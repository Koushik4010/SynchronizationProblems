#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define n_barb 4  //No.of barbers
#define n_cust 20 //No.of customers
#define wtsts 10  //No.of waiting seats

typedef struct {
    int count;
    pthread_mutex_t lock;
    pthread_cond_t non_zero;
} semaphore_t;

pthread_mutex_t mutex;

void s_initialize(semaphore_t *s, int count) {
    s->count = count;
    pthread_mutex_init(&s->lock, NULL);
    pthread_cond_init(&s->non_zero, NULL);
}

void s_wait(semaphore_t *s) {
    pthread_mutex_lock(&s->lock);
    while (s->count == 0) {
        pthread_cond_wait(&s->non_zero, &s->lock);
    }
    s->count--;
    pthread_mutex_unlock(&s->lock);
}

void s_signal(semaphore_t *s) {
    pthread_mutex_lock(&s->lock);
    s->count++;
    pthread_cond_signal(&s->non_zero);
    pthread_mutex_unlock(&s->lock);
}

void s_destroy(semaphore_t *s) {
    pthread_mutex_destroy(&s->lock);
    pthread_cond_destroy(&s->non_zero);
}

semaphore_t brb[n_barb];
int is_slp[n_barb];
semaphore_t m_wtsts;
semaphore_t m_brbs;
semaphore_t rdb;
semaphore_t m_unser;
int slping_bs;
int emp_wts=wtsts;
int unserv=0;
void * barber_f(void *bn){
    int ID=(int)bn;
    while(1){
        s_wait(&m_brbs);
         is_slp[ID]=1;
         slping_bs++;
        s_signal(&rdb);
        s_signal(&m_brbs);
        s_wait(&brb[ID]);  
        //cut hair of the customer who woke him up
        sleep(3); //haircut takes some time
    }

}
void * customer_f(void *cn){
    int ID=(int)cn;
    s_wait(&m_wtsts); // entering customers synchronisation
     if(emp_wts==0){
         s_signal(&m_wtsts); 
            //leave the shop/
        s_wait(&m_unser);
         unserv++;  // synro btm unserved cust
        s_signal(&m_unser); 
     }
     else{
        emp_wts--;
        s_signal(&m_wtsts); 


        s_wait(&rdb);
         s_wait(&m_wtsts); 
          emp_wts++;
         s_signal(&m_wtsts);
         s_wait(&m_brbs); //mutual exclusion btw barbers
          int i=0;
           for(i=0;i<n_barb;i++){
            if(is_slp[i]==1){
                //wake him up
                is_slp[i]=0;   
                slping_bs--;
                s_signal(&brb[i]);  
                break;

             }
           }
         s_signal(&m_brbs);
         printf("customer %d is getting haircut from barber %d\n",ID,i);
     }
}

int main(){
    s_initialize(&m_wtsts,1);
    s_initialize(&m_brbs,1);
    s_initialize(&m_unser,1);
    s_initialize(&rdb,0);
    for(int i=0;i<n_barb;i++){
        s_initialize(&brb[i],0);
    }
    pthread_t barber[n_barb];
    pthread_t customer[n_cust];
    for(int i=0;i<n_barb;i++){
        pthread_create(&barber[i],NULL,&barber_f,(void*)i);
    }
    for(int i=0;i<n_cust;i++){
         sleep(0.01);
        pthread_create(&customer[i],NULL,&customer_f,(void*)i);
    }
    
    for(int i=0;i<n_cust;i++){
        pthread_join(customer[i],NULL);
    }
     
    printf("No.of Unserverd customers : %d\n",unserv);

    pthread_mutex_destroy(&mutex);
    s_destroy(&brb[n_barb]);
    s_destroy(&m_wtsts);
    s_destroy(&m_brbs);
    s_destroy(&rdb);
    s_destroy(&m_unser);

    return 0;
}

