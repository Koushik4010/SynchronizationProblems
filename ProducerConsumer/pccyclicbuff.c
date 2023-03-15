#include <stdio.h>
#define ll long long
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    int count;
    pthread_mutex_t lock;
    pthread_cond_t non_zero;
} semaphore_t;

ll buffer[10];
ll n=10;
semaphore_t empty;
semaphore_t full;
ll c=0;
ll in=0;
ll out=0;
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


void *produce(void * arg){
	int t=*((int *)arg);
	ll j=5;
	ll i=0;
	while(i<j){
		int x=rand()%100; //random number is produced 
		i++;
        //sleep(0.05);
		s_wait(&empty);
		pthread_mutex_lock(&mutex);

		buffer[in]=x;   // produced number is inserted in the buffer 
		printf("%d  produced by producer thread #%d \n",x,*((int *)arg));
		in=(in+1)%n;

		pthread_mutex_unlock(&mutex);
		s_signal(&full);
	}
	return NULL;
}

void *consume(void *arg){int t=*((int * )arg);
	ll j=5;ll i=0;
	while(i<j){
		i++;
		s_wait(&full);
		pthread_mutex_lock(&mutex);

		int y=buffer[out]; //Number is taken out of the buffer and consumed
		out=(out+1)%n;

		pthread_mutex_unlock(&mutex);
		s_signal(&empty);
		printf("%d  consumed by consumer thread #%d \n",y,*((int *)arg));
        sleep(0.05);
	}
	return NULL;
}


int main() {
	pthread_t producer[5];
	pthread_t consumer[5];
    pthread_mutex_init(&mutex, NULL);
    s_initialize(&empty,n);
    s_initialize(&full,0);
    ll q[5]={1,2,3,4,5};
	for(ll i=0;i<5;i++){
		pthread_create(&producer[i],NULL,produce,(void *)&q[i]); 	
		sleep(0.05);
    }
	for(ll i=0;i<5;i++){
		pthread_create(&consumer[i],NULL,consume,(void *)&q[i]);
		sleep(0.05);
	}

	for(ll i=0;i<5;i++){
		pthread_join(producer[i],NULL);	
	}
	for(ll i=0;i<5;i++){
		pthread_join(consumer[i],NULL);	
	}

    pthread_mutex_destroy(&mutex);
    s_destroy(&empty);
    s_destroy(&full);
	return 0;
}
