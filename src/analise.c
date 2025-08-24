/**
 * ================================================================
 * TRABALHO DE ALGORITMOS DE ORDENAÇÃO - MÓDULO DE ANÁLISE
 * ================================================================
 *
 * @file analise.c
 * @brief Sistema de medição, análise e geração de relatórios de algoritmos
 * @version 2.1
 * @date 2025-08-23
 * @author Sistema de Análise de Algoritmos
 *
 * Este módulo implementa toda a infraestrutura de análise de performance
 * dos algoritmos de ordenação. Inclui medição precisa de tempo, contagem
 * de operações, análise de estabilidade e geração de relatórios detalhados.
 *
 * NOVA VERSÃO 2.1: Medição de tempo de alta precisão
 * - Uso de clock_gettime() com precisão de nanossegundos
 * - Medição robusta para algoritmos muito rápidos
 * - Fallback para clock() em sistemas não compatíveis
 * - Detecção automática da melhor função de timing disponível
 *
 * Funcionalidades principais:
 * - Medição precisa de tempo de execução usando clock_gettime()
 * - Execução automatizada de todos os algoritmos em batches
 * - Geração de relatórios comparativos em formato texto
 * - Análise detalhada de estabilidade com casos de teste
 * - Rankings automáticos por diferentes métricas
 * - Salvamento organizado de resultados por categoria
 *
 * Métricas analisadas:
 * - Tempo de execução (precisão de nanossegundos)
 * - Número de comparações realizadas
 * - Número de trocas/movimentações
 * - Análise de estabilidade com dados reais
 * - Eficiência relativa (operações por elemento)
 *
 * ================================================================
 */

#include "../include/sorts.h"

// Incluir headers para medição de alta precisão
#ifdef _WIN32
    #include <windows.h>
    #include <profileapi.h>
#else
    #include <time.h>
    #include <sys/time.h>
#endif

/* ================================================================
 * SISTEMA DE MEDIÇÃO DE TEMPO DE ALTA PRECISÃO
 * ================================================================ */

/**
 * @brief Obtém timestamp de alta precisão multiplataforma
 *
 * Utiliza a melhor função de timing disponível no sistema:
 * - Windows: QueryPerformanceCounter (precisão de microssegundos)
 * - Linux/Unix: clock_gettime() com CLOCK_MONOTONIC (nanossegundos)
 * - Fallback: gettimeofday() (microssegundos)
 *
 * @return Tempo em segundos com precisão de nanossegundos (double)
 */
double obter_timestamp_precisao() {
    #ifdef _WIN32
        // Windows: Usa QueryPerformanceCounter para máxima precisão
        static LARGE_INTEGER frequencia;
        static int inicializado = 0;

        if (!inicializado) {
            QueryPerformanceFrequency(&frequencia);
            inicializado = 1;
        }

        LARGE_INTEGER agora;
        QueryPerformanceCounter(&agora);

        return (double)agora.QuadPart / (double)frequencia.QuadPart;

    #elif defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 199309L
        // Linux/Unix: Usa clock_gettime() para precisão de nanossegundos
        struct timespec tempo;
        clock_gettime(CLOCK_MONOTONIC, &tempo);

        return (double)tempo.tv_sec + (double)tempo.tv_nsec / 1000000000.0;

    #else
        // Fallback: gettimeofday() para compatibilidade
        struct timeval tempo;
        gettimeofday(&tempo, NULL);

        return (double)tempo.tv_sec + (double)tempo.tv_usec / 1000000.0;
    #endif
}

/**
 * @brief Mede tempo de execução com precisão de nanossegundos
 *
 * Nova implementação de alta precisão que substitui clock() por
 * funções de timing modernas. Capaz de medir algoritmos muito rápidos
 * que anteriormente resultavam em tempo zero.
 *
 * Características:
 * - Precisão até nanossegundos (dependente do sistema)
 * - Medição monotônica (não afetada por mudanças de horário)
 * - Compatibilidade multiplataforma (Windows, Linux, macOS)
 * - Overhead mínimo (duas chamadas de sistema)
 *
 * @param sort_fn Ponteiro para a função do algoritmo de ordenação
 * @param arr Ponteiro para o array a ser ordenado (será modificado)
 * @param n Número de elementos no array
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação entre elementos
 * @return Tempo de execução em segundos (precisão de nanossegundos)
 */
