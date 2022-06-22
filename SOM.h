#ifndef SOM_H
#define SOM_H

#define INF 1e9
#define E 2.7182818284

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

typedef unsigned int uint;

class Point{
public:
    Point(){}
    Point(uint _x, uint _y) { x = _x; y = _y; }
    uint x, y;
};

class SOM{
public:
    SOM(uint num, Point* points, uint k = 8);

    ~SOM();

    uint* getRoute(uint* pt) const;

    const uint* getRoute() const;

    double getDist();

    void run(uint iter = 8000, double lr = 0.8);

private:
    double* getNeighbor(const int center, const int radix, double* gaussian);

    double distanceOf(const Point& a, const Point& b) const;

    double distanceOf(uint idx, const Point& b) const;

    uint closest(const Point& origin) const;

    double routeDistance(const uint* route) const;

    uint* computeRoute(const Point* points, uint* route, double* dists) const;

    void initWeight();

    void computeDistMatrix();

public:
    const uint m_k;
    const uint m_num;
    const uint m_domain;
    Point* m_points;
    double* m_distMatrix;
    uint* m_route;
    double m_dist;
    double* m_weight;
};

#endif