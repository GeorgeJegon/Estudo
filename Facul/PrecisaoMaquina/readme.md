#Trabalho Prático Computação Cientifica

1 - Criar um algoritmo para Cacular a Precisão da Máquina

## Tabela de Máquinas Testadas
Máquina | Sistema Operacional        | Processador          | Memória | Base Processador
---     | ---                        | ---                  | ---     | ---
#1      | Windows 8 Single Languae   | Intel Core i7-3632QM | 6GB     | x64
#2      | Windows 7 Enterprise       | Intel Core 2 DUO     | 8GB     | x64
#3      | Windows Vista Home Premium | Intel Core 2 Quad    | 4GB     | x86

## Tabela de Desempenho

Máquina | Precisão Simples        | Precisão Dupla          | Linguagem
---     | ---                     | ---                     | ---
#1      | `2.220446049250313e-16` | `-`                     | `JavaScript`
#1      | `1.1920929E-7`          | `1.1920928955078125E-7` | `Java`
#1      | `1.192093e-007`         | `2.220446e-016`         | `C++`
#3      | `-`                     | `-`                     | `PHP`
#3      | `-`                     | `-`                     | `JavaScript`
#3      | `-`                     | `-`                     | `VisualG`

## Tabela de Precisão em função da Referência

Referência | Precisão Simples | Precisão Dupla  | Linguagem
---        | ---              | ---             | ---
10         | `9.536743e-007`  | `1.776357e-015` | `C++`
17         | `1.907349e-006`  | `3.552714e-015` | `C++`
100        | `7.629395e-006`  | `1.421085e-014` | `C++`
184        | `1.525879e-005`  | `2.842171e-014` | `C++`
1000       | `6.103516e-005`  | `1.136868e-013` | `C++`
1575       | `1.220703e-004`  | `2.273737e-013` | `C++`
10000      | `9.765625e-004`  | `1.818989e-012` | `C++`
17893      | `1.953125e-003`  | `3.637979e-012` | `C++`
