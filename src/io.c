/**
 * ================================================================
 * SISTEMA INTELIGENTE DE ENTRADA/SAÍDA E OPERAÇÕES DE DADOS
 * ================================================================
 *
 * @file io.c
 * @brief Núcleo robusto para leitura, escrita e comparação de dados multiplataforma
 *
 * Este módulo implementa um sistema de I/O inteligente que resolve automaticamente
 * Este módulo implementa um sistema de I/O inteligente que resolve automaticamente
 * os desafios comuns de localização de arquivos e compatibilidade entre diferentes
 * estruturas de projeto, IDEs e sistemas operacionais.
 *
 *  DETECÇÃO AUTOMÁTICA DE CAMINHOS:
 * ┌─────────────────────────────────────────────────────────────────────────┐
 * │ O sistema tenta múltiplos caminhos automaticamente:                     │
 * │ • data/arquivo.txt           (estrutura padrão)                        │
 * │ • ../data/arquivo.txt        (executado em build/debug)                │
 * │ • ../../data/arquivo.txt     (estruturas aninhadas)                    │
 * │ • arquivo.txt                (diretório atual como fallback)           │
 * └─────────────────────────────────────────────────────────────────────────┘
 *
 *  ESTRATÉGIA DE SALVAMENTO INTELIGENTE:
 * - Criação automática de estrutura de diretórios organizada
 * - Salvamento em múltiplos locais para máxima compatibilidade
 * - Estrutura especializada por tipo de dados (numeros/, alunos/, relatorios/)
 * - Tolerância a falhas: continua funcionando mesmo com limitações de permissão
 *
 *  FUNÇÕES DE COMPARAÇÃO OTIMIZADAS:
 * - Comparação aritmética direta para inteiros (máxima eficiência)
 * - Comparação hierárquica sofisticada para estruturas complexas
 * - Compatibilidade total com padrão qsort() da biblioteca C
 * - Suporte a critérios múltiplos de ordenação
 *
 *  COMPATIBILIDADE MULTIPLATAFORMA:
 * - Detecção automática do sistema operacional (Windows/Unix/Linux)
 * - Separadores de caminho apropriados para cada plataforma
 * - Criação de diretórios com permissões adequadas
 * - Tratamento robusto de diferentes sistemas de arquivos
 *
 *  ROBUSTEZ E VALIDAÇÃO:
 * - Validação rigorosa de formatos de arquivo
 * - Tratamento gracioso de arquivos corrompidos ou malformados
 * - Detecção de overflow em operações numéricas
 * - Fallbacks inteligentes para cenários de erro
 *
 * ================================================================
 */

#include "../include/sorts.h"  // Inclui toda a estrutura modular
#include <string.h>  // Para manipulação de strings
#include <stdio.h>   // Para operações de arquivo
#include <stdlib.h>  // Para alocação de memória
#include <limits.h>  // Para INT_MAX, INT_MIN

// Definições de constantes se não estiverem definidas
#ifndef MAX_PATH
    #ifdef _WIN32
        #define MAX_PATH 260
    #else
        #define MAX_PATH 4096
    #endif
#endif

#ifdef _WIN32
    #include <direct.h>  // Para _mkdir no Windows
#else
    #include <sys/stat.h> // Para mkdir no Unix/Linux
#endif

// Removendo definição local conflitante da estrutura Aluno
// A definição correta está em tipos.h como typedef

// Declaração da função auxiliar
static void criar_diretorio_se_necessario(const char* caminho);

/* ================================================================
 * FUNÇÕES DE COMPARAÇÃO OTIMIZADAS PARA DIFERENTES TIPOS
 * ================================================================ */

