#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


#define ORDEM 4
#define TAM_CHAVE 10

typedef struct No{
   int qtd_chaves; //Quantidades de chaves contida no nó
   int prr[ORDEM];
   char chaves[ORDEM][TAM_CHAVE]; //Chaves armazenadas no nó
   struct No *filhos[ORDEM+1]; //Ponteiro para os filhos
   struct No *pai;
}no;

int insere_chave (no **raiz, char* chave);

void promove (no **raiz, no *pNo, char lista[ORDEM][TAM_CHAVE], int qtd_lista, int changes[ORDEM]);

no* busca_no (no *no_recebido, char* chave);

int compara_string(char* string1, char* string2);

void insertionSort(char array[ORDEM][TAM_CHAVE], int n, int changes[ORDEM]);

void ordena_ponteiros(no *pNo, int n, int changes[ORDEM]);

no* atualiza_dados(FILE* arq_base);

void mostraArvore(no* NoAtual);

void imprimeNo(char *nome);








