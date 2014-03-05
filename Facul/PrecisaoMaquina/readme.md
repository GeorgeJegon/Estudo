#Trabalho Prático Computação Cientifica

1 -  Criar um algoritmo para Cacular a Precisão(simples e dupla) da Máquina

  a) Precisão estão listadas nas tabelas abaixo.
  
  b) Como a cada passo A é dividido por 2, então devemos ao final do loop multiplicar o valor de A final para que retornemos um passo antes da soma de A + 1 for igual = 1.
  Exemplo:
	Em C++ com precisão dupla o valor de A para que A + 1 = 1 é 1.110223e-016
	Sendo assim temos que pegar o valor anterior a esse no qual A + 1 > 1 , sendo esse valor 2.220446e-016.
	
  c) O valor da precisão encontrada se altera em função da referência passada, pois elas são inversamente proporcionais já que quanto maior o valor de entrada menor vai ser a precisão.
  

## Tabela de Máquinas Testadas
Máquina | Sistema Operacional        | Processador          | Memória | Base Processador
---     | ---                        | ---                  | ---     | ---
#1      | Windows 8 Single Languae   | Intel Core i7-3632QM | 6GB     | x64
#2      | Windows 7 Enterprise       | Intel Core 2 DUO     | 8GB     | x64
#3      | Windows Vista Home Premium | Intel Core 2 Quad    | 4GB     | x86

## Tabela de Precisão

Máquina | Precisão Simples        | Precisão Dupla          | Linguagem
---     | ---                     | ---                     | ---
#1      | `-`                     | `2.220446049250313e-16` | `JavaScript`
#1      | `1.1920929E-7`          | `2.220446049250313E-16` | `Java`
#1      | `1.192093e-007`         | `2.220446e-016`         | `C++`
#1      | `1.192092896E-07`       | `2.22044604925031E-016` | `Pascal`
#3      | `-`                     | `2.2204460492503E-16`   | `PHP`
#3      | `-`                     | `-`                     | `JavaScript`
#3      | `-`                     | `-`                     | `VisualG`

## Tabela de Precisão em função da Referência

### C++ (#3)

Referência | Precisão Simples | Precisão Dupla 
---        | ---              | ---            
10         | `9.536743e-007`  | `1.776357e-015`
17         | `1.907349e-006`  | `3.552714e-015`
100        | `7.629395e-006`  | `1.421085e-014`
184        | `1.525879e-005`  | `2.842171e-014`
1000       | `6.103516e-005`  | `1.136868e-013`
1575       | `1.220703e-004`  | `2.273737e-013`
10000      | `9.765625e-004`  | `1.818989e-012`
17893      | `1.953125e-003`  | `3.637979e-012`

### Pascal (#3)

Referência | Precisão Simples  | Precisão Dupla 
---        | ---               | ---            
10         | `9.536743164E-07` | `1.77635683940025E-015`
17         | `1.907348633E-06` | `3.55271367880050E-015`
100        | `7.629394531E-06` | `1.42108547152020E-014`
184        | `1.525878906E-05` | `2.84217094304040E-014`
1000       | `6.103515625E-05` | `1.13686837721616E-013`
1575       | `1.220703125E-04` | `2.27373675443232E-013`
10000      | `9.765625000E-04` | `1.81898940354586E-012`
17893      | `1.953125000E-03` | `3.63797880709171E-012`

### Java (#3)

Referência | Precisão Simples | Precisão Dupla 
---        | ---              | ---            
10         | `9.536743E-7`    | `1.7763568394002505E-15`
17         | `1.9073486E-6`   | `3.552713678800501E-15`
100        | `7.6293945E-6`   | `1.4210854715202004E-14`
184        | `1.5258789E-5`   | `2.8421709430404007E-14`
1000       | `6.1035156E-5`   | `1.1368683772161603E-13`
1575       | `1.2207031E-4`   | `2.2737367544323206E-13`
10000      | `9.765625E-4`    | `1.8189894035458565E-12`
17893      | `0.001953125`    | `3.637978807091713E-12`
