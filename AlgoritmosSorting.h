//
// Created by grimm on 10/3/26.
//

#ifndef PROYECTO_DATOS_II_1_PAGED_ARRAYS_ALGORITMOSSORTING_H
#define PROYECTO_DATOS_II_1_PAGED_ARRAYS_ALGORITMOSSORTING_H
#include <iostream>
#include "PagedArray.h"

void shellSort(PagedArray& array, int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            int temp = array[i];
            int j;
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                array[j] = array[j - gap];
            }
            array[j] = temp;
        }
    }
}

void insertionSort (PagedArray& array, int n) {
    for (int i = 1; i < n; i++) {
        int temp = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > temp) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = temp;
    }
}

void heapSortAux(PagedArray& array, int n, int i) {
    int mayor = i;
    int izq = 2 * i + 1;
    int der = 2 * i + 2;

    if (izq < n && array[izq] > array[mayor]) {
        mayor = izq;
    }

    if (der < n && array[der] > array[mayor]) {
        mayor = der;
    }

    if (mayor != i) {
        int copia = array[i];
        array[i] = array[mayor];
        array[mayor] = copia;
        heapSortAux(array, n, mayor);
    }
}

void heapSort(PagedArray& array, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapSortAux(array, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        int copia = array[0];
        array[0] = array[i];
        array[i] = copia;
        heapSortAux(array, i, 0);
    }
}

void mergeSortAux(PagedArray& array, int izq, int med, int der) {
    int n1 = med - izq + 1;
    int n2 = der - med;
    int *temp1 = new int[n1];
    int *temp2 = new int[n2];

    for (int i = 0; i < n1; i++)
        temp1[i] = array[izq + i];
    for (int j = 0; j < n2; j++)
        temp2[j] = array[med + 1 + j];

    int i = 0;
    int j = 0;
    int k = izq;
    while (i < n1 && j < n2) {
        if (temp1[i] <= temp2[j]) {
            array[k] = temp1[i];
            i++;
        }
        else {
            array[k] = temp2[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = temp1[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = temp2[j];
        j++;
        k++;
    }

    delete[] temp1;
    delete[] temp2;
}

void mergeSort(PagedArray& array, int izq, int der) {
    if (izq >= der) {
        return;
    }
    int med = izq + (der - izq) / 2;
    mergeSort(array, izq, med);
    mergeSort(array, med + 1, der);
    mergeSortAux(array, izq, med, der);
}

int quickSortAux(PagedArray& array, int bajo, int alto) {
    int pivot = array[alto];
    int i = (bajo - 1);

    for (int j = bajo; j <= alto - 1; j++) {
        if (array[j] <= pivot) {
            i++;
            int copia = array[i];
            array[i] = array[j];
            array[j] = copia;
        }
    }
    int copia = array[i + 1];
    array[i+1] = array[alto];
    array[alto] = copia;
    return (i + 1);
}

void quickSort(PagedArray& array, int bajo, int alto) {
    if (bajo < alto) {
        int index = quickSortAux(array, bajo, alto);

        quickSort(array, bajo, index - 1);
        quickSort(array, index + 1, alto);
    }
}

#endif //PROYECTO_DATOS_II_1_PAGED_ARRAYS_ALGORITMOSSORTING_H