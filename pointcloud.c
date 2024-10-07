// Author Thomas Olson - olsoto@iastate.edu
#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include "pointcloud.h"
#include "util.h"
#include "bmp.h"

/* stat1(FILE *file)
    takes an open file pointer with point cloud data (doubles x,y,height)
    prints the minimum and maximum heights with their coordinates and
    the average height of all the points
    iterates through the file, updating minimum and maximum heights with their
    coordinates while summing up the heights to calculate the average
*/

void imagePointCloud(List* l, int width, char* filename)
{
    if (l==NULL){
        printf("LIST FAILED");
        return;
    }

    double heightPair[2];
    stat1(l, heightPair);

    double range = heightPair[1] - heightPair[0];
    //int lengths = (int)(range / 256);
    int height = l->size/width;
    //Bitmap* bitmap = malloc(sizeof(bitmap));
    Bitmap *bitmap = bm_create(width, height);

   
    if (!bitmap){
        printf("BITMAP FAILED");
        return;
    }
    
    double rgb;
    unsigned int color = 0x0;

    int x = 0;
    int y = 0;

    for (int i = 0; i < l->size; i++)
    {
        pcd_t* point = *(pcd_t**)listGet(l, i);

        rgb = ((point->z - heightPair[0]) / range)*256.0;
        color = (0xFF000000) | ((int)rgb << 16) | ((int)rgb << 8) | ((int)rgb);

        bm_set_color(bitmap, color);

        if (x < width){
            bm_putpixel(bitmap, x, y);
        }else if (x >= width)
        {
            y++;
            x=0;
            bm_putpixel(bitmap, x, y);
        }
        //printf("x:%d y:%d\n", x, y);
        x++;
    }
    bm_save(bitmap, filename);
    bm_free(bitmap);
    

    //printf("min %lf max %lf\n", heightPair[0], heightPair[1]);
}

void readPointCloudData(FILE *stream, int *rasterWidth, List* list)
{
    listInit(list, sizeof(pcd_t));
    int columns;
    fscanf(stream, "%d", &columns);
    *rasterWidth = columns;
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

       //printf("%lf %lf %lf\n", point->x, point->y, point->z);
    }


    //return (void*)list;
}

void stat1(List* l, double pair[2])
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
    pair[0] = minHeight;
    pair[1] = maxHeight;
    
    
    printf("Minimum Height: %lf at coordinates %lf, %lf\n", minHeight, minCoords[0], minCoords[1]);
    printf("Maximum Height: %lf at coordinates %lf, %lf\n", maxHeight, maxCoords[0], maxCoords[1]);
    printf("Average Height of all the points: %lf\n", averageHeight);
    //printf("Data: %lf %lf %lf", x, y, h);
}
/* int main(int argc, char *argv[])
        handles command line input for the file name, opens the file,
        and calls the stat1 function
*/

