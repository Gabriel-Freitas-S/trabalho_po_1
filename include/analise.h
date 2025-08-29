/**
 * ==============================================================
 * SISTEMA DE ANÁLISE DE ALGORITMOS - MEDIÇÃO E RELATÓRIOS
 * ==============================================================
 *
 * @file analise.h
 * @brief Sistema de medição de performance e geração de relatórios
 * @version 2.1
 * @date 2025-08-24
 *
 * Este arquivo contém as declarações de todas as funções responsáveis
 * pela medição precisa de tempo, coleta de métricas de performance e
 * geração de relatórios comparativos entre os algoritmos implementados.
 *
 * O sistema utiliza funções específicas para cada plataforma (Windows,
 * Linux/Unix) para garantir a maior precisão possível na medição de tempo.
 *
 * ==============================================================
 */

#ifndef ANALISE_H
#define ANALISE_H

#include "tipos.h"

/* ==============================================================
 * FUNÇÕES DE MEDIÇÃO DE TEMPO E PERFORMANCE
 * ============================================================== */

/**
 * @brief Obtém timestamp de alta precisão compatível com múltiplas plataformas
 *
 * Implementa métodos específicos para cada sistema operacional:
 * - Windows: Usa QueryPerformanceCounter (precisão de microssegundos)
 * - Linux/Unix: Usa clock_gettime com CLOCK_MONOTONIC (precisão de nanossegundos)
 * - Fallback: Usa gettimeofday (precisão de microssegundos)
 *
 * @return Timestamp em segundos com precisão de nanossegundos
 */
double obter_tempo_preciso(void);

/**
 * @brief Mede o tempo e outras métricas de execução de um algoritmo
 *
 * Realiza a medição completa do desempenho de um algoritmo de ordenação,
 * incluindo tempo de execução, número de comparações e número de trocas.
 *
 * @param algoritmo_info Informações sobre o algoritmo a ser testado
 * @param dados Ponteiro para os dados a serem ordenados
 * @param tamanho Número de elementos no array
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação entre elementos
 * @param tipo_dados Identificador do tipo de dados ("numeros" ou "alunos")
 * @return Estrutura ResultadoTempo com todas as métricas coletadas
 */
ResultadoTempo medir_algoritmo(AlgoritmoInfo *algoritmo_info, void *dados,
                              int tamanho, size_t elem_size, CompareFn cmp,
                              const char *tipo_dados);

/**
 * @brief Executa análise completa de um algoritmo em múltiplos datasets
 * @param algoritmo_info Informações do algoritmo
 * @param nome_arquivo Base do nome do arquivo de dados
 * @param cmp Função de comparação
 * @param eh_aluno Se os dados são de alunos (1) ou números (0)
 */
void executar_analise_completa(AlgoritmoInfo *algoritmo_info,
                              const char *nome_arquivo, CompareFn cmp,
                              int eh_aluno);

/* ==============================================================
 * FUNÇÕES DE PROCESSAMENTO EM LOTE (BATCH)
 * ============================================================== */

/**
 * @brief Executa todos os algoritmos para dados numéricos
 */
void executar_todos_algoritmos_numeros(void);

/**
 * @brief Executa todos os algoritmos para dados de alunos
 */
void executar_todos_algoritmos_alunos(void);

/**
 * @brief Executa análise completa de todos os algoritmos
 */
void executar_analise_completa_todos(void);

/* ==============================================================
 * FUNÇÕES DE ANÁLISE DE ESTABILIDADE
 * ============================================================== */

/**
 * @brief Analisa estabilidade de todos os algoritmos
 *
 * Testa se algoritmos classificados como estáveis realmente
 * mantêm a ordem relativa de elementos iguais.
 */
void analisar_estabilidade_algoritmos(void);

/**
 * @brief Verifica se um algoritmo é estável usando dados de teste
 * @param algoritmo_info Informações do algoritmo
 * @param dados_originais Dados antes da ordenação
 * @param dados_ordenados Dados após a ordenação
 * @param tamanho Número de elementos
 * @return 1 se estável, 0 se não estável
 */
int verificar_estabilidade(AlgoritmoInfo *algoritmo_info, Aluno *dados_originais,
                          Aluno *dados_ordenados, int tamanho);

/* ==============================================================
 * FUNÇÕES DE GERAÇÃO DE RELATÓRIOS
 * ============================================================== */

/**
 * @brief Gera relatório comparativo de performance
 * @param resultados Array com resultados dos algoritmos
 * @param num_resultados Número de resultados no array
 * @param nome_arquivo Nome do arquivo de relatório
 * @param titulo Título do relatório
 */
