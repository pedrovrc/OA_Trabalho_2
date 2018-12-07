#include "arvoreB.h"

int insere_chave (no **raiz, char* chave) {
    no* pNo = busca_no (*raiz, chave);
    char lista[ORDEM][TAM_CHAVE];
    int changes[ORDEM];

    for (int i = 0; i < ORDEM; i++) {
        changes[i] = i;
    }

    if (pNo == NULL) {
        printf("falha ao inserir\n");
        return -1;
    }

    if (pNo->qtd_chaves < ORDEM-1) {
        for (int i = 0; i < TAM_CHAVE; i++) {
            pNo->chaves[pNo->qtd_chaves][i] = chave[i];
        }
        pNo->qtd_chaves++;
        insertionSort(pNo->chaves, pNo->qtd_chaves, changes);
        //ordena_ponteiros(pNo, pNo->qtd_chaves, changes);
    } else {
        for (int i = 0; i < pNo->qtd_chaves; i++) {
            for (int j = 0; j < TAM_CHAVE; j++) {    
                lista[i][j] = pNo->chaves[i][j];
            }    
        }
        for (int i = 0; i < TAM_CHAVE; i++) {    
            lista[pNo->qtd_chaves][i] = chave[i];
            pNo->chaves[pNo->qtd_chaves][i] = chave[i];
        }
        pNo->filhos[pNo->qtd_chaves+1] = NULL;
        insertionSort(lista, pNo->qtd_chaves+1, changes); 
        //ordena_ponteiros(pNo, pNo->qtd_chaves, changes);
        promove(raiz, pNo, lista, pNo->qtd_chaves+1, changes);
    }
}

void promove (no **raiz, no *pNo, char lista[ORDEM][TAM_CHAVE], int qtd_lista, int changes[ORDEM]) {

    // Acha meio
    int meio = ceil(qtd_lista/2);
    if (qtd_lista%2 == 0) {
        meio++;
    }

    // Cria e preenche elemento divisor
    char elemento_div[TAM_CHAVE];
    
    for (int i = 0; i < TAM_CHAVE; i++) {
        elemento_div[i] = lista[meio-1][i];    
    }

    // Cria no irmao e atualiza chaves
    no *pNovo = (no*)malloc(sizeof(no));

    for(int i = 0; i < meio-1; i++) { 
        for (int j = 0; j < TAM_CHAVE; j++) {
            pNo->chaves[i][j] = lista[i][j];
        }
    }

    for (int i = meio; i < qtd_lista; i++) {
        for (int j = 0; j < TAM_CHAVE; j++) {
            pNovo->chaves[i-meio][j] = lista[i][j];
        }        
    }

    // "Carrega" ponteiros de filhos
    int cont = 0;
    for (int i = 0; i <= qtd_lista; i++) {
        if (meio+i <= qtd_lista) {
            pNovo->filhos[i] = pNo->filhos[meio + i];
        } else {
            pNovo->filhos[i] = NULL;
        }
    }
    for (int i = 0; (meio+i) <= ORDEM; i++) {
        pNo->filhos[meio + i] = NULL;
        cont++;
    }

    // Atualiza quantidades
    pNo->qtd_chaves = ORDEM-cont;
    pNovo->qtd_chaves = cont-1;

    // Cria novo pai caso nao exista ainda
    if (pNo->pai == NULL) {
        no *pPai = (no*)malloc(sizeof(no));
        *raiz = pPai;
        for (int i = 0; i < TAM_CHAVE; i++) {
            pPai->chaves[0][i] = elemento_div[i];    
        }
        for (int i = 0; i < ORDEM; i++) {
            pPai->filhos[i] = NULL;    
        }
        pPai->filhos[0] = pNo;
        pPai->filhos[1] = pNovo;
        pNovo->pai = pPai;
        pNo->pai = pPai;
        pPai->qtd_chaves = 1;
    } else {

        // Se tiver espaco, simplesmente insere
        if (pNo->pai->qtd_chaves < ORDEM-1) {
            
            for (int i = 0; i < TAM_CHAVE; i++) {
                pNo->pai->chaves[pNo->pai->qtd_chaves][i] = elemento_div[i];
            }

            char no_original[TAM_CHAVE];
            char no_novo[TAM_CHAVE];
            strcpy(no_original, pNo->pai->filhos[pNo->pai->qtd_chaves]->chaves[0]);
            strcpy(no_novo, pNovo->chaves[0]);

            no* maior;
            no* menor;

            int situacao = strcmp(no_original, no_novo);

            if (situacao > 0) {
                maior = pNo->pai->filhos[pNo->pai->qtd_chaves];
                menor = pNovo;
            } else {
                maior = pNovo;
                menor = pNo->pai->filhos[pNo->pai->qtd_chaves];
            }

            pNo->pai->filhos[pNo->pai->qtd_chaves+1] = maior;
            pNo->pai->filhos[pNo->pai->qtd_chaves] = menor;

            pNovo->pai = pNo->pai;
            pNo->pai->qtd_chaves++;

            // inserir pNovo no array filhos do pai
            pNo->pai->filhos[pNo->pai->qtd_chaves+1] = pNovo;
            ordena_ponteiros(pNo->pai, pNo->pai->qtd_chaves+1);

            insertionSort(pNo->pai->chaves, pNo->pai->qtd_chaves, changes);
            //ordena_ponteiros(pNo->pai, pNo->pai->qtd_chaves, changes);

        // Se nao tiver espaco, passa elemento divisor para cima e promove    
        } else {
            for (int i = 0; i < pNo->pai->qtd_chaves; i++) {
                for (int j = 0; j < TAM_CHAVE; j++) {
                    lista[i][j] = pNo->pai->chaves[i][j];    
                }
            }
            for (int i = 0; i < TAM_CHAVE; i++) {
                lista[pNo->pai->qtd_chaves][i] = elemento_div[i];
            }
            insertionSort(lista, pNo->pai->qtd_chaves+1, changes);
            //ordena_ponteiros(pNo->pai, pNo->pai->qtd_chaves, changes);

            // inserir pNovo no array filhos do pai
            pNo->pai->filhos[pNo->pai->qtd_chaves+1] = pNovo;
            ordena_ponteiros(pNo->pai, ORDEM+1);

            promove(raiz, pNo->pai, lista, pNo->pai->qtd_chaves+1, changes);
        }
    }
}

