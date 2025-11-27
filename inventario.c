#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Necessário para a função clock()

// --- Constantes ---
#define MAX_COMPONENTES 5 // Capacidade reduzida para testes mais rápidos
#define CHAVE_BUSCA "Chip Central" // Nome do componente-chave para a busca binária

// --- Struct ---

/**
 * @brief Estrutura que representa um componente da torre de fuga.
 * * Armazena nome, tipo e prioridade.
 */
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// --- Variáveis Globais de Controle ---

Componente componentes[MAX_COMPONENTES];
int totalComponentes = 0;

// --- Protótipos das Funções ---

// Entrada/Saída
void cadastrarComponentes();
void mostrarComponentes(const Componente lista[], int tamanho);
void exibirMenuPrincipal();

// Algoritmos de Ordenação (Retornam o número de comparações)
long long bubbleSortNome(Componente lista[], int tamanho);
long long insertionSortTipo(Componente lista[], int tamanho);
long long selectionSortPrioridade(Componente lista[], int tamanho);

// Busca
int buscaBinariaPorNome(const Componente lista[], int tamanho, const char chave[], long long *comparacoes);

// Auxiliares
void copiarComponentes(const Componente origem[], Componente destino[], int tamanho);
void trocar(Componente *a, Componente *b);


// --- Main (Função Principal) ---

int main() {
    int opcao;
    
    printf("🗼 Módulo de Organização de Componentes - Nível Mestre 🗼\n");
    printf("========================================================\n");
    
    // 1. Cadastro dos dados iniciais
    cadastrarComponentes();

    do {
        // Limpa a tela e exibe o menu interativo
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
            
        exibirMenuPrincipal();
        printf("➡️ Digite sua opção de Estratégia: ");
        if (scanf("%d", &opcao) != 1) { opcao = -1; }
        while (getchar() != '\n');

        if (totalComponentes == 0 && opcao != 0) {
            printf("\n🚫 Cadastre os componentes primeiro (Opção 1).\n");
            opcao = -1;
        }

        Componente tempLista[MAX_COMPONENTES]; // Lista temporária para ordenação
        long long comparacoes = 0;
        clock_t inicio, fim;
        double tempo_execucao;
        int indiceChave;

        if (opcao >= 2 && opcao <= 4) {
            // Copia os dados originais para a lista temporária antes de ordenar
            copiarComponentes(componentes, tempLista, totalComponentes);
        }

        switch (opcao) {
            case 1:
                // Já executado no início do main, mas permite recarregar.
                cadastrarComponentes(); 
                break;
                
            case 2: // Bubble Sort (Nome)
                printf("\nEstratégia Escolhida: Ordenar por Nome (Bubble Sort)\n");
                inicio = clock();
                comparacoes = bubbleSortNome(tempLista, totalComponentes);
                fim = clock();
                printf("✅ Montagem final ORDENADA por NOME (Bubble Sort):\n");
                mostrarComponentes(tempLista, totalComponentes);
                
                // Verifica a busca binária após a ordenação por nome
                indiceChave = buscaBinariaPorNome(tempLista, totalComponentes, CHAVE_BUSCA, &comparacoes);
                if (indiceChave != -1) {
                    printf("\n🔑 CHIP CENTRAL ENCONTRADO! Posição após ordenação: %d.\n", indiceChave + 1);
                } else {
                    printf("\n❌ Componente-chave '%s' NÃO encontrado.\n", CHAVE_BUSCA);
                }
                
                break;

            case 3: // Insertion Sort (Tipo)
                printf("\nEstratégia Escolhida: Ordenar por Tipo (Insertion Sort)\n");
                inicio = clock();
                comparacoes = insertionSortTipo(tempLista, totalComponentes);
                fim = clock();
                printf("✅ Montagem final ORDENADA por TIPO (Insertion Sort):\n");
                mostrarComponentes(tempLista, totalComponentes);
                break;
                
            case 4: // Selection Sort (Prioridade)
                printf("\nEstratégia Escolhida: Ordenar por Prioridade (Selection Sort)\n");
                inicio = clock();
                comparacoes = selectionSortPrioridade(tempLista, totalComponentes);
                fim = clock();
                printf("✅ Montagem final ORDENADA por PRIORIDADE (Selection Sort):\n");
                mostrarComponentes(tempLista, totalComponentes);
                break;
                
            case 0:
                printf("\n👋 Fim do Módulo de Organização. Boa Sorte na Fuga!\n");
                break;

            default:
                printf("\n⚠️ Opção inválida. Tente novamente.\n");
                break;
        }
        
        // Exibição do Desempenho (Requisito Educacional)
        if (opcao >= 2 && opcao <= 4) {
            tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
            printf("\n--- ANÁLISE DE DESEMPENHO ---\n");
            printf("📊 Comparações totais: %lld\n", comparacoes);
            printf("⏱️ Tempo de execução: %.6f segundos\n", tempo_execucao);
            printf("-----------------------------\n");
        }

        if (opcao != 0) {
            printf("\nPressione ENTER para voltar ao menu...");
            getchar();
        }

    } while (opcao != 0);

    return 0;
}

