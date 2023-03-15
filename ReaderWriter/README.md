# STARVE-FREE-READERS-AND-WRITERS-PROBLEM
# Problem Description
The readers and writers problem is a  synchronization problem where reading an dwriting done at the same location. Readers tries to read and riter tries to write in the same memory location or common resource.In First Readers-Writer problem Writer starve and Second Readers and writer problem Reader strave .Write Pseudo code for starve free  solutions using semaphores.
# Proposed solution (INTUITION)
Here I allocate the shared resources to Reader or Writer based on First Come First Serve basis.If the resources are already been allocated to some one then we block the process .To maintain the order of the process in the waiting list we maintain a `Queue(FIFO-QUEUE)` .We have the constraint of mutual exclusion is that writer and reader cannot share the common resources simultaneously so as th handle this I used `“cs_mutex”` semaphore.
### **During reading:**
When a resource is in the reader access we can allow other immediate reader to read the file simultaneously .I maintained the count `(“readcount”)` .I used a semaphore `“read_ct”` to allow a single reader to update the value of read_count for not to go in race condition(or to maintain mutual exclusion) . 
I used another semaphore `“execute”`  which a process in queue to execute in an order .The fist reader while entering takes the access of the shared resources for all . 
### **During Writing:**
Here we are not allowed two or more writer to write in the same memory location because they are updating something In the shared resources, we handle this by using semaphore at write place.

# Semaphores
1. semphore `"execute"` is for the process to execute in the order of arrival and i used this semaphore to signal other process to start after its execution.
2. semaphore  `"cs_mutex"` is used to maintain mutual exlusion between reader-writers and writer-writer.
3. semphore ``"read_ct"`` is used for updation od read_count to not to go for a race condition.


# Conclusion
`Mutual Exclusion` :I used semaphore named “cs_mutex” which allow either writer or reader to process simultaneously in the critical section, which implies reader and writer are mutually excluded.<br>
`Bounded waiting` :Here each process will get a chance of progress at some time because of FIFO queue order implementation not the priority.<br>
`Deadlock` : Here there will be no chance of deadlock as it have no cyclic requests ,mutually excluded,Bounded waiting etc.<br>
`Starve free` : I applied FIFO QUEUE which executes the process as in the order of arrival .Each process run in a finite time and exits from the critical section .Here every process will get chance without starvation.<br>
