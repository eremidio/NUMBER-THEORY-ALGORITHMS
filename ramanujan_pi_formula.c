//VAMOS CRIAR UM PROGRAMA QUE USA A FÓRMULA DE RAMANUJAN PARA APROXIMAR O VALOR DE PI 
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o ramanujan_pi_formula ramanujan_pi_formula.c -lm -O2

/*
A FÓMULA DE RAMANUJAN PARA O CÁLCULO DE PI: (1/π)=(2√2/9801)Σ{(4k)!(1103+26390k)}/{(k!)^4[396^(4k)]}, CONVERGE RAPIDAMENTE PARA O VALOR DE PI.
ESTA FÓRMULA BASEIA-SE NO DISCRIMINANTE FUNDAMENTAL d=-232=4(-58) CUJO NÚMERO DE CLASSE É h(-232)=2 E NAS RELAÇÕES 26390=5x7x13x58 E 396²=16*9801.

GENERALIZAÇÕES DESTA FÓRMULA INCLUEM AS CHAMADAS SÉRIES DE RAMANUJAN-SATO.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Ramanujan–Sato_series
*/

//*******************************************************************************************************
//CABEÇALHO
#include<stdint.h>
#include<stdio.h>
#include<math.h>

//*******************************************************************************************************
//FUNÇÕES
//Função que cálcula o fatorial de um número
uint64_t factorial(int n){
if(n==0 || n==1)
return 1;
else
return n*factorial(n-1);
                         };

//Função que calcula o valor de π usando a série de Ramanujan
double ramanujan_formula(int n){
//Variáveis locais
double sum=0.0;
const double root2=sqrt(2);
double parcel;
int i;

//Procedimentos
//Loop principal
for(i=0; i<=n; ++i){
parcel=(1.0*factorial(4*i)*(1103+(26390*i)));
parcel/=(pow(factorial(i), 4)*pow(396, (4*i)));
sum+=parcel;

                   };

sum*=(2*root2);
sum/=9801.0;

//Resultado
return (1.0/sum);
                               };



//*******************************************************************************************************
//FUNÇÃO PRINCIPAL
int main(){
//Variáveis locais
int n;

//Procedimentos
//Recebendo input do usuário
printf("Digite o número de termos na série usado no cálculo de pi: ");
if(scanf("%d", &n)!=1)
return 0;

//Cálculo do valor de pi
printf("Valor exato de pi (25 casas decimais): 3.1415926535897932384626433..\n");
printf("Valor aproximado com a fórmula de Ramanujan com %d termos: %.18lf\n", n, ramanujan_formula(n));

//Finalizando a aplicação
return 0;
          }
