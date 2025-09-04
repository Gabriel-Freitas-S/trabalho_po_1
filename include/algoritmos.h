/**
 * ==============================================================
 * ALGORITMOS DE ORDENAÇÃO - INTERFACES E DECLARAÇÕES PÚBLICAS
 * ==============================================================
 *
 * @file algoritmos.h
 * @brief Declarações completas de todos os algoritmos de ordenação implementados
 * @author Sistema de Análise de Performance de Algoritmos de Ordenação
 *
 * Este módulo contém as interfaces públicas (protótipos) de todos os algoritmos
 * de ordenação disponíveis no sistema. As implementações detalhadas encontram-se
 * no arquivo [`algoritmos.c`](src/algoritmos.c:1) correspondente, seguindo o princípio
 * de separação entre interface e implementação.
 *
 * **Arquitetura de versões duais:**
 * Cada algoritmo é implementado em duas variantes distintas:
 * - **Versão otimizada**: Foco em máxima performance e eficiência
 * - **Versão didática**: Foco em clareza, legibilidade e ensino
 *
 * **Vantagens da modularização:**
 * - Encapsulamento: clientes usam funções sem conhecer implementação
 * - Flexibilidade: múltiplas implementações para a mesma interface
 * - Manutenibilidade: mudanças na implementação não afetam clientes
 * - Testabilidade: interfaces bem definidas facilitam testes unitários
 *
 * **Padrão de nomenclatura:**
 * - Funções principais: `algoritmo_sort()` (selecionam versão automaticamente)
 * - Versões específicas: `algoritmo_sort_optimized()` e `algoritmo_sort_naive()`
 *
 * ==============================================================
 */

#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "tipos.h"

/* ==============================================================
 * ALGORITMOS PRINCIPAIS - INTERFACES ADAPTÁVEIS DE ALTO NÍVEL
 * ==============================================================
 *
 * **CONCEITO FUNDAMENTAL:**
 * Esta seção contém as interfaces principais dos algoritmos de ordenação,
 * que funcionam como "fachadas" inteligentes. Cada função automaticamente
 * seleciona entre a versão otimizada ou didática baseada na configuração
 * global do sistema, proporcionando flexibilidade sem complexidade.
 *
 * **CATEGORIAS DE ALGORITMOS IMPLEMENTADOS:**
 * - **Simples (O(n²))**: Bubble, Selection, Insertion - ideais para ensino
 * - **Avançados (O(n log n))**: Quick, Heap - ideais para produção
 * - **Híbridos**: Shell, Shaker - balanceiam simplicidade e eficiência
 *
 * **CRITÉRIOS DE SELEÇÃO DE ALGORITMOS:**
 * - Tamanho do dataset (pequeno vs. grande)
 * - Características dos dados (ordenados, aleatórios, inversos)
 * - Requisitos de estabilidade (preservar ordem de elementos iguais)
 * - Restrições de memória (in-place vs. auxiliar)
 * - Necessidade de previsibilidade temporal (worst-case garantido)
 */

/**
 * @brief Insertion Sort - Ordenação por Inserção
 *
 * COMO FUNCIONA?
 * Imagine que você está organizando cartas de baralho na sua mão:
 * 1. Você pega uma carta por vez
 * 2. Encontra o lugar certo para ela entre as cartas que já organizou
 * 3. Insere a carta nessa posição
 * 4. Repete o processo para todas as cartas
 *
 * QUANDO É BOM USAR?
 * - Para conjuntos pequenos de dados
 * - Quando os dados já estão quase ordenados
 * - Quando a simplicidade do código é mais importante que a velocidade
 *
 * VELOCIDADE:
 * - Melhor caso: Rápido (O(n)) - quando os dados já estão ordenados
 * - Caso médio: Lento (O(n²)) - para dados aleatórios
 * - Pior caso: Muito lento (O(n²)) - quando os dados estão em ordem inversa
 *
 * CARACTERÍSTICAS:
 * - É estável (mantém a ordem relativa de itens iguais)
 * - Funciona "in-place" (não precisa de espaço extra)
 */
void insertion_sort(void *arr, int n, size_t elem_size, CompareFn cmp);

