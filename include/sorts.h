/**
 * ================================================================
 * TRABALHO DE ALGORITMOS DE ORDENAÇÃO - HEADER PRINCIPAL
 * ================================================================
 *
 * @file sorts.h
 * @brief Definições, estruturas e protótipos para análise comparativa
 *        de algoritmos de ordenação
 * @version 2.1
 * @date 2025-08-24
 * @author Sistema de Análise de Algoritmos
 *
 * Este arquivo contém todas as definições necessárias para a
 * implementação e análise de 7 algoritmos de ordenação diferentes,
 * com suporte para dados genéricos e métricas detalhadas de performance.
 *
 * VERSÃO 2.1: Sistema de Medição de Alta Precisão e Análise Comparativa
 * - Medição de tempo com precisão de nanossegundos multiplataforma
 * - Suporte completo para Windows, Linux e macOS
 * - Medição adaptativa baseada no tamanho do conjunto de dados
 * - Eliminação completa de medições zeradas através de múltiplas execuções
 * - Cálculo de médias estatísticas para maior confiabilidade dos resultados
 * - Sistema dual com versões otimizadas e não otimizadas para comparação
 *
 * Características principais:
 * - Algoritmos genéricos compatíveis com qualquer tipo de dados
 * - Medição precisa de tempo, comparações e operações de troca
 * - Análise automatizada de estabilidade com casos de teste reais
 * - Geração de relatórios detalhados em múltiplos formatos
 * - Organização automática de arquivos de saída por categoria
 * - Sistema de alta precisão para algoritmos com execução muito rápida
 * - Interface unificada que alterna entre versões otimizadas automaticamente
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
 * CONFIGURAÇÕES DE OTIMIZAÇÃO E CONTROLE DE VERSÕES
 * ================================================================ */

/**
 * @brief Flag global para controlar uso de versões otimizadas
 *
 * Esta variável determina qual versão dos algoritmos será utilizada:
 * - Valor 1: utiliza implementações otimizadas (máxima performance)
 * - Valor 0: utiliza implementações não otimizadas (didáticas/comparativas)
 *
 * @note A alternância entre versões permite análise comparativa de
 *       diferentes estratégias de implementação dos mesmos algoritmos
 */
extern int usar_versao_otimizada;

/**
 * @brief Configura o sistema para usar versão otimizada ou não otimizada
 *
 * Permite alternar dinamicamente entre as duas versões de implementação
 * de todos os algoritmos, facilitando análises comparativas de performance.
 *
 * @param otimizada 1 para usar versões otimizadas, 0 para versões didáticas
 */
void configurar_otimizacao(int otimizada);

/* ================================================================
 * ESTRUTURAS DE DADOS E DEFINIÇÕES DE TIPOS
 * ================================================================ */

/**
 * @typedef CompareFn
 * @brief Ponteiro para função de comparação genérica
 *
 * Define o tipo de função utilizada para comparar elementos durante
 * a ordenação. Segue o padrão da biblioteca padrão C (qsort), permitindo
 * que os algoritmos trabalhem com qualquer tipo de dados de forma genérica.
 *
 * @param a Ponteiro para o primeiro elemento a ser comparado
 * @param b Ponteiro para o segundo elemento a ser comparado
 * @return Valor negativo se a < b, zero se a == b, valor positivo se a > b
 */
typedef int (*CompareFn)(const void *a, const void *b);

/**
 * @struct Aluno
 * @brief Estrutura para representar dados acadêmicos de um estudante
 *
 * Contém informações pessoais e acadêmicas do aluno, utilizada para
 * demonstrar ordenação por múltiplos critérios e análise de estabilidade
 * dos algoritmos com dados reais estruturados.
 *
 * @var nome Nome completo do estudante (máximo 99 caracteres + terminador)
 * @var data_nascimento Data de nascimento no formato DD/MM/AAAA
 * @var bairro Bairro de residência (critério primário de ordenação)
 * @var cidade Cidade de residência (critério secundário quando aplicável)
 */
typedef struct {
    char nome[100];
    char data_nascimento[20];
    char bairro[50];
    char cidade[50];
} Aluno;

