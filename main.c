/**
 * ==============================================================
 * SISTEMA DE ANÁLISE DE ALGORITMOS DE ORDENAÇÃO - MÓDULO PRINCIPAL
 * ==============================================================
 *
 * @file main.c
 * @brief Programa principal para análise comparativa de algoritmos de ordenação
 * @version 2.1
 * @date 2025-08-24
 *
 * Este é o ponto de entrada do programa que gerencia:
 * - Interface com o usuário através de menus
 * - Execução dos diferentes algoritmos de ordenação
 * - Coleta e exibição de métricas de performance
 *
 * O sistema implementa 7 algoritmos clássicos de ordenação com:
 * - Versões otimizadas e não otimizadas para comparação
 * - Medição precisa de tempo de execução (nanossegundos)
 * - Contagem de comparações e trocas realizadas
 * - Relatórios detalhados para análise comparativa
 *
 * ==============================================================
 */

#include "include/sorts.h"  // Inclui toda a estrutura modular

/**
 * @brief Função principal do programa
 *
 * Coordena toda a execução do sistema, apresentando interface
 * ao usuário e gerenciando o fluxo de execução da aplicação.
 */
int main(void) {
    // Inicialização do sistema
    limpar_terminal();
    imprimir_cabecalho();

    int opcao;

    // Loop principal do programa
    do {
        imprimir_menu();
        opcao = obter_opcao_usuario();

        switch (opcao) {
            case 1:
                // Executa análise completa de todos os algoritmos
                limpar_terminal();
                imprimir_cabecalho();
                executar_relatorio_completo();
                pausar();
                break;

            case 0:
                printf("\n=== ENCERRANDO O PROGRAMA ===\n");
                printf("Obrigado por usar o Sistema de Analise de Algoritmos!\n");
                printf("Todos os resultados foram salvos na pasta 'output/'\n");
                break;

            default:
                printf("\nOPCAO INVALIDA! Por favor, escolha uma opcao valida.\n");
                printf("Dica: Digite apenas numeros (1 ou 0)\n");
                pausar();
                break;
        }

        if (opcao != 0) {
            limpar_terminal();
            imprimir_cabecalho();
        }

    } while (opcao != 0);

    return 0;
}
