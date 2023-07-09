# Trabalho de Inteligência Artificial

## Equipe

Matrícula       Nome                                E-mail
```
202065020AC      Daniel Muller Rezende               daniel.rezende@estudante.ufjf.br
202035006        Nilton Rego Teixeira                nilton.teixeira@estudante.ufjf.br
```
## Descrição:
Este trabalho consiste em implementar os principais algoritmos de busca em inteligência artificial para o jogo das fichas.

## Jogo das Fichas:
2N blocos são alinhados horizontalmente em uma régua com 2N+1 posições, dos quais N são brancos (B), N são pretos (P) e (V) é a posição vazia. 

Inicialmente as fichas se encontram em posições aleatórias e o objetivo do jogo é colocar todas as fichas brancas à esquerda das fichas pretas. Uma solução ótima para esse problema consiste no menor número de movimentos até a solução.

Neste jogo, define-se j sendo a posição da ficha i. As fichas se limitam em dois possíveis movimentos, mover-se para a posição vazia adjacente à sua posição (j = j+1 ou j = j-1) e pular para a posição vazia adjacente ao seu vizinho (j = j+2 ou j = j-2).

## Algoritmos Implementados:

- Backtraking;
- Busca em Largura;
- Busca em Profundidade (Limitada);
- Busca Ordenada;
- Busca Gulosa;
- Busca A*;
- Busca IDA*;

## Como Compilar?

Para compilar no linux, abra o diretório raiz do projeto no terminal e compile com:
 g++ -o exec Sources/*.cpp

## Como rodar?

Para rodar o programa use:
./exec "endereço do arquivo de entrada"
