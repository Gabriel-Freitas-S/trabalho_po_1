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
 * VERSÃO 2.1 MODULAR: Estrutura Reorganizada
 * - Agora usa arquitetura modular com headers específicos
 * - Interface simplificada e focada na funcionalidade principal
 * - Sistema robusto de análise comparativa
 * - Organização automática de resultados
 *
 * EXPLICAÇÃO DIDÁTICA:
 * Este é o "coração" do programa - onde tudo começa!
 *
 * Imagine que este programa é como um laboratório de testes para algoritmos
 * de ordenação. O main.c é como o "controlador principal" que:
 * 1. Mostra um menu para o usuário escolher o que fazer
 * 2. Chama as funções certas baseado na escolha
 * 3. Organiza tudo de forma limpa e fácil de usar
 *
 * ================================================================
 */

#include "include/sorts.h"  // Inclui toda a estrutura modular

/**
 * @brief Função principal do programa
 *
 * Coordena a execução geral do sistema, apresentando interface
 * amigável ao usuário e gerenciando o fluxo principal da aplicação.
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
