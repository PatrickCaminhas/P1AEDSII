#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include "funcionarios.h"



void save(TEmployee *emp, FILE *out)
{
    fwrite(&emp->code, sizeof(int), 1, out);
    fwrite(&emp->name, sizeof(char), sizeof(emp->name), out);
    fwrite(&emp->cpf, sizeof(char), sizeof(emp->cpf),out);
    fwrite(&emp->birthday, sizeof(char), sizeof(emp->birthday),out);
    fwrite(&emp->wage, sizeof(double),1,out);
}


TEmployee *read (FILE *in)
{
    TEmployee *emp = (TEmployee*)malloc(sizeof(TEmployee));
    if(0 >= fread(&emp->code,sizeof(int),1,in))
    {
        free(emp);
        return NULL;
    }
    fread(&emp->name,sizeof(char),sizeof(emp->name),in);
    fread(&emp->cpf,sizeof(char),sizeof(emp->cpf),in);
    fread(&emp->birthday,sizeof(char),sizeof(emp->birthday),in);
    fread(&emp->wage,sizeof(double),1,in);

    return emp;
}
void printEmployee(TEmployee * emp)
{
    if(emp==NULL)
    {
        printf("Funcionario nao encontrado!\n");
    }
    else
    {
        printf("[Funcionario encontrado!] \n");
        printf("- Codigo: %d \n",emp->code);
        printf("- Nome: %s \n",emp->name);
        printf("- CPF: %s \n",emp->cpf);
        printf("- Data de Nascimento: %s \n", emp->birthday);
        printf("- Salario: R$ %.2f\n\n", emp->wage);
    }
}


// -----------------------------------------------------------------------------------------------------------------

// (A)
// Crie uma base de dados contendo 100 registros de funcionários,
// armazenados em um arquivo binário.

void createDataBase(FILE *arq, int empQtd)
{
    srand(time(NULL));
    for(int i=1; i<= empQtd; i++)
    {
            int code= rand() % empQtd;
        TEmployee emp;
        emp.code = code;
        sprintf(emp.name,"Funcionario %d", code);
        sprintf(emp.cpf, "111.111.111-11");
        sprintf(emp.birthday, "25/02/2023");
        emp.wage = 1000+code;
        fseek(arq,(i-1)*sizeof(TEmployee),SEEK_SET);
        save(&emp,arq);
    }
}

// -----------------------------------------------------------------------------------------------------------------

// (B)
// Realize uma busca sequencial por um funcionário específico. Considerar como
// chave de busca o código do funcionário. Informe o total de comparações feitas até encontrar o
// funcionário em questão, bem como o tempo gasto na busca.

TEmployee *sequentialSearch(int code, FILE *file, int empQtd)
{
    int i;
    clock_t t;
    t = clock();
    double timeTaken;
    for(i=1; i<=empQtd; i++)
    {
        fseek(file,i*sizeof(TEmployee),SEEK_SET);
        TEmployee *emp = read(file);
        if(code==emp->code)
        {

            t = clock() - t;
            timeTaken = ((double)t)/CLOCKS_PER_SEC;
            printf("BUSCA SEQUENCIAL\n");
            printf("  [Demorou %f segundos para executar] \n", timeTaken);
            printf("  [Numero de comparacoes: %d] \n", i);
            return emp;
        }
    }
    t = clock() - t;
    timeTaken = ((double)t)/CLOCKS_PER_SEC;
    printf("BUSCA SEQUENCIAL\n");
    printf("  [Demorou %f segundos para executar] \n", timeTaken);
    printf("  [Numero de compara��es: %d] \n", i);
    return NULL;

}
// -----------------------------------------------------------------------------------------------------------------

// (C)
// Utilize o método de ordenação KeySorting para ordenar o arquivo contendo a base
// de dados. Informe tempo na ordenação.