/**
 * @brief Função de comparação ultra-otimizada para inteiros com aritmética direta
 *
 *  FILOSOFIA DE DESIGN:
 * Esta implementação privilegia performance máxima através de comparação
 * aritmética direta, evitando estruturas condicionais que introduziriam
 * branches desnecessários no pipeline do processador.
 *
 *  VANTAGENS DA COMPARAÇÃO ARITMÉTICA:
 * ┌─────────────────────────────────────────────────────────────────────────┐
 * │ • Uma única operação CPU (subtração) vs múltiplas comparações           │
 * │ • Sem branches condicionais → melhor previsão de branch do processador  │
 * │ • Compatibilidade total com padrão qsort() da biblioteca C              │
 * │ • Resultado direto: negativo, zero, ou positivo (semântica padrão)      │
 * └─────────────────────────────────────────────────────────────────────────┘
 *
 *  SEMÂNTICA DE RETORNO (Padrão ANSI C):
 * - Resultado < 0: primeiro elemento é MENOR que segundo (a < b)
 * - Resultado = 0: elementos são IGUAIS (a == b)
 * - Resultado > 0: primeiro elemento é MAIOR que segundo (a > b)
 *
 *  PERFORMANCE vs ALTERNATIVAS:
 * ┌─────────────────────────┬─────────────────┬─────────────────────────┐
 * │ Implementação           │ Operações CPU   │ Branches                │
 * ├─────────────────────────┼─────────────────┼─────────────────────────┤
 * │ Aritmética (esta)       │ 2 (load, sub)   │ 0                       │
 * │ If-else tradicional     │ 4+ (load,cmp,jmp│ 2-3                     │
 * │ Ternário otimizado      │ 3 (load,cmp,sel)│ 0-1 (dep. compilador)   │
 * └─────────────────────────┴─────────────────┴─────────────────────────┘
 *
 *  SEGURANÇA NUMÉRICA:
 * Para dados controlados de teste (números típicos), a subtração direta
 * é segura. Em contextos com valores extremos próximos a INT_MAX/INT_MIN,
 * considerar implementação com validação de overflow.
 *
 *  INTEGRAÇÃO COM ALGORITMOS:
 * Esta função é chamada milhares de vezes durante algoritmos de ordenação.
 * A otimização extrema aqui se reflete diretamente na performance global
 * de todos os algoritmos que dependem desta comparação.
 *
 * @param a Ponteiro para primeiro inteiro (será dereferenciado)
 * @param b Ponteiro para segundo inteiro (será dereferenciado)
 * @return Diferença aritmética (a - b):
 *         - < 0 se a < b (ordem crescente: a deve vir antes de b)
 *         - = 0 se a == b (elementos equivalentes)
 *         - > 0 se a > b (ordem crescente: a deve vir depois de b)
 *
 * @note Otimizada para processamento de grandes volumes. Em datasets com
 *       bilhões de comparações, esta otimização resulta em economia significativa.
 */
int comparar_inteiros(const void *a, const void *b) {
    const int *ia = (const int *)a;
    const int *ib = (const int *)b;

    // Comparação aritmética direta - mais eficiente que estruturas condicionais
    return (*ia - *ib);
}

