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
//Função que implementa uma versão binária do algoritmo de Euclides extendido ( ax+bx=mdc(a,b))
void binary_extended_gcd(int64_t* a, int64_t* b, int64_t* gcd, int64_t x, int64_t y){

  //Variáveis locais
  int64_t u, v, d;
  int64_t t1, t3, v1, v3;
  int bit_shift=0;
  bool f1=false, f2=false;

  //Procedimentos
    //Redução da ordem dos operandos
    if(x<y){
      int64_t temp=y;
      y=x; x=temp;
      f1=true;
    }
   
    //Caso base: b=0
    base_case:
    if(y==0){
      if(f1==false){
        u=1; v=0; d=x;
        goto yield_result;
      }

      if(f1==true){
        u=0; v=1; d=x;
        goto yield_result;
      }

    };

    //Redução
      /*NOTA: Essa etapa é feita para que os números de bits de x e y, o algoritmo em questão se aplica se apenas um dos
            argumentos for um inteiro de precisão multipla, nesse caso as variáveis auxiliares t1, t3, v1, v3
            necessitam ser um inteiro de precisão múltipla
      */
      int64_t r=(x%y);
      int64_t q=(x/y);
      x=y; y=r;
      if(y==0) goto base_case;

    //Removendo os fatores 2 em comum
    while(!(x&1) && !(y&1)){
      x>>=1; y>>=1;
      bit_shift++;
    };     

    
    //Inicializando variáveis
    if(!(y&1)){
      int64_t temp=y;
      y=x; x=temp;
      f2=true;
    }

    u=1; d=x; v1=0; v3=y;
    if(x&1){
      t1=0; t3=(-y);
      goto positive_check;    
    }
    else{
      t1=((y+1)>>2); t3=(x>>1);
    };

    //Loop principal: redução euclidiana
    while(t3>0){

      //Removendo fatores 2 restante
      if(!(t3&1)){
        t3>>=1;
        if(!(t1&1)) t1>>=1;
        else t1=((t1+y)>>1);  
      }

      //Ajuste de variáveis
      positive_check:
      if(t3>0){
        u=t1; d=t3;
      } 
      else{
        v1=(y-t1); v3=(-t3);
      }

      t1=(u-v1);
      t3=(d-v3);
      if(t1<0) t1+=y;
  
    };//Fim do loop principal


    //Ajuste fino do resultado
    v=(d-(x*u))/y;
    if(f2==true){
      int64_t temp=u;
      u=v; v=temp;
    }
    
    u=-(v*q);

    //Resultado
    yield_result:
      if(f1==true){
        (*a)=u; (*b)=v;
      }
      else{
        (*a)=v; (*b)=u;
      }
      if(bit_shift>0) (*gcd)=(d<<bit_shift);
      else (*gcd)= d;

};

//*******************************************************************************************************************************************
//FIM DO HEADER
#endif
