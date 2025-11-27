#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Necessário para system("cls") ou system("clear")

// --- Constantes ---
// Capacidade máxima da mochila
#define CAPACIDADE_MAXIMA 10 

// --- Definição da Struct ---

/**
 * @brief Estrutura que representa um item dentro do inventário (mochila).
 * * Contém informações essenciais como nome, tipo e quantidade.
 */
typedef struct {
    char nome[30];      // Nome do item (ex: Rifle de Assalto)
    char tipo[20];      // Tipo do item (ex: Arma, Munição, Cura)
    int quantidade;     // Quantidade em posse
    int ativo;          // Flag para indicar se a posição está ocupada (1) ou livre (0)
} Item;

// --- Variáveis Globais (Gerenciamento da Mochila) ---

// Vetor de structs para armazenar os itens (Lista Sequencial)
Item mochila[CAPACIDADE_MAXIMA]; 
// Contador de itens REALMENTE cadastrados (útil para saber a próxima posição livre ou se a mochila está cheia)
int totalItens = 0; 

// --- Protótipos das Funções Obrigatórias ---

void inicializarMochila();
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
void exibirMenu();

// --- Main (Função Principal) ---

int main() {
    int opcao;
    
    inicializarMochila();

    printf("🎮 Sistema de Inventário (Mochila Virtual) 🎒\n");
    printf("==================================================\n");

    do {
        exibirMenu();
        printf("➡️ Digite sua opção: ");
        // Uso de scanf para ler a opção (inteiro)
        if (scanf("%d", &opcao) != 1) {
            // Limpa o buffer em caso de entrada não numérica
            while (getchar() != '\n'); 
            opcao = -1; // Opção inválida
        }
        
        // Limpa o buffer após a leitura do inteiro
        while (getchar() != '\n'); 

        printf("\n"); // Espaçamento para clareza

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("👋 Saindo do jogo. Inventário finalizado.\n");
                break;
            default:
                printf("⚠️ Opção inválida. Tente novamente.\n");
                break;
        }

        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar(); // Espera o usuário pressionar Enter
            // Tenta limpar a tela (para usabilidade, mas pode não funcionar em todos os sistemas)
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
        }
        
    } while (opcao != 0);

    return 0;
}

// -------------------------------------------------------------------
// IMPLEMENTAÇÃO DAS FUNÇÕES
// -------------------------------------------------------------------

/**
 * @brief Inicializa a flag 'ativo' de todos os slots da mochila para 0 (livre).
 */
void inicializarMochila() {
    for (int i = 0; i < CAPACIDADE_MAXIMA; i++) {
        mochila[i].ativo = 0;
    }
}

/**
 * @brief Exibe o menu de opções para o usuário.
 */
void exibirMenu() {
    printf("==================================================\n");
    printf(" Capacidade: %d/%d\n", totalItens, CAPACIDADE_MAXIMA);
    printf("--------------------------------------------------\n");
    printf(" [1] Coletar Item (Cadastrar)\n");
    printf(" [2] Descartar Item (Remover)\n");
    printf(" [3] Abrir Mochila (Listar)\n");
    printf(" [4] Procurar Item (Buscar)\n");
    printf(" [0] Sair\n");
    printf("--------------------------------------------------\n");
}


/**
 * @brief Encontra o índice da primeira posição livre no vetor de structs.
 * @return O índice da posição livre ou -1 se a mochila estiver cheia.
 */
int encontrarPosicaoLivre() {
    for (int i = 0; i < CAPACIDADE_MAXIMA; i++) {
        if (mochila[i].ativo == 0) {
            return i;
        }
    }
    return -1; // Mochila cheia
}

/**
 * @brief Cadastra um novo item na primeira posição livre da mochila.
 */
