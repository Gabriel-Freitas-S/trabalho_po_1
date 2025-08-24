/**
 * ================================================================
 * ENTRADA E SAÍDA DE DADOS - PROTÓTIPOS E DEFINIÇÕES
 * ================================================================
 *
 * @file io.h
 * @brief Funções para leitura, escrita e manipulação de arquivos de dados
 * @version 2.1
 * @date 2025-08-24
 * @author Sistema de Análise de Algoritmos
 *
 * Este arquivo contém protótipos para todas as funções relacionadas
 * à entrada e saída de dados, incluindo leitura de arquivos,
 * escrita de resultados e manipulação de datasets.
 *
 * ================================================================
 */

#ifndef IO_H
#define IO_H

#include "tipos.h"

/* ================================================================
 * FUNÇÕES DE LEITURA DE DADOS
 * ================================================================ */

/**
 * @brief Carrega dados numéricos de um arquivo
 * @param nome_arquivo Nome do arquivo a ser lido
 * @param tamanho Ponteiro para armazenar o número de elementos lidos
 * @return Ponteiro para array de inteiros ou NULL em caso de erro
 */
int* carregar_dados_numericos(const char *nome_arquivo, int *tamanho);

/**
 * @brief Carrega dados de alunos de um arquivo
 * @param nome_arquivo Nome do arquivo a ser lido
 * @param tamanho Ponteiro para armazenar o número de elementos lidos
 * @return Ponteiro para array de estruturas Aluno ou NULL em caso de erro
 */
Aluno* carregar_dados_alunos(const char *nome_arquivo, int *tamanho);

/**
 * @brief Verifica se um arquivo existe e pode ser lido
 * @param nome_arquivo Nome do arquivo a verificar
 * @return 1 se arquivo existe e é legível, 0 caso contrário
 */
int arquivo_existe(const char *nome_arquivo);

/**
 * @brief Lista todos os arquivos de dados disponíveis
 */
void listar_arquivos_disponiveis(void);

/* ================================================================
 * FUNÇÕES DE ESCRITA DE DADOS
 * ================================================================ */

/**
 * @brief Salva dados numéricos ordenados em arquivo
 * @param dados Array de inteiros a ser salvo
 * @param tamanho Número de elementos no array
 * @param nome_arquivo Nome do arquivo de destino
 * @param algoritmo Nome do algoritmo usado para ordenação
 * @return 1 se sucesso, 0 se erro
 */
int salvar_dados_numericos(int *dados, int tamanho, const char *nome_arquivo,
                          const char *algoritmo);

/**
 * @brief Salva dados de alunos ordenados em arquivo
 * @param dados Array de estruturas Aluno a ser salvo
 * @param tamanho Número de elementos no array
 * @param nome_arquivo Nome do arquivo de destino
 * @param algoritmo Nome do algoritmo usado para ordenação
 * @return 1 se sucesso, 0 se erro
 */
int salvar_dados_alunos(Aluno *dados, int tamanho, const char *nome_arquivo,
                       const char *algoritmo);

/**
 * @brief Salva resultado de análise em arquivo específico
 * @param resultado Estrutura com dados de performance
 * @param diretorio Diretório onde salvar o arquivo
 * @return 1 se sucesso, 0 se erro
 */
int salvar_resultado_analise(ResultadoTempo *resultado, const char *diretorio);

/* ================================================================
 * FUNÇÕES DE MANIPULAÇÃO DE CAMINHOS E DIRETÓRIOS
 * ================================================================ */

/**
 * @brief Cria diretório se não existir
 * @param caminho Caminho do diretório a ser criado
 * @return 1 se sucesso, 0 se erro
 */
int criar_diretorio(const char *caminho);

/**
 * @brief Constrói caminho completo para arquivo de dados
 * @param nome_base Nome base do arquivo
 * @param buffer Buffer para armazenar o caminho completo
 * @param tamanho_buffer Tamanho do buffer
 */
void construir_caminho_dados(const char *nome_base, char *buffer, size_t tamanho_buffer);

/**
 * @brief Constrói caminho completo para arquivo de saída
 * @param tipo_dados Tipo de dados ("numeros" ou "alunos")
 * @param algoritmo Nome do algoritmo
 * @param dataset Nome do dataset
 * @param otimizada Se é versão otimizada (1) ou não (0)
 * @param buffer Buffer para armazenar o caminho
 * @param tamanho_buffer Tamanho do buffer
 */
void construir_caminho_saida(const char *tipo_dados, const char *algoritmo,
                            const char *dataset, int otimizada,
                            char *buffer, size_t tamanho_buffer);

/* ================================================================
 * FUNÇÕES DE VALIDAÇÃO DE DADOS
 * ================================================================ */

/**
 * @brief Valida integridade de dados numéricos
 * @param dados Array de inteiros a validar
 * @param tamanho Número de elementos
 * @return 1 se dados são válidos, 0 caso contrário
 */
int validar_dados_numericos(int *dados, int tamanho);

/**
 * @brief Valida integridade de dados de alunos
 * @param dados Array de estruturas Aluno a validar
 * @param tamanho Número de elementos
 * @return 1 se dados são válidos, 0 caso contrário
 */
int validar_dados_alunos(Aluno *dados, int tamanho);

/**
 * @brief Verifica se dados estão ordenados corretamente
 * @param dados Ponteiro para os dados
 * @param tamanho Número de elementos
 * @param elem_size Tamanho de cada elemento
 * @param cmp Função de comparação
 * @return 1 se ordenados corretamente, 0 caso contrário
 */
int verificar_ordenacao(void *dados, int tamanho, size_t elem_size, CompareFn cmp);

/* ================================================================
 * FUNÇÕES DE SALVAMENTO ESPECÍFICAS
 * ================================================================ */

/**
 * @brief Salva array de números em arquivo
 * @param caminho_arquivo Caminho completo do arquivo
 * @param arr Array de inteiros
 * @param tamanho Número de elementos
 */
void salvar_numeros(const char* caminho_arquivo, int arr[], int tamanho);

/**
 * @brief Salva array de alunos em arquivo
 * @param caminho_arquivo Caminho completo do arquivo
 * @param arr Array de alunos
 * @param tamanho Número de elementos
 */
void salvar_alunos(const char* caminho_arquivo, Aluno arr[], int tamanho);

#endif // IO_H
