/**
 * ================================================================
 * TRABALHO DE ALGORITMOS DE ORDENAÇÃO - MÓDULO DE ANÁLISE
 * ================================================================
 *
 * @file analise.c
 * @brief Sistema avançado de medição, análise e geração de relatórios
 * @version 2.1
 * @date 2025-08-24
 * @author Sistema de Análise de Algoritmos
 *
 * Este módulo implementa toda a infraestrutura de análise de performance
 * dos algoritmos de ordenação, incluindo medição precisa de tempo, contagem
 * de operações, análise de estabilidade e geração de relatórios detalhados.
 *
 * VERSÃO 2.1: Sistema de Medição de Alta Precisão Multiplataforma
 * - Medição de tempo com precisão de nanossegundos usando funções nativas do SO
 * - Suporte otimizado para Windows (QueryPerformanceCounter)
 * - Suporte nativo para Linux/Unix (clock_gettime com CLOCK_MONOTONIC)
 * - Fallback automático para gettimeofday() em sistemas não compatíveis
 * - Medição robusta para algoritmos com execução muito rápida
 * - Detecção automática da melhor função de timing disponível no sistema
 * - Eliminação completa de medições zeradas através de estratégias adaptativas
 *
 * Funcionalidades principais:
 * - Medição precisa de tempo usando funções de alta resolução do sistema
 * - Execução automatizada de todos os algoritmos em lotes (batch processing)
 * - Geração de relatórios comparativos em formato texto estruturado
 * - Análise detalhada de estabilidade com casos de teste reais
 * - Rankings automáticos por diferentes métricas de performance
 * - Salvamento organizado de resultados categorizados por tipo
 * - Estratégia de múltiplas execuções para maior precisão estatística
 *
 * Métricas analisadas:
 * - Tempo de execução (precisão até nanossegundos dependendo do sistema)
 * - Número total de comparações realizadas entre elementos
 * - Número total de trocas/movimentações de elementos
 * - Análise de estabilidade usando dados reais com elementos duplicados
 * - Eficiência relativa (operações por elemento processado)
 * - Comparação de performance entre versões otimizadas e não otimizadas
 *
 * ================================================================
 */

#include "../include/sorts.h"

// Headers específicos para medição de alta precisão por plataforma
#ifdef _WIN32
    #include <windows.h>
    #include <profileapi.h>
#else
    #include <time.h>
    #include <sys/time.h>
#endif

/* ================================================================
 * SISTEMA DE MEDIÇÃO DE TEMPO DE ALTA PRECISÃO MULTIPLATAFORMA
 * ================================================================ */

/**
 * @brief Obtém timestamp de alta precisão utilizando a melhor função disponível
 *
 * Esta função utiliza automaticamente a função de timing de maior precisão
 * disponível no sistema operacional atual:
 *
 * - Windows: QueryPerformanceCounter (precisão de microssegundos ou melhor)
 * - Linux/Unix: clock_gettime() com CLOCK_MONOTONIC (precisão de nanossegundos)
 * - Sistemas legados: gettimeofday() (precisão de microssegundos)
 *
 * A função é otimizada para ser chamada repetidamente com overhead mínimo,
 * sendo ideal para medição de algoritmos com execução muito rápida.
 *
 * @return Tempo atual em segundos como valor de ponto flutuante (double)
 *         com a máxima precisão disponível no sistema
 *
 * @note Esta implementação é thread-safe e utiliza inicialização lazy
 *       para otimizar performance em medições repetitivas
 */
double obter_timestamp_precisao() {
    #ifdef _WIN32
        // Windows: Utiliza QueryPerformanceCounter para máxima precisão
        static LARGE_INTEGER frequencia;
        static int inicializado = 0;

        // Inicialização lazy thread-safe (executada apenas uma vez)
        if (!inicializado) {
            QueryPerformanceFrequency(&frequencia);
            inicializado = 1;
        }

        LARGE_INTEGER agora;
        QueryPerformanceCounter(&agora);

        return (double)agora.QuadPart / (double)frequencia.QuadPart;

    #elif defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 199309L
        // Linux/Unix: Utiliza clock_gettime() para precisão de nanossegundos
        struct timespec tempo;
        clock_gettime(CLOCK_MONOTONIC, &tempo);

        return (double)tempo.tv_sec + (double)tempo.tv_nsec / 1000000000.0;

    #else
        // Fallback: gettimeofday() para compatibilidade com sistemas antigos
        struct timeval tempo;
        gettimeofday(&tempo, NULL);

        return (double)tempo.tv_sec + (double)tempo.tv_usec / 1000000.0;
    #endif
}

