/**
 * ================================================================
 * TRABALHO DE ALGORITMOS DE ORDENAÇÃO - MÓDULO PRINCIPAL
 * ================================================================
 *
 * @file main.c
 * @brief Programa principal para análise comparativa de algoritmos de ordenação
 * @version 2.1
 * @date 2025-08-24
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
 * - Limpeza automática da tela para melhor experiência do usuário
 * - Validação robusta de entrada do usuário
 * - Suporte para versões otimizadas e não otimizadas dos algoritmos
 *
 * Estrutura do programa:
 * 1. Inicialização e configuração da interface
 * 2. Loop principal do menu interativo
 * 3. Processamento das opções escolhidas pelo usuário
 * 4. Finalização elegante com resumo dos resultados gerados
 *
 * ================================================================
 */

#include "include/sorts.h"

// Protótipos das funções locais
void testar_algoritmos_unificado(void);
void processar_opcao(int opcao);

/**
 * @brief Função principal do programa
 *
 * Controla o fluxo principal da aplicação, gerenciando o menu
 * interativo e coordenando a execução das diferentes funcionalidades
 * disponíveis no sistema.
 *
 * Fluxo de execução:
 * 1. Limpa a tela e exibe cabeçalho informativo
 * 2. Apresenta menu de opções em loop contínuo
 * 3. Processa cada opção escolhida pelo usuário
 * 4. Limpa a tela entre operações para manter interface limpa
 * 5. Exibe mensagem de finalização com informações dos arquivos gerados
 *
 * @return SUCESSO (0) se executado com sucesso, código de erro caso contrário
 */
int main(void) {
    // Inicialização da interface do usuário
    limpar_terminal();
    imprimir_cabecalho();

    int opcao;

    // Loop principal do menu interativo
    do {
        imprimir_menu();
        opcao = obter_opcao_usuario();

        // Validação robusta de entrada do usuário
        if (opcao == -1) {
            printf("ERRO: Entrada inválida! Por favor, digite um número válido.\n");
            continue;
        }

        // Processamento da opção escolhida pelo usuário
        processar_opcao(opcao);

        // Pausa e limpeza da tela após cada operação (exceto na saída)
        if (opcao != 0) {
            pausar();
            limpar_terminal();
            imprimir_cabecalho();
        }

    } while (opcao != 0);

    // Finalização elegante do programa com informações úteis
    limpar_terminal();
    printf("\n================================================================\n");
    printf("              PROGRAMA FINALIZADO COM SUCESSO!                 \n");
    printf("================================================================\n");
    printf("Todos os resultados foram salvos na pasta 'output/' do projeto:\n");
    printf("  ├── output/numeros/     (arrays de números ordenados)\n");
    printf("  ├── output/alunos/      (dados de alunos ordenados)\n");
    printf("  └── output/relatorios/  (análises detalhadas de performance)\n");
    printf("\nObrigado por utilizar nosso sistema de análise de algoritmos!\n");

    return SUCESSO;
}

/**
 * @brief Processa a opção escolhida pelo usuário no menu principal
 *
 * Direciona a execução para a função apropriada baseada na opção
 * selecionada pelo usuário no menu interativo. Inclui validação
 * de entrada e tratamento de casos inválidos.
 *
 * @param opcao Número da opção escolhida pelo usuário (0-1)
 */
void processar_opcao(int opcao) {
    switch (opcao) {
        case 1:
            printf("\n=== EXECUTANDO RELATÓRIO COMPLETO DE ANÁLISE ===\n");
            printf("Processando versões otimizada e não otimizada de todos os algoritmos...\n");
            printf("Este processo pode levar alguns minutos dependendo do hardware.\n");
            executar_relatorio_completo();
            break;

        case 0:
            printf("\nFinalizando programa... Aguarde.\n");
            break;

        default:
            printf("ERRO: Opção inválida! Por favor, escolha entre 0 e 1.\n");
            break;
    }
}

/**
 * @brief Função de teste unificado dos algoritmos (funcionalidade futura)
 *
 * Interface planejada para testar algoritmos individualmente ou em conjunto,
 * permitindo ao usuário escolher arquivos específicos e algoritmos para análise.
 * Atualmente serve como placeholder para futuras implementações.
 *
 * @note Esta função está implementada de forma básica e pode ser expandida
 *       para incluir funcionalidades interativas mais avançadas.
 */
void testar_algoritmos_unificado(void) {
    printf("Esta função permite testar os algoritmos individualmente.\n");
    printf("Versão atual em uso: %s\n",
           usar_versao_otimizada ? "OTIMIZADA" : "NÃO OTIMIZADA");

    printf("\nImplementação básica da função de teste interativo.\n");
    printf("Para análise completa, utilize a opção 1 do menu principal.\n");

    // Exibe informações dos algoritmos disponíveis no sistema
    exibir_info_algoritmos();

    // Lista arquivos de dados disponíveis para teste
    listar_arquivos_disponiveis();
}
