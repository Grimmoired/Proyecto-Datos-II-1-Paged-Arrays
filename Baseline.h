//
// Created by grimm on 9/4/26.
//

#ifndef PROYECTO_DATOS_II_1_PAGED_ARRAYS_BASELINE_H
#define PROYECTO_DATOS_II_1_PAGED_ARRAYS_BASELINE_H

#include <iostream>
#include <ctime>

void shellSortBaseline(int* array, int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = array[i];
            int j;
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                array[j] = array[j - gap];
            }
            array[j] = temp;
        }
    }
}

void insertionSortBaseline(int* array, int n) {
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

void heapSortAuxBaseline(int* array, int n, int i) {
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
        heapSortAuxBaseline(array, n, mayor);
    }
}

void heapSortBaseline(int* array, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapSortAuxBaseline(array, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        int copia = array[0];
        array[0] = array[i];
        array[i] = copia;
        heapSortAuxBaseline(array, i, 0);
    }
}

void mergeSortAuxBaseline(int* array, int izq, int med, int der) {
    int n1 = med - izq + 1;
    int n2 = der - med;
    int* temp1 = new int[n1];
    int* temp2 = new int[n2];

    for (int i = 0; i < n1; i++)
        temp1[i] = array[izq + i];
    for (int j = 0; j < n2; j++)
        temp2[j] = array[med + 1 + j];

    int i = 0, j = 0, k = izq;
    while (i < n1 && j < n2) {
        if (temp1[i] <= temp2[j]) {
            array[k] = temp1[i];
            i++;
        } else {
            array[k] = temp2[j];
            j++;
        }
        k++;
    }
    while (i < n1) { array[k] = temp1[i]; i++; k++; }
    while (j < n2) { array[k] = temp2[j]; j++; k++; }

    delete[] temp1;
    delete[] temp2;
}

void mergeSortBaseline(int* array, int izq, int der) {
    if (izq >= der) { return; }
    int med = izq + (der - izq) / 2;
    mergeSortBaseline(array, izq, med);
    mergeSortBaseline(array, med + 1, der);
    mergeSortAuxBaseline(array, izq, med, der);
}

int quickSortAuxBaseline(int* array, int bajo, int alto) {
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
    array[i + 1] = array[alto];
    array[alto] = copia;
    return (i + 1);
}

void quickSortBaseline(int* array, int bajo, int alto) {
    if (bajo < alto) {
        int index = quickSortAuxBaseline(array, bajo, alto);
        quickSortBaseline(array, bajo, index - 1);
        quickSortBaseline(array, index + 1, alto);
    }
}

double ejecutarBaseline(const char* filePath, const char* algoritmo, int arraySize) {
    int* baselineArray = new int[arraySize];
    FILE* archivo = fopen(filePath, "rb");
    if (archivo == nullptr) {
        std::cerr << "Error: no se pudo abrir el archivo para baseline" << std::endl;
        delete[] baselineArray;
        return -1.0;
    }
    fread(baselineArray, sizeof(int), arraySize, archivo);
    fclose(archivo);

    clock_t inicio = clock();

    if (strcmp(algoritmo, "shellSort") == 0) {
        shellSortBaseline(baselineArray, arraySize);
    } else if (strcmp(algoritmo, "insertionSort") == 0) {
        insertionSortBaseline(baselineArray, arraySize);
    } else if (strcmp(algoritmo, "heapSort") == 0) {
        heapSortBaseline(baselineArray, arraySize);
    } else if (strcmp(algoritmo, "mergeSort") == 0) {
        mergeSortBaseline(baselineArray, 0, arraySize - 1);
    } else if (strcmp(algoritmo, "quickSort") == 0) {
        quickSortBaseline(baselineArray, 0, arraySize - 1);
    }

    clock_t fin = clock();
    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    delete[] baselineArray;
    return tiempo;
}

#endif //PROYECTO_DATOS_II_1_PAGED_ARRAYS_BASELINE_H