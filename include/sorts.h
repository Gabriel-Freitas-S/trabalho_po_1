/**
 * ================================================================
 * TRABALHO DE ALGORITMOS DE ORDENAÇÃO - HEADER PRINCIPAL
 * ================================================================
 *
 * @file sorts.h
 * @brief Definições, estruturas e protótipos para análise comparativa
 *        de algoritmos de ordenação
 * @version 2.0
 * @date 2025-08-23
 * @author Sistema de Análise de Algoritmos
 *
 * Este arquivo contém todas as definições necessárias para a
 * implementação e análise de 7 algoritmos de ordenação diferentes,
 * com suporte para dados genéricos e métricas detalhadas.
 *
 * Características principais:
 * - Algoritmos genéricos que funcionam com qualquer tipo de dados
 * - Medição precisa de tempo, comparações e trocas
 * - Análise de estabilidade automática
 * - Geração de relatórios detalhados
 * - Organização automática de arquivos de saída
 *
 * ================================================================
 */

#ifndef SORTS_H
#define SORTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ================================================================
 * ESTRUTURAS DE DADOS
 * ================================================================ */

/**
 * @struct Aluno
 * @brief Estrutura para representar dados de um aluno
 *
 * Contém informações pessoais do aluno utilizadas para demonstrar
 * ordenação por múltiplos critérios e análise de estabilidade.
 *
 * @var nome Nome completo do aluno (até 100 caracteres)
 * @var data_nascimento Data no formato DD/MM/AAAA
 * @var bairro Bairro de residência (critério primário de ordenação)
 * @var cidade Cidade de residência
 */
typedef struct {
    char nome[100];
    char data_nascimento[20];
    char bairro[50];
    char cidade[50];
} Aluno;

/**
 * @struct ResultadoTempo
 * @brief Estrutura para armazenar métricas de desempenho de algoritmos
 *
 * Utilizada para coletar e organizar dados de performance dos
 * algoritmos de ordenação, incluindo tempo de execução e operações.
 *
 * @var algoritmo Nome do algoritmo testado
 * @var tempo_execucao Tempo de execução em segundos (precisão de microssegundos)
 * @var tamanho_dados Quantidade de elementos processados
 * @var tipo_dados Tipo de dados processados ("numeros" ou "alunos")
 * @var comparacoes Número total de comparações realizadas
 * @var trocas Número total de trocas/movimentações realizadas
 */
typedef struct {
    char algoritmo[30];
    double tempo_execucao;
    int tamanho_dados;
    char tipo_dados[20];
    long long comparacoes;
    long long trocas;
} ResultadoTempo;

/**
 * @typedef CompareFn
 * @brief Ponteiro para função de comparação genérica
 *
 * Permite que os algoritmos trabalhem com qualquer tipo de dados,
 * seguindo o padrão da função qsort() da biblioteca padrão C.
 *
 * @param a Ponteiro para o primeiro elemento
 * @param b Ponteiro para o segundo elemento
 * @return Valor negativo se a < b, 0 se a == b, positivo se a > b
 */
typedef int (*CompareFn)(const void *a, const void *b);

/**
 * @struct AlgoritmoInfo
 * @brief Estrutura unificada com informações completas de um algoritmo
 *
 * Centraliza todas as informações e ponteiros de função necessários
 * para executar e analisar cada algoritmo de ordenação.
 *
 * @var nome Nome identificador do algoritmo
 * @var complexidade_melhor Complexidade no melhor caso (notação Big-O)
 * @var complexidade_media Complexidade no caso médio (notação Big-O)
 * @var complexidade_pior Complexidade no pior caso (notação Big-O)
 * @var eh_estavel Flag indicando se o algoritmo preserva ordem de elementos iguais
 * @var sort_fn Ponteiro para função de ordenação padrão (se aplicável)
 * @var quick_sort_fn Ponteiro para função Quick Sort (caso especial)
 * @var eh_quick Flag indicando se usa interface especial do Quick Sort
 */
typedef struct {
    char nome[30];
    char complexidade_melhor[15];
    char complexidade_media[15];
    char complexidade_pior[15];
    int eh_estavel;
    void (*sort_fn)(void *arr, int n, size_t elem_size, CompareFn cmp);
    void (*quick_sort_fn)(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp);
    int eh_quick;
} AlgoritmoInfo;

/* ================================================================
 * PROTÓTIPOS DOS ALGORITMOS DE ORDENAÇÃO
 * ================================================================ */

