//VAMOS ESCREVER UM NÚMERO QUE EXIBE NA TELA A DECOMPOSIÇÃO DE UM NÚMERO EM SEUS FATORES PRIMOS
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o  factoring factoring.c

//****************************************************************************************************************************
//CABEÇALHO
#include<stdio.h>
#include<stdint.h>

//****************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void factorize(uint64_t);

//****************************************************************************************************************************
//FUNÇÕES
//Função que calcula os fatores primos de um número usaremos uma otimização 6k+1
void factorize(uint64_t n){
//Variáveis locais
uint64_t i;
//Procedimentos
printf("Eis os fatores primos de %lu:\n", n);

//Testando divisão por fatores primos menores que 100
while(n%2==0){ n/=2; printf("2, "); };
while(n%3==0){ n/=3; printf("3, "); };
while(n%5==0){ n/=5; printf("5, "); };
while(n%7==0){ n/=7; printf("7, "); };
while(n%11==0){ n/=11; printf("11, "); };
while(n%13==0){ n/=13; printf("13, "); };
while(n%17==0){ n/=17; printf("17, "); };
while(n%19==0){ n/=19; printf("19, "); };
while(n%23==0){ n/=23; printf("23, "); };
while(n%29==0){ n/=29; printf("29, "); };
while(n%31==0){ n/=31; printf("31, "); };
while(n%37==0){ n/=37; printf("37, "); };
while(n%41==0){ n/=41; printf("41, "); };
while(n%43==0){ n/=43; printf("43, "); };
while(n%47==0){ n/=47; printf("47, "); };
while(n%53==0){ n/=53; printf("53, "); };
while(n%59==0){ n/=59; printf("59, "); };
while(n%61==0){ n/=61; printf("61, "); };
while(n%67==0){ n/=67; printf("67, "); };
while(n%71==0){ n/=71; printf("71, "); };
while(n%73==0){ n/=73; printf("73, "); };
while(n%79==0){ n/=79; printf("79, "); };
while(n%83==0){ n/=83; printf("83, "); };
while(n%89==0){ n/=89; printf("89, "); };
while(n%97 ==0){ n/=97; printf("97, "); };

//Loop principal
for(i=101; i<=n; i+=6){
while((n%i)==0){
n/=i;
printf("%lu, ", i);
               };

while((n%(i+2))==0){
n/=(i+2);
printf("%lu, ", (i+2));
                   };
if(n==1)
break;
                     };
if(n==1)
printf("...\n");
                          };

//FUNÇÃO PRINCIPAL
int main(){
//Variáveis locais
uint64_t number;
//Prcedimento
printf("Digite um número para ser fatorado: ");
scanf("%lu", &number);
//Fatorando o número
factorize(number);

//Finalizando a aplicação
return 0;

          };
