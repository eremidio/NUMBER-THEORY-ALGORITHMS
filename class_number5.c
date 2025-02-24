//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO class_number5.h 
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o class_number5 class_number5.c -lm 


//Cabeçalho
#include"class_number5.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int64_t d;

  
  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número inteiro correspondente a um discriminante fundamental: ");
    scanf("%li", &d); d=(-1)*d;

    //Calculando o número de classe
    printf("h(%li)=%li (fórmula analítica)\n", d, class_number_analytical(d));


  //Finalizando a aplicação
  return 0;

}

