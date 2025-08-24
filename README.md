# 🔄 Sistema de Análise de Algoritmos de Ordenação

[![C](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Version](https://img.shields.io/badge/Version-2.0-green.svg)]()
[![License](https://img.shields.io/badge/License-Academic-yellow.svg)]()

## 📋 Índice

1. [Sobre o Projeto](#-sobre-o-projeto)
2. [Características Principais](#-características-principais)
3. [Algoritmos Implementados](#-algoritmos-implementados)
4. [Estrutura do Projeto](#-estrutura-do-projeto)
5. [Compilação e Execução](#-compilação-e-execução)
6. [Manual de Uso](#-manual-de-uso)
7. [Análise de Dados](#-análise-de-dados)
8. [Arquivos de Saída](#-arquivos-de-saída)
9. [Documentação Técnica](#-documentação-técnica)
10. [Métricas Analisadas](#-métricas-analisadas)

## 🎯 Sobre o Projeto

Este sistema implementa uma **análise comparativa completa** de 7 algoritmos clássicos de ordenação, desenvolvido em linguagem C com foco em **performance, precisão e usabilidade**. O projeto oferece uma interface interativa que permite testar algoritmos individualmente ou executar análises automatizadas completas.

### 🎓 Objetivos Acadêmicos

- **Comparar empiricamente** diferentes algoritmos de ordenação
- **Medir precisamente** tempo de execução, comparações e trocas
- **Analisar estabilidade** dos algoritmos com dados reais
- **Gerar relatórios detalhados** para análise acadêmica
- **Demonstrar implementações genéricas** que funcionam com qualquer tipo de dados

## ✨ Características Principais

### 🚀 **Interface Moderna**
- Menu interativo limpo e intuitivo
- Limpeza automática de tela para melhor experiência
- Validação robusta de entrada do usuário
- Feedback detalhado sobre operações

### 📊 **Análise Precisa**
- Medição de tempo com precisão de **microssegundos**
- Contagem exata de **comparações** e **trocas**
- Análise automática de **estabilidade**
- Métricas de eficiência relativa (operações por elemento)

### 📁 **Organização Automática**
- Criação automática de estrutura de diretórios
- Separação de resultados por categoria
- Nomenclatura consistente de arquivos
- Relatórios em formato texto legível

### 🔧 **Implementação Técnica**
- Algoritmos **genéricos** (funcionam com qualquer tipo de dados)
- Uso de **ponteiros void** e funções de comparação
- Tratamento robusto de **erros e casos extremos**
- Código modular e bem documentado

## 🔢 Algoritmos Implementados

| Algoritmo | Estabilidade | Melhor Caso | Caso Médio | Pior Caso | Espaço |
|-----------|--------------|-------------|------------|-----------|---------|
| **Insertion Sort** | ✅ Estável | O(n) | O(n²) | O(n²) | O(1) |
| **Bubble Sort** | ✅ Estável | O(n) | O(n²) | O(n²) | O(1) |
| **Selection Sort** | ❌ Não-Estável | O(n²) | O(n²) | O(n²) | O(1) |
| **Shaker Sort** | ✅ Estável | O(n) | O(n²) | O(n²) | O(1) |
| **Shell Sort** | ❌ Não-Estável | O(n log n) | O(n^1.25) | O(n²) | O(1) |
| **Quick Sort** | ❌ Não-Estável | O(n log n) | O(n log n) | O(n²) | O(log n) |
| **Heap Sort** | ❌ Não-Estável | O(n log n) | O(n log n) | O(n log n) | O(1) |

### 📝 **Detalhes dos Algoritmos**

#### 🔸 **Insertion Sort**
- **Quando usar**: Conjuntos pequenos (n < 50), dados parcialmente ordenados
- **Vantagem**: Muito eficiente para pequenos datasets e dados quase ordenados
- **Características**: In-place, estável, adaptativo

#### 🔸 **Bubble Sort**  
- **Quando usar**: Fins educacionais, detecção de dados já ordenados
- **Vantagem**: Algorítmo mais simples conceptualmente
- **Características**: In-place, estável, com otimização para dados ordenados

#### 🔸 **Selection Sort**
- **Quando usar**: Quando número de trocas deve ser minimizado
- **Vantagem**: Máximo n-1 trocas, comportamento consistente
- **Características**: In-place, não-estável, comparações fixas

#### 🔸 **Shaker Sort (Cocktail Sort)**
- **Quando usar**: Alternativa melhorada ao Bubble Sort
- **Vantagem**: Elementos pequenos no final são movidos mais rapidamente
- **Características**: In-place, estável, bidirecional

#### 🔸 **Shell Sort**
- **Quando usar**: Dados grandes onde Insertion Sort seria lento
- **Vantagem**: Melhoria significativa sobre Insertion Sort
- **Características**: In-place, não-estável, usa sequência de incrementos

#### 🔸 **Quick Sort**
- **Quando usar**: Conjuntos grandes, quando espaço é limitado
- **Vantagem**: Excelente performance média, baixo uso de memória
- **Características**: Divide-e-conquista, não-estável, recursivo

#### 🔸 **Heap Sort**
- **Quando usar**: Quando garantia de O(n log n) é necessária
- **Vantagem**: Performance garantida em todos os casos
- **Características**: In-place, não-estável, usa estrutura heap

## 📂 Estrutura do Projeto

```
trabalho-po-1/
├── 📁 include/
│   └── sorts.h                 # Cabeçalho principal com todas as definições
├── 📁 src/
│   ├── algoritmos.c           # Implementações dos 7 algoritmos
│   ├── analise.c              # Sistema de medição e relatórios
│   ├── io.c                   # Funções de entrada/saída de dados
│   └── utils.c                # Utilitários e interface do usuário
├── 📁 data/                   # Arquivos de entrada para testes
│   ├── alunos.txt            # Dados de alunos para teste de estabilidade
│   ├── numeros_pequeno.txt   # Conjunto pequeno (100 elementos)
│   ├── numeros_medio.txt     # Conjunto médio (1.000 elementos)
│   ├── numeros_grande.txt    # Conjunto grande (10.000 elementos)
│   ├── numeros_ordenados.txt # Dados já ordenados (melhor caso)
│   ├── numeros_reversos.txt  # Dados em ordem reversa (pior caso)
│   └── numeros_duplicados.txt # Dados com elementos repetidos
├── 📁 output/                # Diretório de saída (criado automaticamente)
│   ├── 📁 numeros/           # Arrays ordenados de números
│   ├── 📁 alunos/            # Arrays ordenados de alunos
│   └── 📁 relatorios/        # Relatórios de análise detalhados
├── main.c                    # Programa principal com menu interativo
├── CMakeLists.txt           # Configuração de compilação
└── README.md                # Este arquivo
```

## 🔧 Compilação e Execução

### **Pré-requisitos**
- Compilador C (GCC, Clang, MSVC)
- CMake 3.10 ou superior (opcional)
- Sistema operacional: Windows, Linux, macOS

### **Opção 1: Compilação com CMake (Recomendado)**
```bash
mkdir build
cd build
cmake ..
make
./trabalho_po_1
```

### **Opção 2: Compilação Manual**
```bash
# Linux/macOS
gcc -o programa main.c src/*.c -I include

# Windows
gcc -o programa.exe main.c src/*.c -I include
```

### **Opção 3: Visual Studio/CLion**
- Abra o projeto no IDE
- Configure CMake se necessário
- Compile e execute (Ctrl+F5 / Shift+F10)

## 📖 Manual de Uso

### **🏠 Menu Principal**

Ao executar o programa, você verá:

```
================================================================
              TRABALHO DE ALGORITMOS DE ORDENACAO              
                     Programacao - 2025                        
                    Estrutura Otimizada                        
================================================================

================================================================
                        MENU PRINCIPAL                         
================================================================
  1. Testar algoritmos de ordenacao                            
  2. Gerar relatorio completo de todos os testes               
  0. Sair do programa                                           
================================================================
Escolha uma opcao: 
```

### **1️⃣ Teste Individual de Algoritmos**

Esta opção permite testar todos os algoritmos com um arquivo específico:

1. **Escolha o tipo de dados:**
   - `1` para números inteiros
   - `2` para dados de alunos

2. **Digite o nome do arquivo** (exemplo: `numeros_pequeno.txt`)

3. **Visualize os resultados:**
   - Tabela comparativa em tempo real
   - Rankings por tempo, comparações e trocas
   - Análise de estabilidade (para alunos)

### **2️⃣ Relatório Completo Automatizado**

Executa todos os testes disponíveis automaticamente:

- ✅ Testa **todos os arquivos de números** disponíveis
- ✅ Testa **arquivo de alunos** se disponível  
- ✅ Gera **relatórios detalhados** para cada teste
- ✅ Executa **análise de estabilidade** automaticamente
- ✅ Organiza **arquivos de saída** por categoria

### **🎨 Interface Visual**

- **Limpeza automática** da tela entre operações
- **Tabelas formatadas** para fácil leitura
- **Códigos de cores** conceituais (verde ✅ / vermelho ❌)
- **Feedback em tempo real** sobre operações
- **Validação de entrada** com mensagens claras

## 📊 Análise de Dados

### **📈 Tipos de Dados Suportados**

#### **🔢 Números Inteiros**
- Arquivos formato texto, um número por linha
- Suporte a números negativos e zeros
- Detecção automática do tamanho do conjunto

**Exemplo de arquivo:**
```
1507
892  
1234
567
-42
```

#### **👥 Dados de Alunos**
- Formato CSV: `nome,data_nascimento,bairro,cidade`
- Ordenação primária por **bairro**, secundária por **nome**
- Ideal para demonstração de estabilidade

**Exemplo de arquivo:**
```
João Silva,15/03/1995,Centro,São Paulo
Maria Santos,22/07/1994,Vila Nova,São Paulo  
Pedro Costa,10/01/1996,Centro,São Paulo
```

### **🔍 Cenários de Teste Incluídos**

| Arquivo | Descrição | Propósito |
|---------|-----------|-----------|
| `numeros_pequeno.txt` | 100 elementos | Teste básico, comparação geral |
| `numeros_medio.txt` | 1.000 elementos | Análise de escalabilidade |
| `numeros_grande.txt` | 10.000 elementos | Performance com grandes volumes |
| `numeros_ordenados.txt` | Dados já ordenados | Análise do melhor caso |
| `numeros_reversos.txt` | Ordem reversa | Análise do pior caso |
| `numeros_duplicados.txt` | Elementos repetidos | Comportamento com duplicatas |
| `alunos.txt` | Dados estruturados | Análise de estabilidade |

## 📤 Arquivos de Saída

O sistema organiza automaticamente todos os resultados:

### **📁 output/numeros/**
Contém arrays ordenados de números por cada algoritmo:
- `Insertion_Sort_numeros_numeros_pequeno.txt`
- `Quick_Sort_numeros_numeros_grande.txt`
- etc.

### **📁 output/alunos/**
Contém dados de alunos ordenados:
- `Bubble_Sort_alunos_alunos.txt`
- `Heap_Sort_alunos_alunos.txt`
- etc.

### **📁 output/relatorios/**
Relatórios detalhados de análise:
- `relatorio_numeros_numeros_pequeno.txt`
- `relatorio_alunos_alunos.txt`
- etc.

### **📄 Exemplo de Relatório**

```
RELATORIO COMPLETO DE ANALISE - ALGORITMOS DE ORDENACAO
=======================================================

Data de Execucao: Aug 23 2025
Tipo de Dados: numeros
Tamanho do Conjunto: 1000 elementos

METRICAS DETALHADAS POR ALGORITMO
=================================

Algoritmo: Quick Sort
Complexidade Media: O(n log n)
Estabilidade: NAO ESTAVEL
Tempo de Execucao: 0.002341 segundos
Numero de Comparacoes: 9.847
Numero de Trocas: 2.934
Comparacoes por Elemento: 9.85
Trocas por Elemento: 2.93
---------------------------------------------------

ANALISE COMPARATIVA
===================

MELHOR TEMPO: Quick Sort (0.002341 segundos)
PIOR TEMPO: Bubble Sort (0.145623 segundos)

MENOS COMPARACOES: Insertion Sort (4.521 comparacoes)
MAIS COMPARACOES: Selection Sort (499.500 comparacoes)
```

## 🔧 Documentação Técnica

### **🏗️ Arquitetura do Sistema**

#### **📋 sorts.h - Cabeçalho Principal**
- Definições de todas as estruturas
- Protótipos de funções
- Constantes e macros
- Documentação estilo Doxygen

#### **⚙️ algoritmos.c - Implementações**
- 7 algoritmos implementados genericamente  
- Contadores automáticos de operações
- Tratamento robusto de erros
- Otimizações específicas por algoritmo

#### **📊 analise.c - Sistema de Medição**
- Medição precisa de tempo com `clock()`
- Execução automatizada em batches
- Geração de relatórios formatados
- Análise de estabilidade com casos reais

#### **💾 io.c - Entrada/Saída**
- Leitura de arquivos com múltiplos formatos
- Salvamento organizado por categoria
- Detecção automática de tipos
- Tratamento de erros de I/O

#### **🎮 utils.c - Interface e Utilitários**
- Menu interativo responsivo
- Funções de limpeza de tela
- Validação de entrada robusta
- Criação automática de diretórios

#### **🚀 main.c - Programa Principal**
- Loop principal do menu
- Coordenação entre módulos
- Gerenciamento de estado
- Finalização elegante

### **🔄 Fluxo de Execução**

1. **Inicialização**: Limpeza da tela e exibição do cabeçalho
2. **Menu Principal**: Apresentação das opções disponíveis
3. **Processamento**: Execução da opção escolhida
4. **Análise**: Medição e coleta de métricas
5. **Relatórios**: Geração e salvamento de resultados
6. **Feedback**: Exibição de resultados ao usuário
7. **Loop**: Retorno ao menu ou finalização

### **🧮 Algoritmos Genéricos**

Todos os algoritmos foram implementados usando:

```c
void algoritmo(void *arr, int n, size_t elem_size, CompareFn cmp)
```

**Vantagens desta abordagem:**
- ✅ **Reutilização**: O mesmo código funciona para `int`, `Aluno`, etc.
- ✅ **Manutenibilidade**: Uma única implementação por algoritmo
- ✅ **Extensibilidade**: Fácil adição de novos tipos de dados
- ✅ **Precisão**: Contadores automáticos sem duplicação de código

## 📏 Métricas Analisadas

### **⏱️ Tempo de Execução**
- **Precisão**: Microssegundos  
- **Tipo**: Tempo de CPU (não wall clock)
- **Medição**: Função `clock()` da biblioteca padrão
- **Overhead**: Mínimo (duas chamadas de sistema)

### **🔄 Número de Comparações**
- **Definição**: Chamadas à função de comparação
- **Implementação**: Wrapper automático transparente
- **Precisão**: Contagem exata sem overhead
- **Uso**: Análise teórica vs. prática

### **↔️ Número de Trocas**
- **Definição**: Movimentações de elementos
- **Inclui**: Trocas diretas e movimentações complexas
- **Implementação**: Contagem na função `swap_elements()`
- **Aplicação**: Análise de operações de memória

### **🎯 Análise de Estabilidade**
- **Método**: Teste com dados de alunos duplicados
- **Verificação**: Visual e automática
- **Importância**: Crítica para ordenações por múltiplos critérios
- **Resultado**: Classificação binária (estável/não-estável)

### **📈 Eficiência Relativa**
- **Comparações por elemento**: `total_comparações / n`
- **Trocas por elemento**: `total_trocas / n`
- **Uso**: Normalização para comparação entre conjuntos
- **Interpretação**: Menor valor = maior eficiência

---

## 🎓 Conclusão Acadêmica

Este sistema oferece uma plataforma completa para **análise empírica** de algoritmos de ordenação, permitindo:

- **Verificação prática** das complexidades teóricas
- **Comparação objetiva** entre diferentes abordagens  
- **Compreensão visual** do comportamento dos algoritmos
- **Análise quantitativa** com métricas precisas
- **Documentação automática** para relatórios acadêmicos

### 🔍 **Insights Obtidos**

- **Quick Sort** geralmente oferece melhor performance prática
- **Insertion Sort** é extremamente eficiente para pequenos conjuntos
- **Bubble Sort** é útil apenas para fins educacionais
- **Heap Sort** garante performance consistente
- **Estabilidade** é crucial em aplicações do mundo real

---

**📧 Contato**: Sistema de Análise de Algoritmos  
**📅 Data**: Agosto de 2025  
**🔖 Versão**: 2.0  
**📜 Licença**: Uso Acadêmico

---

*"A medição precisa é o fundamento de toda ciência."* - Lord Kelvin
