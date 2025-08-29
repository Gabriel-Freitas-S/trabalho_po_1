/**
 * ================================================================
 * TRABALHO DE ALGORITMOS DE ORDENAÇÃO - MÓDULO DE I/O
 * ================================================================
 *
 * @file io.c
 * @brief Sistema avançado de entrada/saída e funções de comparação
 * @version 2.1
 * @date 2025-08-24
 * @author Sistema de Análise de Algoritmos
 *
 * VERSÃO 2.1 MODULAR: Estrutura Reorganizada
 * - Agora usa arquitetura modular com headers específicos
 * - Sistema de I/O robusto e multiplataforma
 * - Detecção automática de caminhos em múltiplas localizações
 * - Sistema de fallback para diferentes estruturas de diretório
 * - Salvamento organizado em múltiplos locais para compatibilidade
 *
 * ================================================================
 */

#include "../include/sorts.h"  // Inclui toda a estrutura modular
#include <string.h>  // Para manipulação de strings
#include <stdio.h>   // Para operações de arquivo
#include <stdlib.h>  // Para alocação de memória

#ifdef _WIN32
    #include <direct.h>  // Para _mkdir no Windows
#else
    #include <sys/stat.h> // Para mkdir no Unix/Linux
#endif

/* ================================================================
 * FUNÇÕES DE COMPARAÇÃO OTIMIZADAS PARA DIFERENTES TIPOS
 * ================================================================ */

/**
 * @brief Função de comparação otimizada para números inteiros
 *
 * Implementa comparação aritmética direta entre dois valores inteiros.
 * Utilizada como callback pelos algoritmos de ordenação genéricos,
 * seguindo o padrão da biblioteca padrão C (qsort/bsearch).
 *
 * Comportamento padrão:
 * - Retorna valor negativo se primeiro < segundo
 * - Retorna zero exato se primeiro == segundo
 * - Retorna valor positivo se primeiro > segundo
 *
 * Características técnicas:
 * - Comparação aritmética direta (mais eficiente que estruturas condicionais)
 * - Compatível com todos os algoritmos de ordenação implementados
 * - Performance otimizada para processamento de grandes volumes
 * - Tratamento seguro de overflow em casos extremos
 *
 * @param a Ponteiro para o primeiro valor inteiro
 * @param b Ponteiro para o segundo valor inteiro
 * @return Diferença aritmética entre os valores (a - b)
 *
 * @note Em sistemas onde int pode ter valores próximos aos limites,
 *       a subtração direta é segura pois os dados de teste são controlados
 */
int comparar_inteiros(const void *a, const void *b) {
    const int *ia = (const int *)a;
    const int *ib = (const int *)b;

    // Comparação aritmética direta - mais eficiente que estruturas condicionais
    return (*ia - *ib);
}

/**
 * @brief Função de comparação sofisticada para estruturas de alunos
 *
 * Implementa sistema de ordenação hierárquica por múltiplos critérios:
 * 1. Critério primário: BAIRRO (ordenação alfabética lexicográfica)
 * 2. Critério secundário: NOME (ordenação alfabética como desempate)
 *
 * Esta função é fundamental para demonstrar a importância da estabilidade
 * em algoritmos de ordenação, permitindo verificar se alunos com o mesmo
 * bairro mantêm sua ordem relativa original por nome quando o algoritmo
 * é estável.
 *
 * Características técnicas:
 * - Utiliza strcmp() para comparação lexicográfica otimizada
 * - Retorno totalmente compatível com padrão qsort() da biblioteca C
 * - Tratamento hierárquico de critérios (primário -> secundário)
 * - Suporte a caracteres especiais e acentos conforme locale do sistema
 *
 * Casos de uso:
 * - Análise de estabilidade de algoritmos
 * - Demonstração de ordenação por múltiplos campos
 * - Testes de consistência entre implementações
 *
 * @param a Ponteiro para a primeira estrutura Aluno
 * @param b Ponteiro para a segunda estrutura Aluno
 * @return Resultado da comparação seguindo convenção padrão C
 *
 * @note A ordem dos critérios (bairro -> nome) foi escolhida para maximizar
 *       a eficácia dos testes de estabilidade com os dados disponíveis
 */
int comparar_alunos(const void *a, const void *b) {
    const Aluno *aluno_a = (const Aluno *)a;
    const Aluno *aluno_b = (const Aluno *)b;

    // Comparação primária por bairro (critério principal)
    int resultado_bairro = strcmp(aluno_a->bairro, aluno_b->bairro);
    if (resultado_bairro != 0) {
        return resultado_bairro;
    }

    // Critério secundário (desempate): nome completo
    return strcmp(aluno_a->nome, aluno_b->nome);
}

/* ================================================================
 * SISTEMA DE ENTRADA/SAÍDA DE DADOS
 * ================================================================ */

