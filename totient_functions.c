//VAMOS CRIAR UM PROGRAMA PARATESTAR AS ROTINAS DEFINIDAS NO ARQUIVO totient_functions.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o totient_functions totient_functions.c -lm


//Cabeçalho
#include"totient_functions.h"
#include<stdio.h>
#include<stdint.h>


//Função principal
int main(){

  //Variáveis locais
  uint64_t number1;


  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número inteiro: ");
    scanf("%lu", &number1);



    //Testando funções totientes
    for(uint64_t i=1; i<=number1; ++i){
      printf("λ(%lu)=%lu, ", i, carmichael_function(i));
      printf("J(%lu, 2)=%lu, ", i, jordan_totient_function(i, 2));
      printf("Ψ(%lu, 2)=%lu, ", i, dedekind_psi_function(i, 2));
    }
    printf("...\n");
  

  //Finalizando a aplicação
  return 0;

} 
