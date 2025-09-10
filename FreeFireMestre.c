#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade; // 1 a 5
} Item;

typedef enum {
    NAO_ORDENADO,
    ORDENADO_NOME,
    ORDENADO_TIPO,
    ORDENADO_PRIORIDADE
} CriterioOrdenacao;

void insertionSort(Item mochila[], int total, CriterioOrdenacao criterio, int *comparacoes) {
    int i, j;
    Item chave;
    *comparacoes = 0;

    for (i = 1; i < total; i++) {
        chave = mochila[i];
        j = i - 1;

        while (j >= 0) {
            (*comparacoes)++;
            int cmp = 0;
            if (criterio == ORDENADO_NOME)
                cmp = strcmp(mochila[j].nome, chave.nome);
            else if (criterio == ORDENADO_TIPO)
                cmp = strcmp(mochila[j].tipo, chave.tipo);
            else if (criterio == ORDENADO_PRIORIDADE)
                cmp = mochila[j].prioridade - chave.prioridade;

            if (cmp > 0) {
                mochila[j + 1] = mochila[j];
                j--;
            } else {
                break;
            }
        }
        mochila[j + 1] = chave;
    }
}

int buscaBinaria(Item mochila[], int total, char nomeBusca[]) {
    int esquerda = 0, direita = total - 1, meio;
    while (esquerda <= direita) {
        meio = (esquerda + direita) / 2;
        int cmp = strcmp(mochila[meio].nome, nomeBusca);
        if (cmp == 0) {
            return meio;
        } else if (cmp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return -1; // não encontrado
}

int main() {
    Item mochila[MAX_ITENS];
    int total = 0, opcao;
    CriterioOrdenacao estadoOrdenacao = NAO_ORDENADO;

    do {
        printf("\n===== MENU MOCHILA =====\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Ordenar itens\n");
        printf("5 - Buscar item por nome (Binária)\n");
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
                    do {
                        printf("Prioridade (1 a 5): ");
                        scanf("%d", &mochila[total].prioridade);
                    } while (mochila[total].prioridade < 1 || mochila[total].prioridade > 5);
                    total++;
                    estadoOrdenacao = NAO_ORDENADO;
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
                        estadoOrdenacao = NAO_ORDENADO;
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
                    printf("%-20s %-15s %-10s %-10s\n", "Nome", "Tipo", "Quantidade", "Prioridade");
                    for (i = 0; i < total; i++) {
                        printf("%-20s %-15s %-10d %-10d\n",
                               mochila[i].nome,
                               mochila[i].tipo,
                               mochila[i].quantidade,
                               mochila[i].prioridade);
                    }
                }
                break;

            case 4: { // Ordenar itens
                int criterio, comparacoes;
                printf("Ordenar por:\n");
                printf("1 - Nome\n");
                printf("2 - Tipo\n");
                printf("3 - Prioridade\n");
                printf("Escolha: ");
                scanf("%d", &criterio);

                if (criterio == 1) {
                    insertionSort(mochila, total, ORDENADO_NOME, &comparacoes);
                    estadoOrdenacao = ORDENADO_NOME;
                } else if (criterio == 2) {
                    insertionSort(mochila, total, ORDENADO_TIPO, &comparacoes);
                    estadoOrdenacao = ORDENADO_TIPO;
                } else if (criterio == 3) {
                    insertionSort(mochila, total, ORDENADO_PRIORIDADE, &comparacoes);
                    estadoOrdenacao = ORDENADO_PRIORIDADE;
                } else {
                    printf("Opcao invalida!\n");
                    break;
                }
                printf("Mochila ordenada com sucesso! Comparacoes: %d\n", comparacoes);
                break;
            }

            case 5: { // Busca binária
                if (estadoOrdenacao != ORDENADO_NOME) {
                    printf("A busca binaria exige que a mochila esteja ordenada por nome!\n");
                    break;
                }
                char nomeBusca[30];
                printf("Digite o nome do item para buscar: ");
                scanf(" %[^\n]", nomeBusca);

                int pos = buscaBinaria(mochila, total, nomeBusca);
                if (pos != -1) {
                    printf("\nItem encontrado!\n");
                    printf("Nome: %s\n", mochila[pos].nome);
                    printf("Tipo: %s\n", mochila[pos].tipo);
                    printf("Quantidade: %d\n", mochila[pos].quantidade);
                    printf("Prioridade: %d\n", mochila[pos].prioridade);
                } else {
                    printf("Item nao encontrado!\n");
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
