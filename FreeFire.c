#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Código da Ilha – Edição Free Fire
// Nível: Novato
// Este programa simula o gerenciamento básico de uma mochila com itens coletados na ilha.
// O jogador pode adicionar, remover, listar e buscar itens de forma simples.

// --- Estrutura de Dados ---
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// --- Protótipos das Funções ---
void inserirItem(Item mochila[], int *numItens);
void removerItem(Item mochila[], int *numItens);
void listarItens(Item mochila[], int numItens);
void buscarItem(Item mochila[], int numItens);

// --- Função Principal ---
int main() {
    Item mochila[10];
    int numItens = 0;
    int opcao;

    do {
        printf("\n===== MOCHILA DE SOBREVIVÊNCIA =====\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                inserirItem(mochila, &numItens);
                listarItens(mochila, numItens);
                break;
            case 2:
                removerItem(mochila, &numItens);
                listarItens(mochila, numItens);
                break;
            case 3:
                listarItens(mochila, numItens);
                break;
            case 4:
                buscarItem(mochila, numItens);
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}

// --- Implementação das Funções ---

void inserirItem(Item mochila[], int *numItens) {
    if (*numItens >= 10) {
        printf("A mochila está cheia!\n");
        return;
    }

    Item novo;
    printf("Nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';
    printf("Tipo do item: ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*numItens] = novo;
    (*numItens)++;
    printf("Item adicionado!\n");
}

void removerItem(Item mochila[], int *numItens) {
    if (*numItens == 0) {
        printf("A mochila está vazia!\n");
        return;
    }

    char nomeRemover[30];
    printf("Digite o nome do item para remover: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < *numItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            for (int j = i; j < *numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*numItens)--;
            encontrado = 1;
            printf("Item removido!\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Item não encontrado.\n");
    }
}

void listarItens(Item mochila[], int numItens) {
    if (numItens == 0) {
        printf("A mochila está vazia!\n");
        return;
    }

    printf("\n===== ITENS NA MOCHILA =====\n");
    for (int i = 0; i < numItens; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

void buscarItem(Item mochila[], int numItens) {
    if (numItens == 0) {
        printf("A mochila está vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item para buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int achou = 0;
    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("Item encontrado!\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            achou = 1;
            break;
        }
    }
    if (!achou) {
        printf("Item não encontrado.\n");
    }
}

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
