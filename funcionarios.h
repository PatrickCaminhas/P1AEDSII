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
void salvaKey(TKey *key, FILE *out);
TFunc *le (FILE *in);
TKey *leKey (FILE *in);
void cria_base_dados(FILE *arq, int nFunc);
void cria_keys(FILE *arq, FILE *arqKey, int nFunc);
TFunc *busca_Key(FILE *arq, FILE *arqKey, int codigo, int nFunc );
TFunc *busca_binaria(int codigo, FILE *arq, int tamanho);
TFunc *busca_sequencial(int codigo, FILE *arq, int tamanho);
void imprimir(TFunc * func);

#endif // FUNCIONARIOS_H_INCLUDED
