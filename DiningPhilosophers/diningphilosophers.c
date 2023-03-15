#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#define no_of_phi 5
int chop_sticks[no_of_phi];

void semwait(int *s){
    while((*s)<=0);
    (*s)--;
}
void semsignal(int *s){
(*s)++;
}
void * philosoher(void *bn){
    sleep(0.1);
    int i=(int)bn;
    int k=0,j=1;
    while(k<j){
        // Thinking;
        semwait(&chop_sticks[i]);
        semwait(&chop_sticks[(i+1)%no_of_phi]);
        //C.S
        printf("philoshore %d started eating \n",i);
        sleep(1);
        printf("philoshore %d completed eating \n",i);

        semsignal(&chop_sticks[i]);
        semsignal(&chop_sticks[(i+1)%no_of_phi]);

        k++;
    }
    return NULL;

}

void * reverse_philosophoer(void *bn){
    int last_phi=(int)bn;
    int k=0,j=1;
    while(k<j){
        // Thinking();
        semwait(&chop_sticks[(last_phi+1)%5]);
        semwait(&chop_sticks[last_phi]);
        // Eat();
        //C.S
        printf("philoshore %d started eating \n",last_phi);
        sleep(1);
        printf("philoshore %d completed eating \n",last_phi);

        semsignal(&chop_sticks[last_phi]);
        semsignal(&chop_sticks[(last_phi+1)%5]);
        k++;
    }
    return NULL;

}


int main(){
    for(int i=0;i<no_of_phi;i++){
       chop_sticks[i]=1;
    }
    pthread_t p[no_of_phi];
    for(int i=0;i<no_of_phi-1;i++){
        pthread_create(&p[i],NULL,&philosoher,(void*)i);
    }
    pthread_create(&p[no_of_phi-1],NULL,&reverse_philosophoer,(void*)(no_of_phi-1));

    for(int i=0;i<no_of_phi;i++){
        pthread_join(p[i],NULL);
    }

    return 0;
}