void gerar_relatorio_comparativo(ResultadoTempo *resultados, int num_resultados,
                                const char *nome_arquivo, const char *titulo);

/**
 * @brief Gera ranking de algoritmos por tempo de execução
 * @param resultados Array com resultados dos algoritmos
 * @param num_resultados Número de resultados no array
 * @param nome_arquivo Nome do arquivo de ranking
 */
void gerar_ranking_por_tempo(ResultadoTempo *resultados, int num_resultados,
                            const char *nome_arquivo);

/**
 * @brief Gera relatório de métricas detalhadas
 * @param resultados Array com resultados dos algoritmos
 * @param num_resultados Número de resultados no array
 * @param nome_arquivo Nome do arquivo de relatório
 */
void gerar_relatorio_metricas(ResultadoTempo *resultados, int num_resultados,
                             const char *nome_arquivo);

/**
 * @brief Salva resultado individual em arquivo específico
 * @param resultado Resultado a ser salvo
 */
void salvar_resultado_individual(ResultadoTempo *resultado);

/* ==============================================================
 * FUNÇÕES AUXILIARES DE ANÁLISE
 * ============================================================== */

/**
 * @brief Calcula estatísticas básicas de um conjunto de resultados
 * @param resultados Array com resultados
 * @param num_resultados Número de resultados
 * @param tempo_medio Ponteiro para armazenar tempo médio
 * @param tempo_min Ponteiro para armazenar tempo mínimo
 * @param tempo_max Ponteiro para armazenar tempo máximo
 */
void calcular_estatisticas(ResultadoTempo *resultados, int num_resultados,
                          double *tempo_medio, double *tempo_min, double *tempo_max);

/**
 * @brief Compara dois resultados por tempo (para ordenação)
 * @param a Primeiro resultado
 * @param b Segundo resultado
 * @return Valor negativo se a < b, positivo se a > b, zero se iguais
 */
int comparar_resultados_por_tempo(const void *a, const void *b);

/**
 * @brief Formata tempo em string legível
 * @param tempo Tempo em segundos
 * @param buffer Buffer para armazenar resultado formatado
 * @param tamanho_buffer Tamanho do buffer
 */
void formatar_tempo(double tempo, char *buffer, size_t tamanho_buffer);

/**
 * @brief Formata número grande com separadores
 * @param numero Número a ser formatado
 * @param buffer Buffer para armazenar resultado
 * @param tamanho_buffer Tamanho do buffer
 */
void formatar_numero_grande(long long numero, char *buffer, size_t tamanho_buffer);

/* ==============================================================
 * FUNÇÕES DE EXECUÇÃO E ANÁLISE
 * ============================================================== */

/**
 * @brief Executa todos os algoritmos e gera análises com contagem de comparações e trocas
 * @param dados Ponteiro para os dados a serem ordenados (não modificados)
 * @param tamanho Número de elementos
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação entre elementos
 * @param tipo_dados Tipo dos dados ("numeros" ou "alunos")
 * @param arquivo_base Nome base para arquivos de saída
 */
void executar_todos_algoritmos(const void *dados, int tamanho, size_t elem_size, CompareFn cmp,
                              const char* tipo_dados, const char* arquivo_base);

/**
 * @brief Executa todos os algoritmos com salvamento dos arrays ordenados
 * @param dados Ponteiro para os dados a serem ordenados (não modificados)
 * @param tamanho Número de elementos
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação entre elementos
 * @param tipo_dados Tipo dos dados ("numeros" ou "alunos")
 * @param arquivo_base Nome base para arquivos de saída
 * @param versao Identificador da versão ("otimizada" ou "nao_otimizada")
 */
void executar_todos_algoritmos_com_salvamento(const void *dados, int tamanho, size_t elem_size, CompareFn cmp,
                                            const char* tipo_dados, const char* arquivo_base, const char* versao);

/**
 * @brief Executa medição múltipla para maior precisão estatística
 * @param sort_fn Ponteiro para a função do algoritmo
 * @param dados_originais Dados originais (não serão modificados)
 * @param n Número de elementos
 * @param elem_size Tamanho de cada elemento
 * @param cmp Função de comparação
 * @param num_execucoes Número de execuções para média
 * @return Tempo médio de execução
 */
double medir_tempo_multiplo(void (*sort_fn)(void*, int, size_t, CompareFn),
                           const void *dados_originais, int n, size_t elem_size,
                           CompareFn cmp, int num_execucoes);

#endif // ANALISE_H
