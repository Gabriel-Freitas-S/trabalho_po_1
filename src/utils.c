/**
 * ================================================================
 * TRABALHO DE ALGORITMOS DE ORDENAÇÃO - MÓDULO UTILITÁRIO
 * ================================================================
 *
 * @file utils.c
 * @brief Sistema de utilidades, interface de usuário e gerenciamento de diretórios
 * @version 2.1
 * @date 2025-08-24
 * @author Sistema de Análise de Algoritmos
 *
 * Este módulo implementa todas as funções utilitárias do sistema, incluindo
 * interface de usuário, gerenciamento de diretórios, callbacks de escrita
 * e funcionalidades de suporte geral para o programa principal.
 *
 * VERSÃO 2.1: Sistema Utilitário Robusto e Multiplataforma
 * - Criação automática de estruturas de diretórios em múltiplos locais
 * - Interface de usuário limpa e informativa com feedback visual
 * - Sistema de callbacks flexível para diferentes tipos de dados
 * - Compatibilidade total entre Windows, Linux e macOS
 * - Gerenciamento inteligente de caminhos e estruturas de arquivos
 *
 * Funcionalidades principais:
 * - Gerenciamento automático de diretórios de saída organizados
 * - Interface de usuário com menus claros e informativos
 * - Sistema de callbacks para escrita personalizada de diferentes tipos
 * - Funções utilitárias multiplataforma (limpeza de terminal, etc.)
 * - Validação e tratamento robusto de entrada do usuário
 * - Sistema de salvamento em múltiplos locais para compatibilidade
 *
 * Estrutura de diretórios gerenciada:
 * - output/numeros/     - Arrays de números ordenados
 * - output/alunos/      - Dados de alunos ordenados
 * - output/relatorios/  - Relatórios de análise e performance
 * - Réplicas em cmake-build-debug/ para compatibilidade com IDEs
 *
 * ================================================================
 */

#include "../include/sorts.h"

// Headers específicos por plataforma para operações de diretório
#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(path) _mkdir(path)
#else
    #include <sys/stat.h>
    #define MKDIR(path) mkdir(path, 0755)
#endif

/* ================================================================
 * SISTEMA DE GERENCIAMENTO DE DIRETÓRIOS MULTIPLATAFORMA
 * ================================================================ */

/**
 * @brief Cria estrutura completa de diretórios para organização de resultados
 *
 * Esta função implementa um sistema robusto de criação de diretórios que
 * garante que todos os arquivos de saída sejam organizados adequadamente,
 * independentemente de onde o programa foi executado.
 *
 * Estratégia de criação:
 * 1. Tenta criar estrutura em múltiplos locais simultaneamente
 * 2. Ignora erros de diretórios já existentes (comportamento normal)
 * 3. Cria hierarquia completa: base -> subdiretórios especializados
 *
 * Estrutura criada:
 * - output/ (diretório raiz dos resultados)
 *   ├── numeros/ (arrays de números ordenados)
 *   ├── alunos/ (dados de alunos ordenados)
 *   └── relatorios/ (análises e relatórios de performance)
 * - Réplicas em ../output/ e ../../output/ para compatibilidade
 *
 * @note Esta função é chamada automaticamente no início do programa
 *       e falha silenciosamente se os diretórios já existem (comportamento desejado)
 */
void criar_diretorios_output() {
    // Múltiplos caminhos base para máxima compatibilidade
    const char* caminhos_base[] = {
        "output",           // Diretório atual
        "../output",        // Um nível acima (para cmake-build-debug)
        "../../output"      // Dois níveis acima (para estruturas aninhadas)
    };

    // Subdiretórios especializados por tipo de dados
    const char* subdiretorios[] = {
        "/numeros",         // Arrays de números ordenados
        "/alunos",          // Estruturas de alunos ordenadas
        "/relatorios"       // Relatórios de análise e performance
    };

    // Criação da estrutura completa em todos os locais possíveis
    for (int i = 0; i < 3; i++) {
        // Cria diretório base principal
        MKDIR(caminhos_base[i]);

        // Cria cada subdiretório especializado
        for (int j = 0; j < 3; j++) {
            char caminho_completo[MAX_PATH];
            snprintf(caminho_completo, sizeof(caminho_completo),
                    "%s%s", caminhos_base[i], subdiretorios[j]);
            MKDIR(caminho_completo);
        }
    }
}

