//VAMOS CRIAR UM PROGRAMA QUE TESTA A PRIMALIDADE DE UM INTEIRO DE 64 BITS USANDO TENTATIVA POR DIVISÃO
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o  trial_division trial_division.c -lm -O2

//****************************************************************************************************************************
//CABEÇALHO
#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<math.h>

//****************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool trial_division(uint64_t);


//****************************************************************************************************************************
//FUNÇÕES
//Função que testa a primalidade de um número usaremos uma otimização 30k+1
bool trial_division(uint64_t n){
//Variáveis locais
uint64_t i;
uint64_t limit = sqrt(n);
uint64_t divisors[8]={1, 7, 11, 13, 17, 19, 23, 29};//Números coprimos com 30 no intervalo 1,...,30

//Procedimentos
//Teste de divisão por 2, 3, 5
if((n%5)==0 || (n%3)==0 || (n%2)==0)
return false;

//Loop principal
//1º iteração
for(i=1; i<8; ++i){
if((n%divisors[i])==0)
return false;
                  };

//Demais interações
while(divisors[7]<limit){
//Atualizando variáveis
for(i=0; i<8; ++i)
divisors[i]=divisors[i]+30;

//Testando possíveis divisores
for(i=0; i<8; ++i){
if((n%divisors[i])==0)
return false;
                  };



                        };

//Caso o número passe nos testes acima
return true;

                               };



//FUNÇÃO PRINCIPAL
int main(){
//Váriaveis locais
uint64_t number;

//Procedimentos
//Recebendo input do usuário
printf("Digite um número que será testado:\n");
if(scanf("%lu", &number)!=1);

//Executando o teste
if(trial_division(number)==true)
printf("Primo encontrado!\n");
else
printf("Número composto.\n");

//Finalizando a aplicação
return 0;
          }
