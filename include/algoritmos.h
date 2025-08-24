/**
 * ================================================================
 * ALGORITMOS DE ORDENAÇÃO - PROTÓTIPOS E DEFINIÇÕES
 * ================================================================
 *
 * @file algoritmos.h
 * @brief Protótipos de todos os algoritmos de ordenação implementados
 * @version 2.1
 * @date 2025-08-24
 * @author Sistema de Análise de Algoritmos
 *
 * Este arquivo contém apenas os protótipos dos algoritmos de ordenação,
 * separados do arquivo principal para melhor organização modular.
 *
 * ================================================================
 */

#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "tipos.h"

/* ================================================================
 * ALGORITMOS PRINCIPAIS - VERSÕES ADAPTÁVEIS
 * ================================================================ */

/**
 * @brief Insertion Sort - Ordenação por inserção
 *
 * Algoritmo estável que constrói a sequência ordenada inserindo
 * elementos um por vez na posição correta.
 *
 * Complexidades:
 * - Melhor caso: O(n) - dados já ordenados
 * - Caso médio: O(n²)
 * - Pior caso: O(n²) - dados em ordem reversa
 */
void insertion_sort(void *arr, int n, size_t elem_size, CompareFn cmp);

/**
 * @brief Bubble Sort - Ordenação por bolha
 *
 * Algoritmo estável que compara elementos adjacentes e os troca
 * se estiverem na ordem errada.
 *
 * Complexidades:
 * - Melhor caso: O(n) - dados já ordenados (com otimização)
 * - Caso médio: O(n²)
 * - Pior caso: O(n²)
 */
void bubble_sort(void *arr, int n, size_t elem_size, CompareFn cmp);

/**
 * @brief Selection Sort - Ordenação por seleção
 *
 * Algoritmo não-estável que encontra o menor elemento e o coloca
 * na primeira posição, repetindo o processo.
 *
 * Complexidades:
 * - Melhor caso: O(n²)
 * - Caso médio: O(n²)
 * - Pior caso: O(n²)
 */
void selection_sort(void *arr, int n, size_t elem_size, CompareFn cmp);

/**
 * @brief Shaker Sort - Ordenação cocktail/bidirecional
 *
 * Variação do Bubble Sort que percorre o array em ambas as direções.
 *
 * Complexidades:
 * - Melhor caso: O(n)
 * - Caso médio: O(n²)
 * - Pior caso: O(n²)
 */
void shaker_sort(void *arr, int n, size_t elem_size, CompareFn cmp);

/**
 * @brief Shell Sort - Ordenação por incrementos
 *
 * Algoritmo não-estável que melhora o Insertion Sort comparando
 * elementos distantes.
 *
 * Complexidades:
 * - Melhor caso: O(n log n)
 * - Caso médio: O(n^1.25)
 * - Pior caso: O(n²)
 */
void shell_sort(void *arr, int n, size_t elem_size, CompareFn cmp);

/**
 * @brief Quick Sort - Ordenação por particionamento
 *
 * Algoritmo não-estável baseado em "dividir para conquistar".
 *
 * Complexidades:
 * - Melhor caso: O(n log n)
 * - Caso médio: O(n log n)
 * - Pior caso: O(n²)
 */
void quick_sort(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp);

/**
 * @brief Heap Sort - Ordenação por heap
 *
 * Algoritmo não-estável que usa árvore heap binária.
 *
 * Complexidades:
 * - Melhor caso: O(n log n)
 * - Caso médio: O(n log n)
 * - Pior caso: O(n log n)
 */
void heap_sort(void *arr, int n, size_t elem_size, CompareFn cmp);

/* ================================================================
 * VERSÕES ESPECÍFICAS - OTIMIZADAS E NÃO OTIMIZADAS
 * ================================================================ */

// Versões não otimizadas (didáticas)
void insertion_sort_naive(void *arr, int n, size_t elem_size, CompareFn cmp);
void bubble_sort_naive(void *arr, int n, size_t elem_size, CompareFn cmp);
void selection_sort_naive(void *arr, int n, size_t elem_size, CompareFn cmp);
void shaker_sort_naive(void *arr, int n, size_t elem_size, CompareFn cmp);
void shell_sort_naive(void *arr, int n, size_t elem_size, CompareFn cmp);
void quick_sort_naive(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp);
void heap_sort_naive(void *arr, int n, size_t elem_size, CompareFn cmp);

// Versões otimizadas
void insertion_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp);
void bubble_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp);
void selection_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp);
void shaker_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp);
void shell_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp);
void quick_sort_optimized(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp);
void heap_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp);

/* ================================================================
 * FUNÇÕES AUXILIARES
 * ================================================================ */

/**
 * @brief Ajusta heap para manter propriedade de heap binário
 * @param arr Ponteiro para o array/heap
 * @param n Tamanho do heap
 * @param i Índice da raiz da subárvore a ser ajustada
 * @param elem_size Tamanho de cada elemento
 * @param cmp Função de comparação
 */
void heapify(void *arr, int n, int i, size_t elem_size, CompareFn cmp);

/**
 * @brief Particiona array para o Quick Sort
 * @param arr Ponteiro para o array
 * @param inicio Índice inicial da partição
 * @param fim Índice final da partição
 * @param elem_size Tamanho de cada elemento
 * @param cmp Função de comparação
 * @return Nova posição do pivô
 */
int partition(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp);

// Versões otimizadas das funções auxiliares
void heapify_optimized(void *arr, int n, int i, size_t elem_size, CompareFn cmp);
void heapify_naive(void *arr, int n, int i, size_t elem_size, CompareFn cmp);
int partition_optimized(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp);
int partition_naive(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp);

#endif // ALGORITMOS_H
