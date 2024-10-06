// Author Thomas Olson - olsoto@iastate.edu
#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include "pointcloud.h"
#include "util.h"

/* stat1(FILE *file)
    takes an open file pointer with point cloud data (doubles x,y,height)
    prints the minimum and maximum heights with their coordinates and
    the average height of all the points
    iterates through the file, updating minimum and maximum heights with their
    coordinates while summing up the heights to calculate the average
*/
void* readPointCloudData(FILE *stream)
{
    List* list = (List*)malloc(sizeof(List));
    listInit(list, sizeof(pcd_t));
    int columns;
    fscanf(stream, "%d", &columns);
    for (int i = 0; i < columns; i++){
            double x;
            double y;
            double h;
            fscanf(stream, "%lf %lf %lf", &x, &y, &h);
            pcd_t* point = malloc(sizeof(pcd_t));
            point->x = x;
            point->y = y;
            point->z = h;
            // printf("%lf %lf %lf", point->x, point->y, point->z);
            // printf("\n");

            point->water_amt = 0;
            // point->north->NULL;
            // point->east->NULL;
            // point->south->NULL;
            // point->west->NULL;
            listAddEnd(list, point);
    }

    for (int i = 0; i < columns; i++)
    {
        pcd_t* point = *(pcd_t**)listGet(list, i);

       printf("%lf %lf %lf\n", point->x, point->y, point->z);
    }


    return (void*)list;
}

void stat1(List* l)
{

    double x;
    double y;
    double h;
    double minHeight = DBL_MAX;
    double maxHeight = -DBL_MAX;
    double minCoords [2];
    double maxCoords [2];
    double totalHeight = 0.0;
    int count = 0;
    
    
    for (int i = 0; i < l->size ; i++)
    {
        pcd_t* point = *(pcd_t**)listGet(l, i);
        h = point->z;
        x = point->x;
        y = point->y;
        if (h < minHeight){
            minHeight = h;
            minCoords[0] = x;
            minCoords[1] = y;
        }
        if (h > maxHeight){
            maxHeight = h;
            maxCoords[0] = x;
            maxCoords[1] = y;
        }
        totalHeight += h;
        count++;
    }

    double averageHeight = (count > 0)?(totalHeight/count):0;
    
    printf("Minimum Height: %lf at coordinates %lf, %lf\n", minHeight, minCoords[0], minCoords[1]);
    printf("Maximum Height: %lf at coordinates %lf, %lf\n", maxHeight, maxCoords[0], maxCoords[1]);
    printf("Average Height of all the points: %lf\n", averageHeight);
    //printf("Data: %lf %lf %lf", x, y, h);
}
/* int main(int argc, char *argv[])
        handles command line input for the file name, opens the file,
        and calls the stat1 function
*/

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
    
    List* l = (List*)readPointCloudData(file);

    stat1(l);

    fclose(file);

    for (int i = 0; i < l->size; i++)
    {
        free ((pcd_t*)listGet(l, i));
    }
    free(l->data);
    free(l);

    return 0;
}