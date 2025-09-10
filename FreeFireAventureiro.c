#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

int main() {
    Item mochila[MAX_ITENS];
    int total = 0, opcao;

    do {
        printf("\n===== MENU MOCHILA =====\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item por nome\n"); // NOVA OPÇÃO
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // Adicionar item
                if (total < MAX_ITENS) {
                    printf("Nome do item: ");
                    scanf(" %[^\n]", mochila[total].nome);
                    printf("Tipo do item: ");
                    scanf(" %[^\n]", mochila[total].tipo);
                    printf("Quantidade: ");
                    scanf("%d", &mochila[total].quantidade);
                    total++;
                } else {
                    printf("Mochila cheia!\n");
                }
                break;

            case 2: { // Remover item
                char nomeRemover[30];
                int i, j, encontrado = 0;
                printf("Nome do item para remover: ");
                scanf(" %[^\n]", nomeRemover);

                for (i = 0; i < total; i++) {
                    if (strcmp(mochila[i].nome, nomeRemover) == 0) {
                        for (j = i; j < total - 1; j++) {
                            mochila[j] = mochila[j + 1];
                        }
                        total--;
                        encontrado = 1;
                        printf("Item removido!\n");
                        break;
                    }
                }
                if (!encontrado) {
                    printf("Item nao encontrado!\n");
                }
                break;
            }

            case 3: // Listar itens
                if (total == 0) {
                    printf("Mochila vazia!\n");
                } else {
                    int i;
                    printf("\n--- Itens na Mochila ---\n");
                    printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Quantidade");
                    for (i = 0; i < total; i++) {
                        printf("%-20s %-15s %-10d\n",
                               mochila[i].nome,
                               mochila[i].tipo,
                               mochila[i].quantidade);
                    }
                }
                break;

            case 4: { // Buscar item por nome
                char nomeBusca[30];
                int i, encontrado = 0;
                printf("Digite o nome do item para buscar: ");
                scanf(" %[^\n]", nomeBusca);

                for (i = 0; i < total; i++) {
                    if (strcmp(mochila[i].nome, nomeBusca) == 0) {
                        printf("\nItem encontrado!\n");
                        printf("Nome: %s\n", mochila[i].nome);
                        printf("Tipo: %s\n", mochila[i].tipo);
                        printf("Quantidade: %d\n", mochila[i].quantidade);
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {
                    printf("Item nao encontrado na mochila!\n");
                }
                break;
            }

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