/* ================================================================
 * SISTEMA DE CALLBACKS PARA ESCRITA DE DIFERENTES TIPOS DE DADOS
 * ================================================================ */

/**
 * @brief Callback especializado para escrita de arrays de números inteiros
 *
 * Função callback utilizada pelo sistema de salvamento em múltiplos locais
 * para escrever arrays de números inteiros em formato padronizado.
 *
 * Formato de saída:
 * - Um número por linha
 * - Sem formatação especial ou separadores
 * - Encoding padrão do sistema
 * - Números negativos suportados
 *
 * @param arquivo Ponteiro para arquivo aberto para escrita
 * @param dados Ponteiro para array de inteiros (deve ser int*)
 * @param tamanho Número de elementos no array
 */
void escrever_numeros_callback(FILE* arquivo, void* dados, int tamanho) {
    int* numeros = (int*)dados;

    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%d\n", numeros[i]);
    }
}

/**
 * @brief Callback especializado para escrita de estruturas de alunos
 *
 * Função callback para escrever dados de alunos em formato CSV padronizado,
 * mantendo compatibilidade com o formato de entrada original.
 *
 * Formato de saída CSV:
 * nome,data_nascimento,bairro,cidade
 *
 * Características:
 * - Campos separados por vírgula (padrão CSV)
 * - Sem aspas ao redor dos campos (simplificado)
 * - Uma linha por aluno
 * - Ordem dos campos mantida para consistência
 *
 * @param arquivo Ponteiro para arquivo aberto para escrita
 * @param dados Ponteiro para array de estruturas Aluno
 * @param tamanho Número de estruturas no array
 */
void escrever_alunos_callback(FILE* arquivo, void* dados, int tamanho) {
    Aluno* alunos = (Aluno*)dados;

    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%s,%s,%s,%s\n",
                alunos[i].nome,
                alunos[i].data_nascimento,
                alunos[i].bairro,
                alunos[i].cidade);
    }
}

/**
 * @brief Sistema unificado de salvamento em múltiplos locais
 *
 * Esta função implementa o core do sistema de salvamento que garante
 * que todos os arquivos sejam salvos em múltiplos locais para máxima
 * compatibilidade com diferentes estruturas de projeto.
 *
 * Estratégia de salvamento:
 * 1. Tenta salvar em vários locais possíveis
 * 2. Para na primeira tentativa bem-sucedida
 * 3. Usa callbacks especializados para cada tipo de dados
 * 4. Cria estrutura de diretórios se necessário
 *
 * Locais tentados (em ordem):
 * - output/subdir/arquivo
 * - ../output/subdir/arquivo
 * - ../../output/subdir/arquivo
 *
 * @param subdir Subdiretório de destino ("numeros", "alunos", "relatorios", ou "")
 * @param nome_arquivo Nome do arquivo a ser criado
 * @param conteudo_callback Função callback para escrever o conteúdo específico
 * @param dados Dados a serem escritos (tipo depende do callback)
 * @param tamanho Tamanho dos dados (interpretação depende do callback)
 */
