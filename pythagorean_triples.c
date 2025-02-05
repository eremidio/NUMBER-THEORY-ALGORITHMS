//VAMOS ESCREVER UM PROGRAMA QUE CALCULA TRIPLAS PITAGÓRICAS A PARTIR DO ALGORITMO DE EUCLIDES
//COMPILAR ESTE PORGRAMA COM O COMANDO: gcc -o pythagorean_triples pythagorean_triples.c

/*
O TEOREMA DE PITÁGORAS RELACIONA AS DIMENSÕES DE UM TRIÂNGULO RETÂNGULO DE LADOS a, b, c COM c>a,b (O MAIOR LADO É CHAMADO DE HIPOTENUSA), POR MEIO DA RELAÇÃO: a²+b²=c².
NUMÉROS INTEIROS SATISFAZENDO ESTA RELAÇÃO FORMAM AS CHAMADAS TRIPLAS PITAGÓRICAS.
UM TEOREMA GARANTE QUE AS TRIPLAS PITAGORÍCAS SÃO INFINITAS.
SE a, b, c FORMAM UMA TRIPLA PITAGÓRICA, ENTÃO PARA QUALQUER k INTEIRO ka, kb, kc TAMBÉM FORMA UMA TRIPLA PITAGÓRICA.

AS FÓRMULAS DE EUCLIDES FORNECEM UM ALGORITMO PARA PRODUZIR TRIPLAS PITAGÓRICAS LINEARMENTE INDEPDENTE (QUE NÃO SÃO DEFINIDAS A MENOS DE UM FATOR MULTIPLICATIVO).
PARA m>n>0, INTEIROS SENDO UM PARA E OUTRO ÍMPAR TEMOS QUE OS TERMOS DA TRIPLA PITAGÓRICA SÃO DEFINIDAS POR:
a=m²-n², b=2mn, c=m²+n².

SUBSTITUIÇÃO DIRETA NOS MOSTRA QUE PARA ESTES VALORES O TEOREMA DE PITÁGORAS É VÁLIDO.

DADO UM NÚMERO COMPLEXO z=a+bi, TEMOS QUE z.z=(a²-b²)+(2ab)i  E |z|²=z*z=a²+b².
ESTAS SÃO EXATAMENTE AS FÓRMULASDE EUCLIDES PARA AS TRIPLAS PITAGÓRICAS.
DESTA FORMA COMPLEXOS DA FORMA z=a+bi, COM a, b INTEIROS E DE PARIDADES DIFERENTES NOS DÃO OUTRA FORMA DE CALCULA TRIPLAS PITAGÓRICAS.


*/

//*************************************************************************************************************************
//CABEÇALHO
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
//*************************************************************************************************************************
//FUNÇÃO PRINCIPAL

int main(){

  //Variáveis locais
  long long int limit;
  long long int m, n, a, b, c;
  bool end;


  //Procedimentos
    //Recebendo input do usuário
    printf("Usuário digite um limitante superior para as triplas pitagóricas: ");
    scanf("%lli", &limit);


    //Printando as triplas pitagóricas na tela
    printf("Eis a sua lista de triplas pitagóricas:\n");
    
    for(m=2; m<limit; m++){
    
      //Caso 1: m é par
      if(!(m&1)){
        for(n=1; n<m; n+=2){
          a=(m*m)-(n*n);
          b=2*m*n;
          c=(m*m)+(n*n);

            //Finalizando o loop
            if(c>limit){
              end=true;
              break;
            } 

          printf("(%lli, %lli, %lli)\n", a, b, c);
                  };
          };


      //Caso 2: m é par
      if(m%2==1){

        for(n=2; n<m; n+=2){
          a=(m*m)-(n*n);
          b=2*m*n;
          c=(m*m)+(n*n);

          //Finalizando o loop
          if(c>limit){
            end=true;
            break;
          } 

        printf("(%lli, %lli, %lli)\n", a, b, c);
       };
     };

      if(end==true) break;
    };

  //Finalizando a aplicação
  return 0;

};
