//VAMOS CRIAR UM PROGRAMA QUE FATORA NÚMEROS INTEIROS USANDO POLINÔMIOS DO SEGUNDO GRAU

/*
DAS IDENTIDADES (a+b)²=a²+2ab+b² E (a-b)²=a²-2ab+b² SEGUE-SE QUE (a+b)²=(a-b)²+4ab. SEJA n UM NÚMERO A SER FATORADO E p, q FATORES PRIMOS TAIS QUE n=pq. TEMOS DA
IDENTIDADE ANTERIOR COM r=p+q E s=p-q QUE r²=s²+4n, COMO r>s VEMOS QUE O PROBLEMA DE FATORAR UM NÚMERO INTEIRO SE REDUZ AO PROBLEMA DE RESOLVER UMA EQUAÇÃO DO SEGUNDO GRAU OU EQUIVALENTEMENTE A PROCURAR VALORES r E s SATISFAZENDO A IDENTIDADE ACIMA.

PARA MAIORES INFORMAÇÕES: https://www.codeproject.com/Articles/281718/Factoring-Algorithms-for-Selected-RSA-Numbers

*/


//*******************************************************************************************************************************************************************
//CABEÇALHO
#ifndef TRINOMIAL_INTEGER_FACTORIZATION_H
#define TRINOMIAL_INTEGER_FACTORIZATION_H
#include<stdint.h>
#include<stdbool.h>
#include<math.h>
#include<stdio.h>


//*******************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool is_perfect_square(int64_t, int64_t*);
void trinomial_integer_factorization(int64_t);


//*******************************************************************************************************************************************************************
//FUNÇÕES
//Função que checa se um número é um quadrado perfeito
bool is_perfect_square(int64_t n, int64_t* sqrt_n){
//Variáveis locais
int64_t odd=1;

//Procedimentos
//Ajuste de variáveis
(*sqrt_n)=0;

//Loop principal
while(n>0){
n-=odd;
odd+=2;
(*sqrt_n)=(*sqrt_n)+1;

if(n<0)
return false;

          };

return true;
                                                  };

//Função que fatoramum número inteiro usando um trinômio do segundo grau
void trinomial_integer_factorization(int64_t n){
//--------------------------------------------------------------------------------------
//Caso trivial: n par
if((n%2)==0){
printf("Fatores de %li encontrados: 2 e %li\n", n, (n/2));
return;
            }

//--------------------------------------------------------------------------------------
//Caso geral: n ímpar
//Variáveis locais
int64_t r, s, r_squared, tester, p, q;

//Procedimentos
//Loop principal
for(s=2; s<(n/2); s+=2){
r_squared=(s*s)+(4*n);


if(is_perfect_square(r_squared, &r)==true){
factorization:
p=((r+s)/2);
q=((r-s)/2);
printf("Fatores de %li encontrados: %li e %li\n", n, p, q);
return;
                                          };
                       };


//Resultado da execução do algoritmo
primality:
printf("%li é primo\n", n);
                                              };


//*******************************************************************************************************************************************************************
//FIM DO HEADER 
#endif