void salvar_arquivo_multiplos_locais(const char* subdir, const char* nome_arquivo,
                                   void (*conteudo_callback)(FILE*, void*, int),
                                   void* dados, int tamanho) {

    // Múltiplos caminhos base para tentar salvamento
    const char* caminhos_base[] = {
        "output",           // Diretório atual
        "../output",        // Um nível acima
        "../../output"      // Dois níveis acima
    };

    char caminho_completo[MAX_PATH];
    FILE* arquivo = NULL;

    // Tenta salvar em cada local possível até conseguir
    for (int i = 0; i < 3; i++) {
        if (strlen(subdir) > 0) {
            // Com subdiretório especializado
            snprintf(caminho_completo, sizeof(caminho_completo),
                    "%s/%s/%s", caminhos_base[i], subdir, nome_arquivo);
        } else {
            // Diretamente no diretório output
            snprintf(caminho_completo, sizeof(caminho_completo),
                    "%s/%s", caminhos_base[i], nome_arquivo);
        }

        arquivo = fopen(caminho_completo, "w");
        if (arquivo) {
            // Sucesso: escreve conteúdo usando callback especializado
            conteudo_callback(arquivo, dados, tamanho);
            fclose(arquivo);

            printf("Arquivo salvo: %s\n", caminho_completo);
            return; // Sucesso: interrompe tentativas adicionais
        }
    }

    // Se chegou aqui, todas as tentativas falharam
    printf("AVISO: Nao foi possivel salvar %s em nenhum local\n", nome_arquivo);
}

/* ================================================================
 * FUNÇÕES UTILITÁRIAS MULTIPLATAFORMA
 * ================================================================ */

/**
 * @brief Limpa a tela do terminal de forma multiplataforma
 *
 * Implementa limpeza de terminal compatível com diferentes sistemas
 * operacionais, melhorando a experiência visual do usuário.
 *
 * Comandos utilizados:
 * - Windows: "cls" (command prompt padrão)
 * - Unix/Linux/macOS: "clear" (terminal padrão)
 */
void limpar_terminal() {
#ifdef _WIN32
    system("cls");    // Windows: Command Prompt
#else
    system("clear");  // Unix/Linux/macOS: Terminal
#endif
}

/**
 * @brief Copia array genérico de forma segura
 *
 * Utiliza memcpy para copiar arrays de qualquer tipo de dados de forma
 * eficiente e segura. Fundamental para preservar dados originais durante
 * múltiplas execuções de algoritmos.
 *
 * @param origem Ponteiro para dados de origem (não modificado)
 * @param destino Ponteiro para área de destino (será sobrescrita)
 * @param tamanho Número de elementos a copiar
 * @param elem_size Tamanho de cada elemento em bytes
 *
 * @note Assume que o destino tem espaço suficiente alocado
 */
void copiar_array(const void *origem, void *destino, int tamanho, size_t elem_size) {
    memcpy(destino, origem, tamanho * elem_size);
}

/* ================================================================
 * INTERFACE DE USUÁRIO E MENUS
 * ================================================================ */

/**
 * @brief Exibe cabeçalho informativo e elegante do programa
 *
 * Apresenta informações sobre o programa de forma visualmente atraente,
 * incluindo identificação do projeto, ano e características especiais
 * da implementação atual.
 */
void imprimir_cabecalho() {
    printf("================================================================\n");
    printf("              TRABALHO DE ALGORITMOS DE ORDENAÇÃO              \n");
    printf("                    Programação Avançada - 2025                \n");
    printf("                Sistema Dual: Otimizada + Didática             \n");
    printf("================================================================\n");
}

/**
 * @brief Exibe menu principal com opções detalhadas e informativas
 *
 * Apresenta ao usuário as opções disponíveis com descrições claras
 * sobre o que cada opção fará, incluindo informações sobre as duas
 * versões de algoritmos que serão testadas.
 */
void imprimir_menu() {
    printf("\n================================================================\n");
    printf("                        MENU PRINCIPAL                         \n");
    printf("================================================================\n");
    printf("  1. Gerar relatório completo de todos os testes               \n");
    printf("     (Inclui análise de ambas as versões dos algoritmos)       \n");
    printf("  0. Sair do programa                                           \n");
    printf("================================================================\n");
    printf("O relatório completo incluirá análise de AMBAS as versões:     \n");
    printf("  ✓ Versão OTIMIZADA (máxima performance, com melhorias)       \n");
    printf("  ✓ Versão NÃO OTIMIZADA (didática, para fins comparativos)    \n");
    printf("================================================================\n");
    printf("Todos os conjuntos de dados serão testados automaticamente:    \n");
    printf("  • Arrays de números (6 conjuntos diferentes)                 \n");
    printf("  • Dados de alunos (ordenação por múltiplos critérios)        \n");
    printf("  • Análise completa de estabilidade dos algoritmos            \n");
    printf("================================================================\n");
    printf("Escolha uma opção: ");
}

