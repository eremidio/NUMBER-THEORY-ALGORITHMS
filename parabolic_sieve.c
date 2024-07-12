//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DA PENEIRA QUADRÁTICA (PARABÓLICA) PARA COMPUTAR NÚMEROS PRIMOS
//COMPILAR ESTE PROGRAMA COM O COMANDO: clang -o parabolic_sieve parabolic_sieve.c -lm


/*
O ALGORITMO DA PENEIRA QUADRÁTICA (PARABÓLICA) USA A CURVA DE EQUAÇÃO x=y², PARA GERAR NÚMEROS PRIMOS. PONTOS NESTA CURVA TEM AS
COORDENADAS (y², y) OU (y², -y). SELECIONANDO OS PONTOS DA CURVA COM COORDENADAS INTEIRAS É POSSÍVEL MOSTRAR QUE OS PONTOS DE 
INTERSEÇÃO DAS RETAS CONECTANDOS DOIS PONTOS UM ACIMA DO EIXO x (y POSITIVO) E OUTRO ABAIXO DO EIXO x (y NEGATIVO) COM O EIXO x
TEM COORDENADA (n, 0) COM n INTEIRO, SENDO n UM QUADRADO PERFEITO OU PRIMO.

PARA MAIORES INFORMAÇÕES: https://mathworld.wolfram.com/QuadraticSieve.html
*/


//**************************************************************************************************************************
//CABEÇALHO
#include"prime_power_detection.h"
#include<stdio.h>



//**************************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo da peneira parábolica

  //Variáveis locais
  void parabolic_sieve(int64_t n){
  int64_t x1, x2, y1, y2, intersection, temp;
  double slope;
  bool boolean[n];
  int64_t i, j, k;//Variáveis de iteração

  //Procedimento
    //Ajuste do array de booleanos
    for(k=0; k<n; ++k){
      if(k==0 || k==1){
        boolean[k]=false;
        continue;
      };

      boolean[k]=true;
    };



    //Loop principal
    for(i=2; i<n; ++i){
    
      //Definindo as coordenadas dos pontos acima do eixo x
      y1=i; x1=y1*y1;

      for(j=2; j<n; ++j){
        //Definindo as coordenadas dos pontos abaixo do eixo x
        y2=(-1)*j; x2=y2*y2;
        if(x1==x2) continue;

        //Calculando a inclinação das retas
        slope=(x2-x1)/(y2-y1);

        //Calculando a intesercção da reta com o ponto
        intersection = x1-(slope*y1);
        if(intersection<n) boolean[intersection]=false;

      };

    };



    //Printando os números primos na tela
    printf("Eis a sua lista de primos até %li: ", n);
    for(i=0; i<n; i++){
      if(boolean[i]==true && fast_square_detection(i, &temp)==false)
        printf("%li, ", i);
    };

    printf("...\n");
 
};

//**************************************************************************************************************************
//FUNÇÃO PRINCIPAL
int main(){

  //Variáveis locais
  int64_t number;

  //Procedimentos  
    //Recebendo input do usuário
    printf("Vamos calcular os números primos até um certo valor usando a peneira quadrática (parabólica).\n");
    printf("Usuário digite um número inteiro: ");
    scanf("%li", &number);
  
    //Calculando primos usando a peneira parabólica
    parabolic_sieve(number);


  //Finalizando a aplicação
  return 0;

}
