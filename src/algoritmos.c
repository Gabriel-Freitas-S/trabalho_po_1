/**
 * ================================================================
 * TRABALHO DE ALGORITMOS DE ORDENAÇÃO - IMPLEMENTAÇÕES
 * ================================================================
 *
 * @file algoritmos.c
 * @brief Implementação de 7 algoritmos de ordenação com análise de performance
 * @version 2.1
 * @date 2025-08-24
 * @author Sistema de Análise de Algoritmos
 *
 * NOVA VERSÃO 2.1: Sistema com Versões Otimizadas e Não Otimizadas
 * - Implementações otimizadas para máxima performance
 * - Implementações não otimizadas para fins didáticos
 * - Sistema de flags para alternar entre versões
 * - Comparação automática entre as implementações
 *
 * Algoritmos implementados:
 * 1. Insertion Sort - Ordenação por inserção (estável)
 * 2. Bubble Sort - Ordenação por bolha (estável)
 * 3. Selection Sort - Ordenação por seleção (não-estável)
 * 4. Shaker Sort - Ordenação cocktail (estável)
 * 5. Shell Sort - Ordenação por incrementos (não-estável)
 * 6. Quick Sort - Ordenação por particionamento (não-estável)
 * 7. Heap Sort - Ordenação por heap (não-estável)
 *
 * ================================================================
 */

#include "../include/sorts.h"

/* ================================================================
 * VARIÁVEL GLOBAL PARA CONTROLE DE OTIMIZAÇÃO
 * ================================================================ */

int usar_versao_otimizada = 1;

void configurar_otimizacao(int otimizada) {
    usar_versao_otimizada = otimizada;
}

/* ================================================================
 * VARIÁVEIS GLOBAIS PARA MÉTRICAS DE PERFORMANCE
 * ================================================================ */

long long contador_comparacoes = 0;
long long contador_trocas = 0;
static CompareFn funcao_comparacao_atual = NULL;

/* ================================================================
 * FUNÇÕES AUXILIARES
 * ================================================================ */

int comparar_e_contar(const void *a, const void *b) {
    contador_comparacoes++;
    return funcao_comparacao_atual(a, b);
}

void swap_elements(void *a, void *b, size_t elem_size) {
    char *temp = malloc(elem_size);
    if (!temp) return;

    memcpy(temp, a, elem_size);
    memcpy(a, b, elem_size);
    memcpy(b, temp, elem_size);

    contador_trocas++;
    free(temp);
}

/* ================================================================
 * IMPLEMENTAÇÕES NÃO OTIMIZADAS (DIDÁTICAS)
 * ================================================================ */

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
    funcao_comparacao_atual = cmp;

    if (inicio < fim) {
        int pi = partition_naive(arr, inicio, fim, elem_size, cmp);
        quick_sort_naive(arr, inicio, pi - 1, elem_size, cmp);
        quick_sort_naive(arr, pi + 1, fim, elem_size, cmp);
    }
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
}

/* ================================================================
 * IMPLEMENTAÇÕES OTIMIZADAS
 * ================================================================ */

void insertion_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp) {
    funcao_comparacao_atual = cmp;
    char *base = (char *)arr;
    char *key = malloc(elem_size);
    if (!key) return;

    for (int i = 1; i < n; i++) {
        memcpy(key, base + i * elem_size, elem_size);
        int j = i - 1;

        while (j >= 0 && comparar_e_contar(base + j * elem_size, key) > 0) {
            memcpy(base + (j + 1) * elem_size, base + j * elem_size, elem_size);
            contador_trocas++;
            j--;
        }

        memcpy(base + (j + 1) * elem_size, key, elem_size);
        contador_trocas++;
    }
    free(key);
}

void bubble_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp) {
    funcao_comparacao_atual = cmp;
    char *base = (char *)arr;
    int houve_troca;

    for (int i = 0; i < n - 1; i++) {
        houve_troca = 0;
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
    int inicio = 0, fim = n - 1, houve_troca;

    do {
        houve_troca = 0;
        for (int i = inicio; i < fim; i++) {
            if (comparar_e_contar(base + i * elem_size, base + (i + 1) * elem_size) > 0) {
                swap_elements(base + i * elem_size, base + (i + 1) * elem_size, elem_size);
                houve_troca = 1;
            }
        }
        fim--;
        if (!houve_troca) break;

        for (int i = fim; i > inicio; i--) {
            if (comparar_e_contar(base + i * elem_size, base + (i - 1) * elem_size) < 0) {
                swap_elements(base + i * elem_size, base + (i - 1) * elem_size, elem_size);
                houve_troca = 1;
            }
        }
        inicio++;
    } while (houve_troca);
}

void shell_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp) {
    funcao_comparacao_atual = cmp;
    char *base = (char *)arr;
    char *temp = malloc(elem_size);
    if (!temp) return;

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            memcpy(temp, base + i * elem_size, elem_size);
            int j;

            for (j = i; j >= gap && comparar_e_contar(base + (j - gap) * elem_size, temp) > 0; j -= gap) {
                memcpy(base + j * elem_size, base + (j - gap) * elem_size, elem_size);
                contador_trocas++;
            }

            memcpy(base + j * elem_size, temp, elem_size);
            contador_trocas++;
        }
    }
    free(temp);
}

void quick_sort_optimized(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp) {
    funcao_comparacao_atual = cmp;
    if (inicio < fim) {
        int pi = partition_optimized(arr, inicio, fim, elem_size, cmp);
        quick_sort_optimized(arr, inicio, pi - 1, elem_size, cmp);
        quick_sort_optimized(arr, pi + 1, fim, elem_size, cmp);
    }
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
    return (i + 1);
}

void heap_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp) {
    funcao_comparacao_atual = cmp;

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify_optimized(arr, n, i, elem_size, cmp);

    for (int i = n - 1; i >= 0; i--) {
        swap_elements(arr, (char*)arr + i * elem_size, elem_size);
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

/* ================================================================
 * INTERFACES UNIFICADAS - ALTERNAM ENTRE VERSÕES
 * ================================================================ */

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
