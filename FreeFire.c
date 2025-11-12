#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Implementa ordenação (bubble, insertion, selection), busca binária e contagem de desempenho.

// Struct Componente:
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Protótipos
void cadastrar(Componente *v, int *n);
void listar(const Componente *v, int n);
void bubbleSortNome(Componente *v, int n, int *comp);
void insertionSortTipo(Componente *v, int n, int *comp);
void selectionSortPrioridade(Componente *v, int n, int *comp);
int buscaBinariaPorNome(Componente *v, int n, const char *chave);
void trocar(Componente *a, Componente *b);

// Função principal
int main() {
    Componente componentes[20];
    int num = 0, opcao;
    int comparacoes = 0;
    clock_t inicio, fim;
    double tempo;
    int ordenadoPorNome = 0;

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Cadastrar componente\n");
        printf("2. Listar componentes\n");
        printf("3. Ordenar componentes\n");
        printf("4. Buscar por nome (binária)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            if (num < 20)
                cadastrar(componentes, &num);
            else
                printf("Mochila cheia!\n");
        }
        else if (opcao == 2) {
            listar(componentes, num);
        }
        else if (opcao == 3) {
            printf("\n1. Bubble (nome)\n2. Insertion (tipo)\n3. Selection (prioridade)\nEscolha: ");
            int met;
            scanf("%d", &met);
            getchar();
            comparacoes = 0;
            inicio = clock();
            if (met == 1) {
                bubbleSortNome(componentes, num, &comparacoes);
                ordenadoPorNome = 1;
            } else if (met == 2) {
                insertionSortTipo(componentes, num, &comparacoes);
                ordenadoPorNome = 0;
            } else if (met == 3) {
                selectionSortPrioridade(componentes, num, &comparacoes);
                ordenadoPorNome = 0;
            }
            fim = clock();
            tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            printf("Ordenado! Comparacoes: %d | Tempo: %.5f seg\n", comparacoes, tempo);
        }
        else if (opcao == 4) {
            if (!ordenadoPorNome) {
                printf("Ordene por nome antes!\n");
            } else {
                char chave[30];
                printf("Nome a buscar: ");
                fgets(chave, 30, stdin);
                chave[strcspn(chave, "\n")] = 0;
                int pos = buscaBinariaPorNome(componentes, num, chave);
                if (pos != -1)
                    printf("Encontrado: %s | Tipo: %s | Prioridade: %d\n", componentes[pos].nome, componentes[pos].tipo, componentes[pos].prioridade);
                else
                    printf("Componente nao encontrado.\n");
            }
        }

    } while (opcao != 0);

    return 0;
}

// Cadastrar item
void cadastrar(Componente *v, int *n) {
    printf("\n--- Novo componente ---\n");
    printf("Nome: ");
    fgets(v[*n].nome, 30, stdin);
    v[*n].nome[strcspn(v[*n].nome, "\n")] = 0;
    printf("Tipo: ");
    fgets(v[*n].tipo, 20, stdin);
    v[*n].tipo[strcspn(v[*n].tipo, "\n")] = 0;
    printf("Prioridade (1-10): ");
    scanf("%d", &v[*n].prioridade);
    getchar();
    (*n)++;
}

// Listar todos
void listar(const Componente *v, int n) {
    printf("\n===== COMPONENTES =====\n");
    for (int i = 0; i < n; i++)
        printf("%d. %s | %s | Prioridade: %d\n", i + 1, v[i].nome, v[i].tipo, v[i].prioridade);
}

// Trocar dados
void trocar(Componente *a, Componente *b) {
    Componente temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble sort (por nome)
void bubbleSortNome(Componente *v, int n, int *comp) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            (*comp)++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0)
                trocar(&v[j], &v[j + 1]);
        }
    }
}

// Insertion sort (por tipo)
void insertionSortTipo(Componente *v, int n, int *comp) {
    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;
        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            v[j + 1] = v[j];
            j--;
            (*comp)++;
        }
        v[j + 1] = chave;
    }
}

// Selection sort (por prioridade)
void selectionSortPrioridade(Componente *v, int n, int *comp) {
    for (int i = 0; i < n - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < n; j++) {
            (*comp)++;
            if (v[j].prioridade < v[menor].prioridade)
                menor = j;
        }
        if (menor != i)
            trocar(&v[i], &v[menor]);
    }
}

// Busca binária (por nome)
int buscaBinariaPorNome(Componente *v, int n, const char *chave) {
    int ini = 0, fim = n - 1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(chave, v[meio].nome);
        if (cmp == 0)
            return meio;
        else if (cmp > 0)
            ini = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}
