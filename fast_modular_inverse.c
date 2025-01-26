//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS DO ARQUIVO fast_modular_inversion.h
//COMPILAR ESTE PROGRAMA COM O  COMANDO: gcc -o fast_modular_inverse fast_modular_inverse.c -lm


//Cabeçalho
#include<stdio.h>
#include"fast_modular_inverse.h"


//Função principal
int main(){

  //Variáveis locais
  int64_t n, p, mersenne, inv1, inv2;

  //Procedimentos
    //Recebendo input do usuario
    printf("[Inteiro] n: ");
    scanf("%li", &n);  
    printf("[Inteiro] p: ");
    scanf("%li", &p);
    printf("[Inteiro - primo de Mersenne] m: ");
    scanf("%li", &mersenne);


    //Cálculo dos inversos modulares
    inv1=fast_modular_inverse(n, p);
    //inv2=fast_modular_inverse_mersenne_prime(n, mersenne);

    printf("(%li)⁻¹ mod %li=%li\n", n, p, inv1);
    printf("(%li)⁻¹ mod %li=%li\n", n, mersenne, inv2);


  //Finalizando o programa
  return 0;

}
