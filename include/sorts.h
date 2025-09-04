/**
 * ==============================================================
 * HEADER PRINCIPAL - FACADE UNIFICADO DO SISTEMA
 * ==============================================================
 *
 * @file sorts.h
 * @brief Interface unificada para todo o sistema de análise de algoritmos de ordenação
 * @author Sistema de Análise de Performance de Algoritmos de Ordenação
 *
 * Este header implementa o padrão Facade, fornecendo um ponto único de acesso
 * a todas as funcionalidades do sistema. Ao incluir apenas este arquivo,
 * o código cliente obtém acesso completo a todos os módulos especializados,
 * mantendo baixo acoplamento e alta coesão na arquitetura.
 *
 * **Vantagens da arquitetura unificada:**
 * - **Simplicidade**: Um único include para todo o sistema
 * - **Consistência**: Ordem de inclusão controlada e otimizada
 * - **Manutenibilidade**: Mudanças de dependências centralizadas
 * - **Portabilidade**: Interface estável independente da estrutura interna
 * - **Performance**: Evita inclusões redundantes e conflitos de dependência
 *
 * **Módulos integrados (ordem de dependência):**
 * 1. [`tipos.h`](include/tipos.h:1) - Tipos fundamentais e estruturas de dados
 * 2. [`algoritmos.h`](include/algoritmos.h:1) - Interfaces dos algoritmos de ordenação
 * 3. [`analise.h`](include/analise.h:1) - Sistema de medição e benchmarking
 * 4. [`io.h`](include/io.h:1) - Operações de entrada/saída e persistência
 * 5. [`utils.h`](include/utils.h:1) - Utilitários e funções auxiliares
 *
 * **Uso recomendado:**
 * ```c
 * #include "sorts.h"  // Único include necessário
 *
 * int main() {
 *     // Acesso completo a todas as funcionalidades
 *     configurar_otimizacao(1);
 *     executar_analise_completa_todos();
 *     return 0;
 * }
 * ```
 *
 * ==============================================================
 */

#ifndef SORTS_H
#define SORTS_H

// Inclusão ordenada de todos os módulos especializados do sistema
#include "tipos.h"      ///< Tipos fundamentais e estruturas de dados centrais
#include "algoritmos.h" ///< Interfaces de todos os algoritmos de ordenação
#include "analise.h"    ///< Sistema completo de análise e benchmarking
#include "io.h"         ///< Subsistema de entrada/saída e persistência
#include "utils.h"      ///< Biblioteca de utilitários e funções auxiliares

/* ================================================================
 * CONSTANTES GLOBAIS E CONFIGURAÇÕES DO SISTEMA
 * ================================================================ */

/**
 * @brief Tamanho máximo para caminhos de arquivo multiplataforma
 *
 * Define o limite máximo de caracteres para caminhos de arquivos,
 * garantindo compatibilidade entre sistemas operacionais diferentes.
 *
 * **Considerações multiplataforma:**
 * - Windows: Limite típico de 260 caracteres (MAX_PATH)
 * - Linux/Unix: Limite típico de 4096 caracteres (PATH_MAX)
 * - Este valor garante portabilidade máxima
 *
 * **Uso no sistema:**
 * - Alocação de buffers para caminhos de arquivo
 * - Validação de tamanho de paths antes de operações
 * - Prevenção de overflow em operações de string
 */
#define MAX_PATH 260

#endif // SORTS_H
