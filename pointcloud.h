#ifndef POINTCLOUD_H
#define POINTCLOUD_H
#include "util.h"
#include "bmp.h"

#include <stdio.h>

//prototype for the stat1 function from the pointcloud.c file
void stat1(List* list, double pair[2]);
void readPointCloudData(FILE *stream, int *rasterWidth, List* pc);


void imagePointCloud(List* l, int width, char* filename);

typedef struct pcd pcd_t;

typedef struct pcd{
    double x;
    double y;
    double z; //height
    double water_amt;
    struct pcd* north;
    struct pcd* south;
    struct pcd* east;
    struct pcd* west;
}pcd_t;


#endif