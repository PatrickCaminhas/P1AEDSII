#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct Employee
{
    int code;
    char name[30];
    char cpf[15];
    char birthday[11];
    double wage;
} TEmployee;

typedef struct EmployeeKey
{
    int position;
    int code;
} TKey;

// Pega o tamanho do registro
int registerSize()
{
    return sizeof(TEmployee);
}

void save(TEmployee *employee, FILE *out)
{
    fwrite(&employee->code, sizeof(int), 1, out);
    fwrite(employee->name, sizeof(char), sizeof(employee->name), out);
    fwrite(employee->cpf, sizeof(char), sizeof(employee->cpf), out);
    fwrite(employee->birthday, sizeof(char), sizeof(employee->birthday), out);
    fwrite(&employee->wage, sizeof(double), 1, out);
}

void saveKey(TKey *key, FILE *out)
{
    fwrite(&key->code, sizeof(int), 1, out);
    fwrite(&key->position, sizeof(int), 1, out);
}

TKey *readKey (FILE *in)
{
    TKey *key = (TKey*)malloc(sizeof(TKey));
    if(0 >= fread(&key->code, sizeof(int), 1, in))
    {
        free(key);
        return NULL;
    }
    fread(&key->position, sizeof(int), 1, in);
    return key;
}

TEmployee *read(FILE *in)
{
    TEmployee *emp = (struct Employee *) malloc(sizeof(struct Employee));
    if (fread(&emp->code, sizeof(int), 1, in) <= 0)
    {
        free(emp);
        return NULL;
    }

    fread(emp->name, sizeof(char), sizeof(emp->name), in);
    fread(emp->cpf, sizeof(char), sizeof(emp->cpf), in);
    fread(emp->birthday, sizeof(char), sizeof(emp->birthday), in);
    fread(&emp->wage, sizeof(double), 1, in);
    return emp;
}

void printData(TEmployee * emp)
{
    if(emp == NULL)
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
void createDataBase(FILE *file, int empQty)
{
    for (int i = 1; i <= empQty; i++)
    {
        TEmployee emp;
        emp.code = rand()%1000;
        sprintf(emp.name, "Employee %d", i);
        sprintf(emp.cpf, "111.111.111-11");
        sprintf(emp.birthday, "20/08/1990");
        emp.wage = 1000;
        fseek(file, (i-1)*sizeof(struct Employee), SEEK_SET);
        save(&emp, file);
    }
}

// -----------------------------------------------------------------------------------------------------------------

// (B)
// Realize uma busca sequencial por um funcionário específico. Considerar como
// chave de busca o código do funcionário. Informe o total de comparações feitas até encontrar o
// funcionário em questão, bem como o tempo gasto na busca.
TEmployee *sequencial_search(int code, FILE *file, int size)
{
    int i;
    clock_t t;
    t = clock();
    double timeTaken;
    for(i=1; i<= size; i++)
    {
        fseek(file, i*sizeof(TEmployee), SEEK_SET);
        TEmployee *emp = read(file);
        if(code == emp->code)
        {
            t = clock() - t;
            timeTaken = ((double)t) / CLOCKS_PER_SEC;
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
    printf("  [Numero de comparações: %d] \n", i);
    return NULL;
}

// -----------------------------------------------------------------------------------------------------------------

// (C)
// Utilize o método de ordenação KeySorting para ordenar o arquivo contendo a base
// de dados. Informe tempo na ordenação.
void createKeyes(FILE *file, FILE *fileKey, int nFunc)
{
    for(int i=i; i<= nFunc; i++)
    {
        fseek(file,(i-1)*sizeof(TEmployee), SEEK_SET);
        TEmployee *emp = read(file);
        TKey key;
        key.code = emp->code;
        key.position = i;
        fseek(fileKey,(i-1)*sizeof(TKey), SEEK_SET);
        saveKey(&key, fileKey);
    }
}

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
            fseek(file,(key->position-1)*sizeof(TEmployee),SEEK_SET);
            TEmployee *emp = read(file);
            timeTaken = ((double)t)/CLOCKS_PER_SEC; // in seconds
            printf("BUSCA PELA KEY\n");
            printf("  [Demorou %f segundos para executar] \n", timeTaken);
            return emp;
        }
    }
    return NULL;
}

