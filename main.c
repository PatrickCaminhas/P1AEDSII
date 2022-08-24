#include <stdio.h>
#include <stdlib.h>
#include "funcionarios.c"
#include "funcionarios.h"

int main()
{
        FILE *arq = fopen("funcionarios.dat", "wb+");
        FILE *arqkey = fopen("funcionariosKeys.dat", "wb+");
        if(arq==NULL)
        {
            printf("Não foi possivel abrir o arquivo! \n");
            return 1;
        }
        int nFunc= 100;
        cria_base_dados(arq,nFunc);
        TFunc *func = busca_binaria(37,arq,nFunc);

        if(func==NULL){
            printf("Funcionario nao encontrado!\n");
        }else{
            printf("[Funcionario encontrado!] \n");
            printf("- Codigo: %d \n",func->codigo);
            printf("- Nome: %s \n",func->nome);
            printf("- CPF: %s \n",func->cpf);
            printf("- Data de Nascimento: %s \n", func->data_nascimento);
            printf("- Salario: R$ %.2f", func->salario);

        }
        TFunc funciz;
        free(func);
        fclose(arq);
    return 0;
}