/**
 * @brief Bubble Sort - Ordenação por Bolha
 *
 * COMO FUNCIONA?
 * É como bolhas subindo na água:
 * 1. Compara dois elementos vizinhos
 * 2. Troca-os se estiverem fora de ordem
 * 3. Continua comparando e trocando até o final do array
 * 4. Repete o processo até que nenhuma troca seja necessária
 *
 * QUANDO É BOM USAR?
 * - Para fins educativos (aprender sobre ordenação)
 * - Em conjuntos de dados muito pequenos
 * - Quando o código simples é mais importante que a performance
 *
 * VELOCIDADE:
 * - Melhor caso: Razoável (O(n)) - quando os dados já estão ordenados
 * - Caso médio: Lento (O(n²)) - para dados aleatórios
 * - Pior caso: Muito lento (O(n²)) - quando o maior elemento está no início
 *
 * CARACTERÍSTICAS:
 * - É estável (mantém a ordem relativa de itens iguais)
 * - Muito fácil de implementar
 */
void bubble_sort(void *arr, int n, size_t elem_size, CompareFn cmp);

/**
 * @brief Selection Sort - Ordenação por Seleção
 *
 * COMO FUNCIONA?
 * Como selecionar o menor item e colocá-lo no lugar certo:
 * 1. Encontra o menor elemento no array não-ordenado
 * 2. Coloca-o na primeira posição do array não-ordenado
 * 3. Repete para o restante do array não-ordenado
 *
 * QUANDO É BOM USAR?
 * - Quando o custo de trocar elementos é alto
 * - Para conjuntos de dados pequenos
 * - Quando você precisa de um algoritmo simples
 *
 * VELOCIDADE:
 * - Melhor caso: Lento (O(n²)) - mesmo para dados já ordenados
 * - Caso médio: Lento (O(n²)) - para qualquer tipo de dados
 * - Pior caso: Lento (O(n²)) - performance consistente
 *
 * CARACTERÍSTICAS:
 * - NÃO é estável (pode mudar a ordem relativa de itens iguais)
 * - Faz menos trocas que outros algoritmos simples
 */
void selection_sort(void *arr, int n, size_t elem_size, CompareFn cmp);

/**
 * @brief Shaker Sort - Ordenação Coquetel (Vai e Vem)
 *
 * COMO FUNCIONA?
 * É um Bubble Sort melhorado que vai nas duas direções:
 * 1. Faz uma passagem do Bubble Sort do início ao fim (como bolhas subindo)
 * 2. Depois faz outra passagem do fim ao início (como bolhas descendo)
 * 3. Repete até que não ocorram mais trocas
 *
 * QUANDO É BOM USAR?
 * - Quando os dados têm "tartarugas" (pequenos valores no final do array)
 * - Como uma alternativa ligeiramente melhor ao Bubble Sort
 *
 * VELOCIDADE:
 * - Melhor caso: Razoável (O(n)) - para dados já ordenados
 * - Caso médio: Lento (O(n²)) - para dados aleatórios
 * - Pior caso: Lento (O(n²)) - mas geralmente melhor que o Bubble Sort
 *
 * CARACTERÍSTICAS:
 * - É estável (mantém a ordem relativa de itens iguais)
 * - Resolve o problema das "tartarugas" do Bubble Sort
 */
void shaker_sort(void *arr, int n, size_t elem_size, CompareFn cmp);

/**
 * @brief Shell Sort - Ordenação por Incrementos Diminutivos
 *
 * COMO FUNCIONA?
 * É uma versão melhorada do Insertion Sort:
 * 1. Organiza elementos distantes um do outro primeiro
 * 2. Gradualmente reduz a distância entre os elementos comparados
 * 3. Termina com um Insertion Sort normal (distância = 1)
 *
 * QUANDO É BOM USAR?
 * - Para conjuntos de tamanho médio
 * - Quando você precisa de um algoritmo sem recursão
 * - Como uma alternativa mais rápida aos algoritmos simples
 *
 * VELOCIDADE:
 * - Melhor caso: Bom (O(n log n)) - dependendo da sequência de incrementos
 * - Caso médio: Razoável (O(n^1.25)) - melhor que O(n²)
 * - Pior caso: Lento (O(n²)) - mas raramente ocorre
 *
 * CARACTERÍSTICAS:
 * - NÃO é estável (pode mudar a ordem relativa de itens iguais)
 * - A eficiência depende muito da sequência de incrementos escolhida
 */
void shell_sort(void *arr, int n, size_t elem_size, CompareFn cmp);

