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
 * @brief Troca dois elementos de posição em um array genérico
 * @param arr Ponteiro para o array
 * @param i Índice do primeiro elemento
 * @param j Índice do segundo elemento
 * @param elem_size Tamanho de cada elemento em bytes
 */
void trocar_elementos(void *arr, int i, int j, size_t elem_size);

/**
 * @brief Copia um elemento de uma posição para outra
 * @param destino Ponteiro para posição de destino
 * @param origem Ponteiro para posição de origem
 * @param elem_size Tamanho do elemento em bytes
 */
void copiar_elemento(void *destino, const void *origem, size_t elem_size);

/**
 * @brief Obtém ponteiro para elemento em posição específica
 * @param arr Ponteiro para o array
 * @param indice Índice do elemento desejado
 * @param elem_size Tamanho de cada elemento
 * @return Ponteiro para o elemento na posição especificada
 */
void* obter_elemento(void *arr, int indice, size_t elem_size);

/**
 * @brief Copia um array completo para outro local de memória
 * @param origem Ponteiro para array de origem
 * @param destino Ponteiro para array de destino
 * @param tamanho Número de elementos a copiar
 * @param elem_size Tamanho de cada elemento em bytes
 */
void copiar_array(const void *origem, void *destino, int tamanho, size_t elem_size);

/* ================================================================
 * FUNÇÕES DE INFORMAÇÃO E DOCUMENTAÇÃO
 * ================================================================ */

/**
 * @brief Exibe informações sobre todos os algoritmos implementados
 *
 * Mostra uma tabela com características de cada algoritmo:
 * nome, complexidades, estabilidade, etc.
 */
void exibir_info_algoritmos(void);

/**
 * @brief Exibe menu principal do sistema
 */
void exibir_menu_principal(void);

/**
 * @brief Exibe menu de seleção de algoritmos
 */
void exibir_menu_algoritmos(void);

/**
 * @brief Exibe menu de seleção de datasets
 */
void exibir_menu_datasets(void);

/**
 * @brief Exibe informações sobre um algoritmo específico
 * @param algoritmo_info Ponteiro para estrutura com informações do algoritmo
 */
void exibir_info_algoritmo(const AlgoritmoInfo *algoritmo_info);

/* ================================================================
 * FUNÇÕES DE INICIALIZAÇÃO E CONFIGURAÇÃO
 * ================================================================ */

/**
 * @brief Inicializa array de informações dos algoritmos
 * @return Ponteiro para array de AlgoritmoInfo inicializado
 */
AlgoritmoInfo* inicializar_algoritmos(void);

/**
 * @brief Obtém número total de algoritmos implementados
 * @return Número de algoritmos disponíveis
 */
int obter_numero_algoritmos(void);

/**
 * @brief Inicializa contadores de métricas
 */
void inicializar_contadores(void);

/**
 * @brief Reseta contadores de métricas para zero
 */
void resetar_contadores(void);

/* ================================================================
 * FUNÇÕES DE VALIDAÇÃO E VERIFICAÇÃO
 * ================================================================ */

/**
 * @brief Verifica se uma string é válida (não nula e não vazia)
 * @param str String a ser verificada
 * @return 1 se válida, 0 caso contrário
 */
int string_valida(const char *str);

/**
 * @brief Verifica se um ponteiro é válido (não nulo)
 * @param ptr Ponteiro a ser verificado
 * @return 1 se válido, 0 caso contrário
 */
int ponteiro_valido(const void *ptr);

/**
 * @brief Verifica se um tamanho de array é válido
 * @param tamanho Tamanho a ser verificado
 * @return 1 se válido (> 0), 0 caso contrário
 */
int tamanho_valido(int tamanho);

/* ================================================================
 * FUNÇÕES DE FORMATAÇÃO E CONVERSÃO
 * ================================================================ */

/**
 * @brief Remove espaços em branco do início e fim de uma string
 * @param str String a ser processada (modificada in-place)
 */
void remover_espacos(char *str);

/**
 * @brief Converte string para minúsculas
 * @param str String a ser convertida (modificada in-place)
 */
void para_minusculas(char *str);

