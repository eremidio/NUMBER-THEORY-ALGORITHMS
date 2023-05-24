//VAMOS CRIAR UM PROGRAM EM C QUE IMPLEMENTA O ALGORITMO DE SHOR PARA FATORIZAR NÚMEROS INTEIROS
//ESTE PROGRAMA NEM SEMPRE PRODUZ UM RESULTADO DESEJADO, DE FATO O ALGORITMMO USA NÚMEROS ALEÁTÓRIOS EM SUA IMPLMENTAÇÃO.
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o shor_factorization shor_factorization.c -lm

/*
O ALGORITMO DE SHOR É EXECUTADO NAS SEGUINTES ETAPAS:
1. DADO UM NÚMERO n A SER FATORADO TESTA-SE PRIMEIRO SE n É PAR: NESTE CASO UMA DECOMPOSIÇÃO EM NÚMEROS PRIMOS É DADA POR:
(n, n/2) E O ALGORITMO SE ENCERRA.
2. SELECIONA-SE UM NÚMERO ALEATÓRIO x ENTRE 2 E n.
3. É TESTADO SE x É UM DIVISOR DE n. CASO POSITIVO FATORES DE n FORAM ENCONTRADOS E O ALGORITMO SE ENCERRA.
4. ENCONTRA-SE UM EXPOENTE r TAL QUE (x^r)≡1 mod(n);
4. SE (x^(r/2)+1) NÃO FOR ZERO, OS FATORES PRIMOS SÃO DADOS POR mdc((x^(r/2)+1), n) E mdc((x^(r/2)-1), n), ONDE mdc DENOTA O
MÁXIMO DIVISOR COMUM QUE É ENCONTRADO VIA ALGORITMO DE LONGA DIVISÃO (EUCLIDES).

ESTE ALGORITMO SÓ É COMPUTACIONALMENTE VANTAJOSO PARA FATORAR NÚMEROS MUITO GRANDES. COMO O ADVENTO DA COMPUTAÇÃO QUÂNTICA SE ESPERA QUE NOVAS IMPLMENTAÇÕES DESTE ALGORITMO FUNCIONEM DE FORMA EFICAZ.
*/

//CABEÇALHO
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<time.h>

//FUNÇÕES
//Função que usa um gerador de números para gerar um número usado no teste do algoriutmo de Shor
long long int generate_key (long long int value){
//Semente para geração de números 
srand(time(NULL));
//Variáveis locais
long long int key;
key= 2+rand()%value-2;
return key;
                                                };

//Algoritmo de Euclides - usado para se checar se um fator primo foi encontrado usando um gerador de números aleatórios
long long int euclides_check(long long int a, long long int b){
//Variáveis
long long int bigger, smaller, residue;
//Ajuste de variáveis
if(a>b){
bigger = a;
smaller = b;
       };

if(a<b){
bigger = b;
smaller = a;
       };

//Algoritmo de Euclides
do{
residue = (bigger%smaller);
bigger= smaller;
smaller= residue;
  }while(residue>0);
return bigger;
                                                 };

//Função que calcula um expoente do algoritmo de Shor
long long int get_exponent(long long int number1/*semente aleatória*/, long long int number2/*número a ser fatorado*/){
//Variáveis locais
long long int residue;
long long int exponent;
long long int temp;

//Caso geral
for(int i=1; i<1000000; ++i){
temp = pow(number1, i);
residue= temp%number2;

if(residue==1 && (i%2)==0){
exponent = i;
break;
                          };

                            };

return exponent;
                                                                                                                      }; 


//Algoritmo de Shor
void shor_algorithm(long long int shor_int){
//Variáveis locais
int counter=0;
long long int shor_factor1, shor_factor2, shor_exponent, shor_random, shor_test;

//Testando se o número a ser fatorado é par
if((shor_int%2)==0){
shor_factor1=2;
shor_factor2=shor_int/2;
printf("Fator1:%lli.\nFator2:%lli.\n", shor_factor1, shor_factor2);
return;
                   };

//Testando se um fator primo já foi encontrado
step1:
counter++;
if(counter>15000000){
printf("Algoritmo falhou.\n");
return;
                    };
//O número gerado aleatoriamente deve ser coprimo com o número a ser fatorado
shor_random=generate_key(shor_int);
if(euclides_check(shor_random, shor_int)!=1)
goto step1;


if((shor_int%shor_random)==0){
shor_factor1=shor_random;
shor_factor2=shor_int/shor_random;
printf("Fator1:%lli.\nFator2:%lli.\n", shor_factor1, shor_factor2);
return;
                             };

//Prosseguindo com o teste
//Calculando o expoente 
shor_exponent = get_exponent(shor_random, shor_int);
if(shor_exponent==0)
goto step1;

//Testando a fatorização do número de interesse
step2:
shor_test = pow(shor_random, (shor_exponent)/2)+1;
if(shor_test==0)
goto step1;

shor_factor1= euclides_check(shor_test, shor_int);
shor_test = pow(shor_random, (shor_exponent)/2)-1;
shor_factor2= euclides_check(shor_test, shor_int);

//Exibindo o resultado
printf("Fator1:%lli.\nFator2:%lli.\n", shor_factor1, shor_factor2);


                                           };


//FUNÇÃO PRINCIPAL
int main(){
//Variáveis
long long int number;


//Recebendo input do usuário
printf("Digite un número inteiro para que fatores deste número seja calculado.\n->");
scanf("%lli", &number);


//TESTES, USE /**/ APÓS OS TESTES
    //long long int test1 = euclides_check(39, 14);
    //printf("%lli\n", test1);
    //long long int test2 = get_exponent(4, 79);
    //printf("%lli\n", test2);

//Calculando os fatores do número a ser decomposto
shor_algorithm(number);

//Finalizando a aplicação
return 0;
          }
