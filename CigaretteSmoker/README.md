# CigaretteSmokerProblem
## Problem Statement
Implement CigaretteSmoker problem using ***pthreads***.(multiple smokers)
## Solution
- Cigarette smokers problem is a concurrency problem in which there are three smokers and one agent.Where,initially each smoker is provided with infinite supply of each item(i.e,tobacco,paper or matches) and the agent is provided with infinite supply of all the three items.
- In this problem we have created three threads each for the three smokers.A random number j is used to prioritize the smokers avoiding deadlock situation.Signal will be sent to agent after the completion of smoking of each and every smoker.
- When the agent is waiting ,according to j the next smoker will send signals and start smoking.The smoker with tobacco have to pick paper and matche,the smoker with paper have to pick tobacco and matche, and the smoker with matches have to pick paper ana tobacco.

### **Semaphore used:**
1. `tobac` binary semapohore used for the process of smoker with infinite supply of tobacco.
2. `pape` binary semaphore used for the process of smoker with infinite supply of paper.
3. `match` binary semaphore used for the process of smoker with infinite supply of matches.
4. `agent` binary semaphore used to manage the state of agent.