double medir_tempo_ordenacao(void (*sort_fn)(void*, int, size_t, CompareFn),
                            void *arr, int n, size_t elem_size, CompareFn cmp) {
    // Timestamp inicial com máxima precisão
    double tempo_inicio = obter_timestamp_precisao();

    // Execução do algoritmo de ordenação
    sort_fn(arr, n, elem_size, cmp);

    // Timestamp final
    double tempo_fim = obter_timestamp_precisao();

    // Cálculo do tempo decorrido
    double tempo_decorrido = tempo_fim - tempo_inicio;

    // Garantia de que o tempo nunca seja zero (mínimo 1 nanossegundo)
    return (tempo_decorrido > 0.0) ? tempo_decorrido : 0.000000001;
}

/**
 * @brief Mede tempo de execução do Quick Sort com alta precisão
 *
 * Versão especializada da medição de alta precisão para o Quick Sort,
 * que requer parâmetros diferentes devido à sua interface recursiva.
 *
 * @param quick_fn Ponteiro para a função Quick Sort
 * @param arr Ponteiro para o array a ser ordenado (será modificado)
 * @param n Número de elementos no array
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação entre elementos
 * @return Tempo de execução em segundos (precisão de nanossegundos)
 */
double medir_tempo_quick_sort(void (*quick_fn)(void*, int, int, size_t, CompareFn),
                            void *arr, int n, size_t elem_size, CompareFn cmp) {
    // Timestamp inicial com máxima precisão
    double tempo_inicio = obter_timestamp_precisao();

    // Quick Sort sempre ordena do índice 0 até n-1
    quick_fn(arr, 0, n - 1, elem_size, cmp);

    // Timestamp final
    double tempo_fim = obter_timestamp_precisao();

    // Cálculo do tempo decorrido
    double tempo_decorrido = tempo_fim - tempo_inicio;

    // Garantia de que o tempo nunca seja zero (mínimo 1 nanossegundo)
    return (tempo_decorrido > 0.0) ? tempo_decorrido : 0.000000001;
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
 * Organiza em subpasta de relatórios
 */
void gerar_relatorio_tempos(ResultadoTempo resultados[], int num_resultados, const char* arquivo_saida) {
    // Possíveis caminhos para salvar o arquivo na pasta de relatórios
    const char* caminhos[] = {
        "output/relatorios/%s",
        "../output/relatorios/%s",
        "../../output/relatorios/%s"
    };

    char caminho_completo[MAX_PATH];
    FILE* arquivo = NULL;
    int caminho_usado = -1;

    // Tenta cada caminho até conseguir criar o arquivo
    for (int i = 0; i < 3; i++) {
        snprintf(caminho_completo, sizeof(caminho_completo), caminhos[i], arquivo_saida);
        arquivo = fopen(caminho_completo, "w");
        if (arquivo) {
            caminho_usado = i;
            printf("Relatorio salvo em: %s\n", caminho_completo);
            break;
        }
    }

    if (!arquivo) {
        printf("ERRO: Nao foi possivel criar relatorio %s\n", arquivo_saida);
        printf("Tentou salvar em:\n");
        for (int i = 0; i < 3; i++) {
            snprintf(caminho_completo, sizeof(caminho_completo), caminhos[i], arquivo_saida);
            printf("  - %s\n", caminho_completo);
        }
        return;
    }

    // Cabeçalho do relatório TXT
    fprintf(arquivo, "RELATORIO COMPLETO DE ANALISE - ALGORITMOS DE ORDENACAO\n");
    fprintf(arquivo, "=======================================================\n\n");

    fprintf(arquivo, "Data de Execucao: %s", __DATE__);
    fprintf(arquivo, "\nTipo de Dados: %s\n", resultados[0].tipo_dados);
    fprintf(arquivo, "Tamanho do Conjunto: %d elementos\n\n", resultados[0].tamanho_dados);

    AlgoritmoInfo* info_algoritmos = obter_info_algoritmos();

    // Relatório detalhado por algoritmo
    fprintf(arquivo, "METRICAS DETALHADAS POR ALGORITMO\n");
    fprintf(arquivo, "=================================\n\n");

    for (int i = 0; i < num_resultados; i++) {
        // Encontra informação do algoritmo
        const char* complexidade = "N/A";
        int eh_estavel = 0;
        for (int j = 0; j < NUM_ALGORITMOS; j++) {
            if (strcmp(resultados[i].algoritmo, info_algoritmos[j].nome) == 0) {
                complexidade = info_algoritmos[j].complexidade_media;
                eh_estavel = info_algoritmos[j].eh_estavel;
                break;
            }
        }

        fprintf(arquivo, "Algoritmo: %s\n", resultados[i].algoritmo);
        fprintf(arquivo, "Complexidade Media: %s\n", complexidade);
        fprintf(arquivo, "Estabilidade: %s\n", eh_estavel ? "ESTAVEL" : "NAO ESTAVEL");
        fprintf(arquivo, "Tempo de Execucao: %.6f segundos\n", resultados[i].tempo_execucao);
        fprintf(arquivo, "Numero de Comparacoes: %lld\n", resultados[i].comparacoes);
        fprintf(arquivo, "Numero de Trocas: %lld\n", resultados[i].trocas);

        // Calcula eficiência relativa
        if (resultados[i].tamanho_dados > 0) {
            double comp_por_elemento = (double)resultados[i].comparacoes / resultados[i].tamanho_dados;
            double trocas_por_elemento = (double)resultados[i].trocas / resultados[i].tamanho_dados;
            fprintf(arquivo, "Comparacoes por Elemento: %.2f\n", comp_por_elemento);
            fprintf(arquivo, "Trocas por Elemento: %.2f\n", trocas_por_elemento);
        }

        fprintf(arquivo, "---------------------------------------------------\n\n");
    }

    // Análise comparativa
    fprintf(arquivo, "ANALISE COMPARATIVA\n");
    fprintf(arquivo, "===================\n\n");

    // Encontrar melhores e piores em cada categoria
    int melhor_tempo = 0, pior_tempo = 0;
    int melhor_comp = 0, pior_comp = 0;
    int melhor_trocas = 0, pior_trocas = 0;

    for (int i = 1; i < num_resultados; i++) {
        if (resultados[i].tempo_execucao < resultados[melhor_tempo].tempo_execucao)
            melhor_tempo = i;
        if (resultados[i].tempo_execucao > resultados[pior_tempo].tempo_execucao)
            pior_tempo = i;

        if (resultados[i].comparacoes < resultados[melhor_comp].comparacoes)
            melhor_comp = i;
        if (resultados[i].comparacoes > resultados[pior_comp].comparacoes)
            pior_comp = i;

        if (resultados[i].trocas < resultados[melhor_trocas].trocas)
            melhor_trocas = i;
        if (resultados[i].trocas > resultados[pior_trocas].trocas)
            pior_trocas = i;
    }

    fprintf(arquivo, "MELHOR TEMPO: %s (%.6f segundos)\n",
            resultados[melhor_tempo].algoritmo, resultados[melhor_tempo].tempo_execucao);
    fprintf(arquivo, "PIOR TEMPO: %s (%.6f segundos)\n\n",
            resultados[pior_tempo].algoritmo, resultados[pior_tempo].tempo_execucao);

    fprintf(arquivo, "MENOS COMPARACOES: %s (%lld comparacoes)\n",
            resultados[melhor_comp].algoritmo, resultados[melhor_comp].comparacoes);
    fprintf(arquivo, "MAIS COMPARACOES: %s (%lld comparacoes)\n\n",
            resultados[pior_comp].algoritmo, resultados[pior_comp].comparacoes);

    fprintf(arquivo, "MENOS TROCAS: %s (%lld trocas)\n",
            resultados[melhor_trocas].algoritmo, resultados[melhor_trocas].trocas);
    fprintf(arquivo, "MAIS TROCAS: %s (%lld trocas)\n\n",
            resultados[pior_trocas].algoritmo, resultados[pior_trocas].trocas);

    // Algoritmos estáveis
    fprintf(arquivo, "ALGORITMOS ESTAVEIS:\n");
    for (int i = 0; i < num_resultados; i++) {
        for (int j = 0; j < NUM_ALGORITMOS; j++) {
            if (strcmp(resultados[i].algoritmo, info_algoritmos[j].nome) == 0 &&
                info_algoritmos[j].eh_estavel) {
                fprintf(arquivo, "- %s\n", resultados[i].algoritmo);
                break;
            }
        }
    }

    fprintf(arquivo, "\nALGORITMOS NAO ESTAVEIS:\n");
    for (int i = 0; i < num_resultados; i++) {
        for (int j = 0; j < NUM_ALGORITMOS; j++) {
            if (strcmp(resultados[i].algoritmo, info_algoritmos[j].nome) == 0 &&
                !info_algoritmos[j].eh_estavel) {
                fprintf(arquivo, "- %s\n", resultados[i].algoritmo);
                break;
            }
        }
    }

    fclose(arquivo);
    printf("Relatorio completo gerado: %s\n", caminho_completo);
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

    // Salva análise em arquivo
    FILE* arquivo = fopen("output/analise_estabilidade.txt", "w");
    if (arquivo) {
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

        fclose(arquivo);
        printf("\nAnalise completa salva em: output/analise_estabilidade.txt\n");
    }
}