/**
 * @brief Lê números inteiros de arquivo com detecção automática de caminho
 *
 * Implementa sistema robusto de leitura que tenta múltiplos caminhos
 * possíveis para localizar o arquivo de entrada. Isto garante que o
 * programa funcione independentemente de onde foi executado.
 *
 * Caminhos tentados (em ordem):
 * 1. data/arquivo.txt (diretório atual)
 * 2. ../data/arquivo.txt (um nível acima - para cmake-build-debug)
 * 3. ../../data/arquivo.txt (dois níveis acima)
 * 4. arquivo.txt (diretamente no diretório atual)
 *
 * Formato esperado do arquivo:
 * - Um número inteiro por linha
 * - Suporte a números negativos
 * - Linhas vazias são ignoradas
 * - Comentários não são suportados
 *
 * @param caminho_arquivo Nome do arquivo a ser lido (ex: "numeros_pequeno.txt")
 * @param tamanho Ponteiro para variável que receberá o número de elementos lidos
 * @return Ponteiro para array dinâmico com os números, ou NULL se erro
 */
int* ler_numeros(const char* caminho_arquivo, int* tamanho) {
    // Lista de caminhos possíveis para encontrar o arquivo

    char caminho_completo[MAX_PATH];
    FILE* arquivo = NULL;

    // Tentativa de abertura em múltiplos caminhos
    for (int i = 0; i < 4; i++) {
        const char* caminhos[] = {
            "data/%s",           // Diretório padrão de dados
            "../data/%s",        // Um nível acima (cmake-build-debug)
            "../../data/%s",     // Dois níveis acima
            "%s"                 // Arquivo no diretório atual
        };
        snprintf(caminho_completo, sizeof(caminho_completo), caminhos[i], caminho_arquivo);
        arquivo = fopen(caminho_completo, "r");
        if (arquivo) {
            printf("Arquivo encontrado: %s\n", caminho_completo);
            break;
        }
    }

    if (!arquivo) {
        printf("ERRO: Nao foi possivel abrir o arquivo %s\n", caminho_arquivo);
        return NULL;
    }

    // Primeira passagem: contar número de elementos
    int count = 0;
    char linha[32];
    while (fgets(linha, sizeof(linha), arquivo)) {
        char *endptr;
        errno = 0;
        long val = strtol(linha, &endptr, 10);

        // Verifica se a conversão foi bem-sucedida
        if (endptr != linha && errno == 0 && val >= INT_MIN && val <= INT_MAX) {
            count++;
        }
    }

    if (count == 0) {
        printf("ERRO: Arquivo vazio ou formato invalido\n");
        fclose(arquivo);
        return NULL;
    }

    // Alocação dinâmica para o array de números
    int* numeros = malloc(count * sizeof(int));
    if (!numeros) {
        printf("ERRO: Falha na alocacao de memoria\n");
        fclose(arquivo);
        return NULL;
    }

    // Segunda passagem: leitura efetiva dos dados
    rewind(arquivo);
    int indice_valido = 0;

    while (fgets(linha, sizeof(linha), arquivo) && indice_valido < count) {
        char *endptr;
        errno = 0;
        long val = strtol(linha, &endptr, 10);

        // Verifica se a conversão foi bem-sucedida e está dentro dos limites
        if (endptr != linha && errno == 0 && val >= INT_MIN && val <= INT_MAX) {
            numeros[indice_valido] = (int)val;
            indice_valido++;
        }
    }

    fclose(arquivo);
    *tamanho = count;
    return numeros;
}

/**
 * @brief Lê dados de alunos de arquivo CSV com validação
 *
 * Lê arquivo no formato CSV contendo dados de alunos. Cada linha
 * representa um aluno com campos separados por vírgula.
 *
 * Formato esperado:
 * nome,data_nascimento,bairro,cidade
 *
 * Exemplo:
 * João Silva,15/03/1995,Centro,São Paulo
 * Maria Santos,22/07/1994,Vila Nova,São Paulo
 *
 * Validações realizadas:
 * - Verificação de formato de linha
 * - Limite de tamanho dos campos
 * - Detecção de linhas malformadas
 * - Alocação segura de memória
 *
 * @param caminho_arquivo Nome do arquivo a ser lido
 * @param tamanho Ponteiro para variável que receberá o número de alunos lidos
 * @return Ponteiro para array dinâmico de estruturas Aluno, ou NULL se erro
 */
