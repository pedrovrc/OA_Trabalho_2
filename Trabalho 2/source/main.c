#include "arvoreB.h"

int main() {
    FILE* arq_base = fopen("registros.txt", "r");
    //no* raiz = atualiza_dados(arq_base);

    no* raiz = (no*)malloc(sizeof(no)); 
    for (int i = 0; i < ORDEM; i++) {
        raiz->filhos[i] = NULL;
    }
    raiz->pai = NULL;

    char *nome = "CCC62364";
    insere_chave(&raiz, nome);

    nome = "RRR18375";
    insere_chave(&raiz, nome);

    nome = "OOO99999";
    insere_chave(&raiz, nome);

    nome = "VVV12345";
    insere_chave(&raiz, nome);


    nome = "BBB12345";
    insere_chave(&raiz, nome);


    nome = "AAA12345";
    insere_chave(&raiz, nome);

    mostraArvore(raiz);
    return 0;
}