/**
 * @brief Quick Sort - Ordenação Rápida
 *
 * COMO FUNCIONA?
 * Usa a estratégia "dividir para conquistar":
 * 1. Escolhe um elemento como "pivô"
 * 2. Reorganiza o array: menores que o pivô à esquerda, maiores à direita
 * 3. Repete o processo recursivamente para as duas metades
 *
 * QUANDO É BOM USAR?
 * - Para conjuntos grandes de dados
 * - Quando você precisa de performance média excelente
 * - Como algoritmo de uso geral para ordenação
 *
 * VELOCIDADE:
 * - Melhor caso: Muito bom (O(n log n)) - com pivô balanceado
 * - Caso médio: Muito bom (O(n log n)) - para dados aleatórios
 * - Pior caso: Muito lento (O(n²)) - quando o pivô é sempre o menor/maior elemento
 *
 * CARACTERÍSTICAS:
 * - NÃO é estável (pode mudar a ordem relativa de itens iguais)
 * - É recursivo (usa a pilha de chamadas)
 * - Geralmente o mais rápido na prática para conjuntos grandes
 */
void quick_sort(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp);

/**
 * @brief Heap Sort - Ordenação por Montículo
 *
 * COMO FUNCIONA?
 * Usa uma estrutura de dados especial chamada "heap":
 * 1. Transforma o array em uma árvore binária especial (heap)
 * 2. Extrai repetidamente o elemento máximo dessa árvore
 * 3. Coloca cada máximo na posição correta do array
 *
 * QUANDO É BOM USAR?
 * - Para garantir boa performance em todos os casos
 * - Quando você precisa de um algoritmo sem casos patológicos
 * - Para sistemas que não podem tolerar variações de performance
 *
 * VELOCIDADE:
 * - Melhor caso: Bom (O(n log n)) - mesmo para dados já ordenados
 * - Caso médio: Bom (O(n log n)) - consistente para qualquer dado
 * - Pior caso: Bom (O(n log n)) - sem casos degenerados
 *
 * CARACTERÍSTICAS:
 * - NÃO é estável (pode mudar a ordem relativa de itens iguais)
 * - Performance consistente (sem casos especiais ruins)
 * - Usa espaço constante (sem recursão ou espaço extra)
 */
void heap_sort(void *arr, int n, size_t elem_size, CompareFn cmp);

/* ==============================================================
 * VERSÕES ESPECÍFICAS - IMPLEMENTAÇÕES ESPECIALIZADAS
 * ==============================================================
 *
 * **FILOSOFIA DE DESIGN DUAL:**
 * O sistema implementa cada algoritmo em duas variantes distintas,
 * cada uma otimizada para objetivos específicos. Esta abordagem
 * atende tanto necessidades pedagógicas quanto requisitos de produção.
 *
 * **VERSÕES DIDÁTICAS (NAIVE):**
 * - **Objetivo**: Máxima clareza e compreensibilidade
 * - **Características**: Código linear, estruturas simples, sem otimizações
 * - **Público-alvo**: Estudantes, ensino de algoritmos, depuração
 * - **Trade-off**: Sacrifica performance em favor da legibilidade
 * - **Exemplo**: Loops explícitos, variáveis com nomes descritivos
 *
 * **VERSÕES OTIMIZADAS (OPTIMIZED):**
 * - **Objetivo**: Máxima performance e eficiência
 * - **Características**: Técnicas avançadas, minimização de operações
 * - **Público-alvo**: Produção, benchmarks, análise de performance
 * - **Trade-off**: Pode sacrificar legibilidade em favor da velocidade
 * - **Exemplo**: Loop unrolling, otimizações de branch prediction
 *
 * **CRITÉRIOS DE OTIMIZAÇÃO APLICADOS:**
 * - Redução de comparações redundantes
 * - Detecção precoce de arrays já ordenados
 * - Otimização de acesso à memória (cache-friendly)
 * - Minimização de operações de troca/movimento
 * - Uso de técnicas específicas por algoritmo (ex: median-of-three no Quick Sort)
 */

// Versões não otimizadas (didáticas) - mais simples de entender
void insertion_sort_naive(void *arr, int n, size_t elem_size, CompareFn cmp);
void bubble_sort_naive(void *arr, int n, size_t elem_size, CompareFn cmp);
void selection_sort_naive(void *arr, int n, size_t elem_size, CompareFn cmp);
void shaker_sort_naive(void *arr, int n, size_t elem_size, CompareFn cmp);
void shell_sort_naive(void *arr, int n, size_t elem_size, CompareFn cmp);
void quick_sort_naive(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp);
void heap_sort_naive(void *arr, int n, size_t elem_size, CompareFn cmp);

// Versões otimizadas - mais eficientes, para uso real
void insertion_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp);
void bubble_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp);
void selection_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp);
void shaker_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp);
void shell_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp);
void quick_sort_optimized(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp);
void heap_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp);

