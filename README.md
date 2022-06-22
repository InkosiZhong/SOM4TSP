# SOM4TSP

This is a SOM implementation using **C Lib Functions** and **C++ Object Oriented Programming Style**

### Easy Start

1. Edit points data in main.cpp - initPoints()

2. ```bash
   g++ SOM.cpp main.cpp -I SOM.h -o SOM
   ```

3. ```bash
   ./SOM
   ```

### Use in your project

#### Class Point

a simple structure with attributes **x** and **y**

you can init by using **Point(X, Y)**

#### Class SOM

```c++
SOM som(NUM_OF_POINTS, PTR_POINT_LIST); // initialization
som.run(NUM_OF_ITERATIONS); 						// start iteration
som.getRoute();													// get the best route (readonly)
som.getRoute(PTR_ROUTE_LIST); 					// copy to new LIST (writable)
som.getDist();													// get min distance
```

