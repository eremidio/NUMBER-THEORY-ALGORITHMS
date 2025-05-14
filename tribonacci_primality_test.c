//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O TESTE DE PRIMALIDADE USANDO AS SEQUÊNCIAS DE TROBONACCI
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o tribonacci_primality_test tribonacci_primality_test.c


/*
EXISTEM VÁRIAS GENERALIZAÇÕES DA SEQUÊNCIA DE FIBONACCI. UMA VARIANTES DAS CHAMADAS SEQUÊNCIAS DE TRIBONACCI É
DEFINIDA PELAS RELAÇÕES: T(0)=0; T(1)=0, T(2)=9 E T(n)=T(n-1)+3T(n-2)+9T(n-3).

UM SIMPLES TESTE DE PRIMALIDADE BASEIA-SE NA SEGUINTE PROPROSIÇÃO:
PARA n PRIMO T(n)= 0 (mod n) PARA n=1,3 (mod 8) OU T(n)= 4 (mod n) PARA n=5,7 (mod 8), PARA n>5.

PARA MAIORES INFORMAÇÕES: https://trizenx.blogspot.com/2020/01/primality-testing-algorithms.html
                          https://en.wikipedia.org/wiki/Generalizations_of_Fibonacci_numbers#Tribonacci_numbers

*/

//*********************************************************************************************************************************************************************
//CABEÇALHO
#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>

//*********************************************************************************************************************************************************************
//FUNÇÕES 
bool tribonacci_primality_test(uint64_t n){

  //Variáveis locais
  int64_t t0=0, t1=0, t2=9, t3;
  int64_t i;

  //Procedimentos
  for(i=0; i<=(n-3); i++){
    t3=((t2%n)+((3*t1)%n)+((9*t1)%n))%n;

    //Atualizando variáveis para a próxima iteração
    t0=t1;
    t1=t2;
    t2=t3;
  };

  //Resultado da execução do algoritmo
  if(t3==0){
    if((n&7)==1 || (n&7)==3) return true;
  };

  if(t3==4){
    if((n&7)==7 || (n&7)==5)  return true;
  };

  return false;

};

//*********************************************************************************************************************************************************************
//FUNÇÃO PRINCIPAL
int main(){

  //Váriaveis
  uint64_t number;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número que será testado:\n");
    scanf("%lu", &number);

    //Executando o teste
    if(tribonacci_primality_test(number)==true)
      printf("Provável primo encontrado!\n");
    else
      printf("Número composto.\n");

  //Finalizando a aplicação
  return 0;

}
