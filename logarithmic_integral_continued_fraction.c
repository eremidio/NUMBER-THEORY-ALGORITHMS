//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO logarithm_integral_continued_fraction.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o logarithmic_integral_continued_fraction logarithmic_integral_continued_fraction.c


//Cabeçalho
#include"logarithmic_integral_continued_fraction.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  long double li_x, x;
  
  //Proecedimentos
    //Recebendo input do usuário
    printf("[Número real] x: ");
    scanf("%Lf", &x);

    //Calculando um valor aproximado da função li(x)
    li_x=logarithmic_integral_continued_fraction(x);
    printf("li(%Lf)=%.10Lf\n", x, li_x);


  //Finalizando a aplicação
  return 0;
  

}
