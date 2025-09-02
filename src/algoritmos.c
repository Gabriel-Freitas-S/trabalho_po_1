/**
 * ==============================================================
 * SISTEMA DE ANÁLISE DE ALGORITMOS DE ORDENAÇÃO - IMPLEMENTAÇÕES
 * ==============================================================
 *
 * @file algoritmos.c
 * @brief Implementação dos 7 algoritmos de ordenação com medição de performance
 * @version 2.1
 * @date 2025-08-24
 *
 * Este arquivo contém a implementação completa dos algoritmos de ordenação
 * utilizados no sistema. Cada algoritmo possui duas versões:
 *
 * 1. Versão não otimizada: Implementação didática e mais clara
 * 2. Versão otimizada: Implementação com foco em performance
 *
 * Algoritmos implementados:
 * - Insertion Sort: Ordenação por inserção (estável)
 * - Bubble Sort: Ordenação por bolha (estável)
 * - Selection Sort: Ordenação por seleção (não-estável)
 * - Shaker Sort: Ordenação cocktail (estável)
 * - Shell Sort: Ordenação por incrementos (não-estável)
 * - Quick Sort: Ordenação por particionamento (não-estável)
 * - Heap Sort: Ordenação por heap (não-estável)
 *
 * O sistema de contadores globais permite a análise precisa do número
 * de comparações e trocas realizadas por cada algoritmo.
 *
 * ==============================================================
 */

#include <string.h>  // Para memcpy
#include <stdlib.h>  // Para malloc e free
#include "../include/sorts.h"  // Inclui toda a estrutura modular

/* ==============================================================
 * VARIÁVEIS DE CONTROLE E CONFIGURAÇÃO
 * ============================================================== */

/**
 * @brief Controla qual versão dos algoritmos será utilizada
 *
 * Quando definida como 1, o sistema usa as versões otimizadas.
 * Quando definida como 0, usa as versões não otimizadas (didáticas).
 */
int usar_versao_otimizada = 1;

/**
 * @brief Configura o uso de versões otimizadas ou didáticas
 *
 * @param otimizada 1 para ativar otimizações, 0 para versão didática
 */
void configurar_otimizacao(int otimizada) {
    usar_versao_otimizada = otimizada;
}

/* ==============================================================
 * CONTADORES GLOBAIS PARA MÉTRICAS DE PERFORMANCE
 * ============================================================== */

/**
 * @brief Contador global de comparações realizadas
 *
 * Registra o número total de comparações entre elementos durante
 * a execução de um algoritmo de ordenação.
 */
long long contador_comparacoes = 0;

/**
 * @brief Contador global de trocas realizadas
 *
 * Registra o número total de trocas (swaps) entre elementos durante
 * a execução de um algoritmo de ordenação.
 */
long long contador_trocas = 0;

/**
 * @brief Contador global de movimentações realizadas
 *
 * Registra o número total de movimentações de memória (memcpy) durante
 * a execução de um algoritmo de ordenação.
 */
long long contador_movimentacoes = 0;

/**
 * @brief Armazena a função de comparação atualmente em uso
 *
 * Utilizada para registrar comparações sem modificar a função original.
 */
static CompareFn funcao_comparacao_atual = NULL;

/* ==============================================================
 * FUNÇÕES AUXILIARES
 * ============================================================== */

/**
 * @brief Compara dois elementos e conta a comparação
 *
 * Esta função é uma camada sobre a função de comparação original,
 * responsável por incrementar o contador de comparações.
 *
 * @param a Primeiro elemento a ser comparado
 * @param b Segundo elemento a ser comparado
 * @return Resultado da comparação entre a e b
 */
int comparar_e_contar(const void *a, const void *b) {
    contador_comparacoes++;
    return funcao_comparacao_atual(a, b);
}

/**
 * @brief Troca dois elementos de lugar na memória
 *
 * Realiza a troca dos valores de dois elementos, atualizando o
 * contador de trocas e movimentações.
 *
 * @param a Ponteiro para o primeiro elemento
 * @param b Ponteiro para o segundo elemento
 * @param elem_size Tamanho em bytes de cada elemento
 */
