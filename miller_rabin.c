//VAMOS CRIAR UM PROGRAMA QUE IMPLMENTA O ALGORITMO DE MILLER-RABIN PARA TESTAR A PRIMALIDADE DE UM NÚMERO INTEIRO
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o miller_rabin miller_rabin.c

/*
O TESTE DE MILLER-RABIN É UM TESTE DA PRIMALIDADE DE UM NÚMERO INTEIRO QUE GENERALIZA O TESTE DE PRIMALIDADE DE FERMAT.
ELE É FUNDAMENTADO NO CHAMADO PEQUENO TEOREMA DE FERMAT QUE AFIRMA QUE PARA UM DADO NÚMERO PRIMO p E UM INTEIRO a COPRIMO COM ELE a^(p-1) = 1(mod p).

O ALGORITMO FUNCIONA DA SEGUINTE FORMA:
1. DADO UM NÚMERO n A SER TESTADO, TESTA=SE SE O PNÚMERO EM QUESTÃO É PAR (CASO TRIVIAL).
2. NÚMEROS ÍMPARES PODEM SER ESCRITOS NA FORMA: n-1=2^(s)d, COM s>0 E d ÍMPAR.
3. ESCOLHE-SE ALEATORIAMENTE UM NÚMERO INTEIRO a TAL QUE a É COPRIMO COM n. a É UMA TESTEMUNHA DA PRIMALIADE DE n.
4. n É UM POSSÍVEL PRIMO SE a^(d)= 1 mod(n) OU a^(2^(r)d)= -1 mod(n), PARA ALGUM r NO INTERVALO 0, 1, 2,..., s-1

PARA MAIORES INFORMAÇÕES: https://cp-algorithms.com/algebra/primality_tests.html

*/


//********************************************************************************************************************
//CABEÇALHO
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
#include<time.h>
#include"mod_bin_exponentiation.h"


//********************************************************************************************************************
//FUNÇÕES

//Função que implementa o algoritmo de Euclides para se calcular o mdc de dois inteiros
uint64_t gdc_euclides(uint64_t a, uint64_t b){
if(b==0)
return a;
else
return gdc_euclides(b, a%b);
                                             };

//Função que executa o teste para um dado número inteiro
bool test(uint64_t n){
//Números pares estão excluídos do teste
if(n%2==0)
return false;

//Definindo uma semente para geração de números aleatórios
srand(time(NULL));

//Variáveis locais
uint64_t s, r, d, a, x, n_even;

//Procedimentos
//Escolhendo uma base coprimo com n
pick:
a=2+rand()%(n-4);

if(gdc_euclides(n, a)!=1)
 goto pick;

//Definindo valores de s, d
s=0;//Ajuste de variáveis
n_even=n-1;//Ajuste devariáveis

while(n_even%2==0){
 n_even/=2;
 s++;
                  };

d=n_even;

//Teste 1: a^(d)=1 mod(n)
if(mod_bin_pow(a, d, n)==1 || mod_bin_pow(a, d, n)==(n-1))
 goto step2;
else
 return true;

//Teste 2: a^(2^(r)d)=1 mod(n) para r no intervalo 1, 2,..., s-1
step2:

for(r=1; r<s; ++r){
 x= mod_bin_pow(a, bin_pow(2, r)*d, n);
 if((x*x)%n==1)
  return true;
                  };

//Caso haja falhas no teste acima
return false;
                    };



//Teste de Miller-Rabin
bool miller_rabin_test(uint64_t n, int k){
//Variáveis locais
int i;
int p_results=0;
int f_results=0;//Variável de iteração e contagem de acertos e erros

//Teste
for(i=0; i<=k;  ++i){
if(test(n)==false)
++f_results;
else if(test(n)==true)
p_results++;
                    };

if(f_results>=p_results)
return false;
if(f_results<p_results)
return true;
                                        };

//********************************************************************************************************************
//FUNÇÃO PRINCIPAL

int main(){

//Váriaveis
uint64_t number;
int k;


//Procedimentos
//Recebendo input do usuário
printf("Digite um número que será testado:\n");
scanf("%lu", &number);
printf("Digite um número que define a precisão do teste a ser realizado:\n");
scanf("%d", &k);


//Executando o teste
if(miller_rabin_test(number, k)==true)
 printf("Provável primo encontrado!\n");
else
 printf("Número composto.\n");


//Finalizando a aplicação
return 0;
          }
