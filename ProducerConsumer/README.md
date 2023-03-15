# ProducerConsumerProblem
## Problem Statement
Implement ProducerConsumer problem using ***pthreads***.(multiple producers, multiple consumers)
   - Bounded Buffer
   - Cyclic Buffer
   - Infinite Buffer 
## Solution
### **Bounded Buffer**
- Equal number of producer and consumer threads are created using pthreads library and the        functions of producers and consumers are passed correspondingly and then later these threads are joined to the main threads.
- Semaphore functions are created explicitly instead of using the library. These semaphores are used to ensure the empty and full slots before proceeding to the critical section for avoiding the errors.
   - **Semaphore used:**
   >* semphore `"full"` used to check number of full slots in the buffer, intialised to 0.
   >* semaphore `"empty"` used to check the number of empty slots in the buffer, intialized to BUFFER_SIZE.
- A ***random function*** is used to produce a random number by the producer and it is placed inside the buffer which is of fixed length. Here Buffer is created using array.
- Every producer and consumer thread is limited to produce or consume only a finite number of numbers to terminate the program in finite time.

### **Cyclic Buffer**
- It is same as bounded buffer but the only change is we used mod operator to explicitly keep on inserting the produced elements into the buffer in a cyclic manner.
- Semaphore usage initialization is same as the bounded buffer problem

### **Infinite Buffer**
- For implementing the infinite buffer we have used ***linked list*** so that we keep on inserting the produced elements and consume them without and limitation.
- Here insertion is done at the end and deletion at the front so that the elements are consumed in the order of their arrival.
- Also there is no need for the semaphore empty because it is infinite buffer.
   - **Semaphore used:**
   >* semphore `"full"` used to check number of full slots in the buffer, intialised to 0.
   

