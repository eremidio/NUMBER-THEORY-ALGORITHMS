//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO modular_inverse.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o modular_inverse modular_inverse.c -lm


//Cabeçalho
#include"modular_inverse.h"
#include<stdio.h>

//Função principal
int main(){

  //Variáveis locais
  uint64_t a, n;


  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um inteiro (a): ");
    scanf("%lu", &a);
    printf("Digite um inteiro (n): ");
    scanf("%lu", &n);


    //Cálculando o inverso multiplicativo modular
    printf("%lu⁻¹ (mod %lu)=%lu\n", a, n, modular_inverse(a,n));

  //Finalizando a aplicação
  return 0;

          }
