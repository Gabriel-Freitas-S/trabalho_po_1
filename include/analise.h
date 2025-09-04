/**
 * ==============================================================
 * SISTEMA DE ANÁLISE DE PERFORMANCE - MEDIÇÃO E BENCHMARKING
 * ==============================================================
 *
 * @file analise.h
 * @brief Sistema completo de medição de performance e geração de relatórios analíticos
 * @author Sistema de Análise de Performance de Algoritmos de Ordenação
 *
 * Este módulo implementa um sistema científico de benchmarking para algoritmos
 * de ordenação, fornecendo medições precisas de performance e análises
 * comparativas detalhadas. O sistema utiliza técnicas avançadas de cronometragem
 * multiplataforma para garantir máxima precisão e confiabilidade das medições.
 *
 * **Capacidades do sistema de análise:**
 * - Medição de tempo com precisão de nanossegundos
 * - Coleta de métricas operacionais (comparações, trocas, movimentações)
 * - Análise de estabilidade algorítmica
 * - Geração de relatórios comparativos formatados
 * - Processamento em lote (batch) de múltiplos algoritmos e datasets
 * - Validação experimental de complexidades teóricas
 *
 * **Compatibilidade multiplataforma:**
 * - Windows: QueryPerformanceCounter (alta precisão)
 * - Linux/Unix: clock_gettime com CLOCK_MONOTONIC
 * - Sistemas genéricos: gettimeofday (fallback)
 *
 * **Metodologia científica aplicada:**
 * - Medições repetidas para redução de ruído estatístico
 * - Isolamento de execução para minimizar interferências
 * - Preservação de dados originais para validação de corretude
 * - Análise estatística de resultados (média, mínimo, máximo)
 *
 * ==============================================================
 */

#ifndef ANALISE_H
#define ANALISE_H

#include "tipos.h"

/* ==============================================================
 * NÚCLEO DE MEDIÇÃO TEMPORAL E COLETA DE MÉTRICAS
 * ============================================================== */

/**
 * @brief Obtém timestamp de alta precisão para medição de performance
 *
 * Esta função retorna o tempo atual com a maior precisão disponível no sistema.
 * É essencial para medir com precisão o tempo de execução dos algoritmos.
 *
 * **Como funciona:**
 * - Windows: QueryPerformanceCounter (precisão de microssegundos)
 * - Linux/Unix: clock_gettime CLOCK_MONOTONIC (precisão de nanossegundos)
 * - Outros sistemas: gettimeofday (precisão de microssegundos)
 *
 * **Quando usar:**
 * Para cronometrar execução de algoritmos e obter medições precisas
 *
 * @return Timestamp em segundos (double) com precisão de nanossegundos
 * @see medir_algoritmo() Para medição completa de algoritmos
 */
double obter_tempo_preciso(void);

/**
 * @brief Executa medição completa de performance de um algoritmo de ordenação
 *
 * Esta é a função principal para analisar o desempenho de algoritmos.
 * Ela mede tempo de execução, conta comparações e trocas durante a ordenação.
 *
 * **O que faz:**
 * - Cronometra o tempo de execução com precisão de nanossegundos
 * - Conta número de comparações entre elementos
 * - Conta número de trocas/movimentações realizadas
 * - Retorna todos os dados em uma estrutura organizada
 *
 * **Como usar:**
 * ```c
 * ResultadoTempo resultado = medir_algoritmo(&info_bubble, dados, 1000,
 *                                           sizeof(int), comparar_inteiros, "numeros");
 * ```
 *
 * @param algoritmo_info Estrutura com informações do algoritmo (nome, função, etc.)
 * @param dados Ponteiro para array de dados a serem ordenados
 * @param tamanho Quantidade de elementos no array
 * @param elem_size Tamanho em bytes de cada elemento (ex: sizeof(int))
 * @param cmp Função que compara dois elementos (ex: comparar_inteiros)
 * @param tipo_dados String identificando o tipo: "numeros" ou "alunos"
 * @return Estrutura ResultadoTempo com tempo, comparações, trocas e outras métricas
 * @see ResultadoTempo Estrutura que armazena os resultados
 * @see obter_tempo_preciso() Função usada internamente para cronometragem
 */
