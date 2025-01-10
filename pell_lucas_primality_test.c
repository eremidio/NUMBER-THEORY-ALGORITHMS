//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO  ARQUIVO pell_lucas_primality_test.h 
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o pell_lucas_primality_test pell_lucas_primality_test.c


//Cabeçalho
#include"pell_lucas_primality_test.h"
#include<stdio.h>



//Função principal
int main(){


  //Váriaveis
  int64_t number, i;
  int64_t counter=0;


  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um limitante superior para a sequência de possíveis números: ");
    scanf("%li", &number);


    //Executando o teste
    printf("Eis sua sequência de (prováveis) números primos:\n");

    for(i=1; i<=number; ++i){
      if(pell_lucas_primality_test(i)==true){
      printf("%li, ", i);
      counter+=1;
      };
    };
  
    printf("...\n");
    printf("Número de primos encontrados até %lu: %lu\n", number, counter);

  //Finalizando a aplicação
  return 0;

}
