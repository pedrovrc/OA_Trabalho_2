#include "arvoreB.h"

void testes() {
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

    nome = "TTT12345";
    insere_chave(&raiz, nome);

    nome = "UUU12345";
    insere_chave(&raiz, nome);

    nome = "XXX12345";
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