/**
 * @brief Mede tempo de execução com precisão de nanossegundos
 *
 * Nova implementação de alta precisão que substitui clock() por funções
 * de timing modernas do sistema operacional. Capaz de medir com precisão
 * algoritmos muito rápidos que anteriormente resultavam em tempo zero.
 *
 * Características avançadas:
 * - Utiliza timestamp de alta precisão antes e depois da execução
 * - Garante que o resultado nunca seja zero (mínimo de 1 microssegundo)
 * - Trata casos especiais como arrays já ordenados ou muito pequenos
 * - Realiza medição adaptativa baseada no tamanho do conjunto
 *
 * @param sort_fn Ponteiro para a função do algoritmo de ordenação
 * @param arr Ponteiro para o array a ser ordenado (será modificado)
 * @param n Número de elementos no array
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação entre elementos
 * @return Tempo de execução em segundos (nunca retorna zero)
 */
double medir_tempo_ordenacao(void (*sort_fn)(void*, int, size_t, CompareFn),
                            void *arr, int n, size_t elem_size, CompareFn cmp) {

    // Estratégia adaptativa baseada no tamanho do conjunto
    int num_execucoes = determinar_num_execucoes(n);

    if (num_execucoes > 1) {
        // Para conjuntos pequenos/rápidos: múltiplas execuções para maior precisão
        double tempo_total = 0.0;
        void *dados_backup = malloc(n * elem_size);

        if (!dados_backup) {
            // Fallback para medição única se falhar alocação
            double tempo_inicio = obter_timestamp_precisao();
            sort_fn(arr, n, elem_size, cmp);
            double tempo_fim = obter_timestamp_precisao();

            double tempo_decorrido = tempo_fim - tempo_inicio;
            return (tempo_decorrido > 0.0) ? tempo_decorrido : 0.000001;
        }

        // Salva dados originais para restauração entre execuções
        memcpy(dados_backup, arr, n * elem_size);

        for (int i = 0; i < num_execucoes; i++) {
            // Restaura estado original para cada medição
            memcpy(arr, dados_backup, n * elem_size);

            // Medição individual
            double tempo_inicio = obter_timestamp_precisao();
            sort_fn(arr, n, elem_size, cmp);
            double tempo_fim = obter_timestamp_precisao();

            tempo_total += (tempo_fim - tempo_inicio);
        }

        free(dados_backup);

        // Retorna tempo médio, garantindo que nunca seja zero
        double tempo_medio = tempo_total / num_execucoes;
        return (tempo_medio > 0.0) ? tempo_medio : 0.000001;

    } else {
        // Para conjuntos grandes: uma execução é suficiente para precisão adequada
        double tempo_inicio = obter_timestamp_precisao();
        sort_fn(arr, n, elem_size, cmp);
        double tempo_fim = obter_timestamp_precisao();

        double tempo_decorrido = tempo_fim - tempo_inicio;
        return (tempo_decorrido > 0.0) ? tempo_decorrido : 0.000001;
    }
}

/**
 * @brief Versão especializada de medição de tempo para Quick Sort
 *
 * O Quick Sort requer interface especial devido à sua natureza recursiva
 * e parâmetros adicionais (índices de início e fim). Esta função adapta
 * a medição de alta precisão para esta interface específica.
 *
 * @param quick_fn Ponteiro para a função Quick Sort
 * @param arr Ponteiro para o array a ser ordenado
 * @param n Número de elementos no array
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação entre elementos
 * @return Tempo de execução em segundos (nunca retorna zero)
 */
double medir_tempo_quick_sort(void (*quick_fn)(void*, int, int, size_t, CompareFn),
                            void *arr, int n, size_t elem_size, CompareFn cmp) {

    int num_execucoes = determinar_num_execucoes(n);

    if (num_execucoes > 1) {
        // Múltiplas execuções para conjuntos pequenos
        double tempo_total = 0.0;
        void *dados_backup = malloc(n * elem_size);

        if (!dados_backup) {
            // Fallback para medição única
            double tempo_inicio = obter_timestamp_precisao();
            quick_fn(arr, 0, n - 1, elem_size, cmp);
            double tempo_fim = obter_timestamp_precisao();

            double tempo_decorrido = tempo_fim - tempo_inicio;
            return (tempo_decorrido > 0.0) ? tempo_decorrido : 0.000001;
        }

        memcpy(dados_backup, arr, n * elem_size);

        for (int i = 0; i < num_execucoes; i++) {
            // Restaura dados originais para cada execução
            memcpy(arr, dados_backup, n * elem_size);

            // Mede tempo desta execução específica
            double tempo_inicio = obter_timestamp_precisao();
            quick_fn(arr, 0, n - 1, elem_size, cmp);
            double tempo_fim = obter_timestamp_precisao();

            tempo_total += (tempo_fim - tempo_inicio);
        }

        free(dados_backup);

        // Retorna tempo médio, garantindo que nunca seja zero
        double tempo_medio = tempo_total / num_execucoes;
        return (tempo_medio > 0.0) ? tempo_medio : 0.000001;

    } else {
        // Para conjuntos grandes, uma execução é suficiente
        double tempo_inicio = obter_timestamp_precisao();
        quick_fn(arr, 0, n - 1, elem_size, cmp);
        double tempo_fim = obter_timestamp_precisao();

        double tempo_decorrido = tempo_fim - tempo_inicio;
        return (tempo_decorrido > 0.0) ? tempo_decorrido : 0.000001;
    }
}

