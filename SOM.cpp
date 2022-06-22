#include "SOM.h"

double U(double min = 0, double max = 1){
    double val = double(rand()) / RAND_MAX;
    return val * (max - min) + min;
}

SOM::SOM(uint num, Point* points, uint k): 
    m_num(num), m_k(k), m_domain(m_num * m_k){
    m_points = (Point*)malloc(sizeof(Point) * m_num);
    memcpy(m_points, points, sizeof(Point) * m_num);
    m_route = (uint*)malloc(sizeof(uint) * m_num);
    computeDistMatrix();
}

void SOM::initWeight(){
    m_weight = (double*)malloc(sizeof(double) * m_domain * 2);
    for (uint i = 0; i < m_domain * 2; i++){
        m_weight[i] = U(0, 1);
    }
}

void SOM::computeDistMatrix(){
    m_distMatrix = (double*)malloc(sizeof(double) * m_num * m_num);
    for (uint i = 0; i < m_num; i++){
        m_distMatrix[i * m_num + i] = 0;
        for (uint j = i + 1; j < m_num; j++){
            m_distMatrix[i * m_num + j] = m_distMatrix[j * m_num + i] = \
                distanceOf(m_points[i], m_points[j]);
        }
    }
}

SOM::~SOM(){
    free(m_points);
    free(m_distMatrix);
    free(m_route);
}

double* SOM::getNeighbor(const int center, const int radix, double* gaussian){
    int realRadix = radix < 1 ? 1 : radix;
    for (uint i = 0; i < m_domain; i++){
        gaussian[i] = (center > i) ? center - i : i - center;
        double distance = m_domain - gaussian[i];
        if (gaussian[i] > distance) gaussian[i] = distance;
        gaussian[i] = -(gaussian[i] * gaussian[i]) / (2 * realRadix * realRadix);
        gaussian[i] = pow(E, gaussian[i]);
    }
    return gaussian;
}

double SOM::distanceOf(const Point& a, const Point& b) const{
    double dx = int(a.x - b.x);
    double dy = int(a.y - b.y);
    return pow(dx * dx + dy * dy, 0.5);
}

double SOM::distanceOf(uint idx, const Point& b) const {
    double dx = m_weight[idx] - b.x;
    double dy = m_weight[idx + m_domain] - b.y;
    return pow(dx * dx + dy * dy, 0.5);
}

uint SOM::closest(const Point& origin) const {
    double minDist = INF;
    uint minIdx = 0;
    for (uint i = 0; i < m_domain; i++){
        double dist = distanceOf(i, origin);
        if (dist < minDist){
            minDist = dist;
            minIdx = i;
        }
    }
    return minIdx;
}

double SOM::routeDistance(const uint* route) const {
    double dist = 0;
    for (uint i = 0; i < m_num - 1; i++){
        dist += m_distMatrix[route[i] * m_num + route[i + 1]];
    }
    dist += m_distMatrix[route[0] * m_num + route[m_num - 1]];
    return dist;
}

uint* SOM::computeRoute(const Point* points, uint* route, double* dists) const {
    for (uint i = 0; i < m_num; i++){
        dists[i] = closest(points[i]);
        route[i] = i;
    }
    for (uint i = 0; i < m_num; i++){
        for (uint j = i + 1; j < m_num; j++){
            if (dists[j] < dists[i]){
                double tmp = dists[i];
                dists[i] = dists[j];
                dists[j] = tmp;
                uint tmp_idx = route[i];
                route[i] = route[j];
                route[j] = tmp_idx;
            }
        }
    }
    return route;
}

uint* SOM::getRoute(uint* pt) const {
    memcpy(pt, m_route, sizeof(uint) * m_num);
    return pt;
}

const uint* SOM::getRoute() const {
    return m_route;
}

double SOM::getDist(){
    return m_dist;
}

void SOM::run(uint iter, double lr){
    Point* tmp_points = (Point*)malloc(sizeof(Point) * m_num);
    memcpy(tmp_points, m_points, sizeof(Point) * m_num);
    initWeight();
    uint* route = (uint*)malloc(sizeof(uint) * m_num);
    double* dists = (double*)malloc(sizeof(double) * m_num);
    double* gaussian = (double*)malloc(sizeof(double) * m_domain);
    double n = m_domain;
    m_dist = INF;
    for (uint cur_iter = 0; cur_iter < iter; cur_iter++){
        int idx = int(U(0, m_num));
        uint winner_idx = closest(m_points[idx]);
        gaussian = getNeighbor(winner_idx,  n / 10, gaussian);
        for (uint i = 0; i < m_domain; i++){
            m_weight[i] += gaussian[i] * lr * (m_points[idx].x - m_weight[i]);
            m_weight[i + m_domain] += gaussian[i] * lr * (m_points[idx].y - m_weight[i + m_domain]);
        }
        lr *= 0.99997;
        n *= 0.9997;
        if (n < 1)break;
        route = computeRoute(tmp_points, route, dists);
        double dist = routeDistance(route);
        if (dist < m_dist){
            m_dist = dist;
            memcpy(m_route, route, sizeof(uint) * m_num);
        }
    }
    free(tmp_points);
    free(route);
    free(dists);
    free(gaussian);
}