/* ==============================================================
 * PADRÃO STRATEGY - SELEÇÃO DINÂMICA DE IMPLEMENTAÇÕES
 * ==============================================================
 *
 * **DESIGN PATTERN IMPLEMENTADO:**
 * As funções principais (ex: [`insertion_sort()`](include/algoritmos.h:65), [`bubble_sort()`](include/algoritmos.h:91))
 * implementam o padrão Strategy, permitindo alternar entre diferentes
 * implementações em runtime baseado em configuração global.
 *
 * **ARQUITETURA DA SELEÇÃO:**
 * ```c
 * void insertion_sort(void *arr, int n, size_t elem_size, CompareFn cmp) {
 *     if (usar_versao_otimizada) {
 *         insertion_sort_optimized(arr, n, elem_size, cmp);
 *     } else {
 *         insertion_sort_naive(arr, n, elem_size, cmp);
 *     }
 * }
 * ```
 *
 * **VANTAGENS DA ABORDAGEM UNIFICADA:**
 * - **Transparência**: Cliente não precisa decidir qual versão usar
 * - **Flexibilidade**: Mudança de estratégia sem alterar código cliente
 * - **Configurabilidade**: Uma única flag controla todo o sistema
 * - **Compatibilidade**: Interface consistente independente da implementação
 * - **Facilidade de teste**: Comparação direta entre versões
 *
 * **ALTERNATIVA ARQUITETURAL:**
 * Chamadas diretas às versões específicas (ex: `insertion_sort_optimized()`)
 * seriam mais explícitas mas menos flexíveis, exigindo decisões
 * distribuídas pelo código cliente.
 *
 * **OVERHEAD DE PERFORMANCE:**
 * O custo adicional de uma decisão `if/else` por chamada é negligível
 * comparado ao custo de execução dos algoritmos de ordenação.
 */

/* ==============================================================
 * FUNÇÕES AUXILIARES E PRIMITIVAS DE ORDENAÇÃO
 * ==============================================================
 *
 * **CONCEITO DE FUNÇÕES AUXILIARES:**
 * Estas funções implementam operações fundamentais e específicas
 * que são utilizadas como blocos de construção pelos algoritmos
 * principais. Seguem o princípio de responsabilidade única,
 * focando em tarefas bem definidas e reutilizáveis.
 *
 * **CATEGORIAS DE FUNÇÕES AUXILIARES:**
 * - **Primitivas de heap**: [`heapify()`](include/algoritmos.h:313) para manutenção da propriedade de montículo
 * - **Primitivas de particionamento**: [`partition()`](include/algoritmos.h:324) para divisão no Quick Sort
 * - **Utilitários de comparação**: Abstraem lógica de comparação específica
 * - **Manipuladores de dados**: Operações de troca e movimentação
 *
 * **VANTAGENS DA MODULARIZAÇÃO:**
 * - **Reutilização**: Uma função auxiliar pode servir múltiplos algoritmos
 * - **Testabilidade**: Cada função pode ser testada independentemente
 * - **Clareza**: Algoritmos principais ficam mais legíveis
 * - **Manutenibilidade**: Correções em um local beneficiam todo o sistema
 * - **Especialização**: Cada função tem responsabilidade bem definida
 */

/**
 * @brief Ajusta um montículo (heap) para manter sua propriedade especial
 *
 * COMO FUNCIONA?
 * 1. Verifica se um nó pai é maior que seus filhos na árvore heap
 * 2. Se não for, troca o pai com o maior dos filhos
 * 3. Continua o processo até que a propriedade do heap seja restaurada
 *
 * PARA QUE SERVE?
 * Esta função é usada pelo Heap Sort para garantir que o maior elemento
 * esteja sempre na raiz da árvore.
 *
 * PARÂMETROS:
 * @param arr - O array que representa o heap
 * @param n - O tamanho do heap
 * @param i - O índice do nó raiz da subárvore a ser ajustada
 * @param elem_size - O tamanho de cada elemento no array em bytes
 * @param cmp - A função que compara dois elementos
 */
void heapify(void *arr, int n, int i, size_t elem_size, CompareFn cmp);

/**
 * @brief Particiona um array para o Quick Sort
 *
 * COMO FUNCIONA?
 * 1. Escolhe um elemento como pivô (geralmente o último)
 * 2. Coloca todos os elementos menores que o pivô à esquerda
 * 3. Coloca todos os elementos maiores que o pivô à direita
 * 4. Retorna a posição final do pivô
 */
int partition(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp);

// Versões otimizadas das funções auxiliares
void heapify_optimized(void *arr, int n, int i, size_t elem_size, CompareFn cmp);
void heapify_naive(void *arr, int n, int i, size_t elem_size, CompareFn cmp);
int partition_optimized(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp);
int partition_naive(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp);

#endif // ALGORITMOS_H