// -------------------------------------------------------------------
// IMPLEMENTAÇÃO DAS FUNÇÕES
// -------------------------------------------------------------------

/**
 * @brief Solicita o cadastro dos componentes da torre.
 */
void cadastrarComponentes() {
    int i;
    char buffer[30]; // Buffer para fgets

    printf("\n--- Cadastro dos Componentes para a Torre (Máx. %d) ---\n", MAX_COMPONENTES);
    totalComponentes = 0; // Zera para recadastro

    // Dados de exemplo para agilizar o teste
    Componente exemplos[] = {
        {"Cabo Principal", "Suporte", 5},
        {"Chip Central", "Controle", 10}, // Item-chave
        {"Motor A", "Propulsao", 7},
        {"Motor B", "Propulsao", 7},
        {"Painel Solar", "Suporte", 3}
    };
    int numExemplos = sizeof(exemplos) / sizeof(exemplos[0]);
    
    for (i = 0; i < MAX_COMPONENTES && i < numExemplos; i++) {
        componentes[i] = exemplos[i];
        printf("[%d] Preenchido: Nome: %s | Tipo: %s | Prioridade: %d\n", 
               i + 1, componentes[i].nome, componentes[i].tipo, componentes[i].prioridade);
        totalComponentes++;
    }
    printf("\n✅ %d Componentes cadastrados (usando dados de exemplo para agilizar).\n", totalComponentes);
}

/**
 * @brief Exibe o menu principal de estratégias.
 */
void exibirMenuPrincipal() {
    printf("\n--- Escolha a Estratégia de Montagem ---\n");
    printf(" [1] Recadastrar Componentes\n");
    printf(" [2] Estratégia 1: Ordenar por NOME (Bubble Sort) + Busca Binária\n");
    printf(" [3] Estratégia 2: Ordenar por TIPO (Insertion Sort)\n");
    printf(" [4] Estratégia 3: Ordenar por PRIORIDADE (Selection Sort)\n");
    printf(" [0] Sair do Módulo\n");
    printf("-----------------------------------------\n");
}

/**
 * @brief Exibe o vetor de componentes formatado.
 */
void mostrarComponentes(const Componente lista[], int tamanho) {
    if (tamanho == 0) {
        printf("Lista vazia.\n");
        return;
    }
    printf("| # | Nome                         | Tipo                 | Prioridade |\n");
    printf("|---|------------------------------|----------------------|------------|\n");
    for (int i = 0; i < tamanho; i++) {
        printf("| %-1d | %-28s | %-20s | %-10d |\n", 
               i + 1, lista[i].nome, lista[i].tipo, lista[i].prioridade);
    }
    printf("----------------------------------------------------------------------\n");
}

/**
 * @brief Copia um vetor de Componentes para outro.
 */
void copiarComponentes(const Componente origem[], Componente destino[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        destino[i] = origem[i];
    }
}

/**
 * @brief Troca dois elementos do tipo Componente.
 */
