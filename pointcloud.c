// Author Thomas Olson - olsoto@iastate.edu
/**
 * pointcloud.c - Core functionalities for processing and visualizing point cloud data.
 * 
 * Functions:
 * - imagePointCloud: Generates an image file visualizing point cloud data.
 * - readPointCloudData: Reads point cloud data from a file.
 * - stat1: Calculates minimum, maximum, and average heights in the point cloud.
 */

#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include "pointcloud.h"
#include "util.h"
#include "bmp.h"



/**
 * imagePointCloud - Creates a grayscale image representing point cloud height.
 * @param l: Pointer to the List containing point cloud data.
 * @param width: The width of the generated image.
 * @param filename: Name of the output image file.
 */
void imagePointCloud(List* l, int width, char* filename)
{
    if (l==NULL){
        printf("LIST FAILED");
        return;
    }

    double heightPair[2];
    stat1(l, heightPair);
    // printf("%lf\n", heightPair[1]);
    // printf("%lf\n", heightPair[0]);

    double range = heightPair[1] - heightPair[0];

    // printf("%lf\n", range);

    if (range == 0){
        range = 1;
    }

    //int lengths = (int)(range / 256);
    int height = l->size / width;
    if (l->size % width != 0){
        height++;
    }
    //Bitmap* bitmap = malloc(sizeof(bitmap));
    Bitmap *bitmap = bm_create(width, height);

   
    if (!bitmap){
        printf("BITMAP MALLOC FAILED");
        return;
    }
    
    double rgb;
    unsigned int color = 0x0;

    int x = 0;
    int y = 0;

    //map each point's height to grayscale and plot on bitmap
    for (int i = 0; i < l->size; i++)
    {
        pcd_t* point = (pcd_t*)listGet(l, i);

        rgb = ((point->z - heightPair[0]) / range)*255.0;

        if (rgb < 0) {
            rgb = 0;
        } else if (rgb > 255) {
            rgb = 255;
        }

        color = (0xFF000000) | ((int)rgb << 16) | ((int)rgb << 8) | ((int)rgb);

        bm_set_color(bitmap, color);
    //printf("Point %d: x=%f, y=%f, z=%f, rgb=%f\n", i, point->x, point->y, point->z, rgb);

        bm_putpixel(bitmap, x, y);
        x++;
        if (x >= width)
        {
            y++;
            x=0;
            
        }
        //printf("x:%d y:%d\n", x, y);
        
    }
    bm_save(bitmap, filename);
    bm_free(bitmap);
    

    //printf("min %lf max %lf\n", heightPair[0], heightPair[1]);
}


/**
 * readPointCloudData - Reads point cloud data from a file and stores it in a List.
 * @param stream: File stream to read from.
 * @param rasterWidth: Pointer to an int storing raster width.
 * @param list: Pointer to List to store read points.
 */

void readPointCloudData(FILE *stream, int *rasterWidth, List* list)
{
    if (!stream){
        fprintf(stderr, "No stream to read");
        return;
    }


    
    fscanf(stream, "%d", rasterWidth);

        double x;
        double y;
        double h;
        pcd_t point;
    
    while (fscanf(stream, "%lf %lf %lf", &x, &y, &h) == 3){

            
            //pcd_t* point = malloc(sizeof(pcd_t));
            point.x = x;
            point.y = y;
            point.z = h;
            // printf("%lf %lf %lf", point->x, point->y, point->z);
            // printf("\n");

            point.water_amt = 0;
            // point->north->NULL;
            // point->east->NULL;
            // point->south->NULL;
            // point->west->NULL;
            listAddEnd(list, &point);
    }

    // for (int i = 0; i < columns; i++)
    // {
    //     pcd_t* point = *(pcd_t**)listGet(list, i);

    //    //printf("%lf %lf %lf\n", point->x, point->y, point->z);
    // }


    //return (void*)list;
}

/* stat1(FILE *file)
    takes an open file pointer with point cloud data (doubles x,y,height)
    prints the minimum and maximum heights with their coordinates and
    the average height of all the points
    iterates through the file, updating minimum and maximum heights with their
    coordinates while summing up the heights to calculate the average
*/

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
        pcd_t* point = (pcd_t*)listGet(l, i);
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