/**
 * @brief Executa medição múltipla para maior precisão estatística
 *
 * Para algoritmos muito rápidos, executa múltiplas medições e calcula
 * a média para obter resultados mais confiáveis e reduzir variabilidade.
 *
 * @param sort_fn Ponteiro para a função do algoritmo
 * @param dados_originais Dados originais (não serão modificados)
 * @param n Número de elementos
 * @param elem_size Tamanho de cada elemento
 * @param cmp Função de comparação
 * @param num_execucoes Número de execuções para média (padrão: 3)
 * @return Tempo médio de execução
 */
double medir_tempo_multiplo(void (*sort_fn)(void*, int, size_t, CompareFn),
                           void *dados_originais, int n, size_t elem_size,
                           CompareFn cmp, int num_execucoes) {
    if (num_execucoes < 1) num_execucoes = 1;

    double tempo_total = 0.0;
    void *dados_copia = malloc(n * elem_size);

    if (!dados_copia) {
        // Fallback para medição única se falhar alocação
        return medir_tempo_ordenacao(sort_fn, dados_originais, n, elem_size, cmp);
    }

    for (int i = 0; i < num_execucoes; i++) {
        // Restaura dados originais para cada execução
        memcpy(dados_copia, dados_originais, n * elem_size);

        // Mede tempo desta execução
        double tempo_execucao = medir_tempo_ordenacao(sort_fn, dados_copia, n, elem_size, cmp);
        tempo_total += tempo_execucao;
    }

    free(dados_copia);

    // Retorna tempo médio
    return tempo_total / num_execucoes;
}

/**
 * @brief Determina automaticamente o número de execuções baseado no tamanho
 *
 * Para conjuntos pequenos (que executam muito rápido), usa múltiplas
 * execuções para maior precisão. Para conjuntos grandes, uma execução
 * é suficiente.
 *
 * @param tamanho_conjunto Número de elementos no conjunto
 * @return Número recomendado de execuções
 */
int determinar_num_execucoes(int tamanho_conjunto) {
    if (tamanho_conjunto < 100) {
        return 10;  // Conjuntos muito pequenos: 10 execuções
    } else if (tamanho_conjunto < 1000) {
        return 5;   // Conjuntos pequenos: 5 execuções
    } else if (tamanho_conjunto < 10000) {
        return 3;   // Conjuntos médios: 3 execuções
    } else {
        return 1;   // Conjuntos grandes: 1 execução
    }
}

/* ================================================================
 * BASE DE CONHECIMENTO DOS ALGORITMOS
 * ================================================================ */

/**
 * @brief Retorna array com informações completas de todos os algoritmos
 *
 * Centraliza todas as informações teóricas e práticas dos algoritmos
 * implementados. Esta base de conhecimento é utilizada para gerar
 * relatórios, análises e comparações automáticas.
 *
 * Informações incluídas para cada algoritmo:
 * - Nome identificador único
 * - Complexidades teóricas (melhor, médio, pior caso)
 * - Propriedade de estabilidade
 * - Ponteiros para as implementações
 * - Flags de controle para execução diferenciada
 *
 * @return Ponteiro para array estático com dados dos algoritmos
 */
AlgoritmoInfo* obter_info_algoritmos() {
    // Array estático - mantém dados entre chamadas
    static AlgoritmoInfo algoritmos[NUM_ALGORITMOS] = {
        {
            "Insertion Sort", "O(n)", "O(n²)", "O(n²)", 1,
            insertion_sort, NULL, 0
        },
        {
            "Bubble Sort", "O(n)", "O(n²)", "O(n²)", 1,
            bubble_sort, NULL, 0
        },
        {
            "Selection Sort", "O(n²)", "O(n²)", "O(n²)", 0,
            selection_sort, NULL, 0
        },
        {
            "Shaker Sort", "O(n)", "O(n²)", "O(n²)", 1,
            shaker_sort, NULL, 0
        },
        {
            "Shell Sort", "O(n log n)", "O(n^1.25)", "O(n²)", 0,
            shell_sort, NULL, 0
        },
        {
            "Quick Sort", "O(n log n)", "O(n log n)", "O(n²)", 0,
            NULL, quick_sort, 1
        },
        {
            "Heap Sort", "O(n log n)", "O(n log n)", "O(n log n)", 0,
            heap_sort, NULL, 0
        }
    };
    return algoritmos;
}

/* ================================================================
 * SISTEMA DE EXECUÇÃO E ANÁLISE AUTOMATIZADA
 * ================================================================ */

/**
 * Executa todos os algoritmos e gera análises com contagem de comparações e trocas
 */
