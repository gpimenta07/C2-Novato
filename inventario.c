#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Constantes e Variáveis Globais para Contagem ---
#define MAX_VETOR 5 // Capacidade reduzida para testes mais rápidos e claros

// Contadores de desempenho
int contadorComparacoes = 0;

// --- Definições das Structs ---

/**
 * @brief Estrutura que armazena os dados de um item.
 */
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

/**
 * @brief Estrutura do Nó para a Lista Encadeada.
 */
typedef struct No {
    Item dados;
    struct No* proximo;
} No;


// --- Variáveis de Controle das Estruturas ---

// Vetor (Lista Sequencial)
Item vetorMochila[MAX_VETOR];
int totalVetor = 0; // Número atual de itens no vetor

// Lista Encadeada
No* cabecaLista = NULL; // Ponteiro para o início da lista

// --- Protótipos das Funções ---

// Funções de Menu e Auxiliares
void exibirMenuPrincipal();
void exibirMenuEstrutura(const char* estrutura);
Item criarNovoItem();

// Funções do Vetor
void inserirItemVetor(Item novoItem);
void removerItemVetor(const char* nomeRemocao);
void listarItensVetor();
void ordenarVetor();
void buscarSequencialVetor(const char* nomeBusca);
void buscarBinariaVetor(const char* nomeBusca);

// Funções da Lista Encadeada
void inserirItemLista(Item novoItem);
void removerItemLista(const char* nomeRemocao);
void listarItensLista();
void buscarSequencialLista(const char* nomeBusca);

// Função de Limpeza de Memória
void liberarLista();

// --- Main (Função Principal) ---

int main() {
    int opcaoPrincipal, opcaoEstrutura;

    do {
        // Limpa a tela para melhor usabilidade
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        exibirMenuPrincipal();
        printf("➡️ Digite sua opção: ");
        if (scanf("%d", &opcaoPrincipal) != 1) {
            opcaoPrincipal = -1;
        }
        while (getchar() != '\n'); // Limpa buffer

        switch (opcaoPrincipal) {
            case 1:
                // Operações no Vetor
                do {
                    exibirMenuEstrutura("Vetor (Lista Sequencial)");
                    printf("➡️ Digite sua opção (Vetor): ");
                    if (scanf("%d", &opcaoEstrutura) != 1) { opcaoEstrutura = -1; }
                    while (getchar() != '\n');
                    
                    switch (opcaoEstrutura) {
                        case 1: inserirItemVetor(criarNovoItem()); break;
                        case 2: {
                            char nome[30]; 
                            printf("Nome do item para remover: "); 
                            scanf("%29s", nome);
                            removerItemVetor(nome); 
                            break;
                        }
                        case 3: listarItensVetor(); break;
                        case 4: {
                            char nome[30]; 
                            printf("Nome do item para buscar (Sequencial): "); 
                            scanf("%29s", nome);
                            buscarSequencialVetor(nome); 
                            break;
                        }
                        case 5: ordenarVetor(); break;
                        case 6: {
                            char nome[30]; 
                            printf("Nome do item para buscar (Binária): "); 
                            scanf("%29s", nome);
                            buscarBinariaVetor(nome); 
                            break;
                        }
                        case 0: printf("\nVoltando ao menu principal...\n"); break;
                        default: printf("⚠️ Opção inválida. Tente novamente.\n"); break;
                    }
                    if (opcaoEstrutura != 0) {
                        printf("\nPressione ENTER para continuar...");
                        getchar();
                    }
                } while (opcaoEstrutura != 0);
                break;

            case 2:
                // Operações na Lista Encadeada
                do {
                    exibirMenuEstrutura("Lista Encadeada");
                    printf("➡️ Digite sua opção (Lista): ");
                    if (scanf("%d", &opcaoEstrutura) != 1) { opcaoEstrutura = -1; }
                    while (getchar() != '\n');

                    switch (opcaoEstrutura) {
                        case 1: inserirItemLista(criarNovoItem()); break;
                        case 2: {
                            char nome[30]; 
                            printf("Nome do item para remover: "); 
                            scanf("%29s", nome);
                            removerItemLista(nome); 
                            break;
                        }
                        case 3: listarItensLista(); break;
                        case 4: {
                            char nome[30]; 
                            printf("Nome do item para buscar (Sequencial): "); 
                            scanf("%29s", nome);
                            buscarSequencialLista(nome); 
                            break;
                        }
                        case 0: printf("\nVoltando ao menu principal...\n"); break;
                        default: printf("⚠️ Opção inválida. Tente novamente.\n"); break;
                    }
                    if (opcaoEstrutura != 0) {
                        printf("\nPressione ENTER para continuar...");
                        getchar();
                    }
                } while (opcaoEstrutura != 0);
                break;

            case 0:
                printf("\n👋 Encerrando o sistema. Liberando memória da lista...\n");
                liberarLista();
                break;

            default:
                printf("⚠️ Opção principal inválida.\n");
                break;
        }

    } while (opcaoPrincipal != 0);

    return 0;
}