void trocar(Componente *a, Componente *b) {
    Componente temp = *a;
    *a = *b;
    *b = temp;
}

// -------------------------------------------------------------------
// ALGORITMOS DE ORDENAÇÃO
// -------------------------------------------------------------------

/**
 * @brief Implementa Bubble Sort para ordenar por NOME.
 * @return O número total de comparações.
 */
long long bubbleSortNome(Componente lista[], int tamanho) {
    long long comparacoes = 0;
    int i, j;
    int trocou;

    for (i = 0; i < tamanho - 1; i++) {
        trocou = 0;
        for (j = 0; j < tamanho - 1 - i; j++) {
            comparacoes++; // Comparação de strings
            // Compara os nomes alfabeticamente
            if (strcmp(lista[j].nome, lista[j + 1].nome) > 0) {
                trocar(&lista[j], &lista[j + 1]);
                trocou = 1;
            }
        }
        // Otimização: se não houve troca na passagem, o vetor está ordenado
        if (trocou == 0) break;
    }
    return comparacoes;
}

/**
 * @brief Implementa Insertion Sort para ordenar por TIPO.
 * @return O número total de comparações.
 */
long long insertionSortTipo(Componente lista[], int tamanho) {
    long long comparacoes = 0;
    int i, j;
    Componente chave;

    for (i = 1; i < tamanho; i++) {
        chave = lista[i];
        j = i - 1;

        // Move os elementos de lista[0..i-1] que são maiores que a chave (por tipo)
        // para uma posição à frente de sua posição atual
        while (j >= 0) {
            comparacoes++; // Comparação de strings dentro do loop
            if (strcmp(lista[j].tipo, chave.tipo) > 0) {
                lista[j + 1] = lista[j];
                j = j - 1;
            } else {
                break;
            }
        }
        lista[j + 1] = chave;
    }
    return comparacoes;
}

/**
 * @brief Implementa Selection Sort para ordenar por PRIORIDADE (inteiro).
 * @return O número total de comparações.
 */
long long selectionSortPrioridade(Componente lista[], int tamanho) {
    long long comparacoes = 0;
    int i, j, indiceMinimo;

    for (i = 0; i < tamanho - 1; i++) {
        indiceMinimo = i;
        for (j = i + 1; j < tamanho; j++) {
            comparacoes++; // Comparação de inteiros
            // Procura o elemento com a menor prioridade
            if (lista[j].prioridade < lista[indiceMinimo].prioridade) {
                indiceMinimo = j;
            }
        }
        // Troca o elemento de menor prioridade com o elemento atual
        if (indiceMinimo != i) {
            trocar(&lista[indiceMinimo], &lista[i]);
        }
    }
    return comparacoes;
}

// -------------------------------------------------------------------
// BUSCA BINÁRIA
// -------------------------------------------------------------------

/**
 * @brief Implementa a Busca Binária por NOME (string) no vetor ordenado.
 * @param comparacoes Ponteiro para a variável que contará as comparações.
 * @return O índice do item encontrado ou -1 se não for encontrado.
 */
int buscaBinariaPorNome(const Componente lista[], int tamanho, const char chave[], long long *comparacoes) {
    *comparacoes = 0; // Reseta o contador para a busca
    int esquerda = 0;
    int direita = tamanho - 1;
    int meio;
    
    // A Busca Binária só é eficiente em vetores ordenados
    
    while (esquerda <= direita) {
        meio = esquerda + (direita - esquerda) / 2;
        int resultadoComparacao;
        
        (*comparacoes)++; // Conta a comparação principal (strcmp)
        resultadoComparacao = strcmp(lista[meio].nome, chave);

        if (resultadoComparacao == 0) {
            return meio; // Item encontrado
        } else if (resultadoComparacao < 0) {
            // O nome buscado é 'maior' (vem depois)
            esquerda = meio + 1;
        } else {
            // O nome buscado é 'menor' (vem antes)
            direita = meio - 1;
        }
    }
    return -1; // Item não encontrado
}