ResultadoTempo medir_algoritmo(AlgoritmoInfo *algoritmo_info, void *dados,
                              int tamanho, size_t elem_size, CompareFn cmp,
                              const char *tipo_dados);

/**
 * @brief Testa um algoritmo em todos os datasets disponíveis
 *
 * Executa o mesmo algoritmo em vários conjuntos de dados diferentes
 * (tamanhos variados, dados crescentes, decrescentes, aleatórios).
 * Gera relatórios comparativos para cada teste.
 *
 * **O que faz:**
 * - Carrega automaticamente todos os arquivos de dados relacionados
 * - Executa o algoritmo em cada dataset
 * - Gera arquivos de resultado para cada teste
 * - Salva os dados ordenados em arquivos separados
 *
 * **Exemplo de uso:**
 * ```c
 * executar_analise_completa(&info_quick, "numeros_aleatorios",
 *                          comparar_inteiros, 0);
 * ```
 *
 * @param algoritmo_info Estrutura com dados do algoritmo a ser testado
 * @param nome_arquivo Nome base dos arquivos (ex: "numeros_aleatorios")
 * @param cmp Função de comparação apropriada para o tipo de dados
 * @param eh_aluno 1 para dados de alunos, 0 para dados numéricos
 * @see medir_algoritmo() Função chamada internamente para cada dataset
 * @see executar_analise_completa_todos() Para testar todos os algoritmos de uma vez
 */
void executar_analise_completa(AlgoritmoInfo *algoritmo_info,
                              const char *nome_arquivo, CompareFn cmp,
                              int eh_aluno);

/* ==============================================================
 * SISTEMA DE PROCESSAMENTO EM LOTE - ANÁLISES AUTOMATIZADAS
 * ============================================================== */

/**
 * @brief Testa todos os algoritmos implementados com dados numéricos
 *
 * Executa uma bateria completa de testes com todos os algoritmos
 * disponíveis usando apenas datasets de números inteiros.
 * Ideal para comparar performance em dados simples.
 *
 * **O que acontece:**
 * - Carrega todos os arquivos de números (crescentes, decrescentes, aleatórios)
 * - Testa todos os 7 algoritmos implementados
 * - Gera relatórios comparativos
 * - Salva resultados organizados por tamanho de dataset
 *
 * @see executar_todos_algoritmos_alunos() Para dados de estruturas complexas
 * @see executar_analise_completa_todos() Para análise completa de ambos os tipos
 */
void executar_todos_algoritmos_numeros(void);

/**
 * @brief Testa todos os algoritmos implementados com dados de alunos
 *
 * Executa uma bateria completa de testes com todos os algoritmos
 * disponíveis usando datasets de estruturas Aluno (dados complexos).
 * Ideal para testar performance com dados do mundo real.
 *
 * **O que acontece:**
 * - Carrega arquivos de registros de alunos
 * - Testa ordenação por nome, data, bairro, cidade
 * - Compara performance com dados complexos vs. simples
 * - Gera relatórios específicos para estruturas
 *
 * @see executar_todos_algoritmos_numeros() Para dados numéricos simples
 * @see comparar_alunos_por_nome() Função de comparação usada internamente
 */
void executar_todos_algoritmos_alunos(void);

/**
 * @brief Executa análise completa e abrangente de todos os algoritmos
 *
 * Esta é a função mais completa do sistema de análise.
 * Testa todos os algoritmos com todos os tipos de dados disponíveis,
 * gerando um conjunto completo de relatórios comparativos.
 *
 * **O que inclui:**
 * - Testes com dados numéricos (crescentes, decrescentes, aleatórios)
 * - Testes com dados de alunos (estruturas complexas)
 * - Análise de estabilidade dos algoritmos
 * - Relatórios comparativos detalhados
 * - Rankings de performance por categoria
 *
 * **Tempo estimado:** Pode demorar vários minutos para datasets grandes
 *
 * @see executar_todos_algoritmos_numeros() Para apenas dados numéricos
 * @see executar_todos_algoritmos_alunos() Para apenas dados de alunos
 * @see analisar_estabilidade_algoritmos() Função chamada internamente
 */
