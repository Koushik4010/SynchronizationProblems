# Problem Statement

Bridge Crossing Problem where there are two hills and bridge in middle and tourists on both hills. Our goal is to implement a code to make sure that tourists from both sides do not collide on the bridge.

# Solution
The implementation of the scenario using pthreads can be done by using various semaphores and variables. They are,               
**Global Variables:**  
An Array of 2 elements,`tourists_waiting`, representing tourists waiting on each hill.  
An Array of 2 elements,`tourists_on_bridge`, representing tourists from each hill on the bridge.  
**Semaphores:**  
An array of semaphores,`sem`,representing two semaphores that regulate the flow of tourists onto the bridge.  
**The Tourist:**  
Every tourist is structured with an integer id, the hill he will be on and a unique thread he will produce.  
**Other variables:**. 
An integer `tt` representing the total number of tourists that can be given as input.