// -----------------------------------------------------------------------------------------------------------------

// (D)
// Realize a busca pelo mesmo funcionário escolhido na letra b. Utilize agora a busca
// binária no arquivo ordenado. Informe o total de comparações feitas até encontrar o funcionário
// em questão, bem como o tempo gasto na busca.
TEmployee *binary_search(int code, FILE *file, int size)
{
    int counter=0;
    clock_t t;
    t = clock();
    double timeTaken;
    int left = 0, right =  size - 1;
    while(left <= right)
    {
        int middle = (left + right) / 2;
        fseek(file, middle*sizeof(struct Employee), SEEK_SET);
        TEmployee *emp = read(file);
        if (code == emp->code)
        {
            t = clock() - t;
            timeTaken = ((double)t)/CLOCKS_PER_SEC; // in seconds
            printf("BUSCA BINARIA\n");
            printf("  [Demorou %f segundos para executar] \n", timeTaken);
            printf("  [Numero de comparacoes: %d] \n", counter);
            return emp;
        }
        else if (emp->code < code)
        {
            left = middle + 1;
        }
        else
        {
            right = middle - 1;
        }
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
void insertionSort(FILE *file, int size)
{
    fseek(file, 0, SEEK_SET);
    int i;
    for (int j = 2; j <= size; j++)
    {
        fseek(file, (j-1) * registerSize(), SEEK_SET);
        TEmployee *f = read(file);
        i = j - 1;
        fseek(file, (i-1) * registerSize(), SEEK_SET);
        do
        {
            TEmployee *fl = read(file);
            if( (fl->code < f->code))
            {
                break;
            }
            fseek(file, i * registerSize(), SEEK_SET);
            save(fl, file);
            i = i - 1;
            fseek(file, (i-1) * registerSize(), SEEK_SET);
            free(fl);
        }
        while ((i > 0) );
        fseek(file, (i) * registerSize(), SEEK_SET);
        save(f, file);
        free(f);
    }
    fflush(file);
}

// -----------------------------------------------------------------------------------------------------------------

void printDataset(FILE *file, int size)
{
    int i = 0;
    fseek(file, 0 * sizeof(struct Employee), SEEK_SET);
    if (file != NULL)
    {

        int aux = 1;
        do
        {
            fseek(file, (i)*registerSize(), SEEK_SET);
            TEmployee *emp = read(file);
            if (emp)
            {
                printData(emp);
                i++;
                free(emp);
            }
            else
                aux = 0;
        }
        while (aux);
    }
    else
        printf("Erro ao abrir arquivo\n");
}
void printAllKeys(FILE *fileKey, int empQtd)
{
    for(int i = 0; i <= empQtd-1; i++)
    {
        fseek(fileKey,i*sizeof(TKey),SEEK_SET);
        TKey *key = readKey(fileKey);
        printf("[Posicao: %d] | [Codigo: %d] \n",key->position, key->code);
    }
}

// -----------------------------------------------------------------------------------------------------------------

int main()
{

    FILE *file = fopen("funcionarios.dat", "wb+");
    FILE *fileKey = fopen("funcionariosKeys.dat", "wb+");

    if(file==NULL)
    {
        printf("Não foi possivel abrir o arquivo! \n");
        return 1;
    }

    createDataBase(file, 100);
    insertionSort(file, 100);
    printDataset(file, 100);
    TEmployee * emp;


    printf("--------\n");
    emp = binary_search(6, file, 100);
    printData(emp);
    printf("--------\n");

    emp = sequencial_search(35,file,100);
    printData(emp);


    printf("--------\n");
    createKeyes(file, fileKey, 100);
    emp = searchKey(file, fileKey, 995, 100);
    printData(emp);

    free(emp);
    fclose(file);
    fclose(fileKey);
    return 0;
}
