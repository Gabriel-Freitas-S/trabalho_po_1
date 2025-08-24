/**
 * ================================================================
 * TRABALHO DE ALGORITMOS DE ORDENAÇÃO - IMPLEMENTAÇÕES
 * ================================================================
 *
 * @file algoritmos.c
 * @brief Implementação de 7 algoritmos de ordenação com análise de performance
 * @version 2.0
 * @date 2025-08-23
 * @author Sistema de Análise de Algoritmos
 *
 * Este módulo contém as implementações genéricas de todos os algoritmos
 * de ordenação analisados no trabalho. Cada algoritmo é implementado
 * de forma a funcionar com qualquer tipo de dados através de ponteiros
 * void e funções de comparação customizáveis.
 *
 * Características das implementações:
 * - Algoritmos genéricos que funcionam com qualquer tipo de dados
 * - Contagem automática de comparações e trocas para análise
 * - Implementações otimizadas seguindo literatura clássica
 * - Preservação da estabilidade onde aplicável
 * - Tratamento robusto de casos extremos
 *
 * Algoritmos implementados:
 * 1. Insertion Sort - Ordenação por inserção (estável)
 * 2. Bubble Sort - Ordenação por bolha (estável)
 * 3. Selection Sort - Ordenação por seleção (não-estável)
 * 4. Shaker Sort - Ordenação cocktail (estável)
 * 5. Shell Sort - Ordenação por incrementos (não-estável)
 * 6. Quick Sort - Ordenação por particionamento (não-estável)
 * 7. Heap Sort - Ordenação por heap (não-estável)
 *
 * ================================================================
 */

#include "../include/sorts.h"

/* ================================================================
 * VARIÁVEIS GLOBAIS PARA MÉTRICAS DE PERFORMANCE
 * ================================================================ */

/**
 * @var contador_comparacoes
 * @brief Contador global para operações de comparação
 *
 * Rastreia o número total de comparações realizadas durante a execução
 * de qualquer algoritmo de ordenação. Reset automaticamente antes de
 * cada teste para garantir medições precisas.
 */
long long contador_comparacoes = 0;

/**
 * @var contador_trocas
 * @brief Contador global para operações de troca/movimentação
 *
 * Rastreia o número total de trocas ou movimentações de elementos
 * realizadas durante a execução dos algoritmos. Inclui tanto trocas
 * diretas quanto movimentações complexas.
 */
long long contador_trocas = 0;

/* ================================================================
 * FUNÇÕES AUXILIARES PARA CONTAGEM E OPERAÇÕES GENÉRICAS
 * ================================================================ */

/**
 * @var funcao_comparacao_atual
 * @brief Ponteiro para a função de comparação atualmente em uso
 *
 * Variável estática que armazena a função de comparação para permitir
 * o wrapper de contagem funcionar corretamente com diferentes tipos.
 */
static CompareFn funcao_comparacao_atual = NULL;

/**
 * @brief Wrapper para função de comparação que conta automaticamente
 *
 * Esta função encapsula qualquer função de comparação para incrementar
 * automaticamente o contador de comparações. Permite medição precisa
 * do número de comparações sem modificar cada algoritmo individualmente.
 *
 * @param a Ponteiro para o primeiro elemento a ser comparado
 * @param b Ponteiro para o segundo elemento a ser comparado
 * @return Resultado da comparação: < 0 se a < b, 0 se a == b, > 0 se a > b
 */
int comparar_e_contar(const void *a, const void *b) {
    contador_comparacoes++;
    return funcao_comparacao_atual(a, b);
}

/**
 * @brief Troca dois elementos genéricos e registra a operação
 *
 * Função auxiliar que realiza a troca segura de dois elementos de
 * qualquer tipo, utilizando alocação temporária. Incrementa
 * automaticamente o contador de trocas para análise estatística.
 *
 * Características:
 * - Funciona com elementos de qualquer tamanho
 * - Aloca memória temporária de forma segura
 * - Registra automaticamente a operação para métricas
 * - Tratamento de erro em caso de falha de alocação
 *
 * @param a Ponteiro para o primeiro elemento
 * @param b Ponteiro para o segundo elemento
 * @param elem_size Tamanho em bytes de cada elemento
 */
