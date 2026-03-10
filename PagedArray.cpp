//
// Created by grimm on 7/3/26.
//

#include "PagedArray.h"

PagedArray::PagedArray(const char *filePath, int pageSize, int pageCount) {
    this-> pageSize = pageSize;
    this-> pageCount = pageCount;
    this-> filePath = filePath;
    faultCount = 0;
    hitCount = 0;
    indexFIFO = 0;

    ptrPageFile = fopen(filePath, "r+b");
    if (ptrPageFile == nullptr) {
        std::cerr << "Error: no se pudo abrir el archivo, path inexistente: " << filePath << std::endl;
        exit(1);
    }

    pages = new int*[pageCount];
    pageNumArray = new int[pageCount];
    fseek(ptrPageFile, 0, SEEK_END);
    long sizeEnBytes = ftell(ptrPageFile);
    this-> arraySize = sizeEnBytes / 4;
    fseek(ptrPageFile, 0, SEEK_SET);

    for (int i = 0; i < pageCount; i++) {
        pages[i] = nullptr;
        pageNumArray[i] = -1;
    }
}


PagedArray::~PagedArray() {
    for (int i = 0; i < pageCount; i++) {
        if (pages[i] != nullptr) {
            long posicion = (long)pageNumArray[i] * 4 * pageSize;
            fseek(ptrPageFile, posicion, SEEK_SET);
            fwrite(pages[i], sizeof(int), pageSize, ptrPageFile);
            delete[] pages[i];
            pages[i] = nullptr;
        }
    }
    delete[] pages;
    delete[] pageNumArray;
    fclose(ptrPageFile);
}


int& PagedArray::operator[](int index) {
    int pageNum = index / pageSize;
    int offset = index % pageSize;


    for (int i = 0; i < pageCount; i++) {
        if (pageNumArray[i] == pageNum) {
            hitCount++;
            return pages[i][offset];
        }
    }

    faultCount++;

    if (pages[indexFIFO] != nullptr) {
        long posicion = (long)pageNumArray[indexFIFO] * 4 * pageSize;
        fseek(ptrPageFile, posicion, SEEK_SET);
        fwrite(pages[indexFIFO], sizeof(int), pageSize, ptrPageFile);
        delete[] pages[indexFIFO];
        pages[indexFIFO] = nullptr;
    }

    pages[indexFIFO] = new int[pageSize];
    pageNumArray[indexFIFO] = pageNum;
    long posicion = (long)pageNumArray[indexFIFO] * 4 * pageSize;
    fseek(ptrPageFile, posicion, SEEK_SET);
    fread(pages[indexFIFO], sizeof(int), pageSize, ptrPageFile);
    int espacioUsado = indexFIFO;
    indexFIFO = (indexFIFO + 1) % pageCount;
    return pages[espacioUsado][offset];

}