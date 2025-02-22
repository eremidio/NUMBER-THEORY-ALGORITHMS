//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO HEADER class_number3.h
//COMPILAR ESTE PROGRAMA: gcc -o class_number3 class_number3.c -lm


//Cabeçalho
#include"class_number3.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int64_t t, u, d;
  int64_t h;


  //Procedimentos
    //Recebendo input do usuário
    printf("[Discriminante do corpo quadrático real] d: ");
    scanf("%li", &d);

    //Computando uma unidade fundamental
    compute_fundamental_unit(&t, &u, d);
    printf("Unidade fundamental de Q(√%li): η=(1/2)(%li+%li√%li)\n\n", d , t, u, d);

    //Computando o número de classe
    printf("h(%li)=%li (via fórmula do número de classe)\n", d, class_number_formula_positive_discriminant(d));


  //Finalizando a aplicalção
  return 0;

}