void swap_elements(void *a, void *b, size_t elem_size) {
    char *temp = malloc(elem_size);
    if (!temp) return;

    memcpy(temp, a, elem_size);
    memcpy(a, b, elem_size);
    memcpy(b, temp, elem_size);

    contador_trocas++;          // Conta +1 para a operação de alto nível "troca"
    contador_movimentacoes += 3;  // Conta +3 para as operações de escrita reais
    free(temp);
}

/**
 * @brief Implementa a estratégia "Mediana de Três" para otimização do Quick Sort
 *
 * Esta função pega os elementos do início, meio e fim do array, os ordena
 * e coloca o pivô (mediana) na penúltima posição. Isso evita o pior caso
 * O(n²) para arrays já ordenados.
 *
 * @param arr Ponteiro para o array
 * @param inicio Índice inicial
 * @param fim Índice final
 * @param elem_size Tamanho de cada elemento
 * @param cmp Função de comparação
 */
void mediana_de_tres(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp) {
    char *base = (char*)arr;
    int meio = inicio + (fim - inicio) / 2;

    // Usar a função de comparação global já configurada
    (void)cmp; // Suppresses unused parameter warning

    // Ordenar os três elementos: inicio, meio, fim
    // Após a ordenação: menor no início, mediana no meio, maior no fim

    if (comparar_e_contar(base + meio * elem_size, base + inicio * elem_size) < 0) {
        swap_elements(base + inicio * elem_size, base + meio * elem_size, elem_size);
    }

    if (comparar_e_contar(base + fim * elem_size, base + inicio * elem_size) < 0) {
        swap_elements(base + inicio * elem_size, base + fim * elem_size, elem_size);
    }

    if (comparar_e_contar(base + fim * elem_size, base + meio * elem_size) < 0) {
        swap_elements(base + meio * elem_size, base + fim * elem_size, elem_size);
    }

    // Agora temos: menor em inicio, mediana em meio, maior em fim
    // Colocamos a mediana (pivô) na penúltima posição
    swap_elements(base + meio * elem_size, base + (fim - 1) * elem_size, elem_size);
}

/* ==============================================================
 * IMPLEMENTAÇÕES NÃO OTIMIZADAS (DIDÁTICAS)
 * ============================================================== */

void insertion_sort_naive(void *arr, int n, size_t elem_size, CompareFn cmp) {
    funcao_comparacao_atual = cmp;
    char *base = (char *)arr;

    for (int i = 1; i < n; i++) {
        char *key = malloc(elem_size);
        if (!key) return;

        memcpy(key, base + i * elem_size, elem_size);
        int j = i - 1;

        while (j >= 0) {
            if (comparar_e_contar(base + j * elem_size, key) > 0) {
                memcpy(base + (j + 1) * elem_size, base + j * elem_size, elem_size);
                contador_trocas++;
                j--;
            } else {
                break;
            }
        }

        memcpy(base + (j + 1) * elem_size, key, elem_size);
        contador_trocas++;
        free(key);
    }
}

void bubble_sort_naive(void *arr, int n, size_t elem_size, CompareFn cmp) {
    funcao_comparacao_atual = cmp;
    char *base = (char *)arr;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (comparar_e_contar(base + j * elem_size, base + (j + 1) * elem_size) > 0) {
                swap_elements(base + j * elem_size, base + (j + 1) * elem_size, elem_size);
            }
        }
    }
}

void selection_sort_naive(void *arr, int n, size_t elem_size, CompareFn cmp) {
    funcao_comparacao_atual = cmp;
    char *base = (char *)arr;

    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (comparar_e_contar(base + j * elem_size, base + min_idx * elem_size) < 0) {
                min_idx = j;
            }
        }
        swap_elements(base + i * elem_size, base + min_idx * elem_size, elem_size);
    }
}

