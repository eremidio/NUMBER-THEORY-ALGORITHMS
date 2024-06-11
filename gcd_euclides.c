//VAMOS ESCREVER UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE EUCLIDES PARA SE CALCULAR O MDC DE DOIS NÚMEROS INTEIROS
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o gcd_euclides gcd_euclides.c

/*EXPLICAÇÃO DO ALGORITMO DE EUCLIDES:

DADOS DOIS NÚMEROS 'A' E 'B' COM A>B DIVIMOS A POR B E OBTEMOS A SEGUINTE EXPRESSÃO A=P(0)*B+Q(0) COM Q(0)<B,
EM SEGUIDA PROSSEGUIMOS COM B=Q(0)*P(1)+Q(1)--> Q(0)=Q(1)*P(2)+Q(2) --> Q(1)=Q(2)*P(3)+Q(3) -->  ...
REPETE-SE ESSE CÁLCULO ATÉ QUE O N-ÉSIMO TERMO DA SEQUÊNCIA SEJA Q(N)=0. O MÁXIMO DIVISOR COMUM DE A E B É O TERMO Q(N-1).
É UM DOS ALGORITMOS MAIS BÁSICOS E ESSENCIAIS EM TEORIA DE NÚMEROS. ELE PODE SER IMPLEMENTADO USANDO LOOPS OU RECURSÃO.

*/

/*CABEÇALHO*/
#include <stdio.h>
#include<stdint.h>


//*****************************************************************************************************************************
//FUNÇÕES
//Versão que utiliza somente operações de subtração
int64_t gcd_slow(int64_t a, int64_t b){

  //Procedimentos
    //Loop principal
    while(1){
      if(b==a) break;
      if(a>b) a-=b;
      if(b>a) b-=a;

            }

  //Resultado
  return a;

}


//Versão que usa aritmética modula: algoritmo de divisão de Euclides
int64_t gcd_fast(int64_t a, int64_t b){

  //Variáveis locais
  int64_t remainder;

  //Procedimentos
    //Ajuste de variáveis
    if(b>a){
      int64_t temp=a;
      a=b; b=temp;
    };

      
    //Loop principal
    do{
    
      remainder=(a%b);
      a=b;
      b=remainder;

    }while(b>0);


  //Resultado
  return a;

}



//*****************************************************************************************************************************
//FUNÇÃO PRINCIPAL
int main(){

  //Variáveis locais
  int64_t a, b;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um inteiro positivo: ");
    scanf("%li", &a);
    printf("Digite um inteiro positivo: ");
    scanf("%li", &b);

    //Executando o algoritmo de Euclides
    printf("[Versão lenta só usando subtração]: mdc(%li,%li)=%li\n",a , b, gcd_slow(a, b));
    printf("[Versão rápida/Algoritmo de divisão]: mdc(%li,%li)=%li\n",a , b, gcd_fast(a, b));


  //Finalizando a aplicação
  return 0;
    
      

}
