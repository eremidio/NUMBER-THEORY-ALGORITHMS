//VAMOS CRIAR UM PROGRAMA QUE COMPUTA A FUNÇÃO TOTIENTE DE CARMICHAEL λ(n)

/*

  PARA MAIORES INFORMAÇÕES: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/totient_functions.h

*/


//**************************************************************************************************************
//CABEÇALHO
#ifndef CARMICHAEL_FUNCTION_SIEVING_H
#define CARMICHAEL_FUNCTION_SIEVING_H
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>


//**************************************************************************************************************
//DECLARAÇLÃO DE FUNÇÕES
int32_t gcd_s32(int32_t, int32_t);
bool* prime_sieving(int32_t);
int32_t* compute_carmichael_function(int32_t);


//**************************************************************************************************************
//FUNÇÕES
//Função que calcula o gcd de dois inteiros de 32 bits
int32_t gcd_s32(int32_t a, int32_t b){

  if(b==0) return a;
  else return gcd_s32(b, (a%b));

};

//Função que computa um array de números primos usando o crivo de Eratóstenes
bool* prime_sieving(int32_t n){

  //Variáveis locais
  bool* prime_power_array = (bool*) calloc((n+1), sizeof(bool));


  //Procedimentos
    //Ajuste do array de valores
    for(int32_t i=2; i<=n; ++i) prime_power_array[i]=true;


    //Computando números primos
    for(int32_t i=2; (i*i)<=n; ++i){
      if(prime_power_array[i]==true){
        for(int32_t j=(2*i); j<=n; j+=i) prime_power_array[j]=false;
      }
    };



  //Resultado
  return prime_power_array;

};


//Função que computa um cojunto de valores da função totiente de Carmichael
int32_t* compute_carmichael_function(int32_t n){

  //Variáveis locais
  int32_t* carmichael_function_array = (int32_t*)calloc(n+1, sizeof(int32_t));
  bool* prime_power_array = prime_sieving(n+1);
  int64_t index=0, phi=0, gcd_value=0;

  //Procedimentos
     //AJuste de elementos do array
     for(int32_t i=0; i<=n; ++i)
       carmichael_function_array[i]=0;

    //Pré-computando a função de carmichael usando a relação entre a função λ(n) e a função totiente de Euler φ(n)
      //n=1
      carmichael_function_array[1]=1;

      //p=2
      carmichael_function_array[2]=1; carmichael_function_array[4]=2;//λ(n)=φ(n) se  n=2, 4
      phi=2; index=8;//φ(p)=(p-1) se p é primo

      while(1){ //λ(n)=(1/2)φ(n) se  n=2^r com r≳3
        carmichael_function_array[index]=phi;
        phi*=2; index*=2;
        if(index>n) break;

      }

      //p é primo impar
      for(int32_t p=3; p<=n; p+=2){

        if(prime_power_array[p]==true){

          phi=(p-1); index=p; //φ(p)=(p-1)p^(r-1) se p é primo ímpar e r é inteiro
          carmichael_function_array[index]=phi;

          while(1){
            carmichael_function_array[index]=phi;
            phi*=p; index*=p;
            if(index> n) break;
          }

        };

      };

      //Computando a função de λ(n) para compostos com distintos fatores primos
      for(int32_t k=1; k<=n; ++k){
        for(int32_t l=(k+1); l<=n; ++l){
          if(l>n/k) break; index=l*k;
          if(gcd_s32(k, l)>1) continue;

          phi=((int64_t)carmichael_function_array[l]*(int64_t)carmichael_function_array[k]);
          gcd_value = gcd_s32(carmichael_function_array[l], carmichael_function_array[k]);
          carmichael_function_array[index]=phi/gcd_value;
   
        }
      };

      
    //Limpando o cachê de memória
    if(prime_power_array) free(prime_power_array); prime_power_array=NULL;


  //Resultado
  return carmichael_function_array;

};


//**************************************************************************************************************
//FIM DO HEADER
#endif