/**
 * @brief Exibe informações detalhadas e tabela comparativa de todos os algoritmos
 *
 * Apresenta uma tabela estruturada com informações técnicas completas sobre
 * cada algoritmo implementado, incluindo complexidades teóricas e características
 * de estabilidade. Essencial para compreensão teórica antes dos testes práticos.
 *
 * Informações exibidas:
 * - Nome do algoritmo
 * - Complexidade no melhor caso (Big-O)
 * - Complexidade no caso médio (Big-O)
 * - Complexidade no pior caso (Big-O)
 * - Propriedade de estabilidade (Sim/Não)
 *
 * @note Esta função obtém dados da base de conhecimento centralizada
 *       e os apresenta em formato tabular legível
 */
void exibir_info_algoritmos() {
    AlgoritmoInfo* algoritmos = obter_info_algoritmos();

    printf("\n=== INFORMAÇÕES DOS ALGORITMOS IMPLEMENTADOS ===\n");
    printf("===============================================================================\n");

    printf("+----------------+------------+------------+------------+------------+\n");
    printf("| Algoritmo      | Melhor     | Médio      | Pior       | Estável    |\n");
    printf("+----------------+------------+------------+------------+------------+\n");

    for (int i = 0; i < NUM_ALGORITMOS; i++) {
        printf("| %-14s | %-10s | %-10s | %-10s | %-10s |\n",
               algoritmos[i].nome,
               algoritmos[i].complexidade_melhor,
               algoritmos[i].complexidade_media,
               algoritmos[i].complexidade_pior,
               algoritmos[i].eh_estavel ? "Sim" : "Não");
    }

    printf("+----------------+------------+------------+------------+------------+\n");
    printf("\nLEGENDA:\n");
    printf("• Complexidades em notação Big-O (comportamento assintótico)\n");
    printf("• Estável: preserva ordem relativa de elementos iguais\n");
    printf("• Melhor caso: dados já ordenados ou estrutura favorável\n");
    printf("• Pior caso: dados em ordem reversa ou estrutura desfavorável\n");
    printf("===============================================================================\n");
}

/**
 * @brief Lista e exibe informações sobre arquivos de dados disponíveis
 *
 * Apresenta uma lista organizada de todos os arquivos de teste disponíveis
 * no sistema, categorizados por tipo, com descrições sobre suas características
 * e propósitos específicos nos testes de algoritmos.
 *
 * Categorias apresentadas:
 * - Arquivos de números inteiros (diferentes tamanhos e organizações)
 * - Arquivo de dados de alunos (para testes de estabilidade)
 *
 * @note Esta função serve principalmente para fins informativos e educacionais
 */
void listar_arquivos_disponiveis() {
    printf("\n=== ARQUIVOS DE DADOS DISPONÍVEIS PARA TESTE ===\n");
    printf("================================================================\n");

    printf("\nARQUIVOS DE NÚMEROS INTEIROS:\n");
    printf("─────────────────────────────────────────────────────────────\n");
    printf("• numeros_pequeno.txt     - Conjunto pequeno (~100 elementos)\n");
    printf("• numeros_medio.txt       - Conjunto médio (~1.000 elementos)\n");
    printf("• numeros_grande.txt      - Conjunto grande (~10.000 elementos)\n");
    printf("• numeros_ordenados.txt   - Dados já ordenados (melhor caso)\n");
    printf("• numeros_reversos.txt    - Dados em ordem inversa (pior caso)\n");
    printf("• numeros_duplicados.txt  - Muitos elementos repetidos\n");

    printf("\nARQUIVOS DE DADOS ESTRUTURADOS:\n");
    printf("─────────────────────────────────────────────────────────────\n");
    printf("• alunos.txt              - Dados de estudantes (nome, data,\n");
    printf("                           bairro, cidade) para testes de\n");
    printf("                           estabilidade e múltiplos critérios\n");

    printf("\nCARACTERÍSTICAS DOS CONJUNTOS:\n");
    printf("─────────────────────────────────────────────────────────────\n");
    printf("• Pequeno:    Ideal para algoritmos O(n²) - execução rápida\n");
    printf("• Médio:      Mostra diferenças entre O(n²) e O(n log n)\n");
    printf("• Grande:     Destaca vantagens de algoritmos eficientes\n");
    printf("• Ordenados:  Testa melhor caso e otimizações especiais\n");
    printf("• Reversos:   Força pior caso na maioria dos algoritmos\n");
    printf("• Duplicados: Essencial para análise de estabilidade\n");
    printf("================================================================\n");
}