/**
 * @struct ResultadoTempo
 * @brief Estrutura para armazenar métricas completas de performance
 *
 * Centraliza todas as métricas coletadas durante a execução dos algoritmos
 * de ordenação, incluindo tempo de execução e contadores de operações.
 * Utilizada para geração de relatórios detalhados e análises comparativas.
 *
 * @var algoritmo Nome identificador do algoritmo testado
 * @var tempo_execucao Tempo total de execução em segundos (precisão de nanossegundos)
 * @var tamanho_dados Quantidade de elementos processados no teste
 * @var tipo_dados Tipo de dados processados ("numeros" ou "alunos")
 * @var comparacoes Número total de comparações realizadas durante a ordenação
 * @var trocas Número total de trocas/movimentações de elementos realizadas
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
 * @struct AlgoritmoInfo
 * @brief Estrutura unificada com metadados completos de um algoritmo
 *
 * Centraliza todas as informações teóricas e ponteiros de função necessários
 * para executar e analisar cada algoritmo de ordenação. Permite tratamento
 * uniforme de todos os algoritmos através de uma interface comum.
 *
 * @var nome Nome descritivo do algoritmo para exibição
 * @var complexidade_melhor Complexidade temporal no melhor caso (notação Big-O)
 * @var complexidade_media Complexidade temporal no caso médio (notação Big-O)
 * @var complexidade_pior Complexidade temporal no pior caso (notação Big-O)
 * @var eh_estavel Flag indicando se preserva a ordem relativa de elementos iguais
 * @var sort_fn Ponteiro para função de ordenação padrão (interface unificada)
 * @var quick_sort_fn Ponteiro específico para Quick Sort (interface especializada)
 * @var eh_quick Flag indicando se utiliza interface especializada do Quick Sort
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
 * PROTÓTIPOS DOS ALGORITMOS - VERSÕES NÃO OTIMIZADAS
 * ================================================================ */

/**
 * @brief Versões não otimizadas dos algoritmos (didáticas)
 */
void insertion_sort_naive(void *arr, int n, size_t elem_size, CompareFn cmp);
void bubble_sort_naive(void *arr, int n, size_t elem_size, CompareFn cmp);
void selection_sort_naive(void *arr, int n, size_t elem_size, CompareFn cmp);
void shaker_sort_naive(void *arr, int n, size_t elem_size, CompareFn cmp);
void shell_sort_naive(void *arr, int n, size_t elem_size, CompareFn cmp);
void quick_sort_naive(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp);
void heap_sort_naive(void *arr, int n, size_t elem_size, CompareFn cmp);

/**
 * @brief Versões otimizadas dos algoritmos (implementações originais)
 */
void insertion_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp);
void bubble_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp);
void selection_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp);
void shaker_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp);
void shell_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp);
void quick_sort_optimized(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp);
void heap_sort_optimized(void *arr, int n, size_t elem_size, CompareFn cmp);

/**
 * @brief Funções auxiliares otimizadas e não otimizadas
 */
void heapify_optimized(void *arr, int n, int i, size_t elem_size, CompareFn cmp);
void heapify_naive(void *arr, int n, int i, size_t elem_size, CompareFn cmp);
int partition_optimized(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp);
int partition_naive(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp);

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
 * FUNÇÕES AUXILIARES DE SALVAMENTO
 * ================================================================ */

/**
 * @brief Salva arquivo em múltiplos locais (cmake-build-debug/output e output/)
 *
 * Função auxiliar que tenta salvar o arquivo tanto no diretório de build
 * quanto no diretório output do projeto raiz.
 *
 * @param subdir Subdiretório (numeros, alunos, relatorios)
 * @param nome_arquivo Nome do arquivo a ser salvo
 * @param conteudo_callback Função callback para escrever o conteudo
 * @param dados Dados a serem escritos
 * @param tamanho Tamanho dos dados
 */
void salvar_arquivo_multiplos_locais(const char* subdir, const char* nome_arquivo,
                                   void (*conteudo_callback)(FILE*, void*, int),
                                   void* dados, int tamanho);

/**
 * @brief Função callback para escrever números inteiros
 */
void escrever_numeros_callback(FILE* arquivo, void* dados, int tamanho);

/**
 * @brief Função callback para escrever alunos
 */
void escrever_alunos_callback(FILE* arquivo, void* dados, int tamanho);

/**
 * @brief Função callback para escrever relatórios
 */
void escrever_relatorio_callback(FILE* arquivo, void* dados, int tamanho);

/**
 * @brief Função callback para escrever análise de estabilidade
 */
void escrever_estabilidade_callback(FILE* arquivo, void* dados, int tamanho);

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

/* ================================================================
 * FUNÇÕES DE MEDIÇÃO E ANÁLISE - VERSÃO 2.1 ALTA PRECISÃO
 * ================================================================ */

/**
 * @brief Obtém timestamp de alta precisão multiplataforma
 *
 * Utiliza a melhor função de timing disponível no sistema para
 * obter timestamps com máxima precisão possível.
 *
 * @return Tempo em segundos com precisão de nanossegundos
 */
