#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

void *allocateArray(int rows, int columns){
    double* array = (double*)calloc(rows*columns, sizeof(double));

    return (void*)array;
}

int listInit(List* l, int max_elmt_size)
{
    l->max_size = 10;
    l->max_element_size = max_elmt_size;
    l->data = malloc(l->max_size * max_elmt_size);
    if (l->data == NULL)
    {
        fprintf(stderr, "Memory allocation failure");
        return -1;
    }
    l->size = 0;
    return 0;
}

/*
typedef struct
{
    int max_size; //current maximum possible size of list
    int max_element_size; //max size of any element in the array
    void* data; //pointer to current array containing data
    int size; //current number of elements in the list
} List;

*/

void listAddEnd(List* l, void* elmt)
{
    if (l->size == l->max_size){
        l->max_size *= 2;
        l->data = realloc(l->data, l->max_size * l->max_element_size);
        if (l->data == NULL){
            fprintf(stderr, "Memory reallocation failure");
            return;
        }
    }
    void* destination = (char*)l->data + (l->size * l->max_element_size);

    //destination = elmt;

    memcpy(destination, &elmt, l->max_element_size);

    l->size++;

    //l->(void*)(data+(size * max_element_size))->elmt;
}

void *listGet(List* l, int index)
{
    if (index < 0 || index >= l->size)
    {
        fprintf(stderr, "Index out of bound in listGet function.");
        return NULL;
    }

    void* address = (char*)l->data + (index * l->max_element_size);
    return address;
}


int main(int argc, char *argv[])
{
    List* list = (List*)malloc(sizeof(List));
    listInit(list, sizeof(int));

    for (int i = 1; i <= 15; i++)
    {
        int* value = (int*)malloc(sizeof(int));
        *value = i;
        listAddEnd(list, value);
    }

    for (int i = 0; i < 15; i++)
    {
       printf("%d\n", *(int*)*(int**)listGet(list, i));
    }

    for (int i = 0; i < list->size; i++)
    {
        free (*(int**)listGet(list, i));
    }

    free(list->data);
    free(list);
    
    return 0;
}