/**
 * @brief Obtém e valida entrada do usuário de forma robusta
 *
 * Implementa sistema robusto de entrada que trata adequadamente:
 * - Entradas não numéricas (letras, símbolos, etc.)
 * - Valores fora da faixa esperada
 * - Buffers de entrada corrompidos
 * - Múltiplos caracteres na mesma linha
 *
 * Características do tratamento:
 * - Limpeza automática do buffer de entrada
 * - Retorno de código de erro para entradas inválidas
 * - Mensagens claras de erro (tratadas pela função chamadora)
 * - Não trava em loops infinitos com entradas malformadas
 *
 * @return Número válido escolhido pelo usuário, ou -1 se entrada inválida
 *
 * @note Retorna -1 para qualquer entrada que não seja um número inteiro válido,
 *       permitindo que a função chamadora trate adequadamente o erro
 */
int obter_opcao_usuario() {
    int opcao;
    int resultado = scanf("%d", &opcao);

    // Limpa buffer de entrada para evitar loops infinitos
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Descarta caracteres extras no buffer
    }

    // Retorna -1 se a leitura falhou (entrada não numérica)
    if (resultado != 1) {
        return -1;
    }

    return opcao;
}

/**
 * @brief Pausa a execução aguardando interação do usuário
 *
 * Implementa pausa elegante que aguarda o usuário pressionar ENTER
 * antes de continuar. Útil para permitir que o usuário leia resultados
 * na tela antes que seja limpa para a próxima operação.
 *
 * Características:
 * - Mensagem clara sobre como prosseguir
 * - Limpeza automática do buffer de entrada
 * - Funciona mesmo com buffers contaminados de operações anteriores
 */
void pausar() {
    printf("\nPressione ENTER para continuar...");

    // Limpa qualquer entrada pendente no buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Descarta caracteres no buffer até encontrar newline
    }

    // Aguarda nova entrada do usuário
    getchar();
}

/**
 * @brief Executa bateria completa de testes com ambas as versões dos algoritmos
 *
 * Esta é a função central que coordena toda a análise comparativa do sistema.
 * Executa uma sequência completa de testes que incluem:
 *
 * Sequência de execução:
 * 1. Criação da estrutura de diretórios de saída
 * 2. Execução de todos os testes com versão NÃO OTIMIZADA
 * 3. Execução de todos os testes com versão OTIMIZADA
 * 4. Análise detalhada de estabilidade com dados reais
 * 5. Geração de relatório comparativo final consolidado
 *
 * Dados testados automaticamente:
 * - 6 conjuntos diferentes de números inteiros
 * - 1 conjunto de dados de alunos estruturados
 * - Análise de estabilidade com casos especiais
 *
 * Arquivos gerados:
 * - Arrays ordenados por algoritmo e versão (output/numeros/, output/alunos/)
 * - Relatórios de performance detalhados (output/relatorios/)
 * - Análise de estabilidade (output/analise_estabilidade.txt)
 * - Relatório comparativo final (output/relatorios/)
 *
 * @note Esta função pode levar vários minutos para executar completamente,
 *       dependendo do hardware e do tamanho dos conjuntos de dados
 */