void swap_elements(void *a, void *b, size_t elem_size) {
    // Alocação de buffer temporário
    char *temp = malloc(elem_size);
    if (!temp) {
        // Falha na alocação - operação não pode ser realizada
        return;
    }

    // Sequência de cópia tripla para troca segura
    memcpy(temp, a, elem_size);    // temp = a
    memcpy(a, b, elem_size);       // a = b
    memcpy(b, temp, elem_size);    // b = temp (valor original de a)

    // Registro da operação para análise
    contador_trocas++;

    // Liberação da memória temporária
    free(temp);
}

/* ================================================================
 * IMPLEMENTAÇÕES DOS ALGORITMOS DE ORDENAÇÃO
 * ================================================================ */

/**
 * @brief Insertion Sort - Algoritmo de ordenação por inserção
 *
 * Constrói a sequência ordenada elemento por elemento, inserindo cada
 * novo item na posição correta dentro da parte já ordenada do array.
 *
 * CARACTERÍSTICAS TÉCNICAS:
 * - Algoritmo IN-PLACE: não requer memória adicional
 * - Algoritmo ESTÁVEL: preserva ordem de elementos iguais
 * - Algoritmo ADAPTATIVO: eficiente para dados parcialmente ordenados
 *
 * ANÁLISE DE COMPLEXIDADE:
 * - Tempo melhor caso: O(n) - array já ordenado
 * - Tempo caso médio: O(n²) - elementos em ordem aleatória
 * - Tempo pior caso: O(n²) - array em ordem reversa
 * - Espaço: O(1) - apenas algumas variáveis auxiliares
 *
 * QUANDO USAR:
 * - Conjuntos pequenos de dados (n < 50)
 * - Dados parcialmente ordenados
 * - Quando estabilidade é importante
 * - Como sub-rotina de algoritmos híbridos
 *
 * @param arr Ponteiro para o array a ser ordenado
 * @param n Número de elementos no array
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação entre elementos
 */
void insertion_sort(void *arr, int n, size_t elem_size, CompareFn cmp) {
    // Configuração da função de comparação para contagem
    funcao_comparacao_atual = cmp;

    // Conversão para manipulação byte-a-byte
    char *base = (char *)arr;

    // Alocação de buffer para elemento-chave temporário
    char *key = malloc(elem_size);
    if (!key) return; // Falha na alocação

    // Iteração sobre elementos não-ordenados (começando do segundo)
    for (int i = 1; i < n; i++) {
        // Armazena elemento atual como chave a ser inserida
        memcpy(key, base + i * elem_size, elem_size);

        int j = i - 1;

        // Desloca elementos maiores que a chave para a direita
        while (j >= 0 && comparar_e_contar(base + j * elem_size, key) > 0) {
            // Movimento para direita (conta como troca)
            memcpy(base + (j + 1) * elem_size, base + j * elem_size, elem_size);
            contador_trocas++;
            j--;
        }

        // Insere chave na posição correta
        memcpy(base + (j + 1) * elem_size, key, elem_size);
        contador_trocas++; // Conta a inserção final
    }

    free(key);
}

/**
 * @brief Bubble Sort - Algoritmo de ordenação por bolha
 *
 * Compara pares de elementos adjacentes e os troca se estiverem fora
 * de ordem. Repete o processo até que nenhuma troca seja necessária.
 *
 * CARACTERÍSTICAS TÉCNICAS:
 * - Algoritmo IN-PLACE: não requer memória adicional
 * - Algoritmo ESTÁVEL: preserva ordem de elementos iguais
 * - Algoritmo com OTIMIZAÇÃO: para se array já está ordenado
 *
 * ANÁLISE DE COMPLEXIDADE:
 * - Tempo melhor caso: O(n) - com otimização, array já ordenado
 * - Tempo caso médio: O(n²) - elementos em ordem aleatória
 * - Tempo pior caso: O(n²) - array em ordem reversa
 * - Espaço: O(1) - apenas flag de controle
 *
 * QUANDO USAR:
 * - Fins educacionais (algoritmo conceptualmente simples)
 * - Conjuntos muito pequenos onde simplicidade importa mais que eficiência
 * - Quando é necessário detectar se dados já estão ordenados
 *
 * @param arr Ponteiro para o array a ser ordenado
 * @param n Número de elementos no array
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação entre elementos
 */