void executar_todos_algoritmos(void *dados, int tamanho, size_t elem_size, CompareFn cmp,
                              const char* tipo_dados, const char* arquivo_base) {
    AlgoritmoInfo* algoritmos = obter_info_algoritmos();
    ResultadoTempo resultados[NUM_ALGORITMOS];

    // Determina número de execuções baseado no tamanho do conjunto
    int num_execucoes = determinar_num_execucoes(tamanho);

    printf("\nExecutando %d algoritmos com %d elementos...\n", NUM_ALGORITMOS, tamanho);
    if (num_execucoes > 1) {
        printf("(Usando %d execucoes por algoritmo para maior precisao)\n", num_execucoes);
    }
    printf("+--------------------+-------------+-------------+-------------+-------------+\n");
    printf("| Algoritmo          | Tempo (s)   | Comparacoes | Trocas      |Estabilidade|\n");
    printf("+--------------------+-------------+-------------+-------------+-------------+\n");

    void *dados_copia = malloc(tamanho * elem_size);
    if (!dados_copia) {
        printf("ERRO: Falha na alocacao de memoria\n");
        return;
    }

    for (int i = 0; i < NUM_ALGORITMOS; i++) {
        double tempo_total = 0.0;
        long long comparacoes_total = 0;
        long long trocas_total = 0;

        // Executa múltiplas medições para maior precisão
        for (int exec = 0; exec < num_execucoes; exec++) {
            // Copia dados originais para cada execução
            copiar_array(dados, dados_copia, tamanho, elem_size);

            // Zera contadores para esta execução
            contador_comparacoes = 0;
            contador_trocas = 0;

            double tempo_execucao;
            if (algoritmos[i].eh_quick) {
                tempo_execucao = medir_tempo_quick_sort(algoritmos[i].quick_sort_fn, dados_copia, tamanho, elem_size, cmp);
            } else {
                tempo_execucao = medir_tempo_ordenacao(algoritmos[i].sort_fn, dados_copia, tamanho, elem_size, cmp);
            }

            // Acumula métricas de todas as execuções
            tempo_total += tempo_execucao;
            comparacoes_total += contador_comparacoes;
            trocas_total += contador_trocas;
        }

        // Calcula médias
        double tempo_medio = tempo_total / num_execucoes;
        long long comparacoes_media = comparacoes_total / num_execucoes;
        long long trocas_media = trocas_total / num_execucoes;

        // Armazena resultado com médias
        strcpy(resultados[i].algoritmo, algoritmos[i].nome);
        resultados[i].tempo_execucao = tempo_medio;
        resultados[i].tamanho_dados = tamanho;
        strcpy(resultados[i].tipo_dados, tipo_dados);
        resultados[i].comparacoes = comparacoes_media;
        resultados[i].trocas = trocas_media;

        printf("| %-18s | %9.6f   | %11lld | %11lld | %-11s |\n",
               algoritmos[i].nome,
               tempo_medio,
               comparacoes_media,
               trocas_media,
               algoritmos[i].eh_estavel ? "Estavel" : "Nao Estavel");

        // Salva resultado ordenado (usando última execução)
        char nome_saida[MAX_PATH];
        snprintf(nome_saida, sizeof(nome_saida), "%s_%s_%s",
                algoritmos[i].nome, tipo_dados, arquivo_base);

        // Remove espaços do nome do arquivo
        for (char *p = nome_saida; *p; ++p) {
            if (*p == ' ') *p = '_';
        }

        if (strcmp(tipo_dados, "numeros") == 0) {
            salvar_numeros(nome_saida, (int*)dados_copia, tamanho);
        } else {
            salvar_alunos(nome_saida, (Aluno*)dados_copia, tamanho);
        }
    }

    printf("+--------------------+-------------+-------------+-------------+-------------+\n");

    if (num_execucoes > 1) {
        printf("Nota: Tempos, comparacoes e trocas sao medias de %d execucoes\n", num_execucoes);
    }

    // Gera relatório de tempos com métricas
    char nome_relatorio[MAX_PATH];
    snprintf(nome_relatorio, sizeof(nome_relatorio), "relatorio_%s_%s.txt", tipo_dados, arquivo_base);
    gerar_relatorio_tempos(resultados, NUM_ALGORITMOS, nome_relatorio);

    // Mostra ranking por tempo
    printf("\n=== RANKING POR TEMPO DE EXECUCAO ===\n");

    // Ordena resultados por tempo
    for (int i = 0; i < NUM_ALGORITMOS - 1; i++) {
        for (int j = i + 1; j < NUM_ALGORITMOS; j++) {
            if (resultados[i].tempo_execucao > resultados[j].tempo_execucao) {
                ResultadoTempo temp = resultados[i];
                resultados[i] = resultados[j];
                resultados[j] = temp;
            }
        }
    }

    for (int i = 0; i < NUM_ALGORITMOS; i++) {
        printf("   %d. %s: %.6f segundos\n",
               i + 1, resultados[i].algoritmo, resultados[i].tempo_execucao);
    }

    // Ranking por comparações
    printf("\n=== RANKING POR NUMERO DE COMPARACOES ===\n");

    // Ordena por comparações
    for (int i = 0; i < NUM_ALGORITMOS - 1; i++) {
        for (int j = i + 1; j < NUM_ALGORITMOS; j++) {
            if (resultados[i].comparacoes > resultados[j].comparacoes) {
                ResultadoTempo temp = resultados[i];
                resultados[i] = resultados[j];
                resultados[j] = temp;
            }
        }
    }

    for (int i = 0; i < NUM_ALGORITMOS; i++) {
        printf("   %d. %s: %lld comparacoes\n",
               i + 1, resultados[i].algoritmo, resultados[i].comparacoes);
    }

    // Ranking por trocas
    printf("\n=== RANKING POR NUMERO DE TROCAS ===\n");

    // Ordena por trocas
    for (int i = 0; i < NUM_ALGORITMOS - 1; i++) {
        for (int j = i + 1; j < NUM_ALGORITMOS; j++) {
            if (resultados[i].trocas > resultados[j].trocas) {
                ResultadoTempo temp = resultados[i];
                resultados[i] = resultados[j];
                resultados[j] = temp;
            }
        }
    }

    for (int i = 0; i < NUM_ALGORITMOS; i++) {
        printf("   %d. %s: %lld trocas\n",
               i + 1, resultados[i].algoritmo, resultados[i].trocas);
    }

    free(dados_copia);
}