/**
 * @brief Algoritmo Insertion Sort - Ordenação por inserção
 *
 * Algoritmo estável que constrói a sequência ordenada inserindo
 * elementos um por vez na posição correta. Eficiente para pequenos
 * conjuntos de dados e dados parcialmente ordenados.
 *
 * Complexidades:
 * - Melhor caso: O(n) - dados já ordenados
 * - Caso médio: O(n²)
 * - Pior caso: O(n²) - dados em ordem reversa
 *
 * @param arr Ponteiro para o array a ser ordenado
 * @param n Número de elementos no array
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação
 */
void insertion_sort(void *arr, int n, size_t elem_size, CompareFn cmp);

/**
 * @brief Algoritmo Bubble Sort - Ordenação por bolha
 *
 * Algoritmo estável que compara elementos adjacentes e os troca
 * se estiverem na ordem errada. Simple mas ineficiente para
 * grandes conjuntos de dados.
 *
 * Complexidades:
 * - Melhor caso: O(n) - dados já ordenados (com otimização)
 * - Caso médio: O(n²)
 * - Pior caso: O(n²)
 *
 * @param arr Ponteiro para o array a ser ordenado
 * @param n Número de elementos no array
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação
 */
void bubble_sort(void *arr, int n, size_t elem_size, CompareFn cmp);

/**
 * @brief Algoritmo Selection Sort - Ordenação por seleção
 *
 * Algoritmo não-estável que encontra o menor elemento e o coloca
 * na primeira posição, repetindo o processo para as demais posições.
 *
 * Complexidades:
 * - Melhor caso: O(n²)
 * - Caso médio: O(n²)
 * - Pior caso: O(n²)
 *
 * @param arr Ponteiro para o array a ser ordenado
 * @param n Número de elementos no array
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação
 */
void selection_sort(void *arr, int n, size_t elem_size, CompareFn cmp);

/**
 * @brief Algoritmo Shaker Sort - Ordenação cocktail/bidirecional
 *
 * Variação do Bubble Sort que percorre o array em ambas as direções,
 * melhorando o desempenho em alguns casos específicos.
 *
 * Complexidades:
 * - Melhor caso: O(n)
 * - Caso médio: O(n²)
 * - Pior caso: O(n²)
 *
 * @param arr Ponteiro para o array a ser ordenado
 * @param n Número de elementos no array
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação
 */
void shaker_sort(void *arr, int n, size_t elem_size, CompareFn cmp);

/**
 * @brief Algoritmo Shell Sort - Ordenação por incrementos
 *
 * Algoritmo não-estável que melhora o Insertion Sort comparando
 * elementos distantes. Usa sequência de incrementos para reduzir
 * gradualmente a distância entre comparações.
 *
 * Complexidades:
 * - Melhor caso: O(n log n)
 * - Caso médio: O(n^1.25) - depende da sequência de incrementos
 * - Pior caso: O(n²)
 *
 * @param arr Ponteiro para o array a ser ordenado
 * @param n Número de elementos no array
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação
 */
void shell_sort(void *arr, int n, size_t elem_size, CompareFn cmp);

/**
 * @brief Algoritmo Quick Sort - Ordenação por particionamento
 *
 * Algoritmo não-estável baseado no paradigma "dividir para conquistar".
 * Escolhe um pivô, particiona o array e ordena recursivamente.
 *
 * Complexidades:
 * - Melhor caso: O(n log n)
 * - Caso médio: O(n log n)
 * - Pior caso: O(n²) - quando o pivô é sempre o menor/maior elemento
 *
 * @param arr Ponteiro para o array a ser ordenado
 * @param inicio Índice inicial da partição
 * @param fim Índice final da partição
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação
 */
void quick_sort(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp);

/**
 * @brief Algoritmo Heap Sort - Ordenação por heap
 *
 * Algoritmo não-estável que constrói uma árvore heap binária e
 * extrai sucessivamente o maior elemento. Garante O(n log n)
 * em todos os casos.
 *
 * Complexidades:
 * - Melhor caso: O(n log n)
 * - Caso médio: O(n log n)
 * - Pior caso: O(n log n)
 *
 * @param arr Ponteiro para o array a ser ordenado
 * @param n Número de elementos no array
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação
 */
void heap_sort(void *arr, int n, size_t elem_size, CompareFn cmp);

/* ================================================================
 * FUNÇÕES AUXILIARES DOS ALGORITMOS
 * ================================================================ */

/**
 * @brief Ajusta heap para manter propriedade de heap binário
 *
 * Função auxiliar do Heap Sort que garante que a subárvore com
 * raiz no índice i mantenha a propriedade de heap máximo.
 *
 * @param arr Ponteiro para o array/heap
 * @param n Tamanho do heap
 * @param i Índice da raiz da subárvore a ser ajustada
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação
 */
