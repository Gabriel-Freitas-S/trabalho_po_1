/**
 * ==============================================================
 * TIPOS E ESTRUTURAS DE DADOS - DEFINIÇÕES FUNDAMENTAIS
 * ==============================================================
 *
 * @file tipos.h
 * @brief Definições de tipos, estruturas de dados e constantes centrais do sistema
 * @author Sistema de Análise de Performance de Algoritmos de Ordenação
 *
 * Este módulo fundamental contém todas as definições de tipos personalizados,
 * estruturas de dados e constantes utilizadas em todo o sistema de análise
 * de algoritmos de ordenação. A modularização dessas definições em um arquivo
 * dedicado segue o princípio de separação de responsabilidades, facilitando:
 *
 * - Manutenção centralizada de tipos e estruturas
 * - Reutilização consistente em todos os módulos
 * - Evolução controlada das definições de dados
 * - Documentação clara das interfaces de dados
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
 * @brief Tipo de função para comparação genérica entre elementos de qualquer tipo
 *
 * Define um ponteiro para função que implementa o protocolo padrão de comparação
 * utilizado por algoritmos de ordenação genéricos. Este tipo permite que os
 * algoritmos trabalhem com dados de qualquer natureza (inteiros, strings,
 * estruturas complexas) desde que seja fornecida uma função de comparação adequada.
 *
 * **Protocolo de retorno (compatível com qsort da biblioteca padrão):**
 * - **Valor negativo**: primeiro elemento é MENOR que o segundo (a < b)
 * - **Zero**: elementos são IGUAIS (a == b)
 * - **Valor positivo**: primeiro elemento é MAIOR que o segundo (a > b)
 *
 * **Vantagens do polimorfismo via ponteiros de função:**
 * - Reutilização de código: um algoritmo funciona com múltiplos tipos
 * - Flexibilidade: diferentes critérios de ordenação para o mesmo tipo
 * - Performance: evita overhead de verificações de tipo em runtime
 * - Compatibilidade: segue padrão estabelecido pela biblioteca C
 *
 * **Exemplo de implementação:**
 * ```c
 * int comparar_inteiros(const void *a, const void *b) {
 *     int *x = (int*)a;
 *     int *y = (int*)b;
 *     return (*x > *y) - (*x < *y);  // Comparação eficiente sem overflow
 * }
 * ```
 *
 * @param a Ponteiro para o primeiro elemento a ser comparado
 * @param b Ponteiro para o segundo elemento a ser comparado
 * @return Inteiro indicando a relação de ordem entre os elementos
 * @see comparar_inteiros() Implementação para números inteiros
 * @see comparar_alunos_por_nome() Implementação para estruturas complexas
 */
typedef int (*CompareFn)(const void *a, const void *b);

/* ==============================================================
 * ESTRUTURAS DE DADOS
 * ============================================================== */

/**
 * @brief Estrutura de dados para registro completo de estudante
 *
 * Representa um registro acadêmico contendo informações pessoais e geográficas
 * de um estudante. Esta estrutura serve como exemplo prático de dados complexos
 * para validação dos algoritmos de ordenação com tipos não-primitivos.
 *
 * **Casos de uso na análise de algoritmos:**
 * - Teste de estabilidade: verificar se algoritmos preservam ordem relativa
 * - Ordenação multi-critério: nome, idade, localização geográfica
 * - Performance com dados reais: simulação de cenários do mundo real
 * - Validação de robustez: dados com tamanhos variáveis de campos
 *
 * **Critérios de ordenação suportados:**
 * - Alfabético por nome (ordem lexicográfica)
 * - Cronológico por data de nascimento (mais novo/mais velho)
 * - Geográfico por bairro ou cidade (agrupamento territorial)
 *
 * **Limitações de design:**
 * - Tamanhos fixos para strings (evita complexidade de alocação dinâmica)
 * - Formato específico de data (DD/MM/AAAA) para parsing simplificado
 * - Encoding ASCII para nomes (compatibilidade multiplataforma)
 *
 * @see comparar_alunos_por_nome() Função para ordenação alfabética
 * @see comparar_alunos_por_data() Função para ordenação cronológica
 * @see comparar_alunos_por_bairro() Função para agrupamento por bairro
 */
typedef struct {
    char nome[100];           ///< Nome completo do estudante (máx. 99 caracteres + '\0')
    char data_nascimento[20]; ///< Data no formato "DD/MM/AAAA" (ex: "15/03/2000")
    char bairro[50];          ///< Bairro de residência (máx. 49 caracteres + '\0')
    char cidade[50];          ///< Cidade de residência (máx. 49 caracteres + '\0')
} Aluno;

