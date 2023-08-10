//VAMOS CRIAR UM PROGRAMA QUE CALCULA RAÍZES QUADRADAS AMENOS DE UMA RELAÇÃO DE CONGRUÊNCIA USANDO TENTATIVA E ERRO
//COMPILAR ESTE PROGRAMA COM: gcc modular_square_root2  modular_square_root2.c


/*
UM NÚMERO r É DEFINIDO COMO A RAÍZ QUADRADA DE UM NÚMERO n A MENOS DE UMA CONGRUÊNCIA ENVOLVENDO UM PRIMO p SE r²= n (mod p).
*/

//***************************************************************************************************************************
//CABEÇALHO
#include<stdio.h>
#include"mod_bin_exponentiation.h"
//VARIÁVEIS GLOBAIS
#define MAX_SEARCH 1000000000000000

//***************************************************************************************************************************
//FUNÇÕES
uint64_t modular_sqrt(uint64_t n, uint64_t p){
//Variáveis locais
uint64_t i;
uint64_t tester = mod_pow(n,((p-1)/2), p);

//Descartando quadrados não residuais
if(tester!=1)
return 0;

for(i=n; ; ++i){
if(((i*i)%p)==n)
return i;
if(i>MAX_SEARCH)
return 0;
               };
                                             };



//***************************************************************************************************************************
//FUNÇÃO PRINCIPAL
//Função principal
int main(){
//Variáveis locais
uint64_t n, p, root;
//Procedimentos
//Recebendo input do usuário
printf("Digite um número primo ímpar: ");
scanf("%lu", &p);
printf("Digite um número inteiro: ");
scanf("%lu", &n);

//Calculando raíz quadrada a menos de uma relação de congruência
root = modular_sqrt(n, p);

if(root==0)
printf("Não foram em contradas raízes quadradas de %lu (mod %lu)\n", n, p);
else
printf("Raíz quadrada de %lu (mod %lu)=%lu.\n", n, p, root);

//Finalizando a aplicação
return 0;

          }
