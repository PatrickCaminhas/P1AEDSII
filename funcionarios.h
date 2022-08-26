#ifndef FUNCIONARIOS_H_INCLUDED
#define FUNCIONARIOS_H_INCLUDED
#include <stdio.h>

typedef struct Employee{
int code;
char name [50];
char cpf[15];
char birthday[11];
double wage;
} TEmployee;

typedef struct EmployeeKey{
int position;
char code;
}TKey;

void save(TEmployee *emp, FILE *out);
void saveKey(TKey *key, FILE *out);
TEmployee *read (FILE *in);
TKey *readKey (FILE *in);
void createDataBase(FILE *file, int nFunc);
void createKeys(FILE *file, FILE *fileKey, int empQtd);
TEmployee *searchKey(FILE *file, FILE *fileKey, int codigo, int empQtd );
TEmployee *binarySearch(int code, FILE *file, int empQtd);
TEmployee *sequentialSearch(int code, FILE *file, int empQtd);
void printEmployee(TEmployee * emp);
void insertionSort(FILE *file, int empQtd);
int registerSize();

#endif // FUNCIONARIOS_H_INCLUDED