// -------------------------------------------------------------------
// FUNÇÕES DE MENU E AUXILIARES
// -------------------------------------------------------------------

void exibirMenuPrincipal() {
    printf("--- Comparação de Estruturas de Dados ---\n");
    printf(" [1] Mochila com Vetor (Lista Sequencial)\n");
    printf(" [2] Mochila com Lista Encadeada\n");
    printf(" [0] Sair\n");
    printf("------------------------------------------\n");
}

void exibirMenuEstrutura(const char* estrutura) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    printf("--- Operações em %s ---\n", estrutura);
    printf(" [1] Inserir Item\n");
    printf(" [2] Remover Item\n");
    printf(" [3] Listar Itens\n");
    printf(" [4] Buscar Sequencial (Contar Comparações)\n");
    if (strcmp(estrutura, "Vetor (Lista Sequencial)") == 0) {
        printf(" [5] Ordenar Itens (Por Nome)\n");
        printf(" [6] Buscar Binária (Contar Comparações)\n");
    }
    printf(" [0] Voltar\n");
    printf("------------------------------------------\n");
}

Item criarNovoItem() {
    Item novo;
    printf("--- Inserir Novo Item ---\n");
    printf("Nome: ");
    scanf("%29s", novo.nome);
    printf("Tipo (ex: Arma, Cura): ");
    scanf("%19s", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    while (getchar() != '\n'); // Limpa buffer
    return novo;
}


// -------------------------------------------------------------------
// FUNÇÕES DO VETOR (LISTA SEQUENCIAL)
// -------------------------------------------------------------------

/**
 * @brief Insere um item na primeira posição livre do vetor.
 */
void inserirItemVetor(Item novoItem) {
    if (totalVetor < MAX_VETOR) {
        vetorMochila[totalVetor] = novoItem;
        totalVetor++;
        printf("\n✅ Item '%s' inserido no Vetor (Posição %d).\n", novoItem.nome, totalVetor);
    } else {
        printf("\n🚫 Vetor Cheio! Capacidade máxima atingida (%d).\n", MAX_VETOR);
    }
}

/**
 * @brief Remove um item do vetor por nome e realoca os elementos restantes.
 */
void removerItemVetor(const char* nomeRemocao) {
    int i, indiceRemover = -1;

    // Busca o item para encontrar o índice
    for (i = 0; i < totalVetor; i++) {
        if (strcmp(vetorMochila[i].nome, nomeRemocao) == 0) {
            indiceRemover = i;
            break;
        }
    }

    if (indiceRemover != -1) {
        // Remoção e compactação: move os elementos subsequentes uma posição para trás
        for (i = indiceRemover; i < totalVetor - 1; i++) {
            vetorMochila[i] = vetorMochila[i + 1];
        }
        totalVetor--;
        printf("\n✅ Item '%s' removido do Vetor. Vetor compactado.\n", nomeRemocao);
    } else {
        printf("\n❌ Item '%s' não encontrado no Vetor.\n", nomeRemocao);
    }
}

/**
 * @brief Lista todos os itens do vetor.
 */
void listarItensVetor() {
    printf("--- Itens no Vetor (%d/%d) ---\n", totalVetor, MAX_VETOR);
    if (totalVetor == 0) {
        printf("⭐ Vetor vazio.\n");
        return;
    }
    printf("| Posição | Nome                         | Tipo                 | Quantidade |\n");
    printf("|---------|------------------------------|----------------------|------------|\n");
    for (int i = 0; i < totalVetor; i++) {
        printf("| %-7d | %-28s | %-20s | %-10d |\n", 
               i + 1, vetorMochila[i].nome, vetorMochila[i].tipo, vetorMochila[i].quantidade);
    }
    printf("---------------------------------------------------------------------------\n");
}

/**
 * @brief Ordena o vetor de structs por nome (usando Selection Sort).
 */
void ordenarVetor() {
    int i, j, min_idx;
    Item temp;

    // Selection Sort (implementação simples)
    for (i = 0; i < totalVetor - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < totalVetor; j++) {
            // Compara os nomes alfabeticamente
            if (strcmp(vetorMochila[j].nome, vetorMochila[min_idx].nome) < 0) {
                min_idx = j;
            }
        }
        // Troca o elemento encontrado com o primeiro elemento não ordenado
        if (min_idx != i) {
            temp = vetorMochila[i];
            vetorMochila[i] = vetorMochila[min_idx];
            vetorMochila[min_idx] = temp;
        }
    }
    printf("\n✅ Vetor ordenado com sucesso por nome (Selection Sort).\n");
    listarItensVetor();
}

