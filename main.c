/**
 * ================================================================
 * TRABALHO DE ALGORITMOS DE ORDENAÇÃO - MÓDULO PRINCIPAL
 * ================================================================
 *
 * @file main.c
 * @brief Programa principal para análise comparativa de algoritmos de ordenação
 * @version 2.0
 * @date 2025-08-23
 * @author Sistema de Análise de Algoritmos
 *
 * Este módulo implementa a interface principal do sistema de análise
 * de algoritmos de ordenação. Oferece um menu interativo que permite
 * ao usuário testar algoritmos individualmente ou executar análises
 * completas automatizadas.
 *
 * Funcionalidades principais:
 * - Interface de linha de comando limpa e intuitiva
 * - Teste individual de algoritmos com dados customizados
 * - Relatório completo automatizado de todos os algoritmos
 * - Limpeza automática da tela para melhor experiência
 * - Validação robusta de entrada do usuário
 *
 * Estrutura do programa:
 * 1. Inicialização e limpeza da tela
 * 2. Loop principal do menu interativo
 * 3. Processamento das opções escolhidas
 * 4. Finalização elegante com resumo dos resultados
 *
 * ================================================================
 */

#include "include/sorts.h"

// Protótipos das funções locais
void testar_algoritmos_unificado();
void processar_opcao(int opcao);

/**
 * @brief Função principal do programa
 *
 * Controla o fluxo principal da aplicação, gerenciando o menu
 * interativo e coordenando a execução das diferentes funcionalidades.
 *
 * Fluxo de execução:
 * 1. Limpa a tela e exibe cabeçalho
 * 2. Apresenta menu de opções em loop
 * 3. Processa cada opção escolhida pelo usuário
 * 4. Limpa a tela entre operações para manter interface limpa
 * 5. Exibe mensagem de finalização elegante
 *
 * @return SUCESSO (0) se executado com sucesso
 */
int main(void) {
    // Inicialização da interface
    limpar_terminal();
    imprimir_cabecalho();

    int opcao;

    // Loop principal do menu interativo
    do {
        imprimir_menu();
        opcao = obter_opcao_usuario();

        // Validação de entrada
        if (opcao == -1) {
            printf("ERRO: Entrada invalida! Digite um numero.\n");
            continue;
        }

        // Processamento da opção escolhida
        processar_opcao(opcao);

        // Pausa e limpeza da tela após cada operação (exceto saída)
        if (opcao != 0) {
            pausar();
            limpar_terminal();
            imprimir_cabecalho();
        }

    } while (opcao != 0);

    // Finalização elegante do programa
    limpar_terminal();
    printf("\n================================================================\n");
    printf("              PROGRAMA FINALIZADO COM SUCESSO!                 \n");
    printf("================================================================\n");
    printf("Todos os resultados estao salvos na pasta 'output/'\n");
    printf("  - output/numeros/     (dados ordenados)\n");
    printf("  - output/alunos/      (dados de alunos)\n");
    printf("  - output/relatorios/  (analises detalhadas)\n");
    printf("\nObrigado por usar nosso sistema!\n");

    return SUCESSO;
}

/**
 * @brief Processa a opção escolhida pelo usuário no menu principal
 *
 * Direciona a execução para a função apropriada baseada na opção
 * selecionada pelo usuário. Inclui validação de entrada e tratamento
 * de opções inválidas.
 *
 * Opções disponíveis:
 * - 1: Teste individual de algoritmos com arquivo customizado
 * - 2: Relatório completo automatizado de todos os cenários
 * - 0: Finalizar programa
 *
 * @param opcao Número da opção escolhida pelo usuário
 */
void processar_opcao(int opcao) {
    switch (opcao) {
        case 1:
            // Teste individual interativo
            testar_algoritmos_unificado();
            break;

        case 2:
            // Relatório completo automatizado
            executar_relatorio_completo();
            break;

        case 0:
            // Finalizar programa - não faz nada, retorna ao main
            break;

        default:
            // Opção inválida
            printf("ERRO: Opcao invalida! Escolha entre 0-2.\n");
    }
}