// (C1) Procura dentro do arquivo de funcionarios e depois salva no arquivo de chaves
// o codigo de todos funcionarios e a posição correspondente deles no arquivo de funcionarios.
void createKeys(FILE *file, FILE *fileKey, int empQtd)
{
    for(int i=1; i<= empQtd; i++)
    {
        fseek(file,i*sizeof(TEmployee),SEEK_SET);
        TEmployee *emp = read(file);
        TKey key;
        key.code= emp->code;
        key.position=i;
        fseek(fileKey,(i-1)*sizeof(TKey),SEEK_SET);
        saveKey(&key,fileKey);
    }
}
// (C2)Salva no arquivo de chaves o codigo e a posição do funcionario
void saveKey(TKey *key, FILE *out)
{
    fwrite(&key->code, sizeof(int), 1, out);
    fwrite(&key->position, sizeof(int), 1, out);
}
//  (3) Retorna a chave
TKey *readKey (FILE *in)
{
    TKey *key = (TKey*)malloc(sizeof(TKey));
    if(0 >= fread(&key->code,sizeof(int),1,in))
    {
        free(key);
        return NULL;
    }
    fread(&key->position,sizeof(int),1,in);
    return key;
}
// (C4)Faz uma busca sequencial do usuario do codigo solicitado no arquivo de chaves e
// com a posição dele é retornado as informações completas do funcionario.
TEmployee *searchKey(FILE *file, FILE *fileKey, int code, int empQtd )
{
    clock_t t;
    t = clock();
    double timeTaken;
    for(int i = 0; i<empQtd; i++)
    {
        fseek(fileKey,i*sizeof(TKey),SEEK_SET);
        TKey *key = readKey(fileKey);
        if(code==key->code)
        {
            fseek(file,key->position*sizeof(TEmployee),SEEK_SET);
            TEmployee *emp = read(file);
            timeTaken = ((double)t)/CLOCKS_PER_SEC; // in seconds
            printf("BUSCA PELA KEY\n");
            printf("  [Demorou %f segundos para executar] \n", timeTaken);
            return emp;
        }
    }
    return NULL;
}
// (C5) Imprime todas as chaves, apenas para comparação
void printAllKeys(FILE *fileKey, int empQtd)
{
    for(int i = 0; i <= empQtd-2; i++)
    {
        fseek(fileKey,i*sizeof(TKey),SEEK_SET);
        TKey *key = readKey(fileKey);
        printf("[Posicao: %d] | [Codigo: %d] \n",key->position, key->code);
    }
}

// -----------------------------------------------------------------------------------------------------------------

// (D)
// Realize a busca pelo mesmo funcionário escolhido na letra b. Utilize agora a busca
// binária no arquivo ordenado. Informe o total de comparações feitas até encontrar o funcionário
// em questão, bem como o tempo gasto na busca.

TEmployee *binarySearch(int code, FILE *file, int empQtd)
{
    int left = 0, right = empQtd-1;
    int counter=0;
    clock_t t;
    t = clock();
    double timeTaken;
    while(left <= right)
    {

        int middle = (left+right)/2;
        fseek(file,middle*sizeof(TEmployee),SEEK_SET);
        TEmployee *emp = read(file);
        if(code==emp->code)
        {
            t = clock() - t;
            timeTaken = ((double)t)/CLOCKS_PER_SEC; // in seconds
            printf("BUSCA BINARIA\n");
            printf("  [Demorou %f segundos para executar] \n", timeTaken);
            printf("  [Numero de comparacoes: %d] \n", counter);
            return emp;
        }

        else if(emp->code<code)
        {
            left = middle+1;
        }

        else
        {
            right = middle-1;
        }
        counter++;
    }
    t = clock() - t;
    timeTaken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("BUSCA BINARIA\n");
    printf("  [Demorou %f segundos para executar] \n", timeTaken);
    printf("  [Numero de comparacoes: %d] \n", counter);
    return NULL;
}

// -----------------------------------------------------------------------------------------------------------------

// Insertion Sort (Extra)
int registerSize() {
     return sizeof(TEmployee);
 }

 void insertionSort(FILE *file, int empQtd) {
    fseek(file, 0, SEEK_SET);
    int i;
    for (int j = 2; j <= empQtd; j++) {
        fseek(file, (j-1) * registerSize(), SEEK_SET);
        TEmployee *f = read(file);
        i = j - 1;
        fseek(file, (i-1) * registerSize(), SEEK_SET);
        do{
            TEmployee *fl = read(file);
            if( (fl->code < fl->code)){
                break;
            }
            fseek(file, i * registerSize(), SEEK_SET);
            save(fl, file);
            i = i - 1;
            fseek(file, (i-1) * registerSize(), SEEK_SET);
            free(fl);
        }while ((i > 0) );
        fseek(file, (i) * registerSize(), SEEK_SET);
        save(f, file);
        free(f);
    }
    fflush(file);
}

// -----------------------------------------------------------------------------------------------------------------