/**
 * @brief Realiza busca sequencial no vetor, contando as comparações.
 */
void buscarSequencialVetor(const char* nomeBusca) {
    contadorComparacoes = 0;
    int encontrado = 0;

    for (int i = 0; i < totalVetor; i++) {
        contadorComparacoes++; // Conta cada comparação de nome
        if (strcmp(vetorMochila[i].nome, nomeBusca) == 0) {
            printf("\n✅ Item '%s' encontrado por Busca Sequencial na Posição %d.\n", nomeBusca, i + 1);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\n❌ Item '%s' não encontrado por Busca Sequencial.\n", nomeBusca);
    }
    printf("📊 Comparações realizadas (Busca Sequencial): %d\n", contadorComparacoes);
}

/**
 * @brief Realiza busca binária no vetor (requer vetor ordenado), contando as comparações.
 */
void buscarBinariaVetor(const char* nomeBusca) {
    contadorComparacoes = 0;
    int esquerda = 0;
    int direita = totalVetor - 1;
    int meio, encontrado = 0;

    // A busca binária só funciona se o vetor estiver ordenado.
    if (totalVetor == 0) {
        printf("\n🚫 Vetor vazio. Impossível buscar.\n");
        return;
    }
    
    printf("\n⚠️ Atenção: A Busca Binária exige que o Vetor esteja ordenado.\n");

    while (esquerda <= direita) {
        meio = esquerda + (direita - esquerda) / 2;
        int resultadoComparacao;
        
        contadorComparacoes++; // Conta a comparação principal
        resultadoComparacao = strcmp(vetorMochila[meio].nome, nomeBusca);

        if (resultadoComparacao == 0) {
            printf("\n✅ Item '%s' encontrado por Busca Binária na Posição %d.\n", nomeBusca, meio + 1);
            encontrado = 1;
            break;
        } else if (resultadoComparacao < 0) {
            // O nome buscado é 'maior' (vem depois)
            esquerda = meio + 1;
        } else {
            // O nome buscado é 'menor' (vem antes)
            direita = meio - 1;
        }
    }

    if (!encontrado) {
        printf("\n❌ Item '%s' não encontrado por Busca Binária.\n", nomeBusca);
    }
    printf("📊 Comparações realizadas (Busca Binária): %d\n", contadorComparacoes);
}


// -------------------------------------------------------------------
// FUNÇÕES DA LISTA ENCADEADA
// -------------------------------------------------------------------

/**
 * @brief Insere um item no final da lista encadeada.
 */
void inserirItemLista(Item novoItem) {
    // 1. Aloca dinamicamente o novo nó (malloc)
    No* novoNo = (No*) malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("\n🚫 Erro de alocação de memória (Lista Encadeada).\n");
        return;
    }

    // 2. Preenche os dados do nó
    novoNo->dados = novoItem;
    novoNo->proximo = NULL; // Novo nó sempre aponta para NULL (se for o último)

    // 3. Insere na lista
    if (cabecaLista == NULL) {
        // Lista vazia, o novo nó é a cabeça
        cabecaLista = novoNo;
    } else {
        // Percorre até o último nó
        No* atual = cabecaLista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        // O último nó passa a apontar para o novo nó
        atual->proximo = novoNo;
    }
    printf("\n✅ Item '%s' inserido na Lista Encadeada.\n", novoItem.nome);
}

