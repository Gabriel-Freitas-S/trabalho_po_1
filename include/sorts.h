/**
 * ================================================================
 * TRABALHO DE ALGORITMOS DE ORDENAÇÃO - HEADER PRINCIPAL
 * ================================================================
 *
 * @file sorts.h
 * @brief Header principal que inclui todos os módulos do sistema
 * @version 2.1
 * @date 2025-08-24
 * @author Sistema de Análise de Algoritmos
 *
 * VERSÃO 2.1 - ARQUITETURA MODULAR:
 * Este arquivo agora é o ponto de entrada principal que inclui todos
 * os módulos especializados do sistema, proporcionando melhor organização
 * e manutenibilidade do código.
 *
 * MÓDULOS INCLUÍDOS:
 * - tipos.h: Estruturas de dados e definições de tipos
 * - algoritmos.h: Protótipos dos algoritmos de ordenação
 * - analise.h: Funções de medição e análise de performance
 * - io.h: Funções de entrada e saída de dados
 * - utils.h: Funções utilitárias e de comparação
 *
 * BENEFÍCIOS DA MODULARIZAÇÃO:
 * - Código mais organizado e fácil de manter
 * - Compilação mais eficiente (apenas módulos necessários)
 * - Melhor separação de responsabilidades
 * - Facilita trabalho em equipe
 * - Headers específicos para diferentes funcionalidades
 *
 * ================================================================
 */

#ifndef SORTS_H
#define SORTS_H

// Incluir todos os módulos especializados
#include "tipos.h"      // Estruturas e tipos fundamentais
#include "algoritmos.h" // Algoritmos de ordenação
#include "analise.h"    // Sistema de análise e métricas
#include "io.h"         // Entrada e saída de dados
#include "utils.h"      // Funções utilitárias

/* ================================================================
 * CONSTANTES DO SISTEMA
 * ================================================================ */

#define NUM_ALGORITMOS 7
#define MAX_PATH 260

#endif // SORTS_H
