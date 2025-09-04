/**
 * ==============================================================
 * SISTEMA DE ANÁLISE DE ALGORITMOS DE ORDENAÇÃO - HEADER PRINCIPAL
 * ==============================================================
 *
 * @file sorts.h
 * @brief Header principal que unifica todos os módulos do sistema
 * @version 2.1
 * @date 2025-08-24
 *
 * Este header funciona como ponto central de integração de todos os
 * componentes do sistema. Ao incluí-lo, todos os módulos necessários
 * são automaticamente adicionados na sequência correta, seguindo
 * o princípio de arquitetura modular para melhor organização e
 * manutenção do código.
 *
 * Módulos integrados:
 * - tipos.h: Definição de estruturas de dados e tipos personalizados
 * - algoritmos.h: Implementação dos algoritmos de ordenação
 * - analise.h: Funções de medição e análise de performance
 * - io.h: Funções de entrada/saída e interface com usuário
 * - utils.h: Funções utilitárias e auxiliares
 *
 * ==============================================================
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

#define MAX_PATH 260

#endif // SORTS_H
