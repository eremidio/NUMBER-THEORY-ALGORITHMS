//VAMOS IMPLEMENTAR UMA FUNÇÃO QUE CALCULAO SÍMBOLO DE JACOBI

/*
O CHAMADO SÍMBOLOS DE JACOBI SÃO UMA GENERALIZAÇÃO DOS SÍMBOLOS DE LEGENDRE.
O SÍMBOLO DE LEGENDRE (a/b) É DEFINIDO COMO:
       { 0 SE a = 0 mod(b)
(a/b)= { +1 SE a ≠ 0 mod(b) E PARA ALGUM x SE VERIFICA A RELAÇÃO a = x² mod(b) 
       { -1 SE a ≠ 0 mod(b) E PARA NENHUM x SE VERIFICA A RELAÇÃO a = x² mod(b) 
 
OS SÍMBOLOS DE JACOBI SÃO CALCULADOS MULTIPLICANDO-SE OS REPECTIVOS SÍMBOLOS DE LEGENDRE DOS FATORES PRIMOS UM DADO NÚMERO ELEVADO AO SEU NÚMERO DE OCORRÊNCA NESTE NÚMERO.
PARA NÚMEROS PRIMOS AMBOS DOS SÍMBOLOS SÃO IGUAIS.
UMA SÉRIE DE  RELAÇÕES RECURSIVAS PERMITE OBTER O SÍMBOLO DE JACOBI DE FORMA SIMPLES.
PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Jacobi_symbol


O SÍMBOLO DE JACOBI É UM CASO ESPECIAL CARACTÉRE DE DIRICHLET A MENOS DE UMA RELAÇÃO DE CONGRUÊNCIA.
PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Dirichlet_character

*/

//********************************************************************************************************************
//CABEÇALHO
#include<stdint.h>
#include<assert.h>

//Protótipo de funções
int jacobi(int64_t, int64_t);
int64_t euclides_check(int64_t, int64_t);

//********************************************************************************************************************
//Função que implementa o algoritmo de Euclides para se calcular o mdc de dois inteiros
int64_t euclides_check(int64_t a, int64_t b){
if(b==0)
return a;
else
return euclides_check(b, a%b);
                                            };

//Função que calcula o símbolo de Jacobi
int jacobi(int64_t a, int64_t b){
//Restrições para o cálculo
assert(b>a && a>0 && (b%2)==1);

//Variáveis locais
int j=1;//Resultado
int64_t temp;//Variável temporária

//Procedimentos

//Loop principal (tentaremos obter o numerador a=1)
while(a!=1){
//Reduzindo fatores pares no numerador
while(a%2==0){
a/=2;
if(b%8==3 || b%8==5)
j*=(-1);
if(b%8==1 || b%8==7)
continue;
             };

//Caso trivial:numerador e denominador não são relativamente primos
if(euclides_check(a, b)!=1)
return 0;

//Lei da reciprocidade quadrática
temp=a;
a=b;
b=temp;

if(a%4==3 && b%4==3)
j*=(-1);

//Reduzindo o númerador
a%=b;

//Caso geral
if(b==1)
return j;
           };
                                  }; 

