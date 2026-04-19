# Proyecto-Datos-II-1-Paged-Arrays

Este proyecto implementa una clase `PagedArray` que permite manejar arreglos de
gran tamaño sin mantener todo su contenido en memoria principal, aplicando el
concepto de paginación de administración de memoria; el proyecto incluye dos
programas independientes: un generador de archivos binarios de enteros aleatorios
y un ordenador que implementa cinco algoritmos de ordenamiento sobre la clase
`PagedArray`.

---

## Requisitos

### Linux
- GCC 7.0 o superior
- CMake 3.10 o superior
- Make

### Windows
- MinGW-w64 con GCC
- CMake 3.10 o superior
- Los tres deben estar agregados al PATH del sistema

---

## Compilación

### Linux

Abra una terminal en la raíz del proyecto y ejecute:
```bash
mkdir build
cd build
cmake ..
make
```

Esto generará dos ejecutables dentro de la carpeta `build`:
- `generador`
- `sorter`

### Windows

Abra una terminal (cmd o PowerShell) en la raíz del proyecto y ejecute:
```cmd
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
```

Esto generará dos ejecutables dentro de la carpeta `build`:
- `generador.exe`
- `sorter.exe`

---

## Uso

### Generador

El generador crea un archivo binario de enteros aleatorios del tamaño especificado.

**Linux:**
```bash
./generador -size  -output 
```

**Windows:**
```cmd
generador.exe -size <SIZE> -output <OUTPUT FILE PATH>
```

**Parámetros:**
- `-size`: tamaño del archivo a generar. Valores válidos:
  - `SMALL`: genera un archivo de 64 MB
  - `MEDIUM`: genera un archivo de 128 MB
  - `LARGE`: genera un archivo de 256 MB
- `-output`: ruta completa donde se guardará el archivo generado

**Ejemplo Linux:**
```bash
./generador -size SMALL -output /home/usuario/archivos/datos.bin
```

**Ejemplo Windows:**
```cmd
generador.exe -size SMALL -output C:\usuarios\archivos\datos.bin
```

---

### Sorter

El sorter ordena un archivo binario generado previamente y produce dos archivos
de salida: uno binario ordenado y uno legible en texto plano con los números
separados por comas.

**Linux:**
```bash
./sorter -input <Path de archivo de input> -output <Path de archivo de output> -alg <Algoritmo> -pageSize <Tamaño PageSize>  -pageCount <Tamaño PageCount>
```

**Windows:**
```cmd
sorter.exe -input <Path de archivo de input> -output <Path de archivo de output> -alg <Algoritmo> -pageSize <Tamaño PageSize> -pageCount <Tamaño PageCount>
```

**Parámetros:**
- `-input`: ruta del archivo binario a ordenar
- `-output`: ruta donde se guardará el archivo ordenado. Se generarán dos
  archivos: el binario en la ruta especificada y un archivo de texto legible
  con el sufijo `_legible.txt`
- `-alg`: algoritmo de ordenamiento a utilizar. Valores válidos:
  - `insertionSort`: solo viable para archivos SMALL
  - `shellSort`: viable para archivos SMALL y MEDIUM
  - `heapSort`: viable para todos los tamaños
  - `mergeSort`: viable para archivos SMALL y MEDIUM
  - `quickSort`: viable para todos los tamaños
- `-pageSize`: cantidad máxima de enteros por página, debe ser un entero
  positivo mayor a cero
- `-pageCount`: cantidad de páginas simultáneas en memoria, debe ser un
  entero mayor a 1

**Ejemplo Linux:**
```bash
./sorter -input /home/usuario/archivos/datos.bin -output /home/usuario/archivos/resultado.bin -alg mergeSort -pageSize 10000 -pageCount 4
```

**Ejemplo Windows:**
```cmd
sorter.exe -input C:\usuarios\archivos\datos.bin -output C:\usuarios\archivos\resultado.bin -alg mergeSort -pageSize 10000 -pageCount 4
```

---

## Archivos de salida

El sorter genera dos archivos:
- **Archivo binario:** en la ruta especificada en `-output`, contiene los
  enteros ordenados en formato binario
- **Archivo legible:** en la misma ruta con el sufijo `_legible.txt`, contiene
  los enteros ordenados separados por comas, verificable desde cualquier
  editor de texto

---

## Estadísticas de ejecución

Al finalizar, el sorter imprime en consola un resumen con:
- Algoritmo utilizado
- Tiempo de ejecución en segundos
- Número de page hits
- Número de page faults

---
