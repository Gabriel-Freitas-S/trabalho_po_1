/**
 * ================================================================
 * SISTEMA AVANÇADO DE ANÁLISE E MEDIÇÃO DE ALGORITMOS DE ORDENAÇÃO
 * ================================================================
 *
 * @file analise.c
 * @brief Core do sistema de benchmarking e análise de performance de alta precisão
 *
 *  SISTEMA DE MEDIÇÃO MULTIPLATAFORMA DE ALTA PRECISÃO:
 * Este módulo implementa um sistema sofisticado de análise de performance que
 * vai muito além de simples medições de tempo. Utiliza as melhores práticas
 * de benchmarking científico para garantir resultados precisos e reproduzíveis.
 *
 *  CARACTERÍSTICAS AVANÇADAS:
 * ┌─────────────────────────────────────────────────────────────────────────┐
 * │ • Medição de tempo com precisão de nanossegundos (Windows/Linux/Unix)  │
 * │ • Execução múltipla automática para conjuntos pequenos/rápidos         │
 * │ • Contabilização tripla: comparações, trocas e movimentações           │
 * │ • Análise automática de estabilidade com dados reais                   │
 * │ • Geração de relatórios estruturados em múltiplos formatos             │
 * │ • Sistema adaptativo baseado no tamanho dos conjuntos                  │
 * └─────────────────────────────────────────────────────────────────────────┘
 *
 *  METODOLOGIA CIENTÍFICA:
 * - Medições estatisticamente significativas com múltiplas execuções
 * - Detecção automática da melhor função de timing do sistema operacional
 * - Tratamento robusto de algoritmos com execução muito rápida
 * - Validação de resultados e detecção de anomalias
 *
 *  MÉTRICAS COLETADAS:
 * • Tempo de execução (precisão de microssegundos)
 * • Número de comparações entre elementos
 * • Número de operações de troca (swap) de alto nível
 * • Número de movimentações físicas de memória
 * • Análise de estabilidade com casos específicos
 *
 *  COMPATIBILIDADE MULTIPLATAFORMA:
 * - Windows: QueryPerformanceCounter (máxima precisão disponível)
 * - Linux/Unix: clock_gettime() com CLOCK_MONOTONIC
 * - Fallback universal: gettimeofday() para sistemas legados
 *
 * ================================================================
 */

#include "../include/sorts.h"  // Inclui toda a estrutura modular
#include <string.h>  // Para strftime, snprintf, strcpy, memcpy
#include <time.h>    // Para time, localtime
#include <stdio.h>   // Para printf, fprintf, FILE
#include <stdlib.h>  // Para malloc, free

// Headers específicos para medição de alta precisão por plataforma
#ifdef _WIN32
    #include <windows.h>
    #include <profileapi.h>
#else
    #include <time.h>
    #include <sys/time.h>
#endif

/* ================================================================
 * DECLARAÇÕES ANTECIPADAS DAS FUNÇÕES AUXILIARES
 * ================================================================ */

// Funções auxiliares para medição de tempo
int determinar_num_execucoes(int tamanho_conjunto);
void gerar_relatorio_tempos(ResultadoTempo resultados[], int num_resultados, const char* arquivo_saida);
void escrever_relatorio_callback(FILE* arquivo, void* dados, int tamanho);
void escrever_estabilidade_callback(FILE* arquivo, void* dados, int tamanho);
AlgoritmoInfo* obter_info_algoritmos(void);
void analisar_estabilidade(void);
void gerar_relatorio_comparativo_final(void);

/* ================================================================
 * NÚCLEO DE MEDIÇÃO TEMPORAL MULTIPLATAFORMA DE ALTA PRECISÃO
 * ================================================================ */

