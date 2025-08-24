/**
 * ================================================================
 * ANÁLISE E MEDIÇÃO DE PERFORMANCE - PROTÓTIPOS E DEFINIÇÕES
 * ================================================================
 *
 * @file analise.h
 * @brief Sistema de medição, análise e geração de relatórios
 * @version 2.1
 * @date 2025-08-24
 * @author Sistema de Análise de Algoritmos
 *
 * Este arquivo contém protótipos para todas as funções relacionadas
 * à medição de performance, análise de dados e geração de relatórios.
 *
 * ================================================================
 */

#ifndef ANALISE_H
#define ANALISE_H

#include "tipos.h"

/* ================================================================
 * FUNÇÕES DE MEDIÇÃO DE TEMPO E PERFORMANCE
 * ================================================================ */

/**
 * @brief Obtém timestamp de alta precisão multiplataforma
 * @return Timestamp em segundos com precisão de nanossegundos
 */
double obter_tempo_preciso(void);

/**
 * @brief Mede tempo de execução de um algoritmo
 * @param algoritmo_info Informações do algoritmo
 * @param dados Ponteiro para os dados a serem ordenados
 * @param tamanho Número de elementos
 * @param elem_size Tamanho de cada elemento
 * @param cmp Função de comparação
 * @param tipo_dados Tipo dos dados ("numeros" ou "alunos")
 * @return Resultado com métricas de performance
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

/* ================================================================
 * FUNÇÕES DE PROCESSAMENTO EM LOTE (BATCH)
 * ================================================================ */

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

/* ================================================================
 * FUNÇÕES DE ANÁLISE DE ESTABILIDADE
 * ================================================================ */

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

/* ================================================================
 * FUNÇÕES DE GERAÇÃO DE RELATÓRIOS
 * ================================================================ */

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

/* ================================================================
 * FUNÇÕES AUXILIARES DE ANÁLISE
 * ================================================================ */

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

#endif // ANALISE_H
