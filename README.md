# Sistema de Análise de Algoritmos de Ordenação

![Badge Status](https://img.shields.io/badge/status-concluído-brightgreen)
![Badge Versão](https://img.shields.io/badge/versão-2.1-blue)
![Badge Data](https://img.shields.io/badge/data-Agosto%202025-orange)
![Badge Linguagem](https://img.shields.io/badge/linguagem-C-blue)

## 📝 Sumário
- [Descrição](#-descrição)
- [Algoritmos Implementados](#-algoritmos-implementados)
- [Funcionalidades](#-funcionalidades)
- [Estrutura do Projeto](#-estrutura-do-projeto)
- [Requisitos de Sistema](#-requisitos-de-sistema)
- [Como Compilar e Executar](#-como-compilar-e-executar)
- [Arquivos de Entrada](#-arquivos-de-entrada)
- [Arquivos de Saída](#-arquivos-de-saída)
- [Análises Realizadas](#-análises-realizadas)
- [Arquitetura do Sistema](#-arquitetura-do-sistema)
- [Resultados](#-resultados)
- [Contribuidores](#-contribuidores)

## 📋 Descrição

Este sistema foi desenvolvido como parte de um trabalho acadêmico para a disciplina de Pesquisa Operacional, focado na análise comparativa de algoritmos clássicos de ordenação. O projeto implementa, analisa e documenta o comportamento de 7 algoritmos diferentes, medindo com precisão suas performances em termos de tempo de execução, número de comparações e trocas realizadas.

Cada algoritmo é implementado em duas versões:
- **Versão não otimizada**: Implementação didática e clara para fins educacionais
- **Versão otimizada**: Implementação com foco em performance e eficiência

## 🔄 Algoritmos Implementados

O sistema implementa os seguintes algoritmos de ordenação:

| Algoritmo | Estabilidade | Complexidade Média | Ideal para |
|-----------|-------------|-------------------|-----------|
| **Insertion Sort** | Estável | O(n²) | Conjuntos pequenos ou quase ordenados |
| **Bubble Sort** | Estável | O(n²) | Fins didáticos, conjuntos pequenos |
| **Selection Sort** | Não-estável | O(n²) | Minimizar número de trocas |
| **Shaker Sort** | Estável | O(n²) | Melhoria do Bubble Sort para certos casos |
| **Shell Sort** | Não-estável | O(n log² n) | Melhoria do Insertion Sort |
| **Quick Sort** | Não-estável | O(n log n) | Grande volume de dados aleatórios |
| **Heap Sort** | Não-estável | O(n log n) | Garantia de performance no pior caso |

## ⚙️ Funcionalidades

- **Análise precisa de tempo**: Medição em nanossegundos usando funções específicas para cada sistema operacional
- **Métricas detalhadas**: Contagem exata de comparações e trocas realizadas por cada algoritmo
- **Testes com diferentes conjuntos de dados**: 
  - Números ordenados, reversos, aleatórios, duplicados
  - Conjuntos de diferentes tamanhos (pequeno, médio, grande)
  - Dados de alunos (estruturas complexas)
- **Relatórios comparativos**: Geração automática de relatórios de análise
- **Verificação de estabilidade**: Análise da propriedade de estabilidade dos algoritmos
- **Interface de usuário**: Menu simples para execução e visualização dos resultados

## 📁 Estrutura do Projeto

```
trabalho-po-1/
├── CMakeLists.txt          # Configuração de compilação CMake
├── main.c                  # Ponto de entrada do programa
├── include/                # Arquivos de cabeçalho
│   ├── algoritmos.h        # Declaração dos algoritmos
│   ├── analise.h           # Sistema de análise e relatórios
│   ├── io.h                # Entrada/Saída de dados
│   ├── sorts.h             # Header principal unificado
│   ├── tipos.h             # Definições de tipos e estruturas
│   └── utils.h             # Funções utilitárias
├── src/                    # Código fonte
│   ├── algoritmos.c        # Implementação dos algoritmos
│   ├── analise.c           # Funções de análise e relatórios
│   ├── io.c                # Implementação de E/S
│   └── utils.c             # Implementação de utilitários
├── data/                   # Dados de entrada
│   ├── alunos.txt          # Dados de alunos para teste
│   ├── numeros_pequeno.txt # Conjunto pequeno de números
│   ├── numeros_medio.txt   # Conjunto médio de números
│   ├── numeros_grande.txt  # Conjunto grande de números
│   ├── numeros_ordenados.txt # Números já ordenados
│   ├── numeros_reversos.txt  # Números em ordem reversa
│   └── numeros_duplicados.txt # Números com valores repetidos
└── output/                 # Resultados gerados
    ├── analise_estabilidade.txt # Análise de estabilidade
    ├── alunos/             # Resultados para dados de alunos
    ├── numeros/            # Resultados para dados numéricos
    └── relatorios/         # Relatórios consolidados
```

## 💻 Requisitos de Sistema

- Compilador C compatível com C99 ou superior
- Sistema operacional: Windows, Linux ou macOS
- CMake 3.10 ou superior (para compilação)
- 2GB de RAM (mínimo)
- Espaço em disco: 50MB para o projeto e dados de teste

## 🚀 Como Compilar e Executar

### Usando CMake (recomendado)

```bash
# Clone o repositório (se aplicável)
git clone https://github.com/seu-usuario/trabalho-po-1.git
cd trabalho-po-1

# Configure o CMake
mkdir -p build && cd build
cmake ..

# Compile o projeto
cmake --build .

# Execute o programa
./trabalho_po_1
```

### Compilação manual

```bash
# Compile todos os arquivos fonte
gcc -o trabalho_po_1 main.c src/*.c -I./include -std=c99 -O2

# Execute o programa
./trabalho_po_1
```

## 📊 Análises Realizadas

O sistema realiza diversas análises para cada algoritmo de ordenação:

1. **Tempo de execução**: Medição precisa em nanossegundos
2. **Operações realizadas**: Contagem de comparações e trocas
3. **Comportamento com diferentes entradas**:
   - Dados já ordenados
   - Dados em ordem reversa
   - Dados aleatórios
   - Dados com valores duplicados
   - Dados de diferentes tamanhos
4. **Estabilidade**: Verificação da manutenção da ordem relativa de elementos com valores iguais
5. **Comportamento com tipos de dados complexos**: Estruturas de dados de alunos

## 🏗️ Arquitetura do Sistema

O projeto segue uma arquitetura modular, com separação clara de responsabilidades:

- **Módulo de Algoritmos**: Implementação dos métodos de ordenação
- **Módulo de Análise**: Medição de performance e geração de relatórios
- **Módulo de E/S**: Leitura de dados e escrita de resultados
- **Módulo de Tipos**: Definição das estruturas de dados utilizadas
- **Módulo de Utilitários**: Funções auxiliares para o sistema

Esta arquitetura permite:
- Fácil manutenção e extensão do código
- Adição de novos algoritmos ou métricas
- Reutilização de componentes em outros projetos

## 📈 Resultados

Os resultados detalhados das análises são salvos na pasta `output/`:

- **Arquivos individuais**: Mostram o desempenho de cada algoritmo para cada conjunto de dados
- **Relatórios comparativos**: Apresentam tabelas e gráficos comparando os diferentes algoritmos
- **Análise de estabilidade**: Documenta quais algoritmos preservam a ordem relativa dos elementos

## 👥 Contribuidores

- [Seu Nome] - Desenvolvimento e documentação
- [Professor] - Orientação e especificações do projeto

---

> Este projeto foi desenvolvido para fins acadêmicos como parte da disciplina de Pesquisa Operacional da [Nome da sua Instituição], sob orientação do Prof. [Nome do Professor].