/**
 * @brief Estrutura de métricas abrangentes para análise de performance de algoritmos
 *
 * Concentra todas as informações quantitativas sobre o desempenho de um algoritmo
 * de ordenação durante sua execução. Esta estrutura permite análise científica
 * rigorosa e comparações objetivas entre diferentes implementações e estratégias.
 *
 * **Métricas de tempo:**
 * - Medição de alta precisão usando contadores de performance do sistema
 * - Resolução típica: nanossegundos em sistemas modernos
 * - Compatível com análises estatísticas e benchmark científico
 *
 * **Métricas operacionais:**
 * - Comparações: fundamentais para análise de complexidade algorítmica
 * - Trocas: indicador de movimentação de dados e cache performance
 * - Movimentações: métrica abrangente incluindo trocas e deslocamentos
 *
 * **Aplicações analíticas:**
 * - Validação experimental de complexidades teóricas O(n), O(n log n), O(n²)
 * - Identificação de gargalos de performance em implementações
 * - Análise comparativa entre versões otimizadas e didáticas
 * - Geração de relatórios científicos e gráficos de performance
 *
 * @note Contadores são globais e resetados antes de cada execução
 * @see obter_tempo_preciso() Função para medição de timestamps
 * @see medir_algoritmo() Função que popula esta estrutura
 */
typedef struct {
    char algoritmo[30];      ///< Identificação do algoritmo testado (ex: "Quick Sort")
    double tempo_execucao;   ///< Tempo total em segundos (precisão de nanossegundos)
    int tamanho_dados;       ///< Quantidade de elementos processados
    char tipo_dados[20];     ///< Classificação dos dados ("numeros" ou "alunos")
    long long comparacoes;   ///< Contador de operações de comparação realizadas
    long long trocas;        ///< Contador de operações de troca/swap executadas
    long long movimentacoes; ///< Contador total de movimentações de elementos
} ResultadoTempo;

/**
 * @brief Registro descritivo completo de um algoritmo de ordenação
 *
 * Esta estrutura funciona como uma "carteira de identidade" técnica para cada
 * algoritmo implementado, centralizando tanto informações teóricas quanto
 * ponteiros para as implementações concretas. Permite análise comparativa
 * systematizada e seleção algorítmica baseada em critérios objetivos.
 *
 * **Informações de complexidade computacional:**
 * - Melhor caso: cenário mais favorável (ex: dados já ordenados)
 * - Caso médio: performance típica esperada (ex: dados aleatórios)
 * - Pior caso: cenário menos favorável (ex: dados em ordem inversa)
 *
 * **Propriedades algorítmicas importantes:**
 * - Estabilidade: preservação da ordem relativa de elementos iguais
 * - Adaptabilidade: melhor performance com dados parcialmente ordenados
 * - Localidade: padrão de acesso à memória (importante para cache)
 *
 * **Design pattern Strategy implementado:**
 * Os ponteiros de função permitem trocar algoritmos em runtime sem
 * modificar o código cliente, seguindo o princípio aberto/fechado.
 *
 * **Tratamento especial para Quick Sort:**
 * Quick Sort usa assinatura diferente (início/fim em vez de tamanho)
 * devido à natureza recursiva e necessidade de particionamento.
 *
 * @note Ponteiros de função devem ser inicializados para versões adequadas
 * @see configurar_otimizacao() Para alternar entre versões otimizadas/didáticas
 */
typedef struct {
    char nome[30];                    ///< Nome descritivo para exibição (ex: "Bubble Sort")
    char complexidade_melhor[15];     ///< Notação Big-O melhor caso (ex: "O(n)")
    char complexidade_media[15];      ///< Notação Big-O caso médio (ex: "O(n log n)")
    char complexidade_pior[15];       ///< Notação Big-O pior caso (ex: "O(n²)")
    int eh_estavel;                   ///< Flag de estabilidade: 1=estável, 0=não-estável

    /// Ponteiro para implementação padrão (assinatura genérica)
    void (*sort_fn)(void*, int, size_t, CompareFn);
    /// Ponteiro específico para Quick Sort (assinatura com início/fim)
    void (*quick_sort_fn)(void*, int, int, size_t, CompareFn);
    int eh_quick;                     ///< Identificador Quick Sort: 1=sim, 0=não
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
