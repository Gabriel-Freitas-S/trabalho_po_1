/**
 * ================================================================
 * SISTEMA DE ENTRADA/SAÍDA E GERENCIAMENTO DE DADOS
 * ================================================================
 *
 * @file io.h
 * @brief Sistema completo de I/O para manipulação de datasets e persistência de resultados
 * @author Sistema de Análise de Performance de Algoritmos de Ordenação
 *
 * Este módulo implementa um sistema robusto de entrada e saída de dados,
 * fornecendo funcionalidades completas para carregamento de datasets,
 * validação de dados, persistência de resultados e gerenciamento do
 * sistema de arquivos para organização de experimentos.
 *
 * **Funcionalidades principais:**
 * - Carregamento automático de datasets de múltiplos tipos
 * - Validação e verificação de integridade de dados
 * - Persistência estruturada de resultados de experimentos
 * - Gerenciamento inteligente de diretórios e caminhos
 * - Suporte multiplataforma para operações de arquivo
 * - Interface unificada para diferentes formatos de dados
 *
 * **Tipos de dados suportados:**
 * - Números inteiros (datasets numéricos de teste)
 * - Estruturas de estudantes (dados complexos para validação)
 * - Resultados de análise (métricas de performance)
 * - Relatórios formatados (documentação científica)
 *
 * **Organização estrutural:**
 * ```
 * data/           - Datasets de entrada
 * output/         - Resultados experimentais
 *   numeros/      - Dados ordenados (numéricos)
 *   alunos/       - Dados ordenados (estruturas)
 *   relatorios/   - Análises comparativas
 * ```
 *
 * ================================================================
 */

#ifndef IO_H
#define IO_H

#include "tipos.h"

/* ================================================================
 * SUBSISTEMA DE CARREGAMENTO E LEITURA DE DATASETS
 * ================================================================ */

/**
 * @brief Carrega array de números inteiros de um arquivo de dados
 *
 * Lê arquivo contendo números inteiros (um por linha) e retorna
 * array dinâmico alocado. Gerencia automaticamente a memória necessária.
 *
 * **Formato esperado do arquivo:**
 * ```
 * 42
 * 17
 * 85
 * 3
 * ```
 *
 * **Como funciona:**
 * - Abre e valida o arquivo
 * - Conta o número de elementos
 * - Aloca memória dinamicamente
 * - Carrega todos os números do arquivo
 *
 * **Exemplo de uso:**
 * ```c
 * int tamanho;
 * int* dados = carregar_dados_numericos("numeros.txt", &tamanho);
 * if (dados != NULL) {
 *     printf("Carregados %d números\n", tamanho);
 *     free(dados); // Lembre-se de liberar a memória!
 * }
 * ```
 *
 * @param nome_arquivo Nome do arquivo contendo os números
 * @param tamanho Ponteiro para variável que receberá o número de elementos carregados
 * @return Ponteiro para array de inteiros alocado dinamicamente, ou NULL em caso de erro
 * @see ler_numeros() Função alternativa com implementação similar
 * @warning Lembre-se de usar free() para liberar a memória alocada
 */
int* carregar_dados_numericos(const char *nome_arquivo, int *tamanho);

/**
 * @brief Lê números inteiros de arquivo (implementação alternativa simplificada)
 *
 * Versão alternativa de carregamento de dados numéricos com interface
 * ligeiramente diferente. Funciona de forma similar à função principal.
 *
 * **Diferenças da função principal:**
 * - Interface de parâmetros ligeiramente diferente
 * - Pode ter implementação mais otimizada para casos específicos
 * - Mantida para compatibilidade com código existente
 *
 * **Exemplo de uso:**
 * ```c
 * int total;
 * int* array = ler_numeros("data/teste.txt", &total);
 * ```
 *
 * @param caminho_arquivo Caminho completo para o arquivo de dados
 * @param tamanho Ponteiro para armazenar a quantidade de números lidos
 * @return Ponteiro para array dinâmico de inteiros, ou NULL se erro
 * @see carregar_dados_numericos() Função principal equivalente
 * @warning Memória deve ser liberada com free() após uso
 */
int* ler_numeros(const char* caminho_arquivo, int* tamanho);