void bubble_sort(void *arr, int n, size_t elem_size, CompareFn cmp) {
    funcao_comparacao_atual = cmp;
    char *base = (char *)arr;

    // Otimização: flag para detectar se houve trocas
    int houve_troca;

    // Passes externos - cada pass garante que o maior elemento "borbulhe" ao final
    for (int i = 0; i < n - 1; i++) {
        houve_troca = 0;

        // Comparações internas - elementos adjacentes
        for (int j = 0; j < n - i - 1; j++) {
            // Se elementos estão fora de ordem, troca
            if (comparar_e_contar(base + j * elem_size, base + (j + 1) * elem_size) > 0) {
                swap_elements(base + j * elem_size, base + (j + 1) * elem_size, elem_size);
                houve_troca = 1;
            }
        }

        // Otimização: se não houve trocas, array já está ordenado
        if (!houve_troca) break;
    }
}

/**
 * @brief Selection Sort - Algoritmo de ordenação por seleção
 *
 * Encontra o menor elemento e o coloca na primeira posição, depois
 * encontra o segundo menor e o coloca na segunda posição, e assim
 * sucessivamente até ordenar todo o array.
 *
 * CARACTERÍSTICAS TÉCNICAS:
 * - Algoritmo IN-PLACE: não requer memória adicional
 * - Algoritmo NÃO-ESTÁVEL: pode alterar ordem de elementos iguais
 * - Número fixo de comparações independente da entrada
 *
 * ANÁLISE DE COMPLEXIDADE:
 * - Tempo melhor caso: O(n²) - sempre faz todas as comparações
 * - Tempo caso médio: O(n²) - comportamento consistente
 * - Tempo pior caso: O(n²) - comportamento consistente
 * - Espaço: O(1) - apenas índice para menor elemento
 *
 * QUANDO USAR:
 * - Quando o número de trocas deve ser minimizado (máximo n-1 trocas)
 * - Memória é extremamente limitada
 * - Performance consistente é mais importante que performance ótima
 *
 * @param arr Ponteiro para o array a ser ordenado
 * @param n Número de elementos no array
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação entre elementos
 */
void selection_sort(void *arr, int n, size_t elem_size, CompareFn cmp) {
    funcao_comparacao_atual = cmp;
    char *base = (char *)arr;

    // Para cada posição no array
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i; // Assume que o primeiro elemento é o menor

        // Encontra o menor elemento na parte não-ordenada
        for (int j = i + 1; j < n; j++) {
            if (comparar_e_contar(base + j * elem_size, base + min_idx * elem_size) < 0) {
                min_idx = j; // Atualiza índice do menor elemento
            }
        }

        // Troca apenas se necessário (otimização menor)
        if (min_idx != i) {
            swap_elements(base + i * elem_size, base + min_idx * elem_size, elem_size);
        }
    }
}

/**
 * @brief Shaker Sort - Algoritmo de ordenação cocktail (bidirecional)
 *
 * Variação melhorada do Bubble Sort que percorre o array em ambas as
 * direções alternadamente. Move elementos pequenos para o início e
 * grandes para o final simultaneamente.
 *
 * CARACTERÍSTICAS TÉCNICAS:
 * - Algoritmo IN-PLACE: não requer memória adicional
 * - Algoritmo ESTÁVEL: preserva ordem de elementos iguais
 * - Melhoria sobre Bubble Sort para alguns padrões de dados
 *
 * ANÁLISE DE COMPLEXIDADE:
 * - Tempo melhor caso: O(n) - array já ordenado
 * - Tempo caso médio: O(n²) - melhor que Bubble Sort em alguns casos
 * - Tempo pior caso: O(n²) - similar ao Bubble Sort
 * - Espaço: O(1) - variáveis de controle dos limites
 *
 * QUANDO USAR:
 * - Dados com elementos pequenos no final e grandes no início
 * - Alternativa ligeiramente melhor ao Bubble Sort
 * - Quando estabilidade é necessária mas Insertion Sort não é adequado
 *
 * @param arr Ponteiro para o array a ser ordenado
 * @param n Número de elementos no array
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação entre elementos
 */
