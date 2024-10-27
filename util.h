// util.h - header file for utility functions and List structure
#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

#define INDEX (row, column, num_cols) ((row*num_cols) + column)

void *allocateArray(int rows, int columns);

typedef struct
{
    int max_size; //current maximum possible size of list
    int max_element_size; //max size of any element in the array
    void* data; //pointer to current array containing data
    int size; //current number of elements in the list
} List;

int listInit(List* l, int max_elmt_size); 
void listAddEnd(List* l, void* elmt);
void *listGet(List* l, int index);

#endif