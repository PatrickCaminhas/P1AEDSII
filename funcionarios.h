#ifndef FUNCIONARIOS_H_INCLUDED
#define FUNCIONARIOS_H_INCLUDED
#include <stdio.h>

typedef struct Funcionario{
int codigo;
char nome [50];
char cpf[15];
char data_nascimento[11];
double salario;
} TFunc;

typedef struct FuncionarioKey{
int posicao;
char codigo;
}TKey;

void salva(TFunc *func, FILE *out);
TFunc *le (FILE *in);
void cria_base_dados(FILE *arq, int nFunc);
TFunc *busca_binaria(int codigo, FILE *arq, int tamanho);
TFunc *busca_sequencial(int codigo, FILE *arq, int tamanho)


#endif // FUNCIONARIOS_H_INCLUDED
