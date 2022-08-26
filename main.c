#include <stdio.h>
#include <stdlib.h>
#include "funcionarios.c"
#include "funcionarios.h"

int main()
{

    FILE *arq = fopen("funcionarios.dat", "wb+");
    FILE *arqKey = fopen("funcionariosKeys.dat", "wb+");
    if(arq==NULL)
    {
        printf("Não foi possivel abrir o arquivo! \n");
        return 1;
    }
    if(arqKey==NULL)
    {
        printf("Não foi possivel abrir o arquivo! \n");
        return 1;
    }
    int nFunc= 100;
    cria_base_dados(arq,nFunc);

    TFunc *func = busca_sequencial(2,arq,nFunc);
    imprimir(func);
    func = busca_binaria(2,arq,nFunc);
    imprimir(func);
    cria_keys(arq,arqKey,99);

    func = busca_Key(arq,arqKey,2,99);

    imprimir(func);
    free(func);
    fclose(arq);
    return 0;
}
