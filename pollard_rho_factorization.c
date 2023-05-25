//VAMOS IMPLEMENTAR O ALGORITMO DE POLLARD-RHO (p-1) PARA FATORIZAR NÚMEROS INTEIROS
//ESTE ALGORITMO USA UM GERADOR DE NÚMEROS ALEATÓRIOS, ENTÃO NEM SEMPRE ELE PRODUZ UM RESULTADO SATISFATÓRIO
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o pollard_rho_factorization pollard_rho_factorization.c -lm

/*
O ALGORITMO DE POLLARD-RHO (p-1) FAZ USO DO CHAMADO PEQUENO TEOREMA DE FERMAT QUE AFIRMA QUE:
"QUE PARA QUAISQUER NÚMEROS COPRIMOS a E p, ISTO É, TAL QUE mdc(a, p) = 1, TEMOS QUE a^(p-1)≡1 (mod p)".
COMO EXEMPLO SEJAM a=2, p=3, a^(p-1)=2^(3-1)=4≡1 (mod 3).
SIMILARMENTE PARA a=4, p=7 TEMOS QUE a^(p-1)=4^(7-1)=4096≡1 (mod 7). 

SEJA n UM NÚMERO COMPOSTO, QUALQUER FATOR f NÃO TRIVIAL DE n OBEDECE AS RELAÇÕES f < n E f<n^(1/2).
SEJAM p, q DOIS NÚMEROS NO INTERVALO [0, n-1]. p≡q (mod n), APENAS NOS CASOS EM QUE p E q SÃO IDÊNTICOS.
SEJAM p E q DOIS NÚMEROS PRIMOS E SUPONHA QUE n SEJA UM PRODUTO DESTES DOIS FATORES PRIMOS.
SEJA (p-1) UM FATOR PRIMO DE UM NÚMERO l DE MODO QUE l=k(p-1), ONDE k É UM INTEIRO QUALQUER.
PELO TEOREMA DE FERMAT TEMOS QUE: a^l≡(a^(p-1))^k (mod p)≡1.
USANDO ESTES RESULTADOS OBTEMOS QUE p DIVIDE a^l, E POR SUPOSIÇÃO p É UM FATOR PRIMO DE n.
ASSIM O mdc(a^l-1, n) INCLUIRÁ p COM CERTEZA. O PROBLEMA RESIDE ENTÃO EM ENCONTRAR UM VALOR DE l ADEQUADO.


O ALGORITMO DE POLLARD-RHO (p-1) É EXECUTADO NAS SEGUINTES ETAPAS:

1. ESCOLHEMOS UM NÚMERO a COPRIMO COM O NÚMERO n A SER FATORADO.
2. CALCULAMOS a^k PARA k NO INTERVALO [0, n^(1/2)].
3. CALCULAMOS O mdc DE (a^k-1) mod n E n.
4. VALORES NÃO TRIVIAIS ENCONTRADOS NA ETAPA 3 SÃO FATORES PRIMOS DE n.

*/

//*********************************************************************************************************************
//CABEÇALHO
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<math.h>
#include<time.h>


//*********************************************************************************************************************
//FUNÇÕES
//Algoritmo de Euclides para calcular o mdc de dois inteiros
uint64_t euclides_check(uint64_t a, uint64_t b){
//Procedimentos
if(a==b)
return a;
if(a>b)
return euclides_check((a-b), b);
if(a<b)
return euclides_check(a, (b-a));

                                               };


//Função que usa um gerador de números para gerar um número usado no teste do algoritmo de Pollard rho (p-1)
uint64_t generate_key (uint64_t value){
//Caso triviais: o valor a ser fatorado não é múltiplo de 2, 3, 5 (os menores números primos)
if(value%2!=0)
return 2;
if(value%3!=0)
return 3;
if(value%5!=0)
return 5;

//Caso geral escolhendo um palpite maior do que 7
//Semente para geração de números aleatórios
srand(time(NULL));
//Variáveis locais
uint64_t key;
//Selecionando uma chave aleatoriamente
selection:
key= 2+rand()%value-2;
//A chave escolhida deve ser coprima do número a ser fatorado 
if(euclides_check(value, key)!=1)
goto selection;

return key;
                                                };


//O algoritmo de Pollard rho (p-1)
void pollard_rho(uint64_t pollard_int/*Número a ser fatorado*/){
//Variáveis locais
uint64_t pollard_root, pollard_prime, temp1, temp2;
uint64_t i, power_counter; //Variáveis de iteração
uint64_t * power_array=NULL;
//Ajuste de variáveis
power_counter=0;

//Procedimentos
//Escolhendo um número coprimo a ser usado no algoritmo de Pollard
pollard_prime = generate_key(pollard_int);

//Estimando um limite superior para os expoentes no algoritmo de Pollard
pollard_root=(uint64_t)sqrt(pollard_int);

//Calculando os valores de potências do número coprimo a ser fatorado
for(i=1; i<=pollard_root; ++i){
power_counter++;
power_array = (uint64_t *)realloc(power_array, power_counter*sizeof(uint64_t));
power_array[power_counter-1] = pow(pollard_prime, i);
                              };


//Calculando os fatores primos do número a ser fatorado e exibindo o resultado na tela
printf("Eis uma lista de fatores de %li:\n", pollard_int);
for(i=0; i<power_counter; ++i){
temp1 = (power_array[i]-1)%pollard_int;
temp2 = euclides_check(temp1, pollard_int);
if(temp2!=1 && temp2!=pollard_int)
printf("%li, ", temp2);
                               };

printf("...\n");

//Limpando o cachê de memória
free(power_array);
                                      };

//*********************************************************************************************************************
//FUNÇÃO PRINCIPAL
int main(){
//Variáveis locais
uint64_t number;
//Recebendo o input
printf("Digite o número a ser fatorado.\n->");
scanf("%li", &number);

//Aplicando o algoritmo de Pollard rho (p-1)
pollard_rho(number);

//Finalizando a aplicação
return 0;
          }
