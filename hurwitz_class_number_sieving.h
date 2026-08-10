//VAMOS CRIAR UM PROGRAMA PARA COMPUTAR NÚMEROS DE CLASSES DE HURWITZ DE FORMA RECURSIVA

/*

SEJA λ(n)= (1/2) Σ min(n/d, d), ONDE A SOMA É REALIZADA SOBRE TODOS OS DIVISORES DE n TAL QUE d≲√n. O TEOREMA DE
HURWITZ-EICHLER PERMITE COMPUTAR O SOMATÓRIO DE NÚMEROS DE CLASSE DE HURWITZ EM TERMOS DESSA FUNÇÃO λ(n) E DA
FUNÇÃO DE SOMA DE DIVISORES DE UM INTEIRO σ(n). COMO UM COROLÁRIO DESTE TEOREMA PODE-SE MOSTRAR QUE: SE
N=3 (mod 4) ENTÃO H(N)={σ(n)/3}-λ(n)-2{Σ H(n-4s²)} COM O SOMÁRIO FEITO SOBRE s=1,..., [√(N/4)-1]; PARA N=0 (mod 4)
TÊM-SE QUE H(N)={σ(n+1)/6}-{λ(n+1)/2}-2{Σ H(n-4s(s+1))} COM A SOMA FEITA SOBRE s=1,..., (√(N+1)-1)/2.

TAIS FÓRMULAS SÃO ÚTEIS EM COMPUTAR TABELAS DE NÚMEROS DE CLASSE DE HURWITZ PARA UMA DADO INTERVALO DE FORMA
RECURSIVA. ELAS ESTÃO DIRETAMENTE  RELACIONADAS A TEORIA DA FORMAS MODULARES DE PESO 3/2, MAIS ESPECIFICAMENTE
SOBRE O COMPORTAMENTO DAS SÉRIES DE FOURIER DO TIPO Σ {H(N)e^(i2πNτ)} SOB A TRANSFORMAÇÃO LINEAR FRACIONÁRIA
τ ->(aτ+b)/(cτ+d).


PARA MAIORES INFORMAÇÕES: A Course In Computational Algebraic Number Theory by Henri Cohen


*/


//***************************************************************************************************************
//CABEÇALHO
#ifndef HURWITZ_CLASS_NUMBER_SIEVE_H
#define HURWITZ_CLASS_NUMBER_SIEVE_H
#include"hurwitz_class_number.h"
#include"sum_of_divisors_lambert_series.h"
#include<stdlib.h>


//***************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
struct hurwitz_fraction* hurwitz_lambda_function(int64_t);
struct hurwitz_fraction* hurwitz_class_number_recursive(int64_t, struct hurwitz_fraction[]);


//***************************************************************************************************************
//FUNÇÕES
//Função que computa um conjunto de valores da função λ(n) de Hurwitz
struct hurwitz_fraction* hurwitz_lambda_function(int64_t n){

  //Variáveis locais
  struct hurwitz_fraction* hurwitz_lambda_array= (struct hurwitz_fraction*)calloc(n+1, sizeof(struct hurwitz_fraction));

  
  //Procedimentos
    //Inicializando os elementos do array
    for(int64_t k=0; k<=n; ++k){
      hurwitz_lambda_array[k].num=0;
      hurwitz_lambda_array[k].den=0;
    }

    //Computando a soma Σ min(n/d, d) sobre os divisores d de n
    for(int64_t i=1; i<=n; ++i){
      for(int64_t j=i; j<=n; j+=i){
        if((i*i)<=j)
          hurwitz_lambda_array[j].num=hurwitz_lambda_array[j].num+i;
        else
          hurwitz_lambda_array[j].num=hurwitz_lambda_array[j].num+(j/i);
      }
    };
    
    //Ajuste dos denominadores das frações
    for(int64_t l=1; l<=n; ++l){

      int64_t s=hurwitz_lambda_array[l].num;
      
      if((s&1))
        hurwitz_lambda_array[l].den=2;
      else{
        hurwitz_lambda_array[l].num>>=1;
        hurwitz_lambda_array[l].den=1;

      }
        
    };


  //Return 
  return hurwitz_lambda_array;

};