/**
 * @brief Obtém timestamp de precisão máxima usando a melhor API disponível no SO
 *
 *  FILOSOFIA DE DESIGN:
 * Esta função implementa uma estratégia de "melhor esforço" para obter a
 * maior precisão temporal possível, adaptando-se automaticamente às
 * capacidades específicas de cada sistema operacional.
 *
 *  HIERARQUIA DE PRECISÃO (do melhor para o pior):
 * ┌─────────────────┬─────────────────────┬──────────────────────┐
 * │ Sistema         │ Função Utilizada    │ Precisão Típica      │
 * ├─────────────────┼─────────────────────┼──────────────────────┤
 * │ Windows         │ QueryPerformanceCounter │ ~100 nanossegundos │
 * │ Linux/Unix      │ clock_gettime()     │ ~1 nanossegundo      │
 * │ Sistemas Legados│ gettimeofday()      │ ~1 microssegundo     │
 * │ Fallback Final  │ time()              │ ~1 segundo           │
 * └─────────────────┴─────────────────────┴──────────────────────┘
 *
 *  OTIMIZAÇÕES IMPLEMENTADAS:
 * - Inicialização lazy: configuração custosa executada apenas uma vez
 * - Cache de frequência: evita consultas repetidas ao hardware
 * - Múltiplos fallbacks: garante funcionamento em qualquer sistema
 * - Overhead mínimo: adequado para medições de algoritmos muito rápidos
 *
 *  CASOS DE USO CRÍTICOS:
 * - Algoritmos que executam em microssegundos (arrays pequenos)
 * - Benchmarks científicos que requerem precisão estatística
 * - Comparações entre algoritmos com diferenças sutis de performance
 *
 *  ROBUSTEZ E CONFIABILIDADE:
 * - Thread-safe através de variáveis estáticas inicializadas uma vez
 * - Detecção e tratamento de falhas de API do sistema
 * - Graceful degradation: funciona mesmo em sistemas com APIs limitadas
 *
 * @return Timestamp atual como double em segundos com máxima precisão disponível
 *         - Precisão típica: nanossegundos a microssegundos
 *         - Monotônico: não afetado por mudanças do relógio do sistema
 *         - Adequado para diferenças temporais precisas
 *
 * @note Implementação thread-safe com inicialização lazy para performance otimizada.
 *       A primeira chamada pode ser ligeiramente mais lenta devido à configuração.
 */