void shaker_sort(void *arr, int n, size_t elem_size, CompareFn cmp) {
    funcao_comparacao_atual = cmp;
    char *base = (char *)arr;

    int inicio = 0;       // Limite inferior
    int fim = n - 1;      // Limite superior
    int houve_troca;

    do {
        houve_troca = 0;

        // Passa da esquerda para direita (move grandes elementos para o final)
        for (int i = inicio; i < fim; i++) {
            if (comparar_e_contar(base + i * elem_size, base + (i + 1) * elem_size) > 0) {
                swap_elements(base + i * elem_size, base + (i + 1) * elem_size, elem_size);
                houve_troca = 1;
            }
        }
        fim--; // Maior elemento já está na posição correta

        // Se não houve troca, array está ordenado
        if (!houve_troca) break;

        // Passa da direita para esquerda (move pequenos elementos para o início)
        for (int i = fim; i > inicio; i--) {
            if (comparar_e_contar(base + i * elem_size, base + (i - 1) * elem_size) < 0) {
                swap_elements(base + i * elem_size, base + (i - 1) * elem_size, elem_size);
                houve_troca = 1;
            }
        }
        inicio++; // Menor elemento já está na posição correta

    } while (houve_troca);
}

/**
 * @brief Shell Sort - Algoritmo de ordenação por incrementos
 *
 * Melhora o Insertion Sort clássico utilizando uma sequência de
 * incrementos para mover elementos para suas posições finais de
 * forma mais eficiente.
 *
 * CARACTERÍSTICAS TÉCNICAS:
 * - Algoritmo IN-PLACE: não requer memória adicional
 * - Algoritmo NÃO-ESTÁVEL: pode alterar ordem de elementos iguais
 * - Requer uma sequência de gaps (incrementos) - quanto melhor a
 *   sequência, mais eficiente o algoritmo
 *
 * ANÁLISE DE COMPLEXIDADE:
 * - Tempo melhor caso: O(n log n) - com sequência de gaps adequada
 * - Tempo caso médio: O(n log n) a O(n²) - depende da sequência
 * - Tempo pior caso: O(n²) - sequência de gaps muito ruim
 * - Espaço: O(1) - apenas algumas variáveis auxiliares
 *
 * QUANDO USAR:
 * - Dados grandes onde o Insertion Sort seria muito lento
 * - Quando a estabilidade não é crítica
 * - Como sub-rotina em algoritmos mais complexos
 *
 * @param arr Ponteiro para o array a ser ordenado
 * @param n Número de elementos no array
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação entre elementos
 */
void shell_sort(void *arr, int n, size_t elem_size, CompareFn cmp) {
    funcao_comparacao_atual = cmp;
    char *base = (char *)arr;

    // Buffer temporário para operações de movimentação
    char *temp = malloc(elem_size);
    if (!temp) return; // Falha na alocação

    // Sequência de gaps - pode ser otimizada com outras sequências
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Inserção de elementos distantes (gap apart)
        for (int i = gap; i < n; i++) {
            memcpy(temp, base + i * elem_size, elem_size);
            int j;

            // Move elementos para frente para abrir espaço
            for (j = i; j >= gap && comparar_e_contar(base + (j - gap) * elem_size, temp) > 0; j -= gap) {
                memcpy(base + j * elem_size, base + (j - gap) * elem_size, elem_size);
                contador_trocas++; // Conta movimento
            }

            // Insere o elemento temporário na posição correta
            memcpy(base + j * elem_size, temp, elem_size);
            contador_trocas++; // Conta inserção
        }
    }

    free(temp);
}

/**
 * @brief Quick Sort - Algoritmo de ordenação por particionamento
 *
 * Seleciona um "pivô" e particiona o array em duas partes: uma com
 * elementos menores que o pivô e outra com elementos maiores. O
 * processo é repetido recursivamente para as duas partes.
 *
 * CARACTERÍSTICAS TÉCNICAS:
 * - Algoritmo NÃO-ESTÁVEL: pode alterar ordem de elementos iguais
 * - Requer escolha de um bom pivô para eficiência
 * - Pode ser implementado de forma recursiva ou iterativa
 *
 * ANÁLISE DE COMPLEXIDADE:
 * - Tempo melhor caso: O(n log n) - escolha ótima de pivôs
 * - Tempo caso médio: O(n log n) - comportamento consistente
 * - Tempo pior caso: O(n²) - escolha de pivô desastrosa (ex: sempre o maior)
 * - Espaço: O(log n) a O(n) - pilha de chamadas recursivas
 *
 * QUANDO USAR:
 * - Conjuntos grandes de dados
 * - Quando a estabilidade não é crítica
 * - Quando o espaço em memória é limitado
 *
 * @param arr Ponteiro para o array a ser ordenado
 * @param inicio Índice do primeiro elemento da sub-lista
 * @param fim Índice do último elemento da sub-lista
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação entre elementos
 */
