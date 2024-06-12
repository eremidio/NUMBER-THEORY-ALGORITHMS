//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UMA VERSÃO DO ALGORITMO EXTENDIDO DE EUCLIDES USANDO OPERAÇÕES DE MANIPULAÇÃO DE BITS 

/*
PARA MAIORES INFORMAÇÕES: A Course In Computational Algebraic Number Theory by Henri Cohen

*/


//*******************************************************************************************************************************************
//CABEÇALHO
#ifndef EXTENDED_GCD_FAST_H
#define EXTENDED_GCD_FAST_H
#include<stdint.h>
#include<inttypes.h>
#include<stdbool.h>


//*******************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void extended_gcd_fast(int64_t*, int64_t*, int64_t*, int64_t, int64_t);


//*******************************************************************************************************************************************
//FUNÇÕES
//Função que implementa uma versão binária do algoritmo de Euclides extendido
void extended_gcd_fast(int64_t* u, int64_t* v, int64_t* gcd, int64_t a, int64_t b){

  //Variáveis locais
  int64_t u_,v_, v1, v3, t1, t3;
  int64_t r, d, k=0;
  bool f1=false, f2=false;


  //Procedimento
    //Ajuste de variáveis 
    if(b>a){
      int64_t temp=a;
      a=b; b=temp;
      f1=true;
    }
    
    //Caso base:b=0
    stop1:
    if(b==0){
    
      if(f1==true){
        d=a; v_=1; u_=0;
        goto end;
        
                  }

      if(f1==false){
        d=a; v_=0; u_=1;
        goto end;
        
                  }


    };


    //Redução dos valores: algoritmo de divisão
    r=(a%b);
    a=b;
    b=r;
    if(b==0) goto stop1;

    //Remoção de fatores 2 em comum
    while(1){
      if((a&1) || (b&1)) break;
      else{
        a>>=1; b>>=1;
        k++;      
          };

    }


    //Checando a paridade do segundo elemento e ajuste de variáveis
    if(!(b&1)){
      int64_t temp=a;
      a=b; b=temp;
      f2=true;

    }
    
    u_=1; d=a; v1=b; v3=b;
    
    if((a&1)){
      t1=0; t3=(-1)*b;
      goto stop3;    
    }
    else{
      t1=(1+b)/2; t3=a/2;

    };  


    //Removendo fatores 2 de t1 e t3: ínicio loop euclidiano
    stop2:
    while(!(t3&1)){
      t3>>=1;
       if(!(t1&1)) t1>>=1;
       else t1=(t1+b)>>1;
    }

    //Ajuste de variáveis
    stop3:
    if(t3>0){
      u_=t1; d=t3;
    }
    else{
      v1=(b-t1); v3 =(-1)*t3;
    };

    //Ajuste de variáveis: fim do loop euclidiano
    t1=u_-v1;
    t3=d-v3;
    if(t1<0) t1+=b;

    if(t3!=0) goto stop2;

    //Fim do loop euclidiano
    v_=(d-(a*u_))/b;
    d<<=k;
    
    if(f2==true){
      int64_t temp=v_;
      v_=u_; u_=temp;
    }

    int64_t q=d/v3;
    u_-=(q*v_);


  //Resultado
  end:
  if(f1=true){
    (*u)=u_; (*v)=v_; (*gcd)=d;
  }  
  else{
    (*v)=u_; (*u)=v_; (*gcd)=d;
  }


};

//*******************************************************************************************************************************************
//FIM DO HEADER
#endif