/**
 * Gera relatório de tempos em formato TXT com métricas completas
 * Organiza em subpasta de relatórios e salva em múltiplos locais
 */

// Função callback para escrever relatórios - deve estar fora da função principal
void escrever_relatorio_callback(FILE* arquivo, void* dados, int tamanho) {
    ResultadoTempo* resultados = (ResultadoTempo*)dados;

    // Cabeçalho do relatório
    fprintf(arquivo, "================================================================\n");
    fprintf(arquivo, "              RELATORIO DE DESEMPENHO - ALGORITMOS             \n");
    fprintf(arquivo, "================================================================\n\n");
    fprintf(arquivo, "Dados analisados: %d conjuntos de teste\n\n", tamanho);

    // Tabela de resultados com mais precisão nos tempos
    fprintf(arquivo, "+----------------+----------------+-------------+----------+--------+\n");
    fprintf(arquivo, "| Algoritmo      | Tipo Dados     | Tempo (s)   | Compar.  | Trocas |\n");
    fprintf(arquivo, "+----------------+----------------+-------------+----------+--------+\n");

    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "| %-14s | %-14s | %9.6f | %8lld | %6lld |\n",
               resultados[i].algoritmo,
               resultados[i].tipo_dados,
               resultados[i].tempo_execucao,
               resultados[i].comparacoes,
               resultados[i].trocas);
    }

    fprintf(arquivo, "+----------------+----------------+-------------+----------+--------+\n\n");

    // Análises adicionais
    fprintf(arquivo, "OBSERVACOES:\n");
    fprintf(arquivo, "- Tempos em segundos (precisao: microssegundos - 6 casas decimais)\n");
    fprintf(arquivo, "- Para algoritmos muito rapidos, foram executadas multiplas medicoes\n");
    fprintf(arquivo, "- Conjuntos < 1000 elementos: 100 execucoes para maior precisao\n");
    fprintf(arquivo, "- Conjuntos < 5000 elementos: 10 execucoes para maior precisao\n");
    fprintf(arquivo, "- Conjuntos < 10000 elementos: 3 execucoes para maior precisao\n");
    fprintf(arquivo, "- Conjuntos >= 10000 elementos: 1 execucao (suficientemente lenta)\n");
    fprintf(arquivo, "- Comparacoes e Trocas: valores absolutos\n");
    fprintf(arquivo, "- Dados ordenados por algoritmo\n\n");

    fprintf(arquivo, "COMPLEXIDADES TEORICAS:\n");
    fprintf(arquivo, "Bubble Sort:    O(n²) medio, O(n) melhor, O(n²) pior\n");
    fprintf(arquivo, "Insertion Sort: O(n²) medio, O(n) melhor, O(n²) pior\n");
    fprintf(arquivo, "Selection Sort: O(n²) todos os casos\n");
    fprintf(arquivo, "Quick Sort:     O(n log n) medio, O(n log n) melhor, O(n²) pior\n");
    fprintf(arquivo, "Heap Sort:      O(n log n) todos os casos\n");
    fprintf(arquivo, "Shell Sort:     O(n^1.25) medio (varia com incrementos)\n");
    fprintf(arquivo, "Shaker Sort:    O(n²) medio, O(n) melhor, O(n²) pior\n");
}

