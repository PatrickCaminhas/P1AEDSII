#include <stdlib.h>
#include <string.h>
#include "funcionarios.h"

void salva(TFunc * func, FILE *out)
{
    fwrite(&func->codigo, sizeof(int), 1, out);
    fwrite(&func->nome, sizeof(char), sizeof(func->nome), out);
    fwrite(&func->cpf, sizeof(char), sizeof(func->cpf),out);
    fwrite(&func->data_nascimento, sizeof(char), sizeof(func->data_nascimento),out);
    fwrite(&func->salario, sizeof(double),1,out);
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

void cria_base_dados(FILE *arq, int nFunc)
{
    for(int i=1; i<= nFunc; i++)
    {
        TFunc func;
        func.codigo = i;
        sprintf(func.nome,"Funcionario %d", i);
        sprintf(func.cpf, "111.111.111-111");
        sprintf(func.data_nascimento, "25/02/2023");
        func.salario = 1000+i;
        fseek(arq,(i-1)*sizeof(TFunc),SEEK_SET);
        salva(&func,arq);
    }
}

void cria_keys(FILE *arq, FILE *arqKey, int nFunc)
{
    for(int i=1; i<= nFunc; i++)
    {
        TKey key;
        key.codigo=i;
        key.posicao=i;
    }
}

TFunc *busca_Key(FILE *arq, FILE *arqKey, int codigo, int tamanho )
{
    TFunc func = busca_sequencial(codigo,arq,tam);
    fseek(arq,middle*sizeof(TFunc),SEEK_SET);
    return le(arq);
}


TFunc *busca_binaria(int codigo, FILE *arq, int tamanho)
{
    int left = 0, right = tamanho-1;
    int contador=0;
    while(left <= right)
    {

        int middle = (left+right)/2;
        fseek(arq,middle*sizeof(TFunc),SEEK_SET);
        TFunc *func = le(arq);
        if(codigo==func->codigo)
        {
            printf("Numero de comparacoes: %d \n", contador);
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
    printf("Numero de comparacoes: %d \n", contador);
    return NULL;
}

TFunc *busca_sequencial(int codigo, FILE *arq, int tamanho)
{
    int i;
    for(i=0; i<tamanho; i++)
    {
        fseek(arq,i*sizeof(TFunc),SEEK_SET);
        TFunc *func = le(arq);
        if(codigo==func->codigo)
        {
            printf("Numero de comparacoes: %d \n", i);
            return func;
        }
    }
    printf("Numero de comparações: %d \n", i);
    return NULL;

}

TFunc *ordernarKeySorting(int codigo, FILE *arq, int tamanho)
{
    int i=0;
    for(int i=0; i<tamanho; i++)
    {

    }
}

