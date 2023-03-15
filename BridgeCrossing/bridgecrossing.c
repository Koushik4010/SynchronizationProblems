#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    int count;
    pthread_mutex_t lock;
    pthread_cond_t non_zero;
} semaphore_t;

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

enum side
{
    right = 0,
    left = 1
};

typedef struct 
{
    int id;                      //  tourist to be identified by id
    enum side dir;               // side at which the tourist started
    pthread_t tourist_thread_id; // thread to be created for the tourist 
} tourist;

semaphore_t sem[2];
int tourists_waiting[2];        // tourists waiting on each side at that time
int tourists_on_bridge[2];     // tourists crossing from each side at that time
pthread_mutex_t mutex;

void *crossing(tourist *new)
{
    int id = new->id;
    enum side dir = new->dir;
    int oppdir = !dir;
    if(dir==1){
      printf("tourist number %d is waiting at the left side to pass the bridge\n", id);}
    else{
      printf("tourist number %d is waiting at the right side to pass the bridge\n", id);
    }

    s_wait(&sem[dir]);

    pthread_mutex_lock(&mutex);
    tourists_waiting[dir]--;       // the tourist is on bridge now 
    tourists_on_bridge[dir]++;
    if(dir==1){
    printf("tourist number %d started on the bridge from left side\n", id);}
    else{
    printf("tourist number %d started on the bridge from right side\n", id);
    }
    pthread_mutex_unlock(&mutex);
    sleep(1);            // Let time taken to cross be 1 unit. 
    pthread_mutex_lock(&mutex);

    tourists_on_bridge[dir]--;
    if (tourists_on_bridge[dir] == 0) // All tourists crossed.
    {
        if (tourists_waiting[oppdir] > 0)
        {
            int i = tourists_waiting[oppdir]; 
            while (i--)
            {
                s_signal(&sem[oppdir]);       // signalling all tourists on other side to cross
            }
        }
        else if (tourists_waiting[dir] > 0)     // if there is no tourist on other side 
        {
            int i = tourists_waiting[dir];     // signal to tourists on the last crossed person's side
            while (i--)
            {
                s_signal(&sem[dir]);
            }
        }
    }
    if(dir==1){
    printf("tourist number %d reached the right side\n", id);}
    else{
    printf("tourist number %d reached the left side\n", id);
    }
    pthread_mutex_unlock(&mutex);
}

void *arrival(void *arg)
{
    tourist *new = (tourist *)arg;
    int id = new->id;
    enum side dir = new->dir;
    int oppdir = !dir;
    sleep(rand()%2);
    pthread_mutex_lock(&mutex);
    if (tourists_on_bridge[dir] >= 0 && tourists_waiting[dir] == 0 && tourists_on_bridge[oppdir] == 0 && tourists_waiting[oppdir] == 0)
    {
        s_signal(&sem[dir]);                 //Initially zeroes will be incremented according to which side the first tourist comes. 
    }
    tourists_waiting[dir]++;
    if(dir==1){
    printf("tourist number %d arrived at the left side\n", id);}
    else{
    printf("tourist number %d arrived at the right side\n", id);
    }
    pthread_mutex_unlock(&mutex);
    crossing(new);
    return NULL;
}

int main()
{
    pthread_mutex_init(&mutex, NULL);
    s_initialize(&(sem[0]), 0);          // Both semaphores initialized to zero.
    s_initialize(&(sem[1]), 0); 
    tourists_waiting[0]=0;          // All zeroes initially
    tourists_waiting[1]=0;
    tourists_on_bridge[0]=0;
    tourists_on_bridge[1]=0;
    int tourist_id = 0;          // to give unique id to each tourist
    int f;
    printf("Enter the number of rounds of tourists: ");
        scanf("%d", &f);
    while(f--){  
        int tt;                         // Total numbers of tourists
        printf("Enter the number of tourists: ");
        scanf("%d", &tt);
        tourist A[tt];
        for (int i = 0; i < tt; i++)
        {
          A[i].id = ++tourist_id; // tourist id incremented every time
          A[i].dir = rand()&1; // for random sides for tourists
        }
        for (int i = 0; i < tt; i++)
        {
          pthread_create(&(A[i].tourist_thread_id), NULL, arrival, &A[i]);
        }
        for (int i = 0; i < tt; i++)
        {
          pthread_join(A[i].tourist_thread_id, NULL);
        }
    }
    pthread_mutex_destroy(&mutex);
    s_destroy(&sem[0]);
    s_destroy(&sem[1]);
}
