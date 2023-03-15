# Dining-Philosphers-Problem
# Problem Statement
The Dining Philosophers problem is a classic synchronization problem in computer science where multiple processes compete for limited resources without causing a deadlock or a starvation. Specifically, the problem involves a group of philosophers who alternate between thinking and eating. They sit around a circular table with a bowl of rice in front of each philosopher and a single chopstick between each pair of adjacent philosophers.
# Intuition
intially all philosphers will take left chopstick first and right chopstick next but last philospher will take right chopstick first left chopstick next by this way we can avoid starvation and deadlock
# Semaphore initialization
 chop_sticks[no_of_phi]  Semaphore array is declared which are intialized to one
# Solution
1. Intialization of semaphore array of length equal to number of chopsticks
2. We create a function which is called by first n-1 philospher threads in which they first pick up left chopsticks and then right chopstick and after completion of eating they put back chopsticks down in same order left first and right next
// Thinking;

        semwait(&chop_sticks[i]);
        
        semwait(&chop_sticks[(i+1)%no_of_phi]);
        
        //C.S
        printf("philoshore %d started eating \n",i);
        sleep(1);
        printf("philoshore %d completed eating \n",i);
        semsignal(&chop_sticks[i]);
        semsignal(&chop_sticks[(i+1)%no_of_phi]);
3. We create another function which is typically opposite the function we created earlier which is called by last philospher thread in which he/she first pick up right chopstick and then right chopstick and after completion of eating he would put back them in same order
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
        
 By this way we can avoid deadlock and starvation       