/**
 * @brief Interface unificada para teste interativo de algoritmos
 *
 * Permite ao usuário escolher o tipo de dados (números ou alunos)
 * e o arquivo específico para testar todos os algoritmos de ordenação.
 * Fornece feedback detalhado sobre arquivos disponíveis e resultados.
 *
 * Funcionalidades:
 * - Listagem de arquivos disponíveis para orientar o usuário
 * - Suporte para dados numéricos e estruturas de alunos
 * - Validação robusta de entrada e arquivos
 * - Execução automática de análise de estabilidade para alunos
 * - Criação automática de diretórios de saída
 *
 * Tipos de dados suportados:
 * 1. Números inteiros (arquivos numeros_*.txt)
 * 2. Dados de alunos (arquivo alunos.txt)
 */
void testar_algoritmos_unificado() {
    // Garantia de estrutura de diretórios
    criar_diretorios_output();

    printf("\n=== TESTE DE ALGORITMOS DE ORDENACAO ===\n");

    // Orientação ao usuário sobre arquivos disponíveis
    listar_arquivos_disponiveis();

    printf("\n=== TIPOS DE DADOS DISPONIVEIS ===\n");
    printf("1. Numeros (arquivos: numeros_*.txt)\n");
    printf("2. Alunos (arquivo: alunos.txt)\n");
    printf("Escolha o tipo (1 ou 2): ");

    int tipo;
    if (scanf("%d", &tipo) != 1) {
        printf("ERRO: Entrada invalida.\n");
        return;
    }

    if (tipo == 1) {
        // ========== PROCESSAMENTO DE DADOS NUMÉRICOS ==========
        char nome_arquivo[100];
        printf("\nDigite o nome do arquivo de numeros (ex: numeros_pequeno.txt): ");
        if (scanf("%99s", nome_arquivo) != 1) {
            printf("ERRO: Nao foi possivel ler nome do arquivo.\n");
            return;
        }

        // Carregamento dos dados numéricos
        int tamanho;
        int* dados = ler_numeros(nome_arquivo, &tamanho);

        if (!dados) {
            printf("ERRO: Nao foi possivel carregar o arquivo.\n");
            printf("Dica: Certifique-se de que o arquivo esta na pasta 'data/'\n");
            return;
        }

        // Execução dos testes
        printf("\nIniciando testes com %d numeros...\n", tamanho);
        executar_todos_algoritmos(dados, tamanho, sizeof(int), comparar_inteiros,
                                "numeros", nome_arquivo);
        free(dados);

    } else if (tipo == 2) {
        // ========== PROCESSAMENTO DE DADOS DE ALUNOS ==========
        char nome_arquivo[100];
        printf("\nDigite o nome do arquivo de alunos (ex: alunos.txt): ");
        if (scanf("%99s", nome_arquivo) != 1) {
            printf("ERRO: Nao foi possivel ler nome do arquivo.\n");
            return;
        }

        // Carregamento dos dados de alunos
        int tamanho;
        Aluno* dados = ler_alunos(nome_arquivo, &tamanho);

        if (!dados) {
            printf("ERRO: Nao foi possivel carregar o arquivo de alunos.\n");
            printf("Dica: O arquivo deve estar na pasta 'data/' no formato correto\n");
            printf("   Formato esperado: nome,data_nascimento,bairro,cidade\n");
            return;
        }

        // Informações sobre critério de ordenação
        printf("\nCriterio de ordenacao para alunos:\n");
        printf("  1. Primario: BAIRRO (ordem alfabetica)\n");
        printf("  2. Secundario: NOME (ordem alfabetica)\n");
        printf("\nIniciando testes com %d alunos...\n", tamanho);

        // Execução dos testes
        executar_todos_algoritmos(dados, tamanho, sizeof(Aluno), comparar_alunos,
                                "alunos", nome_arquivo);

        // Análise automática de estabilidade para dados de alunos
        printf("\n=== ANALISE DE ESTABILIDADE (automatica) ===\n");
        printf("Verificando preservacao da ordem relativa de elementos iguais...\n");
        analisar_estabilidade();

        free(dados);

    } else {
        // Tipo inválido
        printf("ERRO: Tipo invalido! Escolha 1 para numeros ou 2 para alunos.\n");
    }
}
