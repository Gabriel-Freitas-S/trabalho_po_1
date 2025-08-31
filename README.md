# Sistema de Análise de Algoritmos de Ordenação

![Badge Linguagem](https://img.shields.io/badge/linguagem-C-blue)

## 📝 Sumário
- [Descrição](#-descrição)
- [Objetivos do Trabalho](#-objetivos-do-trabalho)
- [Algoritmos Implementados](#-algoritmos-implementados)
- [Conjuntos de Dados](#-conjuntos-de-dados)
- [Funcionalidades](#-funcionalidades)
- [Estrutura do Projeto](#-estrutura-do-projeto)
- [Requisitos de Sistema](#-requisitos-de-sistema)
- [Como Compilar e Executar](#-como-compilar-e-executar)
- [Arquivos de Entrada](#-arquivos-de-entrada)
- [Arquivos de Saída](#-arquivos-de-saída)
- [Análises Realizadas](#-análises-realizadas)
- [Análise de Estabilidade](#-análise-de-estabilidade)
- [Metodologia](#-metodologia)
- [Resultados](#-resultados)
- [Contribuidores](#-contribuidores)

## 📋 Descrição

Este sistema foi desenvolvido como trabalho acadêmico para a **Disciplina: Pesquisa e Ordenação**, focado na **Implementação e Análise Comparativa de Algoritmos de Ordenação**. O projeto implementa, analisa e documenta o comportamento de 7 algoritmos clássicos de ordenação, conforme especificado no enunciado do trabalho.

## 🎯 Objetivos do Trabalho

O objetivo principal é implementar os algoritmos de ordenação especificados e realizar uma análise comparativa dos tempos de execução entre eles, considerando diferentes conjuntos de dados de entrada. 

### Objetivos Específicos:
- **Medição precisa de tempo**: Contabilizar exclusivamente o tempo de execução da ordenação, desconsiderando o tempo de leitura dos arquivos
- **Análise comparativa**: Comparar o desempenho dos algoritmos em diferentes cenários de entrada
- **Avaliação de estabilidade**: Analisar o conceito de estabilidade dos algoritmos, especialmente na ordenação de registros de alunos
- **Geração de relatórios**: Produzir gráficos comparativos e análises detalhadas

## 🔄 Algoritmos Implementados

Conforme especificação do trabalho, foram implementados os seguintes algoritmos de ordenação:

| Algoritmo          | Nome Técnico        | Estabilidade | Complexidade Média | Características                                      |
|--------------------|---------------------|--------------|--------------------|------------------------------------------------------|
| **Insertion Sort** | Inserção Direta     | Estável      | O(n²)              | Eficiente para conjuntos pequenos ou quase ordenados |
| **Bubble Sort**    | Ordenação por Bolha | Estável      | O(n²)              | Algoritmo didático, simples de compreender           |
| **Selection Sort** | Seleção Direta      | Não-estável  | O(n²)              | Minimiza número de trocas                            |
| **Shaker Sort**    | Ordenação Coquetel  | Estável      | O(n²)              | Melhoria bidirecional do Bubble Sort                 |
| **Shell Sort**     | Ordenação Shell     | Não-estável  | O(n log² n)        | Melhoria do Insertion Sort com gaps                  |
| **Quick Sort**     | Ordenação Rápida    | Não-estável  | O(n log n)         | Eficiente para grandes volumes de dados              |
| **Heap Sort**      | Ordenação por Heap  | Não-estável  | O(n log n)         | Garante performance no pior caso                     |

### Implementação
Cada algoritmo foi **implementado integralmente pelo desenvolvedor**, sem uso de bibliotecas prontas de ordenação, conforme exigido nas especificações do trabalho.

## 📊 Conjuntos de Dados

Os conjuntos de dados utilizados seguem exatamente a especificação do trabalho:

### Arquivos 1 a 12: Listas Numéricas
- **500, 5000, 10000 e 50000 números** em três configurações:
  - **Aleatórios**: `numeros_aleatorios_[tamanho].txt`
  - **Ordenados crescente**: `numeros_crescentes_[tamanho].txt`
  - **Ordenados decrescente**: `numeros_decrescentes_[tamanho].txt`

### Arquivo 13: Cadastro de Alunos
- **1000 registros** com campos: Nome, Sexo, Data de nascimento, Cidade
- **Critério de ordenação**: Por cidade e, dentro de cada cidade, por nome
- **Formato**: Campos separados por vírgulas

## ⚙️ Funcionalidades

- **Medição precisa de tempo**: Utilização da função `clock()` da biblioteca `<time.h>` para medir exclusivamente o tempo de ordenação
- **Análise detalhada**: Contagem de comparações e trocas realizadas por cada algoritmo
- **Testes abrangentes**: Execução em todos os conjuntos de dados especificados
- **Geração de arquivos de saída**: Criação automática de arquivos com dados ordenados
- **Análise de estabilidade**: Verificação e demonstração da propriedade de estabilidade
- **Relatórios comparativos**: Geração de dados para criação de gráficos comparativos

## 📁 Estrutura do Projeto

```
trabalho-po-1/
├── CMakeLists.txt              # Configuração de compilação
├── main.c                      # Programa principal
├── include/                    # Arquivos de cabeçalho
│   ├── algoritmos.h            # Declaração dos algoritmos de ordenação
│   ├── analise.h               # Sistema de análise e medição
│   ├── io.h                    # Entrada/Saída de dados
│   ├── sorts.h                 # Header principal unificado
│   ├── tipos.h                 # Definições de tipos e estruturas
│   └── utils.h                 # Funções utilitárias
├── src/                        # Código fonte
│   ├── algoritmos.c            # Implementação dos algoritmos
│   ├── analise.c               # Funções de análise e relatórios
│   ├── io.c                    # Implementação de E/S
│   └── utils.c                 # Implementação de utilitários
├── data/                       # Dados de entrada (conforme especificação)
│   ├── numeros_aleatorios_500.txt        # 500 números aleatórios
│   ├── numeros_aleatorios_5000.txt       # 5.000 números aleatórios
│   ├── numeros_aleatorios_10000.txt      # 10.000 números aleatórios
│   ├── numeros_aleatorios_50000.txt      # 50.000 números aleatórios
│   ├── numeros_crescentes_500.txt        # 500 números crescentes
│   ├── numeros_crescentes_5000.txt       # 5.000 números crescentes
│   ├── numeros_crescentes_10000.txt      # 10.000 números crescentes
│   ├── numeros_crescentes_50000.txt      # 50.000 números crescentes
│   ├── numeros_decrescentes_500.txt      # 500 números decrescentes
│   ├── numeros_decrescentes_5000.txt     # 5.000 números decrescentes
│   ├── numeros_decrescentes_10000.txt    # 10.000 números decrescentes
│   ├── numeros_decrescentes_50000.txt    # 50.000 números decrescentes
│   └── registros_pessoas_1000.txt        # 1.000 registros de alunos
└── output/                     # Resultados gerados
    ├── alunos/                 # Resultados para cadastro de alunos
    ├── numeros/                # Resultados para dados numéricos
    └── relatorios/             # Relatórios consolidados e dados para gráficos
```

## 💻 Requisitos de Sistema

- **Linguagem**: C (conforme especificação do trabalho)
- **Compilador**: GCC ou equivalente compatível com C99+
- **Sistema Operacional**: Windows, Linux ou macOS
- **CMake**: 3.10 ou superior (opcional para compilação)
- **Memória**: 2GB de RAM (mínimo)
- **Espaço em disco**: 100MB para o projeto e resultados

## 🚀 Como Compilar e Executar

### Usando CMake (Recomendado)

```bash
# Configure o CMake
mkdir -p build && cd build
cmake ..

# Compile o projeto
cmake --build .

# Execute o programa
./trabalho_po_1
```

### Compilação Manual

```bash
# Compile todos os arquivos fonte
gcc -o trabalho_po_1 main.c src/*.c -I./include -std=c99 -O2

# Execute o programa
./trabalho_po_1
```

## 📄 Arquivos de Entrada

### Formato dos Arquivos Numéricos
```
[número_de_elementos]
[elemento_1]
[elemento_2]
...
[elemento_n]
```

### Formato do Arquivo de Alunos
```
[número_de_registros]
Nome,Sexo,Data_nascimento,Cidade
Nome,Sexo,Data_nascimento,Cidade
...
```

## 📤 Arquivos de Saída

O programa gera automaticamente:
- **Dados ordenados**: Arquivos com os resultados da ordenação
- **Métricas de performance**: Tempo de execução, comparações e trocas
- **Dados para gráficos**: Informações estruturadas para análise comparativa
- **Análise de estabilidade**: Exemplos demonstrando estabilidade/não-estabilidade

## 📊 Análises Realizadas

### 1. Medição de Tempo
- Uso exclusivo da função `clock()` da biblioteca `<time.h>`
- Medição apenas do tempo de ordenação (excluindo leitura de arquivos)
- Precisão em microssegundos

### 2. Análise de Performance
- **Comparações realizadas**: Contagem exata de operações de comparação
- **Trocas realizadas**: Número de movimentações de elementos
- **Comportamento por tipo de entrada**: Análise diferenciada para dados aleatórios, ordenados e reversos

### 3. Análise por Tamanho de Entrada
- Comportamento com 500, 5000, 10000 e 50000 elementos
- Geração de dados para gráficos comparativos (tempo × tamanho da entrada)

## 🔄 Análise de Estabilidade

### Conceito de Estabilidade
Um algoritmo é **estável** se mantém a ordem relativa de elementos com valores iguais após a ordenação.

### Algoritmos Estáveis Implementados:
- Insertion Sort
- Bubble Sort
- Shaker Sort

### Algoritmos Não-Estáveis Implementados:
- Selection Sort
- Shell Sort
- Quick Sort
- Heap Sort

### Demonstração Prática
Para o arquivo de cadastro de alunos, o sistema:
- Identifica casos onde a não-estabilidade é relevante
- Gera exemplos de saída mostrando a diferença entre algoritmos estáveis e não-estáveis
- Documenta o impacto da estabilidade na ordenação por cidade e nome

## 🔬 Metodologia

### Processo de Teste
1. **Leitura dos dados**: Carregamento dos arquivos de entrada
2. **Cópia dos dados**: Criação de cópias idênticas para cada algoritmo
3. **Medição isolada**: Execução de cada algoritmo com medição de tempo exclusiva da ordenação
4. **Coleta de métricas**: Registro de comparações, trocas e tempo de execução
5. **Geração de saídas**: Criação de arquivos ordenados e relatórios

### Precisão das Medições
- Uso da função `clock()` para medição de tempo
- Execução isolada de cada algoritmo
- Desconsideração do tempo de I/O conforme especificado

## 📈 Resultados

Os resultados são organizados em:

### Arquivos de Saída Individual
- Dados ordenados para cada combinação algoritmo × conjunto de dados
- Métricas detalhadas de performance

### Dados para Gráficos Comparativos
- Tempo de execução × tamanho da entrada
- Comparações × tipo de entrada
- Análise de escalabilidade

### Relatórios de Estabilidade
- Exemplos práticos de diferenças entre algoritmos estáveis e não-estáveis
- Casos específicos do arquivo de cadastro de alunos

## 📋 Entregáveis

### 1. Código Fonte ✅
- ✅ Implementação completa de todos os 7 algoritmos especificados
- ✅ Código bem estruturado e comentado
- ✅ Todos os arquivos necessários para execução

### 2. Funcionalidades Implementadas ✅
- ✅ Leitura de todos os arquivos de entrada especificados
- ✅ Execução isolada de cada algoritmo com medição de tempo
- ✅ Geração de arquivos de saída com dados ordenados
- ✅ Análise de estabilidade com exemplos práticos

- **Disciplina**: Pesquisa e Ordenação
- **Tema**: Implementação e Análise Comparativa de Algoritmos de Ordenação

---

> **Nota Acadêmica**: Este projeto foi desenvolvido integralmente seguindo as especificações do trabalho acadêmico da disciplina de Pesquisa e Ordenação. Todos os algoritmos foram implementados, sem uso de bibliotecas prontas de ordenação, conforme exigido.