void heapify(void *arr, int n, int i, size_t elem_size, CompareFn cmp);

/**
 * @brief Particiona array para o Quick Sort
 *
 * Reorganiza o array colocando elementos menores que o pivô à esquerda
 * e maiores à direita. Retorna a posição final do pivô.
 *
 * @param arr Ponteiro para o array
 * @param inicio Índice inicial da partição
 * @param fim Índice final da partição (posição do pivô)
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação
 * @return Nova posição do pivô após particionamento
 */
int partition(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp);

/**
 * @brief Troca dois elementos de tamanho genérico
 *
 * Função auxiliar que troca o conteúdo de dois elementos de qualquer tipo,
 * usando um buffer temporário para preservar os dados.
 *
 * @param a Ponteiro para o primeiro elemento
 * @param b Ponteiro para o segundo elemento
 * @param elem_size Tamanho de cada elemento em bytes
 */
void swap_elements(void *a, void *b, size_t elem_size);

/* ================================================================
 * FUNÇÕES DE COMPARAÇÃO
 * ================================================================ */

/**
 * @brief Função de comparação para inteiros
 *
 * Compara dois valores inteiros.
 *
 * @param a Ponteiro para o primeiro inteiro
 * @param b Ponteiro para o segundo inteiro
 * @return Valor negativo se a < b, 0 se a == b, positivo se a > b
 */
int comparar_inteiros(const void *a, const void *b);

/**
 * @brief Função de comparação para alunos
 *
 * Compara dois alunos primeiramente pelo bairro e em seguida pelo nome.
 *
 * @param a Ponteiro para o primeiro aluno
 * @param b Ponteiro para o segundo aluno
 * @return Valor negativo se a < b, 0 se a == b, positivo se a > b
 */
int comparar_alunos(const void *a, const void *b);

/* ================================================================
 * FUNÇÕES DE I/O
 * ================================================================ */

/**
 * @brief Lê um arquivo de números inteiros
 *
 * Lê os números de um arquivo e armazena em um array dinâmico.
 *
 * @param caminho_arquivo Caminho para o arquivo de entrada
 * @param tamanho Ponteiro para variável que receberá o tamanho do array
 * @return Ponteiro para o array de números inteiros
 */
int* ler_numeros(const char* caminho_arquivo, int* tamanho);

/**
 * @brief Lê um arquivo de dados de alunos
 *
 * Lê os dados de alunos de um arquivo e armazena em um array dinâmico.
 *
 * @param caminho_arquivo Caminho para o arquivo de entrada
 * @param tamanho Ponteiro para variável que receberá o tamanho do array
 * @return Ponteiro para o array de estruturas Aluno
 */
Aluno* ler_alunos(const char* caminho_arquivo, int* tamanho);

/**
 * @brief Salva um array de números inteiros em arquivo
 *
 * Escreve os números de um array em um arquivo texto.
 *
 * @param caminho_arquivo Caminho para o arquivo de saída
 * @param arr Array de números inteiros
 * @param tamanho Tamanho do array
 */
void salvar_numeros(const char* caminho_arquivo, int arr[], int tamanho);

/**
 * @brief Salva um array de dados de alunos em arquivo
 *
 * Escreve os dados de alunos de um array em um arquivo texto.
 *
 * @param caminho_arquivo Caminho para o arquivo de saída
 * @param arr Array de estruturas Aluno
 * @param tamanho Tamanho do array
 */
void salvar_alunos(const char* caminho_arquivo, Aluno arr[], int tamanho);

/* ================================================================
 * FUNÇÕES DE MEDIÇÃO E ANÁLISE
 * ================================================================ */

/**
 * @brief Mede o tempo de execução de um algoritmo de ordenação
 *
 * Executa o algoritmo de ordenação passado como parâmetro e mede
 * o tempo que leva para ordenar os dados.
 *
 * @param sort_fn Ponteiro para a função do algoritmo de ordenação
 * @param arr Ponteiro para o array a ser ordenado
 * @param n Número de elementos no array
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação
 * @return Tempo de execução em segundos
 */
double medir_tempo_ordenacao(void (*sort_fn)(void*, int, size_t, CompareFn),
                            void *arr, int n, size_t elem_size, CompareFn cmp);

