//VAMOS CRIARUM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO quadratic_form_reduction.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o quadratic_form_reduction quadratic_form_reduction.c -lm


//Cabeçalho
#include"quadratic_form_reduction.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  struct binary_quadratic_form f, red_f;
  int64_t delta, red_delta;


  //Procedimentos
    //Recebendo input do usuário
    printf("[Coeficiente de  f(x, y)=ax²+bxy+cy²] a:");
    scanf("%li", &f.a);
    printf("[Coeficiente de  f(x, y)=ax²+bxy+cy²] b:");
    scanf("%li", &f.b);
    printf("[Coeficiente de  f(x, y)=ax²+bxy+cy²] c:");
    scanf("%li", &f.c);

    //Calculando o discriminante e exibindo a forma 
    print_binary_quadratic_form(f); printf("\n");
    printf("[Discriminante] Δ(f): %li\n", binary_quadratic_form_discriminant(f));


    //Redução da forma quadrática
    red_f=reduce_quadratic_form(f);
    printf("[Forma quadrática reduzida] ");
    print_binary_quadratic_form(red_f); printf("\n");
    printf("[Discriminante] Δ(f): %li\n", binary_quadratic_form_discriminant(red_f));


  //Finalizando a aplicação
  return 0;

}
