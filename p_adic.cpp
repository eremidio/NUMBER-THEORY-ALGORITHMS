//VAMOS ESCREVER UM PROGRAMA EM C++ QUE CALCULA A EXPANSÃO P-ÁDICA DE NÚMEROS INTEIROS E RACIONAIS
//COMPILAR ESTE PROGRAMA COM O COMANDO: g++ -o p_adic p_adic.cpp

/*
NÚMEROS P-ÁDICOS SÃO UMA EXTENSÃO DOS NÚMEROS RACIONAIS DIFERENTES DOS NÚMEROS REAIS, AO PASSO QUE OS 
REAIS USAM O VALOR ABSOLUTO PARA DEFINIR A MÉTRICA (DISTÂNCIA DE UM PONTO NA RETA REAL), NOS P-ÁDICOS
USA-SE A FUNÇÃO ν(p)=k, QUE DETERMINA A MAIORA POTÊNCIA DEUM PRIMO p QUE DIVIDE UM INTEIRO n. 
ESPECIFICAMENTE A MÉTRICA É DADA POR |n|(p)=p^(-k). 

TAL QUAL OS NÚMEROS REAIS, NÚMEROS P-ÁDICOS ADMITEM UMA EXPANSÃO EM DIGITOS EM UMA BASE p, QUE PODE
SER FINITA OU NÃO (NESTE CASO OS DÍGITOS SÃO LIDOS DA ESQUERDA PARA A DIREITA).

PARA MAIORES INFORMAÇÕES SOBRE NÚMEROS P-ÁDICOS: https://en.wikipedia.org/wiki/P-adic_number
                                                 

*/



//***************************************************************************************************************************
/*CABEÇALHO*/
#include<iostream>
#include<string>
#include<cstdlib>
#include<cmath>
using namespace std;

//***************************************************************************************************************************
//Função que calcula a expansão p-ádica de um inteiro positivo
void p_adic_positive_integer(long long int number, long long int prime){

  //VÁRIÁVEIS LOCAIS
  string result="";
  long long int power_prime, value, digit;
  int i;



  //PROCEDIMENTOS
    //CASOS BASE
    if(number==prime){
      cout<<"Coeficientes da expansão p-ádica de "<<number <<" na base "<<prime<<": 1, 0, \n";
      return;
    };

    if(number<prime){
      cout<<"Coeficientes da expansão p-ádica de "<<number <<" na base "<<prime<<": "<<number<<", \n";
      return;
    };

    //CALCULANDO A VALUAÇÃO P-ÁDICA DO NÚMERO CUJA EXPANSÃO P-ÁDICA SERÁ CALCULADA
    value=number;
    power_prime=1;
    i=0;

    while(power_prime<value){
      power_prime*=prime;
      ++i;
    };

  power_prime/=prime;


    //CALCULANDO O RESULTADO
    do{
        digit=value/power_prime;
        result+=to_string(digit);
        result+=", ";


        value=value%power_prime;
        power_prime=power_prime/prime;


        if(value<prime){
          result+=to_string(value);//ADICIONANDO O ÚLTIMO DIGITO AO RESULTADO
          result+=", ";
        };

    }while(power_prime!=1);


    //EXIBINDO O RESULTADO
    result+="...";
    cout<<"Coeficientes da expansão p-ádica de "<<number <<" na base "<<prime<<": "<<result<<'\n';

};


