#include "../include/sorts.h"

#ifdef _WIN32
#include <direct.h>
#define MKDIR(path) _mkdir(path)
#else
#include <sys/stat.h>
#define MKDIR(path) mkdir(path, 0755)
#endif

/* ========================= FUNÇÕES PARA CRIAR DIRETÓRIOS ========================= */

/**
 * Cria os diretórios necessários para organizar a saída
 */
void criar_diretorios_output() {
    // Possíveis caminhos base
    const char* caminhos_base[] = {
        "output",
        "../output",
        "../../output"
    };

    const char* subdirs[] = {
        "/numeros",
        "/alunos",
        "/relatorios"
    };

    for (int i = 0; i < 3; i++) {
        // Cria diretório principal
        MKDIR(caminhos_base[i]);

        // Cria subdiretórios
        for (int j = 0; j < 3; j++) {
            char caminho_completo[MAX_PATH];
            snprintf(caminho_completo, sizeof(caminho_completo), "%s%s", caminhos_base[i], subdirs[j]);
            MKDIR(caminho_completo);
        }
    }
}

/* ========================= FUNÇÕES UTILITÁRIAS ========================= */

/**
 * Limpa o terminal (compatível com Windows e Unix)
 */
void limpar_terminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/**
 * Copia array genérico
 */
void copiar_array(const void *origem, void *destino, int tamanho, size_t elem_size) {
    memcpy(destino, origem, tamanho * elem_size);
}

/**
 * Imprime cabeçalho do programa
 */
void imprimir_cabecalho() {
    printf("================================================================\n");
    printf("              TRABALHO DE ALGORITMOS DE ORDENACAO              \n");
    printf("                     Programacao - 2025                        \n");
    printf("                    Estrutura Otimizada                        \n");
    printf("================================================================\n");
}

/**
 * Exibe menu principal
 */
void imprimir_menu() {
    printf("\n================================================================\n");
    printf("                        MENU PRINCIPAL                         \n");
    printf("================================================================\n");
    printf("  1. Testar algoritmos de ordenacao                            \n");
    printf("  2. Gerar relatorio completo de todos os testes               \n");
    printf("  0. Sair do programa                                           \n");
    printf("================================================================\n");
    printf("Escolha uma opcao: ");
}

/**
 * Exibe informações detalhadas dos algoritmos
 */
void exibir_info_algoritmos() {
    AlgoritmoInfo* algoritmos = obter_info_algoritmos();

    printf("\n=== INFORMACOES DOS ALGORITMOS IMPLEMENTADOS ===\n");
    printf("===============================================================================\n");

    printf("+----------------+------------+------------+------------+------------+\n");
    printf("| Algoritmo      | Melhor Caso| Caso Medio | Pior Caso  |Estabilidade|\n");
    printf("+----------------+------------+------------+------------+------------+\n");

    for (int i = 0; i < NUM_ALGORITMOS; i++) {
        printf("| %-14s | %-10s | %-10s | %-10s | %-10s |\n",
               algoritmos[i].nome,
               algoritmos[i].complexidade_melhor,
               algoritmos[i].complexidade_media,
               algoritmos[i].complexidade_pior,
               algoritmos[i].eh_estavel ? "Estavel" : "Nao Est.");
    }

    printf("+----------------+------------+------------+------------+------------+\n");

    printf("\n=== CARACTERISTICAS IMPORTANTES ===\n");
    printf("* Algoritmos ESTAVEIS preservam a ordem de elementos iguais\n");
    printf("* Quick Sort tem O(n²) no pior caso, mas e O(n log n) na media\n");
    printf("* Heap Sort garante O(n log n) em todos os casos\n");
    printf("* Insertion Sort e muito eficiente para pequenos conjuntos\n");
    printf("* Shell Sort melhora significativamente o Insertion Sort\n");
}

/**
 * Lista arquivos disponíveis para teste
 */
void listar_arquivos_disponiveis() {
    printf("\n=== ARQUIVOS DE TESTE DISPONIVEIS ===\n");
    printf("---------------------------------------\n");

    // Verifica arquivos de números
    printf("Arquivos de Numeros:\n");
    const char* arquivos_numeros[] = {"numeros_pequeno.txt", "numeros_medio.txt", "numeros_grande.txt",
                                     "numeros_ordenados.txt", "numeros_reversos.txt", "numeros_duplicados.txt"};

    for (int i = 0; i < 6; i++) {
        // Possíveis caminhos para encontrar o arquivo
        const char* caminhos[] = {"data/%s", "../data/%s", "../../data/%s", "%s"};
        char caminho_completo[MAX_PATH];
        FILE* teste = NULL;

        // Tenta cada caminho até encontrar o arquivo
        for (int j = 0; j < 4; j++) {
            snprintf(caminho_completo, sizeof(caminho_completo), caminhos[j], arquivos_numeros[i]);
            teste = fopen(caminho_completo, "r");
            if (teste) {
                fclose(teste);
                break;
            }
        }

        if (teste) {
            printf("  [OK] %s\n", arquivos_numeros[i]);
        } else {
            printf("  [--] %s (nao encontrado)\n", arquivos_numeros[i]);
        }
    }

    // Verifica arquivo de alunos
    printf("\nArquivos de Alunos:\n");
    const char* caminhos[] = {"data/alunos.txt", "../data/alunos.txt", "../../data/alunos.txt", "alunos.txt"};
    FILE* teste = NULL;

    // Tenta cada caminho até encontrar o arquivo
    for (int i = 0; i < 4; i++) {
        teste = fopen(caminhos[i], "r");
        if (teste) {
            fclose(teste);
            break;
        }
    }

    if (teste) {
        printf("  [OK] alunos.txt\n");
    } else {
        printf("  [--] alunos.txt (nao encontrado)\n");
    }
}

