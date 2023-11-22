//VAMOS ESCREVER UM NÚMERO QUE EXIBE NA TELA A DECOMPOSIÇÃO DE UM NÚMERO EM SEUS FATORES PRIMOS
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o  factoring factoring.c -lm -O2

//****************************************************************************************************************************
//CABEÇALHO
#include<stdio.h>
#include<stdint.h>
#include<math.h>

//****************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void factorize(uint64_t);

//****************************************************************************************************************************
//FUNÇÕES
//Função que calcula os fatores primos de um número usaremos uma otimização 30k+1
void factorize(uint64_t n){
//Variáveis locais
uint64_t i;
uint64_t limit = sqrt(n);
uint64_t divisors[8]={1, 7, 11, 13, 17, 19, 23, 29};//Números coprimos com 30 no intervalo 1,...,30

//Procedimentos
printf("Eis os fatores primos de %lu:\n", n);

//Busca por fatores 2, 3, 5
while((n%2)==0){
printf("2, ");
n/=2;
               };

while((n%3)==0){
printf("3, ");
n/=3;
               };

while((n%5)==0){
printf("5, ");
n/=5;
               };

//Condição que detecta o fim do algoritmo
if(n==1){
printf("...\n");
return;
        };

//Loop principal
//1º iteração
for(i=1; i<8; ++i){
while((n%divisors[i])==0){
printf("%lu, ", divisors[i]);
n/=divisors[i];
                         };
                  };

//Condição que detecta o fim do algoritmo
if(n==1){
printf("...\n");
return;
        };

//Demais interações
while(divisors[7]<limit){
//Atualizando variáveis
for(i=0; i<8; ++i)
divisors[i]=divisors[i]+30;

//Testando possíveis divisores
for(i=0; i<8; ++i){
while((n%divisors[i])==0){
printf("%lu, ", divisors[i]);
n/=divisors[i];
                         };
                  };

//Condição que detecta o fim do algoritmo
if(n==1){
printf("...\n");
return;
        };
                        };

//Fatores superiores a n^(1/2)
printf("%lu, ...\n", n);
return;

                          };

//FUNÇÃO PRINCIPAL
int main(){
//Variáveis locais
uint64_t number;
//Procedimentos
//Recebendo input do usuário
printf("Digite um número para ser fatorado: ");
if(scanf("%lu", &number)!= 1)
return 1;

//Fatorando o número
factorize(number);

//Finalizando a aplicação
return 0;

          };