//***************************************************************************************************************************
//Função que calcula a expansão p-ádica de um inteiro negativo
void p_adic_negative_integer(long long int number, long long int prime){


  //VARIÁVEIS LOCAIS
  long long int * positive_digits_array=NULL;
  long long int * negative_digits_array=NULL;
  int digits_array_size;
  int i;
  long long int power_prime, value;
  string result="..., ";
  result+=to_string(prime-1);
  result+=", ";


  //PROCEDIMENTOS
    //CÁLCULO DOS DIGITOS DA EXPANSÃO P-ÁDICA DO MÓDULO DE UM NÚMERO NEGATIVO
    value=number*(-1);


      //CASO BASE
      if(value==prime){
        digits_array_size=2;
        positive_digits_array=(long long int*)realloc(positive_digits_array, 2*sizeof(long long int));
        positive_digits_array[0]=1;
        positive_digits_array[1]=0;
        goto negative_step;
      };

      if(value<prime){
        digits_array_size=1;
        positive_digits_array=(long long int*)realloc(positive_digits_array, sizeof(long long int));
        positive_digits_array[0]=value;
        goto negative_step;
      };


    //CASO GERAL
    if(value>prime){
      power_prime=1;
      digits_array_size=0;

      //CALCULANDO A VALUAÇÃO P-ÁDICA DO NÚMERO CUJA EXPANSÃO P-ÁDICA SERÁ CALCULADA
      while(power_prime<value){
        power_prime*=prime;
      };
      power_prime/=prime;

      //CALCULANDO OS DÍGITOS DA EXPANSÃO P-ÁDICA DO MÓDULO DE UM NÚMERO POSITIVO
      do{
          digits_array_size++;
          positive_digits_array=(long long int*)realloc(positive_digits_array, digits_array_size*sizeof(long long int));
          positive_digits_array[digits_array_size-1]=value/power_prime;


          //REDEFININDO OS VALORES
          value=value%power_prime;
          power_prime=power_prime/prime;


          if(value<prime){
            digits_array_size++;
            positive_digits_array=(long long int*)realloc(positive_digits_array, digits_array_size*sizeof(long long int));
            positive_digits_array[digits_array_size-1]=value;
            break;
          };

       }while(power_prime!=1);

    };



    //CÁLCULO DOS DIGITOS DA EXPANSÃO P-ÁDICA DE UM NÚMERO NEGATIVO
    negative_step:


    //AJUSTANDO O ARRAY DE INDEXES
    negative_digits_array=(long long int*)realloc(negative_digits_array, digits_array_size*sizeof(long long int));

    //CALCULANDO OS ELEMENTOS DESTE ARRAY
    for(i=0; i< digits_array_size; ++i){
      if(i!=digits_array_size-1){
        negative_digits_array[i]=prime-positive_digits_array[i]-1;
        result+=to_string(negative_digits_array[i]);
        result+=", ";
                                };

      if(i==digits_array_size-1){
        negative_digits_array[i]=prime-positive_digits_array[i];
        result+=to_string(negative_digits_array[i]);
        result+=", ";
                                };
    };


    //EXPRESSANDO O RESULTADO FINAL
    cout<<"Coeficientes da expansão p-ádica de "<<number <<" na base "<<prime<<": "<<result<<"\n";

    //LIMPANDO O CACHÊ DE MEMÓRIA
    free(negative_digits_array);
    free(positive_digits_array);


};



//***************************************************************************************************************************
//Função que calcula aexpansão p-ádica de um número racional provido das seguintes condições:
    //1. Numerador<denominado
    //2. Base, numerador e denominador relativamente primos

/*

As três funções providas servem para qualquer racional ou inteiro, bastando apenas algumas modificações na hora de expressar o resultado.

Por exemplo: 

O 30=1×5^2 +1×5 +0×5^0 na base 5 fica 110.

Já o -1= 0, ...44444 na base 5 . 
Por esta mesma razão -1 na base 7 é 0, ...66666.

Usa-se essa notação --- --> digitos da esquerda para a direita. 


Implementou-se a expansão de frações (racionais) apenas no caso em que o numerador é menor do que o denominador.
Para números com numerador maior que denominador é só reduzir a este caso, exemplo:

A expansão p-ádica de 2/9 na base 7 é:

0,....530530531

128/9= 14+2/9  

Assim: 

A expansão de 14 na base 7 é

14= 2×7^1+0×7^0 ==20

Assim a expansão p-ádica de 128/9 base 7 é:

            0,....530530531
          +              20
            _______________
            0,....530530551


Como 11/5=2 +1/5 e 2 na base 3 é 2=2×3^0 ==2


             0,......121012102
           +                 2
            __________________
              0,......12101211

(2+2= 4 = 1×3^1+1×3^0 == 11 na base 3, fica um dígito o segundo sobe na soma).


Fatores primos no numerador acrescenta 0 no fim, já no denominador é só usar um .ponto para separar parcelas com expoentes negativos. 


Para 27/5 (3^3×1/5) na base 3:
0,......121012102000


Similarmente 
Para 1/45 (1/3×3^(-2)) na base 3:
0,......1210121.02
*/


