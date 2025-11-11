#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Código da Ilha – Edição Free Fire
// Nível: Aventureiro
// Este programa evolui o sistema básico de mochila, agora utilizando listas encadeadas.
// O jogador pode adicionar, remover, listar e buscar itens dinamicamente.

// --- Estrutura de Dados ---
typedef struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
    struct Item* prox;
} Item;

// --- Protótipos das Funções ---
Item* inserirItem(Item* inicio);
Item* removerItem(Item* inicio);
void listarItens(Item* inicio);
void buscarItem(Item* inicio);
void liberarMemoria(Item* inicio);

// --- Função Principal ---
int main() {
    Item* inicio = NULL;
    int opcao;

    do {
        printf("\n===== MOCHILA DE SOBREVIVÊNCIA (DINÂMICA) =====\n");
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
                inicio = inserirItem(inicio);
                listarItens(inicio);
                break;
            case 2:
                inicio = removerItem(inicio);
                listarItens(inicio);
                break;
            case 3:
                listarItens(inicio);
                break;
            case 4:
                buscarItem(inicio);
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    liberarMemoria(inicio);
    return 0;
}

// --- Implementação das Funções ---

Item* inserirItem(Item* inicio) {
    Item* novo = (Item*)malloc(sizeof(Item));
    if (!novo) {
        printf("Erro de memória!\n");
        return inicio;
    }

    printf("Nome do item: ");
    fgets(novo->nome, sizeof(novo->nome), stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0';
    printf("Tipo do item: ");
    fgets(novo->tipo, sizeof(novo->tipo), stdin);
    novo->tipo[strcspn(novo->tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novo->quantidade);
    getchar();

    novo->prox = inicio;
    printf("Item adicionado!\n");
    return novo;
}

Item* removerItem(Item* inicio) {
    if (inicio == NULL) {
        printf("A mochila está vazia!\n");
        return inicio;
    }

    char nomeRemover[30];
    printf("Digite o nome do item para remover: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    Item* atual = inicio;
    Item* anterior = NULL;

    while (atual != NULL && strcmp(atual->nome, nomeRemover) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Item não encontrado.\n");
        return inicio;
    }

    if (anterior == NULL) {
        inicio = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    printf("Item removido!\n");
    return inicio;
}

void listarItens(Item* inicio) {
    if (inicio == NULL) {
        printf("A mochila está vazia!\n");
        return;
    }

    printf("\n===== ITENS NA MOCHILA =====\n");
    Item* atual = inicio;
    int i = 1;
    while (atual != NULL) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i, atual->nome, atual->tipo, atual->quantidade);
        atual = atual->prox;
        i++;
    }
}

void buscarItem(Item* inicio) {
    if (inicio == NULL) {
        printf("A mochila está vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item para buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    Item* atual = inicio;
    while (atual != NULL) {
        if (strcmp(atual->nome, nomeBusca) == 0) {
            printf("Item encontrado!\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\n",
                   atual->nome, atual->tipo, atual->quantidade);
            return;
        }
        atual = atual->prox;
    }

    printf("Item não encontrado.\n");
}

void liberarMemoria(Item* inicio) {
    Item* temp;
    while (inicio != NULL) {
        temp = inicio;
        inicio = inicio->prox;
        free(temp);
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
