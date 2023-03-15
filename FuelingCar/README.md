# fueling_car_synchronization
## Problem Description
There are multiple number of cars heading towards the fueling station,there are multiple trucks to fill the fueling station.
They come in randomn order, According to the time of arrival of car, if the fuel is avaliable to full its tank,fueling is done or else the car goes into waiting state.
when there are multiple cars waiting there is the problem of synchronization.
<br>
We solve this using semaphores and threads in this solution.
<br>
## Problem_Solution
### Variables used:
- `n` refilling amount of fuel at once.
- `m` fuel required for the car to get filled.
- `Fuel` Amount of fuel present in the tank/station for now.
- We created 6 threads,in which two are for filling the fueling station and another four for cars.
- There are two fucntions `car_fueling` and `fuel_filling`
- We are using a semaphore adjust both execute exclusively as both filling and car fueling can't happen at once.
- In `car_fueling` fucntion we run a loop untill we get the atleast amount to fill the tank of car, and if it is not sufficient we call the fuel_filling fucntion to fill the station 
with the total truck capacity of fuel,which we can adjust in the given solution code,represented by n.
<br>
Variable `Fuel` helps us in knowing the current available fuel in the station and excute the functions accordingly.
This filling function is called using semaphore `condFuel`,which informs the cars that they can get fueled now.
<br>
Semaphore `mutexFuel` is used to allow only one car at a time to get feuled, in this way we can solve the synchronization problem without deadlock.

## SEMAPHORES
`mutexFuel`:Used to allow only one vehicle to the statiion, either the filling one or the car. <br>
`condFuel`:To check whether the available fuel is sufficient for the car fueling and signal the filling_fuel function for filling the station.