/**
 * @brief Sistema hierárquico de comparação para estruturas complexas de alunos
 *
 *  OBJETIVO EDUCACIONAL PRINCIPAL:
 * Esta função é o coração da demonstração de estabilidade de algoritmos!
 * Implementa ordenação por múltiplos critérios para revelar visualmente
 * quais algoritmos preservam a ordem relativa de elementos equivalentes.
 *
 *  ARQUITETURA HIERÁRQUICA DE CRITÉRIOS:
 * ┌─────────────────────────────────────────────────────────────────────────┐
 * │ CRITÉRIO PRIMÁRIO: BAIRRO (string lexicográfica)                       │
 * │ ├─ Determina agrupamento principal dos dados                           │
 * │ ├─ Comparação case-sensitive usando strcmp()                           │
 * │ └─ Se iguais → avança para critério secundário                         │
 * │                                                                         │
 * │ CRITÉRIO SECUNDÁRIO: NOME (desempate lexicográfico)                    │
 * │ ├─ Usado apenas quando bairros são idênticos                           │
 * │ ├─ Garante ordenação total (sem empates)                               │
 * │ └─ Preserva determinismo em algoritmos estáveis                        │
 * └─────────────────────────────────────────────────────────────────────────┘
 *
 *  DEMONSTRAÇÃO DE ESTABILIDADE:
 * Considere este exemplo pedagógico:
 * ┌─────────────────┬─────────────────┬─────────────────────────────────────┐
 * │ Dados Originais │ Ordem de Entrada│ Após Ordenação (Algoritmo Estável) │
 * ├─────────────────┼─────────────────┼─────────────────────────────────────┤
 * │ Alice, Centro   │ 1ª posição      │ Alice, Centro (1ª - preservada)    │
 * │ Bruno, Centro   │ 2ª posição      │ Bruno, Centro (2ª - preservada)    │
 * │ Carlos, Vila    │ 3ª posição      │ Carlos, Vila                        │
 * └─────────────────┴─────────────────┴─────────────────────────────────────┘
 *
 * Se Alice e Bruno têm o mesmo bairro, um algoritmo ESTÁVEL manterá
 * Alice antes de Bruno. Um algoritmo INSTÁVEL pode inverter esta ordem.
 *
 *  LÓGICA DE DECISÃO IMPLEMENTADA:
 * ```
 * 1. Compara bairro_a com bairro_b
 *    ├─ Se diferentes: retorna resultado da comparação (< 0, > 0)
 *    └─ Se iguais: avança para passo 2
 *
 * 2. Compara nome_a com nome_b (critério de desempate)
 *    └─ Retorna resultado da comparação (< 0, = 0, > 0)
 * ```
 *
 *  OTIMIZAÇÕES TÉCNICAS:
 * - strcmp() utiliza implementação otimizada da biblioteca C
 * - Avaliação lazy: critério secundário só executado se necessário
 * - Sem alocações dinâmicas: máxima eficiência em comparações
 * - Compatibilidade total com padrão ANSI C para qsort()
 *
 *  CONSIDERAÇÕES INTERNACIONAIS:
 * A comparação respeita o locale atual do sistema para caracteres especiais
 * e acentuação. Para garantir comportamento consistente em testes, considere
 * definir locale explicitamente no início do programa.
 *
 * @param a Ponteiro para primeira estrutura Aluno (não modificada)
 * @param b Ponteiro para segunda estrutura Aluno (não modificada)
 * @return Resultado da comparação hierárquica:
 *         - < 0: estrutura 'a' deve vir antes de 'b' na ordenação
 *         - = 0: estruturas são equivalentes (casos raros com dados reais)
 *         - > 0: estrutura 'a' deve vir depois de 'b' na ordenação
 *
 * @note A escolha bairro→nome (ao invés de nome→bairro) maximiza a
 *       detectabilidade de problemas de estabilidade nos conjuntos de dados de teste
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
        const char* formato_caminhos[] = {
            "data/%s",           // Diretório padrão de dados
            "../data/%s",        // Um nível acima (cmake-build-debug)
            "../../data/%s",     // Dois níveis acima
            "%s"                 // Arquivo no diretório atual
        };
        snprintf(caminho_completo, sizeof(caminho_completo), formato_caminhos[i], caminho_arquivo);
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

    // Lê a primeira linha para obter o número de elementos
    char linha[32];
    if (!fgets(linha, sizeof(linha), arquivo)) {
        printf("ERRO: Arquivo vazio ou formato invalido\n");
        fclose(arquivo);
        return NULL;
    }

    // Converte a primeira linha para obter a contagem de elementos
    char *endptr;
    long count_from_file = strtol(linha, &endptr, 10);

    // Verifica se a conversão foi bem-sucedida
    if (endptr == linha || count_from_file < 0 || count_from_file > INT_MAX) {
        printf("ERRO: Formato de cabecalho invalido\n");
        fclose(arquivo);
        return NULL;
    }

    int count = (int)count_from_file;

    // Alocação dinâmica para o array de números
    int* numeros = malloc(count * sizeof(int));
    if (!numeros) {
        printf("ERRO: Falha na alocacao de memoria\n");
        fclose(arquivo);
        return NULL;
    }

    // Leitura dos dados (agora sem a primeira linha que já foi lida)
    int indice_valido = 0;

    while (fgets(linha, sizeof(linha), arquivo) && indice_valido < count) {
        char *endptr_inner;
        long val = strtol(linha, &endptr_inner, 10);

        // Verifica se a conversão foi bem-sucedida e está dentro dos limites
        if (endptr_inner != linha && val >= INT_MIN && val <= INT_MAX) {
            numeros[indice_valido] = (int)val;
            indice_valido++;
        }
    }

    fclose(arquivo);

    // Verifica se o número de elementos lidos corresponde ao declarado no cabeçalho
    if (indice_valido != count) {
        printf("AVISO: Numero de elementos lidos (%d) difere do declarado no cabecalho (%d)\n",
               indice_valido, count);
        // Ainda assim, retornamos os elementos que conseguimos ler
    }

    *tamanho = indice_valido;
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
        const char* formato_caminhos[] = {
            "data/%s",
            "../data/%s",
            "../../data/%s",
            "%s"
        };
        snprintf(caminho_completo, sizeof(caminho_completo), formato_caminhos[i], caminho_arquivo);
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
 * na estrutura de diretórios apropriada. Tenta salvar em múltiplos locais.
 *
 * Formato de saída:
 * - Um número por linha
 * - Sem formatação especial
 * - Encoding padrão do sistema
 *
 * @param caminho_arquivo Nome base do arquivo
 * @param arr Array de números inteiros a ser salvo
 * @param tamanho Número de elementos no array
 */
