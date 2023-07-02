//VAMOS CRIAR UM PROGRAMA EM C QUE CALCULA O VALOR DE x NO TEOREMADE RESÍDUO CHINÊS
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o chinese_remainder_theorem chinese_remainder_theorem.c

/*

O TEOREMA DE RESÍDUO CHINÊS AFIMA QUE DADO RELAÇÕES DE CONGRUÊNCIA:
x = a(1) mod(n(1))
x = a(2) mod(n(2))
....
x = a(k) mod(n(k))

PROVIDO QUE O TERMOS DA SEQUÊNCIA n(1), n(2), ... ; SEJAM RELATIVAMENTE PRIMOS E PARA TODOi=1,2,...; 0<a(i)<n(i).
EXISTE UM ÚNICO x QUE SATISFAZ ESTAS RELAÇÕES A MENOS DE UMA RELAÇÃO DE CONGRUÊNCIA COM N = n(1).n(2).(...).n(k).

VÁRIAS TÉCNICAS EXISTEM PARA CALCULAR O VALOR DE x QUE SATIFAZ ESTAS RELAÇÕES.
O TEOREMA PODE SER EXTENDIDO PARA CASOS EM QUE n(1), n(2), ... ; NÃO SÃO RELATIVAMENTE PRIMOS.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Chinese_remainder_theorem

*/

//**************************************************************************************************************************
//CABEÇALHO
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
#include<assert.h>

#define MAX_X 1e12 //Constante que ajusta o valor máximo a ser investigado

//**************************************************************************************************************************
//FUNÇÕES
uint64_t chinese_residue_theorem(uint64_t a[], uint64_t n[], uint64_t k){
//Variáves locais
uint64_t x, status;
uint64_t i;//Variáveis de iteração
//Procedimentos
//Calculando o valor x
x=a[0];//Valor inicial

while(true){
status=0;//Variável de controle
//Checando se as relações de congruência são satisfeitas
for(i=1; i<k; ++i){
if(x%n[i]!=a[i]){
status++;
break;
                };
                  };
if(status==0)//Condição para que todas as relações de congruências sejam satisfeitas
break;
else
x+=n[0];

//Restrição de valores a serem investigados
assert(x<MAX_X);

           };

return x;
                                                                        };

//**************************************************************************************************************************
//FUNÇÃO PRINCIPAL
int main(){
//Variáveis locais
uint64_t k, i;
uint64_t N=1;

//Procedimentos
//Recebendo input do usuário
printf("Usuário digite o número de equações modulares: ");
scanf("%lu",&k);

//Preenchendo os arrays contendo os valores de a(i) e n(i)
uint64_t a[k], n[k];
for(i=0; i<k; ++i){
printf("Entre com o valor de n(%li) (o maior dos n(i)'s deve vir primeiro): ", i);
scanf("%lu", &n[i]);
printf("Entre com o valor de a(%li): ", i);
scanf("%lu", &a[i]);
N*=n[i];//Ajuste de variável
                  }; 

for(i=0; i<k; ++i)
printf("x ≡ %lu mod(%lu)\n", a[i], n[i]);

//Computando valor de x e exibindo o resultado
printf("x = %lu+%luk\n", chinese_residue_theorem(a, n, k), N);

//Finalizandoa palicação
return 0;
          };