void executar_analise_completa_todos(void);

/* ==============================================================
 * MÓDULO DE ANÁLISE DE ESTABILIDADE ALGORÍTMICA
 * ============================================================== */

/**
 * @brief Testa a estabilidade real de todos os algoritmos implementados
 *
 * **O que é estabilidade?**
 * Um algoritmo estável mantém a ordem relativa de elementos iguais.
 * Por exemplo, se temos dois "João" no array, um algoritmo estável
 * garantirá que o primeiro "João" continue antes do segundo após a ordenação.
 *
 * **Como funciona o teste:**
 * - Cria dados de teste com elementos duplicados
 * - Ordena usando cada algoritmo
 * - Verifica se a ordem relativa foi preservada
 * - Compara resultado prático com a teoria
 *
 * **Por que é importante:**
 * - Valida se a implementação está correta
 * - Ajuda a escolher algoritmo adequado para cada situação
 * - Essencial para dados com múltiplos critérios de ordenação
 *
 * @see verificar_estabilidade() Função auxiliar para testar um algoritmo específico
 * @see AlgoritmoInfo.eh_estavel Campo que indica se algoritmo deveria ser estável
 */
void analisar_estabilidade_algoritmos(void);

/**
 * @brief Verifica se um algoritmo específico é estável na prática
 *
 * Compara os dados antes e depois da ordenação para verificar se elementos
 * iguais mantiveram sua ordem relativa original. É uma validação prática
 * da propriedade teórica de estabilidade.
 *
 * **Como funciona:**
 * 1. Compara cada elemento do array ordenado
 * 2. Para elementos com mesmo valor, verifica se ordem original foi mantida
 * 3. Retorna resultado do teste de estabilidade
 *
 * **Exemplo de uso:**
 * ```c
 * int eh_estavel = verificar_estabilidade(&info_insertion, dados_orig,
 *                                        dados_ord, 1000);
 * if (eh_estavel) printf("Algoritmo manteve estabilidade!\n");
 * ```
 *
 * @param algoritmo_info Estrutura com informações do algoritmo testado
 * @param dados_originais Array de dados antes da ordenação (referência)
 * @param dados_ordenados Array de dados após a ordenação (para verificar)
 * @param tamanho Número de elementos em ambos os arrays
 * @return 1 se o algoritmo foi estável, 0 se não foi estável
 * @see analisar_estabilidade_algoritmos() Para testar todos os algoritmos
 * @see Aluno Estrutura usada nos testes (permite identificar elementos duplicados)
 */
int verificar_estabilidade(AlgoritmoInfo *algoritmo_info, Aluno *dados_originais,
                          Aluno *dados_ordenados, int tamanho);

/* ==============================================================
 * SISTEMA DE GERAÇÃO DE RELATÓRIOS E DOCUMENTAÇÃO
 * ============================================================== */

/**
 * @brief Cria relatório comparativo detalhado entre múltiplos algoritmos
 *
 * Gera um arquivo de texto com análise comparativa side-by-side
 * de todos os algoritmos testados. Inclui tabelas formatadas
 * com métricas de performance e análises estatísticas.
 *
 * **Conteúdo do relatório:**
 * - Tabela comparativa de tempos de execução
 * - Número de comparações e trocas por algoritmo
 * - Análise estatística (melhor, pior, médio desempenho)
 * - Recomendações de uso para cada algoritmo
 *
 * **Formato de saída:** Arquivo de texto formatado, legível por humanos
 *
 * @param resultados Array contendo resultados de performance de cada algoritmo
 * @param num_resultados Quantidade de algoritmos no array de resultados
 * @param nome_arquivo Caminho/nome do arquivo onde salvar o relatório
 * @param titulo Título principal que aparecerá no cabeçalho do relatório
 * @see gerar_ranking_por_tempo() Para ranking específico por velocidade
 * @see ResultadoTempo Estrutura com dados de cada algoritmo
 */
void gerar_relatorio_comparativo(ResultadoTempo *resultados, int num_resultados,
                                const char *nome_arquivo, const char *titulo);

