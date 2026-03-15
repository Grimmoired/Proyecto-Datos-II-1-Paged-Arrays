//
// Created by grimm on 7/3/26.
//

#ifndef PROYECTO_DATOS_II_1_PAGED_ARRAYS_PAGEDARRAY_H
#define PROYECTO_DATOS_II_1_PAGED_ARRAYS_PAGEDARRAY_H
#include <iostream>
#include <cstdio>


class PagedArray {
private:
    int** pages;
    FILE* ptrPageFile;
    int pageSize;
    int pageCount;
    long long faultCount;
    long long hitCount;
    int* pageNumArray;
    int arraySize;
    const char* filePath;
    int indexFIFO;

public:
    PagedArray(const char* filePath, int pageSize, int pageCount);
    ~PagedArray();
    int& operator[](int index);
    int getArraySize();
    long long getFaultCount();
    long long getHitCount();
};

#endif //PROYECTO_DATOS_II_1_PAGED_ARRAYS_PAGEDARRAY_H