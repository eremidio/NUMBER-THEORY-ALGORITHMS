//VAMOS CRIAR UM PROGRAMA QUE CALCULAS AS CHAMADAS SEQUÊNCIAS DE FAREY

/*
AS CHAMADAS SEQUÊNCIAS DE FAREY SÃO SEQUÊNCIAS DE FRAÇÕES COMPLETAMENTE REDUZIDAS.
ESTAS SEQUÊNCIAS NORMALMENTE SÃO RESTRITAS ENTRE 0 E 1.

AS SEQUÊNCIAS DE FAREY SÃO MUITO IMPORTANTES EM DIVERSAS ÁREAS DA MATEMÁTICA TENDO UMA RELAÇÃO DIRETA COM A CONJECTURA DE 
COLLATZ, A HIPÓTESE DE RIEMANN, APROXIMAÇÃO DE IRRACIONAIS, CICLOS DE FORD EM GEOMETRIA, TEORIA DOS FRACTAIS, ALÉM DE APARECER
EM UMA SÉRIE DE RELAÇÕES EXTREMAMENTE ÚTEIS ENVOLVENDO FUNÇÕES ESPECIAIS.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Farey_sequence

*/

//*************************************************************************************************************************
//CABEÇALHO
#ifndef FAREY_SEQUENCE_H
#define FAREY_SEQUENCE_H
#include<stdio.h>
#include<math.h>

//CONSTANTES GLOBAIS
enum ordering{Up, Down};
//*************************************************************************************************************************
//DECLARAÇÕES DE FUNÇÕES
void generate_farey_sequence(int, enum ordering);

//*************************************************************************************************************************
//FUNÇÕES
void generate_farey_sequence(int n, enum ordering x){
//Variáveis locais
int a, b, c, d, k;
//Procedimentos
//Ajuste de variáveis
a=0, b=1; c=1; d=n;
if(x==Down)
a=1; c=n-1;

//Printando o primeiro elemento da sequencia
printf("F(%i) = {%i/%i", n-1, a, b);

//Loop principal: ordem crescente
if(x==Up){
while(c<=n){
k=floor(n+b/d);
a=c;
b=d;
c=(k*c)-a;
d=(k*d)-b;
printf(", %i/%i", a, b);
           };
         };

//Loop principal: ordem decrescente
if(x==Down){
while(a>0){
k=floor(n+b/d);
a=c;
b=d;
c=(k*c)-a;
d=(k*d)-b;
printf(",%i/%i", a, b);
          }
            };

printf("}\n");
                                                    };

//*************************************************************************************************************************
//FIM DO HEADER
#endif