void p_adic_rational(long long int numerator, long long int denominator, long long int prime){


  //VARIÁVEIS LOCAIS
  long long int periodic_length;
  long long int constant1, constant2;
  long long int power_prime, value, residue1;
  long long int* digits_array=NULL;
  long long int header_integer=1;
  int i;
  string result="..., ";


  //PROCEDIMENTOS
    //CALCULANDO A EXTENSÃO PARTE PERIÓDICA DA EXPANSÃO
    power_prime=prime;
    periodic_length=1;

    do{
        periodic_length++;
        residue1=power_prime%denominator;

        //CONDIÇÃO PARA ENCERRAR O LOOP
        if(residue1==1) break;

        //BUSCANDO AS PRÓXIMAS POTÊNCIAS DA BASE
        power_prime=power_prime*prime;
    }while(true);



    //CALCULANDO O FATOR MULTIPLICATIVO DA FRAÇÃO 1/(1-prime^periodic_length)
    constant1=denominator-numerator;
    constant2=constant1*(power_prime-1);
    constant2=constant2/denominator;



    //CALCULANDO OS DIGITOS DA EXPANSÃO P-ÁDICA
    digits_array=(long long int*)realloc(digits_array, periodic_length*sizeof(long long int));
    power_prime=power_prime/prime;
    value=constant2;


    for(i=0; i<periodic_length; ++i){
      digits_array[i]=static_cast<long long int>(value/power_prime);


      //REAJUSTANDO VARIÁVEIS
      value=value%power_prime;
      power_prime=power_prime/prime;
      if(power_prime==0) break;
    };



    //EXIBINDO O RESULTADO
    for(i=0; i<periodic_length-1; ++i){
      result+=to_string(digits_array[i]);
      result+=", ";
    };

    for(i=0; i<periodic_length-1; ++i){
      result+=to_string(digits_array[i]);
      result+=", ";
    };


    //AJUSTANDO O ÚLTIMO DÍGITO
    for(i=0; i<periodic_length-1; ++i){
      if(i==(periodic_length-2))
        digits_array[i]=(digits_array[i]+header_integer)%prime;
        result+=to_string(digits_array[i]);
        result+=", ";
    };

    cout<<"Coeficientes da expansão p-ádica de "<<numerator<<"/"<<denominator <<" na base "<<prime<<": "<<result<<'\n';


  //LIBERANDO O CACHÊ DE MEMÓRIA
  free(digits_array);


                                                                                        };


//***************************************************************************************************************************
//FUNÇÃO PRINCIPAL
int main(){

  //VARIÁVEIS
  long long int number1, number2, denominator, numerator, prime;

  //PROCEDIMENTOS 
    //RECEBENDO INPUT DO USUÁRIO
    cout<<"Inteiro primo: ";
    cin>>prime;
    cout<<"Inteiro positivo: ";
    cin>>number1;
    cout<<"Inteiro negativo: ";
    cin>>number2;
    cout<<"Numerador de fração: ";
    cin>>numerator;
    cout<<"Denominador de fração: ";
    cin>>denominator;

    

    //TESTE 1: CALCULANDO A EXPANSÃO P-ÁDICA PARA UM NÚMERO INTEIRO POSITIVO
    p_adic_positive_integer(number1, prime);

    //TESTE 2: CALCULANDO A EXPANSÃO P-ÁDICA PARA UM NÚMERO INTEIRO POSITIVO 
    p_adic_negative_integer(number2, prime);

    //TESTE 3: CALCULANDO A EXPANSÃO P-ÁDICA PARA UM NÚMERO RACIONAL
    p_adic_rational(numerator, denominator, prime);


    //FINALIZANDO O PROGRAMA
    return 0;
          };