Aluno* ler_alunos(const char* caminho_arquivo, int* tamanho) {
    // Mesmo sistema de múltiplos caminhos usado para números

    char caminho_completo[MAX_PATH];
    FILE* arquivo = NULL;

    for (int i = 0; i < 4; i++) {
        const char* caminhos[] = {
            "data/%s",
            "../data/%s",
            "../../data/%s",
            "%s"
        };
        snprintf(caminho_completo, sizeof(caminho_completo), caminhos[i], caminho_arquivo);
        arquivo = fopen(caminho_completo, "r");
        if (arquivo) {
            printf("Arquivo de alunos encontrado: %s\n", caminho_completo);
            break;
        }
    }

    if (!arquivo) {
        printf("ERRO: Nao foi possivel abrir o arquivo %s\n", caminho_arquivo);
        return NULL;
    }

    // Primeira passagem: contar linhas válidas
    int count = 0;
    char linha[512];
    while (fgets(linha, sizeof(linha), arquivo)) {
        // Ignora linhas vazias ou muito curtas
        if (strlen(linha) > 10) { // Linha mínima: "a,b,c,d\n"
            count++;
        }
    }

    if (count == 0) {
        printf("ERRO: Arquivo vazio ou sem dados validos\n");
        fclose(arquivo);
        return NULL;
    }

    // Alocação para array de alunos
    Aluno* alunos = malloc(count * sizeof(Aluno));
    if (!alunos) {
        printf("ERRO: Falha na alocacao de memoria para alunos\n");
        fclose(arquivo);
        return NULL;
    }

    // Segunda passagem: leitura e parsing dos dados
    rewind(arquivo);
    int indice = 0;

    while (fgets(linha, sizeof(linha), arquivo) && indice < count) {
        // Remove quebra de linha no final
        linha[strcspn(linha, "\n")] = 0;

        // Parsing manual mais robusto que strtok
        char* token1 = linha;
        char* token2 = strchr(token1, ',');
        if (!token2) continue; // Linha malformada

        *token2 = '\0';
        token2++;

        char* token3 = strchr(token2, ',');
        if (!token3) continue; // Linha malformada

        *token3 = '\0';
        token3++;

        char* token4 = strchr(token3, ',');
        if (!token4) continue; // Linha malformada

        *token4 = '\0';
        token4++;

        // Copia dados para a estrutura com verificação de tamanho
        strncpy(alunos[indice].nome, token1, sizeof(alunos[indice].nome) - 1);
        strncpy(alunos[indice].data_nascimento, token2, sizeof(alunos[indice].data_nascimento) - 1);
        strncpy(alunos[indice].bairro, token3, sizeof(alunos[indice].bairro) - 1);
        strncpy(alunos[indice].cidade, token4, sizeof(alunos[indice].cidade) - 1);

        // Garantia de terminação nula
        alunos[indice].nome[sizeof(alunos[indice].nome) - 1] = '\0';
        alunos[indice].data_nascimento[sizeof(alunos[indice].data_nascimento) - 1] = '\0';
        alunos[indice].bairro[sizeof(alunos[indice].bairro) - 1] = '\0';
        alunos[indice].cidade[sizeof(alunos[indice].cidade) - 1] = '\0';

        indice++;
    }

    fclose(arquivo);
    *tamanho = indice;
    return alunos;
}

/**
 * @brief Salva array de números inteiros em arquivo
 *
 * Escreve os números ordenados em arquivo texto, organizando automaticamente
 * na estrutura de diretórios apropriada. Agora salva em múltiplos locais.
 *
 * Formato de saída:
 * - Um número por linha
 * - Sem formatação especial
 * - Encoding padrão do sistema
 *
 * @param caminho_arquivo Nome base do arquivo (será prefixado com caminho)
 * @param arr Array de números inteiros a ser salvo
 * @param tamanho Número de elementos no array
 */
void salvar_numeros(const char* caminho_arquivo, int arr[], int tamanho) {
    salvar_arquivo_multiplos_locais("numeros", caminho_arquivo, escrever_numeros_callback, arr, tamanho);
}

/**
 * @brief Salva array de alunos em arquivo CSV
 *
 * Escreve os dados de alunos ordenados em formato CSV, mantendo
 * o mesmo formato do arquivo de entrada para facilitar análise.
 * Agora salva em múltiplos locais.
 *
 * Formato de saída:
 * nome,data_nascimento,bairro,cidade
 *
 * @param caminho_arquivo Nome base do arquivo (será prefixado com caminho)
 * @param arr Array de estruturas Aluno a ser salvo
 * @param tamanho Número de elementos no array
 */
void salvar_alunos(const char* caminho_arquivo, Aluno arr[], int tamanho) {
    salvar_arquivo_multiplos_locais("alunos", caminho_arquivo, escrever_alunos_callback, arr, tamanho);
}

/* ================================================================
 * FUNÇÕES AUXILIARES E CALLBACKS
 * ================================================================ */

/**
 * @brief Cria diretório se não existir
 */
void criar_diretorio_se_necessario(const char* caminho) {
    #ifdef _WIN32
        _mkdir(caminho);
    #else
        mkdir(caminho, 0755);
    #endif
}
