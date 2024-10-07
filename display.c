#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include "pointcloud.h"
#include "util.h"
#include "bmp.h"



int main(int argc, char *argv[])
{
    if (argc < 2){
        printf("Usage: %s <filename>\n", argv[0]);
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL){
        printf("Error, could not open file %s\n", argv[1]);
        return 1;
    }

    printf("Processing point cloud data from %s\n", argv[1]);
    
    List* l = (List*)malloc(sizeof(List));
    int width; 
    readPointCloudData(file, &width, l);

    //printf("width: %d\n", width);
    //stat1(l);
    
    imagePointCloud(l, width, "./out.gif");
    

    fclose(file);

    for (int i = 0; i < l->size; i++)
    {
        free ((pcd_t*)listGet(l, i));
    }
    free(l->data);
    free(l);

    return 0;
}