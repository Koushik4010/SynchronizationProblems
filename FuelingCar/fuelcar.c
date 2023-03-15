#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
int n=30;
int m=40;
pthread_mutex_t mutexFuel; //to control the action ie either fueling the tank or filling the tank at a time
pthread_mutex_t condFuel; // to check whether the fuel in the tank is suffice to fill the tank of car. and gives signal
int fuel = 0; //amt of fuel in the tank

void* fuel_filling(void* arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutexFuel);
        fuel=fuel+n;
        printf("Filled fuel... %d\n", fuel);
        pthread_mutex_unlock(&mutexFuel);
        pthread_mutex_unlock(&condFuel);
        sleep(1);
    }
}

void* fueling_car(void* arg) {
    pthread_mutex_lock(&mutexFuel);
    // the car waits in the loop untill the required fuel is achieved
    while (fuel < m) {
        printf("No fuel.car is Waiting...\n");
        pthread_mutex_unlock(&mutexFuel);
        pthread_mutex_lock(&condFuel);
        // wait for signal on condFuel
        pthread_mutex_lock(&mutexFuel);
    }
    fuel=fuel-m;
    printf("car tank filled remaining fuel left in tank: %d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);
}

int main() {
    pthread_t thread[6];
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_mutex_init(&condFuel, NULL);
    for (int i = 0; i < 6; i++) {
        if (i == 0 || i == 1) {
            pthread_create(&thread[i], NULL, &fuel_filling, NULL);
            }
        else {
            pthread_create(&thread[i], NULL, &fueling_car, NULL);
            }
        }

    for (int i = 0; i < 6; i++) {
        pthread_join(thread[i], NULL);
    }
    pthread_mutex_destroy(&mutexFuel);
    pthread_mutex_destroy(&condFuel);
    return 0;
}
