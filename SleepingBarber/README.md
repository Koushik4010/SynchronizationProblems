# Sleeping-barbers-problem
## Problem statement:
The Sleeping Barber problem is a classic synchronization problem that involves multiple barbers and multiple customers. The problem assumes a barbershop with a certain number of chairs for customers to wait in, and a certain number of barbers who can cut hair at the same time. Customers arrive randomly and either sit in a chair if one is available or leave if all chairs are occupied. If a barber is available, they begin cutting the hair of a customer. If all barbers are busy, customers must wait in their chairs until a barber becomes available.

The challenge in this problem is to synchronize the access to shared resources (chairs and barbers) and to prevent race conditions where two customers might try to sit in the same chair, or two barbers might try to cut the hair of the same customer. Additionally, the solution must ensure that the barbers only cut hair when there is a customer in the chair.

## Solution


**Global Variables:** <br>
number of barbers = n_brbs <br>
number of customers=n_cust <br>
number of waiting seats=wtsts

### Semaphore initialisation and usage
1. For mutual exclusion between waiting seats of entering customers we have used `m_wtsts` binary semaphore initialized to 1. <br>
2. For mutual exclusion between barbers we used `m_brbs` initialized to 1. <br>
3. For mutual exclusion between the un-served customers(customers who exited the shop with out the job has done) we used `m_unser` initialised to 1. <br>
4. To keep track of the number of ready barbers we used `rdb`(counting sem) initialized to 0. <br>
5. `brb[n_brbs]`is the array of semaphores which are used such that whenever customer signals it then barber starts doing haircut. They are initialized to "0" so that barbers are blocked initially. <br>

Initially, all the barber threads are created. Each thread is given an ID number and calls the function **"barber_f"**. **is_slp[ID] = 1** is set for all the barber ID's such that initially every barber is sleeping,also semaphore(rdb) is signaled.
Now,when the Customer threads are created each thread calls **"customer_f"** function and checks the no.of empty seats. If the empty seats are "0" then the customer leaves the shop by incrementing unserved customers(m_unser sem is used for mutual exclusion between unserved customers). Else he will enter the shop and sit and check for the ready barbers(barbers who are sleeping). If there are ready barbers  then the customer need to select the first ready barber (which is implemented using a for loop) and signal the brb[i] semaphore so that the particular barber cut the hair of the customer who woke him up.
Finally, we print the corresponding ID numbers of the barber and the customer where the haircut is done.