/**
 * @brief Cria ranking dos algoritmos ordenado por tempo de execução
 *
 * Gera arquivo com lista dos algoritmos do mais rápido ao mais lento
 * para um conjunto específico de dados. Útil para identificar rapidamente
 * qual algoritmo teve melhor performance.
 *
 * **Formato do ranking:**
 * 1. [Algoritmo mais rápido] - X.XXX segundos
 * 2. [Segundo mais rápido] - X.XXX segundos
 * 3. ...
 *
 * **Quando usar:**
 * - Para escolher algoritmo mais eficiente para um tipo de dados
 * - Para apresentar resultados de forma simples e direta
 * - Como resumo executivo de análises complexas
 *
 * @param resultados Array com dados de performance dos algoritmos
 * @param num_resultados Número de algoritmos a incluir no ranking
 * @param nome_arquivo Caminho onde salvar o arquivo de ranking
 * @see gerar_relatorio_comparativo() Para análise mais detalhada
 * @see comparar_resultados_por_tempo() Função usada internamente para ordenar
 */
void gerar_ranking_por_tempo(ResultadoTempo *resultados, int num_resultados,
                            const char *nome_arquivo);

/**
 * @brief Gera relatório técnico com métricas detalhadas de performance
 *
 * Cria arquivo com dados técnicos aprofundados sobre o desempenho
 * de cada algoritmo. Focado em análise técnica e científica.
 *
 * **Métricas incluídas:**
 * - Tempo de execução (precisão de nanossegundos)
 * - Número exato de comparações realizadas
 * - Número exato de trocas/movimentações
 * - Taxa de operações por segundo
 * - Análise de complexidade prática vs. teórica
 *
 * **Público-alvo:** Desenvolvedores, pesquisadores, análise técnica
 *
 * @param resultados Array com resultados detalhados dos algoritmos
 * @param num_resultados Quantidade de algoritmos analisados
 * @param nome_arquivo Caminho para arquivo de saída das métricas
 * @see gerar_relatorio_comparativo() Para relatório mais acessível
 * @see ResultadoTempo Estrutura que contém todas as métricas
 */
void gerar_relatorio_metricas(ResultadoTempo *resultados, int num_resultados,
                             const char *nome_arquivo);

/**
 * @brief Salva resultado de um algoritmo individual em arquivo próprio
 *
 * Cria arquivo específico para armazenar os resultados de desempenho
 * de um único algoritmo. Útil para análises focadas ou debugging.
 *
 * **Nome do arquivo gerado automaticamente:**
 * `[Algoritmo]_[TipoDados]_[Tamanho].txt`
 *
 * **Exemplo de uso:**
 * ```c
 * ResultadoTempo res = medir_algoritmo(&info_quick, dados, 1000, ...);
 * salvar_resultado_individual(&res);
 * // Gera: Quick_Sort_numeros_1000.txt
 * ```
 *
 * @param resultado Ponteiro para estrutura com dados de performance
 * @see medir_algoritmo() Função que gera a estrutura ResultadoTempo
 * @see ResultadoTempo Estrutura com todas as métricas de performance
 */
void salvar_resultado_individual(ResultadoTempo *resultado);

/* ==============================================================
 * UTILITÁRIOS ESTATÍSTICOS E FUNÇÕES AUXILIARES
 * ============================================================== */

/**
 * @brief Calcula estatísticas descritivas de um conjunto de resultados de performance
 *
 * Analisa um array de resultados e extrai informações estatísticas básicas
 * sobre os tempos de execução. Útil para análise comparativa e identificação
 * de padrões de performance entre algoritmos.
 *
 * **O que calcula:**
 * - Tempo médio de execução
 * - Tempo mínimo (melhor performance)
 * - Tempo máximo (pior performance)
 *
 * **Exemplo de uso:**
 * ```c
 * double medio, min, max;
 * calcular_estatisticas(resultados, 7, &medio, &min, &max);
 * printf("Tempo médio: %.6f segundos\n", medio);
 * ```
 *
 * @param resultados Array com resultados de performance dos algoritmos
 * @param num_resultados Quantidade de resultados no array
 * @param tempo_medio Ponteiro para variável que receberá o tempo médio
 * @param tempo_min Ponteiro para variável que receberá o tempo mínimo
 * @param tempo_max Ponteiro para variável que receberá o tempo máximo
 * @see ResultadoTempo Estrutura que contém os dados de cada algoritmo
 */
