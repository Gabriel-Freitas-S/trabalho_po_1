# 🔄 Sistema de Análise de Algoritmos de Ordenação

[![C](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Version](https://img.shields.io/badge/Version-2.1-green.svg)]()
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)]()
[![Precision](https://img.shields.io/badge/Timing-Nanosecond%20Precision-red.svg)]()

## 📋 Índice

1. [Sobre o Projeto](#-sobre-o-projeto)
2. [🆕 Novidades Versão 2.1](#-novidades-versão-21)
3. [Características Principais](#-características-principais)
4. [Algoritmos Implementados](#-algoritmos-implementados)
5. [Estrutura do Projeto](#-estrutura-do-projeto)
6. [Compilação e Execução](#-compilação-e-execução)
7. [Manual de Uso](#-manual-de-uso)
8. [Análise de Dados](#-análise-de-dados)
9. [Arquivos de Saída](#-arquivos-de-saída)
10. [Documentação Técnica](#-documentação-técnica)
11. [Métricas Analisadas](#-métricas-analisadas)
12. [Contribuição](#-contribuição)
13. [Licença](#-licença)

## 🎯 Sobre o Projeto

Este sistema implementa uma **análise comparativa completa** de 7 algoritmos clássicos de ordenação, desenvolvido em linguagem C com foco em **performance, precisão e usabilidade**. O projeto oferece uma interface interativa que permite testar algoritmos individualmente ou executar análises automatizadas completas.

### 🎓 Objetivos Acadêmicos

- **Comparar empiricamente** diferentes algoritmos de ordenação
- **Medir precisamente** tempo de execução, comparações e trocas
- **Analisar estabilidade** dos algoritmos com dados reais
- **Gerar relatórios detalhados** para análise acadêmica
- **Demonstrar implementações genéricas** que funcionam com qualquer tipo de dados

## 🆕 **Novidades Versão 2.1**

### ⚡ **Sistema de Medição de Alta Precisão**

A versão 2.1 introduz um revolucionário sistema de medição de tempo que **elimina completamente** o problema de algoritmos rápidos aparecerem com tempo zero nos relatórios.

#### **🔬 Tecnologias de Precisão Implementadas:**

| Plataforma | Função Utilizada | Precisão | Características |
|------------|------------------|----------|------------------|
| **Windows** | `QueryPerformanceCounter` | **Microssegundos** | Hardware timer de alta resolução |
| **Linux/Unix** | `clock_gettime(CLOCK_MONOTONIC)` | **Nanossegundos** | Timer monotônico do kernel |
| **Fallback** | `gettimeofday()` | **Microssegundos** | Compatibilidade universal |

#### **📊 Medição Adaptativa Inteligente:**

O sistema agora ajusta automaticamente o número de execuções baseado no tamanho do conjunto:

- **< 100 elementos**: 10 execuções → média estatística
- **< 1.000 elementos**: 5 execuções → precisão balanceada  
- **< 10.000 elementos**: 3 execuções → otimização de tempo
- **≥ 10.000 elementos**: 1 execução → medição única suficiente

### 🔄 **Sistema Dual: Otimizada + Didática**

Implementação única que oferece **duas versões** de cada algoritmo:

- **✅ Versão OTIMIZADA**: Máxima performance com otimizações avançadas
- **📚 Versão NÃO OTIMIZADA**: Implementação didática para fins educacionais

## ✨ Características Principais

### 🎯 **Interface e Usabilidade**
- ✅ Menu interativo limpo e intuitivo
- ✅ Execução automatizada de todos os testes
- ✅ Feedback visual em tempo real
- ✅ Limpeza automática da tela entre operações

### 🔧 **Robustez Técnica**
- ✅ **Algoritmos genéricos** compatíveis com qualquer tipo de dados
- ✅ **Detecção automática** de caminhos de arquivos
- ✅ **Sistema de fallback** para diferentes estruturas de projeto
- ✅ **Tratamento robusto** de erros e casos extremos

### 📊 **Análise Avançada**
- ✅ **Medição de alta precisão** até nanossegundos
- ✅ **Contagem precisa** de comparações e trocas
- ✅ **Análise de estabilidade** com dados reais
- ✅ **Rankings automáticos** por diferentes métricas

### 💾 **Organização de Dados**
- ✅ **Salvamento automático** em estrutura organizada
- ✅ **Compatibilidade multiplataforma** (Windows/Linux/macOS)
- ✅ **Múltiplos formatos** de relatórios
- ✅ **Backup automático** em diferentes locais

## 🧮 Algoritmos Implementados

| Algoritmo | Complexidade (Melhor) | Complexidade (Médio) | Complexidade (Pior) | Estável | Características |
|-----------|----------------------|---------------------|-------------------|---------|-----------------|
| **Insertion Sort** | O(n) | O(n²) | O(n²) | ✅ Sim | Eficiente para pequenos conjuntos |
| **Bubble Sort** | O(n) | O(n²) | O(n²) | ✅ Sim | Algorítmo simples, didático |
| **Selection Sort** | O(n²) | O(n²) | O(n²) | ❌ Não | Número fixo de trocas |
| **Shaker Sort** | O(n) | O(n²) | O(n²) | ✅ Sim | Bubble sort bidirecional |
| **Shell Sort** | O(n log n) | O(n^1.25) | O(n²) | ❌ Não | Insertion sort com incrementos |
| **Quick Sort** | O(n log n) | O(n log n) | O(n²) | ❌ Não | Dividir para conquistar |
| **Heap Sort** | O(n log n) | O(n log n) | O(n log n) | ❌ Não | Garantia de O(n log n) |

### 🏆 **Características de Estabilidade**

```
📝 ALGORITMOS ESTÁVEIS:
   ✅ Insertion Sort  - Preserva ordem de elementos iguais
   ✅ Bubble Sort     - Comparações adjacentes mantêm ordem
   ✅ Shaker Sort     - Bubble Sort bidirecional estável

⚠️  ALGORITMOS NÃO ESTÁVEIS:
   ❌ Selection Sort  - Troca elementos distantes
   ❌ Shell Sort      - Comparações com gap podem quebrar estabilidade
   ❌ Quick Sort      - Particionamento pode reorganizar elementos iguais
   ❌ Heap Sort       - Construção do heap quebra ordem original
```

## 📁 Estrutura do Projeto

```
trabalho-po-1/
├── 📁 data/                          # Conjuntos de dados de teste
│   ├── 📄 alunos.txt                 # Dados estruturados (nome, data, bairro, cidade)
│   ├── 📄 numeros_pequeno.txt        # ~100 elementos
│   ├── 📄 numeros_medio.txt          # ~1.000 elementos  
│   ├── 📄 numeros_grande.txt         # ~10.000 elementos
│   ├── 📄 numeros_ordenados.txt      # Melhor caso (já ordenados)
│   ├── 📄 numeros_reversos.txt       # Pior caso (ordem inversa)
│   └── 📄 numeros_duplicados.txt     # Elementos repetidos
│
├── 📁 include/                       # Headers e definições
│   └── 📄 sorts.h                    # API completa do sistema
│
├── 📁 src/                           # Código fonte modularizado
│   ├── 📄 algoritmos.c               # Implementações dos algoritmos
│   ├── 📄 analise.c                  # Sistema de medição e análise
│   ├── 📄 io.c                       # Entrada/saída e funções de comparação
│   └── 📄 utils.c                    # Utilitários e interface
│
├── 📁 output/                        # Resultados organizados automaticamente
│   ├── 📁 numeros/                   # Arrays ordenados (números)
│   ├── 📁 alunos/                    # Arrays ordenados (estruturas)
│   ├── 📁 relatorios/                # Análises de performance
│   └── 📄 analise_estabilidade.txt   # Relatório de estabilidade
│
├── 📄 main.c                         # Programa principal
├── 📄 CMakeLists.txt                 # Configuração do CMake
├── 📄 README.md                      # Este arquivo
└── 📄 LICENSE                        # Licença MIT
```

## 🛠️ Compilação e Execução

### **Pré-requisitos**

- **Compilador C**: GCC, Clang, MSVC ou compatível
- **CMake**: 3.10 ou superior (opcional)
- **Sistema**: Windows, Linux, macOS

### **Método 1: CMake (Recomendado)**

```bash
# 1. Criar diretório de build
mkdir build && cd build

# 2. Configurar projeto
cmake ..

# 3. Compilar
cmake --build .

# 4. Executar
./trabalho_po_1        # Linux/macOS
trabalho_po_1.exe      # Windows
```

### **Método 2: Compilação Direta**

```bash
# GCC/Clang
gcc -o trabalho_po_1 main.c src/*.c -Iinclude -std=c99

# MSVC (Windows)
cl main.c src/*.c /Iinclude /Fe:trabalho_po_1.exe
```

### **Método 3: IDEs Compatíveis**

- **CLion**: Abrir pasta do projeto
- **Visual Studio**: Usar "Abrir Pasta"
- **Code::Blocks**: Criar projeto e adicionar arquivos
- **Dev-C++**: Compilação direta

## 📖 Manual de Uso

### **1. Execução Principal**

```
================================================================
              TRABALHO DE ALGORITMOS DE ORDENAÇÃO              
                    Programação Avançada - 2025                
                Sistema Dual: Otimizada + Didática             
================================================================

                        MENU PRINCIPAL                         
================================================================
  1. Gerar relatório completo de todos os testes               
     (Inclui análise de ambas as versões dos algoritmos)       
  0. Sair do programa                                           
================================================================
```

### **2. Processo Automatizado**

O programa executa automaticamente:

#### **🔄 FASE 1: Versão Não Otimizada**
- Testa todos os 6 conjuntos de números
- Processa dados de alunos
- Gera métricas detalhadas

#### **🔄 FASE 2: Versão Otimizada**
- Repete todos os testes com versões otimizadas
- Compara performance
- Analisa diferenças de implementação

#### **🔄 FASE 3: Análise de Estabilidade**
- Testes específicos com elementos duplicados
- Verificação de ordem relativa
- Relatório detalhado de estabilidade

#### **🔄 FASE 4: Relatório Final**
- Consolidação de todos os resultados
- Comparação entre versões
- Índices de arquivos gerados

### **3. Tempo de Execução**

⏱️ **Tempo estimado**: 2-5 minutos (dependendo do hardware)
- Conjuntos pequenos: ~10 segundos
- Conjuntos médios: ~30 segundos  
- Conjuntos grandes: ~2 minutos
- Análises extras: ~30 segundos

## 📊 Análise de Dados

### **📈 Conjuntos de Teste Disponíveis**

#### **Números Inteiros (6 conjuntos):**

| Arquivo | Elementos | Propósito | Características |
|---------|-----------|-----------|-----------------|
| `numeros_pequeno.txt` | ~100 | Algoritmos O(n²) | Execução rápida, boa para testes |
| `numeros_medio.txt` | ~1.000 | Diferenciação | Mostra vantagens O(n log n) |
| `numeros_grande.txt` | ~10.000 | Performance | Destaca algoritmos eficientes |
| `numeros_ordenados.txt` | Variado | Melhor caso | Testa otimizações especiais |
| `numeros_reversos.txt` | Variado | Pior caso | Força comportamento quadrático |
| `numeros_duplicados.txt` | Variado | Estabilidade | Elementos repetidos |

#### **Dados Estruturados (1 conjunto):**

- **`alunos.txt`**: Estruturas com nome, data de nascimento, bairro e cidade
- **Propósito**: Análise de estabilidade e ordenação por múltiplos critérios
- **Formato**: CSV (nome,data,bairro,cidade)

### **🎯 Estratégia de Análise**

O sistema realiza **análise comparativa em 3 dimensões**:

1. **⏱️ Temporal**: Tempo de execução com precisão de nanossegundos
2. **🔢 Operacional**: Contagem de comparações e trocas
3. **🎲 Comportamental**: Análise de estabilidade e casos extremos

## 📁 Arquivos de Saída

O sistema organiza automaticamente todos os resultados na pasta `output/`:

### **📁 output/numeros/**

Arrays de números ordenados por cada algoritmo:

```
Bubble_Sort_otimizada_numeros_pequeno.txt
Bubble_Sort_nao_otimizada_numeros_pequeno.txt
Insertion_Sort_otimizada_numeros_grande.txt
Quick_Sort_otimizada_numeros_reversos.txt
[... todos os algoritmos × todos os conjuntos × 2 versões]
```

### **📁 output/alunos/**

Dados de alunos ordenados por bairro e nome:

```
Bubble_Sort_otimizada_alunos.txt
Insertion_Sort_nao_otimizada_alunos.txt
[... todos os algoritmos × 2 versões]
```

### **📁 output/relatorios/**

Análises detalhadas de performance:

```
relatorio_numeros_otimizada_numeros_pequeno.txt
relatorio_numeros_nao_otimizada_numeros_grande.txt
relatorio_alunos_otimizada_alunos.txt
relatorio_comparativo_final.txt
[... relatórios por conjunto e versão]
```

### **📄 output/analise_estabilidade.txt**

Relatório específico sobre estabilidade dos algoritmos.

## 🔧 Documentação Técnica

### **⚙️ Arquitetura do Sistema**

#### **Modularização**
- **`main.c`**: Interface principal e controle de fluxo
- **`algoritmos.c`**: Implementações dual (otimizada/didática)  
- **`analise.c`**: Sistema de medição de alta precisão
- **`io.c`**: Entrada/saída robusta e funções de comparação
- **`utils.c`**: Utilitários e gerenciamento de arquivos

#### **Características Técnicas**

##### **🎯 Algoritmos Genéricos**
```c
// Assinatura padrão - funciona com qualquer tipo
void insertion_sort(void *arr, int n, size_t elem_size, CompareFn cmp);

// Função de comparação personalizada
typedef int (*CompareFn)(const void *a, const void *b);
```

##### **⏱️ Sistema de Medição Avançado**
```c
// Medição multiplataforma de alta precisão
double obter_timestamp_precisao();

// Medição adaptativa com múltiplas execuções
double medir_tempo_multiplo(/* parâmetros */);
```

##### **🔄 Sistema Dual**
```c
// Configuração global de versão
extern int usar_versao_otimizada;
void configurar_otimizacao(int otimizada);

// Interfaces unificadas que alternam automaticamente
void insertion_sort(/*...*/);  // Chama versão ativa
void insertion_sort_optimized(/*...*/);  // Versão específica
void insertion_sort_naive(/*...*/);      // Versão específica
```

### **📊 Estruturas de Dados**

#### **Informações de Algoritmo**
```c
typedef struct {
    char nome[30];
    char complexidade_melhor[15];
    char complexidade_media[15]; 
    char complexidade_pior[15];
    int eh_estavel;
    // Ponteiros de função...
} AlgoritmoInfo;
```

#### **Resultados de Performance**
```c
typedef struct {
    char algoritmo[30];
    double tempo_execucao;      // Precisão de nanossegundos
    int tamanho_dados;
    char tipo_dados[20];
    long long comparacoes;      // Contagem precisa
    long long trocas;          // Contagem precisa
} ResultadoTempo;
```

## 📈 Métricas Analisadas

### **1. ⏱️ Tempo de Execução**

- **Precisão**: Até nanossegundos (dependente do hardware)
- **Método**: Medição antes/depois com timestamps de alta resolução
- **Adaptação**: Múltiplas execuções para algoritmos muito rápidos
- **Garantia**: Nunca retorna zero (mínimo 1 microssegundo)

### **2. 🔢 Número de Comparações**

- **Contagem**: Interceptação transparente via wrapper
- **Precisão**: Todas as comparações entre elementos
- **Uso**: Análise da complexidade real vs teórica

### **3. 🔄 Número de Trocas/Movimentações**

- **Definição**: Qualquer movimentação de elementos
- **Inclui**: Trocas diretas, deslocamentos, inserções
- **Análise**: Overhead de movimentação de dados

### **4. 🎯 Análise de Estabilidade**

- **Teste**: Elementos com chaves iguais
- **Verificação**: Preservação da ordem relativa original
- **Casos**: Dados reais com alunos do mesmo bairro

### **5. 📊 Rankings Automáticos**

O sistema gera automaticamente rankings por:
- **⚡ Tempo de execução** (mais rápido primeiro)
- **🔢 Número de comparações** (menos comparações primeiro)
- **🔄 Número de trocas** (menos movimentações primeiro)

### **6. 📋 Relatórios Comparativos**

- **Por conjunto**: Performance em cada tipo de dados
- **Por algoritmo**: Comportamento em diferentes cenários  
- **Por versão**: Otimizada vs Não Otimizada
- **Consolidado**: Visão geral de todos os testes

## 🤝 Contribuição

### **Como Contribuir**

1. **Fork** do repositório
2. **Clone** sua fork localmente
3. **Crie** uma branch para sua feature (`git checkout -b feature/nova-funcionalidade`)
4. **Commit** suas mudanças (`git commit -am 'Adiciona nova funcionalidade'`)
5. **Push** para a branch (`git push origin feature/nova-funcionalidade`)
6. **Abra** um Pull Request

### **Áreas para Contribuição**

- 🔬 **Novos algoritmos** (Merge Sort, Radix Sort, etc.)
- 📊 **Novas métricas** (uso de memória, cache misses)
- 🖥️ **Interface gráfica** (visualização em tempo real)
- 📈 **Análises estatísticas** (desvio padrão, intervalos de confiança)
- 🔧 **Otimizações** (paralelização, SIMD)

### **Padrões de Código**

- **Documentação**: Comentários em português, estilo Doxygen
- **Nomenclatura**: snake_case para funções e variáveis
- **Modularização**: Separação clara de responsabilidades
- **Compatibilidade**: Código multiplataforma (Windows/Linux/macOS)

## 📄 Licença

Este projeto está licenciado sob a **Licença MIT** - veja o arquivo [LICENSE](LICENSE) para detalhes.

```
MIT License

Copyright (c) 2025 Sistema de Análise de Algoritmos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
```

---

## 📞 Contato e Suporte

**📧 Para dúvidas acadêmicas**: Consulte a documentação nos comentários do código
**🐛 Para reportar bugs**: Use as Issues do GitHub
**💡 Para sugestões**: Pull Requests são bem-vindos

---

<div align="center">

**🏆 Desenvolvido com foco em qualidade, precisão e usabilidade**

[![Made with ❤️](https://img.shields.io/badge/Made%20with-❤️-red.svg)]()
[![C Programming](https://img.shields.io/badge/C-Programming-blue.svg)]()
[![Academic Project](https://img.shields.io/badge/Academic-Project-green.svg)]()

**⭐ Se este projeto foi útil para você, considere dar uma estrela!**

</div>
