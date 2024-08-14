//VAMOS CRIARUM PROGRAMA QUE TESTA A PRIMALIDADE DE UM INTEIRO n USANDO A FATORAÇÃO DE n-1
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o order_primality_test order_primality_test.c -O2 -lm

/*
O SEGUINTE TEOREMA PODE SER USADO PARA TESTAR DE FORMA SIMPLES A PRIMALIDADE DE UM INTEIRO n.

TEOREMA: SEJA n=2rq+1 UM INTEIRO ÍMPAR E q UM NÚMERO PRIMO. SE q≳(r-1)/2 e EXISTE UM INTEIRO
a TAL QUE a^(n-1)=1 (mod n) E a^(2r) ≠ 1 (mod n), ENTÃO n É PRIMO.

O LIMITE PARA q NO TEOREMA ACIMA PODE SER REDUZIDO CONFORME A PROPOSIÇÃO ABAIXO:

TEOREMA: SEJA n=2rq+1 UM INTEIRO ÍMPAR E q UM NÚMERO PRIMO. SE q≳(r-2)/4 e EXISTE UM INTEIRO
a TAL QUE a^(n-1)=1 (mod n) E a^(2r) ≠ 1 (mod n), ENTÃO: OU n É PRIMO OU n=p² COM p=2q+1
PRIMO E a^(p-1)= 1 (mod p²).

USAREMOS O PRIMEIRO TEOREMA PARA TESTAR A PRIMALIDADE DE NÚMEROS INTEIROS DA ORDEM 10^18.
OS DOIS TEOREMAS ACIMA FUNCIONAM BEM SE (n-1) TIVER UM FATOR PRIMO DA ORDEM DE n^(1/2).

PARA MAIORES INFORMAÇÕES: Number Theoretical Algorithms in Criptography by O. N. Vasilenko

*/

//***********************************************************************************************************************************************************
//CABEÇALHO
#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<math.h>
#include"mod_bin_exponentiation128.h" 


//***********************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
uint64_t calculate_prime_factor(uint64_t);
bool order_primality_test(uint64_t);

//***********************************************************************************************************************************************************
//FUNÇÕES
//Função que detremina um fator primo de N satisfazendo as condições do teorema acima
uint64_t calculate_prime_factor(uint64_t n){

  //Variáveis locais
  uint64_t prime_factor=0;
  uint64_t root=sqrt(n);
  uint64_t N=(n-1), r=0;


  //Procedimentos
    //Removendo fatores 2 e 3
    while(!(N&1)) N>>=1;
    while((N%3)==0) N/=3;

    //Loop principal
    for(uint64_t i=5; i<=(root+6); i+=6){

      if((N%i)==0){
        r=(N/(2*i));
        if(i>=((r-1)/2)) return i;
      else{
        while((N%i)==0)
          N/=i;
        };
   
      };


      if((N%(i+2))==0){
        r=(N/(2*(i+2)));
        if((i+2)>=((r-1)/2)) return (i+2);
        else{
          while((N%(i+2))==0) N/=(i+2);
        };
      };

    };


    //Fator primo acima de (n-1)^(1/2)
    if(N>1){
      while(!(N&1)) N>>=1;
      return N;
    };

  //Resultado
  return 1;
};


//Função que testa a primalidade de um inteiro usando exponenciações modulares
bool order_primality_test(uint64_t n){

  //Variáveis locais
  uint64_t prime=calculate_prime_factor(n);
  uint64_t r2=(n-1)/prime;
  uint64_t prime_seed[25]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};



  //Procedimentos
    //Testes com primos inferiores a 100 
    for(int i=0; i<25; i++){
      if(n==prime_seed[i]) return true;
      uint64_t divisor =prime_seed[i];
      if(n%divisor==0) return false;
    };

    //Resultado da execução do algoritmo
    if(prime<2){
      printf("Teste inconclusivo.\n");
      return false;
    }
    else{

      for(int i=0; i<25; i++){
        if(mod_bin_pow(prime_seed[i], (n-1), n)==1 && mod_bin_pow(prime_seed[i], r2, n)!=1){
          printf("%lu e %lu certifica a primalidade de %lu.\n", prime_seed[i], prime, n);
          return true;
        };

      };
     };


  //Resultado
  printf("Teste inconclusivo.\n");
  return false;

};


//***********************************************************************************************************************************************************
//FUNÇÃO PRINCIPAL
int main(){
 
  //Váriaveis locais
  uint64_t number;
  bool result;
 
  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número que será testado:\n");
    if(scanf("%lu", &number)!=1);

    //Executando o teste
    result = order_primality_test(number);

  //Finalizando a aplicação
  return 0;

}