/**
 * @brief Carrega registros de alunos de um arquivo de dados
 *
 * Lê arquivo contendo informações de alunos em formato estruturado
 * e retorna array de estruturas Aluno alocado dinamicamente.
 *
 * **Formato esperado do arquivo:**
 * ```
 * Ana Silva|15/03/2000|Centro|Belo Horizonte
 * Bruno Costa|22/07/1999|Savassi|Belo Horizonte
 * ```
 *
 * **Como funciona:**
 * - Abre e valida o arquivo
 * - Conta número de registros
 * - Aloca memória para array de estruturas
 * - Parseia cada linha e preenche estruturas
 *
 * **Exemplo de uso:**
 * ```c
 * int quantidade;
 * Aluno* turma = carregar_dados_alunos("alunos.txt", &quantidade);
 * if (turma != NULL) {
 *     printf("Nome do primeiro aluno: %s\n", turma[0].nome);
 *     free(turma); // Liberar memória após uso
 * }
 * ```
 *
 * @param nome_arquivo Nome do arquivo contendo dados dos alunos
 * @param tamanho Ponteiro para variável que receberá o número de alunos carregados
 * @return Ponteiro para array de estruturas Aluno, ou NULL em caso de erro
 * @see ler_alunos() Função alternativa com implementação similar
 * @see Aluno Estrutura de dados retornada pela função
 * @warning Usar free() para liberar a memória alocada
 */
Aluno* carregar_dados_alunos(const char *nome_arquivo, int *tamanho);

/**
 * @brief Lê dados de alunos de arquivo (implementação alternativa simplificada)
 *
 * Versão alternativa para carregar registros de alunos com interface
 * ligeiramente diferente da função principal.
 *
 * **Características:**
 * - Funcionalidade equivalente à função principal
 * - Interface de parâmetros com nomenclatura diferente
 * - Mantida para compatibilidade e flexibilidade
 *
 * **Exemplo de uso:**
 * ```c
 * int total_alunos;
 * Aluno* estudantes = ler_alunos("data/estudantes.txt", &total_alunos);
 * ```
 *
 * @param caminho_arquivo Caminho completo para arquivo de dados de alunos
 * @param tamanho Ponteiro para receber a quantidade de registros lidos
 * @return Array dinâmico de estruturas Aluno, ou NULL se erro
 * @see carregar_dados_alunos() Função principal equivalente
 * @see Aluno Estrutura de dados processada
 * @warning Lembrar de liberar memória com free()
 */
Aluno* ler_alunos(const char* caminho_arquivo, int* tamanho);

/**
 * @brief Verifica se um arquivo existe e é acessível para leitura
 *
 * Testa a existência e permissão de leitura de um arquivo antes
 * de tentar operações de carregamento de dados.
 *
 * **O que verifica:**
 * - Se o arquivo existe no sistema
 * - Se o arquivo pode ser aberto para leitura
 * - Se não há problemas de permissão
 *
 * **Exemplo de uso:**
 * ```c
 * if (arquivo_existe("dados.txt")) {
 *     printf("Arquivo encontrado, prosseguindo...\n");
 *     int* dados = carregar_dados_numericos("dados.txt", &tamanho);
 * } else {
 *     printf("Erro: Arquivo não encontrado!\n");
 * }
 * ```
 *
 * **Quando usar:**
 * - Antes de tentar carregar arquivos de dados
 * - Para validação de entrada do usuário
 * - Para evitar erros de abertura de arquivo
 *
 * @param nome_arquivo Nome ou caminho do arquivo a verificar
 * @return 1 se arquivo existe e é legível, 0 caso contrário
 * @see carregar_dados_numericos() Função que se beneficia desta verificação
 * @see carregar_dados_alunos() Função que se beneficia desta verificação
 */
int arquivo_existe(const char *nome_arquivo);