//Função que computa o número de classe de Hurwitz de forma recursiva
struct hurwitz_fraction* hurwitz_class_number_recursive(int64_t n, struct hurwitz_fraction hurwitz_lambda_array[]){


  //Variáveis locais
  struct hurwitz_fraction* hurwitz_class_number_array = (struct hurwitz_fraction*)calloc(n+1, sizeof(struct hurwitz_fraction));
  int32_t* sum_of_divisors_array = compute_sum_of_divisors_function(n+1);
  struct hurwitz_fraction adder1={0,1}, adder2={0,1}, sum={0,1};
  uint64_t min=0, max=0, r=0;


  //Procedimento
    //Ajuste do elementos iniciais do array
    hurwitz_class_number_array[0].num=(-1); hurwitz_class_number_array[0].den=12;
    if(n<1) goto end_program;
    

    //Loop principal: computando os elementos do array recursivamente
      for(int64_t i=1; i<=n; ++i){
      
        r=(i&3); //r = N (mod 4)

        //Casos bases: N=1,2 mod(4)
        if(r==1 || r==2){
          hurwitz_class_number_array[i].num=0; hurwitz_class_number_array[i].den=1;
          continue;
        };

        if(i==3){
          hurwitz_class_number_array[i].num=1; hurwitz_class_number_array[i].den=3;
          continue;
        };

        if(i==4){
          hurwitz_class_number_array[i].num=1; hurwitz_class_number_array[i].den=2;
          continue;
        };



        //Caso 2: N=0 mod(4)
        if(r==0){

          //H(N) = σ(N+1)/6 - λ(N+1)/2
          adder1.num= sum_of_divisors_array[i+1]; adder1.den=6; //adder1 = σ(N+1)/6

          adder2.num= (-1)*hurwitz_lambda_array[i+1].num;  adder2.den=hurwitz_lambda_array[i+1].den;
          adder2.den*=2; //adder2 = -λ(N+1)/2

          hurwitz_class_number_array[i] = hurwitz_fraction_add(adder1, adder2); //H(N) = σ(N+1)/6 - λ(N+1)/2

          min=1;
          max=(sqrt(i+1)-1)/2;

      
          sum=hurwitz_zero; //Inicializando a soma
          for(int64_t s=min; s<=max; ++s)
            sum=hurwitz_fraction_add(
              sum,
              hurwitz_class_number_array[i-(4*s*(s+1))]
            );
          sum.num=(-1)*sum.num;
          hurwitz_class_number_array[i] = hurwitz_fraction_add(hurwitz_class_number_array[i], sum); //H(N) = σ(N+1)/6 - λ(N+1)/2 - Σ H(N-4s(s+1))
                                                                                                    //s=1,...,(√(N+1)-1)/2

        };//Fim do caso 2


        //Caso 3: N=3 mod(4)
        if(r==3){

          //H(N) = σ(N)/3 - λ(N)
          adder1.num= sum_of_divisors_array[i]; adder1.den=3; //adder1 = σ(N)/3
          adder2.num= (-1)*hurwitz_lambda_array[i].num; adder2.den=hurwitz_lambda_array[i].den; //adder2 = -λ(N)
          hurwitz_class_number_array[i] =  hurwitz_fraction_add(adder1, adder2); //H(N) = σ(N)/3 - λ(N)

          min=1;
          max=sqrt(i>>2);

     
          sum=hurwitz_zero;
          for(int64_t s=min; s<=max; ++s)
            sum=hurwitz_fraction_add(
              sum,
              hurwitz_class_number_array[i-(4*s*s)]
            );
          sum.num=(-2)*sum.num;

          hurwitz_class_number_array[i] = hurwitz_fraction_add(hurwitz_class_number_array[i], sum); //H(N) = σ(N)/3 - λ(N) - 2Σ H(N-4s²)
                                                                                                    //s=1,...,floor(√(N/4))

        };//Fim do caso 3


      };


    //Limpando o cachê de memória
    end_program:
    if(sum_of_divisors_array) free(sum_of_divisors_array); sum_of_divisors_array=NULL;


  //Resultado
  return hurwitz_class_number_array;

};

//***************************************************************************************************************
//FIM DO HEADER
#endif
