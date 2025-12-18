//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO quadratic_form_composition.h 
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o quadratic_form_composition quadratic_form_composition.c -lm


//Cabeçalho
#include"quadratic_form_composition.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  struct binary_quadratic_form f1, f2, f3;  

  //Procedimentos
    //Recebendo input do usuário
    printf("[Coeficiente de  f(x, y)=ax²+bxy+cy²] a:");
    scanf("%li", &f1.a);
    printf("[Coeficiente de  f(x, y)=ax²+bxy+cy²] b:");
    scanf("%li", &f1.b);
    printf("[Coeficiente de  f(x, y)=ax²+bxy+cy²] c:");
    scanf("%li", &f1.c);

    //Recebendo input do usuário
    printf("[Coeficiente de  f(x, y)=ax²+bxy+cy²] a:");
    scanf("%li", &f2.a);
    printf("[Coeficiente de  f(x, y)=ax²+bxy+cy²] b:");
    scanf("%li", &f2.b);
    printf("[Coeficiente de  f(x, y)=ax²+bxy+cy²] c:");
    scanf("%li", &f2.c);
  
    //Aplicando o algoritmo de composição de formas quadráticas 
    f1=reduce_quadratic_form(f1);
    f2=reduce_quadratic_form(f2);
    print_binary_quadratic_form(f1); printf("\n");
    print_binary_quadratic_form(f2); printf("\n");

    assert(binary_quadratic_form_discriminant(f1)==binary_quadratic_form_discriminant(f2) && 
          "Apenas formas quadráticas de mesmo determinante podem ser combinadas\n");
   
    f3=quadratic_form_composition(f1, f2);
    printf("[Composição de formas quadráticas] ");
    print_binary_quadratic_form(f3); printf("\n");


  //Finalizando a aplicação
  return 0;

}
