//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO hurwitz_class_number.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o hurwitz_class_number hurwitz_class_number.c -lm  



//Cabeçalho
#include"hurwitz_class_number.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int64_t N;

  //Procedimentos
    //Recebendo input do usuário
    printf("[Inteiro] N: ");
    scanf("%li", &N);

    //Computando o número de classe de Hurwitz
    struct hurwitz_fraction H=hurwitz_class_number_reduced_forms(N);
    if(H.num%H.den==0) printf("H(%li)=%li\n", N, (H.num/H.den));
    else printf("H(%li)=%li/%li\n", N, H.num, H.den);


  //Finalizando a aplicação
  return 0;

}


