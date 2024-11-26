//VAMOS CRIAR UM PROGRAMA PARA FATORAR NÚMEROS INTEIROS USANDO O GRUPO DE PONTOS RACIOANIS EM UMA HIPÉRBOLE

/*
PARA MAIORES INFORMAÇÕES: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/hyperbola_group.h
                          https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/circle_group_factorization.h

*/


//*************************************************************************************************************************
//CABEÇALHO
#ifndef HYPERBOLA_GROUP_FACTORIZATION_H
#define HYPERBOLA_GROUP_FACTORIZATION_H
#include"hyperbola_group.h"
#include"prime_power_detection.h"

//*************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t gcd_s64(int64_t, int64_t);
struct hyperbola_point set_initial_point(int64_t);
int64_t calculate_prime_factor(struct hyperbola_point, int64_t);
void hyperbola_group_factorization(int64_t , int64_t);

//*************************************************************************************************************************
//FUNÇÕES

//Função que calcula o mdc de dois inteiros de 64 bits
int64_t gcd_s64(int64_t a, int64_t  b){

  if(b==0) return a;
  else return gcd_s64(b, (a%b));

};


//Função que calcula um ponto racional na hipérbola unitária
struct hyperbola_point set_initial_point(int64_t n){

  //Semente parageração de nmúmeros
  srand(time(NULL));
  
  //Variáveis locais
  struct hyperbola_point p1;
  __int128_t t;
  int64_t x=0, y=0, x_squared;
  int64_t root=sqrt(n);

  //Procedimentos
    //Gerando valores x e y que satifazem a relação x²-y²=1 (mod n)
      y=2+rand()%n;
      if(y>n) x%=n;
  
      //Loop  principal
        while(1){
          t=1+(y*y); t%=n;
          x_squared=t;
          if(fast_square_detection(x_squared, &x)==true) break;
          else x++;
          if(x==n) break;
          
        }

    //Ajuste do resultado final
    p1.x=x;
    p1.y=y;
    p1.p=n;

  //Resultado
  return p1;

};


//Função que computa fatores primos não triviais de um inteiro de 64 bits usando pontos racionais em hipérboles
int64_t calculate_prime_factor(struct hyperbola_point p1, int64_t n){


  //Variáveis locais
  struct hyperbola_point p3={0, 0, p1.p}, Q=p1, temp;
  int64_t factor=1, t1=1, t2=1;

    //Procedimentos
      //Cálculo do resultado
      while(n>0){
      
        //Checando a paridade de n
        if(n&1){
          p3=hyperbola_pointwise_addition(p1, Q);
          t1=(p3.x-1);  t2=(p3.x+1);
          factor=gcd_s64(p3.p, t1); if(factor>1 &&  factor<n) return factor;
          factor=gcd_s64(p3.p, t2); if(factor>1 &&  factor<n) return factor;

          t1=(p3.y-1);  t2=(p3.y+1);
          factor=gcd_s64(p3.p, t1); if(factor>1 &&  factor<n) return factor;
          factor=gcd_s64(p3.p, t2); if(factor>1 &&  factor<n) return factor;

  
        }
  
        //Atualizando variáveis para a próxima iteração
        temp=hyperbola_pointwise_doubling(Q);
        Q=temp;
        n>>=1;

      }

      //Testando se o ponto final gera um fator não trivial
      p3=hyperbola_pointwise_addition(p1, Q);
      t1=(p3.x-1);  t2=(p3.x+1);
      factor=gcd_s64(p3.p, t1); if(factor>1 &&  factor<n) return factor;
      factor=gcd_s64(p3.p, t2); if(factor>1 &&  factor<n) return factor;

      t1=(p3.y-1);  t2=(p3.y+1);
      factor=gcd_s64(p3.p, t1); if(factor>1 &&  factor<n) return factor;
      factor=gcd_s64(p3.p, t2); if(factor>1 &&  factor<n) return factor;
 
  //Resultado
  return factor;

};


//Função que fatora número inteiro usando o grupo de pontos em uma hipébole
void hyperbola_group_factorization(int64_t n, int64_t ord){

  
  //Variáveis locais
  struct hyperbola_point p1;
  __int128_t t1=1, t2=1;
  int64_t factor=1;
  int trials=(-1);

  //Procedimento
    //Selecionando um ponto inicial no círculo unitário
    restart:
    trials++;

    p1=set_initial_point(n);

    //Cálculando múltiplos deste pontos
    factor=calculate_prime_factor(p1, n);

    //Resultado da execução do algoritmo
    if(factor>1 &&  factor<n){
      printf("Fatores de %li encontrados: %li e %li\n", n,  factor, (n/factor));
      return;
    }

    //Reinicializando o algoritmo
    if(trials>50){
       printf("O algoritmo falhou!\n");
    } else  goto restart;
};



//*************************************************************************************************************************
//FIM DO HEADER
#endif
