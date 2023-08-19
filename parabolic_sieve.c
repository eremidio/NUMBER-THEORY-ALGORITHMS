//VAMOS CRIAR UM PROGRAM QUE IMPLMENTA O ALGORITMO DA PENEIRA QUADRÁTICA (PARABÓLICIA) PARA COMPUTAR NÚMEROS PRIMOS
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o parabolic_sieve parabolic_sieve.c -lm

/*
O ALGORITMO DA PENEIRA QUADRÁTICA (PARABÓLICA) USA A CURVA DE EQUAÇÃO x=y², PARA GERA NÚMEROS PRIMOS. PONTOS NESTA CURVA TEM AS
COORDENADAS (y², y) OU (y², -y). SELECIONANDO OS PONTOS DA CURVA COM COORDENADAS INTEIRAS É POSSÍVEL MOSTRAR QUE OS PONTOS DE 
INTERSEÇÃO DAS RETAS CONECTANDOS DOIS PONTOS UM ACIMA DO EIXO x (y POSITIVO) E OUTRO ABAIXO DO EIXO x (y NEGATIVO) COM O EIXO x
TEM COORDENADA (n, 0) COM n INTEIRO.

PARA MAIORES INFORMAÇÕES: https://mathworld.wolfram.com/QuadraticSieve.html
*/


//**************************************************************************************************************************
//CABEÇALHO
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<math.h>


//**************************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo da peneira parábolica
void parabolic_sieve(int n){
int x1, x2, y1, y2, intersection;
double slope;
int boolean[n];
int i, j, k;//Variáveis de iteração

//Procedimento

//TESTE, USE UM // APÓS O FIM DO MESMO
//printf("Teste 1.\n");

//Ajuste do array de booleanos
for(k=0; k<n; ++k){
if(k==0 || k==1){
boolean[k]=0;
continue;
                };
boolean[k]=1;
                  };

//TESTE, USE UM // APÓS O FIM DO MESMO
//printf("Teste 2.\n");

//Loop principal
for(i=2; i<n; ++i){
//Definindo as coordenadas dos pontos acima do eixo x
y1=i;
x1=y1*y1;

for(j=2; j<n; ++j){
//TESTE, USE UM // APÓS O FIM DO MESMO
//printf("Teste 4.\n");

//Definindo as coordenadas dos pontos abaixo do eixo x
y2=(-1)*j;
x2=y2*y2;

if(x1==x2)
continue;

//Calculando a inclinação das retas
slope=(x2-x1)/(y2-y1);

//Calculando a intesercção da reta com o ponto
intersection = x1-(slope*y1);
boolean[intersection]=0;
                   };

                   };

//TESTE, USE UM // APÓS O FIM DO MESMO
//printf("Teste 3.\n");

//Printando os números primos na tela
printf("Eis a sua lista de primos até %d: ", n);
for(i=0; i<n; i++){
if(boolean[i]==1)
printf("%d, ", i);
                  };
printf("...\n");
 
                            };

//**************************************************************************************************************************
//FUNÇÃO PRINCIPAL

int main(){
//DEFINIÇÃO DE VARIÁVEIS
int number;
//RECEBENDO INPUT DO USUÁRIO E EXIBINDO OS NÚMEROS PRIMOS
printf("Vamos calcular os números primos até um certo valor usando a peneira quadrática (parabólica).\n");
printf("Usuário digite um número inteiro: ");
scanf("%d", &number);
parabolic_sieve(number);


//FINALIZANDO A APLICAÇÃO
return 0;
          }
