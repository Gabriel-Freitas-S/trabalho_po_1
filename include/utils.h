/**
 * ================================================================
 * FUNÇÕES UTILITÁRIAS E DE COMPARAÇÃO - PROTÓTIPOS E DEFINIÇÕES
 * ================================================================
 *
 * @file utils.h
 * @brief Funções auxiliares, comparadores e utilitários do sistema
 * @version 2.1
 * @date 2025-08-24
 * @author Sistema de Análise de Algoritmos
 *
 * Este arquivo contém protótipos para funções utilitárias, funções
 * de comparação para diferentes tipos de dados e outras ferramentas
 * auxiliares usadas em todo o sistema.
 *
 * ================================================================
 */

#ifndef UTILS_H
#define UTILS_H

#include "tipos.h"

/* ================================================================
 * FUNÇÕES DE COMPARAÇÃO PARA DIFERENTES TIPOS DE DADOS
 * ================================================================ */

/**
 * @brief Compara dois inteiros em ordem crescente
 * @param a Ponteiro para primeiro inteiro
 * @param b Ponteiro para segundo inteiro
 * @return Negativo se a < b, positivo se a > b, zero se iguais
 */
int comparar_inteiros(const void *a, const void *b);

/**
 * @brief Compara dois inteiros em ordem decrescente
 * @param a Ponteiro para primeiro inteiro
 * @param b Ponteiro para segundo inteiro
 * @return Positivo se a < b, negativo se a > b, zero se iguais
 */
int comparar_inteiros_decrescente(const void *a, const void *b);

/**
 * @brief Compara dois alunos por nome (ordem alfabética)
 * @param a Ponteiro para primeiro aluno
 * @param b Ponteiro para segundo aluno
 * @return Resultado da comparação lexicográfica dos nomes
 */
int comparar_alunos_por_nome(const void *a, const void *b);

/**
 * @brief Compara dois alunos por data de nascimento
 * @param a Ponteiro para primeiro aluno
 * @param b Ponteiro para segundo aluno
 * @return Negativo se a mais novo, positivo se a mais velho, zero se iguais
 */
int comparar_alunos_por_data(const void *a, const void *b);

/**
 * @brief Compara dois alunos por bairro (ordem alfabética)
 * @param a Ponteiro para primeiro aluno
 * @param b Ponteiro para segundo aluno
 * @return Resultado da comparação lexicográfica dos bairros
 */
int comparar_alunos_por_bairro(const void *a, const void *b);

/**
 * @brief Compara dois alunos por cidade (ordem alfabética)
 * @param a Ponteiro para primeiro aluno
 * @param b Ponteiro para segundo aluno
 * @return Resultado da comparação lexicográfica das cidades
 */
int comparar_alunos_por_cidade(const void *a, const void *b);

/* ================================================================
 * FUNÇÕES DE MANIPULAÇÃO DE DADOS GENÉRICOS
 * ================================================================ */

/**
 * @brief Copia um elemento de uma posição para outra
 * @param destino Ponteiro para posição de destino
 * @param origem Ponteiro para posição de origem
 * @param elem_size Tamanho do elemento em bytes
 */
void copiar_elemento(void *destino, const void *origem, size_t elem_size);

/**
 * @brief Copia um array completo para outro local de memória
 * @param origem Ponteiro para array de origem
 * @param destino Ponteiro para array de destino
 * @param tamanho Número de elementos a copiar
 * @param elem_size Tamanho de cada elemento em bytes
 */
void copiar_array(const void *origem, void *destino, int tamanho, size_t elem_size);

/* ================================================================
 * FUNÇÕES DE INTERFACE DE USUÁRIO E CONTROLE
 * ================================================================ */

/**
 * @brief Limpa a tela do terminal de forma multiplataforma
 */
void limpar_terminal(void);

/**
 * @brief Pausa execução aguardando interação do usuário
 */
void pausar(void);

/**
 * @brief Obtém opção do usuário com validação robusta
 * @return Número válido escolhido pelo usuário, ou -1 se entrada inválida
 */
int obter_opcao_usuario(void);

/* ================================================================
 * FUNÇÕES DE INFORMAÇÃO E DOCUMENTAÇÃO
 * ================================================================ */

/**
 * @brief Exibe cabeçalho informativo do programa
 */
void imprimir_cabecalho(void);

/**
 * @brief Exibe menu principal do sistema
 */
void imprimir_menu(void);

/**
 * @brief Exibe informações sobre todos os algoritmos implementados
 *
 * Mostra uma tabela com características de cada algoritmo:
 * nome, complexidades, estabilidade, etc.
 */
void exibir_info_algoritmos(void);

/* ================================================================
 * FUNÇÕES DE SISTEMA DE ARQUIVOS E SALVAMENTO
 * ================================================================ */

/**
 * @brief Cria estrutura completa de diretórios para organização de resultados
 */
void criar_diretorios_output(void);

/**
 * @brief Callback para escrita de arrays de números inteiros
 */
void escrever_numeros_callback(FILE* arquivo, void* dados, int tamanho);

/**
 * @brief Callback para escrita de estruturas de alunos
 */
void escrever_alunos_callback(FILE* arquivo, void* dados, int tamanho);

/**
 * @brief Sistema unificado de salvamento em múltiplos locais
 */
void salvar_arquivo_multiplos_locais(const char* subdir, const char* nome_arquivo,
                                   void (*conteudo_callback)(FILE*, void*, int),
                                   void* dados, int tamanho);

/* ================================================================
 * FUNÇÕES DE EXECUÇÃO E ORQUESTRAÇÃO
 * ================================================================ */

/**
 * @brief Executa bateria completa de testes com ambas versões dos algoritmos
 */
void executar_relatorio_completo(void);

/* ================================================================
 * FUNÇÃO DE COMPARAÇÃO PRINCIPAL PARA ALUNOS
 * ================================================================ */

/**
 * @brief Compara dois alunos usando critério padrão (nome)
 * @param a Ponteiro para primeiro aluno
 * @param b Ponteiro para segundo aluno
 * @return Resultado da comparação lexicográfica dos nomes
 */
int comparar_alunos(const void *a, const void *b);

#endif // UTILS_H
