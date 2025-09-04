/**
 * ==============================================================
 * TIPOS E ESTRUTURAS DE DADOS - DEFINIÇÕES FUNDAMENTAIS
 * ==============================================================
 *
 * @file tipos.h
 * @brief Definições de tipos, estruturas de dados e constantes do sistema
 * @version 2.1
 * @date 2025-08-24
 *
 * Este arquivo contém as definições de tipos e estruturas usadas em
 * todo o sistema de análise de algoritmos. A separação dessas definições
 * em um arquivo próprio facilita a manutenção e permite que outras partes
 * do sistema utilizem estruturas padronizadas.
 *
 * ==============================================================
 */

#ifndef TIPOS_H
#define TIPOS_H

#include <stdio.h>
#include <stdlib.h>

/* ==============================================================
 * DEFINIÇÕES DE TIPOS E PONTEIROS PARA FUNÇÕES
 * ============================================================== */

/**
 * @brief Ponteiro para função de comparação entre dois elementos
 *
 * Define um tipo para funções de comparação que recebem dois ponteiros void*
 * e retornam um valor inteiro que indica a relação entre eles:
 * - Valor negativo: primeiro elemento é menor que o segundo
 * - Zero: elementos são iguais
 * - Valor positivo: primeiro elemento é maior que o segundo
 *
 * Esta abordagem permite que os algoritmos de ordenação funcionem com
 * qualquer tipo de dado, desde que seja fornecida uma função de comparação
 * apropriada para esse tipo.
 *
 * @param a Ponteiro para o primeiro elemento
 * @param b Ponteiro para o segundo elemento
 * @return Inteiro que representa a relação entre os elementos
 */
typedef int (*CompareFn)(const void *a, const void *b);

/* ==============================================================
 * ESTRUTURAS DE DADOS
 * ============================================================== */

/**
 * @brief Estrutura para armazenamento de dados de alunos
 *
 * Esta estrutura representa um registro de estudante com informações
 * pessoais e é usada para testar os algoritmos com dados complexos,
 * permitindo ordenação por diferentes critérios (nome, data, localidade).
 */
typedef struct {
    char nome[100];           // Nome completo do aluno
    char data_nascimento[20]; // Data no formato "DD/MM/AAAA"
    char bairro[50];          // Bairro onde mora
    char cidade[50];          // Cidade onde mora
} Aluno;

/**
 * @brief Estrutura para armazenamento de métricas de performance
 *
 * Armazena todas as informações sobre o desempenho de um algoritmo
 * durante sua execução, permitindo análise detalhada e comparativa
 * entre diferentes métodos de ordenação.
 */
typedef struct {
    char algoritmo[30];      // Nome do algoritmo testado
    double tempo_execucao;   // Tempo em segundos (precisão de nanossegundos)
    int tamanho_dados;       // Número de elementos ordenados
    char tipo_dados[20];     // Tipo de dados ("numeros" ou "alunos")
    long long comparacoes;   // Número de comparações realizadas
    long long trocas;        // Número de trocas realizadas
    long long movimentacoes; // Número de movimentações realizadas
} ResultadoTempo;

/**
 * @brief "Carteira de identidade" de um algoritmo de ordenação
 *
 * Esta estrutura contém todas as informações relevantes sobre um algoritmo,
 * incluindo suas complexidades de tempo e ponteiros para suas implementações
 * específicas. Facilita a comparação e seleção de algoritmos com base em
 * características desejadas para a ordenação de dados.
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

/* ==============================================================
 * CONFIGURAÇÕES E CONSTANTES
 * ============================================================== */

/**
 * @brief Número de algoritmos de ordenação disponíveis no sistema
 *
 * Esta constante define quantos algoritmos de ordenação estão implementados
 * e disponíveis para análise. É usada para dimensionar arrays da estrutura
 * AlgoritmoInfo e controlar loops de iteração pelos algoritmos.
 */
#define NUM_ALGORITMOS 7

/**
 * @brief Flag global para controlar otimizações
 *
 * Esta variável controla se o programa deve usar versões otimizadas (1) ou
 * didáticas (0) dos algoritmos de ordenação. Versões otimizadas são mais
 * eficientes, enquanto as didáticas são mais lentas, mas podem ser mais
 * fáceis de entender e depurar.
 */
extern int usar_versao_otimizada;

/**
 * @brief Contadores globais para métricas de desempenho
 *
 * Estas variáveis são usadas para contar o número de operações realizadas
 * durante a execução dos algoritmos, como comparações, trocas e movimentações. Os valores
 * são armazenados globalmente para permitir o acesso e análise posterior
 * após a execução dos algoritmos.
 */
extern long long contador_comparacoes;
extern long long contador_trocas;
extern long long contador_movimentacoes;

/* ==============================================================
 * FUNÇÕES DE CONFIGURAÇÃO
 * ============================================================== */

/**
 * @brief Configurações de otimização do sistema
 *
 * Esta função permite ao usuário escolher entre versões otimizadas ou
 * didáticas dos algoritmos de ordenação. A configuração é feita através
 * da passagem de um parâmetro inteiro que define o modo desejado.
 *
 * @param otimizada 1 para ativar versões otimizadas, 0 para versões didáticas
 */
void configurar_otimizacao(int otimizada);

#endif // TIPOS_H