void shaker_sort_naive(void *arr, int n, size_t elem_size, CompareFn cmp) {
    funcao_comparacao_atual = cmp;
    char *base = (char *)arr;

    for (int pass = 0; pass < (n - 1) / 2; pass++) {
        for (int i = pass; i < n - pass - 1; i++) {
            if (comparar_e_contar(base + i * elem_size, base + (i + 1) * elem_size) > 0) {
                swap_elements(base + i * elem_size, base + (i + 1) * elem_size, elem_size);
            }
        }

        for (int i = n - pass - 2; i > pass; i--) {
            if (comparar_e_contar(base + i * elem_size, base + (i - 1) * elem_size) < 0) {
                swap_elements(base + i * elem_size, base + (i - 1) * elem_size, elem_size);
            }
        }
    }
}

void shell_sort_naive(void *arr, int n, size_t elem_size, CompareFn cmp) {
    funcao_comparacao_atual = cmp;
    char *base = (char *)arr;

    for (int gap = n / 2; gap > 0; gap = gap / 2) {
        char *temp = malloc(elem_size);
        if (!temp) return;

        for (int i = gap; i < n; i++) {
            memcpy(temp, base + i * elem_size, elem_size);
            int j;

            for (j = i; j >= gap; j -= gap) {
                if (comparar_e_contar(base + (j - gap) * elem_size, temp) > 0) {
                    memcpy(base + j * elem_size, base + (j - gap) * elem_size, elem_size);
                    contador_trocas++;
                } else {
                    break;
                }
            }

            memcpy(base + j * elem_size, temp, elem_size);
            contador_trocas++;
        }
        free(temp);
    }
}

void quick_sort_naive(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp) {
    if (inicio < fim) {
        funcao_comparacao_atual = cmp;
        int pi = partition_naive(arr, inicio, fim, elem_size, cmp);
        quick_sort_naive(arr, inicio, pi - 1, elem_size, cmp);
        quick_sort_naive(arr, pi + 1, fim, elem_size, cmp);
    }
    (void)cmp; // Suppress unused parameter warning
}

int partition_naive(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp) {
    char *base = (char*)arr;
    char *pivo = malloc(elem_size);
    if (!pivo) return inicio;

    memcpy(pivo, base + fim * elem_size, elem_size);
    int i = inicio - 1;

    for (int j = inicio; j <= fim - 1; j++) {
        if (comparar_e_contar(base + j * elem_size, pivo) < 0) {
            i++;
            swap_elements(base + i * elem_size, base + j * elem_size, elem_size);
        }
    }

    swap_elements(base + (i + 1) * elem_size, base + fim * elem_size, elem_size);
    free(pivo);
    (void)cmp;
    return (i + 1);
}

void heap_sort_naive(void *arr, int n, size_t elem_size, CompareFn cmp) {
    funcao_comparacao_atual = cmp;

    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 &&
             comparar_e_contar((char*)arr + j * elem_size,
                               (char*)arr + ((j-1)/2) * elem_size) > 0;
             j = (j-1)/2) {
            swap_elements((char*)arr + j * elem_size,
                         (char*)arr + ((j-1)/2) * elem_size, elem_size);
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        swap_elements(arr, (char*)arr + i * elem_size, elem_size);
        heapify_naive(arr, i, 0, elem_size, cmp);
    }
}

void heapify_naive(void *arr, int n, int i, size_t elem_size, CompareFn cmp) {
    char *base = (char*)arr;

    while (1) {
        int maior = i;
        int esquerda = 2 * i + 1;
        int direita = 2 * i + 2;

        if (esquerda < n) {
            if (comparar_e_contar(base + esquerda * elem_size, base + maior * elem_size) > 0) {
                maior = esquerda;
            }
        }

        if (direita < n) {
            if (comparar_e_contar(base + direita * elem_size, base + maior * elem_size) > 0) {
                maior = direita;
            }
        }

        if (maior == i) break;

        swap_elements(base + i * elem_size, base + maior * elem_size, elem_size);
        i = maior;
    }
    // Suppress unused parameter warning - cmp is used indirectly via funcao_comparacao_atual
    (void)cmp;
}

/* ==============================================================
 * IMPLEMENTAÇÕES OTIMIZADAS
 * ============================================================== */