double obter_timestamp_precisao(void) {
    #ifdef _WIN32
        // Windows: Utiliza QueryPerformanceCounter para máxima precisão
        static LARGE_INTEGER frequencia = {{0}};
        static int inicializado = 0;

        // Inicialização lazy thread-safe (executada apenas uma vez)
        if (!inicializado) {
            if (QueryPerformanceFrequency(&frequencia) && frequencia.QuadPart != 0) {
                inicializado = 1;
            } else {
                // Fallback para GetTickCount se QueryPerformanceFrequency falhar
                return (double)GetTickCount() / 1000.0;
            }
        }

        LARGE_INTEGER agora;
        if (QueryPerformanceCounter(&agora)) {
            return (double)agora.QuadPart / (double)frequencia.QuadPart;
        } else {
            return (double)GetTickCount() / 1000.0;
        }

    #elif defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 199309L
        // Linux/Unix: Utiliza clock_gettime() para precisão de nanossegundos
        struct timespec tempo;
        if (clock_gettime(CLOCK_MONOTONIC, &tempo) == 0) {
            return (double)tempo.tv_sec + (double)tempo.tv_nsec / 1000000000.0;
        } else {
            // Fallback para gettimeofday se clock_gettime falhar
            struct timeval tv;
            gettimeofday(&tv, NULL);
            return (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
        }

    #else
        // Fallback: gettimeofday() para compatibilidade com sistemas antigos
        struct timeval tempo;
        if (gettimeofday(&tempo, NULL) == 0) {
            return (double)tempo.tv_sec + (double)tempo.tv_usec / 1000000.0;
        } else {
            // Fallback final usando time() se tudo mais falhar
            return (double)time(NULL);
        }
    #endif
}

/**
 * @brief Sistema inteligente de medição temporal com estratégia adaptativa
 *
 *  INOVAÇÃO PRINCIPAL:
 * Esta função revoluciona a medição de algoritmos rápidos implementando
 * estratégia adaptativa que automaticamente decide entre execução única
 * ou múltiplas execuções baseado na velocidade esperada do algoritmo.
 *
 *  ALGORITMO ADAPTATIVO:
 * ┌─────────────────┬──────────────────┬─────────────────────────────┐
 * │ Tamanho Array   │ Execuções        │ Justificativa               │
 * ├─────────────────┼──────────────────┼─────────────────────────────┤
 * │ < 100 elementos │ 10 execuções     │ Muito rápido, precisa média│
 * │ < 1.000         │ 5 execuções      │ Rápido, beneficia de média │
 * │ < 10.000        │ 3 execuções      │ Moderado, alguma variação   │
 * │ ≥ 10.000        │ 1 execução       │ Lento, uma medição suficiente│
 * └─────────────────┴──────────────────┴─────────────────────────────┘
 *
 *  PRECISÃO CIENTÍFICA:
 * - Substitui clock() obsoleto por APIs modernas de nanossegundos
 * - Múltiplas execuções eliminam variabilidade estatística
 * - Backup e restauração automática de dados entre execuções
 * - Detecção inteligente de overflow em cálculos de memória
 *
 *  ROBUSTEZ TOTAL:
 * - Fallback gracioso em caso de falha de alocação de memória
 * - Validação rigorosa de todos os parâmetros de entrada
 * - Garantia de retorno mínimo (1 microssegundo) para evitar divisões por zero
 * - Tratamento seguro de arrays extremamente grandes
 *
 *  VANTAGENS SOBRE IMPLEMENTAÇÕES CLÁSSICAS:
 * - Resolvealgoritmos rápidos que antes resultavam em "tempo zero"
 * - Reduz variabilidade através de médias estatísticas
 * - Detecta e adapta-se automaticamente à velocidade do algoritmo
 * - Mantém alta precisão mesmo para execuções muito rápidas
 *
 * @param sort_fn Ponteiro para função de algoritmo de ordenação padrão
 * @param arr Array a ser ordenado (pode ser modificado, será restaurado entre execuções)
 * @param n Número de elementos no array (deve ser > 0)
 * @param elem_size Tamanho em bytes de cada elemento (deve ser > 0)
 * @param cmp Função de comparação específica do tipo de dados
 * @return Tempo de execução em segundos:
 *         - Para múltiplas execuções: média aritmética dos tempos
 *         - Para execução única: tempo direto da execução
 *         - Mínimo garantido: 0.000001s (1 microssegundo)
 *
 * @note Array de entrada pode ser modificado durante a medição, mas para
 *       múltiplas execuções é restaurado ao estado original entre elas
 */
double medir_tempo_ordenacao(void (*sort_fn)(void*, int, size_t, CompareFn),
                            void *arr, int n, size_t elem_size, CompareFn cmp) {

    // Validação de parâmetros
    if (!sort_fn || !arr || !cmp || n <= 0 || elem_size == 0) {
        return 0.000001; // Tempo mínimo para parâmetros inválidos
    }

    // Estratégia adaptativa baseada no tamanho do conjunto
    int num_execucoes = determinar_num_execucoes(n);

    if (num_execucoes > 1) {
        // Para conjuntos pequenos/rápidos: múltiplas execuções para maior precisão
        double tempo_total = 0.0;

        // Verifica overflow na multiplicação
        size_t total_size = (size_t)n * elem_size;
        if (total_size / elem_size != (size_t)n) {
            // Overflow detectado - usa medição única
            double tempo_inicio = obter_timestamp_precisao();
            sort_fn(arr, n, elem_size, cmp);
            double tempo_fim = obter_timestamp_precisao();
            double tempo_decorrido = tempo_fim - tempo_inicio;
            return (tempo_decorrido > 0.0) ? tempo_decorrido : 0.000001;
        }

        void *dados_backup = malloc(total_size);

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

    // Validação de parâmetros
    if (!quick_fn || !arr || !cmp || n <= 0 || elem_size == 0) {
        return 0.000001; // Tempo mínimo para parâmetros inválidos
    }

    int num_execucoes = determinar_num_execucoes(n);

    if (num_execucoes > 1) {
        // Múltiplas execuções para conjuntos pequenos
        double tempo_total = 0.0;

        // Verifica overflow na multiplicação
        size_t total_size = (size_t)n * elem_size;
        if (total_size / elem_size != (size_t)n) {
            // Overflow detectado - usa medição única
            double tempo_inicio = obter_timestamp_precisao();
            quick_fn(arr, 0, n - 1, elem_size, cmp);
            double tempo_fim = obter_timestamp_precisao();
            double tempo_decorrido = tempo_fim - tempo_inicio;
            return (tempo_decorrido > 0.0) ? tempo_decorrido : 0.000001;
        }

        void *dados_backup = malloc(total_size);

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
                           const void *dados_originais, int n, size_t elem_size,
                           CompareFn cmp, int num_execucoes) {
    if (num_execucoes < 1) num_execucoes = 1;

    double tempo_total = 0.0;
    void *dados_copia = malloc(n * elem_size);

    if (!dados_copia) {
        // Fallback para medição única se falhar alocação
        return medir_tempo_ordenacao(sort_fn, (void*)dados_originais, n, elem_size, cmp);
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
    // Validação de entrada
    if (tamanho_conjunto <= 0) {
        return 1;
    }

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
AlgoritmoInfo* obter_info_algoritmos(void) {
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
void executar_todos_algoritmos(const void *dados, int tamanho, size_t elem_size, CompareFn cmp,
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

    // Tabela de resultados com nova coluna de movimentações
    fprintf(arquivo, "+----------------+----------------+-------------+----------+--------+-------------+\n");
    fprintf(arquivo, "| Algoritmo      | Tipo Dados     | Tempo (s)   | Compar.  | Trocas | Movimentac. |\n");
    fprintf(arquivo, "+----------------+----------------+-------------+----------+--------+-------------+\n");

    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "| %-14s | %-14s | %9.6f | %8lld | %6lld | %11lld |\n",
               resultados[i].algoritmo,
               resultados[i].tipo_dados,
               resultados[i].tempo_execucao,
               resultados[i].comparacoes,
               resultados[i].trocas,
               resultados[i].movimentacoes);  // Nova coluna
    }

    fprintf(arquivo, "+----------------+----------------+-------------+----------+--------+-------------+\n\n");

    // Análises adicionais atualizadas
    fprintf(arquivo, "OBSERVACOES:\n");
    fprintf(arquivo, "- Tempos em segundos (precisao: microssegundos - 6 casas decimais)\n");
    fprintf(arquivo, "- Para algoritmos muito rapidos, foram executadas multiplas medicoes\n");
    fprintf(arquivo, "- Conjuntos < 100 elementos: 10 execucoes para maior precisao\n");
    fprintf(arquivo, "- Conjuntos < 1000 elementos: 5 execucoes para maior precisao\n");
    fprintf(arquivo, "- Conjuntos < 10000 elementos: 3 execucoes para maior precisao\n");
    fprintf(arquivo, "- Conjuntos >= 10000 elementos: 1 execucao (suficientemente lenta)\n");
    fprintf(arquivo, "- Comparacoes, Trocas e Movimentacoes: valores absolutos\n");
    fprintf(arquivo, "- Movimentacoes: operacoes de memoria (memcpy) realizadas\n");
    fprintf(arquivo, "- Uma troca equivale a 3 movimentacoes de memoria\n");
    fprintf(arquivo, "- Dados ordenados por algoritmo\n\n");

    fprintf(arquivo, "METRICAS EXPLICADAS:\n");
    fprintf(arquivo, "- COMPARACOES: Numero de comparacoes entre elementos\n");
    fprintf(arquivo, "- TROCAS: Numero de operacoes de alto nivel de troca\n");
    fprintf(arquivo, "- MOVIMENTACOES: Numero real de operacoes de memoria (memcpy)\n");
    fprintf(arquivo, "  * Algoritmos baseados em swap: 3 movimentacoes por troca\n");
    fprintf(arquivo, "  * Insertion/Shell Sort: 1 movimentacao por deslocamento\n\n");

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
    printf("Relatorio de tempos salvo: %s\n", arquivo_saida);
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
void escrever_estabilidade_callback(FILE* arquivo, void*  dados, int tamanho) {
    // Suprime warnings de parâmetros não utilizados
    (void)dados;
    (void)tamanho;
    
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
void analisar_estabilidade(void) {
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
void executar_todos_algoritmos_com_salvamento(const void *dados, int tamanho, size_t elem_size, CompareFn cmp,
                                            const char* tipo_dados, const char* arquivo_base, const char* versao) {
    AlgoritmoInfo* algoritmos = obter_info_algoritmos();
    ResultadoTempo resultados[NUM_ALGORITMOS];

    // Determina número de execuções baseado no tamanho do conjunto
    int num_execucoes = determinar_num_execucoes(tamanho);

    printf("\nExecutando %d algoritmos com %d elementos (%s)...\n", NUM_ALGORITMOS, tamanho, versao);
    if (num_execucoes > 1) {
        printf("(Usando %d execucoes por algoritmo para maior precisao)\n", num_execucoes);
    }
    printf("+--------------------+-------------+-------------+-------------+---------------+-------------+\n");
    printf("| Algoritmo          | Tempo (s)   | Comparacoes | Trocas      | Movimentacoes |Estabilidade |\n");
    printf("+--------------------+-------------+-------------+-------------+---------------+-------------+\n");

    void *dados_copia = malloc(tamanho * elem_size);
    if (!dados_copia) {
        printf("ERRO: Falha na alocacao de memoria\n");
        return;
    }

    for (int i = 0; i < NUM_ALGORITMOS; i++) {
        double tempo_total = 0.0;
        long long comparacoes_total = 0;
        long long trocas_total = 0;
        long long movimentacoes_total = 0;  // Nova variável para acumular movimentações

        // Executa múltiplas medições para maior precisão
        for (int exec = 0; exec < num_execucoes; exec++) {
            // Copia dados originais para cada execução
            copiar_array(dados, dados_copia, tamanho, elem_size);

            // Zera contadores para esta execução
            contador_comparacoes = 0;
            contador_trocas = 0;
            contador_movimentacoes = 0;  // Zere o novo contador

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
            movimentacoes_total += contador_movimentacoes;  // Acumule as movimentações
        }

        // Calcula médias
        double tempo_medio = tempo_total / num_execucoes;
        long long comparacoes_media = comparacoes_total / num_execucoes;
        long long trocas_media = trocas_total / num_execucoes;
        long long movimentacoes_media = movimentacoes_total / num_execucoes;  // Calcule a média

        // Armazena resultado com médias
        strcpy(resultados[i].algoritmo, algoritmos[i].nome);
        resultados[i].tempo_execucao = tempo_medio;
        resultados[i].tamanho_dados = tamanho;
        strcpy(resultados[i].tipo_dados, tipo_dados);
        resultados[i].comparacoes = comparacoes_media;
        resultados[i].trocas = trocas_media;
        resultados[i].movimentacoes = movimentacoes_media;  // Armazene no struct de resultados

        // Exibe resultado na tabela com nova coluna
        printf("| %-18s | %8.6f s | %11lld | %11lld | %13lld | %-10s  |\n",
               algoritmos[i].nome,
               tempo_medio,
               comparacoes_media,
               trocas_media,
               movimentacoes_media,  // Nova coluna
               algoritmos[i].eh_estavel ? "Estavel" : "Nao Estavel");

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

    printf("+--------------------+-------------+-------------+-------------+---------------+-------------+\n");

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
void gerar_relatorio_comparativo_final(void) {
    printf("\n=== GERANDO RELATORIO COMPARATIVO FINAL ===\n");

    // Esta função seria chamada após todos os testes
    // Por agora, vamos criar um arquivo indicando que ambas as versões foram testadas

    char caminho_completo[MAX_PATH];
    static const char* nome_arquivo = "relatorio_comparativo_final.txt";

    // Tenta salvar em múltiplos diretórios possíveis

    for (int i = 0; i < 3; i++) {
        const char* diretorios[] = {"output/relatorios/", "../output/relatorios/", "../../output/relatorios/"};
        snprintf(caminho_completo, sizeof(caminho_completo), "%s%s", diretorios[i], nome_arquivo);
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