void calcular_estatisticas(ResultadoTempo *resultados, int num_resultados,
                          double *tempo_medio, double *tempo_min, double *tempo_max);

/**
 * @brief Função de comparação para ordenar resultados por tempo de execução
 *
 * Compara dois resultados de algoritmos baseado no tempo de execução.
 * Usada internamente pelo sistema de ordenação (qsort) para criar
 * rankings de performance.
 *
 * **Como funciona:**
 * - Retorna valor negativo se primeiro resultado tem tempo menor
 * - Retorna valor positivo se primeiro resultado tem tempo maior
 * - Retorna zero se os tempos são iguais
 *
 * **Uso típico:** Passada como parâmetro para qsort() para ordenar arrays
 *
 * @param a Ponteiro para primeiro resultado (ResultadoTempo*)
 * @param b Ponteiro para segundo resultado (ResultadoTempo*)
 * @return Negativo se a < b, positivo se a > b, zero se iguais
 * @see gerar_ranking_por_tempo() Função que usa esta comparação
 * @see qsort() Função da biblioteca padrão que usa este comparador
 */
int comparar_resultados_por_tempo(const void *a, const void *b);

/**
 * @brief Converte tempo em segundos para string formatada legível
 *
 * Transforma valores de tempo (double) em strings bem formatadas
 * para exibição em relatórios e interface do usuário.
 *
 * **Formatos de saída:**
 * - Nanossegundos: "123.456 ns"
 * - Microssegundos: "123.456 μs"
 * - Milissegundos: "123.456 ms"
 * - Segundos: "1.234 s"
 *
 * **Exemplo de uso:**
 * ```c
 * char buffer[50];
 * formatar_tempo(0.001234, buffer, sizeof(buffer));
 * // Resultado: "1.234 ms"
 * ```
 *
 * @param tempo Valor do tempo em segundos (double)
 * @param buffer Buffer onde será armazenada a string formatada
 * @param tamanho_buffer Tamanho máximo do buffer em bytes
 * @see gerar_relatorio_comparativo() Usa esta função para formatar tempos
 */
void formatar_tempo(double tempo, char *buffer, size_t tamanho_buffer);

/**
 * @brief Formata números grandes com separadores de milhares para legibilidade
 *
 * Converte números grandes (como contadores de comparações/trocas) em
 * strings com separadores de milhares para facilitar a leitura.
 *
 * **Exemplos de formatação:**
 * - 1000 → "1,000"
 * - 1500000 → "1,500,000"
 * - 999 → "999" (sem separador)
 *
 * **Quando usar:**
 * - Para exibir contadores de operações em relatórios
 * - Para melhorar legibilidade de números grandes
 * - Em interfaces de usuário que mostram estatísticas
 *
 * @param numero Número inteiro grande a ser formatado
 * @param buffer Buffer onde será armazenada a string formatada
 * @param tamanho_buffer Tamanho máximo do buffer em bytes
 * @see ResultadoTempo.comparacoes Campo que geralmente precisa desta formatação
 * @see ResultadoTempo.trocas Campo que geralmente precisa desta formatação
 */
void formatar_numero_grande(long long numero, char *buffer, size_t tamanho_buffer);

/* ==============================================================
 * ORQUESTRAÇÃO DE EXECUÇÃO E ANÁLISE COMPARATIVA
 * ============================================================== */