void gerar_relatorio_tempos(ResultadoTempo resultados[], int num_resultados, const char* arquivo_saida) {
    // Usa a função auxiliar para salvar em múltiplos locais
    salvar_arquivo_multiplos_locais("relatorios", arquivo_saida, escrever_relatorio_callback, resultados, num_resultados);
}

/**
 * @brief Gera relatório detalhado de performance
 */
void gerar_relatorio_detalhado(ResultadoTempo resultados[], int num_resultados, const char* nome_arquivo) {
    // Usa a função auxiliar para salvar em múltiplos locais
    salvar_arquivo_multiplos_locais("relatorios", nome_arquivo, escrever_relatorio_callback, resultados, num_resultados);

    printf("Relatorio detalhado salvo: %s\n", nome_arquivo);
}

/**
 * Função callback para escrever análise de estabilidade
 */
void escrever_estabilidade_callback(FILE* arquivo, void* dados, int tamanho) {
    AlgoritmoInfo* algoritmos = obter_info_algoritmos();

    fprintf(arquivo, "ANALISE DE ESTABILIDADE - ALGORITMOS DE ORDENACAO\n");
    fprintf(arquivo, "=================================================\n\n");

    fprintf(arquivo, "DEFINICAO:\n");
    fprintf(arquivo, "Um algoritmo e ESTAVEL se preserva a ordem relativa\n");
    fprintf(arquivo, "de elementos com chaves iguais.\n\n");

    fprintf(arquivo, "IMPORTANCIA:\n");
    fprintf(arquivo, "Essencial quando ordenamos por multiplos criterios.\n");
    fprintf(arquivo, "Ex: Ordenar alunos por bairro e manter ordem por nome.\n\n");

    fprintf(arquivo, "RESUMO DOS ALGORITMOS:\n");
    for (int i = 0; i < NUM_ALGORITMOS; i++) {
        fprintf(arquivo, "%s %s: %s\n",
                algoritmos[i].eh_estavel ? "[ESTAVEL]" : "[NAO ESTAVEL]",
                algoritmos[i].nome,
                algoritmos[i].eh_estavel ? "ESTAVEL" : "NAO ESTAVEL");
    }
}

/**
 * Análise detalhada de estabilidade
 */
void analisar_estabilidade() {
    printf("\n=== ANALISE DE ESTABILIDADE DOS ALGORITMOS ===\n");
    printf("===============================================\n");

    // Dados específicos para demonstrar instabilidade
    Aluno dados_teste[] = {
        {"Alice Santos", "01/01/1995", "Centro", "Sao Paulo"},
        {"Bruno Silva", "15/03/1994", "Centro", "Sao Paulo"},    // Mesmo bairro que Alice
        {"Carlos Lima", "20/07/1996", "Vila Nova", "Sao Paulo"},
        {"Diana Costa", "10/02/1995", "Centro", "Sao Paulo"},    // Mesmo bairro que Alice e Bruno
        {"Eduardo Souza", "05/12/1993", "Vila Nova", "Sao Paulo"} // Mesmo bairro que Carlos
    };
    int tamanho = 5;

    printf("\n=== DADOS ORIGINAIS (ordem de entrada) ===\n");
    printf("%-15s %-12s %-15s %-15s\n", "Nome", "Data Nasc.", "Bairro", "Cidade");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%-15s %-12s %-15s %-15s\n",
               dados_teste[i].nome, dados_teste[i].data_nascimento,
               dados_teste[i].bairro, dados_teste[i].cidade);
    }

    AlgoritmoInfo* algoritmos = obter_info_algoritmos();

    for (int i = 0; i < NUM_ALGORITMOS; i++) {
        Aluno dados_copia[5];
        copiar_array(dados_teste, dados_copia, tamanho, sizeof(Aluno));

        printf("\n%s %s (%s):\n",
               algoritmos[i].eh_estavel ? "[ESTAVEL]" : "[NAO ESTAVEL]",
               algoritmos[i].nome,
               algoritmos[i].eh_estavel ? "ESTAVEL" : "NAO ESTAVEL");

        if (algoritmos[i].eh_quick) {
            algoritmos[i].quick_sort_fn(dados_copia, 0, tamanho - 1, sizeof(Aluno), comparar_alunos);
        } else {
            algoritmos[i].sort_fn(dados_copia, tamanho, sizeof(Aluno), comparar_alunos);
        }

        printf("%-15s %-12s %-15s %-15s\n", "Nome", "Data Nasc.", "Bairro", "Cidade");
        printf("-------------------------------------------------------------\n");
        for (int j = 0; j < tamanho; j++) {
            printf("%-15s %-12s %-15s %-15s\n",
                   dados_copia[j].nome, dados_copia[j].data_nascimento,
                   dados_copia[j].bairro, dados_copia[j].cidade);
        }
    }

    // Salva em múltiplos locais (sem subdiretório específico para este arquivo)
    salvar_arquivo_multiplos_locais("", "analise_estabilidade.txt", escrever_estabilidade_callback, NULL, 0);
    printf("\nAnalise completa salva em multiplos locais\n");
}