no* busca_no (no *no_recebido, char* chave) {
    no* aux = no_recebido;
    int situacao;
    int i;

    for (i = 0; i < aux->qtd_chaves; i++) {
        situacao = strcmp(aux->chaves[i], chave);
        if (situacao < 0) {
            continue;
        } else if (situacao == 0) {
            printf("elemento ja existe\n");
            return NULL;
        } else if (situacao > 0) {
            if (aux->filhos[i] == NULL) {
                return aux;
            }
            return busca_no (aux->filhos[i], chave);
        }
    }
    if (aux->filhos[i] == NULL) {
        return aux;
    }
    return busca_no (aux->filhos[i], chave);
}

void insertionSort(char array[ORDEM][TAM_CHAVE], int n, int changes[ORDEM]) { 
    int i, j; 
    char chave[TAM_CHAVE];
    int chave_changes;
    for (i = 1; i < n; i++) {
        for (int j = 0; j < TAM_CHAVE; j++) { 
            chave[j] = array[i][j];
        }
        chave_changes = changes[i];
        j = i-1; 

        while (j >= 0 && strcmp(array[j], chave) > 0) { 
            for (int k = 0; k < TAM_CHAVE; k++) {
                array[j+1][k] = array[j][k]; 
            }
            changes[j+1] = changes[j];
            j = j-1; 
        }
        for (int k = 0; k < TAM_CHAVE; k++) {
            array[j+1][k] = chave[k]; 
        }
        changes[j+1] = chave_changes;
    }
}

/*
void ordena_ponteiros(no *pNo, int n, int changes[ORDEM+1]) {
    int i, j; 
    int chave_changes;
    no *aux;
    for (i = 1; i < n; i++) {
        chave_changes = changes[i];
        aux = pNo->filhos[i];
        j = i-1;

        while (j >= 0 && changes[j] > chave_changes) { 
            changes[j+1] = changes[j];
            pNo->filhos[j+1] = pNo->filhos[j];
            j = j-1; 
        }
        changes[j+1] = chave_changes;
        pNo->filhos[j+1] = aux;
    }
}
*/

void ordena_ponteiros(no* pNoPai, int n) { 
    for (int i = 0; i < pNoPai->qtd_chaves+1; i++) {
        printf("%s ", pNoPai->filhos[i]->chaves[0]);
    }
    printf("\n");

    int i, j;
    no* aux;
    for (i = 1; i < n; i++) {
        j = i-1; 
        aux = pNoPai->filhos[i];

        while (j >= 0 && strcmp(pNoPai->filhos[j]->chaves[0], aux->chaves[0]) > 0) { 
            pNoPai->filhos[j+1] = pNoPai->filhos[j];
            j = j-1; 
        }
        pNoPai->filhos[j+1] = aux;
    }

    for (int i = 0; i < pNoPai->qtd_chaves+1; i++) {
        printf("%s ", pNoPai->filhos[i]->chaves[0]);
    }
    printf("\n\n\n");
}