double obter_timestamp_precisao();

/**
 * @brief Mede o tempo de execução de um algoritmo com alta precisão
 *
 * Nova implementação v2.1 que utiliza funções de timing de alta precisão
 * para medir algoritmos muito rápidos que anteriormente resultavam em zero.
 *
 * Características:
 * - Precisão até nanossegundos (dependente do sistema)
 * - Windows: QueryPerformanceCounter
 * - Linux/Unix: clock_gettime() com CLOCK_MONOTONIC
 * - Fallback: gettimeofday() para compatibilidade
 *
 * @param sort_fn Ponteiro para a função do algoritmo de ordenação
 * @param arr Ponteiro para o array a ser ordenado
 * @param n Número de elementos no array
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação
 * @return Tempo de execução em segundos (nunca zero)
 */
double medir_tempo_ordenacao(void (*sort_fn)(void*, int, size_t, CompareFn),
                            void *arr, int n, size_t elem_size, CompareFn cmp);

/**
 * @brief Mede o tempo de execução do Quick Sort com alta precisão
 *
 * Versão especializada da medição de alta precisão para o Quick Sort.
 *
 * @param quick_fn Ponteiro para a função Quick Sort
 * @param arr Ponteiro para o array a ser ordenado
 * @param n Número de elementos no array
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação
 * @return Tempo de execução em segundos (nunca zero)
 */
double medir_tempo_quick_sort(void (*quick_fn)(void*, int, int, size_t, CompareFn),
                            void *arr, int n, size_t elem_size, CompareFn cmp);

/**
 * @brief Executa medição múltipla para maior precisão estatística
 *
 * Para algoritmos muito rápidos, executa múltiplas medições e calcula
 * a média para obter resultados mais confiáveis.
 *
 * @param sort_fn Ponteiro para a função do algoritmo
 * @param dados_originais Dados originais (não serão modificados)
 * @param n Número de elementos
 * @param elem_size Tamanho de cada elemento
 * @param cmp Função de comparação
 * @param num_execucoes Número de execuções para média
 * @return Tempo médio de execução
 */
double medir_tempo_multiplo(void (*sort_fn)(void*, int, size_t, CompareFn),
                           void *dados_originais, int n, size_t elem_size,
                           CompareFn cmp, int num_execucoes);

/**
 * @brief Determina automaticamente o número de execuções baseado no tamanho
 *
 * Estratégia adaptativa:
 * - Conjuntos < 100 elementos: 10 execuções
 * - Conjuntos < 1.000 elementos: 5 execuções
 * - Conjuntos < 10.000 elementos: 3 execuções
 * - Conjuntos grandes: 1 execução
 *
 * @param tamanho_conjunto Número de elementos no conjunto
 * @return Número recomendado de execuções
 */
int determinar_num_execucoes(int tamanho_conjunto);

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

/**
 * @brief Alterna entre versão otimizada e não otimizada dos algoritmos
 */
void alternar_versao_algoritmos();

/**
 * @brief Compara versões otimizada e não otimizada dos algoritmos
 */
void comparar_versoes();

/**
 * @brief Obtém opção do usuário com validação
 */
int obter_opcao_usuario();

/**
 * @brief Pausa o programa esperando o usuário pressionar Enter
 */
void pausar();

/**
 * @brief Executa todos os testes disponíveis
 */
void executar_relatorio_completo();

/**
 * @brief Executa todos os algoritmos com salvamento dos arrays ordenados
 * @param dados Ponteiro para os dados a serem ordenados
 * @param tamanho Número de elementos
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação
 * @param tipo_dados Tipo de dados ("numeros" ou "alunos")
 * @param arquivo_base Nome base do arquivo
 * @param versao Identificação da versão ("otimizada" ou "nao_otimizada")
 */
void executar_todos_algoritmos_com_salvamento(void *dados, int tamanho, size_t elem_size, CompareFn cmp,
                                            const char* tipo_dados, const char* arquivo_base, const char* versao);

/**
 * @brief Gera relatório comparativo final das duas versões
 */
void gerar_relatorio_comparativo_final();

/**
 * @brief Gera relatório detalhado de performance
 * @param resultados Array com os resultados dos testes
 * @param num_resultados Número de resultados
 * @param nome_arquivo Nome do arquivo de saída
 */
void gerar_relatorio_detalhado(ResultadoTempo resultados[], int num_resultados, const char* nome_arquivo);

#endif // SORTS_H
