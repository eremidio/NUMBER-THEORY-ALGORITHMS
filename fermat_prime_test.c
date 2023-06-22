//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE FERMAT PARA TESTAR SE UM NÚMERO É PRIMOU NÃO
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o fermat_prime_test fermat_prime_test.c -lm

/*

O TESTE DE FERMAT É UM TESTE DA PRIMALIDADE DE UM NÚMERO INTEIRO.
ELE É FUNDAMENTADO NO CHAMADO PEQUENO TEOREMA DE FERMAT QUE AFIRMA QUE PARA UM DADO NÚMERO PRIMO p E UM INTEIRO a COPRIMO COM ELE a^(p-1) = 1(mod p).

O ALGORITMO FUNCIONA DA SEGUINTE FORMA:
1. PARA UM DADO NÚMERO n A SER TESTADO, ESCOLHE-SE UM NÚMERO a COPRIMO COM n.
2. O TEOREMA DE FERMAT É APLICADO AO PAR (a, n) E EM CASO AFIRMATIVO O NÚMERO EM QUESTÃO É POTENCIALMENTE UM PRIMO.
3. REPETINDO-SE O TESTE UM NÚMERO SUFICIENTEMENTE GRANDE DE VEZES, UMA PRECISÃO MAIOR É GARANTIDA NO TESTE.

*/


//********************************************************************************************************************
//CABEÇALHO
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
#include<time.h>
#include<math.h>


//********************************************************************************************************************
//FUNÇÕES

//Função que implementa o algoritmo de Euclides
uint64_t gcd_euclides(uint64_t a, uint64_t b){
if(b==0)
return a;
else
return gcd_euclides(b, a%b);

                                             };

//Teste unitário
bool test(uint64_t n){
//Descartando os casos trivais
if(n%2==0)
return false;

//Semente para geração de números aleatórios,
srand(time(NULL));

//Variáveis locais
uint64_t a, result;
//Procedimentos 
//Gerando um inteiro aleatória coprimo com o número a ser testado
pick:
a=2+rand()%(n-3);

if(gcd_euclides(n, a)!=1)
goto pick;

//Executando o teste
result=(uint64_t)pow(a, n-1)%n;

if(result==1)
return true;
if(result!=1)
return false;
                     };

//O Teste de Fermat
bool fermat_test(uint64_t n, int k){
//Variáveis locais
int i;//Variável de iteração

//Teste
for(i=0; i<=k;  ++i){
if(test(n)==false)
return false;
                    };

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
if(fermat_test(number, k)==true)
printf("Provável primo encontrado!\n");
else
printf("Número composto.\n");

//Finalizando a aplicação
return 0;
          }
