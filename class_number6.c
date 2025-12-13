//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS IMPLEMENTADAS NO ARQUIVO class_number6.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o class_number6 class_number6.c -lm


//Cabeçalho
#include"class_number6.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int64_t D, minus_D;


  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número inteiro correspondente a um discriminante fundamental: ");
    scanf("%li", &D);

    minus_D = (-1)*D;

    //Calculando o número de classe
    if(is_fundamental_discriminant(minus_D)==true){

      printf("[Limitante inferior] h(%li)>%li\n", minus_D, gross_zagier_lower_bound(D));
      printf("[Limitante superior] h(%li)<%li\n", minus_D, summation_upper_bound(D));
      printf("[Aproximação] h(%li)≃%li\n", minus_D, summation_approximation(D));

    }
    else printf("%li não é um discriminante fundamental.\n", minus_D);


  //Finalizando a aplicação
  return 0;

}
