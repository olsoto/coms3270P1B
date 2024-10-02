#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include <stdio.h>

//prototype for the stat1 function from the pointcloud.c file
void stat1(FILE* file);

typedef struct pcd{
    double x;
    double y;
    double z; //height
    double water_amt;
    pcd* north;
    pcd* south;
    pcd* east;
    pcd* west;
}pcd_t;


#endif