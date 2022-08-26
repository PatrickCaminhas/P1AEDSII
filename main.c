#include <stdio.h>
#include <stdlib.h>
#include "funcionarios.c"
#include "funcionarios.h"

int main()
{

    FILE *file = fopen("funcionarios.dat", "wb+");
    FILE *fileKey = fopen("funcionariosKeys.dat", "wb+");
    if(file==NULL)
    {
        printf("Nao foi possivel abrir o arquivo! \n");
        return 1;
    }
    if(fileKey==NULL)
    {
        printf("Nao foi possivel abrir o arquivo! \n");
        return 1;
    }

    int numberOfEmployees= 100;
    createDataBase(file,numberOfEmployees);
    TEmployee *emp;
    createKeys(file,fileKey,numberOfEmployees-1);

    int menu=0;
    int codigo;
    do
    {
        printf("                                               [MENU]\n");
        printf("1 - Busca Sequencial | 2 - Busca pela Chave | 3 - Busca Binaria | 4 - Imprimir todas as chaves | 5 - Sair");
        printf("\nOpcao selecionada: ");
        scanf("%d", &menu);
        switch(menu)
        {
        case 1:
            printf("Codigo do funcionario a ser procurado: ");
            scanf("%d", &codigo);
            emp = sequentialSearch(codigo,file,numberOfEmployees);
            printEmployee(emp);
            system("pause");
            system("cls");
            break;
        case 2:
            printf("Codigo do funcionario a ser procurado: ");
            scanf("%d", &codigo);
            emp = searchKey(file,fileKey,codigo,99);
            printEmployee(emp);
            system("pause");
            system("cls");
            break;
        case 3:
            printf("Codigo do funcionario a ser procurado: ");
            scanf("%d", &codigo);
            emp = binarySearch(codigo,file,numberOfEmployees);
            printEmployee(emp);
            system("pause");
            system("cls");
            break;
        case 4:
            printAllKeys(fileKey,numberOfEmployees);
            system("pause");
            system("cls");
            break;
        case 5:
            printf("Saindo...");
            break;

        default:
            printf("\nOpcao invalida");
        }

    }
    while(menu!=5);






    free(emp);
    fclose(file);
    fclose(fileKey);
    return 0;
}
