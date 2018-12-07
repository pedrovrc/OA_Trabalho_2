#include "arvoreB.h"

void testes() {
    no* raiz = (no*)malloc(sizeof(no)); 
    for (int i = 0; i < ORDEM; i++) {
        raiz->filhos[i] = NULL;
    }
    raiz->pai = NULL;

    char *nome = "C";
    insere_chave(&raiz, nome);

    nome = "D";
    insere_chave(&raiz, nome);

    nome = "S";
    insere_chave(&raiz, nome);

    nome = "T";
    insere_chave(&raiz, nome);

    nome = "A";
    insere_chave(&raiz, nome);

    nome = "M";
    insere_chave(&raiz, nome);

    nome = "P";
    insere_chave(&raiz, nome);

    nome = "I";
    insere_chave(&raiz, nome);

    nome = "B";
    insere_chave(&raiz, nome);

    nome = "W";
    insere_chave(&raiz, nome);

    nome = "N";
    insere_chave(&raiz, nome);

    nome = "G";
    insere_chave(&raiz, nome);

    nome = "U";
    insere_chave(&raiz, nome);

    nome = "R";
    insere_chave(&raiz, nome);

    nome = "K";
    insere_chave(&raiz, nome);

    mostraArvore(raiz, 0);
    return;
}

void dados_arq() {
    FILE* arq_base = fopen("registros.txt", "r");
    no* raiz = atualiza_dados(arq_base);
    fclose(arq_base);
    return;
}

void limpa_buffer(){
    int n;
    while((n = getchar()) != EOF && n != '\n');
}

int main() {
    int opcao = 5;

    do {
        printf("\n\tOrganização de registros em B-Tree\n\n");
        printf ("O que deseja fazer?\n\n");
        printf("1 - Executar testes\n");
        printf("2 - Carregar base de dados em 'registros.txt'\n");
        printf("3 - Fechar\n");

        while (opcao == 5) {
            scanf("%d", &opcao);
            limpa_buffer();
            if (opcao == 5) {
                printf("Entrada invalida.\n");
            }
            printf("\n\n");
        }

        switch(opcao) {
            case 1:     // Executar testes
                testes();
                opcao = -1;
                break;

            case 2:     // Carregar registros.txt
                dados_arq();
                opcao = -1;
                break;

            case 3:     // Sair
                opcao = -1;
                break;

            default:
                printf("Entrada invalida\n");
                opcao = 5;
        }
    } while (opcao > 0);
    return 0;
}