/**
 * Executa todos os testes disponíveis
 */
void executar_relatorio_completo() {
    // Garante que os diretórios de saída existam
    criar_diretorios_output();

    printf("\n=== EXECUTANDO RELATORIO COMPLETO ===\n");
    printf("=======================================\n");
    printf("Organizando saidas em:\n");
    printf("  - output/numeros/     (dados numericos ordenados)\n");
    printf("  - output/alunos/      (dados de alunos ordenados)\n");
    printf("  - output/relatorios/  (relatorios de tempos)\n\n");

    // Testa arquivos de números - incluindo todos os tipos
    const char* arquivos_numeros[] = {"numeros_pequeno.txt", "numeros_medio.txt", "numeros_grande.txt",
                                     "numeros_ordenados.txt", "numeros_reversos.txt", "numeros_duplicados.txt"};

    for (int i = 0; i < 6; i++) {
        int tamanho;
        int* dados = ler_numeros(arquivos_numeros[i], &tamanho);

        if (dados) {
            printf("\nTestando %s (%d elementos):\n", arquivos_numeros[i], tamanho);
            executar_todos_algoritmos(dados, tamanho, sizeof(int), comparar_inteiros,
                                    "numeros", arquivos_numeros[i]);
            free(dados);
        } else {
            printf("Pulando %s (arquivo nao encontrado)\n", arquivos_numeros[i]);
        }
    }

    // Testa arquivo de alunos
    int tamanho_alunos;
    Aluno* alunos = ler_alunos("alunos.txt", &tamanho_alunos);

    if (alunos) {
        printf("\nTestando alunos.txt (%d elementos):\n", tamanho_alunos);
        executar_todos_algoritmos(alunos, tamanho_alunos, sizeof(Aluno), comparar_alunos,
                                "alunos", "alunos.txt");

        // Executa análise de estabilidade automaticamente
        printf("\n=== ANALISE DE ESTABILIDADE (automatica) ===\n");
        analisar_estabilidade();

        free(alunos);
    } else {
        printf("Pulando alunos.txt (arquivo nao encontrado)\n");
    }

    printf("\n=== RELATORIO COMPLETO FINALIZADO ===\n");
    printf("Estrutura de saida organizada:\n");
    printf("  output/\n");
    printf("  ├── numeros/          (resultados ordenacao numerica)\n");
    printf("  ├── alunos/           (resultados ordenacao alunos)\n");
    printf("  ├── relatorios/       (analises de tempo)\n");
    printf("  └── analise_estabilidade.txt (analise completa)\n");
}

/**
 * Valida entrada do usuário
 */
int obter_opcao_usuario() {
    int opcao;
    if (scanf("%d", &opcao) != 1) {
        // Limpa buffer em caso de entrada inválida
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return -1;
    }
    return opcao;
}

/**
 * Pausa para o usuário pressionar Enter
 */
void pausar() {
    printf("\nPressione Enter para continuar...");
    getchar(); // Limpa buffer
    getchar(); // Aguarda Enter
}

/* ================================================================
 * FUNÇÕES AUXILIARES DE SALVAMENTO EM MÚLTIPLOS LOCAIS
 * ================================================================ */

/**
 * @brief Função callback para escrever números inteiros
 */
void escrever_numeros_callback(FILE* arquivo, void* dados, int tamanho) {
    int* arr = (int*)dados;
    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%d\n", arr[i]);
    }
}

/**
 * @brief Função callback para escrever alunos
 */
void escrever_alunos_callback(FILE* arquivo, void* dados, int tamanho) {
    Aluno* arr = (Aluno*)dados;
    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%s,%s,%s,%s\n",
                arr[i].nome,
                arr[i].data_nascimento,
                arr[i].bairro,
                arr[i].cidade);
    }
}

/**
 * @brief Salva arquivo em múltiplos locais
 *
 * Salva tanto no diretório cmake-build-debug/output quanto no output/
 * do projeto raiz para garantir que os arquivos estejam disponíveis
 * em ambos os locais.
 */
void salvar_arquivo_multiplos_locais(const char* subdir, const char* nome_arquivo,
                                   void (*conteudo_callback)(FILE*, void*, int),
                                   void* dados, int tamanho) {
    // Lista de todos os caminhos possíveis (build + projeto raiz)
    const char* caminhos[] = {
        "output/%s/%s",        // Diretório output do projeto
        "../output/%s/%s",     // Caso esteja executando de subdiretório
        "../../output/%s/%s",  // Caso esteja executando de cmake-build-debug
        "cmake-build-debug/output/%s/%s" // Diretório de build (explícito)
    };

    char caminho_completo[MAX_PATH];
    int arquivos_salvos = 0;

    // Tenta salvar em todos os caminhos possíveis
    for (int i = 0; i < 4; i++) {
        snprintf(caminho_completo, sizeof(caminho_completo), caminhos[i], subdir, nome_arquivo);

        FILE* arquivo = fopen(caminho_completo, "w");
        if (arquivo) {
            conteudo_callback(arquivo, dados, tamanho);
            fclose(arquivo);
            printf("Arquivo salvo em: %s\n", caminho_completo);
            arquivos_salvos++;
        }
    }

    if (arquivos_salvos == 0) {
        printf("ERRO: Nao foi possivel salvar o arquivo %s em nenhum local\n", nome_arquivo);
        printf("Tentou salvar em:\n");
        for (int i = 0; i < 4; i++) {
            snprintf(caminho_completo, sizeof(caminho_completo), caminhos[i], subdir, nome_arquivo);
            printf("  - %s\n", caminho_completo);
        }
    } else {
        printf("Arquivo %s salvo com sucesso em %d local(is)\n", nome_arquivo, arquivos_salvos);
    }
}
