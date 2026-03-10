//
// Created by grimm on 9/3/26.
//

#include <iostream>
#include <ostream>
#include <cstring>
#include <ctime>

int main(int argc, char* argv[]) {

    const int bufferSize = 4096;
    int buffer[bufferSize];
    FILE* ptrPageFile;

    if (argc != 5) {
        std::cerr << "Error: se recibio una cantidad incorrecta de argumentos" << std::endl;
        exit(1);
    }

    if (strcmp(argv[1], "-size") != 0) {
        std::cerr << "Error: parametro " << argv[1] << " no valido, debe especificar el parametro -size." << std::endl;
        exit(1);
    }

    if (strcmp(argv[2], "SMALL") != 0 && strcmp(argv[2], "MEDIUM") != 0 && strcmp(argv[2], "LARGE") != 0) {
        std::cerr << "Error: " << argv[2] << " no es un tamaño valido, especifique unicamente SMALL, MEDIUM o LARGE." << std::endl;
        exit(1);
    }

    if (strcmp(argv[3], "-output") != 0) {
        std::cerr << "Error: parametro " << argv[3] << " no valido, debe especificar el parametro -output." << std::endl;
        exit(1);
    }

    long long sizeConfiguracion = 0;
    if (strcmp(argv[2], "SMALL") == 0) {
        sizeConfiguracion = 512;
    }
    else if (strcmp(argv[2], "MEDIUM") == 0) {
        sizeConfiguracion = 1024;
    }
    else if (strcmp(argv[2], "LARGE") == 0) {
        sizeConfiguracion = 2048;
    }

    long long sizeBytes = (sizeConfiguracion * 1024LL * 1024LL);
    long long sizeEnteros = sizeBytes / 4LL;

    const char* filePath = argv[4];
    ptrPageFile = fopen(filePath, "wb");
    if (ptrPageFile == nullptr) {
        std::cerr << "Error: no se pudo abrir el archivo, path inexistente: " << filePath << std::endl;
        exit(1);
    }

    srand(time(0));

    int enterosEscritos = 0;

    while (enterosEscritos < sizeEnteros) {
        int enterosPendientes = sizeEnteros - enterosEscritos;
        int enterosAProcesar = (enterosPendientes < bufferSize) ? enterosPendientes : bufferSize;
        for (int i = 0; i < enterosAProcesar; i++) {
            buffer[i] = rand();
        }
        fwrite(buffer, sizeof(int), enterosAProcesar, ptrPageFile);
        enterosEscritos = enterosEscritos + enterosAProcesar;
    }

    fclose(ptrPageFile);
}