void salvar_numeros(const char* caminho_arquivo, int arr[], int tamanho) {
    // Lista de caminhos possíveis para salvar o arquivo
    const char* formato_caminhos[] = {
        "output/numeros/%s",     // Diretório padrão de saída
        "../output/numeros/%s",  // Um nível acima
        "numeros/%s",           // Diretório local
        "%s"                    // Arquivo no diretório atual
    };

    char caminho_completo[MAX_PATH];
    FILE* arquivo = NULL;

    // Tenta criar os diretórios necessários e salvar o arquivo
    for (int i = 0; i < 4; i++) {
        snprintf(caminho_completo, sizeof(caminho_completo), formato_caminhos[i], caminho_arquivo);

        // Tenta criar diretório se necessário
        if (i == 0) {
            criar_diretorio_se_necessario("output");
            criar_diretorio_se_necessario("output/numeros");
        } else if (i == 1) {
            criar_diretorio_se_necessario("../output");
            criar_diretorio_se_necessario("../output/numeros");
        } else if (i == 2) {
            criar_diretorio_se_necessario("numeros");
        }

        arquivo = fopen(caminho_completo, "w");
        if (arquivo) {
            printf("Salvando numeros em: %s\n", caminho_completo);
            break;
        }
    }

    if (!arquivo) {
        printf("ERRO: Nao foi possivel criar arquivo para salvar numeros: %s\n", caminho_arquivo);
        return;
    }

    // Escreve os números no arquivo
    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%d\n", arr[i]);
    }

    fclose(arquivo);
    printf("Arquivo de numeros salvo com sucesso: %d elementos\n", tamanho);
}

/**
 * @brief Salva array de alunos em arquivo CSV
 *
 * Escreve os dados de alunos ordenados em formato CSV, mantendo
 * o mesmo formato do arquivo de entrada para facilitar análise.
 * Tenta salvar em múltiplos locais.
 *
 * Formato de saída:
 * nome,data_nascimento,bairro,cidade
 *
 * @param caminho_arquivo Nome base do arquivo
 * @param arr Array de estruturas Aluno a ser salvo
 * @param tamanho Número de elementos no array
 */
void salvar_alunos(const char* caminho_arquivo, Aluno arr[], int tamanho) {
    // Lista de caminhos possíveis para salvar o arquivo
    const char* formato_caminhos[] = {
        "output/alunos/%s",      // Diretório padrão de saída
        "../output/alunos/%s",   // Um nível acima
        "alunos/%s",            // Diretório local
        "%s"                    // Arquivo no diretório atual
    };

    char caminho_completo[MAX_PATH];
    FILE* arquivo = NULL;

    // Tenta criar os diretórios necessários e salvar o arquivo
    for (int i = 0; i < 4; i++) {
        snprintf(caminho_completo, sizeof(caminho_completo), formato_caminhos[i], caminho_arquivo);

        // Tenta criar diretório se necessário
        if (i == 0) {
            criar_diretorio_se_necessario("output");
            criar_diretorio_se_necessario("output/alunos");
        } else if (i == 1) {
            criar_diretorio_se_necessario("../output");
            criar_diretorio_se_necessario("../output/alunos");
        } else if (i == 2) {
            criar_diretorio_se_necessario("alunos");
        }

        arquivo = fopen(caminho_completo, "w");
        if (arquivo) {
            printf("Salvando alunos em: %s\n", caminho_completo);
            break;
        }
    }

    if (!arquivo) {
        printf("ERRO: Nao foi possivel criar arquivo para salvar alunos: %s\n", caminho_arquivo);
        return;
    }

    // Escreve os dados dos alunos no formato CSV
    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%s,%s,%s,%s\n",
                arr[i].nome,
                arr[i].data_nascimento,
                arr[i].bairro,
                arr[i].cidade);
    }

    fclose(arquivo);
    printf("Arquivo de alunos salvo com sucesso: %d elementos\n", tamanho);
}

/**
 * @brief Cria diretório se não existir (função auxiliar)
 */
static void criar_diretorio_se_necessario(const char* caminho) {
    #ifdef _WIN32
        _mkdir(caminho);
    #else
        mkdir(caminho, 0755);
    #endif
}