void insertion_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp) {
    funcao_comparacao_atual = cmp;
    char *base = (char *)arr;
    char *key = malloc(elem_size);
    if (!key) return;

    for (int i = 1; i < n; i++) {
        // 1. Movimentação para salvar a chave
        memcpy(key, base + i * elem_size, elem_size);
        contador_movimentacoes++;
        int j = i - 1;

        while (j >= 0 && comparar_e_contar(base + j * elem_size, key) > 0) {
            // 2. Movimentação de deslocamento
            memcpy(base + (j + 1) * elem_size, base + j * elem_size, elem_size);
            contador_movimentacoes++;
            j--;
        }

        // 3. Movimentação para inserir a chave
        memcpy(base + (j + 1) * elem_size, key, elem_size);
        contador_movimentacoes++;
    }
    free(key);
}

void bubble_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp) {
    funcao_comparacao_atual = cmp;
    char *base = (char *)arr;

    for (int i = 0; i < n - 1; i++) {
        int houve_troca = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (comparar_e_contar(base + j * elem_size, base + (j + 1) * elem_size) > 0) {
                swap_elements(base + j * elem_size, base + (j + 1) * elem_size, elem_size);
                houve_troca = 1;
            }
        }
        if (!houve_troca) break;
    }
}

void selection_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp) {
    funcao_comparacao_atual = cmp;
    char *base = (char *)arr;

    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (comparar_e_contar(base + j * elem_size, base + min_idx * elem_size) < 0) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap_elements(base + i * elem_size, base + min_idx * elem_size, elem_size);
        }
    }
}

void shaker_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp) {
    funcao_comparacao_atual = cmp;
    char *base = (char *)arr;
    int inicio = 0, fim = n - 1;
    int houve_troca = 1;

    while (houve_troca && inicio < fim) {
        houve_troca = 0;
        for (int i = inicio; i < fim; i++) {
            if (comparar_e_contar(base + i * elem_size, base + (i + 1) * elem_size) > 0) {
                swap_elements(base + i * elem_size, base + (i + 1) * elem_size, elem_size);
                houve_troca = 1;
            }
        }
        fim--;

        if (!houve_troca) break;

        houve_troca = 0;
        for (int i = fim; i > inicio; i--) {
            if (comparar_e_contar(base + i * elem_size, base + (i - 1) * elem_size) < 0) {
                swap_elements(base + i * elem_size, base + (i - 1) * elem_size, elem_size);
                houve_troca = 1;
            }
        }
        inicio++;
    }
}

void shell_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp) {
    funcao_comparacao_atual = cmp;
    char *base = (char *)arr;
    char *temp = malloc(elem_size);
    if (!temp) return;

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            // 1. Movimentação para salvar o elemento
            memcpy(temp, base + i * elem_size, elem_size);
            contador_movimentacoes++;
            int j;

            for (j = i; j >= gap && comparar_e_contar(base + (j - gap) * elem_size, temp) > 0; j -= gap) {
                // 2. Movimentação de deslocamento
                memcpy(base + j * elem_size, base + (j - gap) * elem_size, elem_size);
                contador_movimentacoes++;
            }

            // 3. Movimentação para inserir o elemento
            memcpy(base + j * elem_size, temp, elem_size);
            contador_movimentacoes++;
        }
    }
    free(temp);
}

void quick_sort_optimized(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp) {
    if (inicio < fim) {
        funcao_comparacao_atual = cmp;

        // OTIMIZAÇÃO: Aplicar estratégia "Mediana de Três" para evitar pior caso O(n²)
        if (fim - inicio >= 3) {
            mediana_de_tres(arr, inicio, fim, elem_size, cmp);
        }

        int pi = partition_optimized(arr, inicio, fim, elem_size, cmp);
        quick_sort_optimized(arr, inicio, pi - 1, elem_size, cmp);
        quick_sort_optimized(arr, pi + 1, fim, elem_size, cmp);
    }
    (void)cmp; // Suppress unused parameter warning
}