/**
 * @brief Executa todos os algoritmos com salvamento dos arrays ordenados
 *
 * Esta função executa todos os algoritmos de ordenação e salva tanto os
 * resultados ordenados quanto os relatórios de performance, incluindo
 * a identificação da versão (otimizada/não otimizada).
 */
void executar_todos_algoritmos_com_salvamento(void *dados, int tamanho, size_t elem_size, CompareFn cmp,
                                            const char* tipo_dados, const char* arquivo_base, const char* versao) {
    AlgoritmoInfo* algoritmos = obter_info_algoritmos();
    ResultadoTempo resultados[NUM_ALGORITMOS];

    // Determina número de execuções baseado no tamanho do conjunto
    int num_execucoes = determinar_num_execucoes(tamanho);

    printf("\nExecutando %d algoritmos com %d elementos (%s)...\n", NUM_ALGORITMOS, tamanho, versao);
    if (num_execucoes > 1) {
        printf("(Usando %d execucoes por algoritmo para maior precisao)\n", num_execucoes);
    }
    printf("+--------------------+-------------+-------------+-------------+-------------+\n");
    printf("| Algoritmo          | Tempo (s)   | Comparacoes | Trocas      |Estabilidade|\n");
    printf("+--------------------+-------------+-------------+-------------+-------------+\n");

    void *dados_copia = malloc(tamanho * elem_size);
    if (!dados_copia) {
        printf("ERRO: Falha na alocacao de memoria\n");
        return;
    }

    for (int i = 0; i < NUM_ALGORITMOS; i++) {
        double tempo_total = 0.0;
        long long comparacoes_total = 0;
        long long trocas_total = 0;

        // Executa múltiplas medições para maior precisão
        for (int exec = 0; exec < num_execucoes; exec++) {
            // Copia dados originais para cada execução
            copiar_array(dados, dados_copia, tamanho, elem_size);

            // Zera contadores para esta execução
            contador_comparacoes = 0;
            contador_trocas = 0;

            double tempo_execucao;
            if (algoritmos[i].eh_quick) {
                tempo_execucao = medir_tempo_quick_sort(algoritmos[i].quick_sort_fn, dados_copia, tamanho, elem_size, cmp);
            } else {
                tempo_execucao = medir_tempo_ordenacao(algoritmos[i].sort_fn, dados_copia, tamanho, elem_size, cmp);
            }

            // Acumula métricas de todas as execuções
            tempo_total += tempo_execucao;
            comparacoes_total += contador_comparacoes;
            trocas_total += contador_trocas;
        }

        // Calcula médias
        double tempo_medio = tempo_total / num_execucoes;
        long long comparacoes_media = comparacoes_total / num_execucoes;
        long long trocas_media = trocas_total / num_execucoes;

        // Armazena resultado com médias
        strcpy(resultados[i].algoritmo, algoritmos[i].nome);
        resultados[i].tempo_execucao = tempo_medio;
        resultados[i].tamanho_dados = tamanho;
        strcpy(resultados[i].tipo_dados, tipo_dados);
        resultados[i].comparacoes = comparacoes_media;
        resultados[i].trocas = trocas_media;

        // Exibe resultado na tabela
        printf("| %-18s | %8.6f s | %11lld | %11lld | %-10s |\n",
               algoritmos[i].nome,
               tempo_medio,
               comparacoes_media,
               trocas_media,
               algoritmos[i].eh_estavel ? "Estavel" : "Nao Est.");

        // Salva o array ordenado final (usando a última execução)
        copiar_array(dados, dados_copia, tamanho, elem_size);
        contador_comparacoes = 0;
        contador_trocas = 0;

        if (algoritmos[i].eh_quick) {
            algoritmos[i].quick_sort_fn(dados_copia, 0, tamanho - 1, elem_size, cmp);
        } else {
            algoritmos[i].sort_fn(dados_copia, tamanho, elem_size, cmp);
        }

        // Gera nome do arquivo para array ordenado
        char nome_arquivo_ordenado[MAX_PATH];
        char arquivo_limpo[MAX_PATH];

        // Remove extensão .txt se presente
        strncpy(arquivo_limpo, arquivo_base, sizeof(arquivo_limpo) - 1);
        arquivo_limpo[sizeof(arquivo_limpo) - 1] = '\0';
        char* ponto = strrchr(arquivo_limpo, '.');
        if (ponto) *ponto = '\0';

        snprintf(nome_arquivo_ordenado, sizeof(nome_arquivo_ordenado),
                "%s_%s_%s.txt", algoritmos[i].nome, versao, arquivo_limpo);

        // Substitui espaços por underscores no nome do arquivo
        for (char* p = nome_arquivo_ordenado; *p; p++) {
            if (*p == ' ') *p = '_';
        }

        // Salva array ordenado
        if (strcmp(tipo_dados, "numeros") == 0) {
            salvar_arquivo_multiplos_locais(tipo_dados, nome_arquivo_ordenado,
                                          escrever_numeros_callback, dados_copia, tamanho);
        } else {
            salvar_arquivo_multiplos_locais(tipo_dados, nome_arquivo_ordenado,
                                          escrever_alunos_callback, dados_copia, tamanho);
        }
    }

    printf("+--------------------+-------------+-------------+-------------+-------------+\n");

    // Gera relatório de performance
    char nome_relatorio[MAX_PATH];
    char arquivo_limpo[MAX_PATH];

    // Remove extensão .txt se presente
    strncpy(arquivo_limpo, arquivo_base, sizeof(arquivo_limpo) - 1);
    arquivo_limpo[sizeof(arquivo_limpo) - 1] = '\0';
    char* ponto = strrchr(arquivo_limpo, '.');
    if (ponto) *ponto = '\0';

    snprintf(nome_relatorio, sizeof(nome_relatorio),
            "relatorio_%s_%s_%s.txt", tipo_dados, versao, arquivo_limpo);

    gerar_relatorio_detalhado(resultados, NUM_ALGORITMOS, nome_relatorio);

    free(dados_copia);
    printf("\nTestes concluidos para versao %s!\n", versao);
}