void executar_relatorio_completo() {
    printf("\n=== INICIANDO ANÁLISE COMPARATIVA COMPLETA ===\n");
    printf("Este processo testará AMBAS as versões de todos os algoritmos.\n");
    printf("Tempo estimado: 2-5 minutos (dependendo do hardware)\n\n");

    // Inicialização: cria estrutura de diretórios necessária
    criar_diretorios_output();

    // Lista de arquivos de números para teste automatizado
    const char* arquivos_numeros[] = {
        "numeros_pequeno.txt",
        "numeros_medio.txt",
        "numeros_grande.txt",
        "numeros_ordenados.txt",
        "numeros_reversos.txt",
        "numeros_duplicados.txt"
    };

    printf("FASE 1: Testando versão NÃO OTIMIZADA (didática)\n");
    printf("================================================\n");
    configurar_otimizacao(0); // Usa versões não otimizadas

    // Testa todos os conjuntos de números com versão não otimizada
    for (int i = 0; i < 6; i++) {
        printf("\nTestando arquivo: %s\n", arquivos_numeros[i]);

        int tamanho;
        int* dados = ler_numeros(arquivos_numeros[i], &tamanho);

        if (dados) {
            executar_todos_algoritmos_com_salvamento(dados, tamanho, sizeof(int),
                                                   comparar_inteiros, "numeros",
                                                   arquivos_numeros[i], "nao_otimizada");
            free(dados);
        } else {
            printf("AVISO: Não foi possível carregar %s\n", arquivos_numeros[i]);
        }
    }

    // Testa dados de alunos com versão não otimizada
    printf("\nTestando dados de alunos (não otimizada)...\n");
    int tamanho_alunos;
    Aluno* alunos = ler_alunos("alunos.txt", &tamanho_alunos);

    if (alunos) {
        executar_todos_algoritmos_com_salvamento(alunos, tamanho_alunos, sizeof(Aluno),
                                               comparar_alunos, "alunos",
                                               "alunos.txt", "nao_otimizada");
        free(alunos);
    }

    printf("\n\nFASE 2: Testando versão OTIMIZADA (performance)\n");
    printf("===============================================\n");
    configurar_otimizacao(1); // Usa versões otimizadas

    // Testa todos os conjuntos de números com versão otimizada
    for (int i = 0; i < 6; i++) {
        printf("\nTestando arquivo: %s\n", arquivos_numeros[i]);

        int tamanho;
        int* dados = ler_numeros(arquivos_numeros[i], &tamanho);

        if (dados) {
            executar_todos_algoritmos_com_salvamento(dados, tamanho, sizeof(int),
                                                   comparar_inteiros, "numeros",
                                                   arquivos_numeros[i], "otimizada");
            free(dados);
        } else {
            printf("AVISO: Não foi possível carregar %s\n", arquivos_numeros[i]);
        }
    }

    // Testa dados de alunos com versão otimizada
    printf("\nTestando dados de alunos (otimizada)...\n");
    alunos = ler_alunos("alunos.txt", &tamanho_alunos);

    if (alunos) {
        executar_todos_algoritmos_com_salvamento(alunos, tamanho_alunos, sizeof(Aluno),
                                               comparar_alunos, "alunos",
                                               "alunos.txt", "otimizada");
        free(alunos);
    }

    printf("\n\nFASE 3: Análise de estabilidade dos algoritmos\n");
    printf("==============================================\n");
    analisar_estabilidade();

    printf("\n\nFASE 4: Gerando relatório comparativo final\n");
    printf("===========================================\n");
    gerar_relatorio_comparativo_final();

    // Restaura configuração padrão
    configurar_otimizacao(1);

    printf("\n=== ANÁLISE COMPLETA FINALIZADA COM SUCESSO ===\n");
    printf("Verifique a pasta 'output/' para todos os resultados gerados.\n");
    printf("Relatório comparativo final disponível em 'output/relatorios/'.\n");
}
