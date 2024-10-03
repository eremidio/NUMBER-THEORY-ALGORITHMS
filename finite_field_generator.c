//VAMOS CRIAR UM PROGRAMAPARA TESTAR ASROTINAS CRIADAS NO ARQUIVO finite_field_generator.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o finite_field_generator finite_field_generator.c -lm


//Cabeçalho
#include"finite_field_generator.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  uint64_t prime, generator;

  
  //Procedimentos
    //Recebendo input do usuário
    printf("[Característica de F(p)] Primo: ");
    scanf("%lu", &prime);

    //Computando um gerador em F(p)
    generator=finite_field_generator(prime);
    printf("Gerador de F(%lu)=%lu\n", prime, generator);
  

  //Finalziando a aplicação
  return 0;

}
