//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO elliptic_curve_naive_point_counting.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o elliptic_curve_naive_point_counting elliptic_curve_naive_point_counting.c


//Cabeçalho
#include"elliptic_curve_naive_point_counting.h"
#include<stdio.h>

//Função principal
int main(){

  //Variáveis locais
  int64_t point_count, a, b, p;


  //Procedimentos
    //Recebendo input do usuário: ajuste da curva
    printf("Parâmetro 'a' da curva elíptica: ");
    scanf("%li", &a);
    printf("Parâmetro 'b' da curva elíptica: ");
    scanf("%li", &b);
    printf("Primo 'p'característica do corpo sobre o qual a curva é definida: ");
    scanf("%li", &p);

    //Calculando o número de pontos na curva elíptica  y²=x³+ax+b (mod p)
    printf("Curva elíptica: y²=x²+%lix+%li mod %li\n", a, b, p);
    point_count=elliptic_curve_point_counting(a, b, p);
    printf("Número de pontos na curva elíptica: %li\n", point_count);


  //Finalizando a aplicação
  return 0;

}

