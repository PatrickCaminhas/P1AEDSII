#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include "funcionarios.h"



void salva(TFunc *func, FILE *out)
{
    fwrite(&func->codigo, sizeof(int), 1, out);
    fwrite(&func->nome, sizeof(char), sizeof(func->nome), out);
    fwrite(&func->cpf, sizeof(char), sizeof(func->cpf),out);
    fwrite(&func->data_nascimento, sizeof(char), sizeof(func->data_nascimento),out);
    fwrite(&func->salario, sizeof(double),1,out);
}
void salvaKey(TKey *key, FILE *out)
{
    fwrite(&key->codigo, sizeof(int), 1, out);
    fwrite(&key->posicao, sizeof(int), 1, out);
}

TFunc *le (FILE *in)
{
    TFunc *func = (TFunc*)malloc(sizeof(TFunc));
    if(0 >= fread(&func->codigo,sizeof(int),1,in))
    {
        free(func);
        return NULL;
    }
    fread(&func->nome,sizeof(char),sizeof(func->nome),in);
    fread(&func->cpf,sizeof(char),sizeof(func->cpf),in);
    fread(&func->data_nascimento,sizeof(char),sizeof(func->data_nascimento),in);
    fread(&func->salario,sizeof(double),1,in);

    return func;
}

TKey *leKey (FILE *in)
{
    TKey *key = (TKey*)malloc(sizeof(TKey));
    if(0 >= fread(&key->codigo,sizeof(int),1,in))
    {
        free(key);
        return NULL;
    }
    fread(&key->posicao,sizeof(int),1,in);
    return key;
}

void cria_base_dados(FILE *arq, int nFunc)
{
    srand(time(NULL));
    for(int i=1; i<= nFunc; i++)
    {
            int codigo= rand() % 100;
        TFunc func;
        func.codigo = codigo;
        sprintf(func.nome,"Funcionario %d", codigo);
        sprintf(func.cpf, "111.111.111-11");
        sprintf(func.data_nascimento, "25/02/2023");
        func.salario = 1000+codigo;
        fseek(arq,(i-1)*sizeof(TFunc),SEEK_SET);
        salva(&func,arq);
    }
}

void cria_keys(FILE *arq, FILE *arqKey, int nFunc)
{
    for(int i=1; i<= nFunc; i++)
    {
        fseek(arq,i*sizeof(TFunc),SEEK_SET);
        TFunc *func = le(arq);
        TKey key;
        key.codigo= func->codigo;
        key.posicao=i;
        fseek(arqKey,(i-1)*sizeof(TKey),SEEK_SET);
        salvaKey(&key,arqKey);
    }
}

TFunc *busca_Key(FILE *arq, FILE *arqKey, int codigo, int tamanho )
{
    clock_t t;
    t = clock();
    double tempoDemorado;
    for(int i = 0; i<tamanho; i++)
    {
        fseek(arqKey,i*sizeof(TKey),SEEK_SET);
        TKey *key = leKey(arqKey);
        if(codigo==key->codigo)
        {
            fseek(arq,key->posicao*sizeof(TFunc),SEEK_SET);
            TFunc *func = le(arq);
            tempoDemorado = ((double)t)/CLOCKS_PER_SEC; // in seconds
            printf("BUSCA KEY\n");
            printf("  [Demorou %f segundos para executar] \n", tempoDemorado);
            return func;
        }
    }
    return NULL;
}


TFunc *busca_binaria(int codigo, FILE *arq, int tamanho)
{
    int left = 0, right = tamanho-1;
    int contador=0;
    clock_t t;
    t = clock();
    double tempoDemorado;
    while(left <= right)
    {

        int middle = (left+right)/2;
        fseek(arq,middle*sizeof(TFunc),SEEK_SET);
        TFunc *func = le(arq);
        if(codigo==func->codigo)
        {
            t = clock() - t;
            tempoDemorado = ((double)t)/CLOCKS_PER_SEC; // in seconds
            printf("BUSCA BINARIA\n");
            printf("  [Demorou %f segundos para executar] \n", tempoDemorado);
            printf("  [Numero de comparacoes: %d] \n", contador);
            return func;
        }

        else if(func->codigo<codigo)
        {
            left = middle+1;
        }

        else
        {
            right = middle-1;
        }
        contador++;
    }
    t = clock() - t;
    tempoDemorado = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("BUSCA BINARIA\n");
    printf("  [Demorou %f segundos para executar] \n", tempoDemorado);
    printf("  [Numero de comparacoes: %d] \n", contador);
    return NULL;
}

TFunc *busca_sequencial(int codigo, FILE *arq, int tamanho)
{
    int i;
    clock_t t;
    t = clock();
    double tempoDemorado;
    for(i=1; i<=tamanho; i++)
    {
        fseek(arq,i*sizeof(TFunc),SEEK_SET);
        TFunc *func = le(arq);
        if(codigo==func->codigo)
        {

            t = clock() - t;
            tempoDemorado = ((double)t)/CLOCKS_PER_SEC;
            printf("BUSCA SEQUENCIAL\n");
            printf("  [Demorou %f segundos para executar] \n", tempoDemorado);
            printf("  [Numero de comparacoes: %d] \n", i);
            return func;
        }
    }
    t = clock() - t;
    tempoDemorado = ((double)t)/CLOCKS_PER_SEC;
    printf("BUSCA SEQUENCIAL\n");
    printf("  [Demorou %f segundos para executar] \n", tempoDemorado);
    printf("  [Numero de comparações: %d] \n", i);
    return NULL;

}

void imprimir(TFunc * func)
{
    if(func==NULL)
    {
        printf("Funcionario nao encontrado!\n");
    }
    else
    {
        printf("[Funcionario encontrado!] \n");
        printf("- Codigo: %d \n",func->codigo);
        printf("- Nome: %s \n",func->nome);
        printf("- CPF: %s \n",func->cpf);
        printf("- Data de Nascimento: %s \n", func->data_nascimento);
        printf("- Salario: R$ %.2f\n\n", func->salario);
    }
}
