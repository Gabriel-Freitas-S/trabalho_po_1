/**
 * ================================================================
 * BIBLIOTECA DE UTILITÁRIOS E FUNÇÕES AUXILIARES
 * ================================================================
 *
 * @file utils.h
 * @brief Coleção abrangente de funções utilitárias e comparadores especializados
 * @author Sistema de Análise de Performance de Algoritmos de Ordenação
 *
 * Este módulo implementa uma biblioteca completa de funções auxiliares
 * que dão suporte a todas as operações do sistema. Inclui comparadores
 * especializados, utilitários de interface, manipuladores de dados
 * genéricos e ferramentas de sistema para operações transversais.
 *
 * **Categorias funcionais implementadas:**
 * - **Comparadores especializados**: Funções de comparação para diferentes tipos
 * - **Manipulação de dados genéricos**: Operações type-agnostic de cópia/movimento
 * - **Interface de usuário**: Controles de terminal e entrada do usuário
 * - **Sistema de arquivos**: Operações de diretório e organização de saída
 * - **Formatação e apresentação**: Utilitários para exibição de dados
 * - **Orquestração de experimentos**: Funções de alto nível para execução
 *
 * **Design patterns implementados:**
 * - **Strategy**: Comparadores intercambiáveis para diferentes critérios
 * - **Template Method**: Estrutura comum para operações de I/O
 * - **Facade**: Interfaces simplificadas para operações complexas
 * - **Observer**: Sistema de callbacks para escrita de dados
 *
 * ================================================================
 */

#ifndef UTILS_H
#define UTILS_H

#include "tipos.h"

/* ================================================================
 * FAMÍLIA DE COMPARADORES ESPECIALIZADOS
 * ================================================================ */

/**
 * @brief Compara dois números inteiros em ordem crescente (menor para maior)
 *
 * Função padrão de comparação para ordenação de arrays de inteiros.
 * Compatível com qsort() e todos os algoritmos de ordenação implementados.
 *
 * **Como funciona:**
 * - Retorna valor negativo se primeiro número é menor
 * - Retorna valor positivo se primeiro número é maior
 * - Retorna zero se os números são iguais
 *
 * **Exemplo de uso:**
 * ```c
 * int numeros[] = {3, 1, 4, 1, 5};
 * qsort(numeros, 5, sizeof(int), comparar_inteiros);
 * // Resultado: [1, 1, 3, 4, 5]
 * ```
 *
 * @param a Ponteiro para primeiro inteiro (const void*)
 * @param b Ponteiro para segundo inteiro (const void*)
 * @return Negativo se a < b, positivo se a > b, zero se a == b
 * @see comparar_inteiros_decrescente() Para ordem inversa
 * @see qsort() Função da biblioteca padrão que usa este comparador
 */
int comparar_inteiros(const void *a, const void *b);

/**
 * @brief Compara dois números inteiros em ordem decrescente (maior para menor)
 *
 * Função de comparação para ordenação reversa de arrays de inteiros.
 * Útil quando você precisa dos maiores valores primeiro.
 *
 * **Como funciona:**
 * - Retorna valor positivo se primeiro número é menor
 * - Retorna valor negativo se primeiro número é maior
 * - Retorna zero se os números são iguais
 *
 * **Exemplo de uso:**
 * ```c
 * int scores[] = {85, 92, 78, 96, 88};
 * qsort(scores, 5, sizeof(int), comparar_inteiros_decrescente);
 * // Resultado: [96, 92, 88, 85, 78] (maiores primeiro)
 * ```
 *
 * @param a Ponteiro para primeiro inteiro (const void*)
 * @param b Ponteiro para segundo inteiro (const void*)
 * @return Positivo se a < b, negativo se a > b, zero se a == b
 * @see comparar_inteiros() Para ordem crescente normal
 */
int comparar_inteiros_decrescente(const void *a, const void *b);

/**
 * @brief Compara dois alunos por nome em ordem alfabética
 *
 * Função de comparação para ordenar registros de alunos pelo campo nome.
 * Realiza comparação lexicográfica (ordem de dicionário) dos nomes.
 *
 * **Como funciona:**
 * - Usa strcmp() internamente para comparar as strings
 * - Ignora diferenças de maiúscula/minúscula dependendo da implementação
 * - Retorna resultado da comparação alfabética
 *
 * **Exemplo de uso:**
 * ```c
 * Aluno turma[] = {{"Carlos"}, {"Ana"}, {"Bruno"}};
 * qsort(turma, 3, sizeof(Aluno), comparar_alunos_por_nome);
 * // Resultado: Ana, Bruno, Carlos
 * ```
 *
 * @param a Ponteiro para primeiro aluno (const void*)
 * @param b Ponteiro para segundo aluno (const void*)
 * @return Resultado da comparação lexicográfica dos nomes
 * @see comparar_alunos_por_data() Para ordenar por data de nascimento
 * @see Aluno.nome Campo usado na comparação
 */
