//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UMA VERSÃO DO ALGORITMO EXTENDIDO DE EUCLIDES USANDO OPERAÇÕES DE MANIPULAÇÃO DE BITS 

/*
PARA MAIORES INFORMAÇÕES: A Course In Computational Algebraic Number Theory by Henri Cohen
                          Prime Numbers A computational Perspective, by Richard Crandall and Carl Pomerance
                          Number Theoretical Algorithms in Criptography by O. N. Vasilenko

*/


//*******************************************************************************************************************************************
//CABEÇALHO
#ifndef BINARY_EXTENDED_GCD_H
#define BINARY_EXTENDED_GCD_H
#include<stdint.h>
#include<inttypes.h>
#include<stdbool.h>


//*******************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void binary_extended_gcd(int64_t*, int64_t*, int64_t*, int64_t, int64_t);


//*******************************************************************************************************************************************
//FUNÇÕES
//Função que implementa uma versão binária do algoritmo de Euclides
//extendido ( ax+by=mdc(a,b))
void binary_extended_gcd(int64_t* U, int64_t* V, int64_t* gcd,
                         int64_t a, int64_t b){

  //Variáveis locais
  __int128_t u, v, d, q, r;
  __int128_t t1, t3, v1, v3;
  int k=0;
  int f1=0, f2=0;

  //Procedimentos
    //Ajuste dos operandos
    if(b>a){
      int64_t temp = a;
      a=b;
      b=temp;
      f1=1;
    }
    else{
      f1=0;
    }

    //Caso base: b=0
    if(b==0){
      if(f1==0){
        u=1;
        v=0;
        d=a;
        goto yield_result;
      }
      else{
        u=0;
        v=1;
        d=a;
        goto yield_result;
      }
    }

    //Reduzindo a ordem dos operandos: necessário caso a ordem dos números seja muito diferente
    r=(a%b);
    q=(a-r)/b;
    a=b;
    b=r;

    //Caso base: resto nulo
    if(b==0){
      if(f1==0){
        u=0;
        v=1;
        d=a;
        goto yield_result;
      }
      else{
        u=1;
        v=0;
        d=a;
        goto yield_result;
      }
    }


    //Removendo fatores 2 em comum
    while(!(a&1) && !(b&1)){
      b>>=1;
      a>>=1;
      k++;
    }

    //Ajustando a paridade dos operandos
    if(!(b&1)){
      int64_t temp = a;
      a=b;
      b=temp;
      f2=1;
    }
    else{
      f2=0;
    }

    //Ajuste de variáveis usadas no loop euclidiano
    u=1;
    d=a;
    v1=b;
    v3=b;

    if((a&1)){
      t1=0;
      t3=(-b);
      goto a_odd_step;
    }
    else{
      t1=((b+1)>>1);
      t3=(a>>1);
    }


    //Loop euclidiano
    while(1){

      //Ajuste da paridade das variáveis usadas no loop euclidiano
      if(!(t3&1)){
        t3=(t3>>1);

        if(!(t1&1))
          t1=(t1>>1);
        else
          t1=((t1+b)>>1);

        continue;
      }

      //Ajustando das variáveis usadas no loop euclidiano
      a_odd_step:

      if(t3>0){
        u=t1;
        d=t3;
      }
      else{
        v1=b-t1;
        v3=(-t3);
      }

      //Verificando se os operandos foram reduzidos
      t1=(u-v1);
      t3=(d-v3);

      if(t1<0)
        t1+=b;

      if(t3==0)
        break;

    };


    //Ajuste final do resultado
    v=(d-a*u)/b;

    //Restaurando os fatores 2 removidos anteriormente
    d<<=k;

    //Se os operandos foram trocados no ajuste de paridade
    //trocar também os coeficientes correspondentes
    if(f2==1){
      __int128_t temp = u;
      u=v;
      v=temp;
    }

    //Desfazendo a redução euclidiana inicial
    u-=(v*q);

    //Desfazendo a troca inicial dos operandos
    if(f1==0){
      __int128_t temp = u;
      u=v;
      v=temp;
    }


  //Resultado
  yield_result:
  (*U)=(int64_t)u;
  (*V)=(int64_t)v;
  (*gcd)=(int64_t)d;

};


//*******************************************************************************************************************************************
//FIM DO HEADER
#endif