int partition_optimized(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp) {
    char *base = (char*)arr;
    char *pivo = malloc(elem_size);
    if (!pivo) return inicio;

    memcpy(pivo, base + fim * elem_size, elem_size);
    int i = inicio - 1;

    for (int j = inicio; j <= fim - 1; j++) {
        if (comparar_e_contar(base + j * elem_size, pivo) < 0) {
            i++;
            swap_elements(base + i * elem_size, base + j * elem_size, elem_size);
        }
    }
    swap_elements(base + (i + 1) * elem_size, base + fim * elem_size, elem_size);
    free(pivo);
    (void)cmp;
    return (i + 1);
}

void heap_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp) {
    funcao_comparacao_atual = cmp;

    // Fase 1: Construção do heap (bottom-up)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify_optimized(arr, n, i, elem_size, cmp);

    // Fase 2: Extração
    for (int i = n - 1; i >= 0; i--) {
        swap_elements(arr, (char*)arr + i * elem_size, elem_size);

        // CORREÇÃO CRÍTICA: O tamanho do heap agora é 'i', não 'n'
        heapify_optimized(arr, i, 0, elem_size, cmp);
    }
}

void heapify_optimized(void *arr, int n, int i, size_t elem_size, CompareFn cmp) {
    char *base = (char*)arr;
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < n && comparar_e_contar(base + esquerda * elem_size, base + maior * elem_size) > 0)
        maior = esquerda;

    if (direita < n && comparar_e_contar(base + direita * elem_size, base + maior * elem_size) > 0)
        maior = direita;

    if (maior != i) {
        swap_elements(base + i * elem_size, base + maior * elem_size, elem_size);
        heapify_optimized(arr, n, maior, elem_size, cmp);
    }
}

/* ==============================================================
 * INTERFACES UNIFICADAS - ALTERNAM ENTRE VERSÕES
 * ============================================================== */

void insertion_sort(void *arr, int n, size_t elem_size, CompareFn cmp) {
    if (usar_versao_otimizada) {
        insertion_sort_optimized(arr, n, elem_size, cmp);
    } else {
        insertion_sort_naive(arr, n, elem_size, cmp);
    }
}

void bubble_sort(void *arr, int n, size_t elem_size, CompareFn cmp) {
    if (usar_versao_otimizada) {
        bubble_sort_optimized(arr, n, elem_size, cmp);
    } else {
        bubble_sort_naive(arr, n, elem_size, cmp);
    }
}

void selection_sort(void *arr, int n, size_t elem_size, CompareFn cmp) {
    if (usar_versao_otimizada) {
        selection_sort_optimized(arr, n, elem_size, cmp);
    } else {
        selection_sort_naive(arr, n, elem_size, cmp);
    }
}

void shaker_sort(void *arr, int n, size_t elem_size, CompareFn cmp) {
    if (usar_versao_otimizada) {
        shaker_sort_optimized(arr, n, elem_size, cmp);
    } else {
        shaker_sort_naive(arr, n, elem_size, cmp);
    }
}

void shell_sort(void *arr, int n, size_t elem_size, CompareFn cmp) {
    if (usar_versao_otimizada) {
        shell_sort_optimized(arr, n, elem_size, cmp);
    } else {
        shell_sort_naive(arr, n, elem_size, cmp);
    }
}

void quick_sort(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp) {
    if (usar_versao_otimizada) {
        quick_sort_optimized(arr, inicio, fim, elem_size, cmp);
    } else {
        quick_sort_naive(arr, inicio, fim, elem_size, cmp);
    }
}

void heap_sort(void *arr, int n, size_t elem_size, CompareFn cmp) {
    if (usar_versao_otimizada) {
        heap_sort_optimized(arr, n, elem_size, cmp);
    } else {
        heap_sort_naive(arr, n, elem_size, cmp);
    }
}

int partition(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp) {
    if (usar_versao_otimizada) {
        return partition_optimized(arr, inicio, fim, elem_size, cmp);
    } else {
        return partition_naive(arr, inicio, fim, elem_size, cmp);
    }
}

void heapify(void *arr, int n, int i, size_t elem_size, CompareFn cmp) {
    if (usar_versao_otimizada) {
        heapify_optimized(arr, n, i, elem_size, cmp);
    } else {
        heapify_naive(arr, n, i, elem_size, cmp);
    }
}