/**
 * @brief Lista todos os arquivos de dados disponíveis no diretório
 *
 * Examina o diretório de dados e exibe uma lista formatada
 * de todos os arquivos disponíveis para carregamento.
 *
 * **O que exibe:**
 * - Arquivos de dados numéricos (.txt)
 * - Arquivos de dados de alunos
 * - Informações sobre tamanho dos datasets
 * - Status de disponibilidade de cada arquivo
 *
 * **Exemplo de saída:**
 * ```
 * === ARQUIVOS DISPONÍVEIS ===
 * [NÚMEROS]
 * ✓ numeros_aleatorios_500.txt
 * ✓ numeros_crescentes_5000.txt
 *
 * [ALUNOS]
 * ✓ registros_pessoas_1000.txt
 * ```
 *
 * **Quando usar:**
 * - Para mostrar opções ao usuário
 * - Para diagnóstico de problemas de dados
 * - Como ajuda na interface do programa
 *
 * @see arquivo_existe() Função usada internamente para verificar cada arquivo
 */
void listar_arquivos_disponiveis(void);

/* ================================================================
 * SUBSISTEMA DE PERSISTÊNCIA E ESCRITA DE RESULTADOS
 * ================================================================ */

/**
 * @brief Persiste dataset numérico ordenado com metadados do algoritmo
 *
 * Salva array de números inteiros em formato estruturado, incluindo
 * informações sobre o algoritmo utilizado para ordenação e timestamp
 * da operação. Essencial para validação posterior de corretude.
 *
 * **Formato de saída:**
 * ```
 * # Ordenado por: [Nome do Algoritmo]
 * # Timestamp: [Data/Hora]
 * # Elementos: [Quantidade]
 * 1
 * 2
 * 3
 * ...
 * ```
 *
 * @param dados Array de inteiros ordenados a ser persistido
 * @param tamanho Número de elementos no array
 * @param nome_arquivo Caminho/nome do arquivo de destino
 * @param algoritmo Nome do algoritmo usado para ordenação
 * @return 1 se operação bem-sucedida, 0 em caso de erro
 * @see salvar_dados_alunos() Para persistência de estruturas complexas
 */
int salvar_dados_numericos(int *dados, int tamanho, const char *nome_arquivo,
                          const char *algoritmo);

/**
 * @brief Persiste dataset de estudantes ordenado com metadados
 *
 * Salva array de estruturas [`Aluno`](include/tipos.h:100) em formato delimitado,
 * preservando todos os campos e incluindo informações sobre o
 * algoritmo de ordenação utilizado.
 *
 * **Formato de saída:**
 * ```
 * # Ordenado por: [Nome do Algoritmo]
 * # Critério: [Por nome/data/bairro/cidade]
 * Nome|Data|Bairro|Cidade
 * Ana Silva|15/03/2000|Centro|Belo Horizonte
 * Bruno Costa|22/07/1999|Savassi|Belo Horizonte
 * ```
 *
 * @param dados Array de estruturas Aluno ordenadas
 * @param tamanho Número de registros no array
 * @param nome_arquivo Caminho/nome do arquivo de destino
 * @param algoritmo Nome do algoritmo usado para ordenação
 * @return 1 se operação bem-sucedida, 0 em caso de erro
 * @see Aluno Estrutura de dados persistida
 */
int salvar_dados_alunos(Aluno *dados, int tamanho, const char *nome_arquivo,
                       const char *algoritmo);

/**
 * @brief Persiste métricas de performance em arquivo dedicado
 *
 * Salva estrutura [`ResultadoTempo`](include/tipos.h:134) em formato estruturado
 * para análise posterior e geração de relatórios. Cada algoritmo
 * gera seu próprio arquivo de métricas.
 *
 * **Informações persistidas:**
 * - Tempo de execução (precisão de nanossegundos)
 * - Número de comparações realizadas
 * - Número de trocas/movimentações
 * - Metadata do experimento (tamanho, tipo de dados)
 *
 * @param resultado Estrutura com métricas de performance
 * @param diretorio Diretório base onde salvar o arquivo
 * @return 1 se operação bem-sucedida, 0 em caso de erro
 * @see ResultadoTempo Estrutura de dados persistida
 */
int salvar_resultado_analise(ResultadoTempo *resultado, const char *diretorio);

/* ================================================================
 * SUBSISTEMA DE GERENCIAMENTO DO SISTEMA DE ARQUIVOS
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
 * SUBSISTEMA DE VALIDAÇÃO E VERIFICAÇÃO DE INTEGRIDADE
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
 * INTERFACES ESPECIALIZADAS DE PERSISTÊNCIA
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