/**
 * @brief Converte data do formato DD/MM/AAAA para timestamp comparável
 * @param data_str String com data no formato DD/MM/AAAA
 * @return Timestamp para comparação ou -1 se data inválida
 */
long long converter_data_para_timestamp(const char *data_str);

/**
 * @brief Valida formato de data DD/MM/AAAA
 * @param data_str String com data a ser validada
 * @return 1 se formato válido, 0 caso contrário
 */
int validar_formato_data(const char *data_str);

/* ================================================================
 * FUNÇÕES DE DEBUG E LOGGING
 * ================================================================ */

/**
 * @brief Ativa ou desativa modo debug
 * @param ativar 1 para ativar, 0 para desativar
 */
void configurar_modo_debug(int ativar);

/**
 * @brief Imprime mensagem de debug se modo debug estiver ativo
 * @param formato String de formato (como printf)
 * @param ... Argumentos adicionais
 */
void debug_print(const char *formato, ...);

/**
 * @brief Exibe estado atual dos contadores de métricas
 */
void exibir_contadores_debug(void);

/* ================================================================
 * FUNÇÕES DE PERFORMANCE E OTIMIZAÇÃO
 * ================================================================ */

/**
 * @brief Aquece o cache executando operações simples
 *
 * Realiza operações básicas para preparar o sistema para
 * medições de performance mais precisas.
 */
void aquecer_cache(void);

/**
 * @brief Executa múltiplas iterações de uma função e retorna tempo médio
 * @param funcao Função a ser executada
 * @param dados Dados para a função
 * @param tamanho Tamanho dos dados
 * @param elem_size Tamanho de cada elemento
 * @param cmp Função de comparação
 * @param iteracoes Número de iterações a executar
 * @return Tempo médio de execução
 */
double medir_tempo_medio(void (*funcao)(void*, int, size_t, CompareFn),
                        void *dados, int tamanho, size_t elem_size,
                        CompareFn cmp, int iteracoes);

/* ================================================================
 * FUNÇÕES DE INTERFACE DE USUÁRIO
 * ================================================================ */

/**
 * @brief Limpa a tela do terminal de forma multiplataforma
 */
void limpar_terminal(void);

/**
 * @brief Exibe cabeçalho informativo do programa
 */
void imprimir_cabecalho(void);

/**
 * @brief Exibe menu principal com opções disponíveis
 */
void imprimir_menu(void);

/**
 * @brief Obtém e valida entrada do usuário
 * @return Número válido escolhido pelo usuário, ou -1 se entrada inválida
 */
int obter_opcao_usuario(void);

/**
 * @brief Pausa a execução aguardando interação do usuário
 */
void pausar(void);

/**
 * @brief Executa bateria completa de testes com ambas as versões dos algoritmos
 */
void executar_relatorio_completo(void);

/**
 * @brief Função de comparação genérica para alunos
 * @param a Ponteiro para primeiro aluno
 * @param b Ponteiro para segundo aluno
 * @return Resultado da comparação
 */
int comparar_alunos(const void *a, const void *b);

/**
 * @brief Salva arquivo em múltiplos locais com callback personalizado
 * @param subdir Subdiretório onde salvar
 * @param nome_arquivo Nome do arquivo
 * @param callback Função callback para escrita
 * @param dados Dados a serem salvos
 * @param tamanho Número de elementos
 */
void salvar_arquivo_multiplos_locais(const char* subdir, const char* nome_arquivo,
                                   void (*callback)(FILE*, void*, int), void* dados, int tamanho);

/**
 * @brief Callback para escrever números em arquivo
 * @param arquivo Ponteiro para arquivo
 * @param dados Dados a serem escritos
 * @param tamanho Número de elementos
 */
void escrever_numeros_callback(FILE* arquivo, void* dados, int tamanho);

/**
 * @brief Callback para escrever alunos em arquivo
 * @param arquivo Ponteiro para arquivo
 * @param dados Dados a serem escritos
 * @param tamanho Número de elementos
 */
void escrever_alunos_callback(FILE* arquivo, void* dados, int tamanho);

#endif // UTILS_H
