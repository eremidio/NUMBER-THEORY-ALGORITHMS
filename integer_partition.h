//VAMOS CRIAR UM ARQUIVO PARA CALCULAR PARTIÇÕES DE UM NÚMERO INTEIRO

/*

UMA PARTIÇÃO DE UM NÚMERO INTEIRO NÃO NEGATIVO É UMA DECOMPOSIÇÃO DESTE NÚMERO COMO UMA SOMA DE NÚMEROS INTEIROS NÃO NEGATIVOS.
POR EXEMPLO AS PARTIÇÕES DE n=4 SÃO: 1+1+1+1, 2+2, 2+1+1, 3+1, 4.

PARTIÇÕES PODEM SER REPRESENTATADAS DIAGRAMATICAMENTE USANDO CHAMADOS  DIAGRAMAS DE YOUNG (DIAGRAMAS DE FERRER).
PARA n=4 TEMOS OS SEGUINTES DIAGRAMAS DE YOUNG:

+---+  +---+---+  +---+---+  +---+---+---+   +---+---+---+---+
|   |  |   |   |  |   |   |  |   |   |   |   |   |   |   |   |
+---+  +---+---+  +---+---+  +---+---+---+   +---+---+---+---+
|   |  |   |   |  |   |      |   |           4   
+---+  +---+---+  +---+      +---+
|   |  2+2        |   |      3+1 
+---+             +---+
|   |             2+1+1 
+---+
1+1+1+1

DIAGRAMAS DE YOUNG SÃO PARTICULARMENTE ÚTEIS PARA REPRESENTAR FUNÇÕES SIMÉTRICAS E SÃO MUITO IMPORTANTES EM TEORIA DE
REPRESENTAÇÃO DE CONJUNTOS, TENDO APLICAÇÕES IMPORTANTES EM FÍSICA TEÓRICA (MECÂNICA QUÂNTICA E TEORIA QUÂNTICA DE CAMPOS).

A CHAMADA FUNÇÃO PARTIÇÃO p(n) CONTABILIZA O NÚMERO DE PARTIÇÕES DE UM NÚMERO INTEIRO n.
NÃO EXISTE UMA FÓRMULA EXPLÍCITA PARA O CÁLCULO DE p(n), PORÉM SEU VALOR PODE SER EXPLICITAMENTE CALCULADO USANDO RELAÇÕES 
RECURSIVAS OU APROXIMADO PARA GRANDES VALORES USANDO EXPRESSÕES QUE CONVERGEM PARA O VALOR CORRETO COM GRANDE PRECISÃO.
UMA FUNÇÃO GERADORA USANDO SÉRIES GEOMÉTRICAS PODE SER USADA PARA CALCULAR OS VALORES DE p(n) PARA UMA DADOP VALOR DE n.


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Partition_(number_theory)
                          https://en.wikipedia.org/wiki/Partition_function_(number_theory)
                          https://en.wikipedia.org/wiki/Young_tableau#Diagrams

*/

//****************************************************************************************************************************
//CABEÇALHO
#ifndef INTEGER_PARTITON_H
#define INTEGER_PARTITON_H
#include<math.h>


//****************************************************************************************************************************
//PROTÓTIPO DE FUNÇÕES
unsigned int sum_of_divisors(unsigned int);//FUNÇÃO QUE CALCULA A SOMA DE DIVISORES DE UM NÚMERO
unsigned int partition_function(unsigned int);//FUNÇÃO QUE CALCULA O NÚMERO DE PARTIÇÕES DE UM INTEIRO


//****************************************************************************************************************************
//FUNÇÕES
//Função que calcula a soma dos divisores de uma dado número
unsigned int sum_of_divisors(unsigned int n){
//Casos triviais
if(n==0)
return 0;
if(n==1)
return 1;

//Variáveis locais
unsigned int sum=0;
unsigned int i;//Variável de iteração
unsigned int limit = sqrt(n);

//Procedimento
for(i=1; i<=limit; ++i){
//Caso particular de quadrados perfeitos
if((i*i)==n){
sum+=i;
continue;
            };

if((n%i)==0)
sum+=(i+(n/i));
                      };
return sum;
                                            };
                                        

//Função que calcula o número de partições para um dado número inteiro
unsigned int partition_function(unsigned int n){
//Casos triviais
if(n==0 || n==1)
return 1;
//Caso geral
//Variáveis
unsigned int i;
unsigned int sum=0;
//Procedimentos
//Definindo a função recursivamente
for(i=0; i<n; ++i)
sum+=(sum_of_divisors(n-i)*partition_function(i));

//Resultado
return sum/n;
                                              };


//****************************************************************************************************************************
//FIM DO HEADER
#endif