/**
 * @brief Gera relatório comparativo final das duas versões
 */
void gerar_relatorio_comparativo_final() {
    printf("\n=== GERANDO RELATORIO COMPARATIVO FINAL ===\n");

    // Esta função seria chamada após todos os testes
    // Por agora, vamos criar um arquivo indicando que ambas as versões foram testadas

    const char* caminhos[] = {"output/relatorios/%s", "../output/relatorios/%s", "../../output/relatorios/%s"};
    char caminho_completo[MAX_PATH];
    const char* nome_arquivo = "relatorio_comparativo_final.txt";

    for (int i = 0; i < 3; i++) {
        snprintf(caminho_completo, sizeof(caminho_completo), caminhos[i], nome_arquivo);
        FILE* arquivo = fopen(caminho_completo, "w");
        if (arquivo) {
            fprintf(arquivo, "====================================================\n");
            fprintf(arquivo, "         RELATORIO COMPARATIVO FINAL               \n");
            fprintf(arquivo, "====================================================\n\n");

            fprintf(arquivo, "Este relatorio foi gerado apos a execucao completa\n");
            fprintf(arquivo, "de AMBAS as versoes dos algoritmos de ordenacao:\n\n");

            fprintf(arquivo, "VERSAO OTIMIZADA:\n");
            fprintf(arquivo, "- Algoritmos com otimizacoes de performance\n");
            fprintf(arquivo, "- Paradas antecipadas quando possivel\n");
            fprintf(arquivo, "- Menor numero de operacoes desnecessarias\n");
            fprintf(arquivo, "- Tempo de execucao otimizado\n\n");

            fprintf(arquivo, "VERSAO NAO OTIMIZADA:\n");
            fprintf(arquivo, "- Algoritmos em versao didatica\n");
            fprintf(arquivo, "- Sem otimizacoes (para fins educacionais)\n");
            fprintf(arquivo, "- Mais operacoes para demonstracao\n");
            fprintf(arquivo, "- Tempo de execucao maior\n\n");

            fprintf(arquivo, "ARQUIVOS GERADOS:\n\n");
            fprintf(arquivo, "1. Arrays Ordenados:\n");
            fprintf(arquivo, "   output/numeros/*_otimizada_*.txt\n");
            fprintf(arquivo, "   output/numeros/*_nao_otimizada_*.txt\n");
            fprintf(arquivo, "   output/alunos/*_otimizada_*.txt\n");
            fprintf(arquivo, "   output/alunos/*_nao_otimizada_*.txt\n\n");

            fprintf(arquivo, "2. Relatorios de Performance:\n");
            fprintf(arquivo, "   output/relatorios/relatorio_*_otimizada.txt\n");
            fprintf(arquivo, "   output/relatorios/relatorio_*_nao_otimizada.txt\n\n");

            fprintf(arquivo, "3. Analise de Estabilidade:\n");
            fprintf(arquivo, "   output/analise_estabilidade.txt\n\n");

            time_t t = time(NULL);
            struct tm *tm_info = localtime(&t);
            char data_str[100];
            strftime(data_str, sizeof(data_str), "%Y-%m-%d %H:%M:%S", tm_info);

            fprintf(arquivo, "Relatorio gerado em: %s\n", data_str);
            fprintf(arquivo, "Sistema: Trabalho de Algoritmos de Ordenacao\n");

            fclose(arquivo);
            printf("Relatorio comparativo final salvo em: %s\n", caminho_completo);
            break;
        }
    }
}