int comparar_alunos_por_nome(const void *a, const void *b);

/**
 * @brief Compara dois alunos por data de nascimento (mais novo para mais velho)
 *
 * Ordena alunos cronologicamente pela data de nascimento.
 * Assume formato de data "DD/MM/AAAA" nos registros.
 *
 * **Como funciona:**
 * - Extrai dia, mês e ano de cada data
 * - Compara primeiro por ano, depois mês, depois dia
 * - Alunos mais novos (datas mais recentes) ficam primeiro
 *
 * **Formato esperado:** "DD/MM/AAAA" (ex: "15/03/2000")
 *
 * **Exemplo de uso:**
 * ```c
 * Aluno turma[] = {{"Ana", "01/01/2000"}, {"Bruno", "15/06/1999"}};
 * qsort(turma, 2, sizeof(Aluno), comparar_alunos_por_data);
 * // Ana (2000) fica antes de Bruno (1999)
 * ```
 *
 * @param a Ponteiro para primeiro aluno (const void*)
 * @param b Ponteiro para segundo aluno (const void*)
 * @return Negativo se a mais novo, positivo se a mais velho, zero se iguais
 * @see comparar_alunos_por_nome() Para ordenar por nome
 * @see Aluno.data_nascimento Campo usado na comparação
 */
int comparar_alunos_por_data(const void *a, const void *b);

/**
 * @brief Compara dois alunos por bairro em ordem alfabética
 *
 * Função para agrupar alunos por região geográfica (bairro).
 * Útil para análises demográficas ou logística de transporte.
 *
 * **Aplicações práticas:**
 * - Organizar transporte escolar por região
 * - Análise de distribuição geográfica dos alunos
 * - Agrupamento por proximidade residencial
 *
 * **Exemplo de uso:**
 * ```c
 * qsort(alunos, total, sizeof(Aluno), comparar_alunos_por_bairro);
 * // Agrupa alunos do mesmo bairro
 * ```
 *
 * @param a Ponteiro para primeiro aluno (const void*)
 * @param b Ponteiro para segundo aluno (const void*)
 * @return Resultado da comparação lexicográfica dos bairros
 * @see comparar_alunos_por_cidade() Para ordenar por cidade
 * @see Aluno.bairro Campo usado na comparação
 */
int comparar_alunos_por_bairro(const void *a, const void *b);

/**
 * @brief Compara dois alunos por cidade em ordem alfabética
 *
 * Função para agrupar alunos por cidade de origem.
 * Útil em instituições que atendem múltiplas cidades.
 *
 * **Aplicações práticas:**
 * - Relatórios por origem geográfica dos alunos
 * - Estatísticas de distribuição regional
 * - Organização de eventos por localidade
 *
 * **Exemplo de uso:**
 * ```c
 * qsort(estudantes, quantidade, sizeof(Aluno), comparar_alunos_por_cidade);
 * // Agrupa por cidade: Belo Horizonte, Contagem, Nova Lima...
 * ```
 *
 * @param a Ponteiro para primeiro aluno (const void*)
 * @param b Ponteiro para segundo aluno (const void*)
 * @return Resultado da comparação lexicográfica das cidades
 * @see comparar_alunos_por_bairro() Para ordenar por bairro
 * @see Aluno.cidade Campo usado na comparação
 */
int comparar_alunos_por_cidade(const void *a, const void *b);

/* ================================================================
 * PRIMITIVAS DE MANIPULAÇÃO DE DADOS TYPE-AGNOSTIC
 * ================================================================ */

/**
 * @brief Copia um elemento de qualquer tipo de uma posição de memória para outra
 *
 * Função genérica para copiar elementos de tipos arbitrários.
 * Útil para trabalhar com dados de tamanho variável nos algoritmos.
 *
 * **Como funciona:**
 * - Usa memcpy() para copiar byte a byte
 * - Funciona com qualquer tipo de dados (int, struct, etc.)
 * - Preserva perfeitamente o conteúdo original
 *
 * **Exemplo de uso:**
 * ```c
 * int origem = 42;
 * int destino;
 * copiar_elemento(&destino, &origem, sizeof(int));
 * // destino agora contém 42
 * ```
 *
 * @param destino Ponteiro para posição onde será copiado o elemento
 * @param origem Ponteiro para elemento a ser copiado (não modificado)
 * @param elem_size Tamanho do elemento em bytes (ex: sizeof(int))
 * @see copiar_array() Para copiar múltiplos elementos de uma vez
 * @see memcpy() Função da biblioteca padrão usada internamente
 */
void copiar_elemento(void *destino, const void *origem, size_t elem_size);

