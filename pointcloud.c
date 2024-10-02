// Author Thomas Olson - olsoto@iastate.edu
#include <stdio.h>
#include <float.h>
#include "pointcloud.h"

/* stat1(FILE *file)
    takes an open file pointer with point cloud data (doubles x,y,height)
    prints the minimum and maximum heights with their coordinates and
    the average height of all the points
    iterates through the file, updating minimum and maximum heights with their
    coordinates while summing up the heights to calculate the average
*/
void stat1(FILE *file)
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
    
    
    while (fscanf(file, "%lf %lf %lf", &x, &y, &h) == 3){
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
    stat1(file);
    fclose(file);

    return 0;
}