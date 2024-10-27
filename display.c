/**
 * display.c - Main entry for processing and visualizing point cloud data.
 * 
 * Usage: ./display <filename>
 * 
 * Reads a file containing point cloud data, calculates statistics, 
 * and generates a grayscale image representing the height of each point.
 */
#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include "pointcloud.h"
#include "util.h"
#include "bmp.h"



int main(int argc, char *argv[])
{
    // check for correct usage
    if (argc < 2){
        printf("Usage: %s <filename>\n", argv[0]);
    }

    //open file and handle potential errors
    FILE *file = fopen(argv[1], "r");

    if (file == NULL){
        printf("Error, could not open file %s\n", argv[1]);
        return 1;
    }

    printf("Processing point cloud data from %s\n", argv[1]);
    
    //initialize list for point cloud data
    List* l = (List*)malloc(sizeof(List));
    listInit(l, sizeof(pcd_t));
    int width; 
    readPointCloudData(file, &width, l);

    //printf("width: %d\n", width);
    //stat1(l);
    
    //generate and save the image representation
    imagePointCloud(l, width, "./out.gif");
    
    //clean up allocated resources
    fclose(file);

    for (int i = 0; i < l->size; i++)
    {
        free ((pcd_t*)listGet(l, i));
    }
    free(l->data);
    free(l);

    return 0;
}