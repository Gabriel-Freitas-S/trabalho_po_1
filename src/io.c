/**
 * ================================================================
 * TRABALHO DE ALGORITMOS DE ORDENAÇÃO - MÓDULO DE I/O
 * ================================================================
 *
 * @file io.c
 * @brief Sistema de entrada/saída e funções de comparação
 * @version 2.0
 * @date 2025-08-23
 * @author Sistema de Análise de Algoritmos
 *
 * Este módulo implementa todas as operações de entrada e saída de dados,
 * incluindo leitura de arquivos, salvamento de resultados e funções de
 * comparação para diferentes tipos de dados.
 *
 * Funcionalidades principais:
 * - Leitura robusta de arquivos com múltiplos formatos
 * - Detecção automática de caminhos de arquivo
 * - Funções de comparação otimizadas para diferentes tipos
 * - Salvamento organizado de resultados
 * - Tratamento robusto de erros de I/O
 *
 * Tipos de dados suportados:
 * - Números inteiros (formato texto, um por linha)
 * - Estruturas de alunos (formato CSV)
 * - Extensível para novos tipos conforme necessário
 *
 * ================================================================
 */

#include "../include/sorts.h"

/* ================================================================
 * FUNÇÕES DE COMPARAÇÃO OTIMIZADAS
 * ================================================================ */

/**
 * @brief Função de comparação para números inteiros
 *
 * Implementa comparação aritmética simples entre dois inteiros.
 * Utilizada como callback pelos algoritmos de ordenação genéricos.
 *
 * Comportamento:
 * - Retorna valor negativo se a < b
 * - Retorna zero se a == b
 * - Retorna valor positivo se a > b
 *
 * @param a Ponteiro para o primeiro inteiro
 * @param b Ponteiro para o segundo inteiro
 * @return Diferença aritmética entre os valores
 */
int comparar_inteiros(const void *a, const void *b) {
    const int *ia = (const int *)a;
    const int *ib = (const int *)b;

    // Comparação aritmética direta - mais eficiente que if/else
    return (*ia - *ib);
}

/**
 * @brief Função de comparação para estruturas de alunos
 *
 * Implementa ordenação por múltiplos critérios:
 * 1. Critério primário: BAIRRO (ordem alfabética)
 * 2. Critério secundário: NOME (ordem alfabética)
 *
 * Esta função é essencial para demonstrar a importância da estabilidade
 * em algoritmos de ordenação, pois permite verificar se alunos com o
 * mesmo bairro mantêm sua ordem relativa original.
 *
 * Características técnicas:
 * - Usa strcmp() para comparação lexicográfica
 * - Retorno compatível com padrão qsort()
 * - Tratamento de casos de igualdade para critério secundário
 *
 * @param a Ponteiro para a primeira estrutura Aluno
 * @param b Ponteiro para a segunda estrutura Aluno
 * @return Resultado da comparação conforme padrão C
 */
int comparar_alunos(const void *a, const void *b) {
    const Aluno *aluno_a = (const Aluno *)a;
    const Aluno *aluno_b = (const Aluno *)b;

    // Comparação primária por bairro
    int resultado_bairro = strcmp(aluno_a->bairro, aluno_b->bairro);
    if (resultado_bairro != 0) {
        return resultado_bairro;
    }

    // Se bairros são iguais, usa critério secundário (nome)
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
    const char* caminhos[] = {
        "data/%s",           // Diretório padrão de dados
        "../data/%s",        // Um nível acima (cmake-build-debug)
        "../../data/%s",     // Dois níveis acima
        "%s"                 // Arquivo no diretório atual
    };

    char caminho_completo[MAX_PATH];
    FILE* arquivo = NULL;

    // Tentativa de abertura em múltiplos caminhos
    for (int i = 0; i < 4; i++) {
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
    int numero;
    while (fscanf(arquivo, "%d", &numero) == 1) {
        count++;
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
    for (int i = 0; i < count; i++) {
        if (fscanf(arquivo, "%d", &numeros[i]) != 1) {
            printf("ERRO: Falha na leitura do elemento %d\n", i + 1);
            free(numeros);
            fclose(arquivo);
            return NULL;
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
    const char* caminhos[] = {
        "data/%s",
        "../data/%s",
        "../../data/%s",
        "%s"
    };

    char caminho_completo[MAX_PATH];
    FILE* arquivo = NULL;

    for (int i = 0; i < 4; i++) {
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
 * na estrutura de diretórios apropriada (output/numeros/).
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
    // Múltiplos caminhos para garantir compatibilidade
    const char* caminhos[] = {
        "output/numeros/%s",
        "../output/numeros/%s",
        "../../output/numeros/%s"
    };

    char caminho_completo[MAX_PATH];
    FILE* arquivo = NULL;

    // Tenta salvar em cada caminho possível
    for (int i = 0; i < 3; i++) {
        snprintf(caminho_completo, sizeof(caminho_completo), caminhos[i], caminho_arquivo);
        arquivo = fopen(caminho_completo, "w");
        if (arquivo) {
            break;
        }
    }

    if (!arquivo) {
        printf("ERRO: Nao foi possivel criar arquivo %s\n", caminho_arquivo);
        return;
    }

    // Escrita sequencial dos números
    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%d\n", arr[i]);
    }

    fclose(arquivo);
    printf("Numeros salvos em: %s\n", caminho_completo);
}

/**
 * @brief Salva array de alunos em arquivo CSV
 *
 * Escreve os dados de alunos ordenados em formato CSV, mantendo
 * o mesmo formato do arquivo de entrada para facilitar análise.
 *
 * Formato de saída:
 * nome,data_nascimento,bairro,cidade
 *
 * @param caminho_arquivo Nome base do arquivo (será prefixado com caminho)
 * @param arr Array de estruturas Aluno a ser salvo
 * @param tamanho Número de elementos no array
 */
void salvar_alunos(const char* caminho_arquivo, Aluno arr[], int tamanho) {
    const char* caminhos[] = {
        "output/alunos/%s",
        "../output/alunos/%s",
        "../../output/alunos/%s"
    };

    char caminho_completo[MAX_PATH];
    FILE* arquivo = NULL;

    for (int i = 0; i < 3; i++) {
        snprintf(caminho_completo, sizeof(caminho_completo), caminhos[i], caminho_arquivo);
        arquivo = fopen(caminho_completo, "w");
        if (arquivo) {
            break;
        }
    }

    if (!arquivo) {
        printf("ERRO: Nao foi possivel criar arquivo de alunos %s\n", caminho_arquivo);
        return;
    }

    // Escrita em formato CSV
    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%s,%s,%s,%s\n",
                arr[i].nome,
                arr[i].data_nascimento,
                arr[i].bairro,
                arr[i].cidade);
    }

    fclose(arquivo);
    printf("Alunos salvos em: %s\n", caminho_completo);
}