/**
 * @brief Executa bateria completa de todos os algoritmos com métricas detalhadas
 *
 * Função de alto nível que testa todos os algoritmos implementados
 * em um conjunto de dados específico, coletando métricas completas
 * de performance (tempo, comparações, trocas).
 *
 * **O que faz:**
 * - Testa todos os 7 algoritmos no mesmo conjunto de dados
 * - Mede tempo de execução com precisão de nanossegundos
 * - Conta comparações e trocas realizadas
 * - Gera relatório comparativo consolidado
 * - Preserva os dados originais (faz cópias para cada teste)
 *
 * **Exemplo de uso:**
 * ```c
 * executar_todos_algoritmos(numeros, 1000, sizeof(int),
 *                          comparar_inteiros, "numeros", "teste_1000");
 * ```
 *
 * @param dados Ponteiro para dados a serem testados (permanecem inalterados)
 * @param tamanho Quantidade de elementos no array de dados
 * @param elem_size Tamanho em bytes de cada elemento (ex: sizeof(int))
 * @param cmp Função de comparação adequada para o tipo de dados
 * @param tipo_dados String identificando o tipo: "numeros" ou "alunos"
 * @param arquivo_base Nome base usado para gerar arquivos de relatório
 * @see executar_todos_algoritmos_com_salvamento() Para salvar arrays ordenados também
 * @see medir_algoritmo() Função chamada internamente para cada algoritmo
 */
void executar_todos_algoritmos(const void *dados, int tamanho, size_t elem_size, CompareFn cmp,
                              const char* tipo_dados, const char* arquivo_base);

/**
 * @brief Executa todos os algoritmos salvando também os arrays ordenados
 *
 * Versão estendida que além das métricas de performance, salva
 * os arrays ordenados por cada algoritmo em arquivos separados.
 * Útil para verificar corretude e análise posterior dos resultados.
 *
 * **Funcionalidades adicionais:**
 * - Salva array ordenado por cada algoritmo em arquivo próprio
 * - Permite especificar se é versão otimizada ou didática
 * - Organiza arquivos por tipo e versão do algoritmo
 * - Inclui todas as métricas da função básica
 *
 * **Estrutura dos arquivos gerados:**
 * `output/[tipo_dados]/[Algoritmo]_[versao]_[arquivo_base].txt`
 *
 * @param dados Ponteiro para dados originais (preservados)
 * @param tamanho Número de elementos no array
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação para o tipo de dados
 * @param tipo_dados Tipo dos dados ("numeros" ou "alunos")
 * @param arquivo_base Nome base para os arquivos de saída
 * @param versao String identificando versão: "otimizada" ou "nao_otimizada"
 * @see executar_todos_algoritmos() Para versão sem salvamento de arrays
 * @see salvar_resultado_individual() Função usada internamente
 */
void executar_todos_algoritmos_com_salvamento(const void *dados, int tamanho, size_t elem_size, CompareFn cmp,
                                            const char* tipo_dados, const char* arquivo_base, const char* versao);

/**
 * @brief Mede tempo de execução com múltiplas execuções para maior precisão
 *
 * Executa o mesmo algoritmo várias vezes no mesmo conjunto de dados
 * e calcula o tempo médio. Reduz variações causadas por interferências
 * do sistema operacional e melhora a precisão das medições.
 *
 * **Por que usar medição múltipla?**
 * - Reduz ruído causado por outros processos do sistema
 * - Melhora precisão estatística das medições
 * - Fornece resultados mais confiáveis para benchmarks
 * - Compensa variações na latência do sistema
 *
 * **Exemplo de uso:**
 * ```c
 * double tempo_medio = medir_tempo_multiplo(bubble_sort, dados, 1000,
 *                                          sizeof(int), comparar_inteiros, 5);
 * // Executa bubble_sort 5 vezes e retorna a média
 * ```
 *
 * @param sort_fn Ponteiro para função do algoritmo a ser testado
 * @param dados_originais Dados de entrada (não são modificados)
 * @param n Quantidade de elementos nos dados
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação apropriada
 * @param num_execucoes Número de vezes que o algoritmo será executado
 * @return Tempo médio de execução em segundos (double)
 * @see obter_tempo_preciso() Função usada para cronometragem
 * @see medir_algoritmo() Para medição única com métricas completas
 */
double medir_tempo_multiplo(void (*sort_fn)(void*, int, size_t, CompareFn),
                           const void *dados_originais, int n, size_t elem_size,
                           CompareFn cmp, int num_execucoes);

#endif // ANALISE_H