/**
 * @brief Copia um array completo para outro local de memória
 *
 * Função eficiente para duplicar arrays inteiros de qualquer tipo.
 * Essencial para preservar dados originais durante testes de algoritmos.
 *
 * **Como funciona:**
 * - Copia todos os elementos do array de origem
 * - Preserva a ordem e conteúdo originais
 * - Funciona com arrays de qualquer tipo de dados
 *
 * **Exemplo de uso:**
 * ```c
 * int original[] = {3, 1, 4, 1, 5};
 * int copia[5];
 * copiar_array(original, copia, 5, sizeof(int));
 * // copia agora contém {3, 1, 4, 1, 5}
 * ```
 *
 * @param origem Ponteiro para array de origem (dados preservados)
 * @param destino Ponteiro para array de destino (será sobrescrito)
 * @param tamanho Número de elementos a copiar
 * @param elem_size Tamanho de cada elemento em bytes
 * @see copiar_elemento() Para copiar um único elemento
 * @see medir_algoritmo() Função que usa esta para preservar dados originais
 */
void copiar_array(const void *origem, void *destino, int tamanho, size_t elem_size);

/* ================================================================
 * SUBSISTEMA DE INTERFACE E CONTROLE DE TERMINAL
 * ================================================================ */

/**
 * @brief Limpa a tela do terminal de forma multiplataforma
 *
 * Remove todo o conteúdo visível do terminal para melhorar a interface.
 * Funciona em Windows, Linux e macOS usando comandos específicos.
 *
 * **Como funciona:**
 * - Windows: Usa comando "cls"
 * - Linux/Unix/macOS: Usa comando "clear"
 * - Detecta automaticamente o sistema operacional
 *
 * **Quando usar:**
 * - Antes de exibir novos menus
 * - Para organizar visualmente a interface
 * - Entre diferentes seções do programa
 *
 * @see imprimir_menu() Função que geralmente chama esta primeiro
 */
void limpar_terminal(void);

/**
 * @brief Pausa a execução do programa aguardando interação do usuário
 *
 * Interrompe o fluxo do programa até que o usuário pressione ENTER.
 * Útil para permitir que o usuário leia informações na tela.
 *
 * **Como funciona:**
 * - Exibe mensagem "Pressione ENTER para continuar..."
 * - Aguarda o usuário pressionar ENTER
 * - Continua a execução após a interação
 *
 * **Quando usar:**
 * - Após exibir relatórios longos
 * - Entre diferentes seções do programa
 * - Para dar tempo de leitura ao usuário
 *
 * **Exemplo de uso:**
 * ```c
 * printf("Relatório gerado com sucesso!\n");
 * pausar(); // Usuário pode ler a mensagem
 * limpar_terminal(); // Depois limpa a tela
 * ```
 *
 * @see limpar_terminal() Função comumente chamada após esta
 */
void pausar(void);

/**
 * @brief Obtém opção numérica do usuário com validação robusta
 *
 * Lê entrada do usuário e valida se é um número válido.
 * Trata erros de entrada e fornece feedback ao usuário.
 *
 * **Validações realizadas:**
 * - Verifica se entrada é um número inteiro
 * - Trata caracteres inválidos
 * - Limpa buffer de entrada em caso de erro
 * - Fornece feedback sobre entradas inválidas
 *
 * **Exemplo de uso:**
 * ```c
 * printf("Escolha uma opção (1-5): ");
 * int opcao = obter_opcao_usuario();
 * if (opcao == -1) {
 *     printf("Entrada inválida!\n");
 * }
 * ```
 *
 * @return Número inteiro válido escolhido pelo usuário, ou -1 se entrada inválida
 * @see imprimir_menu() Função que usa esta para capturar escolhas do menu
 */
int obter_opcao_usuario(void);

/* ================================================================
 * SISTEMA DE APRESENTAÇÃO E DOCUMENTAÇÃO INTERATIVA
 * ================================================================ */

/**
 * @brief Exibe cabeçalho informativo e apresentação do programa
 *
 * Mostra informações introdutórias sobre o sistema de análise
 * de algoritmos, incluindo versão, propósito e instruções básicas.
 *
 * **O que exibe:**
 * - Título do programa e versão
 * - Descrição do propósito do sistema
 * - Informações sobre os desenvolvedores
 * - Instruções básicas de uso
 *
 * **Quando usar:**
 * - No início da execução do programa
 * - Como tela de boas-vindas ao usuário
 * - Para contextualizar o propósito da aplicação
 *
 * @see imprimir_menu() Função geralmente chamada após esta
 * @see limpar_terminal() Função comumente chamada antes desta
 */
void imprimir_cabecalho(void);

