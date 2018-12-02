# include "arvoreB.h"

#define TAM_REG 60
#define CAMPO_1 41

no* atualiza_dados(FILE* arq_base) {
	no* raiz = (no*)malloc(sizeof(no)); 
    raiz->qtd_chaves = 0;
    for (int i = 0; i < ORDEM; i++) {
        raiz->filhos[i] = NULL;
    }
    raiz->pai = NULL;

    char linha_atual[TAM_REG];
    char registro[TAM_CHAVE];

    while (fgets(linha_atual, TAM_REG, arq_base) != NULL) {
    	for (int i = 0; i < 3; i++) {
    		registro[i] = linha_atual[i];
    	}
    	for (int i = 0; i < 5; i++) {
    		registro[i + 3] = linha_atual[CAMPO_1 + i];
    	}
    	registro[8] = '\0';
    	//printf("%s\n", registro);

    	insere_chave(&raiz, registro);
    }
    return raiz;
}

void imprimeNo(char *nome) {
    int i;
    printf("%s\n", nome);
}

void mostraArvore(no* NoAtual) {
    int i;
    if (NoAtual == NULL) {
        //imprimeNo("*");
        return;
    }
    for (i = 0; i < NoAtual->qtd_chaves; i++) {
        mostraArvore(NoAtual->filhos[i]);
        imprimeNo(NoAtual->chaves[i]);
    }
    mostraArvore(NoAtual->filhos[i]);
}
