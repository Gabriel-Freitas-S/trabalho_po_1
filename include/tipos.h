/**
 * ================================================================
 * TIPOS E ESTRUTURAS DE DADOS - DEFINIÇÕES FUNDAMENTAIS
 * ================================================================
 *
 * @file tipos.h
 * @brief Definições de tipos, estruturas de dados e constantes do sistema
 * @version 2.1
 * @date 2025-08-24
 * @author Sistema de Análise de Algoritmos
 *
 * Este arquivo contém todas as definições de tipos, estruturas e constantes
 * usadas em todo o sistema. Separado do sorts.h para melhor organização.
 *
 * ================================================================
 */

#ifndef TIPOS_H
#define TIPOS_H

#include <stdio.h>
#include <stdlib.h>

/* ================================================================
 * DEFINIÇÕES DE TIPOS E PONTEIROS PARA FUNÇÕES
 * ================================================================ */

/**
 * TYPEDEF COMPAREFN - PONTEIRO PARA FUNÇÃO DE COMPARAÇÃO
 *
 * EXPLICAÇÃO DIDÁTICA:
 * Um "ponteiro para função" é como um "controle remoto genérico"
 * que pode controlar diferentes aparelhos (funções).
 *
 * Permite que os algoritmos trabalhem com qualquer tipo de dados,
 * desde que seja fornecida a função de comparação apropriada.
 */
typedef int (*CompareFn)(const void *a, const void *b);

/* ================================================================
 * ESTRUTURAS DE DADOS
 * ================================================================ */

/**
 * STRUCT ALUNO - ESTRUTURA PARA DADOS DE ESTUDANTE
 *
 * Estrutura para testar algoritmos com dados "reais" ao invés
 * de apenas números. Permite ordenar por diferentes critérios.
 */
typedef struct {
    char nome[100];           // Nome completo do aluno
    char data_nascimento[20]; // Data no formato "DD/MM/AAAA"
    char bairro[50];          // Bairro onde mora
    char cidade[50];          // Cidade onde mora
} Aluno;

/**
 * STRUCT RESULTADOTEMPO - MÉTRICAS DE PERFORMANCE
 *
 * Armazena todas as informações sobre o desempenho de um algoritmo
 * durante sua execução, incluindo tempo, comparações e trocas.
 */
typedef struct {
    char algoritmo[30];      // Nome do algoritmo testado
    double tempo_execucao;   // Tempo em segundos (precisão de nanossegundos)
    int tamanho_dados;       // Número de elementos ordenados
    char tipo_dados[20];     // Tipo de dados ("numeros" ou "alunos")
    long long comparacoes;   // Número de comparações realizadas
    long long trocas;        // Número de trocas realizadas
} ResultadoTempo;

/**
 * STRUCT ALGORITMOINFO - "CARTEIRA DE IDENTIDADE" DE UM ALGORITMO
 *
 * Contém todas as informações sobre um algoritmo, incluindo
 * complexidades e ponteiros para suas implementações.
 */
typedef struct {
    char nome[30];                    // Nome para exibição
    char complexidade_melhor[15];     // Melhor caso (ex: "O(n)")
    char complexidade_media[15];      // Caso médio (ex: "O(n²)")
    char complexidade_pior[15];       // Pior caso (ex: "O(n²)")
    int eh_estavel;                   // É estável? 1=Sim, 0=Não

    // Ponteiros para as implementações das funções
    void (*sort_fn)(void*, int, size_t, CompareFn);
    void (*quick_sort_fn)(void*, int, int, size_t, CompareFn);
    int eh_quick;                     // Flag: é Quick Sort? 1=Sim, 0=Não
} AlgoritmoInfo;

/* ================================================================
 * CONFIGURAÇÕES E CONSTANTES
 * ================================================================ */

/**
 * FLAG GLOBAL PARA CONTROLAR OTIMIZAÇÕES
 *
 * Controla se o programa usa versões otimizadas (1) ou didáticas (0)
 * dos algoritmos.
 */
extern int usar_versao_otimizada;

/**
 * CONTADORES GLOBAIS PARA MÉTRICAS
 *
 * Variáveis globais para contar operações durante a execução
 * dos algoritmos.
 */
extern long long contador_comparacoes;
extern long long contador_trocas;

/* ================================================================
 * FUNÇÕES DE CONFIGURAÇÃO
 * ================================================================ */

/**
 * @brief Configura se deve usar versões otimizadas ou não
 * @param otimizada 1 para usar versões otimizadas, 0 para versões didáticas
 */
void configurar_otimizacao(int otimizada);

#endif // TIPOS_H
