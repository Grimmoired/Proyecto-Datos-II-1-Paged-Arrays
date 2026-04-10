    //
    // Created by grimm on 9/3/26.
    //

    #include <iostream>
    #include <ostream>
    #include <cstring>
    #include "PagedArray.h"
    #include "AlgoritmosSorting.h"
    #include "Baseline.h"

    int main(int argc, char* argv[]) {

        const int bufferSize = 4096;
        int buffer[bufferSize];
        FILE* inputPageFile;
        FILE* outputPageFile;

        if (argc != 11) {
            std::cerr << "Error: se recibio una cantidad incorrecta de argumentos" << std::endl;
            exit(1);
        }

        if (strcmp(argv[1], "-input") != 0) {
            std::cerr << "Error: parametro " << argv[1] << " no valido, debe especificar el parametro -input." << std::endl;
            exit(1);
        }

        if (strcmp(argv[3], "-output") != 0) {
            std::cerr << "Error: parametro " << argv[3] << " no valido, debe especificar el parametro -output." << std::endl;
            exit(1);
        }

        if (strcmp(argv[5], "-alg") != 0) {
            std::cerr << "Error: parametro " << argv[5] << " no valido, debe especificar el parametro -alg." << std::endl;
            exit(1);
        }

        if (strcmp(argv[6], "heapSort") != 0 && strcmp(argv[6], "shellSort") != 0 && strcmp(argv[6], "insertionSort") != 0 && strcmp(argv[6], "mergeSort") != 0 && strcmp(argv[6], "quickSort") != 0) {
            std::cerr << "Error: " << argv[6] << " no es un algoritmo de ordenamiento valido, este programa solo soporta heapSort, shellSort, insertionSort, mergeSort y quickSort." << std::endl;
            exit(1);
        }

        if (strcmp(argv[7], "-pageSize") != 0) {
            std::cerr << "Error: parametro " << argv[7] << " no valido, debe especificar el parametro -pageSize." << std::endl;
            exit(1);
        }

        if (atoi(argv[8]) <= 0) {
            std::cerr << "Error: parametro " << argv[8] << " no valido, pageSize debe ser un numero entero positivo." << std::endl;
            exit(1);
        }

        if (strcmp(argv[9], "-pageCount") != 0) {
            std::cerr << "Error: parametro " << argv[9] << " no valido, debe especificar el parametro -pageCount." << std::endl;
            exit(1);
        }

        if (atoi(argv[10]) < 2) {
            std::cerr << "Error: parametro " << argv[10] << " no valido, pageCount debe ser un numero entero mayor a 1." << std::endl;
            exit(1);
        }

        const char* filePathInput = argv[2];
        const char* filePathOutput = argv[4];

        inputPageFile = fopen(filePathInput, "rb");
        if (inputPageFile == nullptr) {
            std::cerr << "Error: no se pudo abrir el archivo, path inexistente: " << filePathInput << std::endl;
            exit(1);
        }

        fseek(inputPageFile, 0, SEEK_END);
        long long sizeEnBytes = ftell(inputPageFile);

        if (strcmp(argv[6], "heapSort") == 0 && sizeEnBytes > 67108864) {
            std::cerr << "Error: " << argv[6] << " no es soportado por el tamaño LARGE debido a la complejidad de operaciones." << std::endl;
            exit(1);
        }
        if (strcmp(argv[6], "shellSort") == 0 && sizeEnBytes > 33554432) {
            std::cerr << "Error: " << argv[6] << " no es soportado por los tamaños MEDIUM y LARGE debido a la complejidad de operaciones." << std::endl;
            exit(1);
        }
        if (strcmp(argv[6], "insertionSort") == 0 && sizeEnBytes > 33554432 ) {
            std::cerr << "Error: " << argv[6] << " no es soportado por los tamaños MEDIUM y LARGE debido a la complejidad de operaciones." << std::endl;
            exit(1);
        }

        fseek(inputPageFile, 0, SEEK_SET);

        outputPageFile = fopen(filePathOutput, "wb");
        if (outputPageFile == nullptr) {
            std::cerr << "Error: no se pudo abrir el archivo, path inexistente: " << filePathOutput << std::endl;
            exit(1);
        }

        int bloqueLeido = 1;
        while (bloqueLeido > 0) {
            bloqueLeido = fread(buffer, sizeof(int), bufferSize, inputPageFile);
            if (bloqueLeido == 0) {
                break;
            };
            fwrite(buffer, sizeof(int), bloqueLeido, outputPageFile);
        }

        fclose(inputPageFile);
        fclose(outputPageFile);

        int pageSize = atoi(argv[8]);
        int pageCount = atoi(argv[10]);
        PagedArray arr(filePathOutput, pageSize, pageCount);

        clock_t tiempoInicio = clock();
        if (strcmp(argv[6], "heapSort") == 0) {
            heapSort(arr, arr.getArraySize());
        } else if (strcmp(argv[6], "shellSort") == 0) {
            shellSort(arr, arr.getArraySize());
        } else if (strcmp(argv[6], "insertionSort") == 0) {
            insertionSort(arr, arr.getArraySize());
        } else if (strcmp(argv[6], "mergeSort") == 0) {
            mergeSort(arr, 0, arr.getArraySize() - 1);
        } else if (strcmp(argv[6], "quickSort") == 0) {
            quickSort(arr, 0, arr.getArraySize() - 1);
        }

        clock_t tiempoFin = clock();
        double tiempoEjecucion = (double)(tiempoFin - tiempoInicio) / CLOCKS_PER_SEC;

        std::string filePathLegible = std::string(filePathOutput) + "_legible.txt";
        FILE* archivoLegible = fopen(filePathLegible.c_str(), "w");
        if (archivoLegible == nullptr) {
            std::cerr << "Error: no se pudo abrir el archivo, path inexistente: " << filePathInput << std::endl;
            exit(1);
        }

        for (int i = 0; i < arr.getArraySize(); i++) {
            if (i == arr.getArraySize() - 1) {
                fprintf(archivoLegible, "%d", arr[i]);
            } else {
                fprintf(archivoLegible, "%d,", arr[i]);
            }
        }
        fclose(archivoLegible);

        std::cout << "Algoritmo Usado : " << argv[6] << std::endl;
        std::cout << "Tiempo de Ejecucion : " << tiempoEjecucion << " segundos" << std::endl;
        std::cout << "Numero de Page Hit : " << arr.getHitCount() << std::endl;
        std::cout << "Numero de Page Fault : " << arr.getFaultCount() << std::endl;

        std::cout << "\n--- Datos de Baseline (sin paginacion) ---" << std::endl;

        double tiempoBaseline = ejecutarBaseline(filePathOutput, argv[6], arr.getArraySize());

        if (tiempoBaseline < 0) {
            std::cout << "Baseline: no se pudo ejecutar" << std::endl;
        } else {
            double overhead = ((tiempoEjecucion - tiempoBaseline) / tiempoBaseline) * 100.0;
            std::cout << "Tiempo Baseline          : " << tiempoBaseline << " segundos" << std::endl;
            std::cout << "Tiempo con Paginacion    : " << tiempoEjecucion << " segundos" << std::endl;
            std::cout << "Overhead de Paginacion   : " << overhead << "%" << std::endl;
        }
    }