void inserirItem() {
    // 1. Verifica se a mochila está cheia
    if (totalItens >= CAPACIDADE_MAXIMA) {
        printf("🚫 Mochila Cheia! Não é possível coletar mais itens (%d/%d).\n", totalItens, CAPACIDADE_MAXIMA);
        return;
    }
    
    // Encontra o índice para inserção
    int i = encontrarPosicaoLivre();

    printf("--- Cadastro de Novo Item ---\n");

    // 2. Entrada do NOME (String)
    printf("Nome do Item (máx. 29 caracteres): ");
    // scanf com %29s é mais seguro para vetores de char do que fgets neste contexto simples
    scanf("%29s", mochila[i].nome); 
    
    // 3. Entrada do TIPO (String)
    printf("Tipo (ex: Arma, Munição, Cura): ");
    scanf("%19s", mochila[i].tipo);

    // 4. Entrada da QUANTIDADE (Inteiro)
    printf("Quantidade: ");
    scanf("%d", &mochila[i].quantidade);

    // 5. Atualiza o estado da struct e o contador
    mochila[i].ativo = 1; 
    totalItens++;
    
    printf("\n✅ Item '%s' coletado com sucesso e adicionado ao inventário na posição %d.\n", mochila[i].nome, i + 1);
    listarItens();
}

/**
 * @brief Implementa a busca sequencial por um item na mochila com base no nome.
 * @return O índice do item encontrado ou -1 se não for encontrado.
 */
int buscarIndicePorNome(const char* nomeBusca) {
    // Laço 'for' para percorrer sequencialmente o vetor
    for (int i = 0; i < CAPACIDADE_MAXIMA; i++) {
        // Verifica se a posição está ativa E se o nome confere
        if (mochila[i].ativo == 1 && strcmp(mochila[i].nome, nomeBusca) == 0) {
            return i; // Item encontrado
        }
    }
    return -1; // Item não encontrado
}


/**
 * @brief Remove um item da mochila, solicitando o nome.
 */
void removerItem() {
    if (totalItens == 0) {
        printf("🚫 A mochila está vazia. Nada a descartar.\n");
        return;
    }

    char nomeRemocao[30];
    printf("--- Descartar Item ---\n");
    printf("Digite o NOME do item a ser descartado: ");
    scanf("%29s", nomeRemocao);

    // 1. Busca o item pelo nome
    int i = buscarIndicePorNome(nomeRemocao);

    if (i != -1) {
        // 2. Remoção lógica (e marcação da posição como livre)
        mochila[i].ativo = 0;
        totalItens--;
        
        printf("\n✅ Item '%s' descartado com sucesso (Posição %d liberada).\n", nomeRemocao, i + 1);

    } else {
        printf("\n❌ Item '%s' não encontrado na mochila. Não foi possível descartar.\n", nomeRemocao);
    }
    
    listarItens();
}

/**
 * @brief Lista todos os itens ativos (coletados) na mochila.
 */
void listarItens() {
    printf("--- Status Atual da Mochila (%d/%d) ---\n", totalItens, CAPACIDADE_MAXIMA);
    
    if (totalItens == 0) {
        printf("⭐ Mochila VAZIA. Hora de coletar recursos!\n");
        return;
    }

    // Laço 'for' para percorrer o vetor
    printf("| Posição | Nome                         | Tipo                 | Quantidade |\n");
    printf("|---------|------------------------------|----------------------|------------|\n");
    for (int i = 0; i < CAPACIDADE_MAXIMA; i++) {
        // 1. Verifica a flag 'ativo' para listar apenas itens válidos
        if (mochila[i].ativo == 1) {
            printf("| %-7d | %-28s | %-20s | %-10d |\n", 
                   i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
        }
    }
    printf("---------------------------------------------------------------------------\n");
}

/**
 * @brief Implementa a busca sequencial por um item na mochila e exibe seus dados.
 */
void buscarItem() {
    if (totalItens == 0) {
        printf("🚫 A mochila está vazia. Não há itens para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("--- Procurar Item ---\n");
    printf("Digite o NOME do item que deseja localizar: ");
    scanf("%29s", nomeBusca);

    // 1. Busca o item pelo nome, utilizando a função auxiliar
    int i = buscarIndicePorNome(nomeBusca);

    if (i != -1) {
        // 2. Exibe os dados do item encontrado
        printf("\n✅ Item '%s' Localizado (Posição %d):\n", nomeBusca, i + 1);
        printf("  - Tipo: %s\n", mochila[i].tipo);
        printf("  - Quantidade: %d\n", mochila[i].quantidade);
    } else {
        printf("\n❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
    }
}