#include "SOM.h"
#include <ctime>
#define MAX_POINTS 20

Point points[20];

void initPoints(){
    points[0] = Point(64, 96);
    points[1] = Point(80, 39);
    points[2] = Point(69, 23);
    points[3] = Point(72, 42);
    points[4] = Point(48, 67);
    points[5] = Point(58, 43);
    points[6] = Point(81, 34);
    points[7] = Point(79, 17);
    points[8] = Point(30, 23);
    points[9] = Point(42, 67);
    points[10] = Point(7, 76);
    points[11] = Point(29, 51);
    points[12] = Point(78, 92);
    points[13] = Point(64, 8);
    points[14] = Point(95, 57);
    points[15] = Point(57, 91);
    points[16] = Point(40, 35);
    points[17] = Point(68, 40);
    points[18] = Point(92, 34);
    points[19] = Point(62, 1);
}

int main(){
    initPoints();
    clock_t t = clock();
    SOM som(MAX_POINTS, points);
    printf("%lfs\n", double(clock() - t) / CLOCKS_PER_SEC);
    som.run(500);
    printf("%lfs\n", double(clock() - t) / CLOCKS_PER_SEC);
    for (uint i = 0; i < MAX_POINTS; i++){
        printf("%d ", som.getRoute()[i]);
    }
    printf("\n%lf\n", som.getDist());
    return 0;
}