/**
 * @brief Exibe o menu principal de opções do sistema
 *
 * Apresenta todas as opções disponíveis ao usuário em formato
 * numerado e organizado. Interface principal de navegação do programa.
 *
 * **Opções típicas incluem:**
 * - Executar algoritmos individuais
 * - Comparar todos os algoritmos
 * - Visualizar informações dos algoritmos
 * - Gerar relatórios comparativos
 * - Sair do programa
 *
 * **Exemplo de saída:**
 * ```
 * === MENU PRINCIPAL ===
 * 1. Executar algoritmo específico
 * 2. Comparar todos os algoritmos
 * 3. Informações dos algoritmos
 * 4. Sair
 * ```
 *
 * @see obter_opcao_usuario() Função chamada após esta para capturar escolha
 * @see imprimir_cabecalho() Função geralmente chamada antes desta
 */
void imprimir_menu(void);

/**
 * @brief Exibe tabela informativa com características de todos os algoritmos
 *
 * Apresenta uma tabela formatada com informações técnicas detalhadas
 * sobre cada algoritmo implementado. Útil para estudo e comparação teórica.
 *
 * **Informações exibidas:**
 * - Nome do algoritmo
 * - Complexidade no melhor caso
 * - Complexidade no caso médio
 * - Complexidade no pior caso
 * - Se o algoritmo é estável ou não
 * - Características especiais
 *
 * **Exemplo de formato:**
 * ```
 * | Algoritmo    | Melhor | Médio  | Pior   | Estável |
 * |-------------|--------|--------|--------|---------|
 * | Bubble Sort | O(n)   | O(n²)  | O(n²)  | Sim     |
 * | Quick Sort  | O(nlogn)| O(nlogn)| O(n²) | Não     |
 * ```
 *
 * **Quando usar:**
 * - Para consulta rápida das características dos algoritmos
 * - Como material de estudo sobre complexidade
 * - Para decidir qual algoritmo usar em situações específicas
 *
 * @see AlgoritmoInfo Estrutura que contém os dados exibidos
 * @see NUM_ALGORITMOS Constante que define quantos algoritmos são mostrados
 */
void exibir_info_algoritmos(void);

/* ================================================================
 * SUBSISTEMA DE GERENCIAMENTO DE ARQUIVOS E PERSISTÊNCIA
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
 * ORQUESTRADOR PRINCIPAL DE EXPERIMENTOS E ANÁLISES
 * ================================================================ */

/**
 * @brief Executa bateria completa de testes com versões otimizadas e didáticas
 *
 * Função de mais alto nível que executa todos os algoritmos implementados
 * com todos os datasets disponíveis, testando tanto versões otimizadas
 * quanto didáticas. Gera relatórios comparativos completos.
 *
 * **O que executa:**
 * - Todos os 7 algoritmos implementados
 * - Versões otimizadas e não otimizadas de cada um
 * - Todos os datasets de números (crescentes, decrescentes, aleatórios)
 * - Todos os datasets de alunos
 * - Múltiplos tamanhos de dados (500, 5000, 10000, 50000)
 *
 * **Relatórios gerados:**
 * - Comparações detalhadas por dataset
 * - Rankings de performance por categoria
 * - Análise de estabilidade dos algoritmos
 * - Relatório final consolidado
 *
 * **Tempo de execução:** Pode demorar vários minutos para completar
 *
 * **Quando usar:**
 * - Para análise completa e abrangente do sistema
 * - Para gerar documentação completa de performance
 * - Para estudos comparativos detalhados
 * - Para validação completa de todas as implementações
 *
 * @see executar_analise_completa_todos() Função que pode ser chamada internamente
 * @see criar_diretorios_output() Função chamada no início para preparar estrutura
 */
void executar_relatorio_completo(void);

/* ================================================================
 * COMPARADOR PADRÃO PARA ESTRUTURAS DE ESTUDANTES
 * ================================================================ */

/**
 * @brief Comparador padrão para estruturas de estudantes (critério: nome)
 *
 * Função de comparação padrão que implementa ordenação alfabética por nome
 * para estruturas [`Aluno`](include/tipos.h:100). Serve como interface simplificada
 * quando o critério de ordenação não é especificado explicitamente.
 *
 * **Comportamento:**
 * - Ordenação lexicográfica crescente por nome
 * - Case-sensitive (maiúsculas antes de minúsculas)
 * - Compatível com qsort() e todos os algoritmos do sistema
 *
 * **Equivalência funcional:**
 * Esta função é um alias para [`comparar_alunos_por_nome()`](include/utils.h:103),
 * fornecendo uma interface mais concisa para o caso de uso mais comum.
 *
 * @param a Ponteiro para primeira estrutura Aluno
 * @param b Ponteiro para segunda estrutura Aluno
 * @return Resultado da comparação lexicográfica dos nomes
 * @see comparar_alunos_por_nome() Implementação subjacente
 * @see comparar_alunos_por_data() Para ordenação cronológica
 */
int comparar_alunos(const void *a, const void *b);

#endif // UTILS_H