void quick_sort(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp) {
    funcao_comparacao_atual = cmp;
    if (inicio < fim) {
        // Particiona o array e obtém o índice do pivô
        int pi = partition(arr, inicio, fim, elem_size, cmp);

        // Ordena recursivamente as duas metades
        quick_sort(arr, inicio, pi - 1, elem_size, cmp);
        quick_sort(arr, pi + 1, fim, elem_size, cmp);
    }
}

/**
 * @brief Função de partição para o Quick Sort
 *
 * Seleciona o último elemento como pivô e reorganiza os elementos
 * de forma que todos os menores que o pivô fiquem à esquerda e os
 * maiores à direita. Retorna o índice final do pivô.
 *
 * @param arr Ponteiro para o array a ser particionado
 * @param inicio Índice do primeiro elemento da sub-lista
 * @param fim Índice do último elemento da sub-lista
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação entre elementos
 * @return Índice do pivô após a partição
 */
int partition(void *arr, int inicio, int fim, size_t elem_size, CompareFn cmp) {
    char *base = (char*)arr;

    // Pivô é o último elemento da sub-lista
    char *pivo = malloc(elem_size);
    if (!pivo) return inicio;

    memcpy(pivo, base + fim * elem_size, elem_size);
    int i = inicio - 1;

    // Reorganiza elementos em relação ao pivô
    for (int j = inicio; j <= fim - 1; j++) {
        if (comparar_e_contar(base + j * elem_size, pivo) < 0) {
            i++;
            swap_elements(base + i * elem_size, base + j * elem_size, elem_size);
        }
    }

    swap_elements(base + (i + 1) * elem_size, base + fim * elem_size, elem_size);

    free(pivo);
    return (i + 1);
}

/**
 * @brief Heap Sort - Algoritmo de ordenação por heap
 *
 * Constrói uma estrutura de dados do tipo heap (árvore binária completa)
 * a partir do array e, em seguida, extrai repetidamente o maior elemento
 * (para heaps máximos) ou o menor elemento (para heaps mínimos) para
 * ordenar o array.
 *
 * CARACTERÍSTICAS TÉCNICAS:
 * - Algoritmo NÃO-ESTÁVEL: pode alterar ordem de elementos iguais
 * - Requer construção de heap - pode ser otimizado com heaps parciais
 * - Pode ser implementado de forma recursiva ou iterativa
 *
 * ANÁLISE DE COMPLEXIDADE:
 * - Tempo melhor caso: O(n log n) - construção do heap eficiente
 * - Tempo caso médio: O(n log n) - comportamento consistente
 * - Tempo pior caso: O(n log n) - comportamento consistente
 * - Espaço: O(1) - apenas algumas variáveis auxiliares
 *
 * QUANDO USAR:
 * - Conjuntos grandes de dados
 * - Quando a estabilidade não é crítica
 * - Quando o espaço em memória é limitado
 *
 * @param arr Ponteiro para o array a ser ordenado
 * @param n Número de elementos no array
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação entre elementos
 */
void heap_sort(void *arr, int n, size_t elem_size, CompareFn cmp) {
    funcao_comparacao_atual = cmp;

    // Constrói heap máximo
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, elem_size, cmp);

    // Extrai elementos do heap um por um
    for (int i = n - 1; i >= 0; i--) {
        swap_elements(arr, (char*)arr + i * elem_size, elem_size);
        heapify(arr, i, 0, elem_size, cmp);
    }
}

/**
 * @brief Função auxiliar para manter propriedade heap com contagem
 *
 * Função recursiva que garante que a sub-árvore com raiz em i
 * mantenha a propriedade de heap (pai maior que filhos para heap máximo).
 *
 * @param arr Ponteiro para o array representando o heap
 * @param n Tamanho total do heap
 * @param i Índice da raiz da sub-árvore a ser ajustada
 * @param elem_size Tamanho de cada elemento em bytes
 * @param cmp Função de comparação entre elementos
 */
void heapify(void *arr, int n, int i, size_t elem_size, CompareFn cmp) {
    char *base = (char*)arr;
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < n && comparar_e_contar(base + esquerda * elem_size, base + maior * elem_size) > 0)
        maior = esquerda;

    if (direita < n && comparar_e_contar(base + direita * elem_size, base + maior * elem_size) > 0)
        maior = direita;

    if (maior != i) {
        swap_elements(base + i * elem_size, base + maior * elem_size, elem_size);
        heapify(arr, n, maior, elem_size, cmp);
    }
}