/**
 * @brief Remove o primeiro item encontrado na lista encadeada por nome.
 */
void removerItemLista(const char* nomeRemocao) {
    No *atual = cabecaLista;
    No *anterior = NULL;
    int encontrado = 0;

    // 1. Percorre a lista para encontrar o item
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nomeRemocao) == 0) {
            encontrado = 1;
            break;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    if (encontrado) {
        // 2. Ajusta os ponteiros
        if (anterior == NULL) {
            // O nó a ser removido é a cabeça
            cabecaLista = atual->proximo;
        } else {
            // O nó anterior aponta para o próximo do nó atual
            anterior->proximo = atual->proximo;
        }
        
        // 3. Libera a memória do nó removido
        free(atual);
        printf("\n✅ Item '%s' removido da Lista Encadeada.\n", nomeRemocao);
    } else {
        printf("\n❌ Item '%s' não encontrado na Lista Encadeada.\n", nomeRemocao);
    }
}

/**
 * @brief Lista todos os itens da lista encadeada.
 */
void listarItensLista() {
    printf("--- Itens na Lista Encadeada ---\n");
    if (cabecaLista == NULL) {
        printf("⭐ Lista Vazia.\n");
        return;
    }

    No* atual = cabecaLista;
    int i = 1;
    
    printf("| Posição | Nome                         | Tipo                 | Quantidade |\n");
    printf("|---------|------------------------------|----------------------|------------|\n");
    while (atual != NULL) {
        printf("| %-7d | %-28s | %-20s | %-10d |\n", 
               i++, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
    printf("---------------------------------------------------------------------------\n");
}

/**
 * @brief Realiza busca sequencial na lista encadeada, contando as comparações.
 */
void buscarSequencialLista(const char* nomeBusca) {
    contadorComparacoes = 0;
    No* atual = cabecaLista;
    int encontrado = 0;

    while (atual != NULL) {
        contadorComparacoes++; // Conta cada comparação de nome
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            printf("\n✅ Item '%s' encontrado por Busca Sequencial na Lista Encadeada.\n", nomeBusca);
            encontrado = 1;
            break;
        }
        atual = atual->proximo;
    }

    if (!encontrado) {
        printf("\n❌ Item '%s' não encontrado por Busca Sequencial na Lista Encadeada.\n", nomeBusca);
    }
    printf("📊 Comparações realizadas (Busca Sequencial): %d\n", contadorComparacoes);
}

/**
 * @brief Libera toda a memória alocada dinamicamente para a lista encadeada.
 */
void liberarLista() {
    No* atual = cabecaLista;
    No* proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    cabecaLista = NULL;
    printf("Memória da Lista Encadeada liberada com sucesso.\n");
}