/**
 * @brief Mede o tempo de execução do Quick Sort
 *
 * Executa o Quick Sort e mede o tempo que leva para ordenar os dados.
 *
 * @param quick_fn Ponteiro para a função Quick Sort
 * @param arr Ponteiro para o array a ser ordenado
 * @param n Número de elementos no array
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação
 * @return Tempo de execução em segundos
 */
double medir_tempo_quick_sort(void (*quick_fn)(void*, int, int, size_t, CompareFn),
                            void *arr, int n, size_t elem_size, CompareFn cmp);

/**
 * @brief Gera um relatório de tempos de execução
 *
 * Cria um arquivo texto com um relatório detalhado dos tempos de
 * execução dos algoritmos testados.
 *
 * @param resultados Array de estruturas ResultadoTempo com os dados a serem salvos
 * @param num_resultados Número de resultados a serem salvos
 * @param arquivo_saida Caminho para o arquivo de saída
 */
void gerar_relatorio_tempos(ResultadoTempo resultados[], int num_resultados, const char* arquivo_saida);

/**
 * @brief Analisa a estabilidade dos algoritmos
 *
 * Executa testes para verificar se os algoritmos preservam a ordem
 * relativa de elementos iguais.
 */
void analisar_estabilidade();

/**
 * @brief Executa todos os algoritmos em um conjunto de dados
 *
 * Chama cada algoritmo de ordenação em todos os tipos de dados
 * disponíveis e salva os resultados em arquivos separados.
 *
 * @param dados Ponteiro para os dados a serem ordenados
 * @param tamanho Tamanho dos dados
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação
 * @param tipo_dados Tipo de dados ("numeros" ou "alunos")
 * @param arquivo_base Prefixo para os arquivos de saída
 */
void executar_todos_algoritmos(void *dados, int tamanho, size_t elem_size, CompareFn cmp,
                              const char* tipo_dados, const char* arquivo_base);

/* ================================================================
 * FUNÇÕES UTILITÁRIAS
 * ================================================================ */

/**
 * @brief Copia um array para outro
 *
 * Copia os dados de um array de origem para um array de destino,
 * utilizando a função de comparação para determinar a ordem.
 *
 * @param origem Ponteiro para o array de origem
 * @param destino Ponteiro para o array de destino
 * @param tamanho Tamanho do array (número de elementos)
 * @param elem_size Tamanho de cada elemento em bytes
 */
void copiar_array(const void *origem, void *destino, int tamanho, size_t elem_size);

/**
 * @brief Imprime o menu de opções
 *
 * Exibe o menu principal com as opções disponíveis para o usuário.
 */
void imprimir_menu();

/**
 * @brief Obtém informações sobre os algoritmos disponíveis
 *
 * Retorna um array de estruturas AlgoritmoInfo com os dados de
 * todos os algoritmos implementados.
 *
 * @return Ponteiro para o array de estruturas AlgoritmoInfo
 */
AlgoritmoInfo* obter_info_algoritmos();

/**
 * @brief Imprime o cabeçalho do programa
 *
 * Exibe o cabeçalho com informações sobre o trabalho e os autores.
 */
void imprimir_cabecalho();

/* ================================================================
 * CONSTANTES
 * ================================================================ */

/**
 * @def NUM_ALGORITMOS
 * Número total de algoritmos de ordenação implementados
 */
#define NUM_ALGORITMOS 7

/**
 * @def MAX_PATH
 * Tamanho máximo para caminhos de arquivos
 */
#define MAX_PATH 256

/**
 * @def SUCESSO
 * Código de sucesso para operações
 */
#define SUCESSO 0

/**
 * @def ERRO_ARQUIVO
 * Código de erro para operações de arquivo
 */
#define ERRO_ARQUIVO -1

/**
 * @def ERRO_MEMORIA
 * Código de erro para alocação de memória
 */
#define ERRO_MEMORIA -2

/* ================================================================
 * VARIÁVEIS GLOBAIS PARA CONTAGEM
 * ================================================================ */

/**
 * @var contador_comparacoes
 * Contador global para o número de comparações realizadas
 */
extern long long contador_comparacoes;

/**
 * @var contador_trocas
 * Contador global para o número de trocas realizadas
 */
extern long long contador_trocas;

/* ================================================================
 * FUNÇÕES PARA CRIAR DIRETÓRIOS
 * ================================================================ */

/**
 * @brief Cria os diretórios necessários para saída de arquivos
 *
 * Verifica e cria os diretórios onde os arquivos de saída serão
 * armazenados.
 */
void criar_diretorios_output();

/**
 * @brief Limpa o terminal
 *
 * Limpa a tela do terminal para melhor apresentação dos resultados.
 */
void limpar_terminal();

#endif // SORTS_H
